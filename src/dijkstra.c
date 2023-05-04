#include "common.h"

#include "dijkstra.h"

void update_distmap(int n,int p,int dist_map[n][p],int visited_map[n][p]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (visited_map[i][j] == 1)
            {
                dist_map[i][j] = INF;
            }
        }
        
    }
    
}

int find_argmin(int n,int p,int dist_map[n][p],int *dim){
    int min = INF;
    int imin = 0;
    int jmin = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (dist_map[i][j]<min)
            {
                min = dist_map[i][j];
                imin = i;
                jmin = j;
            }
            
        }
        
    }
    return indices_to_index(imin,jmin,dim);   
}

int *dijkstra(int* dim,int **map,int **map_feu, int x, int y,int vm,int vf,int vc,int xe,int ye){
    //printf("(%i,%i)\n",dim[0],dim[1]);
    //display_map(map,dim);
    printf("dij\n");
    
    int origin_map[dim[0]][dim[1]];
    init_array2d(dim[0], dim[1], origin_map,INF);
    
    int visited_map[dim[0]][dim[1]];
    init_array2d(dim[0], dim[1],visited_map,0);

    int dist_map[dim[0]][dim[1]];
    init_array2d(dim[0], dim[1], dist_map,INF);
    
    int speedmap[dim[0]][dim[1]];
    init_array2d(dim[0], dim[1], speedmap,INF);
    map_to_speedMap(dim[0],dim[1],map,speedmap,vm,vf,vc,map_feu);
    
    speedmap[ye][xe] = 0;

    int finished = 0;
    int count = 0;
    int xs = x;
    int ys = y;
    dist_map[ys][xs] = 0;
    
    while (finished == 0)
    {
        
        // display(dist_map,dim);
        //check x+1 y
        if (xs < dim[1]-1)
        {
            if (dist_map[ys][xs+1]>speedmap[ys][xs+1]+dist_map[ys][xs] && visited_map[ys][xs+1] != 1 )
            {
                dist_map[ys][xs+1] = speedmap[ys][xs+1]+dist_map[ys][xs];
                origin_map[ys][xs+1] = indices_to_index(ys,xs,dim);
                
            }  
        }

        //check x-1 y
        if (xs > 0)
        {
            if (dist_map[ys][xs-1]>speedmap[ys][xs-1]+dist_map[ys][xs] && visited_map[ys][xs-1] != 1 )
            {
                dist_map[ys][xs-1] = speedmap[ys][xs-1]+dist_map[ys][xs];
                origin_map[ys][xs-1] = indices_to_index(ys,xs,dim);
            }  
        }

        //check x y+1
        if (ys < dim[0]-1)
        {
            
            if (dist_map[ys+1][xs]>speedmap[ys+1][xs]+dist_map[ys][xs] && visited_map[ys+1][xs] != 1 )
            {
                dist_map[ys+1][xs] = speedmap[ys+1][xs]+dist_map[ys][xs];
                origin_map[ys+1][xs] = indices_to_index(ys,xs,dim);
            }  
        }

        //check x y-1
        if (ys > 0)
        {
            if (dist_map[ys-1][xs]>speedmap[ys-1][xs]+dist_map[ys][xs] && visited_map[ys-1][xs] != 1 )
            {
                dist_map[ys-1][xs] = speedmap[ys-1][xs]+dist_map[ys][xs];
                origin_map[ys-1][xs] = indices_to_index(ys,xs,dim);
            }  
        }

        visited_map[ys][xs] = 1;
        update_distmap(dim[0],dim[1],dist_map,visited_map);

        int *next_coords = index_to_indices(find_argmin(dim[0],dim[1],dist_map,dim),dim);
        xs = next_coords[1];
        ys = next_coords[0];
        free(next_coords);
        
        if ( ys == ye && xs == xe)
        {
            finished = 1;
        }
        count ++;   
    }
    printf("done\n");
    int *path = init_array(count,-1);
    
    int i = 0;
    int time = dist_map[ys][xs];
    while (xs != x || ys != y)
    {
        int *next_coords = index_to_indices(origin_map[ys][xs],dim);
        path[i] = origin_map[ys][xs];
        xs = next_coords[1];
        ys = next_coords[0];
        free(next_coords);
        i++;
    }
    path[i] = time;
    i++;
    path[i] = -1;
    path = inverse_path(count,path);
    
    printf("finish dijkstra\n");
    
    return path;
}

int find_spot(int* dim,int **map, int x, int y,int spot){

    int queue[dim[0]*dim[1]];
    init_array1d(dim[0]*dim[1],queue,-1);

    int visited_map[dim[0]][dim[1]];
    init_array2d(dim[0], dim[1],visited_map,0);

    int first = 0;
    int last = 0;

    queue[last] = indices_to_index(y,x,dim);
    last++;
    int xs;
    int ys;
    while (queue[first] != -1 && first < dim[0]*dim[1])
    {
        int *next_coords = index_to_indices(queue[first],dim);
        xs = next_coords[1];
        ys = next_coords[0];
        visited_map[ys][xs] = 1;
        free(next_coords);

        if ( map[ys][xs] == spot)
        {
            printf("done\n");
            int index = indices_to_index(ys,xs,dim);
            return index;
        }

        if (xs < dim[1]-1)
        {
            if (visited_map[ys][xs+1] != 1)
            {
                queue[last] = indices_to_index(ys,xs+1,dim);
                visited_map[ys][xs+1] = 1;
                last++;
            }  
        }

        if (xs > 0)
        {
            if (visited_map[ys][xs-1] != 1 )
            {
                queue[last] = indices_to_index(ys,xs-1,dim);
                visited_map[ys][xs-1] = 1;
                last++;
            }  
        }

        if (ys < dim[0]-1)
        {
             
            if (visited_map[ys+1][xs] != 1 )
            {
                queue[last] = indices_to_index(ys+1,xs,dim);
                visited_map[ys+1][xs] = 1;
                last++;
            }  
        }

        if (ys > 0)
        {
            if (visited_map[ys-1][xs] != 1 )
            {
                queue[last] = indices_to_index(ys-1,xs,dim);
                visited_map[ys-1][xs] = 1;
                last++;
            }  
        }
        
        first++;
    }

    return -1;
}