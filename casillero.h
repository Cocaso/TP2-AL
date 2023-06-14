#ifndef CASILLERO
#define CASILLERO


enum Terreno {
    TIERRA,
    AGUA,
    AIRE
};

enum Artilleria {
    VACIO,
    SOLDADO,
    MINA,
    AVION,
    BARCO          //tiene municion, si se le termina se inhabilita (inutil)
};

struct Contenido {
    int jugador;
    int numSoldado;
    int municionDelBarco;
    Artilleria artilleria;
    int turnosInactivo = 0;
};

class Casillero {
private:

    Terreno terreno;
    Contenido* contenido;

public:
    /*
    Pre:~~
    Pos: Construye un casillero vacío con AIRE
    */
    Casillero();

    /*
    Pre:~~
    Pos: Bob el destructor
    */
    ~Casillero();

    /*
    Pre:~~
    Pos: Cambia el terreno a TIERRA o AGUA según el template del mapa
    */
    void cambiarTerreno(int terreno);

    /*
    Pre:~~
    Pos: Desactiva la casilla por la cantidad de turnos correspondientes y vacía el casillero
    */
    void desactivarCasilla(int cantidadTurnosCasillaInactiva);

    /*
    Pre:
    Pos: Disminuye 1 turno de inactividad , y ademas devuelve true si llego a 0 la cantidad inactiva
    */
    bool disminuirTurnosInactivo();

    /*
    Pre:~~
    Pos: Coloca la artillería indicada (sirve para cambiar a VACIO)
    */
    void ponerArtilleria(Artilleria artilleria);

    /*
    Pre: Recibe numero jugador y tipo de artilleria
    Pos: Coloca ambos datos en el struct
    */
    void ponerArtilleria(Artilleria artilleria, int numJugador);

    /*
    Pre: Recibe número jugador, tipo de artilleria y númeo de soldado
    Pos: Coloca todos los datos en el struct (solo para SOLDADO)
    */
    void ponerArtilleria(Artilleria artilleria, int numJugador, int numSoldado);

    /*
    Pre: Recibe el tipo de artilleria que se quiere colocar
    Pos: Devuelve true si se puede colocar o false y cout si no se puede
    */
    bool comprobarTerreno(Artilleria unidad);
    
    /*
    Pre: Recibe un casillero
    Pos: Devuelve si la casilla esta activa o inactiva
    */
    bool comprobarEstado();
    /*
    Pre: ~~
    Pos: Devuelve el tipo de artilleria en terreno
    */
    Artilleria devolverArtilleria();

    /*
    Pre: ~~
    Pos: Devuelve , en caso de que haya una artilleria , a que jugador pertenece
    */
    int devolverNroJugador();

    /*
    Pre: ~~
    Pos: Devuelve , en caso de que haya un soldado , que numero de soldado es
    */
    int devolverNroSoldado();

    /*
    Pre: ~~
    Pos: Devuelve , en caso de que haya un soldado , que numero de soldado es
    */
    Terreno devolverTerreno();
};



#endif