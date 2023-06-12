#ifndef DIGIBATTLE_H_
#define DIGIBATTLE_H_

#include <iostream>
#include "tablero.h"
#include "casillero.h"
#include "cartas.h"
#include "jugador.h"


/*struct Jugador{
    int vidas;
    int numDeJugador;
    Lista<Ubicacion>* soldados;
    Lista<Carta*>* cartas;
};*/

class DigiBattle {
private:
    FILE* tableroArchivo;                   //BMP del tablero
    Tablero* tablero;                       //Tablero lol
    Lista<Jugador*>* jugadores;             //Puntero a lista con punteros a structs jugador que tienen punteros a lista de ints (son los numeros del soldado del jugador) y puntero a lista con 
    Lista<Casillero*>* casillerosInactivos; //Puntero a lista de punteros a los casilleros inactivos actuales (para bajarles el contador directamente desde digibattle)

    /*Pre: Recibe coordenadas y un tipo de terreno
    Pos: Devuelve si el casillero dado por coordenadas esta dentro del tablero y respeta el terreno querido
    */
    bool validarCasillero(Ubicacion posicion, Terreno tipo);
    /*Pre: Recibe que tipo de artilleria se va a utilizar
    Pos: Devuelve un struct con coordenadas validadas segun artilleria
    */
    Ubicacion pedirUbicacion(Artilleria tipo);
    /*Pre: Recibe dos ubicacion dentro del tablero
    Pos: Devuelve si la distancia entre una ubicacion y otra hay un movimiento valido
    */
    bool movimientoValida(Ubicacion ubiSoldado, Ubicacion ubiNueva );
public:

    /*Pre:-
    Pos: Bob el constructor
    */
    DigiBattle();

    /*Pre:
    Pos: Bob el destructor
    */
    ~DigiBattle();

    /*Pre:
    Pos: Pide cantidad de jugadores, cantidad de soldados y tamanio de mapa en formato XYZ
    */
    void iniciarJuego();

    /*Pre:
    Pos: maneja el numero de turnos, a qué jugador corresponde y la cuenta de casilleros inactivos
    */
    void turno();

    /*Pre:
    Pos: Si se decide mover un soldado o armamento, se puede hacer en vertical, horizontal o diagonal
    */
    void moverTropa(int NroJugador);

    /*Pre:
    Pos: Pide la posicion XYZ en la que se va a poner la mina
    */
    void ponerMina(int jugador);

    /*Pre:
    Pos: Agrega una carta a la lista de cartas del jugador
    */
    void obtenerCarta();

    /*Pre: La carta debe existir en la lista
    Pos: Usa una carta de la lista de cartas del jugador
    */
    void usarCarta();

    /*Pre: -Recibe numero de jugador , casillero y tipo de artilleria a poner, en caso de ser soldado dejar 
    numero de soldado , en caso contrario dejar en cero
    Pos: Comprueba la colision de en un casillero , y en caso de colision desactiva casilla y baja vidas
    */
    void resolverColision(Casillero* casillero , Artilleria artilleria, int nroJugador);


   /*Pre: 
    Pos: 
    */
    void resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador, int nroSoldado)


 

    /*Pre: -
    Pos: Revisa si se cumplen las condiciones de victoria
    */
    bool comprobarVictoria();


    /*Pre: Recibe un numero de jugador junto con un numero de soldado
    Pos: Le resta una vida al jugador ,ademas de sacarle el soldado
    */
    void bajarVidaJugador(int nroJugador,int nroSoldado);

    /*Pre: Recibe cantidad de soldados por jugador y cantidad de jugadores
    Pos: Coloca todos los soldados iniciales , por jugador
    */
    void colocarSoldados(int cantidadSoldados, int cantidadJugadores);

    /*Pre: Recibe numero de jugador ,numero de soldado , y la ubicacion
    Pos: Coloca el soldado
    */
    void ponerSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado);


};
#endif