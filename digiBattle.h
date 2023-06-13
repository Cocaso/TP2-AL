#ifndef DIGIBATTLE
#define DIGIBATTLE

#include <iostream>
#include "tablero.h"
#include "casillero.h"
#include "cartas.h"
#include "jugador.h"



/*struct Jugador{
    int vidas;
    int numDeJugador;
    Lista<Ubicacion>* tropas;
    Lista<Carta*>* cartas;
};*/

class DigiBattle {
private:
    FILE* tableroArchivo;                   //BMP del tablero
    Tablero* tablero;                       //Tablero lol
    Lista<Jugador*>* jugadores;             //Puntero a lista con punteros a structs jugador que tienen punteros a lista de ints (son los numeros del soldado del jugador) y puntero a lista con 
    Lista<Casillero*>* casillerosInactivos; //Puntero a lista de punteros a los casilleros inactivos actuales (para bajarles el contador directamente desde digibattle)

    //Metodos
    /*
    Pre: Recibe que tipo de artilleria se va a utilizar
    Pos: Devuelve un struct con coordenadas validadas segun artilleria
    */
    Ubicacion pedirUbicacion(Artilleria tipo);

    /*
    Pre: Recibe coordenadas y un tipo de artilleria
    Pos: Devuelve true si el casillero existe y es válido para la artillería requerida
    */ 
    bool validarCasillero(Ubicacion posicion, Artilleria tipo);
    
    /*
    Pre: Recibe dos ubicaciones dentro del tablero para mover SOLDADO o BARCO
    Pos: Devuelve TRUE si la distancia de movimiento y la direccion es permitida
    */
    bool validarMovimiento(Ubicacion ubiSoldado, Ubicacion ubiNueva );

    /*
    Pre: 
    Pos: Reduce los turnos inactivos de las casillas inactivas
    */
    void reducirCasilleroInactivo();

    /*
    Pre: Debe de haber quedado solo un jugador con vida 
    Pos: Anuncia quien fue el ganador y da por terminada la partida
    */
    void anunciarGanador();
    
public:

    /*
    Pre:-
    Pos: Bob el constructor
    */
    DigiBattle();

    /*
    Pre:
    Pos: Bob el destructor
    */
    ~DigiBattle();

    /*
    Pre:
    Pos: Pide cantidad de jugadores, cantidad de tropas y tamanio de mapa en formato XYZ
    */
    void iniciarJuego();

    /*
    Pre:
    Pos: maneja el numero de turnos, a qué jugador corresponde y la cuenta de casilleros inactivos
    */
    void turno();

    /*
    Pre:
    Pos: Pide la posicion XYZ en la que se va a poner la mina
    */
    void ponerMina(int jugador);
    /*
    Pre: Debe elegirse un jugador existente
    Pos: Devuelve un puntero al jugador buscado o NULL si no se encontró
    */
    Jugador* buscarJugador(int nroJugador);

    /*Pre:
    Pos: Si se decide mover una tropa, se puede hacer en vertical, horizontal o diagonal
    */
    void moverTropa();

    /*Pre: Recibe una Artilleria, y la lista de tropas que tiene el jugador
    Pos: Muestra en pantalla el tipo de tropa, el numero de tropa y la ubicacion de cada tropa de ese tipo
    */
    void mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<InfoTropa*>* tropasDelJugador);



    /*Pre: Recibe una Artilleria, la cantidad de aviones y la cantidad de barcos disponibles
    Pos: Devuelve TRUE si la Artilleria recibida existe y tiene al menos 1 disponible para usar
    */
    bool comprobarSeleccionTropa(Artilleria seleccionTropa, int cantidadAviones, int cantidadBarcos);


    /*
    Pre:
    Pos: Agrega una carta a la lista de cartas del jugador
    */
    void obtenerCarta(Jugador * jugador);

    /*
    Pre: La carta debe existir en la lista
    Pos: Usa una carta de la lista de cartas del jugador
    */
    void usarCarta(int nroJugador, Carta* carta);

    /*
    Pre: Recibe numero de jugador , casillero y tipo de artilleria a poner, en caso de ser soldado dejar 
    numero de soldado , en caso contrario dejar en cero
    Pos: Comprueba la colision de en un casillero , y en caso de colision desactiva casilla y baja vidas
    */
    void resolverColision(Casillero* casillero , Artilleria artilleria, int nroJugador);


    /*
    Pre: 
    Pos: 
    */
    void resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador, int nroSoldado);

    /*
    Pre: -
    Pos: Revisa si se cumplen las condiciones de victoria
    */
    bool comprobarVictoria(int nroJugador);


    /*
    Pre: Recibe un numero de jugador junto con un numero de soldado
    Pos: Le resta una vida al jugador ,ademas de sacarle el soldado
    */
    void bajarVidaJugador(int nroJugador,int nroSoldado);

    /*
    Pre: Recibe cantidad de tropas por jugador y cantidad de jugadores
    Pos: Coloca todos los tropas iniciales , por jugador
    */
    void colocarSoldados(int cantidadSoldados, int cantidadJugadores);

    /*
    Pre: Recibe numero de jugador ,numero de soldado , y la ubicacion
    Pos: Coloca el soldado si la artillera en la ubicacion es VACIO y si es SOLDADO se muere el soldado que estaba en la
    ubicacion y el que se iba a colocar
    */
    void ponerSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado);

    /*
    Pre:
    Pos:
    */
    int getPosicionJugadorEnLista(int nroJugador);

    /*
    Pre:
    Pos: Devuelve la lista de jugadores
    */
    Lista<Jugador*>* getListaJugadores();


};
#endif