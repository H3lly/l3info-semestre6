
%{
	#include <stdio.h>
	int cptx = 0;
	int cptlong = 0;
%}

%s PLURIEL

espace [[:space:]\n]

%%
{espace}X[0-1]*{espace} {cptx++;}
{espace}LONG{espace} {cptlong++;}
%%

int main(int argc,char *argv[]) {
	yylex();
}	printf("X[0-1] = %d | LONG = %d\n", cptx, cptlong);
