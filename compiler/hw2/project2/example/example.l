%{
#include "example.tab.h"
#include <stdio.h>
%}

ws 		[ \t]
num 	[0-9]
OP 		"+"|"-"|"*"|"/"

%%
\n 		{ return ENTER; }
{ws} 	{}
{num}+ {
	yylval = atoi(yytext);
	return NUMBER;
	}
{OP} 	{ return yytext[0]; }

%%
int main(int argc, char* argv[]){
    // I/O stream settings                                                                                                               
    if (argc >= 2) {                                                                                                                     
        yyin = fopen(argv[1], "r");                                                                                                        
    } else {                                                                                                                             
        yyin = stdin;                                                                                                                      
    }                                                                                                                                    

    if(!yyin) {                                                                                                                          
        printf("Can't open input stream!\n");                                                                                              
        exit(1);                                                                                                                           
    }                                                                                                                                    

    yyparse();                                                                                                                           
    fclose(yyin);                                                                                                                        

    return 0; 

}

