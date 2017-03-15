%{
  #include <stdio.h>
  #include <string.h>
%}

%option noyywrap
%%
[0-9] {return 0;}
. {return yytext[0];}
%%

int main(){
  int c;
  while((c=yylex())!='\n')
    printf("%d\n", c);
}
