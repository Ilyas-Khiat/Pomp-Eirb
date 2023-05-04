int **init_map(int *dimension,int value);
void display_map(int **map, int *dimension);

int *init_array(int dim,int value);
void display_array(int *array,int dim);
int *inverse_path(int dim,int*path);

int indices_to_index(int row , int col, int *dimensions);
int *index_to_indices(int index , int *dimensions);

void map_to_speedMap(int n,int p,int **map,int speedmap[n][p],int vm, int vf,int vc,int **map_feu);
void init_array2d(int n, int p, int arr[n][p],int value);
void init_array1d(int n, int arr[n],int value);

void int_to_string(int num,char str[3]);