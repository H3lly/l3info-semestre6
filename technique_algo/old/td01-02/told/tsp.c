#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>


#include "utils.h"
#include "variables.h"

#include "misc.c"

// Génère des points aléatoires dans le rectangle [0,max_X] × [0,max_Y]
static point* generatePoints(int n, int max_X, int max_Y) {
	point *V = malloc(n * sizeof(point));
	double ratio_x = (double) max_X / RAND_MAX;
	double ratio_y = (double) max_Y / RAND_MAX;
	for (int i = 0 ; i < n ; i++) {
		V[i].x = rand() * ratio_x;
		V[i].y = rand() * ratio_y;
	}
	return V;
}

static double dist(point p1, point p2) {
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

static double value(point *V, int n, int *P) {
  double val = 0;
  for(int i=0 ; i<n-1 ; ++i)
    val +=dist(V[P[i]], V[P[i+1]]);
  return val+dist(V[P[n-1]], V[P[0]]);
}

/*static int * modifier_P(point *V, int *P,){
  faire le 
  }*/
static double value_opti(point *V, int n, int *P, double w) {
  double val = 0;
  int i;
  for(i=0 ; i<n-1 ; ++i){
    val +=dist(V[P[i]], V[P[i+1]]);
    if(val+=dist(V[P[i+1]], V[P[0]])>w)
      break;
  }
  if(i==n-1)
    return val+dist(V[P[n-1]], V[P[0]]);
  else{
    //modifier_P
    return -i;
  }
}

static double tsp_brute_force_opti(point *V, int n, int *P) {
  int Q[n];
  double res = DBL_MAX;
  for(int i=0 ; i<n ; ++i){
    Q[i] = i;
  }
  do{
    int val = value_opti(V, n, Q, res);
    if(res>val && val>0){
      res=val;
      for(int j=0 ; j<n ; ++j)
        P[j] = Q[j];
    }
  }while(NextPermutation(Q, n)>0);
  return res;
}

static double tsp_brute_force(point *V, int n, int *P) {
  int Q[n];
  double res = DBL_MAX;
  for(int i=0 ; i<n ; ++i){
    Q[i] = i;
  }
  do{
    int val = value(V, n, Q);
    if(res>val){
      res=val;
      for(int j=0 ; j<n ; ++j)
        P[j] = Q[j];
    }
  }while(NextPermutation(Q, n)>0);
  return res;
}

// TP 02 *********************************************************************************************

static void drawPath(point *V, int n, int *path, int len);

/* ==== Programmation dynamique ====*/

static int NextSet(unsigned S, int n){
/*
  Renvoie le plus petit entier immédiatement supérieure à S>0 et qui a
  soit le même poids que S (c'est-à-dire le même nombre de 1 dans son
  écriture binaire que S), soit le poids de S plus 1 s'il n'y en a pas
  de même poids. La fonction renvoie 0 si S est le dernier entier sur
  n bits, soit S=2^n-1. Pensez à inclure <string.h>.
*/
  int p1 = ffs(S);
  int p2 = ffs(~(S >> p1)) + p1 - 1;
  if (p2 - p1 + 1 == n) return 0; // cas S=2^n
  if (p2 == n) return (1 << (p2 - p1 + 2)) - 1; // cas: poids(S)+1
  int mask = (-1) << p2;
  return (S & mask) | 1 << p2 | ((1 << (p2 - p1)) - 1); // cas: poids(S)
}

#define IN_SET(S,i)  ((S) & (1 << (i))) // est-ce que i est dans S ?
#define ADD_SET(S,i) (S | (1 << (i)))   // ajoute i à S
#define DEL_SET(S,i) (S & ~(1 << (i)))  // supprimer i de S

/* une cellule de la table */
typedef struct{
  int v;
  double d;
} cell;

static double tsp_prog_dyn(point *V, int n, int *Q){
  //CODE PROF
  cell **D;
  D = malloc((n-1)*sizeof(cell*));
  for(t=0; t<n-1;t++){
    D[t] = malloc((1<<(n-1))*sizeof(cell)); ///???????
  }
  //FIN CODE PROF



  
/*
  Version programmation dynamique du TSP. Le résultat doit être écrit
  dans la permutation Q. On renvoie la valeur de la tournée minimum ou
  -1 s'il y a eut une erreur.

  Attention ! Par rapport au cours, il est plus malin de commencer la
  tournée à partir du sommet d'indice n-1 (au lieu de 0). Pourquoi ?

  Donc D[t][S] = coût minimum d'un chemin allant de V[n-1] à V[t] qui
  visite tous les sommets d'indice dans S.

  Il sera intéressant de dessiner à chaque fois que possible le chemin
  courant avec drawPath()
*/

  //CODE PROF
  int S = 1; // S=000...0001

  for(int t=0 ; t<n-1 ; t++){
    D[t][S] = dist(V[n-1], V[t]);
    S = NextSet(S, n-1);
  }

  // ici S=000...00011
  
  //FIN CODE PROF
    
    do{
      //CODE PROF
      int xm;
      for(int t=0; t<n1;t++){
	if (!IN_SET(S, t)) continue;
	double m = DBL_MAX; //double maximum
	int St = DEL_SET(S, t);
	for(int x=0 ; x<n-1 ; ++x){
	  if(IN_SET(St, x)){
	    m=fmin(m, D[x][St])+dist(V[x], V[t]);
	    xm = x;
	}
	D[t][S].d=m;
	D[t][S].v=xm;
      }      
      //FIN
      
         drawPath(V, n, Q, i+1); // dessine le chemin courant

	 //...
	
    }while ((S = nextSet(S, n-1)) && running);

    // ne pas reconstruire la permutation si le calcul a été interrompu
    if(!running){
      free(D); //?? pas sûre
      return -1;
    }

    // tournée_min
    ///moi < ?

    
    free ...
    return ...;
}


static void drawPath(point *V, int n, int *path, int len) {
	// Saute le dessin si le précédent a été fait il y a moins de 20ms
	static unsigned int last_tick = 0;
	if (last_tick + 20 > SDL_GetTicks())
		return;
	last_tick = SDL_GetTicks();

	// Gestion de la file d'event
	handleEvent(false);

	// Efface la fenêtre
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Dessin …
	// Choisir la couleur blanche
	selectColor(0.0f, 1.0f, 0.0f);
	for (int i = 0 ; i < len-1 ; i++)
		drawLine(V[path[i]], V[path[i+1]]);
	// Rouge
	selectColor(1.0f, 0.0f, 0.0f);
	for (int i = 0 ; i < n ; i++)
		drawPoint(V[i]);

	// Affiche le dessin
	SDL_GL_SwapWindow(window);
}

// FIN *****************************************************

// Taille initiale de la fenêtre
int width = 640;
int height = 480;

bool running = true;
bool mouse_down = false;
double scale = 1.0f;

static void draw(point *V, int n, int *P) {
	// Efface la fenêtre
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Dessin…
	// Choisir la couleur blanche
	selectColor(1.0f, 1.0f, 1.0f);
	for (int i = 0 ; i < n ; i++)
		drawLine(V[P[i]], V[P[(i+1) % n]]);
	// Rouge
	selectColor(1.0f, 0.0f, 0.0f);
	for (int i = 0 ; i < n ; i++)
		drawPoint(V[i]);

	handleEvent(false);

	// Affiche le dessin
	SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[]) {

	initSDLOpenGL();

	bool need_redraw = true;
	bool wait_event = true;
	int n = 10;
	if(argc > 1)
	  n = atoi(argv[1]);
	int X = 300, Y = 200;
	point *V = generatePoints(n, X, Y);
	int *P = malloc(n * sizeof(int));
	for (int i = 0 ; i < n ; i++) P[i] = i;

	TopChrono(0); // initialise tous les chronos
	TopChrono(1); // départ du chrono 1

	double w = tsp_brute_force(V,n,P);
	//double w = tsp_brute_force_opti(V,n,P);
	
	char *s = TopChrono(1); // s=durée

	printf("value: %g\n",w);
	printf("runing time: %s\n",s);

	// Affiche le résultat (q pour sortir)
	while (running) {

		if (need_redraw)
			draw(V, n, P);

		need_redraw = handleEvent(wait_event);
	}

	// Libération de la mémoire
	TopChrono(-1);
	free(V);
	free(P);

	cleaning();
	return 0;
}
