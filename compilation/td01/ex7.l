%{
  #include <stdio.h>
%}

%s R1 R2 R3

%%
<INITIAL>{
  (aa)+b{
    cpt=yyleng;
    reject();
    BEGIN(R1);
  }
  (ab)+b{
    cpt=yylen;
    reject();
    BEGIN(R2);
  }
  //...
  <RI>{
    a {
      printf("b");
      if(cpt--==0)
	BEGIN(INITIAL);
    }
    b {
      printf("d");
      if(cpt-- ==0)
	BEGIN(INITIAL);
    }
  }
 }
%%
int rescan(){
  char * copy;
  copy = strdup(yytext); //fait un malloc !
  for(int i=yyleng-1 ; i>=0 ; i--)
    input(copy[i]);
  fee(copy);
}

int yywrap(){ return 1;}
int main(int argc, int **argv){
  yylex();
  return 0;
}
