#include <iostream>
#include "sudoku.h"

using namespace std;



bool indiceValido (int i){
		return (0 <= i && i < 9);
}
bool posicionValida (int f, int c){
		return (indiceValido(f) && indiceValido(c));

}

bool sudoku_esCeldaVacia(Tablero t, int f, int c) {
	return (t[f][c] == 0);
}

void sudoku_vaciarTablero(Tablero t) {
	int f =0;
	int c;
	while(f<9){
		c = 0;
		while(c<9){
			if(!sudoku_esCeldaVacia(t,f,c)) {
				t[f][c] = 0;
			}
			c++;
		}
		f++;
	}
}

int sudoku_nroDeCeldasVacias(Tablero t) {
	int celdasVacias = 0;
	int f = 0;
	int c;
	while(f < 9) {
		c = 0;
		while(c < 9){
			if(sudoku_esCeldaVacia(t,f,c)){
				celdasVacias++;
			}
			c++;
		}
		f++;
	}
	return celdasVacias;
}

int sudoku_primerCeldaVaciaFila(Tablero t) {
    int result = -1;
    if (sudoku_nroDeCeldasVacias(t) != 0) {
        int f = 0;
        while (indiceValido(f) && result == -1) {
            if (esFilaDePrimeraCeldaVacia(t,f)) {
                result = f;
            }
            f++;
        }

       }
    return result;
}

int sudoku_primerCeldaVaciaColumna(Tablero t) {
    int result = -1;
    if (sudoku_nroDeCeldasVacias(t) != 0) {
        int c = 0;
        while (indiceValido(c) && result == -1) {
            if (esColumnaDePrimeraCeldaVacia(t,c)) {
                result = c;
            }
            c++;
        }

     }
    return result;
}

int sudoku_valorEnCelda(Tablero t, int f, int c) {
	return t[f][c];
}

void sudoku_llenarCelda(Tablero t, int f, int c, int v) {
    t[f][c] = v;
}

void sudoku_vaciarCelda(Tablero t, int f, int c) {
      t[f][c] = 0;
}

bool sudoku_esTableroValido(Tablero t) {
	return posicionesValidas(t);
}

bool sudoku_esTableroParcialmenteResuelto(Tablero t) {
	return (sudoku_esTableroValido(t) && filasOk(t) && columnasOk(t) && regionesOk(t));
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	return (sudoku_nroDeCeldasVacias(t) == 0 && sudoku_esTableroParcialmenteResuelto(t));
}

bool sudoku_esSubTablero(Tablero t0, Tablero t1) {
	bool res = true;
	for(int f = 0; f < 9; f++){
		for(int c = 0; c < 9; c++){
			if (t0[f][c] != 0 && res == true){
				res = t0[f][c] == t1[f][c];
			}
		}
	}
	return res;
}


bool sudoku_resolver(Tablero t, int& count) {
	bool result = false;
	if(sudoku_esTableroTotalmenteResuelto(t))
	{
		result = true;
	}else if(sudoku_esTableroParcialmenteResuelto(t)){
		int f = sudoku_primerCeldaVaciaFila(t);
		int c = sudoku_primerCeldaVaciaColumna(t);
		int i = 1;
		while(i <= 9 && !result){
				sudoku_llenarCelda(t,f,c,i);
				count++;
				if(sudoku_resolver(t,count))
				{
					result = true;
				}else{
					sudoku_vaciarCelda(t,f,c);
					count++;
	       }
	   i++;
	}
     }
return result;
}
	





/**
 * Funciones Auxiliares de Tablero Parcialmente Resuelto.
 */
int cantEnFila(Tablero t, int f, int v){
	int cantidad = 0;
	int c = 0;
	while(indiceValido(c)){
		if(t[f][c] == v){
			cantidad++;
		}
		c++;
	}
	return cantidad;
}

bool filasOk(Tablero t){
	bool res = true;
	int f = 0;
	int c;
	while(indiceValido(f)){
		c = 0;
		while(indiceValido(c) && res){
			if (cantEnFila(t,f,t[f][c]) != 1 && t[f][c] != 0){
				res = false;
			}
			c++;
		}
		f++;
	}
	return res;
}

int cantEnColumna(Tablero t, int c, int v){
	int cantidad = 0;
		int f = 0;
		while(indiceValido(f)){
			if(t[f][c] == v){
				cantidad++;
			}
			f++;
		}
		return cantidad;
}

bool columnasOk(Tablero t){
	bool res = true;
	int f = 0;
	int c;
	while(indiceValido(f)){
		c = 0;
		while(indiceValido(c) && res){
			if (cantEnColumna(t,c,t[f][c]) != 1 && t[f][c] != 0){
				res = false;
			}
			c++;
		}
		f++;
	}
	return res;
}

int cantEnRegion(Tablero t, int x, int y, int v){
	int cantidad = 0;
	int f = 0;
	int c;
	while(f < 3){
		c = 0;
		while(c < 3){
			if(t[(x*3) + f][(y*3) + c] == v){
				cantidad++;
			}
			c++;
		}
		f++;
	}
	return cantidad;
}

bool regionValida(Tablero t, int x, int y){
	bool res = true;
	int f = 0;
	int c;
	while(f < 3){
		c = 0;
		while(c < 3 && res){
			if(cantEnRegion(t,x,y,t[(x*3) + f][(y*3) + c]) != 1 && t[(x*3) + f][(y*3) + c] != 0){
				res = false;
			}
			c++;
		}
		f++;
	}
	return res;
}

bool regionesOk(Tablero t){
	bool res = true;
	int x = 0;
	int y;
	while(x < 3){
		y = 0;
		while(y < 3 && res){
			if(!regionValida(t,x,y)){
				res = false;
			}
			y++;
		}
		x++;
	}
	return res;
}


/**
 * Funciones Auxiliares de sudoku_primerCeldaVaciaFila
 */
bool esFilaDePrimeraCeldaVacia(Tablero t, int f){
    return (indiceValido(f) && hayCeldaVacia(t,f) && noHayCeldaVaciaAntes(t,f));
}
bool hayCeldaVacia(Tablero t, int f){
    int c = 0;
    bool result = false;
    while(indiceValido(c) && !result){
        if(sudoku_esCeldaVacia(t,f,c)){
            result = true;
        }
        c++;
    }
    return result;

}
bool noHayCeldaVaciaAntes(Tablero t, int f){
    int x = 0;
    bool result = true;
    while (x < f && result){
        if(hayCeldaVacia(t,x)){
            result = false;
        }
        x++;
    }
    return result;
}

/**
 *  Funciones Auxiliares de sudoku_primerCeldaVaciaColumna
 */
bool esColumnaDePrimeraCeldaVacia(Tablero t, int c){
    int f = 0;
    bool result = false;
    while(indiceValido(f) && !result){
        if(hayCeldaVacia(t,f) && noHayCeldaVaciaAntes(t,f) && sudoku_esCeldaVacia(t,f,c) && esPrimeraCeldaVaciaDeFila(t,f,c)){
            result = true;
        }
        f++;
    }
    return result;
}
bool esPrimeraCeldaVaciaDeFila(Tablero t, int f, int c){
    int x = 0;
    bool result = true;
    while (x < c && result){
        if (sudoku_esCeldaVacia(t,f,x)){
            result = false;
        }
        x++;
    }
    return result;
}
void sudoku_print(Tablero t) {
    cout << "-------------------";
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << "|";
        for (int j = 0; j < 9; j++) {
            if (t[i][j] == 0) {
                cout << " ";
            } else {
                cout << t[i][j];
            }
            cout << "|";
        }
        cout << endl;
        if (i == 8) {
            cout << "+-+-+-+-+-+-+-+-+-+";
        } else {
            cout << "-------------------";
        }
        cout << endl;
    }
}

/**
 * Funcion Auxiliar llenarCelda
 */
bool esCeldaLlena(Tablero t,int f,int c,int v){
    return  t[f][c] == v;
}
/**
 * Auxiliar Tablero Valido
 */
bool posicionesValidas(Tablero t){
    int f = 0;
    int c;
    bool result = true;
    while (indiceValido(f)){
        c = 0;
        while (indiceValido(c)){
          if(0 > t[f][c] || t[f][c] > 9){
             result = false;
          }
            c++;
        }
        f++;
    }
    return result;
}



