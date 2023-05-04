#include "common.h"

#include "funcs.h"

int **init_map(int *dimension,int value){
	int n = dimension[0];
	int p = dimension[1];
	int **arr = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(p * sizeof(int));
        for (int j = 0; j < p; j++) {
            arr[i][j] = value;
        }
    }
    return arr;
}

void init_array2d(int n, int p, int arr[n][p],int value) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            arr[i][j] = value;
        }
    }
}

void init_array1d(int n, int arr[n],int value) {
    for (int i = 0; i < n; i++) {
            arr[i] = value;
    }
}

int *init_array(int dim,int value){
	int *array = malloc(sizeof(int)*dim);
	for (int i = 0; i < dim; i++)
	{
		array[i] = value;
	}
	return array;
}

void display_array(int *array,int dim){
	int i = 0;
	while (i < dim)
	{
		printf("%i\t",array[i]);
		i++;
	}
	printf("\n");
}

int *inverse_path(int dim,int*path){
	int fin = 0;
	while (path[fin] != -1){
		fin++;
	}
	fin--;
	
	int *path_inversed = init_array(fin+2,-1);

	int i = 0;
	while (fin-i != -1){
		
		path_inversed[i] = path[fin-i];
		i++;
	}
	
	free(path);
	return path_inversed;
}

void display_map(int **map, int *dimension){
	for (int i = 0; i < dimension[0]; i++)
	{
		for (int j = 0; j < dimension[1]; j++)
		{
			printf("%i\t",map[i][j]);
		}
		printf("\n");
		
	}
	
}

int indices_to_index(int row , int col, int *dimensions){
    return row*dimensions[1] + col;
}

int *index_to_indices(int index , int *dimensions){
    int *indices = malloc(sizeof(int)*2);
    indices[1] = index % dimensions[1];
    indices[0] = (index - indices[1]) / dimensions[1] ; 
    return indices;
}

void map_to_speedMap(int n,int p,int **map,int speedmap[n][p],int vm, int vf,int vc,int **map_feu){

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (map[i][j] == 1)
            {
                speedmap[i][j] = vm;//vitesse moutain
            }
            if (map[i][j] == 2)
            {
                speedmap[i][j] = vc;//vitesse city
            }
            if (map[i][j] == 3)
            {
                speedmap[i][j] = vf;//vitesse forest
            }
			if (map_feu[i][j] == 1)
			{
				speedmap[i][j] = INF;
			}
			
            
        }
        
    }
}

void int_to_string(int num,char str[3]) {
    sprintf(str, "%03d", num);
}
