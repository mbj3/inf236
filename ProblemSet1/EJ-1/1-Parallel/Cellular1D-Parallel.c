#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mpi.h>
#include <time.h>
#include <assert.h>

#define TAM 1024

main(int argc, char *argv[]) {
    
    if(argc!=4) {
        printf("Wrong number of arguments.\n"); 
        exit(1);
    }
    
    /*********/
    FILE *f1;
    FILE *f2;
    
    clock_t start,end;
    int nP = -1; /*Number of Process*/
    int rank = -1; /*Rank of Processes*/
    int it = -1; /*Iterations*/
    int tam = -1; /*Size of the file*/
    int i, j, z, y, w; /*Counters*/
    char*particion;
    char solaux[8][5]; /*Array with all the solutions for the parcial vectors*/
    char derecha, izquierda;
    char parte[4]={};
        parte[3]='\0';
    MPI_Init (NULL , NULL);

    MPI_Comm_size(MPI_COMM_WORLD , &nP);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    
    MPI_Status status;
    MPI_Request request;
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
    
    iterations = argv[1];
    if(iterations == -1){
        printf("Iterations Failed\n");
        exit(-1);
    }
    
    /*Reading the size of the string to read*/
    fgets(tamanio, TAM, f1);
    if(tamanio == NULL){
        printf("Por TONTO\n");
        return -1;
    }
        
    tam = atoi(tamanio);
    if(tam == -1){
        printf("Tam Failed\n");
        exit(-1);
    }
    
    
    
    /*Reading all the solutions*/
    while(!feof(f2)){
        fgets(solaux[i], TAM, f2);
        i++;
    }
    fclose(f2);
    
    /*BRODCAST SOLUTIONS*/
    MPI_Bcast(solaux[0], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[1], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[2], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[3], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[4], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[5], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[6], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(solaux[7], 5, MPI_CHAR, 0, MPI_COMM_WORLD);
        
        start = clock();
    /*BRODCAST SIZE & ITERATIONS*/
    MPI_Bcast(&tam,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&it,1,MPI_INT,0,MPI_COMM_WORLD);

/*    MPI_Bcast(&all_bools,8,MPI_CHAR,0,MPI_COMM_WORLD);    */
    
    char* tamXproc=malloc((sizeof(char)*tam/nP));
    
    MPI_Scatter(particion,tam/nP,MPI_CHAR, ,tam/nP,tamXproc ,MPI_CHAR,0,MPI_COMM_WORLD);
    
    char* resultadoString=malloc(sizeof(char)*(n+1));
    resultadoString[n]='\0';
    char* nuevoString=malloc(sizeof(char)*(n/comm_sz));

    for (int i=0;i<t;i++) {
        //send last element to next process
        MPI_Isend(&tamXproc[(tam / nP) - 1], 1, MPI_CHAR, mod(rank + 1, nP), 37, MPI_COMM_WORLD, &request);
        //send first element to previous process
        MPI_Isend(&tamXproc[0], 1, MPI_CHAR, mod(rank - 1, nP), 38, MPI_COMM_WORLD, &request);
        //receive from previous process
        MPI_Recv(&izquierda, 1, MPI_CHAR, mod(rank - 1, nP), 37, MPI_COMM_WORLD, &status);
        //receive from next process
        MPI_Recv(&derecha, 1, MPI_CHAR, mod(rank + 1, nP), 38, MPI_COMM_WORLD, &status);
    /*********/
    //create the bit-string we want to find in the rules array
        for (int j = 0; j < tam / nP; j++) {
            if (j == 0) {
                parte[0] = left;
                parte[1] = tamXproc[j];
                parte[2] = tamXproc[j + 1];
            }else if (j == (tam / nP - 1)) {
                parte[2] = derecha;
                parte[1] = tamXproc[j];
                parte[0] = tamXproc[j - 1];
            } else {
                parte[0] = tamXproc[j - 1];
                parte[1] = tamXproc[j];
                parte[2] = tamXproc[j + 1];
            }

     //reassign string
        int len = strlen(tamXproc);
        for (int j = 0; j < len; j++) {
            tamXproc[j] = nuevoString[j];
        }

        //gather to the resultString
        MPI_Gather(tamXproc, tam/nP,MPI_CHAR,resultadoString,tam/nP,MPI_CHAR,0,MPI_COMM_WORLD);

        end = clock();
        //print the result
       if(rank==0){
           printf("%s\n", resultadoString);
       }
    }
    double tiempo = (double)(end-start)/ CLOCKS_PER_SEC;

    MPI_Finalize ();
    return  0;
}
    
int mod(int x, int y){
    return(x%m+m)%m;)
    
}