#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "tt.h"

GRID* create_grid(int n){
    NODE* arr[n][n];
    NODE* top = (NODE*)malloc(sizeof(NODE));
    top->data = -1;
    top->left = NULL;
    top->right = NULL;
    arr[0][0] = top;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!i&&!j) continue;
            NODE* temp = (NODE*)malloc(sizeof(NODE));
            temp->data = -1;
            arr[i][j] = temp;

        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            !i?arr[i][j]->up=NULL:(arr[i][j]->up = arr[i-1][j]);
            !j?arr[i][j]->left=NULL:(arr[i][j]->left = arr[i][j-1]);
            (i==n-1)?arr[i][j]->down=NULL:(arr[i][j]->down = arr[i+1][j]);
            (j==n-1)?arr[i][j]->right=NULL:(arr[i][j]->right = arr[i][j+1]);
        }
    }
    GRID* grid = (GRID*)malloc(sizeof(GRID));
    grid->top = top;
    grid->size = n;
    grid->filled = 0;
    return grid;
}

void display_grid(GRID* grid){
    NODE* tr;
    NODE* row = grid->top;
    for(int i=0; i<grid->size; i++){
        tr = row;
        printf("|");
        for(int j=0; j<grid->size; j++){
            
            if(tr->data == 0) printf("X ");
            else if(tr->data == 1) printf("O ");
            else printf("  ");
            printf("|");
            tr = tr->right;
        }
        
        printf("\n");
        printf("|--|--|--|\n");
        row = row->down;
    }
}

void help(){
    printf("inside help\n");
}

int processInput(GRID* gr, VEC2* inp, int turn ){
    NODE* temp = gr->top;
    int fail = 0;
    printf("%d %d\n", inp->x, inp->y);
    for(int i=0; i< inp->x; i++){
        if(temp) temp = temp->right;
        else{
            fail = 1;
            break;
        }
    }
    for(int i=0; i< inp->y; i++){
        if(temp) temp = temp->down;
        else{
            fail = 1;
            break;
        }
    }
    if(fail) return 0;
    else{
        if(temp->data!=-1){
            return 0;
        }
        else temp->data = turn;
    }
    return 1;
}

int main(){
    int winner = -1;
    int turn = 0;
    int change = 1;
    VEC2 inp;
    char inpS[50];
    printf("Welcome to TicTacToe\n");
    GRID* gr = create_grid(3);
    display_grid(gr);
    while(winner == -1 && gr->filled!=(gr->size*gr->size)){
        turn?(printf("Player 2 Turn\n")):(printf("Player 1 Turn\n"));
        change?(turn = !turn):(turn=turn);
        printf(">> ");
        gets(inpS);
        fflush(stdin);
        //printf("%s", inpS);

        for(int i=0; inpS[i]; i++){
            inpS[i] = tolower(inpS[i]);
        }
        if(!strcmp(inpS, "help")){
            help();
            continue;
        } 
        else{
            inp.x = atoi(strtok(inpS, " \0"));
            inp.y = atoi(strtok(NULL, " \0"));  
        }
        //printf("%d %d\n", inp.x, inp.y);
        inp.x--;
        inp.y--;
        change = processInput(gr, &inp, !turn);
        display_grid(gr);
    }
    return 0;
}
