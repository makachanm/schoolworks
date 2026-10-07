/*
 * File Name    : subc.h
 * Description  : A header file for the subc program.
 */

#ifndef __SUBC_H__
#define __SUBC_H__

#include <stdio.h>
#include <string.h>

#define HASH_SIZE 101

typedef enum { T_INT, T_CHAR, T_ARRAY, T_FUNC, T_NULL } TypeKind;

typedef struct TypeInfo {
    TypeKind kind;
    int size;
    struct TypeInfo *base;
    struct ParamList *fields;
    struct SymbolTable *struct_table;
} TypeInfo;

typedef struct ParamList {
    char *name;              
    struct TypeInfo *type;
    struct ParamList *next;
} ParamList;

typedef struct ExprInfo {
    TypeInfo *type;
    int is_lvalue;
} ExprInfo;

typedef struct Symbol {
    char *name;          
    TypeInfo *type;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *buckets[HASH_SIZE];
    struct SymbolTable *outer_scope; 
} SymbolTable;

Symbol* lookup_symbol(char* name);
SymbolTable* create_table();
void error_redeclaration();
void error_return();
void error_assignable();
void error_incompatible();
void error_comparable();
void error_binary();
void error_unary();
void error_undeclared();
void error_addressof();
void error_indirection();
void error_array();
void error_subscript();
void error_strurctp();
void error_struct();
void error_function();
void error_arguments(); 
void error_incompatible();
void error_member();
// declare functions used in other source code file here

#endif
