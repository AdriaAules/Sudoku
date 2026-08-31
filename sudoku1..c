#include <stdio.h>
#include "fichero.h"
#include <math.h>
#include "colores.h"

#define SIZE_NOMBRE_FICHERO	  80
#define DIM 36

typedef struct{
  char valor;
  int modificable; //0 no se modifica, 1 se modifica
}tcasilla;

typedef struct{
	tcasilla s[DIM][DIM];
	int size;
	int ssize;
	int ocu;
	int libres;
	int total;
}tsudoku;


//funciones de posición
char convertirchar(int i);
int comprobar_car(tsudoku sud, char c);

//funciones de sudoku
tsudoku leer_sudoku();
void mostrar_sudoku(tsudoku s);
void linea(int ssize);
int comprobar_sudoku(tsudoku sud_res);
void jugada(tsudoku sud);

int main(){
	tsudoku sud;   
	sud=leer_sudoku();
	jugada(sud);
    
	
}
tsudoku leer_sudoku(){
	int err, f, c, size, car;
	tsudoku sud;
	char nombre_fichero[SIZE_NOMBRE_FICHERO];

	printf("Intro sudoku file name: ");
	scanf("%s%*c", nombre_fichero);
	err = abrir_fichero(nombre_fichero);
	if (err != ABRIR_FICHERO_OK) {
		printf("Error: el fichero no existe.\n");
		sud.size=-1;
	} 
	else {
		
		sud.size = leer_int_fichero();
		sud.ssize = sqrt(sud.size);
		sud.total=sud.size*sud.size;
		sud.libres=sud.total;
		sud.ocu=0;
		leer_char_fichero();
		
		for (f = 0; f < sud.size; f++) {
			for (c = 0; c < sud.size; c++) {
                                sud.s[f][c].modificable=1;
				sud.s[f][c].valor = leer_char_fichero();
				if(sud.s[f][c].valor!=' ')
				{
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

char convertirchar(int i) {
        char c;
        if (i<10) {
             	c=i+'0'; //si va de 0-9, transforma a un char del mateix nombre
        }
        else {
             	i=i+87; //si es major que 9, passa a un char, començant per a
             	c=i;
        }
        return c;
}

int convertirint(char i){
        int c;
        if(i>47 && i<58){ //char número
         	c=i-'0';
        }
        else if(i>96 && i<123){ // char letra minúscula previamente comprovado
         	c=i-'a'+10;
        }
        else if(i>64 && i<91){//char letra mayúscula
         	c=i-'A'+10;
        }
        else{
       	        c=-1;
        }
        return c;
}

void linea(int ssize) {
        int i;
        //fila numero dos
        for (i=0;i<=ssize;i++) {
                printf("-+");
        }
        printf("\n");
}
  

void mostrar_sudoku(tsudoku s) {
   int i,j, car;
   //fila numero uno
   printf_color_negrita();
   printf(" ");
   for (i=0;i<s.size;i++) {
       if (i%s.ssize==0) {
           printf("|");
       }
       else{
           printf(" ");
       }
       car=convertirchar(i);
       printf("%c", car);
   }
   printf("|\n");


   //fileres
   for (i=0;i<s.size;i++) {
       if (i%s.ssize==0) {
           linea(s.size);
       }
       car=convertirchar(i);
       printf("%c", car); 
       
       for (j=0;j<s.size;j++) {
           if (j%s.ssize==0) {
               printf("|");
           }
           else {
               printf(" ");
           }
           if(s.s[i][j].modificable==1)
           {
             printf_reset_color();
             printf("%c", s.s[i][j].valor);
           }
           else
           {
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

int comprobar_car(tsudoku sud, char c)
{
	  int g, p;
	  
		g=convertirint(c);
		if((g>=0 || c==32) && (sud.size<10 && (g!=0 && g<=sud.size)  || (sud.size>10 && g<sud.size))){ //fila y columna introducida coherente con size y si el sudoku admite 0
		 	p=1;
		}
		else{
			p=0;
		}
		
	  return p;
}

int comprobar_sudoku(tsudoku sud_res)
{
  unsigned i, j, k, l, q, est=0; //n: nombre de vegades repetit; est: sudoku correcte (0) o incorrecte (!=0)
  char vec[sud_res.size];
  for(i=0; i<sud_res.size; i++){
    for(j=0; j<sud_res.size; j++){
      for(k=j+1; k<sud_res.size; k++){
        if(sud_res.s[i][k].valor==sud_res.s[i][j].valor){ //revisar les files
          	est++;
        }
      }
      for(k=i+1; k<sud_res.size; k++){
        if(sud_res.s[k][j].valor==sud_res.s[i][j].valor){//revisar les columnes
        	est++;
        }
      }
    }
  }
  //comprobar cuadrantes
  if(est==0){
     int pos = 0;  // índice para llenar vector
  	for(i = 0; i < sud_res.size; i = i + sud_res.ssize){   // filas de cuadrantes
       	 for(j = 0; j < sud_res.size; j = j + sud_res.ssize){ // columnas de cuadrantes
	    pos = 0;
            for(k = i; k < i + sud_res.ssize; k++){  // filas dentro del cuadrante
                for(l = j; l < j + sud_res.ssize; l++){ // columnas dentro del cuadrante
                    vec[pos] = sud_res.s[k][l].valor;   // llenar vector
                    pos++;
                }
            }
            // revisar los valores del vector
            for(k = 0; k < pos; k++){
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
	char a, b, c, d, e, q; //sudoku enunciat i sudoku resposta
        char temp;    // Variable temporal per netejar el buffer si cal
	int est=1;

	if(sud.size!=-1){ //per si l'usuari s'equivoca escrivint el fichero
	        mostrar_sudoku(sud);
	        do{
			printf("\nIntro [fila col car] sin espacios: ");
			scanf("%c%c%c", &a, &b, &c);
                if (a != '\n' || b != '\n' || c != '\n'){
                        scanf("%c", &temp);
                        while (temp != '\n') {
                                scanf("%c", &temp); 
                        }
                }
			printf("\n");
			d=convertirint(a);
			e=convertirint(b);
			q=comprobar_car(sud,c);
			if(sud.s[d][e].modificable==1 && q==1){ //comprovar que el caràcter introduït és correcte i substituir-los
				if (sud.s[d][e].valor==' '){
					sud.libres--;	
				} // si la coorenada esta buida resta 1 al su.libres, sino no
				if (c==' '){
					sud.libres++;
				}
				if((c>64 && c<91) || (c>47 && c<58) || c==32) //o majúscula o número o espai
				{
				  sud.s[d][e].valor=c;
				}
				else
				{
				  sud.s[d][e].valor=c-'a'+'A';
				}
				
			}
			mostrar_sudoku(sud);//mostrar el nou sudoku
			if(sud.libres==0){
				est=comprobar_sudoku(sud);
			}
		}while(est!=0); //sudoku incorrecto
		printf("FELICIDADES: Sudoku resuelto! :-)\n\n");
	}
	//comprovar que els valors del sudoku són correctes
}
