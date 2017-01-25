%{
  #include <stdio.h>
  int flag;
%}

%%
\n {printf("Ok. Flag : %d\n", flag);}
abb {flag=1;} 
[abc] {}
. printf("ERROR : nous n'avons rien trouvé.\n");

%%
int yywrap(){
  return 1;
}

int main(int argc, char ** argv){
  flag=0;
  yylex();
  return 0;
}
