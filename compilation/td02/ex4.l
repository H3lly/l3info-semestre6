
%{
	#include <stdio.h>
	#define NB_FUNC 10
	struct fonction{
    	int nbArg;
    	char *word;
	} fonction;

	struct function functionFound[NB_FUNC];
	int nbFunc = 0;
	int currFunc = 0;
	int currArgs = 0;
%}

%s FUN COUNT
END [)]
COM [,]
INT int
BOOL bool
ARRAY array[ ]of[ ]type

ALL [A-Za-z0-9]

%%
defun[ ]{ALL}+ {BEGIN FUN;}


<readfunction>{}
%%

int main(int argc,char *argv[]) {
	yylex();
}