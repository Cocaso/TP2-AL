#ifndef DIGIBATTLE
#define DIGIBATTLE

#include <iostream>
#include <fstream>
#include <cstdio> // tambien pa probar
#include "tablero.h"
#include "casillero.h"
#include "jugador.h"
#include <cstdlib>
#include <ctime>

class DigiBattle {
private:
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
    Pre: Debe elegirse un jugador existente
    Pos: Devuelve un puntero al jugador buscado o NULL si no se encontró
    */
    Jugador* buscarJugador(int nroJugador);

    /*
    Pre: Recibe coordenadas y un tipo de artilleria
    Pos: Devuelve true si el casillero existe y es válido para la artillería requerida
    */ 
    bool validarCasillero(Ubicacion posicion, Artilleria tipo);
    
    /*
    Pre: Recibe dos ubicaciones dentro del tablero para mover SOLDADO o BARCO
    Pos: Devuelve TRUE si la distancia de movimiento, la direccion es permitida y la tropa no se mueve al mismo casillero
    */
    bool validarDestinoSoldado(Ubicacion ubiSoldado, Ubicacion ubiNueva );

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
    
    /*
    Pre: La carta debe existir en la lista
    Pos: Usa una carta de la lista de cartas del jugador
    */
    void usarCarta(Jugador * jugador);

public:

    /*
    Pre:-
    Pos: construye el digiBatlle
    */
    DigiBattle();

    /*
    Pre:
    Pos: destruye el digiBatte
    */
    ~DigiBattle();

    /*
    Pre:
    Pos: Inicia el juego pidiendo cantidad de jugadores , cantidad de soldados , y tamano del tablero
    */
    void iniciarJuego();

    /*
    Pre:
    Pos: maneja los turnos de cada jugador
    */
    void turno();

    /*
    Pre:
    Pos: Pide la posicion en la que se va a poner la mina
    */
    void ponerMina();

    /*
    Pre: 
    Pos: En caso de tener un barco propio te deja dispararlo
    */
    void dispararBarco();

    /*Pre:
    Pos: Si se decide mover una tropa, se puede hacer en vertical, horizontal o diagonal
    */
    void moverTropa();

    /*Pre: Recibe una Artilleria, y la lista de tropas que tiene el jugador
    Pos: Muestra en pantalla el tipo de tropa, el numero de tropa y la ubicacion de cada tropa de ese tipo
    */
    void mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<InfoTropa*>* tropasDelJugador);

    /*
    Pre: Recibe un jugador
    Pos: Agrega una carta a la lista de cartas del jugador
    */
    void obtenerCarta(Jugador * jugador);

    /*
    Pre: Recibe un numero de jugador junto con un numero de tropa y el tipo de Artilleria
    Pos: Le quita la tropa al jugador y si es tipo SOLDADO le resta una vida ,en caso de
    quedarse sin vidas ,saca al jugador de la lista de jugadores
    */
    void sacarTropaJugador(int nroJugador,int nroTropa, Artilleria artilleria);

    /*
    Pre: Recibe cantidad de tropas por jugador y cantidad de jugadores
    Pos: Coloca todos los tropas iniciales por jugador
    */
    void colocarSoldados(int cantidadSoldados, int cantidadJugadores);

    /*
    Pre: Recibe numero de jugador ,numero de soldado , y la ubicacion
    Pos: Coloca el soldado si la artillera en la ubicacion es VACIO en caso contrario 
    analiza que habia para determinar que hacer
    */
    void ponerSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado);

    /*
    Pre: ~~
    Pos: Devuelve un numero aleatorio entre 3 y 6
    */
    int poderMina();

    /*Pre: Recibe un jugador y el tipo de Artilleria a elegir
    Pos: Devuelve el numero de tropa a mover
    */
    int pedirNumeroTropa(Jugador * jugador, Artilleria seleccionTropa);

    /*
    Pre: Recibe un numero de jugador
    Pos: Devuelve en que posicion de la lista de jugadores esta el jugador
    */
    int getPosicionJugadorEnLista(int nroJugador);

    /*Pre: Recibe una Artilleria, la cantidad de aviones y la cantidad de barcos disponibles
    Pos: Devuelve TRUE si la Artilleria recibida existe y tiene al menos 1 disponible para usar
    */
    bool comprobarSeleccionTropa(Artilleria seleccionTropa, int cantidadAviones, int cantidadBarcos);

    /*
    Pre: Recibe un casillero
    Pos: Compara si habia algo en dicho casillero para realizar lo que corresponda con el choque de artillerias,
    devuelve true si la artillería se coloca o false si se destruye
    */
    bool resolverColision(Casillero* casilleroNuevo);

    /*
    Pre: Recibe un casillero partida, el casillero destino y la posicion destino
    Pos: Compara la artillería del casillero partido con el casillero destino, y devuelve
    true si la artillería del casillero partida se logra colocar en casillero destino
    */
    bool resolverColision(Casillero* casilleroAnterior, Casillero* casilleroNuevo, Ubicacion posicionNueva);

    /*
    Pre: -
    Pos: Revisa si se cumplen las condiciones de victoria
    */
    bool comprobarVictoria();

    /*
    Pre: Recibe una ubicacion donde utilizar la carta ataque quimico
    Pos: Mata todo en su radio y desactiva las casillas la cantidad de turnos correspondientes
    */
    void cartaAtaqueQuimico(Ubicacion posicion);

    /*
    Pre: Recibe un jugador
    Pos: Agrega un Avion al tablero y a la lista tropas del jugador
    */
    void cartaAvionRadar(Jugador * jugador);

    /*
    Pre: Recibe un jugador
    Pos: Agrega un Barco al tablero y a la lista tropas del jugador
    */
    void cartaBarco(Jugador * jugador);

    /*
    Pre: Recibe un jugador
    Pos: Agrega 2 cartas al jugador
    */
    void cartaPotOfGreed(Jugador * jugador);

    /*
    Pre: Recibe un jugador
    Pos: Agrega 2 Soldados al tablero y a la lista tropas del jugador 
    */
    void cartaAgregarSoldados(Jugador * jugador);

    /*
    Pre: Recibe un jugador
    Pos: Lanza un rayo laser en una direccion desde la posicion de un soldado, destruye cualquier tropa que encuentre
    y inactiva la casilla por 5 turnos
    */
    void cartaRayoLaser(Jugador * jugador);

    /*
    Pre:
    Pos: Devuelve la lista de jugadores
    */
    Lista<Jugador*>* getListaJugadores();

    /*
    Pre: recibe ubicacion de soldado ,ademas de numero de jugador
    Pos: Devuelve true si el soldado colisiona con otro soldado
    */
    bool colisionSoldado(Ubicacion posicionSoldado, int numJugador);

};
#endif