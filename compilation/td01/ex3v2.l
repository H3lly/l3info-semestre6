%{
  #include <stdio.h>
%}

%s PP PI IP II  

%%
<PP>{
  a {BEGIN(IP);}
  b {BEGIN(PI);}
  \n {printf("non reconnu\n");}
  . {printf("ERROR\n");}
 }
<PI>{
  \n {printf("Ok.\n"); BEGIN(PP);}
  a {BEGIN(II);}
  b {BEGIN(PP);}
 }
<II>{
  a {BEGIN(PI);}
  b {BEGIN(IP);}
  \n {printf("non reconnu\n"); BEGIN(PP);}
  . {printf("ERROR\n");}
 }
<IP>{
  a {BEGIN(PP);}
  b {BEGIN(II);}
  \n {printf("non reconnu\n"); BEGIN(PP);}
  . {printf("ERROR\n");}
 }
%%

int yywrap(){return 1;}

int main(int argc, int **argv){
  BEGIN(PP);
  yylex();
  return 0;
}
