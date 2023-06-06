#ifndef DIGIBATTLE_H_
#define DIGIBATTLE_H_

#include <iostream>
#include <tablero.h>
#include <casillero.h>
#include <cartas.h>

struct Jugador{
    int vidas;
    Lista<int>* soldados;
    Lista<Carta>* cartas;
};


class DigiBattle {
private:
    FILE* tableroArchivo;                   //BMP del tablero
    Tablero tablero;
    Lista<Jugador>* jugadores;              //Puntero a lista con structs jugador que tienen punteros a lista de ints (son los numeros del soldado del jugador) y puntero a lista con 
    Lista<Casillero*>* casillerosInactivos; //Puntero a lista de punteros a los casilleros inactivos actuales (para bajarles el contador directamente desde digibattle)
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
    void moverTropa();

    /*Pre:
    Pos:
    */
    void obtenerCarta();

    /*Pre:
    Pos: Pide la posicion XYZ en la que se va a poner la mina
    */
    void ponerMina();

    /*Pre:
    Pos: Agrega una carta a la lista de cartas del jugador
    */
    void obtenerCarta();

    /*Pre: La carta debe existir en la lista
    Pos: Usa una carta de la lista de cartas del jugador
    */
    void usarCarta();

    /*Pre: -
    Pos: Comprueba la colision de minas y soldados en un mismo casillero
    */
    void comprobarColision();

    /*Pre: -
    Pos: Revisa si se cumplen las condiciones de victoria
    */
    void condicionDeVictoria();









};
#endif