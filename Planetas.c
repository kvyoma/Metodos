#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static const double G = 6.67408E-11;
void imprimir(double matriz[10][20]);

void calcPreFuerza(double matriz[10][20]);

void preFuerzaUnPlaneta(double matriz[10][20],int planeta);

void preleapUnPlaneta(double matriz[10][20],int planeta, double h);

void preleap(double matriz[10][20], double h);

void resetFs(double matriz[10][20]);

void calFs(double matriz[10][20]);

void calcFsUnPlaneta(double matriz[10][20], int planeta);

void leap(double matriz[10][20], double h);

void leapUnPlaneta(double matriz[10][20], int planeta, double h);

void printLines(double matriz[10][20]);

void solucionar(double matriz[10][20], int steps);

int main(void)
{
	FILE *file;
	file = fopen("coordinates.csv", "r");

	int len = 250;
	char line_buffer[len];
	char *split_buffer;
	int i=0, j=0;
	double matriz[10][20];

	while (fgets(line_buffer, len, file))
	{
		split_buffer=strtok(line_buffer, ",");
		j=0;
		while(split_buffer != NULL)
		{
			
			if(j>0){
				matriz[i][j-1] = atof(split_buffer);
			}
			
			split_buffer=strtok(NULL, ",");
			j +=1;
		}
		i +=1;
	}

	return 0;
}

void solucionar(double matriz[10][20], int steps){

	for(int i = 0; i<10; i++){
		printf("%f %f %f ", matriz[i][1],matriz[i][2],matriz[i][3]);
	}

	printf("\n");
	for(int i = 0; i<steps; i++){
		resetFs(matriz);
		calFs(matriz);
		leap(matriz,0.01);
		printLines(matriz);
	}
}

void printLines(double matriz[10][20]){
	for(int i = 0; i<10; i++){
		printf("%f %f %f ", matriz[i][10],matriz[i][11],matriz[i][12]);
	}
	printf("\n");
}

void imprimir(double matriz[10][20]){
	int i, j;
	for(i=0;i<10;i=i+1){
		for(j=0;j<20;j=j+1){
			printf("%f ",matriz[i][j] );
		}
		printf("\n");
	}
}

void calcPreFuerza(double matriz[10][20]){
	int i;
	for(i = 0; i<10;i++){
		preFuerzaUnPlaneta(matriz,i);
	}

}

void preFuerzaUnPlaneta(double matriz[10][20], int planeta){
	for(int i=0;i<10;i++){
		if(i!=planeta){
			double dx = matriz[i][1] - matriz[planeta][1];
			double dy = matriz[i][2] - matriz[planeta][2];
			double dz = matriz[i][3] - matriz[planeta][3];
			double phi = -1*G*matriz[planeta][0]*matriz[i][0]/(dx*dx + dy*dy + dz*dz);
			double rx = dx/(sqrt(dx*dx + dy*dy + dz*dz));
			double ry = dy/(sqrt(dx*dx + dy*dy + dz*dz));
			double rz = dz/(sqrt(dx*dx + dy*dy + dz*dz));
			matriz[planeta][7] = phi*rx + matriz[planeta][7];
			matriz[planeta][8] = phi*ry + matriz[planeta][8];
			matriz[planeta][9] = phi*rz + matriz[planeta][9];
		}
	}
}


void preleapUnPlaneta(double matriz[10][20],int planeta,double h){
	matriz[planeta][13] = matriz[planeta][4] + h*matriz[planeta][7]/matriz[planeta][0];
	matriz[planeta][14] = matriz[planeta][5] + h*matriz[planeta][8]/matriz[planeta][0];
	matriz[planeta][15] = matriz[planeta][6] + h*matriz[planeta][9]/matriz[planeta][0];

	matriz[planeta][10] = matriz[planeta][1] + h*matriz[planeta][13];
	matriz[planeta][11] = matriz[planeta][2] + h*matriz[planeta][14];
	matriz[planeta][12] = matriz[planeta][3] + h*matriz[planeta][15];
}

void preleap(double matriz[10][20], double h){
	int i;
	for(i = 0; i<10 ; i++){
		preleapUnPlaneta(matriz,i,h);
	}
}

void resetFs(double matriz[10][20]){
	for(int i = 0; i<10; i++){
		matriz[i][16] = 0.0;
		matriz[i][17] = 0.0;
		matriz[i][18] = 0.0;
	}
}

void calFs(double matriz[10][20]){
	for(int i = 0; i<10; i++){
		calcFsUnPlaneta(matriz, i);
	}
}
void calcFsUnPlaneta(double matriz[10][20], int planeta){
	for(int i=0;i<10;i++){
		if(i!=planeta){
			double dx = matriz[i][10] - matriz[planeta][10];
			double dy = matriz[i][11] - matriz[planeta][11];
			double dz = matriz[i][12] - matriz[planeta][12];
			double phi = -1*G*matriz[planeta][0]*matriz[i][0]/(dx*dx + dy*dy + dz*dz);
			double rx = dx/(sqrt(dx*dx + dy*dy + dz*dz));
			double ry = dy/(sqrt(dx*dx + dy*dy + dz*dz));
			double rz = dz/(sqrt(dx*dx + dy*dy + dz*dz));
			matriz[planeta][16] = phi*rx + matriz[planeta][16];
			matriz[planeta][17] = phi*ry + matriz[planeta][17];
			matriz[planeta][18] = phi*rz + matriz[planeta][18];
		}
	}
}

void leap(double matriz[10][20], double h){
	for(int i = 0 ; i<10 ; i++){
		leapUnPlaneta(matriz,i,h);	
	}
}

void leapUnPlaneta(double matriz[10][20], int planeta, double h){

	double vxmed = matriz[planeta][13] + 0.5*h*matriz[planeta][16]/matriz[planeta][0];
	double vymed = matriz[planeta][14] + 0.5*h*matriz[planeta][17]/matriz[planeta][0];
	double vzmed = matriz[planeta][15] + 0.5*h*matriz[planeta][18]/matriz[planeta][0];

	matriz[planeta][10] = matriz[planeta][10] + vxmed*h;
	matriz[planeta][11] = matriz[planeta][11] + vymed*h;
	matriz[planeta][12] = matriz[planeta][12] + vzmed*h; 

	matriz[planeta][13] = vxmed + 0.5*h*matriz[planeta][16]/matriz[planeta][0];
	matriz[planeta][14] = vymed + 0.5*h*matriz[planeta][17]/matriz[planeta][0];
	matriz[planeta][15] = vzmed + 0.5*h*matriz[planeta][18]/matriz[planeta][0];      
}
