#ifndef UBICACION
#define UBICACION

class Ubicacion{
    private:
    int x;
    int y;
    int z;

    public:

    Ubicacion();

    Ubicacion(int x, int y, int z);

    int getX();

    int getY();

    int getZ();

    void setX(int x);

    void setY(int y);

    void setZ(int z);

    void setUbicacion(int x, int y, int z);

    void setUbicacion(Ubicacion ubicacionNueva);

};


#endif