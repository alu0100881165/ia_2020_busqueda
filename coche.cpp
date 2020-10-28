#include "coche.hpp"
#include<iostream>
using namespace std;

Coche_t::Coche_t(void):
    posicion_(),
    coche_()
{}

Coche_t::Coche_t(pair<int, int> posicion) // Inicializar valores
{
    setCoche(posicion);
}

Coche_t::~Coche_t(void) // Destructor
{
    destroyCoche();           
}

void Coche_t::destroyCoche(void)  
{
    //posicion = (0, 0);
    setCoche(posicion_);
}
pair<int, int> Coche_t::getCoche(void)
{
    return posicion_;
}

void Coche_t::setCoche(pair<int, int> posicion)
{
    posicion_ = posicion;
}

int Coche_t::GetCochePos(pair<int, int> posicion)
{
    return i * getCoche() + j;
}

ostream& Coche_t::write(ostream& os)
{
    for(int i = 0; i < getCoche(); i++)
    {
        for(int j = 0; j < getCoche(); j++)
        {
            coche_[getCochePos(i,j)].write(os);
        }
        cout << endl;
    }
    cout << endl;

    return os;
}
