#include <math.h>
#include "sudoku.h"
#include "fichero.h"
#include "colores.h"

tsudoku leer_sudoku(){
	int err, f, c, size, car;
	tsudoku sud;
	char nombre_fichero[SIZE_NOMBRE_FICHERO];
	printf("Intro sudoku file name: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK){
		printf("Error: el fichero no existe.\n");
		sud.size=-1;
	} 
	else{
		sud.size = leer_int_fichero();
		sud.ssize = sqrt(sud.size);
		sud.total=sud.size*sud.size;
		sud.libres=sud.total;
		sud.ocu=0;
		leer_char_fichero(); //'n'
		for (f = 0; f < sud.size; f++){
			for (c = 0; c < sud.size; c++){
                                sud.s[f][c].modificable=1;
				sud.s[f][c].valor = leer_char_fichero();
				if(sud.s[f][c].valor!=' '){
					sud.s[f][c].modificable=0;
				 	sud.libres--;
                                  	sud.ocu++;
				}
			}
			leer_char_fichero(); // '\n'
		}
		cerrar_fichero();
	}
	return sud;
}

void linea(int ssize){ // Diseño del sudoku
        int i;
        for (i=0;i<=ssize;i++){
                printf("-+");
        }
        printf("\n");
}

void mostrar_sudoku(tsudoku s){ 
   	int i,j, car;
   	printf_color_negrita();
   	printf(" ");
   	for (i=0;i<s.size;i++){
	       if (i%s.ssize==0){
		   	printf("|");
	       }
	       else{
		   	printf(" ");
	       }
	       car=convertirchar(i);
	       printf("%c", car);
	}
	printf("|\n");
	for (i=0;i<s.size;i++){
		if (i%s.ssize==0){
		   	linea(s.size);
		}
		car=convertirchar(i);
		printf("%c", car); 
		for (j=0;j<s.size;j++){
			if (j%s.ssize==0){
				printf("|");
			}
			else{
				printf(" ");
			}
			if(s.s[i][j].modificable==1){
				printf_reset_color();
				printf("%c", s.s[i][j].valor);
			}
			else{
				printf_color_negrita();
				printf("%c", s.s[i][j].valor);
			}
			printf_color_negrita();
		}
		printf("|\n");
	}
	linea(s.size);
	printf_reset_color();
}

int comprobar_sudoku(tsudoku sud_res)
{
	unsigned i, j, k, l, q, est=0; // est: sudoku correcto (0) o incorrecto (!=0)
  	char vec[sud_res.size];
  	for(i=0; i<sud_res.size; i++){
		for(j=0; j<sud_res.size; j++){
			for(k=j+1; k<sud_res.size; k++){
				if(sud_res.s[i][k].valor==sud_res.s[i][j].valor){ // Revisar las filas
          				est++;
        			}
      			}
      			for(k=i+1; k<sud_res.size; k++){
        			if(sud_res.s[k][j].valor==sud_res.s[i][j].valor){// Revisar las columnas
        				est++;
        			}
      			}	
    		}
  	}
  	if(est==0){ // Si filas y columnas están bien
     		int pos = 0;  // Índice para llenar vector
  		for(i = 0; i < sud_res.size; i = i + sud_res.ssize){   // Filas de cuadrantes
       	 		for(j = 0; j < sud_res.size; j = j + sud_res.ssize){ // Columnas de cuadrantes
	    			pos = 0;
           			for(k = i; k < i + sud_res.ssize; k++){  // Filas dentro del cuadrante
                			for(l = j; l < j + sud_res.ssize; l++){ // Columnas dentro del cuadrante
                    				vec[pos] = sud_res.s[k][l].valor;   // Llenar vector
                    				pos++;
                			}
            			}
            			for(k = 0; k < pos; k++){ // Comprobar en el vector
                			for(l = k + 1; l < pos; l++){
                    				if(vec[k] == vec[l]){
                        				est++;
                    				}
                			}
            			}	
        		}
    		}
  	}	
  	return est;
}

void jugada(tsudoku sud){
	char a, b, c, q; 
        char temp;    // Para limpiar el buffer si es necesario
	int est=1, d, e;

	if(sud.size!=-1){ // Si el usuario se equivoca con el nombre del fichero
	        mostrar_sudoku(sud);
		do{
			if(sud.libres==0){
				est=comprobar_sudoku(sud);
			}
			else{
				printf("\nIntro [fila col car] sin espacios: ");
				scanf("%c%c%c", &a, &b, &c);
				if (a != '\n' || b != '\n' || c != '\n'){
				        scanf("%c", &temp);
				        while (temp != '\n'){
						scanf("%c", &temp); 
				        }
				}
				printf("\n");
				d=convertirint(a);
				e=convertirint(b);
				q=comprobar_car(sud,c);
				if(sud.s[d][e].modificable==1 && q==1){
					if (sud.s[d][e].valor==' '){
						sud.libres--;	
					}
					if (c==' '){
						sud.libres++;
					}
					if((c>64 && c<91) || (c>47 && c<58) || c==32){ // Letra introducida es o mayúsula o espacio
						sud.s[d][e].valor=c;
					}
					else{
						sud.s[d][e].valor=c-'a'+'A';
					}
				}
				mostrar_sudoku(sud);
			}
		}while(est!=0);
		printf("FELICIDADES: Sudoku resuelto! :-)\n\n");
	}
}
