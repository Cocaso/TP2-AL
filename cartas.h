#ifndef CARTAS
#define CARTAS

#include <cstdlib>
#include "tablero.h"
#include "jugador.h"


class Carta {
private:
    enum tipos {
        ATAQUEQUIMICO,
        AVIONRADAR,
        BARCO,
        FUTURO,
        carta5,
        carta6,
    };

    tipos tipoDeCarta;
public:
    /*Pre:
    Pos:
    */
    Carta();

    /*Pre:
    Pos:
    */
    ~Carta();

    /*Pre:
    Pos:
    */
    void usarCarta(Tablero *tablero, Carta::tipos numDeCarta, unsigned int x, unsigned int y, unsigned int z);

    /*Pre:
    Pos:
    */
    Carta::tipos getCarta();

    /*Pre:
    Pos: Desactiva por 10 turnos la casilla de la posicion que se marco, por 8 turnos el siguiente radio...
    */
    void cartaAtaqueQuimico(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z);

    /*Pre:
    Pos: Pone un avion que si esta en el aire detecta minas enemigas en la zona 
    */
    void cartaAvionRadar(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z);

    /*Pre:
    Pos: Pone un barco que si esta en el agua permite disparar un misil por turno
    */
    void cartaBarco(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z);

    /*Pre:
    Pos:
    */
    void cartaPotOfGreed();

    /*Pre:
    Pos:
    */
    void tipo5();

    /*Pre:
    Pos:
    */
    void tipo6();

};




#endif