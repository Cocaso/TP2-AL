#ifndef JUGADOR
#define JUGADOR

#include "listaBase.h"
#include "tablero.h"
#include <ctime>


enum Tipos {
    ATAQUEQUIMICO,
    AVIONRADAR,
    INVOCARBARCO,
    POTOFGREED,
    SOLDADOSEXTRA,
    RAYOLASER,
};

struct InfoTropa {
    int nroTropa;
    Artilleria tropa;
    Ubicacion posicion;
};

struct casilleroUbi{
    Ubicacion ubicacion;
    Casillero* casillero;
};

class Jugador {
private:
    int vidas;
    int numSiguienteSoldado = vidas;
    int numSiguienteBarco = 0;
    int numSiguienteAvion = 0;
    int numDeJugador;
    Lista<InfoTropa*>* tropas;
    Lista<Tipos>* cartas;
    Lista<casilleroUbi>* casillerosVisibles;

public:
    /*
    Pre:
    Pos: Crea un jugador vacío
    */
    Jugador();

    /*
    Pre: Recibe un número de jugador
    Pos: Crea el jugador con ese número
    */
    Jugador(int nroJugador, int vidas);

    /*
    Pre: Recibe un número de jugador
    Pos: Crea el jugador con ese número
    */
    ~Jugador();

    /*
    Pre:Recibe un numero de soldado y su ubicacion
    Pos:agrega soldado a la lista de tropas del jugador
    */
    void agregarTropa(Ubicacion posicionSoldado, int nroSoldado, Artilleria tipoTropa);

    /*
    Pre: recibe un tipo de carta
    Pos: devuelve el nombre de una carta
    */
    void nombreCarta( Tipos numDeCarta);

    /*
    Pre: ~~
    Pos: devuelve los nombres de las cartas
    */
    void informarCartasDisponibles();

    /*
    Pre: ~~
    Pos: devuelve la cantidad de cartas
    */
    int cantidadCartas();

    /*
    Pre: recibe el numero de tropa y el tipo de Artilleria
    Pos: Si la tropa es SOLDADO le resta una vida al jugador, ademas de sacarle la tropa, y devuelve la cantidad de vidas que le quedan al jugador
    */
    int removerTropa(int nroTropa, Artilleria tipoTropa);

    /*
    Pre:~~
    Pos: Devuelve el numero del jugador
    */
    int getNumeroJugador();

    /*
    Pre:~~
    Pos: Devuelve la posicion de la tropa en la lista de tropas
    */
    int getPosicionTropaEnLista(int nroTropaBuscada, Artilleria tipoTropa);

    /*
    Pre: 
    Pos: 
    */
    int getNumSiguienteSoldado();

    /*
    Pre: 
    Pos: 
    */
    int getNumSiguienteBarco();

    /*
    Pre: 
    Pos: 
    */
    int getNumSiguienteAvion();

    /*
    Pre: recibe un numero de tropa y tipo de artilleria
    Pos: Devuelve si exite dicha tropa
    */
    bool tropaViva(int nroTropaPedida, Artilleria tipoArtilleria);

    /*
    Pre:~~
    Pos: Devuelve la posicion del soldado
    */
    Ubicacion getPosicionTropa(int nroTropa, Artilleria tipoArtilleria);

    /*
    Pre: Debe elegirse una tropa existente
    Pos: Devuelve un puntero a la tropa buscada o NULL si no se encontró
    */
    InfoTropa* getTropa(int nroTropaPedida, Artilleria tipoArtilleria);

    /*
    Pre: Debe elegirse una tropa existente
    Pos: Cambia la ubicacion de la tropa
    */
    void setPosicionTropa(int nroTropaPedida, Artilleria tipoArtilleria, Ubicacion ubicacion);
    
    /*
    Pre:~~
    Pos: Devuelve la lista de tropas
    */
    Lista<InfoTropa*>* getListaTropas();

    /*
    Pre:~~
    Pos: Devuelve la lista de casilleros inactivos
    */
    Lista<casilleroUbi>* getListaCasillerosVisibles();

    /*
    Pre: 
    Pos: Devuelve la lista de cartas para verlas y usarlas
    */
    Lista<Tipos>* getListaCartas();
    
    /*
    Pre: ~~
    Pos: Agrega un numero aleatorio del 0 al 5 a la lista de cartas
    */
    void addCarta();

    /*
    Pre: recibe un numero de carta
    Pos: devuelve 
    */
    Tipos getCarta(int nroCarta);
};
#endif
