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
	return (posicionValida(f,c) && (t[f][c] == 0));
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

        return result;
    }
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

        return result;
    }
}

int sudoku_valorEnCelda(Tablero t, int f, int c) {
	return t[f][c];
}

void sudoku_llenarCelda(Tablero t, int f, int c, int v) {
    if (posicionValida(f,c) && !esCeldaLlena(t,f,c,v)){
        t[f][c] = v;
    }

}

void sudoku_vaciarCelda(Tablero t, int f, int c) {
	if (posicionValida(f,c) && !sudoku_esCeldaVacia(t,f,c)){
		t[f][c] = 0;
	}
}

bool sudoku_esTableroValido(Tablero t) {
	return posicionesValidas(t);
}

bool sudoku_esTableroParcialmenteResuelto(Tablero t) {
    return (sudoku_esTableroValido(t) && filasOK(t) && columnasOK(t) && regionOk(t));
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	return sudoku_nroDeCeldasVacias(t) == 0 && sudoku_esTableroParcialmenteResuelto(t);
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

bool sudoku_resolver(Tablero t) {
	// COMPLETAR
	return false;
}

bool sudoku_resolver(Tablero t, int& count) {
	// COMPLETAR
	return false;
}



/**
 *  Funciones Auziliares ParcialmenteResuleto
 */
bool filasOK(Tablero t){
	bool res = true;
		int f = 0;
		int c;
		while(indiceValido(f)){
			c = 0;
			while(indiceValido(c)){
				if (cantidadEnFila(t,f,t[f][c]) != 1 && t[f][c] != 0){
					res = false;
				}
				c++;
			}
			f++;
		}
		return res;
}
int cantidadEnFila(Tablero t, int f, int v){
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
bool columnasOK(Tablero t){
	bool res = true;
		int f = 0;
		int c;
		while(indiceValido(f)){
			c = 0;
			while(indiceValido(c)){
				if (cantidadEnColumna(t,f,t[f][c]) != 1 && t[f][c] != 0){
					res = false;
				}
				c++;
			}
			f++;
		}
		return res;
}
int cantidadEnColumna(Tablero t, int f, int v){
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
bool regionOk(Tablero t){
    int f =0;
    int c;
    bool result = true;
    while(f < 3){
        c = 0;
        while (c < 3){
            if(!regionValida(t,f,c)){
                result = false;
            }
            c++;
        }
        f++;
    }
    return result;
}
bool regionValida(Tablero t, int x, int y){
    int f = 1;
    int c;
    bool result = true;
    while (f <= 3){
        c = 1;
        while(c <= 3){
            if(cantidadEnRegion(t, x, y, t[3*x+f][3*y+c]) != 1 && t[3*x+f][3*y+c] != 0){
                result = false;
            }
        }
    }
    return result;
}
int cantidadEnRegion(Tablero t, int x, int y, int value){
    int f = 1;
    int c;
    int cantEnColumna = 0;
    while(f <= 3){
        c = 1;
        while (c <= 3) {
            if (t[3*x+f][3*y+c] == value) {
                cantEnColumna++;
            }
            c++;
        }
    }
    return cantEnColumna;
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
