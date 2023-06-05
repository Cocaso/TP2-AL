#ifndef CASILLERO
#define CASILLERO

enum contenido {
    tierra,
    augua,
    aire,
    avion,
    barco,
    soldado
};

class Casillero {
private:
    contenido casilla;
    bool casillaActiva;
public:
    Casillero(/* args */);
    ~Casillero();
};

Casillero::Casillero(/* args */) {
    this->casilla = aire;
    this->casillaActiva = true;
}

Casillero::~Casillero() {
}






#endif