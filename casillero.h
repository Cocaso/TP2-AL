#ifndef CASILLERO
#define CASILLERO
#include <iostream>


class Casillero {
private:
    enum terreno {
        TIERRA,
        AGUA,
        AIRE
    };

    enum artilleria {
        BARCO,
        AVION,
        MINA
    };

    struct contenido {
        int jugador;
        int numSoldado;
        artilleria artillerias;
        int turnosInactivo = 0;
    };

    terreno casilla;
    contenido* contenido;

public:
    Casillero();
    ~Casillero();


    /*Pre:
    Pos:
    */
    void desactivarCasilla();



};



#endif