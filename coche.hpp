#pragma once

#include <utility>

using namespace std;

class Coche_t
{
    private:   
        pair<int, int> posicion_;
        // vector de movimientos -> almacene el camino minimo.
        void destroyCoche(void);

    public:
        Coche_t();
        ~Coche_t();
        
        pair<int, int> getCoche(pair<int, int> posicion); // Getter
        void setCoche(pair<int, int> posicion); // Setter
};