%{
  #include <stdio.h>
%}

%%
[abc]*abb[abc]*\n {printf("Ok.\n");}
.|\n {}
%%

int yywrap(){
  return 1;
}

int main(int argc, char ** argv){
  yylex();
  return 0;
}
