%{
#include "subc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int yylex();
int yyerror(char* s);
int get_lineno();

extern FILE *yyin;
SymbolTable *current_table = NULL;
char *current_filename = NULL;
Symbol* current_parsing_func = NULL;

unsigned int hash(char *str) {
    unsigned int h = 0;
    while (*str) h = (h << 5) + *str++;
    return h % HASH_SIZE;
}

void free_single_table(SymbolTable* table) {
    if (table == NULL) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol *cursor = table->buckets[i];
        while (cursor != NULL) {
            Symbol *next_sym = cursor->next;
            if (cursor->name) free(cursor->name);
            free(cursor);
            cursor = next_sym;
        }
        table->buckets[i] = NULL;
    }
}

void push_scope() {
    SymbolTable* new_table = (SymbolTable *)malloc(sizeof(SymbolTable));
    for (int i = 0; i < HASH_SIZE; i++) new_table->buckets[i] = NULL;
    new_table->outer_scope = current_table;
    current_table = new_table;
}

void pop_scope() { 
    if (current_table == NULL) return;
    SymbolTable* old_table = current_table;
    current_table = old_table->outer_scope;
    free_single_table(old_table);
    free(old_table);
}

void pop_scope_without_free() {
    if (current_table != NULL) {
        current_table = current_table->outer_scope; 
    }
}

Symbol* insert_sym(char* name, TypeInfo* info) {
    if (current_table == NULL) return NULL;
    int id = hash(name);
    Symbol* cursor = current_table->buckets[id];
    while(cursor) {
        if(strcmp(cursor->name, name) == 0) return NULL; 
        cursor = cursor->next;
    }
    Symbol* newsym = (Symbol*)malloc(sizeof(Symbol));
    newsym->name = strdup(name);
    newsym->type = info;
    newsym->next = current_table->buckets[id];
    current_table->buckets[id] = newsym;
    return newsym;
}

Symbol* lookup_symbol(char *name) {
    unsigned int h = hash(name);
    SymbolTable *iter_table = current_table;
    while (iter_table != NULL) {
        Symbol *curr = iter_table->buckets[h];
        while (curr) {
            if (strcmp(curr->name, name) == 0) return curr;
            curr = curr->next;
        }
        iter_table = iter_table->outer_scope;
    }
    return NULL;
}

TypeInfo* make_type(TypeKind kind, TypeInfo* base, int size) {
    TypeInfo* t = (TypeInfo*)malloc(sizeof(TypeInfo));
    t->kind = kind;
    t->size = size;
    t->base = base;
    t->fields = NULL;
    return t;
}

ParamList* append_param(ParamList *list, TypeInfo *type) {
    ParamList *new_param = (ParamList*)malloc(sizeof(ParamList));
    new_param->type = type;
    new_param->next = NULL;
    if (list == NULL) return new_param;
    ParamList *cursor = list;
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }
    cursor->next = new_param;
    return list;
}

int check_arguments_match(ParamList *formals, ParamList *actuals) {
    ParamList *f = formals;
    ParamList *a = actuals;
    while (f != NULL && a != NULL) {
        if (f->type != NULL && a->type != NULL) {
            if (f->type->kind != a->type->kind) {
                return 0;
            } else if (f->type->kind == T_ARRAY) {
                if (f->type->base && a->type->base) {
                    if (f->type->base->kind != a->type->base->kind) {
                        return 0;
                    }
                }
            }
        } else {
            return 0;
        }
        f = f->next;
        a = a->next;
    }
    return (f == NULL && a == NULL);
}

Symbol* lookup_struct_member(SymbolTable* table, char* name) {
    if (table == NULL || name == NULL) return NULL;
    
    int idx = hash(name); 
    Symbol* curr = table->buckets[idx];
    
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int check_struct_table_match(SymbolTable* t1, SymbolTable* t2) {
    if (t1 == t2) return 1;
    if (t1 == NULL || t2 == NULL) return 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol* curr1 = t1->buckets[i];
        while (curr1 != NULL) {
            Symbol* curr2 = lookup_struct_member(t2, curr1->name);
            if (curr2 == NULL) return 0;
            
            if (curr1->type == NULL || curr2->type == NULL) return 0;
            if (curr1->type->kind != curr2->type->kind) return 0;
            
            if (curr1->type->kind == T_ARRAY) {
                if (curr1->type->base == NULL || curr2->type->base == NULL) return 0;
                if (curr1->type->base->kind != curr2->type->base->kind) return 0;
            }
            
            curr1 = curr1->next;
        }
    }
    return 1;
}

int yyerror(char* s) {
    return 0;
}
%}

%union {
  int intVal;
  char *stringVal;
  struct TypeInfo *typePtr;
  struct ExprInfo *exprPtr;
  struct ParamList* param_ptr;
}

%left   ','
%right  '='
%left   LOGICAL_OR
%left   LOGICAL_AND
%left   EQUOP
%left   RELOP
%left   '+' '-'
%left   '*' '/' '%'
%right  '!' '&' INCOP DECOP
%left   '[' ']' '(' ')' '.' STRUCTOP

%precedence IF
%precedence ELSE

%token STRUCT RETURN WHILE FOR BREAK CONTINUE SYM_NULL
%token CHAR_CONST STRING RELOP EQUOP LOGICAL_AND LOGICAL_OR 
%token INCOP DECOP STRUCTOP IF ELSE
%token<intVal> INTEGER_CONST TYPE
%token<stringVal> ID

%type <typePtr> type_specifier struct_specifier pointers param_decl
%type <exprPtr> expr binary unary expr_e
%type <param_ptr> args param_list

%%
program
  : ext_def_list
  ;

ext_def_list
  : ext_def_list ext_def
  | %empty
  ;

ext_def
  : type_specifier pointers ID ';' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      if (insert_sym($3, t) == NULL) { error_redeclaration(); }
      free($3);
    }
  | type_specifier pointers ID '[' INTEGER_CONST ']' ';' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      TypeInfo* arr = make_type(T_ARRAY, t, $5);
      if (insert_sym($3, arr) == NULL) { error_redeclaration(); }
      free($3);
    }
  | struct_specifier ';'
  | func_decl compound_stmt {
      pop_scope();
    }
  ;

type_specifier
  : TYPE {
      if ($1 == T_INT) $$ = make_type(T_INT, NULL, 4);
      else $$ = make_type(T_CHAR, NULL, 1);
    }
  | struct_specifier { $$ = $1; }
  ;

struct_specifier
  : STRUCT ID '{' {
      TypeInfo* str_type = make_type(T_NULL, NULL, 0); 
      Symbol* s = insert_sym($2, str_type);
      if (s == NULL) {
          error_redeclaration();
      }
      push_scope();
    } def_list '}' {
      SymbolTable* struct_scope = current_table;
      Symbol* s = lookup_symbol($2);
      if (s != NULL && s->type != NULL) {
          s->type->struct_table = struct_scope;
          $$ = s->type;
      } else {
          $$ = NULL;
      }
      pop_scope_without_free();
      free($2);
    }
  | STRUCT ID {
      Symbol* s = lookup_symbol($2);
      if (s == NULL || s->type == NULL) {
          $$ = NULL;
      } else {
          $$ = s->type;
      }
      free($2);
    }
  ;

func_decl
  : type_specifier pointers ID '(' ')' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      TypeInfo* f = make_type(T_FUNC, t, 0);
      Symbol* s = insert_sym($3, f);
      if (s == NULL) {
          error_redeclaration();
          current_parsing_func = NULL;
      } else {
          current_parsing_func = s;
      }
      push_scope();
      free($3);
    } 
  | type_specifier pointers ID '(' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      TypeInfo* f = make_type(T_FUNC, t, 0);
      Symbol* s = insert_sym($3, f);
      if (s == NULL) {
          error_redeclaration();
          current_parsing_func = NULL;
      } else {
          current_parsing_func = s; 
      }
      push_scope();
      free($3);
    } param_list ')' {
        if (current_parsing_func != NULL && current_parsing_func->type != NULL) {
            current_parsing_func->type->fields = $6;
        }
    }
  ;

pointers
  : '*'    { $$ = make_type(T_ARRAY, NULL, 0); }
  | %empty { $$ = NULL; }
  ;

param_list
  : param_decl                 { $$ = append_param(NULL, $1); }
  | param_list ',' param_decl  { $$ = append_param($1, $3); }
  ;

param_decl
  : type_specifier pointers ID {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      if (insert_sym($3, t) == NULL) { error_redeclaration(); }
      $$ = t; free($3);
    }
  | type_specifier pointers ID '[' INTEGER_CONST ']' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      TypeInfo* arr = make_type(T_ARRAY, t, $5);
      if (insert_sym($3, arr) == NULL) { error_redeclaration(); }
      $$ = arr; free($3);
    }
  ;

def_list
  : def_list def
  | %empty
  ;

def
  : type_specifier pointers ID ';' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      if (insert_sym($3, t) == NULL) { error_redeclaration(); }
      free($3);
    }
  | type_specifier pointers ID '[' INTEGER_CONST ']' ';' {
      TypeInfo* t = $2 ? make_type(T_ARRAY, $1, 0) : $1;
      TypeInfo* arr = make_type(T_ARRAY, t, $5);
      if (insert_sym($3, arr) == NULL) { error_redeclaration(); }
      free($3);
    }
  ;

compound_stmt
  : '{' { push_scope(); } def_list stmt_list '}' { pop_scope(); }
  ;

stmt_list
  : stmt_list stmt
  | %empty
  ;

stmt
  : expr ';' { if ($1) free($1); }
  | RETURN expr ';' {
      if (current_parsing_func && current_parsing_func->type && current_parsing_func->type->base && $2 && $2->type) {
          int ret_kind = current_parsing_func->type->base->kind;
          int expr_kind = $2->type->kind;
          if (ret_kind != expr_kind) {
              error_return();
          }
       }
       if ($2) free($2);
    }
  | BREAK ';'
  | CONTINUE ';'
  | ';'
  | compound_stmt
  | IF '(' expr ')' stmt                 { if ($3) free($3); }
  | IF '(' expr ')' stmt ELSE stmt        { if ($3) free($3); }
  | WHILE '(' expr ')' stmt               { if ($3) free($3); }
  | FOR '(' expr_e ';' expr_e ';' expr_e ')' stmt { if ($3) free($3); }
  ;

expr_e
  : expr   { $$ = $1; }
  | %empty {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
    }
  ;

expr
  : unary '=' expr {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->is_lvalue == 0) {
              error_assignable();
          } else if ($1->type->kind != $3->type->kind) {
              error_incompatible();
          } else if ($1->type->kind == T_NULL) {
              if (!check_struct_table_match($1->type->struct_table, $3->type->struct_table)) {
                  error_incompatible();
              } else {
                  $$->type = $1->type;
                  $$->is_lvalue = $1->is_lvalue;
              }
          } else if ($1->type->kind == T_ARRAY) {
              if ($1->type->base != NULL && $3->type->base != NULL && 
                  $1->type->base->kind == T_NULL && $3->type->base->kind == T_NULL) {
                  
                  if (!check_struct_table_match($1->type->base->struct_table, $3->type->base->struct_table)) {
                      error_incompatible();
                  } else {
                      $$->type = $1->type;
                      $$->is_lvalue = $1->is_lvalue;
                  }
              } else {
                  if ($1->type->base == NULL || $3->type->base == NULL || 
                      $1->type->base->kind != $3->type->base->kind) {
                      error_incompatible();
                  } else {
                      $$->type = $1->type;
                      $$->is_lvalue = $1->is_lvalue;
                  }
              }
          } else {
              $$->type = $1->type;
              $$->is_lvalue = $1->is_lvalue;
          }
      }
      if ($1) free($1);
      if ($3) free($3);
    }
  | binary { $$ = $1; }
  ;

binary
  : binary RELOP binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          int lhs_kind = $1->type->kind;
          int rhs_kind = $3->type->kind;
          if (lhs_kind != rhs_kind) {
              error_comparable();
          } else if (lhs_kind == T_ARRAY) {
              if ($1->type != $3->type) {
                  error_comparable();
              } else {
                  $$->type = make_type(T_INT, NULL, 0);
              }
          } else if (lhs_kind == T_NULL) {
              if (!check_struct_table_match($1->type->struct_table, $3->type->struct_table)) {
                  error_comparable();
              } else {
                  $$->type = make_type(T_INT, NULL, 0);
              }
          } else {
              $$->type = make_type(T_INT, NULL, 0);
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary EQUOP binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != $3->type->kind) {
              error_comparable();
          } else if ($1->type->kind == T_NULL) {
              if (!check_struct_table_match($1->type->struct_table, $3->type->struct_table)) {
                  error_comparable();
              } else {
                  $$->type = make_type(T_INT, NULL, 0);
              }
          } else if ($1->type->kind == T_ARRAY) {
              if ($1->type != $3->type) {
                  error_comparable();
              } else {
                  $$->type = make_type(T_INT, NULL, 0);
              }
          } else {
              $$->type = make_type(T_INT, NULL, 0);
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary '+' binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind == T_INT && $3->type->kind == T_INT) {
              $$->type = $1->type;
          } else {
              error_binary();
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary '-' binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind == T_INT && $3->type->kind == T_INT) {
              $$->type = $1->type;
          } else {
              error_binary();
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary '*' binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_INT || $3->type->kind != T_INT) {
              error_binary();
          } else {
              $$->type = $1->type;
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary '/' binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_INT || $3->type->kind != T_INT) {
              error_binary();
          } else {
              $$->type = $1->type;
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary '%' binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_INT || $3->type->kind != T_INT) {
              error_binary();
          } else {
              $$->type = $1->type;
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | unary %prec '=' { $$ = $1; }
  | binary LOGICAL_AND binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_INT || $3->type->kind != T_INT) {
              error_binary();
          } else {
              $$->type = make_type(T_INT, NULL, 0);
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | binary LOGICAL_OR binary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_INT || $3->type->kind != T_INT) {
              error_binary();
          } else {
              $$->type = make_type(T_INT, NULL, 0);
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  ;

unary
  : '(' expr ')' { $$ = $2; }
  | '(' unary ')' { $$ = $2; }
  | INTEGER_CONST {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = make_type(T_INT, NULL, 0);
      $$->is_lvalue = 0;
    }
  | CHAR_CONST {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = make_type(T_CHAR, NULL, 0);
      $$->is_lvalue = 0;
    }
  | STRING {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = make_type(T_ARRAY, make_type(T_CHAR, NULL, 0), 0);
      $$->is_lvalue = 0;
    }
  | ID {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      Symbol* s = lookup_symbol($1);
      if (s == NULL) {
        error_undeclared();
        $$->type = NULL;
        $$->is_lvalue = 0;
      } else {
        $$->type = s->type;
        if (s->type && s->type->kind == T_ARRAY && s->type->size > 0) {
            $$->is_lvalue = 0;
        } else {
            $$->is_lvalue = 1;
        }
      }
      free($1);
    }
  | '-' unary %prec '!' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
          if ($2->type->kind != T_INT) {
              error_unary();
          } else {
              $$->type = $2->type;
          }
      }
      if ($2) free($2);
    }
  | '!' unary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
          if ($2->type->kind != T_INT) {
              error_unary();
          } else {
              $$->type = $2->type;
          }
      }
      if ($2) free($2);
    }
  | unary INCOP %prec STRUCTOP {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL) {
        if ($1->is_lvalue == 0) {
            error_assignable();
        } else if ($1->type->kind != T_INT && $1->type->kind != T_CHAR) {
            error_unary();
        } else {
            $$->type = $1->type;
        }
      }
      if ($1) free($1);
    }
  | unary DECOP %prec STRUCTOP {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL) {
        if ($1->is_lvalue == 0) {
            error_assignable();
        } else if ($1->type->kind != T_INT && $1->type->kind != T_CHAR) {
            error_unary();
        } else {
            $$->type = $1->type;
        }
      }
      if ($1) free($1);
    }
  | INCOP unary %prec '!' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
        if ($2->is_lvalue == 0) {
            error_assignable();
        } else if ($2->type->kind != T_INT && $2->type->kind != T_CHAR) {
            error_unary();
        } else {
            $$->type = $2->type;
        }
      }
      if ($2) free($2);
    }
  | DECOP unary %prec '!' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
        if ($2->is_lvalue == 0) {
            error_assignable();
        } else if ($2->type->kind != T_INT && $2->type->kind != T_CHAR) {
            error_unary();
        } else {
            $$->type = $2->type;
        }
      }
      if ($2) free($2);
    }
  | '&' unary {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
        if ($2->is_lvalue == 0) {
          error_addressof();
        } else {
          $$->type = make_type(T_ARRAY, $2->type, 0);
        }
      }
      if ($2) free($2);
    }
  | '*' unary %prec '!' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($2 != NULL && $2->type != NULL) {
        if ($2->type->kind != T_ARRAY) {
          error_indirection();
        } else {
          $$->type = $2->type->base;
          $$->is_lvalue = 1;
        }
      }
      if ($2) free($2);
    }
  | unary '[' expr ']' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $3 != NULL && $1->type != NULL && $3->type != NULL) {
          if ($1->type->kind != T_ARRAY) {
              error_array();
          } else if ($3->type->kind != T_INT) {
              error_subscript();
          } else {
              $$->type = $1->type->base;
              $$->is_lvalue = 1;
          }
      }
      if ($1) free($1); if ($3) free($3);
    }
  | unary '.' ID {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL && $1->type->struct_table != NULL) {
          Symbol* member = lookup_struct_member($1->type->struct_table, $3);
          if (member != NULL) {
              $$->type = member->type;
              $$->is_lvalue = $1->is_lvalue;
          } else {
              error_member();
          }
      } else {
          error_struct();
      }
      if ($1) free($1); free($3);
    }
  | unary STRUCTOP ID {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL && $1->type->kind == T_ARRAY && $1->type->base != NULL) {
          TypeInfo* struct_type = $1->type->base;
          if (struct_type->struct_table != NULL) {
              Symbol* member = lookup_struct_member(struct_type->struct_table, $3);
              if (member != NULL) {
                  $$->type = member->type;
                  $$->is_lvalue = 1;
              } else {
                  error_member();
              }
          } else {
              error_strurctp();
          }
      } else {
          error_strurctp();
      }
      if ($1) free($1); free($3);
    }
  | unary '(' args ')' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL) {
          if ($1->type->kind != T_FUNC) {
              error_function();
          } else {
              if (!check_arguments_match($1->type->fields, $3)) {
                  error_arguments();
              } else {
                  $$->type = $1->type->base;
              }
          }
      }
      if ($1) free($1);
      ParamList *curr = $3;
      while(curr != NULL) {
          ParamList *next = curr->next;
          free(curr);
          curr = next;
      }
    }
  | unary '(' ')' {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = NULL;
      $$->is_lvalue = 0;
      if ($1 != NULL && $1->type != NULL) {
        if ($1->type->kind != T_FUNC) {
          error_function();
        } else {
          if ($1->type->fields != NULL) {
              error_arguments();
          } else {
              $$->type = $1->type->base;
          }
        }
      }
      if ($1) free($1);
    }
  | SYM_NULL {
      $$ = (ExprInfo*)malloc(sizeof(ExprInfo));
      $$->type = make_type(T_ARRAY, NULL, 0);
      $$->is_lvalue = 0;
    }
  ;

args
  : expr { 
      $$ = append_param(NULL, ($1 && $1->type) ? $1->type : NULL); 
    }
  | args ',' expr { 
      $$ = append_param($1, ($3 && $3->type) ? $3->type : NULL); 
    }
  ;
%%

void error_preamble(void) {
  int lineno = get_lineno();
  printf("%s:%d: error: ", current_filename ? current_filename : "stdin", lineno);
}

void error_undeclared(void)   { error_preamble(); printf("use of undeclared identifier\n"); }
void error_redeclaration(void) { error_preamble(); printf("redeclaration\n"); }
void error_assignable(void)    { error_preamble(); printf("lvalue is not assignable\n"); }
void error_incompatible(void)  { error_preamble(); printf("incompatible types for assignment operation\n"); }
void error_null(void)          { error_preamble(); printf("cannot assign 'NULL' to non-pointer type\n"); }
void error_binary(void)        { error_preamble(); printf("invalid operands to binary expression\n"); }
void error_unary(void)         { error_preamble(); printf("invalid argument type to unary expression\n"); }
void error_comparable(void)    { error_preamble(); printf("types are not comparable in binary expression\n"); }
void error_indirection(void)   { error_preamble(); printf("indirection requires pointer operand\n"); }
void error_addressof(void)     { error_preamble(); printf("cannot take the address of an rvalue\n"); }
void error_struct(void)        { error_preamble(); printf("member reference base type is not a struct\n"); }
void error_strurctp(void)      { error_preamble(); printf("member reference base type is not a struct pointer\n"); }
void error_member(void)        { error_preamble(); printf("no such member in struct\n"); }
void error_array(void)         { error_preamble(); printf("subscripted value is not an array\n"); }
void error_subscript(void)     { error_preamble(); printf("array subscript is not an integer\n"); }
void error_incomplete(void)    { error_preamble(); printf("incomplete type\n"); }
void error_return(void)        { error_preamble(); printf("incompatible return types\n"); }
void error_function(void)      { error_preamble(); printf("not a function\n"); }
void error_arguments(void)     { error_preamble(); printf("incompatible arguments in function call\n"); }

SymbolTable* create_table() {
    SymbolTable* new_table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (new_table != NULL) {
        for (int i = 0; i < HASH_SIZE; i++) new_table->buckets[i] = NULL;
        new_table->outer_scope = NULL;
    }
    return new_table;
}

void free_table() {
    while (current_table != NULL) {
        SymbolTable* next_outer = current_table->outer_scope;
        free_single_table(current_table);
        free(current_table);
        current_table = next_outer;
    }
}

int main(int argc, char* argv[]) {
  if(argc >= 2) {
    yyin = fopen(argv[1], "r");
    current_filename = argv[1];
  } else {
    yyin = stdin;
    current_filename = "stdin";
  }

  if(!yyin) {
    printf("Can't open input stream!\n");
    exit(1);
  }
  
  current_table = create_table();
  yyparse();
  
  if(argc >= 2) fclose(yyin);
  free_table();
  return 0;
}