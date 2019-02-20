#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define TAM 1024

int modM(int i, int n);
int modP(int i, int n);

int main(int argc, char *argv[]) {
    /*ERROR CONTROL FOR INITIAL ARGUMENTS*/
    if(argc!=4) {
        printf("Wrong number of arguments.\n"); 
        exit(1);
    }
    
    /*Declaration of Variables*/
    FILE *f1;/*ficher.txt generation matrix*/
    FILE *f2;/*soluciones.txt solution of the matrix GameOfLife*/
    
    int t = -1;     /*Iterations*/
    int n = -1;     /*Matrix Size*/            
    int i, j, z;          /*Counter*/
    char aux[TAM] = "";       /*Auxiliary Value*/
    char aux2[TAM] = "";      /*Auxiliary Value 2*/
    char *aux3;      /*Auxiliary Value 3*/
    char **matrix;  /*Matrix created from F1*/
    char **solutionMatrix;  /*Matrix after transformation*/

    
    /*Initializing Files*/
    f1 = fopen(argv[2], "r"); /*Matrix File*/
    f2 = fopen(argv[3], "r"); /*Solutions File*/
    
    /*Error Control*/
    if(f1 == NULL){
        printf("F1 corrupted\n");
        exit(-1);
    }
    if(f2 == NULL){
        printf("F2 corrupted\n");
        exit(-1);
    }
    
    /*Saving the entrance iteration value*/
    t = atoi(argv[1]);
    
    /*Error Control*/
    if(t == -1){
        printf("T failed\n");
        exit(-1);
    }
    
    /*Reading the matrix Size n*/
    fgets(aux, TAM, f1);
    n = atoi(aux);
    
    /*Error control*/
    if(n == -1){
        printf("N failed\n");
        exit(-1);
    }
    
    /*Raserving Memory for the Original Matrix*/
    matrix = (char **)malloc(n*sizeof(char *));       /*For the ROWS*/
    for (i = 0; i < n; i++){
        matrix[i] = (char *)malloc(n*sizeof(char));  /*For the COLOMS*/
    }
    /*Error Control*/
    if(matrix == NULL){  
        printf("Out of memory for the matrix\n");  
        exit(-1);  
    }
    
    /*Raserving Memory for the Solution Matrix*/
    solutionMatrix = (char **)malloc(n*sizeof(char *));       /*For the ROWS*/
    for (i = 0; i < n; i++){
        solutionMatrix[i] = (char *)malloc(n*sizeof(char));  /*For the COLOMS*/
    }
    /*Error Control*/
    if(solutionMatrix == NULL){  
        printf("Out of memory for the solutionMatrix\n");  
        exit(-1);  
    }
    
    /*Initializing matrix values*/
    for(i = 0; i < n; i++){
        fgets(aux, TAM, f1);
        for(j = 0; j < n; j++){
            matrix[i][j] = aux[j];
        }
    }
    
    /*PRINTING MATRIX CONTROLL*/
    printf("Matrix");
    for(i = 0; i < n; i++){
        printf("\n");
        for(j = 0; j < n; j++){
            printf("[%c]", matrix[i][j]);
        }
    }
    printf("\n");
    
    /*Geting aux empty*//*
    memset(aux, 0, TAM);*/

    for(z = 0; z < t; z++){
        
        printf("\n---\n ROUND %d\n---\n", z+1);
        printf("Solution Matrix\n");
        
        for(i = 0; i < n; i++){
            
            /*Getting the matrix of the neightbours*/
            for(j = 0; j < n; j++){
                aux[0] = matrix[modM(i, n)][modM(j, n)]; 
                aux[1] = matrix[modM(i, n)][j];
                aux[2] = matrix[modM(i, n)][modP(j, n)];
                aux[3] = matrix[i][modM(j, n)];
                aux[4] = matrix[i][j];
                aux[5] = matrix[i][modP(j, n)];
                aux[6] = matrix[modP(i, n)][modM(j, n)];
                aux[7] = matrix[modP(i, n)][j];
                aux[8] = matrix[modP(i, n)][modP(j, n)];
                
                /*Pointing to the start of the file*/
                rewind(f2);
                 /*Reading the solution file until the end*/
                while(feof(f2) == 0){
                    
                    /*Reading Solution File to create solution matrix*/
                    fgets(aux2, TAM, f2);
                
                    /*Control Error*/
                    if(aux2[10] == '\0'){
                        printf("\nERROR COPING THE SOLUTION\n");
                        exit(-1);
                    }
                    
                    /*Dividing the solution value and the string*/
                    aux3 = strtok(aux2, " ");
                    
                    /*Compering strings to get the correct solution in the matrix*/
                    if(strcmp(aux3, aux) == 0){
                        /*printf("aux2: %c\n", aux2[10]);*/
                        solutionMatrix[i][j] = aux2[10];
                        /*printf("    : %c\n", solutionMatrix[i][j]);*/
                    }
                }
                
                /*Coping the solution matrix in the iteration matrix to be able to loop the proces the times asked*/
                matrix[i][j] = solutionMatrix[i][j];
                printf("[%c]", solutionMatrix[i][j]);
            }
            printf("\n");
        }
    }
    
    /*free of memory used*/
    for(i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
    
    for(i = 0; i < n; i++){
        free(solutionMatrix[i]);
    }
    free(solutionMatrix);
    
    fclose(f1);
    fclose(f2);
    
    return 0;
}

/*Function created to get the neightbours indexes*/
int modP(int i, int n){
    i = i+1;
    return i%n;
}

int modM(int i, int n){
    i = i-1;
    i = i%n;
    
    if(i == -1)
        return i+n;
    
    return i;
}