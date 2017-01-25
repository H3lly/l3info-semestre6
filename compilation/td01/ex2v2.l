%{
  #include <stdio.h>
  int cpt;
%}

%%
cabbb { printf("(%d, 0)\n", cpt); REJECT;}
bbc { printf("(%d, 1)\n", cpt); REJECT;}
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
