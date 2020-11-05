
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

vector<pair<int, int>> Coche_t::getCamino(void)
{
    return camino_;
}

void Coche_t::setPosicion(pair<int, int> posicion)
{
    posicion_ = posicion;
}

void Coche_t::setAppendCamino(pair<int, int> posicion)
{
    camino_.push_back(posicion);
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

    //cout << "Valor del openset: " << '(' << openSet[0].first << ", " << openSet[0].second << ')' << endl;

    //cout << "Comienza el bucle del algoritmo." << endl;

    while(1)
    {
        if(!terminado)
        {
            // cout << "No ha terminado" << endl;
            if(!openSet.empty())
            {
                //cout << "El openSet no está vacío. Tiene: " << openSet.size() << " elementos." << endl;
                // recorrer el openset para decidir que celda es mejor (tiene menor coste)
                //cout << "Elegimos el nuevo nodo." << endl;
                for(int i = 0; i < openSet.size(); i++)
                {
                    //cout << "Iteración: " << i << endl;
                    if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
                    {
                        pos = i;
                        //cout << "Se actualiza la posición " << pos << "." << endl;
                    }
                }

                elegido = openSet[pos];

                //cout << "El nodo elegido es (" << elegido.first << ", " << elegido.second << ')' << endl;
                
                if(elegido == mapa.getDestino())
                {
                    // cout << "El elegido es el destino." << endl;
                    // Encontramos el camino
                    terminado = true;

                    pair<int, int> aux;

                    // Recorrer todos los padres hasta que padre = 0, 0 || hasta llegar a la posición del coche.
                    // cout << "El nodo elegido es: (" << elegido.first << ", " << elegido.second << ')' << endl;
                    // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
                    // cout << "El inicio es: (" << posicion_.first << ", " << posicion_.second << ')' << endl;
                    setAppendCamino(elegido);
                    // setAppendCamino(mapa.getCeldaPos(elegido).getPadre());
                    while(mapa.getCeldaPos(elegido).getPadre() != posicion_)
                    {
                        // cout << "El nodo elegido es: (" << elegido.first << ", " << elegido.second << ')' << endl;
                        // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
                        aux = mapa.getCeldaPos(elegido).getPadre();
                        setAppendCamino(aux);
                        elegido = aux;
                    }
                    setAppendCamino(posicion_);

                    return 1;
                }
                else
                {
                    //cout << "El elegido no es el destino. Calculamos los nodos vecinos:" << endl;
                    // Sacar del openSet y meter en el closedSet
                    openSet.erase(openSet.begin() + pos);    //Begin devuelve 0
                    closedSet.push_back(elegido);

                    //cout << "Se elemina el nodo del openSet, que ahora tiene tamaño: " << openSet.size() << endl;
                    //cout << "Se añade el nodo al closedSet, que ahora tiene tamaño: " << closedSet.size() << endl;

                    pair<int, int> celdaMovimiento;

                    // Recorremos los posibles movimientos del nodo elegido
                    Celda_t actual = mapa.getCeldaPos(elegido);
                    //Celda_t movimiento;
                    for(int i = 0; i < actual.getMovimientos().size(); i++)
                    {
                        celdaMovimiento = actual.getMovimiento(i);
                        // cout << "La posición de la celda de movimiento es: (" << mapa.getCeldaPos(elegido).getMovimiento(i).first << ", " << mapa.getCeldaPos(elegido).getMovimiento(i).second << ')' << endl;
                        //movimiento = mapa.getCeldaPos(celdaMovimiento);

                        // ¿Hemos visitado ya esa celda?
                        // begin() y end() devuelven un iterador, find devuelve el valor si lo encuentra, y si no, devuelve un iterador end.
                        if(!(find(closedSet.begin(), closedSet.end(), celdaMovimiento) != closedSet.end()))
                        {
                            // ¿Podemos llegar a esa celda desde otra celda?
                            if(find(openSet.begin(), openSet.end(), celdaMovimiento) != openSet.end())
                            {
                                if(mapa.getCeldaPos(celdaMovimiento).getG() > (actual.getG() + 1))
                                {
                                    mapa.getCeldaPos(celdaMovimiento).setG(actual.getG() + 1);
                                    mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                                }
                            }
                            else
                            {
                                mapa.getCeldaPos(celdaMovimiento).setG(actual.getG() + 1);
                                openSet.push_back(celdaMovimiento);
                                mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                            }

                            mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                            
                            // cout << "El elegido es: (" << elegido.first << ", " << elegido.second << ')' << endl;

                            // cout << "El movimiento es: (" << celdaMovimiento.first << ", " << celdaMovimiento.second << ')' << endl;
                            // cout << "El padre de movimiento es: (" << mapa.getCeldaPos(celdaMovimiento).getPadre().first << ", " << mapa.getCeldaPos(celdaMovimiento).getPadre().second << ')' << endl;
                            // cout << "El padre de la celda movimiento es: (" << mapa.getCeldaPos(celdaMovimiento).getPadre().first << ", " << mapa.getCeldaPos(celdaMovimiento).getPadre().second << ')' << endl;

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

// bool Coche_t::aStar2(Mapa_t& mapa)
// {
//     vector<pair<int, int>> openSet, closedSet; // Nodos que puedo visitar
//     bool terminado = false;
//     pair<int, int> elegido;
//     int pos = 0;

//     openSet.push_back(posicion_);

//     //cout << "Valor del openset: " << '(' << openSet[0].first << ", " << openSet[0].second << ')' << endl;

//     //cout << "Comienza el bucle del algoritmo." << endl;

//     while(1)
//     {
//         if(!terminado)
//         {
//             // cout << "No ha terminado" << endl;
//             if(!openSet.empty())
//             {
//                 //cout << "El openSet no está vacío. Tiene: " << openSet.size() << " elementos." << endl;
//                 // recorrer el openset para decidir que celda es mejor (tiene menor coste)
//                 //cout << "Elegimos el nuevo nodo." << endl;
//                 for(int i = 0; i < openSet.size(); i++)
//                 {
//                     //cout << "Iteración: " << i << endl;
//                     if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
//                     {
//                         pos = i;
//                         //cout << "Se actualiza la posición " << pos << "." << endl;
//                     }
//                 }

//                 elegido = openSet[pos];

//                 //cout << "El nodo elegido es (" << elegido.first << ", " << elegido.second << ')' << endl;
                
//                 if(elegido == mapa.getDestino())
//                 {
//                     cout << "El elegido es el destino." << endl;
//                     // Encontramos el camino
//                     terminado = true;

//                     pair<int, int> aux;

//                     // Recorrer todos los padres hasta que padre = 0, 0 || hasta llegar a la posición del coche.
//                     // cout << "El nodo elegido es: (" << elegido.first << ", " << elegido.second << ')' << endl;
//                     // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
//                     // cout << "El inicio es: (" << posicion_.first << ", " << posicion_.second << ')' << endl;
//                     setAppendCamino(elegido);
//                     while(mapa.getCeldaPos(elegido).getPadre() == posicion_)
//                     {
//                         // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
//                         aux = mapa.getCeldaPos(elegido).getPadre();
//                         setAppendCamino(elegido);
//                         elegido = aux;
//                     }
//                     setAppendCamino(posicion_);

//                     return 1;
//                 }
//                 else
//                 {
//                     //cout << "El elegido no es el destino. Calculamos los nodos vecinos:" << endl;
//                     // Sacar del openSet y meter en el closedSet
//                     openSet.erase(openSet.begin() + pos);    //Begin devuelve 0
//                     closedSet.push_back(elegido);

//                     //cout << "Se elemina el nodo del openSet, que ahora tiene tamaño: " << openSet.size() << endl;
//                     //cout << "Se añade el nodo al closedSet, que ahora tiene tamaño: " << closedSet.size() << endl;

//                     //pair<int, int> celdaMovimiento;

//                     // Recorremos los posibles movimientos del nodo elegido
//                     Celda_t actual = mapa.getCeldaPos(elegido);
//                     //Celda_t movimiento;

//                     // cout << "Celda actual: (" << elegido.first << ", " << elegido.second << ')' << endl;

//                     for(int i = 0; i < mapa.getCeldaPos(elegido).getMovimientos().size(); i++)
//                     {
//                         // cout << "Movimiento " << i << "celda movimiento: (" << mapa.getCeldaPos(elegido).getMovimiento(i).first << ", " << mapa.getCeldaPos(elegido).getMovimiento(i).second << ')' << endl;

//                         //celdaMovimiento = actual.getMovimiento(i);
//                         cout << "La posición de la celda de movimiento es: (" << mapa.getCeldaPos(elegido).getMovimiento(i).first << ", " << mapa.getCeldaPos(elegido).getMovimiento(i).second << ')' << endl;
//                         //movimiento = mapa.getCeldaPos(celdaMovimiento);

//                         // ¿Hemos visitado ya esa celda?
//                         // begin() y end() devuelven un iterador, find devuelve el valor si lo encuentra, y si no, devuelve un iterador end.
//                         if(!(find(closedSet.begin(), closedSet.end(), mapa.getCeldaPos(elegido).getMovimiento(i)) != closedSet.end()))
//                         {
//                             // ¿Podemos llegar a esa celda desde otra celda?
//                             if(find(openSet.begin(), openSet.end(), mapa.getCeldaPos(elegido).getMovimiento(i)) != openSet.end())
//                             {
//                                 if(mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).getG() > (mapa.getCeldaPos(elegido).getG() + 1))
//                                 {
//                                     mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setG(mapa.getCeldaPos(elegido).getG() + 1);
//                                     mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setPadre(elegido);
//                                 }
//                             }
//                             else
//                             {
//                                 mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setG(mapa.getCeldaPos(elegido).getG() + 1);
//                                 openSet.push_back(mapa.getCeldaPos(elegido).getMovimiento(i));
//                                 mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setPadre(elegido);
//                             }

//                             mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setPadre(elegido);
                            
//                             cout << "El elegido es: (" << elegido.first << ", " << elegido.second << ')' << endl;

//                             cout << "El movimiento es: (" << mapa.getCeldaPos(elegido).getMovimiento(i).first << ", " << mapa.getCeldaPos(elegido).getMovimiento(i).second << ')' << endl;
//                             cout << "El padre de movimiento es: (" << mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).getPadre().first << ", " << mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).getPadre().second << ')' << endl;
//                             cout << "El padre de la celda movimiento es: (" << mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).getPadre().first << ", " << mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).getPadre().second << ')' << endl;

//                             // Actualizar valores
//                             mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setH(heuristicaManhattan(mapa.getCeldaPos(elegido).getMovimiento(i), mapa.getDestino()));
//                             mapa.getCeldaPos(mapa.getCeldaPos(elegido).getMovimiento(i)).setF();
//                         }
//                     }
//                 }        
//             }
//             else
//             {
//                 // No hay un camino al destino
//                 terminado = true;
//                 cout << "No hay camino al destino." << endl;
//                 return 0;
//             }   
//         }
//     }
// }

// Funcion heuristica Manhattan
int Coche_t::heuristicaManhattan(pair<int, int> actual, pair<int, int> destino)
{
    int x = abs(actual.first - destino.first); // Ejemplo: posicion_(1,1) , destino_(1,7) = 0 + 6 = 6
    int y = abs(actual.second - destino.second);
    
    
    return x + y;   // Hace falta un valor D que corresponde al coste mínimo para desplazarse a los nodos adyacentes, en nuestro caso vale 1 y no afecta
    //return d * (x + y);  ValorG(1) = d
}