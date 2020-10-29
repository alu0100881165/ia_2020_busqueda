#include "coche.hpp"
#include <iostream>
using namespace std;

Coche_t::Coche_t(void):
    posicion_()
{}

Coche_t::Coche_t(pair<int, int> posicion) // Inicializar valores
{
    setPosicion(posicion);
}

Coche_t::~Coche_t(void) // Destructor
{
    destroyCoche();           
}

void Coche_t::destroyCoche(void)  
{
    pair<int, int> posicion = {0, 0};
    setPosicion(posicion);
}

pair<int, int> Coche_t::getPosicion(void)
{
    return posicion_;
}

void Coche_t::setPosicion(pair<int, int> posicion)
{
    posicion_ = posicion;
}

ostream& Coche_t::write(ostream& os)
{
    os << "Las coordenadas donde se encuentra el coche son: \E[97m(" << posicion_.first << ", " << posicion_.second << ")." << endl;

    return os;
}