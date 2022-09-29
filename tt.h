typedef struct node{
    int data;
    struct node *up;
    struct node *right;
    struct node *down;
    struct node *left; 
}NODE;

typedef struct grid{
    struct node* top;
    int size;
    int filled;
}GRID;

typedef struct vec2{
    int x;
    int y;
}VEC2;

GRID* create_grid(int n);
void display_grid(GRID* gr);
int processInput(GRID* gr, VEC2* inp, int turn);

