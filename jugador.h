#ifndef JUGADOR
#define JUGADOR

#include "listaBase.h"
#include "tablero.h"
#include "cartas.h"

enum tipos {
    ATAQUEQUIMICO,
    AVIONRADAR,
    INVOCARBARCO,
    POTOFGREED,
    SOLDADOEXTRA,
    RAYOLASER,
};

struct InfoTropa {
    int nroTropa;
    Artilleria tropa;
    Ubicacion posicion;
};

class Jugador {
private:
    int vidas;
    int numSiguienteSoldado = vidas;
    int numSiguienteBarco = 0;
    int numSiguienteAvion = 0;
    int numDeJugador;
    Lista<InfoTropa*>* tropas;
    Lista<tipos*>* cartas;

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
    Pre:Recibe un numero de soldado y su ubicacion
    Pos:agrega soldado a la lista de tropas del jugador
    */
    void agregarTropa(Ubicacion posicionSoldado, int nroSoldado, Artilleria tipoTropa);

    /*
    Pre: recibe un tipo de carta
    Pos: devuelve el nombre de una carta
    */
    void nombreCarta( tipos numDeCarta);

    /*
    Pre: ~~
    Pos: devuelve los nombres de las cartas
    */
    void nombrarCartas();

    /*
    Pre: ~~
    Pos: devuelve la cantidad de cartas
    */
    int cantidadCartas();

    /*
    Pre: recibe el numero de soldado muerto
    Pos: Le resta una vida al jugador, ademas de sacarle el soldado muerto, y devuelve la cantidad que le quedan
    */
    int removerSoldado(int nroSoldado );

    /*
    Pre:~~
    Pos: Devuelve el numero del jugador
    */
    int getNumeroJugador();

    /*
    Pre:~~
    Pos: Devuelve el numero del jugador
    */
    int getPosicionSoldadoEnLista(int nroSoldado);

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
    Pre: Debe elegirse un soldado existente
    Pos: Devuelve un puntero al soldado buscado o NULL si no se encontró
    */
    InfoTropa* getTropa(int nroTropaPedida, Artilleria tipoArtilleria);
    
    /*
    Pre:~~
    Pos: Devuelve la lista de tropas
    */
    Lista<InfoTropa*>* getListaTropas();

    /*
    Pre: 
    Pos: Devuelve la lista de cartas para verlas y usarlas
    */
    Lista<tipos*>* getListaCartas();
    
    /*
    Pre: ~~
    Pos: Agrega un numero aleatorio del 0 al 5 a la lista de cartas
    */
    void addCarta();

    /*
    Pre: recibe un numero de carta
    Pos: devuelve 
    */
    tipos getCarta(int nroCarta);
};
#endif
