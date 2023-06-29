#include "digiBattle.h"
using namespace std;



int main(){
    DigiBattle* Juego = new(DigiBattle);
    int opcion;
    int empezarJuego = 1;
    int salir = 2;

    cout << "-------------------------------------"<<endl;
    cout << "Bienvenido a digibattle"<<endl;
    cout << "1: Empezar juego"<<endl;
    cout << "Cualquier otra cosa para salir c:"<<endl;
    cout << "-------------------------------------"<<endl;
    
    do {
      cout << "Ingrese opcion :" << endl;
      cin >> opcion;
    }while(isdigit(opcion) && opcion != empezarJuego && opcion != salir);
    
    if (opcion == empezarJuego){
       Juego->iniciarJuego();
       Juego->turno();
    }else if(isdigit(opcion)){
        cout << "Por favor, ingrese un numero"<<endl;
        cin >> opcion;
    }else{
      cout<<"Adios"<<endl;
    }
    
    
    delete(Juego);
    return 0;
}
