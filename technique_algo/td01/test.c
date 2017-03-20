#include <stdio.h>

int*  MaxPermutation(int *P, int k, int n){
  int prefixe  = k-1;
  while(P[n]!=prefixe){
    P[n] = k;
    n--;
    k++;
  }
  return P;
}

int main(void){
  int t[8];
  t[0] = 0;
  t[1] = 1;
  t[2] = 2;
  t[3] = 3;
  t[4] = 5;
  t[5] = 4;
  t[6] = 7;
  t[7] = 6;
  int* max = MaxPermutation(t, 4, 7);
  for(int i=0 ; i<8 ; ++i)
    printf("%d ", max[i]);
}
