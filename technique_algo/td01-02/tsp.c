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
