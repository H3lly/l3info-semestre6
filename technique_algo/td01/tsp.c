//
//  TSP
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "variables.h"
#include "utils.h"
#include "misc.c"


static void drawTour(point *V, int n, int *P){
  // saute le dessin si le précédent a été fait il y a moins de 20ms
  static unsigned int last_tick = 0;
  if(n<0) { last_tick = 0; n=-n; }  // force le dessin si n<0
  if(last_tick + 20 > SDL_GetTicks()) return;
  last_tick = SDL_GetTicks();

  // gestion de la file d'event
  handleEvent(false);

  // efface la fenêtre
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // dessine le cycle
  if(P && V){
    selectColor(1,1,1); // couleur blanche
    for (int i = 0 ; i < n ; i++)
      drawLine(V[P[i]], V[P[(i+1) % n]]);
  }
  // dessine les points
  if(V){
    selectColor(1,0,0); // couleur rouge
    for (int i = 0 ; i < n ; i++)
      drawPoint(V[i]);
  }

  // affiche le dessin
  SDL_GL_SwapWindow(window);
}


static void drawPath(point *V, int n, int *path, int len){
  // saute le dessin si le précédent a été fait il y a moins de 20ms
  static unsigned int last_tick = 0;
  if(n<0) { last_tick = 0; n=-n; }  // force le dessin si n<0
  if(last_tick + 20 > SDL_GetTicks()) return;
  last_tick = SDL_GetTicks();

  // gestion de la file d'event
  handleEvent(false);

  // efface la fenêtre
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // dessine le chemin
  selectColor(0,1,0); // vert
  for (int i = 0 ; i < len-1 ; i++)
    drawLine(V[path[i]], V[path[i+1]]);

  // dessine les points
  selectColor(1,0,0); // rouge
  for (int i = 0 ; i < n ; i++)
    drawPoint(V[i]);

  // affiche le dessin
  SDL_GL_SwapWindow(window);
}


// Génère n points aléatoires du rectangle entier [0,X] × [0,Y] et
// renvoie le tableau des n points ainsi générés et met à jour la
// variable globale vertices[].
static point* generatePoints(int n, int X, int Y) {
  vertices = malloc(n * sizeof(point));
  const double rx = (double) X / RAND_MAX;
  const double ry = (double) Y / RAND_MAX;
  for (int i = 0 ; i < n ; i++){
    vertices[i].x = random() * rx;
    vertices[i].y = random() * ry;
  }
  return vertices;
}

static double dist(point A, point B){
  return sqrt((B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y));
}

static double value(point *V, int n, int *P){
	double val = 0;
  for(int i=0 ; i<n-1 ; ++i){
    val += dist(V[P[i]], V[P[i+1]]);
  }
  return val+dist(V[P[n-1]], V[P[0]]);
}

static double tsp_brute_force(point *V, int n, int *P){
  //remplissage tmp de la sorte : 0 1 2 3 ... n-1
  int tmp[n];
  for(int i=0 ; i<n ; ++i){
    tmp[i] = P[i];
  }
  double max = value(V, n, tmp); //initialisation de la première val possible
  do{
    double res = value(V, n, tmp);
    if(res<max){
      max=res;
      for(int i=0; i<n ; i++)
        P[i] = tmp[i];
    }
  } while(NextPermutation(tmp, n)/* && tmp[0]==0*/);
  return max;
}

void afficher_tableau(int *P, int n){
  printf("[");
  for(int i=0 ; i<n-1 ; ++i)
    printf("%d, ", P[i]);
  printf("%d]\n", n-1);
}

struct paire {
    int val;
    int use;
};

static void MaxPermutation(int *P, int n, int k) {
    struct paire Tab[n];
    for (int i = 0; i < n; i++) {
        Tab[i].val = i;
        Tab[i].use = 0;
    }
    for (int i = 0; i < k; i++)
        Tab[P[i]].use = 1;
    for (int i = k; i < n; i++) {
        int j = n - 1;
        while (Tab[j].use == 1 && j > 0) {
            j--;
        }
        if (Tab[j].use == 0) {
            P[i] = Tab[j].val;
            Tab[j].use = 1;
        }
    }

}

static double value_opt(point *V, int n, int *P,double w){
	double val = 0;
  for(int i=0 ; i<n-1 ; ++i){
    val += dist(V[P[i]], V[P[i+1]]);
    if(val>w)
      return -(i+1);
  }
  return val+dist(V[P[n-1]], V[P[0]]);
}

static double tsp_brute_force_opt(point *V, int n, int *P){
  int tmp[n];
  for(int i=0 ; i<n ; ++i){
    tmp[i] = P[i];
  }
  double max = value(V, n, tmp);
  do{

    double res = value_opt(V, n, tmp, max);
    if(res>0){
      if(res<max){
        max=res;
        for(int i=0; i<n ; i++)
          P[i] = tmp[i];
      }
    } else {
       MaxPermutation(tmp, -res, n);

    }
  } while(NextPermutation(tmp, n) && tmp[0]==0);
  return max;
}

// taille initiale de la fenêtre
int width = 640;
int height = 480;

// pour la fenêtre graphique
bool running = true;
bool mouse_down = false;
double scale = 1;


int main(int argc, char *argv[]) {

	initSDLOpenGL();
	srandom(time(NULL));
	TopChrono(0); // initialise tous les chronos

	bool need_redraw = true;
	bool wait_event = true;

	int n = 5;
	point *V = generatePoints(n, width, height);
	int *P = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++) P[i] = i; // première permutation
	drawTour(V, n, NULL); // dessine les points

	{/*
	  TopChrono(1); // départ du chrono 1
	  double w = tsp_brute_force(V,n,P);
	  char *s = TopChrono(1); // s=durée
	  printf("value: %g\n",w);
	  printf("runing time: %s\n",s);
	  drawTour(V, -n, P); // dessine la tournée
    */
	}

	{
	  
	    TopChrono(1); // départ du chrono 1
	    double w = tsp_brute_force_opt(V,n,P);
	    char *s = TopChrono(1); // s=durée
	    printf("value: %g\n",w);
	    printf("runing time: %s\n",s);
	    drawTour(V, -n, P); // dessine la tournée
	  
	}

	{
	  /*
	    TopChrono(1); // départ du chrono 1
	    double w = tsp_prog_dyn(V,n,P);
	    char *s = TopChrono(1); // s=durée
	    printf("value: %g\n",w);
	    printf("runing time: %s\n",s);
	    drawTour(V, -n, P); // dessine la tournée
	  */
	}

	// Affiche le résultat et attend (q pour sortir)
	while(running){
	  if (need_redraw) drawTour(V, n, P);
	  need_redraw = handleEvent(wait_event);
	}

	// Libération de la mémoire
	TopChrono(-1);
	free(V);
	free(P);

	cleaning();
	return 0;
}
