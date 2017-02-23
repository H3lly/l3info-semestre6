%{
   #include <stdio.h>
%}

%option noyywrap

radical \[[[:alpha:]]+
premier_groupe er\]
deuxieme_groupe ir\]

%s unPS deuxPS troisPS unPP deuxPP troisPP

%%

[Jj]e  {BEGIN(unPS); ECHO;}
[Tt]u  {BEGIN(deuxPS); ECHO;}
[Ii]l|[Ee]lle|[Oo]n  {BEGIN(troisPS); ECHO;}
[Nn]ous  {BEGIN(unPP); ECHO;}
[Vv]ous  {BEGIN(deuxPP); ECHO;}
[Ii]ls|[Ee]lles  {BEGIN(troisPP); ECHO;}
{premier_groupe} {}
{deuxieme_groupe} {}

<unPS,troisPS>{radical}/{premier_groupe} {printf("%se", yytext+1);}
<deuxPS>{radical}/{premier_groupe} {printf("%ses", yytext+1);}
<unPP>{radical}/{premier_groupe} {printf("%sons", yytext+1);}
<deuxPP>{radical}/{premier_groupe} {printf("%sez", yytext+1);}
<troisPP>{radical}/{premier_groupe} {printf("%sent", yytext+1);}

<unPS,deuxPS>{radical}/{deuxieme_groupe} {printf("%sis", yytext+1);}
<troisPS>{radical}/{deuxieme_groupe} {printf("%sit", yytext+1);}
<unPP>{radical}/{deuxieme_groupe} {printf("%sissons", yytext+1);}
<deuxPP>{radical}/{deuxieme_groupe} {printf("%sissez", yytext+1);}
<troisPP>{radical}/{deuxieme_groupe} {printf("%sissent", yytext+1);}

%%


int main(int argc,char *argv[]) {
	yylex();
}
