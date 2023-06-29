#ifndef TROPA
#define TROPA

#include "casillero.h"
#include "ubicacion.h"

/*
struct Ubicacion{
    int x;
    int y;
    int z;
};
*/
class Tropa {
    private:
    /*
    enum Artilleria {
        VACIO,
        SOLDADO,
        AVION,
        BARCO,
        MINA
    };
    */
    int nroDeTropa;
    Artilleria tipoDeTropa;
    Ubicacion ubicacion;
    int vidasBarco;

    public:


    Tropa(Ubicacion ubicacionTropa, int nroTropa, Artilleria tipoTropa);

    ~Tropa();

    Artilleria getTipoTropa();

    int getNroTropa();

    Ubicacion getUbicacion();

    int getVidasBarco();


    void setTipoTropa(Artilleria tipoTropa);

    void setNroTropa(int nroTropa);

    void setUbicacion(Ubicacion ubicacionNueva);

    void bajarVidasBarco();


};


#endif
