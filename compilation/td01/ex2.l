%{
  #include <stdio.h>
  int cpt;
%}

%%
cabb { printf("(%d, 0)\n", cpt); cpt+=yyleng;}
cbab { printf("(%d, 1)\n", cpt); cpt+=yyleng;}
cbbba { printf("(%d, 3)\n", cpt); cpt+=yyleng;}
cbb { printf("(%d, 2)\n", cpt); cpt+=yyleng;}
[abc] {cpt++;}
. { cpt++;printf("Lecture d'un caractère n'appartenant pas à l'alphabet.\n");}
\n {cpt=0;}
%%


int yywrap() {return 1;}

int main(int argc, char **argv){
  cpt=0;
  yylex();
  return 0;
}
