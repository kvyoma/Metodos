#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stdlib.h"
#include "stdio.h"
#include <time.h>
#include <float.h>

int ITERACIONES = 2000;
int n_x = 744; //Columnas
int n_y = 500; //Filas
int **matrix;
FILE *file;

int minx;
int maxx;
int miny;
int maxy;

int posx;
int posy;
double rad;

void cargarDatos(char *ruta);
void imprimir(int **matrix);
void calcularRta();
double calcRadio(int x, int y);
int darRandom();
int dentroDeBoundaries(int x, int y);
void generarData(char coso[]);

double _random(void);


int main(void){
    srand(time(NULL));
    cargarDatos("map_data.txt");
    calcularRta();
    printf("las coordenadas del punto más alejado son: %d, %d\n",posx,posy );

    generarData("out.dat");
    // imprimir(matrix);


    return 0;
}

void generarData(char coso[]){
  FILE *fp;

   fp = fopen(coso, "w");


   fprintf(fp,"%d\n",posx );
   fprintf(fp,"%d\n",posy );
   fprintf(fp,"%f\n",sqrt(rad) );



   fclose(fp);
}



void calcularRta(){
  minx= 0;
  maxx= n_x-1;
  miny=0;
  maxy=n_y-1;

  posx = 100;
  posy = 300;
  rad = calcRadio(posx,posy);
  // printf("%d %d %f\n",posx, posy, rad );

  int e;
  int tpx = posx;
  int tpy = posy;

  for(e = 0; e < ITERACIONES;e++){
    // printf("EMpezo\n" );
    int ttpx = tpx + darRandom();
    int ttpy = tpy + darRandom();
    // printf("%d %d\n",ttpx,ttpy );
    // printf("%d\n", e);
    double alpha = calcRadio(ttpx,ttpy)/calcRadio(tpx,tpy);

    if(alpha>=1.0&& dentroDeBoundaries(ttpx,ttpy)){
      tpx = ttpx;
      tpy = ttpy;
      // printf("Entro alfa\n" );

      if(calcRadio(tpx,tpy)>rad){
        // printf("Entro a calcRadio\n" );
        posx = tpx;
        posy = tpy;
        rad = calcRadio(tpx,tpy);
        // printf("Entro a pos %d %d %f\n",posx, posy, rad );
      }
    }
    else if(dentroDeBoundaries(ttpx,ttpy)){
      double beta = (double)rand()/RAND_MAX;
      // printf("Entro a beta\n" );
      if(beta<=alpha){
        tpx = ttpx;
        tpy = ttpy;
        //mirar
        if(calcRadio(tpx,tpy)>rad){
          posx = tpx;
          posy = tpy;
          rad = calcRadio(tpx,tpy);
        }
      }
    }
  }


}

int darRandom(){
  int coso =50;
  int rand1 = ((rand()) % coso)-(coso/2)  ;

  // printf("randoo  %d\n",rand1 );
  return rand1;
}
double calcRadio(int x, int y){
  int i,j;
  double tempRad = DBL_MAX;
  for (i = 0; i < n_y; i++)
  {
      for (j = 0; j < n_x; j++)
      {
        if(!(x==j && y==i)){
          if(matrix[i][j]==1){
            double distancia = (x-j)*(x-j) + (y-i)*(y-i);
            if(distancia<tempRad){
              tempRad = distancia;
            }
          }
        }
      }
  }
  return tempRad;
}


void cargarDatos(char *ruta){
  int i, j, contador;

  matrix = malloc(n_y*sizeof(int*));
  for (i = 0; i < n_y; i++)
  {
          matrix[i] = malloc(n_x*sizeof(int));
  }


  file = fopen(ruta, "r");
  for (i = 0; i < n_y; i++)
  {
      for (j = 0; j < n_x; j++)
      {
          fscanf(file, "%d ", &matrix[i][j]);
      }

  }
  fclose(file);
}

void imprimir(int **matrix){
	int i, j;
	for(i=0; i<n_y; i++){
		for(j=0; j<n_x; j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}
int dentroDeBoundaries(int x, int y){
  int ans =1 ;
  if(x<minx || x>maxx){
    ans = 0;
  }
  if(y<miny || y>maxy){
    ans =0;
  }

  return ans;
}
