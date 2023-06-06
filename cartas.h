#ifndef CARTAS
#define CARTAS

#include <random>

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
    void usarCarta();

    /*Pre:
    Pos: Desactiva por 10 turnos la casilla de la posicion que se marco, por 8 turnos el siguiente radio...
    */
    void cartaAtaqueQuimico();

    /*Pre:
    Pos: Pone un avion que si esta en el aire detecta minas enemigas en la zona 
    */
    void cartaAvionRadar();

    /*Pre:
    Pos: Pone un barco que si esta en el agua permite disparar un misil por turno
    */
    void cartaBarco();

    /*Pre:
    Pos:
    */
    void tipo4();

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