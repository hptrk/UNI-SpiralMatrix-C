#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAX_DIMENSION 20

bool matrixExists(int dimension){
    // Ha még nincs mátrix
    if (dimension >= 1 && dimension <= MAX_DIMENSION) return true;

    printf("You don't have a matrix yet.");
    return false;
}

//--------------------
// Program menü
//--------------------

char printMenuGetChoice(){
    printf("--------------------------------------\n");
    printf("#  WELCOME TO SPIRAL MATRIX PROGRAM  #\n");
    printf("--------------------------------------\n");
    printf("#        0 - User Guide              #\n");
    printf("#        1 - Generate a Matrix       #\n");
    printf("#        2 - Save a Matrix           #\n");
    printf("#        3 - Load a Matrix           #\n");
    printf("#        4 - Print Actual Matrix     #\n");
    printf("#        5 - Exit                    #\n");
    printf("--------------------------------------\n");
    printf("     Please enter your choice: ");

    char choice;
    scanf(" %c", &choice);
    return choice;
}

//--------------------
// Felhasználói kézikönyv
//--------------------

// TODO:
void printUserGuide(){
    printf("--------------------------------------\n");
    printf("#       You can generate, save,      #\n");
    printf("#       and load counter             #\n");
    printf("#       clockwise spiral matrixes    #\n");
    printf("#       with dimensions of 1-20      #\n");
    printf("#                                    #\n");
    printf("#       clockwise matrixes:          #\n");
    printf("#       work in progress             #\n");
    printf("--------------------------------------\n");
}

//--------------------
// Mátrix generálás
//--------------------

void getInputsForMatrix(int *dimension, char *direction, char *rotation ){
// DIMENZIÓ
    do {
     printf("     Specify matrix dimension (1-20): ");
     scanf("%d", dimension); // a dimension már egy pointer
    } while(*dimension < 1 || *dimension > MAX_DIMENSION);

// IRÁNY
    do {
     printf("     Specify spiral direction (left,right,up,down): ");
     scanf("%s", direction);
    } while(strcmp(direction, "left") != 0 &&
            strcmp(direction, "right") != 0 && 
            strcmp (direction, "up") != 0 && 
            strcmp(direction, "down") != 0);

// FORGÁS
    do {
     printf("     Specify spiral rotation (cw,ccw): ");
     scanf("%s", rotation);
     if (strcmp(rotation, "cw") == 0) printf("Apologies, but the development of clockwise matrixes is currently underway.\n");
    } while(strcmp(rotation, "ccw") != 0);
}

// Segédfüggvény, feltölti az adott sort/oszlopot az adott irányba
void fill(char dir, int matrix[MAX_DIMENSION][MAX_DIMENSION], int *startCol, int *startRow, int *endCol, int *endRow, int *num){
    // Right
    if(dir=='r'){
        for (int i = *startCol; i <= *endCol; i++) {
            matrix[*startRow][i] = *num;
            (*num)--;
        }
        (*startRow)++;
    }
    // Down
    if(dir=='d'){
        for (int i = *startRow; i <= *endRow; i++) {
            matrix[i][*endCol] = *num;
            (*num)--;
        }
        (*endCol)--;
    }
    // Left
    if(dir=='l'){
            for (int i = *endCol; i >= *startCol; i--) {
                matrix[*endRow][i] = *num;
                (*num)--;
            }
            (*endRow)--;
    }
    // Up
    if(dir=='u'){
             for (int i = *endRow; i >= *startRow; i--) {
                matrix[i][*startCol] = *num;
                (*num)--;
            }
            (*startCol)++;
    }
}

void generateMatrix(int matrix[MAX_DIMENSION][MAX_DIMENSION], int dimension, char *directionInput, char *rotation){
    int num = dimension * dimension;
    int startRow = 0;
    int endRow = dimension - 1;
    int startCol = 0;
    int endCol = dimension - 1;

    // LEFT, CCW
    if (strcmp(directionInput, "left")==0 && strcmp(rotation, "ccw")==0){
        while (startRow <= endRow && startCol <= endCol) {
            fill('r', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('d', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('l', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('u', matrix, &startCol, &startRow, &endCol, &endRow, &num);
        }
    }
    // UP, CCW
    if (strcmp(directionInput, "up")==0 && strcmp(rotation, "ccw")==0){
        while (startRow <= endRow && startCol <= endCol) {
            fill('d', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('l', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('u', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('r', matrix, &startCol, &startRow, &endCol, &endRow, &num);
        }
    }
    // RIGHT, CCW
    if (strcmp(directionInput, "right")==0 && strcmp(rotation, "ccw")==0){
        while (startRow <= endRow && startCol <= endCol) {
            fill('l', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('u', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('r', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('d', matrix, &startCol, &startRow, &endCol, &endRow, &num);
        }
    }
    // DOWN, CCW
    if (strcmp(directionInput, "down")==0 && strcmp(rotation, "ccw")==0){
        while (startRow <= endRow && startCol <= endCol) {
            fill('u', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('r', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('d', matrix, &startCol, &startRow, &endCol, &endRow, &num);
            fill('l', matrix, &startCol, &startRow, &endCol, &endRow, &num);
        }
    }
    printf("Your matrix has been generated successfully!\n");
}

//--------------------
// Mátrix megjelenítése a terminálon
//--------------------

void printActualMatrix(int (*matrix)[MAX_DIMENSION], int dimension){
    // Ha még nincs mátrix, return
    if (!matrixExists(dimension)) return;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // Egyjegyű
            if(matrix[i][j] < 10) printf("   %d", matrix[i][j]);
             // Kétjegyű
            if(matrix[i][j] < 100 && matrix[i][j] > 9) printf("  %d", matrix[i][j]);
             // Háromjegyű
            if(matrix[i][j] > 99) printf(" %d", matrix[i][j]);
        }
        printf("\n");
    }
}

//--------------------
// Mátrix fájlba mentése
//--------------------

void saveMatrixToFile(int (*matrix)[MAX_DIMENSION], int dimension, char *direction, char *rotation){
    // Ha még nincs mátrix, return
    if (!matrixExists(dimension)) return;
    // Ha van dimensionje de nincs rotationje, azt jelenti hogy a felhasználó loadolt mátrixot akar lementeni
    if (*rotation != 'c') {printf("You can't save loaded matrix. Generate one!");return;}

    char filename[30];
    // Fájlnév példa: spiral20rightccw.txt
    snprintf(filename, sizeof(filename), "spiral%d%s%s.txt", dimension, direction, rotation);

    FILE *file = fopen(filename, "w");

    // Ha nem tudja megnyitni a fájlt amibe ír, return
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Mátrix kiírása a fájlba
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    printf("Matrix saved to %s\n", filename);
}

//--------------------
// Mátrix betöltése fájlból
//--------------------

void loadMatrixFromFile(int matrix[MAX_DIMENSION][MAX_DIMENSION], int *dimension, char *rotation){
    char filename[30];

    printf("Enter the filename to load the matrix from: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    // Ha nem tudja megnyitni a fájlt amibe ír, return
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    // Ha loadolt a mátrix, a rotation legyen NULL, hogy később ne lehessen lementeni
    rotation = NULL; 

    // Dimenzió számolása
    int numbers = 0;
    int result;

    while (fscanf(file, "%d", &result) != EOF){
     numbers++; // elemek megszámolása
    }
    *dimension = sqrt(numbers); 

    // fájl elejére rakja a mutatót, hogy újra tudjon az elejéről olvasni
    fseek(file, 0, SEEK_SET); 

    // Aktuális mátrixba elmentés
    for (int i = 0; i < *dimension; i++) {
        for (int j = 0; j < *dimension; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) == EOF) {
                fclose(file);
                return;
            }
        }
    }
    printf("Matrix loaded successfully!");
    fclose(file);
}


int main(){
    int actualMatrix[MAX_DIMENSION][MAX_DIMENSION];
    int dimension;
    char direction[6];
    char rotation[4];

    char choice;
    do {
        printf("\n\n\n");
        choice = printMenuGetChoice();

        // feladat futtató
        switch (choice) {
                case '0':
                    printUserGuide();
                    break;
                case '1':
                    getInputsForMatrix(&dimension, direction, rotation);
                    generateMatrix(actualMatrix, dimension, direction, rotation);
                    break;
                case '2':
                    saveMatrixToFile(actualMatrix, dimension, direction, rotation);
                    break;
                case '3':
                    loadMatrixFromFile(actualMatrix, &dimension, rotation);
                    break;
                case '4':
                    printActualMatrix(actualMatrix, dimension);
                    break;
                case '5':
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            } 

    } while (choice != '5');

    return 0;
}