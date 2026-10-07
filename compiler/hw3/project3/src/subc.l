/*                                                                          */
/* File Name    : subc.l                                                    */
/* Description  : a skeleton flex input                                     */
/*                                                                          */

%{

/* C Code Section */
/* Any code placed inside the brackets will be literally copied into the generated C file. */

#include "subc.h"
#include "subc.tab.h"
static int lineno = 1;
static char* file_name;

%}

/* Definitions Section */
/* This section contains simple name definitions and declarations of start conditions. */

letter        [A-Za-z_]
digit         [0-9]
id            {letter}({letter}|{digit})*
integer_const ([1-9]{digit}*)|"0"
whitespace    [ \t]
special_char  \\[nt]

%x COMMENT

%%

  /* Rules Section */
  /* This section contains series of rules for recognizing tokens. */

  /* Keywords */
"int"                           {
                                  yylval.intVal = T_INT;
                                  return TYPE;
                                }
"char"                          {
                                  yylval.intVal = T_CHAR;
                                  return TYPE;
                                }
"struct"                        { return STRUCT; } 
"NULL"                          { return SYM_NULL; }
"return"                        { return RETURN; }
"if"                            { return IF; }
"else"                          { return ELSE; }
"while"                         { return WHILE; }
"for"                           { return FOR; }
"break"                         { return BREAK; }
"continue"                      { return CONTINUE; }

  /* Identifiers */
{id}                            {
                                  yylval.stringVal = strdup(yytext);
                                  return ID;
                                }

  /* Integer constants */
{integer_const}                 {
                                  yylval.intVal = atoi(yytext);
                                  return INTEGER_CONST;
                                }

  /* String variables */
\"({special_char}|[^\\\"\n])*\" {
                                  return STRING;
                                }

  /* Character variables */
'({special_char}|[^\\'\n])'     {    
                                  return CHAR_CONST;
                                }

  /* Operators */
","|";"|"("|")"|"["|"]"|"{"|"}" { return yytext[0]; }
"!"|"*"|"/"|"%"|"+"|"-"|"&"     { return yytext[0]; }
"="|"."                         { return yytext[0]; }

"&&"                            { return LOGICAL_AND; }
"||"                            { return LOGICAL_OR; }
"<"|"<="|">"|">="               { return RELOP; }
"=="|"!="                       { return EQUOP; }
"++"                            { return INCOP; }
"--"                            { return DECOP; }
"->"                            { return STRUCTOP; }

  /* Whitespaces */
{whitespace}


  /* Comment blocks */
"/*"                            {
                                  BEGIN (COMMENT);
                                }
<COMMENT>"*/"                   { 
                                  BEGIN (INITIAL);
                                }
<COMMENT>.

  /* Line number tracking */
<*>\n       { ++lineno; }

%%
   
/* User Code Section */
/* The user code section is simply copied to lex.yy.c verbatim. */

int get_lineno() {
   return lineno;
}

