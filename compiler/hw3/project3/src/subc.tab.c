/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "subc.y"

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

#line 246 "subc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "subc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* ','  */
  YYSYMBOL_4_ = 4,                         /* '='  */
  YYSYMBOL_5_ = 5,                         /* '+'  */
  YYSYMBOL_6_ = 6,                         /* '-'  */
  YYSYMBOL_7_ = 7,                         /* '*'  */
  YYSYMBOL_8_ = 8,                         /* '/'  */
  YYSYMBOL_9_ = 9,                         /* '%'  */
  YYSYMBOL_10_ = 10,                       /* '!'  */
  YYSYMBOL_11_ = 11,                       /* '&'  */
  YYSYMBOL_12_ = 12,                       /* '['  */
  YYSYMBOL_13_ = 13,                       /* ']'  */
  YYSYMBOL_14_ = 14,                       /* '('  */
  YYSYMBOL_15_ = 15,                       /* ')'  */
  YYSYMBOL_16_ = 16,                       /* '.'  */
  YYSYMBOL_STRUCT = 17,                    /* STRUCT  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_FOR = 20,                       /* FOR  */
  YYSYMBOL_BREAK = 21,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 22,                  /* CONTINUE  */
  YYSYMBOL_SYM_NULL = 23,                  /* SYM_NULL  */
  YYSYMBOL_CHAR_CONST = 24,                /* CHAR_CONST  */
  YYSYMBOL_STRING = 25,                    /* STRING  */
  YYSYMBOL_RELOP = 26,                     /* RELOP  */
  YYSYMBOL_EQUOP = 27,                     /* EQUOP  */
  YYSYMBOL_LOGICAL_AND = 28,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 29,                /* LOGICAL_OR  */
  YYSYMBOL_INCOP = 30,                     /* INCOP  */
  YYSYMBOL_DECOP = 31,                     /* DECOP  */
  YYSYMBOL_STRUCTOP = 32,                  /* STRUCTOP  */
  YYSYMBOL_IF = 33,                        /* IF  */
  YYSYMBOL_ELSE = 34,                      /* ELSE  */
  YYSYMBOL_INTEGER_CONST = 35,             /* INTEGER_CONST  */
  YYSYMBOL_TYPE = 36,                      /* TYPE  */
  YYSYMBOL_ID = 37,                        /* ID  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_ext_def_list = 43,              /* ext_def_list  */
  YYSYMBOL_ext_def = 44,                   /* ext_def  */
  YYSYMBOL_type_specifier = 45,            /* type_specifier  */
  YYSYMBOL_struct_specifier = 46,          /* struct_specifier  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_func_decl = 48,                 /* func_decl  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_pointers = 50,                  /* pointers  */
  YYSYMBOL_param_list = 51,                /* param_list  */
  YYSYMBOL_param_decl = 52,                /* param_decl  */
  YYSYMBOL_def_list = 53,                  /* def_list  */
  YYSYMBOL_def = 54,                       /* def  */
  YYSYMBOL_compound_stmt = 55,             /* compound_stmt  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_stmt_list = 57,                 /* stmt_list  */
  YYSYMBOL_stmt = 58,                      /* stmt  */
  YYSYMBOL_expr_e = 59,                    /* expr_e  */
  YYSYMBOL_expr = 60,                      /* expr  */
  YYSYMBOL_binary = 61,                    /* binary  */
  YYSYMBOL_unary = 62,                     /* unary  */
  YYSYMBOL_args = 63                       /* args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   241

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,     2,     2,     9,    11,     2,
      14,    15,     7,     5,     3,     6,    16,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
       2,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    12,     2,    13,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   210,   210,   214,   215,   219,   224,   230,   231,   237,
     241,   245,   245,   264,   276,   289,   289,   309,   310,   314,
     315,   319,   324,   333,   334,   338,   343,   352,   352,   356,
     357,   361,   362,   372,   373,   374,   375,   376,   377,   378,
     379,   383,   384,   392,   435,   439,   466,   491,   504,   517,
     530,   543,   556,   557,   570,   586,   587,   588,   593,   598,
     603,   620,   633,   646,   661,   676,   691,   706,   719,   733,
     749,   766,   788,   811,   828,   836,   839
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "','", "'='", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'!'", "'&'", "'['", "']'", "'('", "')'",
  "'.'", "STRUCT", "RETURN", "WHILE", "FOR", "BREAK", "CONTINUE",
  "SYM_NULL", "CHAR_CONST", "STRING", "RELOP", "EQUOP", "LOGICAL_AND",
  "LOGICAL_OR", "INCOP", "DECOP", "STRUCTOP", "IF", "ELSE",
  "INTEGER_CONST", "TYPE", "ID", "';'", "'{'", "'}'", "$accept", "program",
  "ext_def_list", "ext_def", "type_specifier", "struct_specifier", "$@1",
  "func_decl", "$@2", "pointers", "param_list", "param_decl", "def_list",
  "def", "compound_stmt", "$@3", "stmt_list", "stmt", "expr_e", "expr",
  "binary", "unary", "args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -128,    15,   -13,  -128,   -20,  -128,  -128,    28,    -1,     1,
       4,  -128,    26,  -128,  -128,  -128,  -128,    -7,  -128,  -128,
       6,    63,  -128,   -13,     2,    70,  -128,   -13,    28,  -128,
    -128,    75,  -128,    38,    28,    10,  -128,    42,   166,   166,
     166,   166,   166,   166,    76,    78,    46,    64,  -128,  -128,
    -128,   166,   166,    89,  -128,  -128,  -128,  -128,  -128,  -128,
      80,   156,   188,  -128,    67,   -13,  -128,    -6,    95,    95,
      95,    95,   104,    14,    84,   166,   166,  -128,  -128,    95,
      95,   166,  -128,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   144,    86,  -128,  -128,    99,   125,
    -128,   103,  -128,  -128,  -128,  -128,   124,   106,  -128,   127,
      40,    95,    40,  -128,  -128,  -128,    66,    61,   205,   200,
    -128,   133,  -128,  -128,    21,  -128,  -128,   117,   140,   110,
     166,   110,  -128,   166,  -128,   143,   119,  -128,   122,   132,
    -128,  -128,  -128,   166,   110,   155,  -128,   110,  -128
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     9,     3,    18,    10,     0,
      13,    17,     0,     7,    27,     8,    11,     0,    24,    24,
       0,    15,     5,    30,     0,     0,    14,     0,    18,    10,
      23,     0,    12,     0,    18,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,    58,
      59,     0,     0,     0,    57,    60,    35,    28,    36,    29,
       0,    44,    52,     6,     0,     0,    16,     0,    61,    68,
      62,    67,     0,    52,     0,     0,    42,    33,    34,    65,
      66,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,     0,    21,
      20,     0,    25,    55,    56,    32,     0,     0,    41,     0,
      47,    52,    48,    49,    50,    51,    45,    46,    53,    54,
      43,     0,    73,    75,     0,    70,    71,     0,     0,     0,
      42,     0,    69,     0,    72,     0,     0,    39,     0,    37,
      76,    22,    26,    42,     0,     0,    38,     0,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,  -128,  -128,     0,   169,  -128,  -128,  -128,   -14,
    -128,   113,   167,  -128,   178,  -128,  -128,   -67,  -127,   -42,
     150,   -30,  -128
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    28,    29,    19,     9,    27,    12,
      35,    36,    23,    30,    58,    18,    31,    59,   107,    60,
      61,    62,   124
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,    74,     7,   138,     4,    20,   101,    21,    68,    69,
      70,    71,    73,    65,    37,     3,   145,    10,    92,     4,
      64,    79,    80,     5,   133,    66,    93,    34,    94,   104,
      95,    22,   102,   106,   108,    11,   134,    13,     5,   109,
      14,    25,    32,    16,    96,    97,    98,    85,    86,    87,
     120,   121,   123,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   137,    17,   139,    34,    83,    84,    85,    86,
      87,    83,    84,    85,    86,    87,    63,   146,    26,    67,
     148,    38,    39,    33,    77,    40,    41,    88,   108,    42,
      75,   140,    76,    43,    44,    45,    46,    47,    48,    49,
      50,   108,    78,    81,    99,    51,    52,    93,    53,    94,
      54,    95,    55,    56,    14,    57,    38,    39,    82,   103,
      40,    41,   105,   125,    42,    96,    97,    98,    43,    44,
      45,    46,    47,    48,    49,    50,   126,   127,   128,   129,
      51,    52,   131,    53,   130,    54,   132,    55,    56,    14,
      38,    39,   135,   136,    40,    41,   141,   142,    42,   122,
     143,    83,    84,    85,    86,    87,   144,    48,    49,    50,
     147,     8,    38,    39,    51,    52,    40,    41,   100,    54,
      42,    55,    88,    89,    90,    91,    24,    15,     0,    48,
      49,    50,    92,     0,     0,     0,    51,    52,     0,     0,
      93,    54,    94,    55,    95,    83,    84,    85,    86,    87,
      83,    84,    85,    86,    87,     0,     0,     0,    96,    97,
      98,     0,     0,     0,     0,     0,    88,    89,    90,     0,
       0,    88,    89,   110,   112,   113,   114,   115,   116,   117,
     118,   119
};

static const yytype_int16 yycheck[] =
{
      42,    43,     2,   130,    17,    12,    12,    14,    38,    39,
      40,    41,    42,     3,    28,     0,   143,    37,     4,    17,
      34,    51,    52,    36,     3,    15,    12,    27,    14,    15,
      16,    38,    38,    75,    76,     7,    15,    38,    36,    81,
      39,    35,    40,    39,    30,    31,    32,     7,     8,     9,
      92,    93,    94,    83,    84,    85,    86,    87,    88,    89,
      90,    91,   129,    37,   131,    65,     5,     6,     7,     8,
       9,     5,     6,     7,     8,     9,    38,   144,    15,    37,
     147,     6,     7,    13,    38,    10,    11,    26,   130,    14,
      14,   133,    14,    18,    19,    20,    21,    22,    23,    24,
      25,   143,    38,    14,    37,    30,    31,    12,    33,    14,
      35,    16,    37,    38,    39,    40,     6,     7,    38,    15,
      10,    11,    38,    37,    14,    30,    31,    32,    18,    19,
      20,    21,    22,    23,    24,    25,    37,    12,    35,    15,
      30,    31,    15,    33,    38,    35,    13,    37,    38,    39,
       6,     7,    35,    13,    10,    11,    13,    38,    14,    15,
      38,     5,     6,     7,     8,     9,    34,    23,    24,    25,
      15,     2,     6,     7,    30,    31,    10,    11,    65,    35,
      14,    37,    26,    27,    28,    29,    19,     9,    -1,    23,
      24,    25,     4,    -1,    -1,    -1,    30,    31,    -1,    -1,
      12,    35,    14,    37,    16,     5,     6,     7,     8,     9,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,
      -1,    26,    27,    83,    84,    85,    86,    87,    88,    89,
      90,    91
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    42,    43,     0,    17,    36,    44,    45,    46,    48,
      37,     7,    50,    38,    39,    55,    39,    37,    56,    47,
      12,    14,    38,    53,    53,    35,    15,    49,    45,    46,
      54,    57,    40,    13,    45,    51,    52,    50,     6,     7,
      10,    11,    14,    18,    19,    20,    21,    22,    23,    24,
      25,    30,    31,    33,    35,    37,    38,    40,    55,    58,
      60,    61,    62,    38,    50,     3,    15,    37,    62,    62,
      62,    62,    60,    62,    60,    14,    14,    38,    38,    62,
      62,    14,    38,     5,     6,     7,     8,     9,    26,    27,
      28,    29,     4,    12,    14,    16,    30,    31,    32,    37,
      52,    12,    38,    15,    15,    38,    60,    59,    60,    60,
      61,    62,    61,    61,    61,    61,    61,    61,    61,    61,
      60,    60,    15,    60,    63,    37,    37,    12,    35,    15,
      38,    15,    13,     3,    15,    35,    13,    58,    59,    58,
      60,    13,    38,    38,    34,    59,    58,    15,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    45,
      45,    47,    46,    46,    48,    49,    48,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    56,    55,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     4,     7,     2,     2,     1,
       1,     0,     6,     2,     5,     0,     7,     1,     0,     1,
       3,     3,     6,     2,     0,     4,     7,     0,     5,     2,
       0,     2,     3,     2,     2,     1,     1,     5,     7,     5,
       9,     1,     0,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     3,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       3,     3,     4,     3,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* ext_def: type_specifier pointers ID ';'  */
#line 219 "subc.y"
                                   {
      TypeInfo* t = (yyvsp[-2].typePtr) ? make_type(T_ARRAY, (yyvsp[-3].typePtr), 0) : (yyvsp[-3].typePtr);
      if (insert_sym((yyvsp[-1].stringVal), t) == NULL) { error_redeclaration(); }
      free((yyvsp[-1].stringVal));
    }
#line 1411 "subc.tab.c"
    break;

  case 6: /* ext_def: type_specifier pointers ID '[' INTEGER_CONST ']' ';'  */
#line 224 "subc.y"
                                                         {
      TypeInfo* t = (yyvsp[-5].typePtr) ? make_type(T_ARRAY, (yyvsp[-6].typePtr), 0) : (yyvsp[-6].typePtr);
      TypeInfo* arr = make_type(T_ARRAY, t, (yyvsp[-2].intVal));
      if (insert_sym((yyvsp[-4].stringVal), arr) == NULL) { error_redeclaration(); }
      free((yyvsp[-4].stringVal));
    }
#line 1422 "subc.tab.c"
    break;

  case 8: /* ext_def: func_decl compound_stmt  */
#line 231 "subc.y"
                            {
      pop_scope();
    }
#line 1430 "subc.tab.c"
    break;

  case 9: /* type_specifier: TYPE  */
#line 237 "subc.y"
         {
      if ((yyvsp[0].intVal) == T_INT) (yyval.typePtr) = make_type(T_INT, NULL, 4);
      else (yyval.typePtr) = make_type(T_CHAR, NULL, 1);
    }
#line 1439 "subc.tab.c"
    break;

  case 10: /* type_specifier: struct_specifier  */
#line 241 "subc.y"
                     { (yyval.typePtr) = (yyvsp[0].typePtr); }
#line 1445 "subc.tab.c"
    break;

  case 11: /* $@1: %empty  */
#line 245 "subc.y"
                  {
      TypeInfo* str_type = make_type(T_NULL, NULL, 0); 
      Symbol* s = insert_sym((yyvsp[-1].stringVal), str_type);
      if (s == NULL) {
          error_redeclaration();
      }
      push_scope();
    }
#line 1458 "subc.tab.c"
    break;

  case 12: /* struct_specifier: STRUCT ID '{' $@1 def_list '}'  */
#line 252 "subc.y"
                   {
      SymbolTable* struct_scope = current_table;
      Symbol* s = lookup_symbol((yyvsp[-4].stringVal));
      if (s != NULL && s->type != NULL) {
          s->type->struct_table = struct_scope;
          (yyval.typePtr) = s->type;
      } else {
          (yyval.typePtr) = NULL;
      }
      pop_scope_without_free();
      free((yyvsp[-4].stringVal));
    }
#line 1475 "subc.tab.c"
    break;

  case 13: /* struct_specifier: STRUCT ID  */
#line 264 "subc.y"
              {
      Symbol* s = lookup_symbol((yyvsp[0].stringVal));
      if (s == NULL || s->type == NULL) {
          (yyval.typePtr) = NULL;
      } else {
          (yyval.typePtr) = s->type;
      }
      free((yyvsp[0].stringVal));
    }
#line 1489 "subc.tab.c"
    break;

  case 14: /* func_decl: type_specifier pointers ID '(' ')'  */
#line 276 "subc.y"
                                       {
      TypeInfo* t = (yyvsp[-3].typePtr) ? make_type(T_ARRAY, (yyvsp[-4].typePtr), 0) : (yyvsp[-4].typePtr);
      TypeInfo* f = make_type(T_FUNC, t, 0);
      Symbol* s = insert_sym((yyvsp[-2].stringVal), f);
      if (s == NULL) {
          error_redeclaration();
          current_parsing_func = NULL;
      } else {
          current_parsing_func = s;
      }
      push_scope();
      free((yyvsp[-2].stringVal));
    }
#line 1507 "subc.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 289 "subc.y"
                                   {
      TypeInfo* t = (yyvsp[-2].typePtr) ? make_type(T_ARRAY, (yyvsp[-3].typePtr), 0) : (yyvsp[-3].typePtr);
      TypeInfo* f = make_type(T_FUNC, t, 0);
      Symbol* s = insert_sym((yyvsp[-1].stringVal), f);
      if (s == NULL) {
          error_redeclaration();
          current_parsing_func = NULL;
      } else {
          current_parsing_func = s; 
      }
      push_scope();
      free((yyvsp[-1].stringVal));
    }
#line 1525 "subc.tab.c"
    break;

  case 16: /* func_decl: type_specifier pointers ID '(' $@2 param_list ')'  */
#line 301 "subc.y"
                     {
        if (current_parsing_func != NULL && current_parsing_func->type != NULL) {
            current_parsing_func->type->fields = (yyvsp[-1].param_ptr);
        }
    }
#line 1535 "subc.tab.c"
    break;

  case 17: /* pointers: '*'  */
#line 309 "subc.y"
           { (yyval.typePtr) = make_type(T_ARRAY, NULL, 0); }
#line 1541 "subc.tab.c"
    break;

  case 18: /* pointers: %empty  */
#line 310 "subc.y"
           { (yyval.typePtr) = NULL; }
#line 1547 "subc.tab.c"
    break;

  case 19: /* param_list: param_decl  */
#line 314 "subc.y"
                               { (yyval.param_ptr) = append_param(NULL, (yyvsp[0].typePtr)); }
#line 1553 "subc.tab.c"
    break;

  case 20: /* param_list: param_list ',' param_decl  */
#line 315 "subc.y"
                               { (yyval.param_ptr) = append_param((yyvsp[-2].param_ptr), (yyvsp[0].typePtr)); }
#line 1559 "subc.tab.c"
    break;

  case 21: /* param_decl: type_specifier pointers ID  */
#line 319 "subc.y"
                               {
      TypeInfo* t = (yyvsp[-1].typePtr) ? make_type(T_ARRAY, (yyvsp[-2].typePtr), 0) : (yyvsp[-2].typePtr);
      if (insert_sym((yyvsp[0].stringVal), t) == NULL) { error_redeclaration(); }
      (yyval.typePtr) = t; free((yyvsp[0].stringVal));
    }
#line 1569 "subc.tab.c"
    break;

  case 22: /* param_decl: type_specifier pointers ID '[' INTEGER_CONST ']'  */
#line 324 "subc.y"
                                                     {
      TypeInfo* t = (yyvsp[-4].typePtr) ? make_type(T_ARRAY, (yyvsp[-5].typePtr), 0) : (yyvsp[-5].typePtr);
      TypeInfo* arr = make_type(T_ARRAY, t, (yyvsp[-1].intVal));
      if (insert_sym((yyvsp[-3].stringVal), arr) == NULL) { error_redeclaration(); }
      (yyval.typePtr) = arr; free((yyvsp[-3].stringVal));
    }
#line 1580 "subc.tab.c"
    break;

  case 25: /* def: type_specifier pointers ID ';'  */
#line 338 "subc.y"
                                   {
      TypeInfo* t = (yyvsp[-2].typePtr) ? make_type(T_ARRAY, (yyvsp[-3].typePtr), 0) : (yyvsp[-3].typePtr);
      if (insert_sym((yyvsp[-1].stringVal), t) == NULL) { error_redeclaration(); }
      free((yyvsp[-1].stringVal));
    }
#line 1590 "subc.tab.c"
    break;

  case 26: /* def: type_specifier pointers ID '[' INTEGER_CONST ']' ';'  */
#line 343 "subc.y"
                                                         {
      TypeInfo* t = (yyvsp[-5].typePtr) ? make_type(T_ARRAY, (yyvsp[-6].typePtr), 0) : (yyvsp[-6].typePtr);
      TypeInfo* arr = make_type(T_ARRAY, t, (yyvsp[-2].intVal));
      if (insert_sym((yyvsp[-4].stringVal), arr) == NULL) { error_redeclaration(); }
      free((yyvsp[-4].stringVal));
    }
#line 1601 "subc.tab.c"
    break;

  case 27: /* $@3: %empty  */
#line 352 "subc.y"
        { push_scope(); }
#line 1607 "subc.tab.c"
    break;

  case 28: /* compound_stmt: '{' $@3 def_list stmt_list '}'  */
#line 352 "subc.y"
                                                 { pop_scope(); }
#line 1613 "subc.tab.c"
    break;

  case 31: /* stmt: expr ';'  */
#line 361 "subc.y"
             { if ((yyvsp[-1].exprPtr)) free((yyvsp[-1].exprPtr)); }
#line 1619 "subc.tab.c"
    break;

  case 32: /* stmt: RETURN expr ';'  */
#line 362 "subc.y"
                    {
      if (current_parsing_func && current_parsing_func->type && current_parsing_func->type->base && (yyvsp[-1].exprPtr) && (yyvsp[-1].exprPtr)->type) {
          int ret_kind = current_parsing_func->type->base->kind;
          int expr_kind = (yyvsp[-1].exprPtr)->type->kind;
          if (ret_kind != expr_kind) {
              error_return();
          }
       }
       if ((yyvsp[-1].exprPtr)) free((yyvsp[-1].exprPtr));
    }
#line 1634 "subc.tab.c"
    break;

  case 37: /* stmt: IF '(' expr ')' stmt  */
#line 376 "subc.y"
                                         { if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); }
#line 1640 "subc.tab.c"
    break;

  case 38: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 377 "subc.y"
                                          { if ((yyvsp[-4].exprPtr)) free((yyvsp[-4].exprPtr)); }
#line 1646 "subc.tab.c"
    break;

  case 39: /* stmt: WHILE '(' expr ')' stmt  */
#line 378 "subc.y"
                                          { if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); }
#line 1652 "subc.tab.c"
    break;

  case 40: /* stmt: FOR '(' expr_e ';' expr_e ';' expr_e ')' stmt  */
#line 379 "subc.y"
                                                  { if ((yyvsp[-6].exprPtr)) free((yyvsp[-6].exprPtr)); }
#line 1658 "subc.tab.c"
    break;

  case 41: /* expr_e: expr  */
#line 383 "subc.y"
           { (yyval.exprPtr) = (yyvsp[0].exprPtr); }
#line 1664 "subc.tab.c"
    break;

  case 42: /* expr_e: %empty  */
#line 384 "subc.y"
           {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
    }
#line 1674 "subc.tab.c"
    break;

  case 43: /* expr: unary '=' expr  */
#line 392 "subc.y"
                   {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->is_lvalue == 0) {
              error_assignable();
          } else if ((yyvsp[-2].exprPtr)->type->kind != (yyvsp[0].exprPtr)->type->kind) {
              error_incompatible();
          } else if ((yyvsp[-2].exprPtr)->type->kind == T_NULL) {
              if (!check_struct_table_match((yyvsp[-2].exprPtr)->type->struct_table, (yyvsp[0].exprPtr)->type->struct_table)) {
                  error_incompatible();
              } else {
                  (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
                  (yyval.exprPtr)->is_lvalue = (yyvsp[-2].exprPtr)->is_lvalue;
              }
          } else if ((yyvsp[-2].exprPtr)->type->kind == T_ARRAY) {
              if ((yyvsp[-2].exprPtr)->type->base != NULL && (yyvsp[0].exprPtr)->type->base != NULL && 
                  (yyvsp[-2].exprPtr)->type->base->kind == T_NULL && (yyvsp[0].exprPtr)->type->base->kind == T_NULL) {
                  
                  if (!check_struct_table_match((yyvsp[-2].exprPtr)->type->base->struct_table, (yyvsp[0].exprPtr)->type->base->struct_table)) {
                      error_incompatible();
                  } else {
                      (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
                      (yyval.exprPtr)->is_lvalue = (yyvsp[-2].exprPtr)->is_lvalue;
                  }
              } else {
                  if ((yyvsp[-2].exprPtr)->type->base == NULL || (yyvsp[0].exprPtr)->type->base == NULL || 
                      (yyvsp[-2].exprPtr)->type->base->kind != (yyvsp[0].exprPtr)->type->base->kind) {
                      error_incompatible();
                  } else {
                      (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
                      (yyval.exprPtr)->is_lvalue = (yyvsp[-2].exprPtr)->is_lvalue;
                  }
              }
          } else {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
              (yyval.exprPtr)->is_lvalue = (yyvsp[-2].exprPtr)->is_lvalue;
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr));
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1722 "subc.tab.c"
    break;

  case 44: /* expr: binary  */
#line 435 "subc.y"
           { (yyval.exprPtr) = (yyvsp[0].exprPtr); }
#line 1728 "subc.tab.c"
    break;

  case 45: /* binary: binary RELOP binary  */
#line 439 "subc.y"
                        {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          int lhs_kind = (yyvsp[-2].exprPtr)->type->kind;
          int rhs_kind = (yyvsp[0].exprPtr)->type->kind;
          if (lhs_kind != rhs_kind) {
              error_comparable();
          } else if (lhs_kind == T_ARRAY) {
              if ((yyvsp[-2].exprPtr)->type != (yyvsp[0].exprPtr)->type) {
                  error_comparable();
              } else {
                  (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
              }
          } else if (lhs_kind == T_NULL) {
              if (!check_struct_table_match((yyvsp[-2].exprPtr)->type->struct_table, (yyvsp[0].exprPtr)->type->struct_table)) {
                  error_comparable();
              } else {
                  (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
              }
          } else {
              (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1760 "subc.tab.c"
    break;

  case 46: /* binary: binary EQUOP binary  */
#line 466 "subc.y"
                        {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != (yyvsp[0].exprPtr)->type->kind) {
              error_comparable();
          } else if ((yyvsp[-2].exprPtr)->type->kind == T_NULL) {
              if (!check_struct_table_match((yyvsp[-2].exprPtr)->type->struct_table, (yyvsp[0].exprPtr)->type->struct_table)) {
                  error_comparable();
              } else {
                  (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
              }
          } else if ((yyvsp[-2].exprPtr)->type->kind == T_ARRAY) {
              if ((yyvsp[-2].exprPtr)->type != (yyvsp[0].exprPtr)->type) {
                  error_comparable();
              } else {
                  (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
              }
          } else {
              (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1790 "subc.tab.c"
    break;

  case 47: /* binary: binary '+' binary  */
#line 491 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind == T_INT && (yyvsp[0].exprPtr)->type->kind == T_INT) {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
          } else {
              error_binary();
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1808 "subc.tab.c"
    break;

  case 48: /* binary: binary '-' binary  */
#line 504 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind == T_INT && (yyvsp[0].exprPtr)->type->kind == T_INT) {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
          } else {
              error_binary();
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1826 "subc.tab.c"
    break;

  case 49: /* binary: binary '*' binary  */
#line 517 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != T_INT || (yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_binary();
          } else {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1844 "subc.tab.c"
    break;

  case 50: /* binary: binary '/' binary  */
#line 530 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != T_INT || (yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_binary();
          } else {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1862 "subc.tab.c"
    break;

  case 51: /* binary: binary '%' binary  */
#line 543 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != T_INT || (yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_binary();
          } else {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type;
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1880 "subc.tab.c"
    break;

  case 52: /* binary: unary  */
#line 556 "subc.y"
                    { (yyval.exprPtr) = (yyvsp[0].exprPtr); }
#line 1886 "subc.tab.c"
    break;

  case 53: /* binary: binary LOGICAL_AND binary  */
#line 557 "subc.y"
                              {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != T_INT || (yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_binary();
          } else {
              (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1904 "subc.tab.c"
    break;

  case 54: /* binary: binary LOGICAL_OR binary  */
#line 570 "subc.y"
                             {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[0].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[-2].exprPtr)->type->kind != T_INT || (yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_binary();
          } else {
              (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
          }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 1922 "subc.tab.c"
    break;

  case 55: /* unary: '(' expr ')'  */
#line 586 "subc.y"
                 { (yyval.exprPtr) = (yyvsp[-1].exprPtr); }
#line 1928 "subc.tab.c"
    break;

  case 56: /* unary: '(' unary ')'  */
#line 587 "subc.y"
                  { (yyval.exprPtr) = (yyvsp[-1].exprPtr); }
#line 1934 "subc.tab.c"
    break;

  case 57: /* unary: INTEGER_CONST  */
#line 588 "subc.y"
                  {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = make_type(T_INT, NULL, 0);
      (yyval.exprPtr)->is_lvalue = 0;
    }
#line 1944 "subc.tab.c"
    break;

  case 58: /* unary: CHAR_CONST  */
#line 593 "subc.y"
               {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = make_type(T_CHAR, NULL, 0);
      (yyval.exprPtr)->is_lvalue = 0;
    }
#line 1954 "subc.tab.c"
    break;

  case 59: /* unary: STRING  */
#line 598 "subc.y"
           {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = make_type(T_ARRAY, make_type(T_CHAR, NULL, 0), 0);
      (yyval.exprPtr)->is_lvalue = 0;
    }
#line 1964 "subc.tab.c"
    break;

  case 60: /* unary: ID  */
#line 603 "subc.y"
       {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      Symbol* s = lookup_symbol((yyvsp[0].stringVal));
      if (s == NULL) {
        error_undeclared();
        (yyval.exprPtr)->type = NULL;
        (yyval.exprPtr)->is_lvalue = 0;
      } else {
        (yyval.exprPtr)->type = s->type;
        if (s->type && s->type->kind == T_ARRAY && s->type->size > 0) {
            (yyval.exprPtr)->is_lvalue = 0;
        } else {
            (yyval.exprPtr)->is_lvalue = 1;
        }
      }
      free((yyvsp[0].stringVal));
    }
#line 1986 "subc.tab.c"
    break;

  case 61: /* unary: '-' unary  */
#line 620 "subc.y"
                        {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_unary();
          } else {
              (yyval.exprPtr)->type = (yyvsp[0].exprPtr)->type;
          }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2004 "subc.tab.c"
    break;

  case 62: /* unary: '!' unary  */
#line 633 "subc.y"
              {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
          if ((yyvsp[0].exprPtr)->type->kind != T_INT) {
              error_unary();
          } else {
              (yyval.exprPtr)->type = (yyvsp[0].exprPtr)->type;
          }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2022 "subc.tab.c"
    break;

  case 63: /* unary: unary INCOP  */
#line 646 "subc.y"
                               {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-1].exprPtr) != NULL && (yyvsp[-1].exprPtr)->type != NULL) {
        if ((yyvsp[-1].exprPtr)->is_lvalue == 0) {
            error_assignable();
        } else if ((yyvsp[-1].exprPtr)->type->kind != T_INT && (yyvsp[-1].exprPtr)->type->kind != T_CHAR) {
            error_unary();
        } else {
            (yyval.exprPtr)->type = (yyvsp[-1].exprPtr)->type;
        }
      }
      if ((yyvsp[-1].exprPtr)) free((yyvsp[-1].exprPtr));
    }
#line 2042 "subc.tab.c"
    break;

  case 64: /* unary: unary DECOP  */
#line 661 "subc.y"
                               {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-1].exprPtr) != NULL && (yyvsp[-1].exprPtr)->type != NULL) {
        if ((yyvsp[-1].exprPtr)->is_lvalue == 0) {
            error_assignable();
        } else if ((yyvsp[-1].exprPtr)->type->kind != T_INT && (yyvsp[-1].exprPtr)->type->kind != T_CHAR) {
            error_unary();
        } else {
            (yyval.exprPtr)->type = (yyvsp[-1].exprPtr)->type;
        }
      }
      if ((yyvsp[-1].exprPtr)) free((yyvsp[-1].exprPtr));
    }
#line 2062 "subc.tab.c"
    break;

  case 65: /* unary: INCOP unary  */
#line 676 "subc.y"
                          {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
        if ((yyvsp[0].exprPtr)->is_lvalue == 0) {
            error_assignable();
        } else if ((yyvsp[0].exprPtr)->type->kind != T_INT && (yyvsp[0].exprPtr)->type->kind != T_CHAR) {
            error_unary();
        } else {
            (yyval.exprPtr)->type = (yyvsp[0].exprPtr)->type;
        }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2082 "subc.tab.c"
    break;

  case 66: /* unary: DECOP unary  */
#line 691 "subc.y"
                          {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
        if ((yyvsp[0].exprPtr)->is_lvalue == 0) {
            error_assignable();
        } else if ((yyvsp[0].exprPtr)->type->kind != T_INT && (yyvsp[0].exprPtr)->type->kind != T_CHAR) {
            error_unary();
        } else {
            (yyval.exprPtr)->type = (yyvsp[0].exprPtr)->type;
        }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2102 "subc.tab.c"
    break;

  case 67: /* unary: '&' unary  */
#line 706 "subc.y"
              {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
        if ((yyvsp[0].exprPtr)->is_lvalue == 0) {
          error_addressof();
        } else {
          (yyval.exprPtr)->type = make_type(T_ARRAY, (yyvsp[0].exprPtr)->type, 0);
        }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2120 "subc.tab.c"
    break;

  case 68: /* unary: '*' unary  */
#line 719 "subc.y"
                        {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[0].exprPtr) != NULL && (yyvsp[0].exprPtr)->type != NULL) {
        if ((yyvsp[0].exprPtr)->type->kind != T_ARRAY) {
          error_indirection();
        } else {
          (yyval.exprPtr)->type = (yyvsp[0].exprPtr)->type->base;
          (yyval.exprPtr)->is_lvalue = 1;
        }
      }
      if ((yyvsp[0].exprPtr)) free((yyvsp[0].exprPtr));
    }
#line 2139 "subc.tab.c"
    break;

  case 69: /* unary: unary '[' expr ']'  */
#line 733 "subc.y"
                       {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-3].exprPtr) != NULL && (yyvsp[-1].exprPtr) != NULL && (yyvsp[-3].exprPtr)->type != NULL && (yyvsp[-1].exprPtr)->type != NULL) {
          if ((yyvsp[-3].exprPtr)->type->kind != T_ARRAY) {
              error_array();
          } else if ((yyvsp[-1].exprPtr)->type->kind != T_INT) {
              error_subscript();
          } else {
              (yyval.exprPtr)->type = (yyvsp[-3].exprPtr)->type->base;
              (yyval.exprPtr)->is_lvalue = 1;
          }
      }
      if ((yyvsp[-3].exprPtr)) free((yyvsp[-3].exprPtr)); if ((yyvsp[-1].exprPtr)) free((yyvsp[-1].exprPtr));
    }
#line 2160 "subc.tab.c"
    break;

  case 70: /* unary: unary '.' ID  */
#line 749 "subc.y"
                 {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[-2].exprPtr)->type->struct_table != NULL) {
          Symbol* member = lookup_struct_member((yyvsp[-2].exprPtr)->type->struct_table, (yyvsp[0].stringVal));
          if (member != NULL) {
              (yyval.exprPtr)->type = member->type;
              (yyval.exprPtr)->is_lvalue = (yyvsp[-2].exprPtr)->is_lvalue;
          } else {
              error_member();
          }
      } else {
          error_struct();
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); free((yyvsp[0].stringVal));
    }
#line 2182 "subc.tab.c"
    break;

  case 71: /* unary: unary STRUCTOP ID  */
#line 766 "subc.y"
                      {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL && (yyvsp[-2].exprPtr)->type->kind == T_ARRAY && (yyvsp[-2].exprPtr)->type->base != NULL) {
          TypeInfo* struct_type = (yyvsp[-2].exprPtr)->type->base;
          if (struct_type->struct_table != NULL) {
              Symbol* member = lookup_struct_member(struct_type->struct_table, (yyvsp[0].stringVal));
              if (member != NULL) {
                  (yyval.exprPtr)->type = member->type;
                  (yyval.exprPtr)->is_lvalue = 1;
              } else {
                  error_member();
              }
          } else {
              error_strurctp();
          }
      } else {
          error_strurctp();
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr)); free((yyvsp[0].stringVal));
    }
#line 2209 "subc.tab.c"
    break;

  case 72: /* unary: unary '(' args ')'  */
#line 788 "subc.y"
                       {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-3].exprPtr) != NULL && (yyvsp[-3].exprPtr)->type != NULL) {
          if ((yyvsp[-3].exprPtr)->type->kind != T_FUNC) {
              error_function();
          } else {
              if (!check_arguments_match((yyvsp[-3].exprPtr)->type->fields, (yyvsp[-1].param_ptr))) {
                  error_arguments();
              } else {
                  (yyval.exprPtr)->type = (yyvsp[-3].exprPtr)->type->base;
              }
          }
      }
      if ((yyvsp[-3].exprPtr)) free((yyvsp[-3].exprPtr));
      ParamList *curr = (yyvsp[-1].param_ptr);
      while(curr != NULL) {
          ParamList *next = curr->next;
          free(curr);
          curr = next;
      }
    }
#line 2237 "subc.tab.c"
    break;

  case 73: /* unary: unary '(' ')'  */
#line 811 "subc.y"
                  {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = NULL;
      (yyval.exprPtr)->is_lvalue = 0;
      if ((yyvsp[-2].exprPtr) != NULL && (yyvsp[-2].exprPtr)->type != NULL) {
        if ((yyvsp[-2].exprPtr)->type->kind != T_FUNC) {
          error_function();
        } else {
          if ((yyvsp[-2].exprPtr)->type->fields != NULL) {
              error_arguments();
          } else {
              (yyval.exprPtr)->type = (yyvsp[-2].exprPtr)->type->base;
          }
        }
      }
      if ((yyvsp[-2].exprPtr)) free((yyvsp[-2].exprPtr));
    }
#line 2259 "subc.tab.c"
    break;

  case 74: /* unary: SYM_NULL  */
#line 828 "subc.y"
             {
      (yyval.exprPtr) = (ExprInfo*)malloc(sizeof(ExprInfo));
      (yyval.exprPtr)->type = make_type(T_ARRAY, NULL, 0);
      (yyval.exprPtr)->is_lvalue = 0;
    }
#line 2269 "subc.tab.c"
    break;

  case 75: /* args: expr  */
#line 836 "subc.y"
         { 
      (yyval.param_ptr) = append_param(NULL, ((yyvsp[0].exprPtr) && (yyvsp[0].exprPtr)->type) ? (yyvsp[0].exprPtr)->type : NULL); 
    }
#line 2277 "subc.tab.c"
    break;

  case 76: /* args: args ',' expr  */
#line 839 "subc.y"
                  { 
      (yyval.param_ptr) = append_param((yyvsp[-2].param_ptr), ((yyvsp[0].exprPtr) && (yyvsp[0].exprPtr)->type) ? (yyvsp[0].exprPtr)->type : NULL); 
    }
#line 2285 "subc.tab.c"
    break;


#line 2289 "subc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 843 "subc.y"


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
