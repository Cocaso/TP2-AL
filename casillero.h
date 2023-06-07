#ifndef CASILLERO
#define CASILLERO
#include <iostream>


class Casillero {
private:
    enum Terreno {
        TIERRA,
        AGUA,
        AIRE
    };

    enum Artilleria {
        BARCO,
        AVION,
        MINA,
        SOLDADO
    };

    struct Contenido {
        int jugador;
        int numSoldado;
        Artilleria artillerias;
        int turnosInactivo = 0;
    };

    Terreno casilla;
    Contenido* contenidos;

public:
    Casillero();
    ~Casillero();

    /*Pre: -
    Pos: cambia el terreno de la casilla
    */
    void cambiarTerreno(int binario);

    /*Pre:
    Pos:
    */
    void desactivarCasilla();



};



#endif