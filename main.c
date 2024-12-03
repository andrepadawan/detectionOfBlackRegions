#include <stdio.h>

#define fileIn "../input.txt"
#define fileOut "../output.txt"
#define maxNum 50

typedef struct {
    int mat[maxNum][maxNum];
    int numOfRows;
    int numOfCol;
} matrix_t;


FILE *fp_read; FILE *fp_write;
void stampaMatrice(matrix_t matrix);
matrix_t caricoMatrice(void);


int main(void) {
    matrix_t matrix;
    matrix = caricoMatrice();
    stampaMatrice(matrix);
    //Eskere fin qui va.
    return 0;
}


void stampaMatrice(matrix_t matrix){
    for(int i = 0; i<matrix.numOfRows; i++){
        for(int j = 0; j<matrix.numOfCol; j++){
            printf("%d ", matrix.mat[i][j]);
        }
        printf("\n");
    }
}
matrix_t caricoMatrice(void){
    fp_read = fopen(fileIn, "r");
    matrix_t temp;
    if(fp_read == NULL){
        printf("Errore nella lettura file di input: %s", fileIn);
    }

    //leggo le misure della tabella: le info sono alla prima riga
    fscanf(fp_read, "%d %d", &temp.numOfRows, &temp.numOfCol);
    //printf("%d %d", nr,nc);

    //Quindi creo la mia matrice e copio il file dentro
    for(int i = 0; i<temp.numOfRows; i++){
        for(int j = 0; j<temp.numOfCol; j++){
            int tempInt;
            fscanf(fp_read, "%d", &tempInt);
            temp.mat[i][j] = tempInt;
        }
    }
    return temp;
}