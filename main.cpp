#include "digiBattle.h"
using namespace std;



int main(){
    DigiBattle* Juego = new(DigiBattle);
    int opcion;
    
    cout << "Bienvenido a digibattle"<<endl;
    cout << "1: Empezar juego"<<endl;
    cout << "2: Salir"<<endl;
    do {
       cout << "Ingrese opcion :" << endl;
       cin >> opcion;
    }while(opcion != 1 && opcion != 2);
    
    if (opcion == 1){
        Juego->iniciarJuego();
        Juego->turno();
    }else{
        cout<<"Adios"<<endl;
    }

    
    delete(Juego);
    return 0;
}
