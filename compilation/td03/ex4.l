%{
#define NUMBER 0
%}

%%


[0-9]+  {return NUMBER;}
.       {return yytext[0];}


%%

int yyerror(char *s){
	fprintf(stderr, "*** ERROR: %s\n", s);
	return 0;
}

int yywrap(){
	return -1;
}

int main(int argc,char *argv[]) {
    int c;
    while ((c=yylex())!='\n') {
	    printf("%d\n",c);
	}
}