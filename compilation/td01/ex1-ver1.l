%{
  #include <stdio.h>
  int flag;
%}

%%
\n {printf("Ok. Flag : %d\n", flag);} //à chaque fois qu'on fais retour chariot
abb {flag=1;} //si on a abb, flag prend la valeur de 1
//[abc] {} //s'il y a, ou pas, les caractères a, b ou c, ne rien faire
. printf("ERROR : nous n'avons rien trouvé.\n"); //n'importe quel autre caractère, affiche erreur
%%

int yywrap() {return 1;}
int main(int argc, char ** argv){flag=0; yylex(); return 0;}
