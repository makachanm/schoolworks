/*                                                                          */
/* File Name    : subc.l                                                    */
/* Description  : a skeleton flex input                                     */
/*                                                                          */
/* Course       : Compiler                                                  */
/*                                                                          */

%{
/* C Code Section */
/* Any code placed inside the brackets will be literally copied into the generated C file. */

#include <stdio.h>
#include <strings.h>
#include "subc.tab.h"
%}

%option noyywrap

/* Definitions Section */
/* This section contains simple name definitions and declarations of start conditions. */
ID            [a-zA-Z_][a-zA-Z0-9_]*
digit         [0-9]
integer_const ([1-9]{digit}*)|"0"

%%

[ \t\r]+     ;
\n           ;
"/*"([^*]|\*+[^*/])*\*+"/" ;

"int"|"char"    { return TYPE; }
"struct"        { return STRUCT; }
"NULL"          { return SYM_NULL; }
"return"        { return RETURN; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }

"||"            { return LOGICAL_OR; }
"&&"            { return LOGICAL_AND; }
"<"|"<="|">"|">=" { return RELOP; }
"=="|"!="       { return EQUOP; }
"++"            { return INCOP; }
"--"            { return DECOP; }
"->"            { return STRUCTOP; }

{integer_const} { return INTEGER_CONST; }
\"([^\"\\\n]|\\.)*\" { return STRING; }
'([^'\\\n]|\\.)'    { return CHAR_CONST; }

{ID}            { return ID; }

.               { return yytext[0]; }
%%

