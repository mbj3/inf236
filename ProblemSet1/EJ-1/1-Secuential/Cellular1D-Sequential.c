#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM 1024

main(int argc, char *argv[]) {
    
    if(argc!=2) {
        printf("Wrong number of arguments.\n"); 
        exit(1);
    }
    
    FILE *f1;
    FILE *f2;
    
    char aux[3];
    char sol[TAM];
    /*char sol2[TAM];*/
    char org[TAM];
    char solaux[8][5];
        
    int t = atoi(argv[1]);
    int i = 0;
    int j = 0;
    int z = 0;
    int count = 0;
    int tam = -1;
        
    sol[0] = '\0';
    /*sol2[0] = '\0';*/
    org[0] = '\0';
    aux[0] = '\0';
    solaux[0][0] = '\0';
    
    
    f1 = fopen("fichero.txt", "r");
    if (f1 == NULL)
    	exit(1);
     		
    f2 = fopen("mod2.txt", "r");
    if (f2 == NULL)
    	exit(1);
        
    fgets(org, TAM, f1);
    if(org == NULL){
        printf("Por TONTO\n");
        return -1;
    }
        
    tam = atoi(org); 
    if(tam == -1){
        printf("No tira el tamaño\n");
        return -1;
    }
        
    /*printf("You Have %d Chars\n", tam);*/
    fgets(org, TAM, f1);
        
    fclose(f1);
        
    while(!feof(f2)){
        fgets(solaux[i], TAM, f2);
        i++;
    }
        
    fclose(f2);
        
    /*printf("SOLAUX = %s", solaux[0]);
    printf("ORG = %s\n", org);*/
    
    for(count = 0; count < t; count++){
        for(i = 0; i < tam; i++){
            
            if(i-1 == -1){
                aux[0] = '0';
                aux[1] = org[i];
                aux[2] = org[i+1];
                /*printf("AUX1 = %s\n", aux);*/
            }
            
            else if (i+1 >= tam){
                aux[0] = org[tam-2];
                aux[1] = org[tam-1];
                aux[2] = '0';
                /*printf("AUX2 = %s\n", aux);*/
            }
            
            else{
                aux[0] = org[i-1];
                aux[1] = org[i];
                aux[2] = org[i+1];
                /*printf("AUX3 = %s\n", aux);*/
            }
            
            /*CAMBIO*/
            for(j = 0; j < 8; j++){
                if(aux[0] == solaux[j][0]){
                    if(aux[1] == solaux[j][1]){
                        if(aux[2] == solaux[j][2]){
                            sol[i] = solaux[j][4];
                            /*printf("SOL[i] = %c\n", sol[i]);*/
                            break;
                        }
                    }
                }
            }
        }
        
        printf("SOL = %s\n", sol);
    
        for(z = 0; z < TAM; z++){
            org[z] = sol[z];   
        }
    }
    
    return -1;
}
