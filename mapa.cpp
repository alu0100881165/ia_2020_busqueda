#include "mapa.hpp"

Mapa_t::Mapa_t(void):
    m_(0),
    n_(0),
    mapa_(0)
{}

Mapa_t::Mapa_t(int n, int m)
{
    setM(m);
    setN(n);
    setMapa(n, m);
}

Mapa_t::~Mapa_t(void)
{
    destroyMapa();
}

void Mapa_t::destroyMapa(void)
{
    setM(0);
    setN(0);
}

int Mapa_t::getM(void)
{
    return m_;
}

int Mapa_t::getN(void)
{
    return n_;
}

Celda_t* Mapa_t::getMapa(void)
{
    return mapa_;
}

int Mapa_t::getMapaPos(int i, int j)
{
    return (i + j * getN());
}

void Mapa_t::setM(int m)
{
    m_ = m; 
}

void Mapa_t::setN(int n)
{
    n_ = n;
}

void Mapa_t::setMapa(int n, int m)
{
    mapa_ = new Celda_t[n * m];
    rellenarMapa();

}

fstream& Mapa_t::setMapa(int n, int m, fstream& fichero)
{
    setN(n);
    setM(m);
    setMapa(n, m);
    rellenarMapa();
    rellenarObstaculos(fichero);
    return fichero;
}

void Mapa_t::rellenarMapa(void)
{
    vector<int> aux = {1, 1, 1, 1};
    for(int i = 0; i < getN(); i++)
    {
        for(int j = 0; j < getM(); j++)
        {
            if(i == 0 || j == 0 | i == (getN() - 1) | j == (getM() -1))
            {
                mapa_[getMapaPos(i, j)].setValor('#');
                mapa_[getMapaPos(i, j)].setMovimientos(aux);
            }
            else
                mapa_[getMapaPos(i, j)].setValor('.');
        }
    }
}

fstream& Mapa_t::rellenarObstaculos(fstream& fichero)
{
    pair<int, int> aux;
    while(!fichero.eof())
    {
        fichero >> aux.first >> aux.second;

        mapa_[getMapaPos(aux.first, aux.second)].setValor('$');
    }

    for(int i = 1; i < (getN() - 1); i++)
    {
        for (int j = 1; j < (getM() - 1); j++)
        {
            rellenarMovimientos(i, j);
            /*
            cout << "La celda " << i << ',' << j << ": ";
            for(int k = 0; k < 4; k++)
                cout << mapa_[getMapaPos(i, j)].getMovimiento(k) << ' ';
            cout << endl;
            */
        }
    }
    
    return fichero;
}

void Mapa_t::rellenarMovimientos(int i, int j)
{
    /*vector<int> aux = {0, 0, 0, 0};

    if(mapa_[getMapaPos(i, j--)].getValor() == '$' || mapa_[getMapaPos(i, j--)].getValor() == '#')  // izquierda
    {
        cout << "Izquierda:  " << mapa_[getMapaPos(i, j--)].getValor() << endl;
        aux[0] = 1;
    }

    if(mapa_[getMapaPos(i--, j)].getValor() == '$' || mapa_[getMapaPos(i--, j)].getValor() == '#')    // arriba
    {
        cout << "arriba: " << mapa_[getMapaPos(i--, j)].getValor() << endl;
        aux[1] = 1;
    }

    if(mapa_[getMapaPos(i, j++)].getValor() == '$' || mapa_[getMapaPos(i, j++)].getValor() == '#')  // derecha
    {
        cout << "derecha: " << mapa_[getMapaPos(i, j++)].getValor() << endl;
        aux[2] = 1;
    }

    if(mapa_[getMapaPos(i++, j)].getValor() == '$' || mapa_[getMapaPos(i++, j)].getValor() == '#')  // abajo
    {
        cout << "abajo: " << mapa_[getMapaPos(i++, j)].getValor() << endl;
        aux[3] = 1;
    }

    mapa_[getMapaPos(i, j)].setMovimientos(aux);*/
}

ostream& Mapa_t::write(ostream& os)
{
    cout << "Número de filas: " << getN() << " Número de columnas: " << getM() << endl;
    cout << "Mapa: " << endl;

    for(int i = 0; i < getN(); i++)
    {
        for(int j = 0; j < getM(); j++)
        {
            mapa_[getMapaPos(i, j)].write(os);   
        }
        cout << endl;
    }
    cout << endl;

    return os;
}