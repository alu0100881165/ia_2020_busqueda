#pragma once

#include <iostream>
#include <cstdio>

using namespace std;

class Coche_t
{
    private:   
        pair<int, int> posicion_;
        // vector de movimientos -> almacene el camino minimo.
        void destroyCoche(void);

    public:
        Coche_t();   // Constructor
        Coche_t(pair<int, int> posicion); // Constructor de copia
        ~Coche_t();  // Destructor
        
        pair<int, int> getPosicion(void);  // Getter posiciones

        void setPosicion(pair<int, int> posicion); // Setter posiciones

        ostream& write(ostream& os);  
};