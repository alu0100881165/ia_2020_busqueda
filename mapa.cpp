#include "mapa.hpp"

Mapa_t::Mapa_t(void):
    m_(0),
    n_(0),
    mapa_(0)
{}

Mapa_t::Mapa_t(int n, int m)
{
    set_m(m);
    set_n(n);
    set_mapa(n, m);
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

void Mapa_t::set_mapa(int n, int m)
{
    mapa_ = new char[n * m];
}

int Mapa_t::get_m(void)
{
    return m_;
}

int Mapa_t::get_n(void)
{
    return n_;
}

char* Mapa_t::get_mapa(void)
{
    return mapa_;
}