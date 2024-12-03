/*
 * Detection of black regions
A text file contains an array of integers (either 0 or 1) with the following format:
• the first row of the file specifies the real dimensions of the matrix (number of rows nr and
number of columns nc, separated by a space). Assume that both values are at most 50
• each of the subsequent rows reports the nc values corresponding to a row of the matrix,
separated by one or more spaces
• each cell of the matrix can either contain the value 0 (associated with the white color) or
the value 1 (associated with the black color)
• the black cells are organized into homogeneous rectangular regions, where each black
region is either surrounded by a frame of white cells, or by the edge (s) of the matrix. To
this end, you should consider the adjacent cells only along the four main cardinal points
(North, South, West, East) and neglect the diagonals.
Write a C program that:
• reads the matrix from the input file. You can assume that the file does not contain any
format errors (i.e., all the black rectangles respect the given formatting constraints).
• identifies the largest black regions, respectively in terms of (1) height, (2) width and (3)
area. In case of tie, the program should report just one of the identified regions that meet
the corresponding criterion.
• for each of the three regions identified at the previous point, outputs the following
characteristics on the screen: coordinates (row,column) of the upper left corner, height,
width and area.
 * */
#include <stdio.h>

#define fileIn "../input.txt"
#define fileOut "../output.txt"
#define maxNum 50

typedef struct {
    int mat[maxNum][maxNum];
    int numOfRows;
    int numOfCol;
} matrix_t;

typedef struct {
    int area; //Area totale
    int r,c; //coordinate di upperLeft corner
    int altezza, larghezza
} blackBox_t;


FILE *fp_read; FILE *fp_write;
void stampaMatrice(matrix_t matrix);
matrix_t caricoMatrice(void);
void letsgosky(matrix_t matrix);
int isBlack(int cell);
void stampaRisultati(blackBox_t box[], int numBoxes);


int main(void) {
    matrix_t matrix;
    matrix = caricoMatrice();
    stampaMatrice(matrix);
    //Eskere fin qui va.
    letsgosky(matrix);
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

int isBlack(int cell){
    if(cell == 1){
        return 1;
    } else
    {
        return 0;
    }
}

void letsgosky(matrix_t matrix){
    int visitati[maxNum][maxNum] = {0};

     blackBox_t box[50]; //Numero molto alto, ma si spera sia meno
     int numBoxes = 0;
    //intanto, l'unica cosa certa da cui posso partire è che
    //devo iterare su tutti i quadratini
    for(int i = 0; i < matrix.numOfRows; i++){
        //itero sulle righe

        for(int j = 0; j<matrix.numOfCol; j++){
            //itero sulle colonne

            if(isBlack(matrix.mat[i][j])&&!visitati[i][j]){
                //Qui mi trovo nella cella [i][j], la quale è nera. Mi approccio da sx a dx, top to bottom.
                //Non è mai stata visitata, quindi è un upperLeft corner

                visitati[i][j] = 1;
                box[numBoxes].c = j; box[numBoxes].r = i; //quindi prendo subito le coordinate di upper left corner
                int k = 1, h = 1;
                box[numBoxes].area++;
                box[numBoxes].larghezza++;
                box[numBoxes].altezza++;

                //controllo i vicini
                while(isBlack(matrix.mat[j][i+k])&&(i+k < matrix.numOfRows)){
                    box[numBoxes].larghezza++;
                    visitati[j][i+k] = 1;//quindi non controllerò più questa cella
                    box[numBoxes].area++;
                    k++; //in modo che all'interazione successiva io controllo il vicino a dx. In caso, il ciclo più esterno salta le nere già controllate

                    while (isBlack(matrix.mat[j+h][i])&&(j+h < matrix.numOfCol)){
                        box[numBoxes].altezza++;
                        visitati[j+h][i] = 1;
                        h++;
                        box[numBoxes].area++;
                    }
                };
                //FOR DEBUG PURPOSES ONLY
                printf("%d\n", numBoxes);
                numBoxes++;
            }

        }

    }
    //Stampare risultati
    stampaRisultati(box, numBoxes);
}

void stampaRisultati(blackBox_t *box, int numBoxes){
    int max = 0, pos;
    //Cerchiamo l'area maggiore
    for(int i = 0; i<numBoxes; i++){
        if(box[i].area>max){
            max = box[i].area;
            pos = i;
        }
    }
    printf("L'area maggiore è di: %d, del rettangolo c: %d, r: %d\n", box[pos].area, box[pos].c+1, box[pos].r+1);

    //CERCO MASSIMA ALTEZZA
    max = 0;
    for(int i = 0; i<numBoxes; i++){
        if(box[i].altezza>max){
            max = box[i].altezza;
            pos = i;
        }
    }
    printf("L'altezza maggiore è di: %d, del rettangolo c: %d, r: %d", box[pos].altezza, box[pos].c+1, box[pos].r+1);

}