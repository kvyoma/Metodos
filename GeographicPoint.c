#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int n_x;
int n_y;

double **Matrix(void);
void freePointer(double **matrix);
void imprimir(double matrix[n_x][n_y]);

int main(void){
    int i, j;

    n_x = 744;
    n_y = 500;

    int **matrix = malloc(n_y*sizeof(int*));
	for (i = 0; i < n_y; i++)
    {
            matrix[i] = malloc(n_x*sizeof(int));
    }

    FILE *file;
    file = fopen("map_data.txt", "r");
    for (i = 0; i < n_y; i++)
    {
        for (j = 0; j < n_x; j++)
        {
            fscanf(file, "%d ", &matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    //imprimir(matrix);
    return 0;
}

double **Matrix(void){
    int i;
    double **matrix;
    matrix = malloc(n_y*sizeof(double *));

    for(i = 0; i < n_y; i++)
    {
        matrix[i] = malloc(n_x*sizeof(double));
    }
    return matrix;
}

void imprimir(double matrix[n_x][n_y]){
	int i, j;
	for(i=0; i<n_y; i=i++){
		for(j=0; j<n_x; j=j++){
			printf("%f ",matrix[i][j]);
		}
		printf("\n");
	}
}
