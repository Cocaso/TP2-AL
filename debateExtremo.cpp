#include "listaBase.h"
#include "cartas.h"
#include <iostream>

int main(){
    Lista<Carta*>* cartitas = new (Lista<Carta*>);
    Carta* cartota = new(Carta);
    for (unsigned int i=0; i<10; i++){
        cartitas->add(cartota);
    };


    for (unsigned int i=0; i<10; i++){
        std::cout << cartitas->get(i);
    }
}