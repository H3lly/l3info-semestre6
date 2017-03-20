#include <stdlib.h>
#include "heap.h"


heap heap_create(int n, int (*f)(const void *, const void *)){
  heap h=malloc(sizeof(*h));
  h->nmax=n;
  h->size=0;
  h->array=malloc((n+1)*sizeof(void*)); // indice 0 non utilisÃ©
  h->f=f;
  return h;
}


void heap_destroy(heap h){
  free(h->array);
  free(h);
}


int heap_empty(heap h){
  return (h->size==0);
}


int heap_add(heap h, void *object){
  if(h->size==h->nmax) return 1;
  int i=++h->size;
  void *p;
  h->array[i]=object;
  
  while((i>1) && (h->f(h->array[i],h->array[i/2])<0)){
    p=h->array[i];
    h->array[i]=h->array[i/2];
    h->array[i/2]=p;
    i/=2;
  }
  
  return 0;
}


void *heap_top(heap h){
  if(heap_empty(h)) return NULL;
  return h->array[1];
}


void *heap_pop(heap h){
  void *p=heap_top(h);
  int i,j,k;
  void *t;

  if(p){
    h->array[1]=h->array[h->size--];
    if(h->size){ // il reste au moins 1 Ã©lÃ©ment
      
      for(i=1;;i=j){
	k=2*i; if(k>h->size) break; // fin si i n'a pas de fils gauche
	j=(h->f(h->array[i],h->array[k])<0)? i : k; // j=min de (i,k)
	k++; if((k<=h->size)&&(h->f(h->array[k],h->array[j])<0)) j=k; // j=min de (i,j,k)
	if(i==j) break; // fin si i est le minimum
	t=h->array[i]; // inverse i avec j
	h->array[i]=h->array[j];
	h->array[j]=t;
      }
      
    }
  }

  return p;
}

