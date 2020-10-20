#include "mapa.hpp"

Mapa_t::Mapa_t(void):
    m_(3),
    n_(3)
{}

Mapa_t::Mapa_t(int n, int m)
{
    set_m(m);
    set_n(n);
}

Mapa_t::~Mapa_t(void)
{
    destroyMap();
}

void Mapa_t::destroyMap(void)
{
    set_m(0);
    set_n(0);
}

void Mapa_t::set_m(int m)
{
    m_ = m; 
}

void Mapa_t::set_n(int n)
{
    n_ = n;
}

int Mapa_t::get_m(void)
{
    return m_;
}

int Mapa_t::get_n(void)
{
    return n_;
}