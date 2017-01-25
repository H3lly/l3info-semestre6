%{
  #include <stdio.h>
  int cpta;
  int cptb;
%}

%%
a {cpta++;}
b {cptb++;}
\n {
  if(cpta%2 == 0 && cptb%2 == 1 && cpta!=0 && cptb !=0)
    printf("Mot reconnu.\n");
  cpta = 0;
  cptb = 0;
}

%%
int yywrap(){ return 1;}
int main(int argc, int **argv){
  cpta = 0;
  cptb = 0;
  yylex();
  return 0;
}
