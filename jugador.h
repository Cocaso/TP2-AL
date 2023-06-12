#ifndef JUGADOR
#define JUGADOR

#include "listaBase.h"
#include "tablero.h"
#include "cartas.h"

struct InfoSoldado {
    int nroSoldado;
    Ubicacion posicion;
}


class Jugador {
private:
    int vidas;
    int numDeJugador;
    Lista<InfoSoldado*>* soldados;
    Lista<Carta*>* cartas;

public:

    /*Pre:
    Pos: Crea un jugador vacío
    */
    Jugador();

    /*Pre: Recibe un número de jugador
    Pos: Crea el jugador con ese número
    */
    Jugador(int nroJugador, int vidas);

    /*Pre:
    Pos:
    */
    ~Jugador();
    
    /*Pre:
    Pos:
    */
    int getNumeroJugador();

     /*Pre:Recibe un numero de soldado y su ubicacion
    Pos:agrega soldado a la lista de soldados del jugador
    */
    void agregarSoldado(int posicionSoldado,int nroSoldado);
    /*Pre: 
    Pos: Resta una vida al jugador, y devuelve la cantidad que le quedan
    */
    int reducirVidaJugador();

    /*Pre: 
    Pos: Devuelve la lista de cartas para verlas y usarlas
    */
    Lista<Carta*>* getCartas();

    *Ubicacion getSoldado(int );


    
}
#endif
