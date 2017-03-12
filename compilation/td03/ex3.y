%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s);
%}

%start A

%%
A: S '\n'	{;}
 | S	 	{;}
 ;

S: 'a' S 'b';
 | 'a' 'b'
 ;
%%

int yylex(){
	return getchar();
}
int yyerror(char *s){
	fprintf( stderr, "*** ERROR: %s\n", s );
	return 0;
}
int main(int argn, char **argv){
	yyparse();
	return 0;
}