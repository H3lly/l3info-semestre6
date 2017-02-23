%{

%}
%option noyywrap
pronoms [:space:][me|te|le|la|nous|les]
radical \[[:alpha:]+
er er\]

%s unPS deuxPS troisPS unPP deuxPP troisPP

%%
(J|j)e{pronoms}?  {BEGIN unPS; printf("%s", yytext);}
(T|t)u{pronoms}?  {BEGIN unPS; printf("%s", yytext);}
(I|i)l|(E|e)lle|(O|o)n{pronoms}? {BEGIN troisPS; printf("%s", yytext);}
(N|n)ous{pronoms}?  {BEGIN unPP; printf("%s", yytext);}
(V|v)ous{pronoms}?  {BEGIN deuxPP; printf("%s", yytext);}
(I|i)ls|(E|e)lles{pronoms}? {BEGIN troisPP; printf("%s", yytext);}

<unPS>{radical}/er\] {
  printf("%se", yytext+1);
}
<deuxPS>{radical}/{er} {
  printf("%ses", yytext);
}
<troisPS>{radical}/{er} {
  printf("%se", yytext);
}
<unPP>{radical}/{er} {
  printf("%sons", yytext);
}
<deuxPP>{radical}/{er} {
  printf("%sez", yytext);
}
<troisPP>{radical}/{er} {
  printf("%sent", yytext);
}
%%


int main(int argc,char *argv[]) {
	yylex();
}
