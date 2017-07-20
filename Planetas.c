#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static const double G = 6.67408E-11;

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
