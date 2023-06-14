#ifndef CARTAS
#define CARTAS

#include <cstdlib>
#include <time.h>
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
    /*
    Pre:~~
    Pos: Constructor randomiza el tipoDeCarta
    */
    Carta();

    /*
    Pre:~~
    Pos: Bob el destructor
    */
    ~Carta();

    /*
    Pre:~~
    Pos: Devuelve el tipo de carta
    */
    Carta::tipos getCarta();

    /*
    Pre:~~
    Pos: Llama a el método correspondiente para usar la carta
    */
    void usarCarta(Tablero *tablero, tipos numDeCarta, Ubicacion posicion, Jugador * jugador);

    /*
    Pre:~~
    Pos: Mata todo en su radio y desactiva las casillas la cantidad de turnos correspondientes
    */
    void cartaAtaqueQuimico(Tablero * tablero, Ubicacion posicion);

    /*
    Pre:~~
    Pos: Coloca un avion radar que detecta minas y soldados en el rango
    */
    void cartaAvionRadar(Tablero * tablero, Ubicacion posicion);

    /*
    Pre:~~
    Pos: Pone un barco que si está en el agua permite disparar un misil por turno (municion limitada)
    */
    void cartaBarco(Tablero * tablero, Ubicacion posicion);

    /*
    Pre:~~
    Pos: Obtiene dos cartas nuevas
    */
    void cartaPotOfGreed(Jugador * jugador);

    /*
    Pre:~~
    Pos:
    */
    void tipo5();

    /*
    Pre:~~
    Pos:
    */
    void tipo6();

};




#endif