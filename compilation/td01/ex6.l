%{
int nb_a = 0;
int nb_b = 0;
int nb_c = 0;
int res;
%}

%%
a		{printf("b");}
b		{printf("c");}
c		{printf("a");}
[^abc\n] 	{ res = 0; return(res);}
%%
int main() {
	yylex();
}
