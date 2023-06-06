#ifndef TABLERO
#define TABLERO

#include "listaBase.h"
#include "casillero.h"
#include "EasyBMP.h"

class Tablero {
private:
    Lista<Lista<Casillero*>*>* tablero;
    int maxX;
    int maxY;
    int maxZ;
public:
    /*Pre:
    Pos:
    */
    Tablero();
    /*Pre:
    Pos:
    */
    Tablero(int x, int y, int z);
    /*Pre:
    Pos:
    */
    ~Tablero();

};




#endif