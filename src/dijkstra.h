int find_argmin(int n,int p,int dist_map[n][p],int *dim);
void update_distmap(int n,int p,int dist_map[n][p],int visited_map[n][p]);
int *dijkstra(int* dim,int **map,int **map_feu, int x, int y,int vm,int vf,int vc,int xe,int ye);
int find_spot(int* dim,int **map, int x, int y,int spot);