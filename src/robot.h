Robot* init_robot(int capa_max,int x,int y,int Vf,int Vm,int Vc);
void deplacer(Robot *robot,int xe,int ye,int **map);
void remplir(Robot *robot);
void info_robot(Robot *robot);
int get_number_robots(FILE *fichier);
void init_robots(FILE *fichier, int dim,Robot *robots[dim]);
