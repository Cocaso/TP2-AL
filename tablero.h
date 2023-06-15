#ifndef TABLERO
#define TABLERO

#include "listaBase.h"
#include "casillero.h"
#include "bitmap_image.hpp"

struct Ubicacion{
        int x;
        int y;
        int z;
};

class Tablero {
private:
    int mapaTemplate[20][20] = {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                                {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                {0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
                                {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}};
    Lista<Lista<Lista<Casillero*>*>*>* tablero;
    //Z     Y     X
    int maxX;
    int maxY;
    int maxZ;
    
    
public:
    
    /*
    Pre:-
    Pos: Crea un tablero vacío
    */
    Tablero();

    /*
    Pre:-
    Pos: Asigna los máximos del tablero
    */
    Tablero(Ubicacion maxSize);
    /*
    Pre:
    Pos:
    */
    ~Tablero();
    /*
    Pre: Las medidas tienen que haber sido establecidas
    Pos: Rellena el tablero con el terreno
    */
    void crearTerreno();

    /*
    Pre: ~~
    Pos: Devuelve el tamaño en el eje X del tablero
    */
    int getTamanhoTableroX();

    /*
    Pre: ~~
    Pos: Devuelve el tamaño en el eje Y del tablero
    */
    int getTamanhoTableroY();

    /*
    Pre:
    Pos:
    */
    void mostrarTablero();

    /*
    Pre: Recibe 3 coordenadas
    Pos: Devuelve true si las coordenadas existen, false si no existen
    */
    bool validarCoordenadas(Ubicacion posicion);
    
    /*
    Pre: recibe coordenadas
    Pos:devuelve una casilla pedida por coordenadas
    */
    Casillero* getCasillero(Ubicacion posicion);
};

#endif