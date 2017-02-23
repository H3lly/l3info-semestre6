
%{
int res = 0;
%}
%s PLURIEL
espace [[:space:]\n]
%%
({espace}les{espace}|{espace}quelques{espace}|{espace}des{espace}) 	{BEGIN PLURIEL;printf("%s",yytext);}
({espace}(U|u)n{espace}|{espace}le{espace})		{BEGIN INITIAL;printf("%s",yytext);}
loups?				{printf("ours");}
Alpes 				{printf("Pyrennes");}
<PLURIEL>chamois{espace}		{printf("izards ");}
chamois{espace}			{printf("izard ");}
Pralognan			{printf("Saint - Girons");}
%%
int main(int argc,char *argv[]) {
	yylex();
}
