#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>

#define SIZE_NOMBRE_FICHERO 80
#define DIM 36

typedef struct{
  char valor;
  int modificable; // 0 no se modifica, 1 se modifica
}tcasilla;

typedef struct{
	tcasilla s[DIM][DIM];
	int size;
	int ssize;
	int ocu;
	int libres;
	int total;
}tsudoku;

// Funciones Sudoku
tsudoku leer_sudoku();
void mostrar_sudoku(tsudoku s);
void linea(int ssize);
int comprobar_sudoku(tsudoku sud_res);
void jugada(tsudoku sud);

// Funciones de posición
char convertirchar(int i);
int convertirint(char i);
int comprobar_car(tsudoku sud, char c);

#endif
