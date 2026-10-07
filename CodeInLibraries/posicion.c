#include "posicion.h"

char convertirchar(int i) {
	char c;
        if (i<10){
             	c=i+'0';
        }
        else{
             	i=i+87;
             	c=i;
        }
        return c;
}

int convertirint(char i){
        int c;
        if(i>47 && i<58){ // Char es un número
         	c=i-'0';
        }
        else if(i>96 && i<123){ // Char letra minúscula
         	c=i-'a'+10;
        }
        else if(i>64 && i<91){// Char letra mayúscula
         	c=i-'A'+10;
        }
        else{
       	        c=-1;
        }
        return c;
}

int comprobar_car(tsudoku sud, char c) {
  	int g, p;
		g=convertirint(c);
		if((g>=0 || c==32) && (sud.size<10 && (g!=0 && g<=sud.size)  || (sud.size>10 && g<sud.size))){ // Si el sudoku admite 0
		 	p=1;
		}
		else{
			p=0;
		}
  	return p;
}
