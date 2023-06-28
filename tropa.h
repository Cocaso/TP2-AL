#ifndef TROPA
#define TROPA

#include "tropa.cpp"


struct Ubicacion{
    int x;
    int y;
    int z;
};

class Tropa {
    private:
    enum Artilleria {
        VACIO,
        SOLDADO,
        AVION,
        BARCO,
        MINA
    };
    int nroTropa;
    Artilleria tropa;
    Ubicacion posicion;
    int vidasBarco;

    public:


    Tropa(Ubicacion posicionTropa, int nroTropa, Artilleria tipoTropa);

    ~Tropa();

    int getTipoTropa();

    int getNroTropa();

    Ubicacion getPosicion();

    void setTipoTropa();

    void setNroTropa();

    void setPosicion();



};


#endif
