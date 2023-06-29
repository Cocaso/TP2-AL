#ifndef JUGADOR
#define JUGADOR

#include "listaBase.h"
#include "tablero.h"
#include "tropa.h"
#include <ctime>


enum Tipos {
    ATAQUEQUIMICO,
    AVIONRADAR,
    INVOCARBARCO,
    POTOFGREED,
    SOLDADOSEXTRA,
    RAYOLASER
};


class Jugador {
    private:
    int vidas;
    int numSiguienteSoldado;
    int numSiguienteBarco;
    int numSiguienteAvion;
    int numDeJugador;
    Lista<Tropa*>* tropas;
    Lista<Tipos>* cartas;

    public:

    /*
    Pre:
    Pos: Crea un jugador vacío
    */
    Jugador();

    /*
    Pre: Recibe un número de jugador
    Pos: Crea el jugador y le asigna ese número
    */
    Jugador(int nroJugador);

    /*
    Pre: 
    Pos: Borra al jugador
    */
    ~Jugador();

    /*
    Pre:Recibe un numero de soldado, tipo de artilleria y su ubicacion
    Pos:agrega soldado a la lista de tropas del jugador
    */
    void agregarTropa(Ubicacion posicionSoldado, int nroSoldado, Artilleria tipoTropa);

    /*
    Pre: recibe un tipo de artilleria , ubicacion a colocar artilleria , y numero de tropa pedia
    Pos: Cambia la ubicacion de la tropa
    */
    void setPosicionTropa(int nroTropaPedida, Artilleria tipoArtilleria, Ubicacion ubicacion);

    /*
    Pre: recibe un tipo de carta
    Pos: devuelve el nombre de la carta
    */
    void nombreCarta( Tipos numDeCarta);

    /*
    Pre: ~~
    Pos: devuelve los nombres de las cartas disponibles por el jugador
    */
    void informarCartasDisponibles();

    /*
    Pre: Recibe un numero de tropa
    Pos: Baja la vida al barco si le quedan vidas
    */
    bool bajarVidaBarco(int nroTropa);

        
    /*
    Pre: ~~
    Pos: Le agrega una carta al jugador
    */
    void addCarta();

    /*
    Pre: Recibe el numero de tropa y el tipo de Artilleria
    Pos: Si la tropa es SOLDADO le resta una vida al jugador, ademas de sacarle la tropa, y devuelve la cantidad de vidas que le quedan al jugador
    */
    int removerTropa(int nroTropa, Artilleria tipoTropa);

    /*
    Pre: ~~
    Pos: Devuelve el numero del jugador
    */
    int getNumeroJugador();


    /*
    Pre: ~~
    Pos: Devuelve el numero de vidas del jugador
    */
    int getVidas();


    /*
    Pre: Recibe una artilleria
    Pos: Devuelve la cantidad de tropas de ese tipo Artilleria que le quedan al jugador
    */
    int cantidadTropas(Artilleria tipoTropa);

    /*
    Pre: Recibe numero de tropa buscada,ademas de su tipo de tropa
    Pos: Devuelve la posicion de la tropa en la lista de tropas
    */
    int getPosicionTropaEnLista(int nroTropaBuscada, Artilleria tipoTropa);
    
    /*
    Pre: ~~
    Pos: Devuelve el numero del siguiente soldado para agregar a la lista de tropas
    */
    int getNumSiguienteSoldado();

    /*
    Pre: ~~
    Pos: Devuelve el numero del siguiente barco para agregar a la lista de tropas
    */
    int getNumSiguienteBarco();

    /*
    Pre: ~~
    Pos: Devuelve el numero del siguiente avion para agregar a la lista de tropas
    */
    int getNumSiguienteAvion();

    /*
    Pre: ~~
    Pos: devuelve la cantidad de cartas que tiene el jugador
    */
    int cantidadCartas();

    /*
    Pre: Recibe un numero de tropa y tipo de artilleria
    Pos: Devuelve si exite dicha tropa
    */
    bool tropaViva(int nroTropaPedida, Artilleria tipoArtilleria);

    /*
    Pre: Recibe numero de tropa y tipo de artilleria
    Pos: Devuelve la posicion de la tropa
    */
    Ubicacion getUbicacionTropa(int nroTropa, Artilleria tipoArtilleria);

    /*
    Pre: Recibe un numero de posicion de carta en la lista cartas
    Pos: Devuelve la carta buscada, ademas de sacarsela del mazo
    */
    Tipos getCarta(int numeroCarta);

    /*
    Pre: Recibe numero de tropa pedida
    Pos: Devuelve un puntero a la tropa buscada o NULL si no se encontró
    */
    Tropa* getTropa(int nroTropaPedida, Artilleria tipoArtilleria);

    /*
    Pre:~~
    Pos: Devuelve la lista de tropas
    */
    Lista<Tropa*>* getListaTropas();

    /*
    Pre: 
    Pos: Devuelve la lista de cartas para verlas y usarlas
    */
    Lista<Tipos>* getListaCartas();


};
#endif
