
#include "coche.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Coche_t::Coche_t(void):
    posicion_(),
    camino_(),
    contNodosGenerados_(1)
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

int Coche_t::getContNodosGenerados(void)
{
    return contNodosGenerados_;
}

void Coche_t::setPosicion(pair<int, int> posicion)
{
    posicion_ = posicion;
}

void Coche_t::setAppendCamino(pair<int, int> posicion)
{
    camino_.push_back(posicion);
}

void Coche_t::setContNodosGenerados(int contNodosGenerados)
{
    contNodosGenerados_ = contNodosGenerados;
}

ostream& Coche_t::write(ostream& os)
{
    os << "Las coordenadas donde se encuentra el coche son: \E[97m(" << posicion_.first << ", " << posicion_.second << ")." << endl;

    return os;
}

// bool Coche_t::aStar(Mapa_t& mapa, bool heur)
// {
//     vector<pair<int, int>> openSet, closedSet; // Nodos que puedo visitar
//     bool terminado = false;
//     bool prueba = false;
//     pair<int, int> elegido, anterior;
//     int pos = 0;

//     if(heur)
//         mapa.getCeldaPos(posicion_).setF(heuristicaManhattan(posicion_, mapa.getDestino()));
//     else
//         mapa.getCeldaPos(posicion_).setF(heuristicaEuclidean(posicion_, mapa.getDestino()));

//     openSet.push_back(posicion_);
//     camino_.resize(0);
//     contNodosGenerados_ = 1;
    
//     while(1)
//     {
//         if(!terminado)
//         {
//             // cout << "No ha terminado" << endl;            
//             if(!openSet.empty())
//             {
//                 // recorrer el openset para decidir que celda es mejor (tiene menor coste)
//                 // cout << "Contenido del openSet" << endl;
//                 if(elegido != posicion_)
//                 {
//                     anterior = elegido;
//                     prueba = true;
//                 }
                
//                 pos = 0;
//                 for(int i = 0; i < openSet.size(); i++)
//                 {
//                     // cout << '(' << openSet[i].first << ", " << openSet[i].second << ')' << " | ";
//                     if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
//                     {
//                         pos = i;
//                     }
//                 }
//                 // cout << endl;
//                 // getchar();

//                 elegido = openSet[pos];
//                 // cout << "Elegimos: (" << elegido.first << ", " << elegido.second << ')' << endl;
//                 // if(prueba)
//                 // {
//                 //     cout << "Elegimos: (" << anterior.first << ", " << anterior.second << ')' << endl;
//                 // }
//                 if(anterior == elegido)
//                 {
//                     // for(int i = 0; i < openSet.size(); i++)
//                     // {
//                     //     cout << '(' << openSet[i].first << ", " << openSet[i].second << ')' << " | ";
//                     //     // if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
//                     //     // {
//                     //     //     pos = i;
//                     //     // }
//                     // }
//                     cout << "Esto es basura" << endl;
//                     cout << mapa.getCeldaPos(elegido).getF() << endl;
//                     for(int i = 0; i < mapa.getCeldaPos(elegido).getMovimientos().size(); i++)
//                     {
//                         cout << mapa.getCeldaPos(elegido).getMovimiento(i).first << ", " << mapa.getCeldaPos(elegido).getMovimiento(i).second << endl;
//                     }
//                     if(find(closedSet.begin(), closedSet.end(), elegido) != closedSet.end())
//                         cout << "ESTA EN EL PUTO CLOSED SET" << endl;
//                     if(find(openSet.begin(), openSet.end(), elegido) != openSet.end())
//                         cout << "TMB ESTA EN EL PUTO OPEN SET" << endl;
//                     usleep(1000000);
//                 }
                
//                 if(elegido == mapa.getDestino())
//                 {
//                     // getchar();
//                     // mapa.write(cout);
//                     cout << "El elegido es el destino." << endl;
//                     // Encontramos el camino
//                     terminado = true;

//                     pair<int, int> aux;

//                     // Recorrer todos los padres hasta que padre = 0, 0 || hasta llegar a la posición del coche.
//                     setAppendCamino(elegido);

//                     while(mapa.getCeldaPos(elegido).getPadre() != posicion_)
//                     {
//                         // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
//                         aux = mapa.getCeldaPos(elegido).getPadre();
//                         mapa.getCeldaPos(aux).setValor('&');
//                         setAppendCamino(aux);
//                         elegido = aux;
//                         // cout << "Bucle" << endl;
//                         // getchar();
//                     }
//                     setAppendCamino(posicion_);

//                     cout << "Acabo" << endl;

//                     return 1;
//                 }
//                 else
//                 {
//                     mapa.getCeldaPos(elegido).setValor('%');
//                     // Sacar del openSet y meter en el closedSet
//                     openSet.erase(openSet.begin() + pos);    //Begin devuelve 0
//                     closedSet.push_back(elegido);


//                     pair<int, int> celdaMovimiento;

//                     // Recorremos los posibles movimientos del nodo elegido
//                     Celda_t actual = mapa.getCeldaPos(elegido);
//                     for(int i = 0; i < actual.getMovimientos().size(); i++)
//                     {
//                         celdaMovimiento = actual.getMovimiento(i);

//                         // ¿Hemos visitado ya esa celda?
//                         // begin() y end() devuelven un iterador, find devuelve el valor si lo encuentra, y si no, devuelve un iterador end.
//                         if(!(find(closedSet.begin(), closedSet.end(), celdaMovimiento) != closedSet.end()))
//                         {
//                             // ¿Podemos llegar a esa celda desde otra celda?
//                             if(find(openSet.begin(), openSet.end(), celdaMovimiento) != openSet.end())
//                             {
//                                 if(mapa.getCeldaPos(celdaMovimiento).getG() > (actual.getG() + 1))
//                                 {
//                                      mapa.getCeldaPos(celdaMovimiento).setG(actual.getG() + 1);
//                                      mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
//                                 }
//                             }
//                             else // Lo metemos
//                             {
//                                 mapa.getCeldaPos(celdaMovimiento).setG(actual.getG() + 1);
//                                 openSet.push_back(celdaMovimiento);
//                                 mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
//                                 contNodosGenerados_++;
//                             }

//                             // Actualizar valores
//                             if(heur)
//                                 mapa.getCeldaPos(celdaMovimiento).setH(heuristicaManhattan(celdaMovimiento, mapa.getDestino()));
//                             else
//                                 mapa.getCeldaPos(celdaMovimiento).setH(heuristicaEuclidean(celdaMovimiento, mapa.getDestino()));

//                             mapa.getCeldaPos(celdaMovimiento).setF();
//                         }
//                     }
//                 }        
//             }
//             else
//             {
//                 // No hay un camino al destino
//                 terminado = true;
//                 cout << "\E[31mNo hay camino al destino." << endl;
//                 cout << endl;
//                 return 0;
//             }  
//             // mapa.write(cout);
//         }
//     }
// }

bool Coche_t::aStar(Mapa_t& mapa, bool heur)
{
    vector<pair<int, int>> openSet, closedSet; // Nodos que puedo visitar
    bool terminado = false;
    pair<int, int> elegido;
    int pos = 0;
    if(heur)
        mapa.getCeldaPos(posicion_).setF(heuristicaManhattan(posicion_, mapa.getDestino()));
    else
        mapa.getCeldaPos(posicion_).setF(heuristicaEuclidean(posicion_, mapa.getDestino()));
    
    openSet.push_back(posicion_);
    camino_.resize(0);
    contNodosGenerados_ = 1;
    
    while(!openSet.empty())
    {
        // recorrer el openset para decidir que celda es mejor (tiene menor coste)
        // cout << "Contenido del openSet" << endl;

        pos = 0;

        for(int i = 0; i < openSet.size(); i++)
        {
            // cout << '(' << openSet[i].first << ", " << openSet[i].second << ')' << " | ";
            if(mapa.getCeldaPos(openSet[i]).getF() < mapa.getCeldaPos(openSet[pos]).getF())
            {
                pos = i;
            }
        }
        // cout << endl;
        // getchar();

        elegido = openSet[pos];
        // cout << "Elegimos: (" << elegido.first << ", " << elegido.second << ')' << endl;
        // getchar();
        // mapa.getCeldaPos(elegido).setValor('%');
        
        if(elegido == mapa.getDestino())
        {
            // mapa.write(cout);
            cout << "El elegido es el destino." << endl;
            // Encontramos el camino
            terminado = true;

            pair<int, int> aux;

            // Recorrer todos los padres hasta que padre = 0, 0 || hasta llegar a la posición del coche.
            setAppendCamino(elegido);

            while(mapa.getCeldaPos(elegido).getPadre() != posicion_)
            {
                // cout << "El padre es: (" << mapa.getCeldaPos(elegido).getPadre().first << ", " << mapa.getCeldaPos(elegido).getPadre().second << ')' << endl;
                aux = mapa.getCeldaPos(elegido).getPadre();
                mapa.getCeldaPos(aux).setValor('&');
                setAppendCamino(aux);
                elegido = aux;
                // cout << "Bucle" << endl;
                // getchar();
            }
            setAppendCamino(posicion_);
            return 1;
        }
        else
        {
            mapa.getCeldaPos(elegido).setValor('%');
            // Sacar del openSet y meter en el closedSet
            openSet.erase(openSet.begin() + pos);    //Begin devuelve 0
            closedSet.push_back(elegido);

            pair<int, int> celdaMovimiento;

            // Recorremos los posibles movimientos del nodo elegido
            Celda_t actual = mapa.getCeldaPos(elegido);
            for(int i = 0; i < actual.getMovimientos().size(); i++)
            {
                celdaMovimiento = actual.getMovimiento(i);

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
                    else // Lo metemos
                    {
                        mapa.getCeldaPos(celdaMovimiento).setG(actual.getG() + 1);
                        openSet.push_back(celdaMovimiento);
                        mapa.getCeldaPos(celdaMovimiento).setPadre(elegido);
                        contNodosGenerados_++;
                    }

                    // Actualizar valores
                    if(heur)
                        mapa.getCeldaPos(celdaMovimiento).setH(heuristicaManhattan(celdaMovimiento, mapa.getDestino()));
                    else
                        mapa.getCeldaPos(celdaMovimiento).setH(heuristicaEuclidean(celdaMovimiento, mapa.getDestino()));

                    mapa.getCeldaPos(celdaMovimiento).setF();
                }
            }
        }        
    }
    if(elegido == mapa.getDestino())
    {
        // No hay un camino al destino
        terminado = true;
        cout << "El elegido es el destino." << endl;
        cout << endl;
        return 1;
    }
    return 0;
}

// Funcion heuristica Manhattan
int Coche_t::heuristicaManhattan(pair<int, int> actual, pair<int, int> destino)
{
    int x = abs(actual.first - destino.first); // Ejemplo: posicion_(1,1) , destino_(1,7) = 0 + 6 = 6
    int y = abs(actual.second - destino.second);
    
    
    return x + y;   // Hace falta un valor D que corresponde al coste mínimo para desplazarse a los nodos adyacentes, en nuestro caso vale 1 y no afecta
    //return d * (x + y);  ValorG(1) = d
}

int Coche_t::heuristicaEuclidean(pair<int, int> actual, pair<int, int> destino)
{
    int x = abs(actual.first - destino.first); 
    int y = abs(actual.second - destino.second);
    
    
    return sqrt(x * x + y * y);  
}
