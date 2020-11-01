
#include "coche.hpp"
#include <iostream>
using namespace std;

Coche_t::Coche_t(void):
    posicion_(),
    camino_()
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

bool Coche_t::aStar(Mapa_t& mapa)
{
    vector<pair<int, int>> openSet, closedSet; // Nodos que puedo visitar
    bool terminado = false;
    pair<int, int> elegido;
    int pos = 0;

    openSet.push_back(posicion_);

    while(1)
    {
        if(!terminado)
        {
            if(!openSet.empty())
            {
                // recorrer el openset para decidir que celda es mejor (tiene menor coste)
                for(int i = 0; i < openSet.size(); i++)
                {
                    if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
                    {
                        pos = i;
                    }
                }

                elegido = openSet[pos];
                
                if(elegido == mapa.getDestino())
                {
                    // Encontramos el camino
                    terminado = true;
                    return 1;
                }
                else
                {
                    // Sacar del openSet y meter en el closedSet
                    openSet.erase(openSet.begin() + pos);    //Begin devuelve 0
                    closedSet.push_back(elegido);         

                    pair<int, int> celdaMovimiento;

                    for(int i = 0; i < mapa.getCeldaPos(elegido).getMovimientos().size(); i++)
                    {
                        celdaMovimiento = mapa.getCeldaPos(elegido).getMovimiento(i);
                        if(!(find(closedSet.begin(), closedSet.end(), celdaMovimiento) != closedSet.end()))
                        {
                            if(find(openSet.begin(), openSet.end(), celdaMovimiento) != openSet.end())
                            {
                                if(mapa.getCeldaPos(celdaMovimiento).getG() > (mapa.getCeldaPos(elegido).getG() + 1))
                                {
                                    mapa.getCeldaPos(celdaMovimiento).setG(mapa.getCeldaPos(elegido).getG() + 1);
                                    mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                                }
                            }
                            else
                            {
                                mapa.getCeldaPos(celdaMovimiento).setG(mapa.getCeldaPos(elegido).getG() + 1);
                                openSet.push_back(celdaMovimiento);
                                mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                            }

                            // Actualizar valores
                            mapa.getCeldaPos(celdaMovimiento).setH(heuristicaManhattan(celdaMovimiento, mapa.getDestino()));
                            mapa.getCeldaPos(celdaMovimiento).setF();
                        }
                    }
                }        
            }
            else
            {
                // No hay un camino al destino
                terminado = true;
                cout << "No hay camino al destino." << endl;
                return 0;
            }   
        }
    }
}

// Funcion heuristica Manhattan
int Coche_t::heuristicaManhattan(pair<int, int> actual, pair<int, int> destino)
{
    int x = abs(actual.first - destino.first); // Ejemplo: posicion_(1,1) , destino_(1,7) = 0 + 6 = 6
    int y = abs(actual.second - destino.second);
    
    
    return x + y;   // Hace falta un valor D que corresponde al coste mínimo para desplazarse a los nodos adyacentes, en nuestro caso vale 1 y no afecta
    //return d * (x + y);  ValorG(1) = d
}