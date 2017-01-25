%{
  #include <stdio.h>
  int tmp;
%}

%%
.*(cabb|cbab|cbb|cbba).* { printf("Trouvé !\n");}
[abc] {}
. { printf("Lecture d'un caractère n'appartenant pas à l'alphabet.\n");}
%%

int yywrap() {return 1;}

   int main(int argc, char **argv){
     yylex();
     return 0;
   }
