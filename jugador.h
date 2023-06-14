#ifndef JUGADOR
#define JUGADOR

#include "listaBase.h"
#include "tablero.h"
#include "cartas.h"



struct InfoTropa {
    int nroTropa;
    Artilleria tropa;
    Ubicacion posicion;
};

class Jugador {
private:
    int vidas;
    int numDeJugador;
    Lista<InfoTropa*>* tropas;
    Lista<Carta*>* cartas;

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
    Pre:
    Pos:
    */
    ~Jugador();
    
    /*
    Pre:Recibe un numero de soldado y su ubicacion
    Pos:agrega soldado a la lista de tropas del jugador
    */
    void agregarSoldado(Ubicacion posicionSoldado, int nroSoldado);

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
    Pre: 
    Pos: Devuelve la lista de cartas para verlas y usarlas
    */
    Lista<Carta*>* getListaCartas();

    /*
    Pre:~~
    Pos: Devuelve la lista de tropas
    */
    Lista<InfoTropa*>* getListaTropas();

    


    /*
    Pre: recive un numero de tropa y tipo de artilleria
    Pos: Devuelve si exite dicha tropa
    */
    bool tropaViva(int nroTropaPedida, Artilleria tipoArtilleria);
};
#endif
