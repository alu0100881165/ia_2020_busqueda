/* Universidad de La Laguna, Escuela Superior de Ingeniería y Tecnología.
*  INTELIGENCIA ARTIFICIAL: **PRÁCTICA DE BÚSQUEDA**.
*  Integrantes del grupo:
*  - Daniel Nuez Wehbe
*  - José Javier Díaz González
*  - Ricardo Fariña Mesa 
*
*  Enunciado del problema:
* 
*      Un coche autónomo se puede suponer rectangular de dimensiones M x N 
*   y constituido por celdas libres y ocupadas, donde el coche puede efectuar acciones 
*   de movimiento, una cada vez, desde la casilla actual a una de las 4-vecinas 
*   (Norte, Sur, Este u Oeste) que no se encuentre ocupada. Las casillas ocupadas 
*   corresponden a obstáculos. Las casillas libres corresponden con celdas libres 
*   de obstáculos.
*/

#include "coche.hpp"

#include <string>
#include <cstdlib>
#include <chrono>

bool casosInt(int& valor)   // Cuando haces una entrada revisa la entrada
{
    cin >> valor;
    bool casos = cin.good(); // Devuelve 0 si la secuencia no existe 
    if (!casos)
    {
        //system("clear");

        cin.clear();    // Limpiamos
        cin.ignore();   // Eliminamos el contenido
        cout << endl << "\E[31mLa respuesta no ha sido un numero\E[39m" << endl;
    }

    return !casos;
}

pair<int, int> crearVehiculo(Mapa_t mapa, int filas, int columnas)
{
    pair<int, int> v;
    cout << endl << "\E[93mDETERMINACIÓN DEL VEHÍCULO.\E[93m"<<endl;
        do
        {
            cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m del vehículo: \E[97m";      // filas -> naranja
            cin >> v.first;
            cout << "\E[94m- Introduzca la posición \E[97mj\E[94m del vehículo: \E[97m";      // columnas -> naranja
            cin >> v.second;

            if(v.first > 0 && v.second > 0 && v.first < (filas - 1) && v.second < (columnas - 1))           // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
            {                                                                                               // Arriba, izquierda, abajo y derecha.
                mapa.rellenarManual(v.first, v.second, '&');                                                // Guarda en la posición pair 'v' el vehículo, '&'               
            }
            else
            {
                cout << endl << "\E[31m--> Error de posición: Introduzca el vehículo en una posición \E[93mviable \E[93m\E[97m(no en los bordes)." << endl;
            }
        } 
        while (v.first <= 0 || v.second <= 0 || v.first >= (filas - 1) || v.second >= (columnas - 1));      // if(-1)
    
    return v;
}

void crearAleatorio(Mapa_t& mapa, Coche_t& coche)
{
    int tam = ((mapa.getN() * mapa.getM()) * 2) / 100;      // Ejemplo: 10x10 10% tam = 10

    srand(time(NULL)); // Caso random = NULL

    pair<int, int> v = {1, 1};
    pair<int, int > d, o;

    for(int i = 0; i < tam; i++)
    {   
        do
        {
            o.first = rand() % mapa.getN(); // caso random first
            o.second = rand() % mapa.getM(); // caso random second
        }
        while (o.first <= 0 || o.second <= 0 || o.first >= (mapa.getN() - 1) || o.second >= (mapa.getM() - 1) || v == d);
                
        if(i == 0)
        {
            v = o;
            coche.setPosicion(v);
        }
        else
        {
            d = o;
        }
    }
    // cout << "Valor de coche: (" << v.first << ", " << v.second << ')' << endl;
    // cout << "Valor de coche: (" << d.first << ", " << d.second << ')' << endl;
    mapa.rellenarCoche(v, d);
    // mapa.write(cout);
    // getchar();
}

pair<int, int> crearDestino(Mapa_t mapa, int filas, int columnas, pair<int, int> v)
{
    pair<int, int> d;

    cout << endl << "\E[93mDETERMINACIÓN DEL DESTINO.\E[93m" << endl;
        do
        {
            cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m del destino: \E[97m";      // filas -> naranja
            cin >> d.first;
            
            cout <<  "\E[94m- Introduzca la posición \E[97mj\E[94m del destino: \E[97m";      // columnas -> naranja
            cin >> d.second;

            if(d.first > 0 && d.second > 0 && d.first < (filas - 1) && d.second < (columnas - 1) && d != v)         // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
            {                                                                                                       // Arriba, Izquierda, abajo y derecha, además de que no esté en la posición del vehículo.
                mapa.rellenarManual(d.first, d.second, '=');                                                        // Guarda en la posición pair 'd' el destino, '='.
            }
            else
            {
                cout << endl << "\E[31m--> Error de posición: Introduzca el destino en una posición válida. \E[31m" << endl;
            }
        } 
        while (d.first <= 0 || d.second <= 0 || d.first >= (filas - 1) || d.second >= (columnas - 1) || d == v);    // if(-1)

    return d;
}

int main(void)
{
    int opcion;
    int filas, columnas, porcentajes_obstaculos, numero_porcentajes;
    fstream ficheroEntrada;     // Variable que almacena el fichero del que se lee
    string nombreFichero;       // Variable que almacena el nombre del fichero para después abrirlo
    pair<int, int> o, v, d;     // obstáculo, vehículo y destino
    Mapa_t mapa;                // Mapa vacío
    Coche_t coche;              // Coche declarado a posición (0, 0)

    // PARA TESTEAR LOS MAPAS
    ofstream outfile;

    cout << "\nPractica 1: INTELIGENCIA ARTIFICIAL. PRÁCTICA DE BÚSQUEDA.\n";
    do
    {
        cout << "\n\E[32m¿Desea leer desde fichero? \e[95m\e[1m(0 NO, 1 SI)\e[0m\e[95m: \E[97m"; // Si el usuario presiona 1 lee desde fichero, no está hecho de momento la opción manual
        cin >> opcion;
        
        // system("clear");
    }
    while (opcion !=0 && opcion != 1);
    
    if(opcion)
    {
        do
        { 
            cout << endl << "\E[93m- Introduzca el nombre del fichero: \E[97m";        // filas -> naranja 
            cin >> nombreFichero;

            ficheroEntrada.open(nombreFichero.c_str(), fstream::in);    // Se abre el fichero de entrada
            if(ficheroEntrada.is_open())    // Comprobamos que el fichero se haya abierto bien
            {
                ficheroEntrada >> filas >> columnas;    // Las dos primeras líneas del fichero son las filas y las columnas, las almacenamos en sus respectivas variables
                
                ficheroEntrada >> v.first >> v.second;
                ficheroEntrada >> d.first >> d.second;

                coche.setPosicion(v);
                // mapa.setDestino(d);

                mapa.setMapa(filas, columnas, ficheroEntrada, v, d);  // Se pasa al método setMapa lo necesario para construir todo el mapa sin punto de salida ni de llegada
            }
            else    // En caso de error al abrir el fichero se indica al usuario y termina la ejecución del programa
            {
                cout << endl << "\E[31m--> Error: El fichero no existe o no tiene permisos\E[31m" << endl;
            }
        }    
        while(ficheroEntrada.is_open() != 1);
    }
    
    // cout << endl<<"\E[43mFUNCIÓN HEURÍSTICA.\E[49m"<<endl;
    
    // while(true)
    // {    
    //     do{
    //         cout << endl <<"1.-Distancia de Manhattan.";
    //         cout << endl <<"2.-Distancia de Euclidean.";
    //         cout << endl <<"\E[31mIndique con un valor numérico la función heurística que desea emplear (1|2|3): \E[97m";
    //     }
    //     while (casosInt(heuristica))
    // }

    else    // Opción manual
    {      
        // outfile.open("prueba.txt", ofstream::out | ofstream::trunc);
        cout << endl << "\E[93mDIMENSIONES DEL TABLERO.\E[93m" << endl;       // cian negrita    

        do
        {
            cout << endl << "\E[94m- Introduzca el número de \E[97mfilas\E[94m de la tabla \e[92m\e[4m(>= 4)\e[0m: \E[97m";        // filas -> naranja
        } 
        while (casosInt(filas) || filas < 4);

        do
        {
            cout << "\E[94m- Introduzca el número de \E[97mcolumnas\E[94m de la tabla \e[92m\e[4m(>= 4)\e[0m: \E[97m";      // columnas -> naranja
        } 
        while (casosInt(columnas) || columnas < 4);

        mapa.setN(filas);
        mapa.setM(columnas);
        mapa.setMapa(filas, columnas);

        //bool opcion2;
        do
        {
            cout << endl << "\E[32m¿Desea introducir manualmente los obstáculos o generarlos aleatoriamente? \e[95m\e[1m(0 Aleatorio, 1 Manual)\e[95m\e[0m: \E[97m";      // columnas -> naranja
            cin >> opcion;
        }
        while (opcion !=0 && opcion != 1);

        v = crearVehiculo(mapa, filas, columnas);
        d = crearDestino(mapa, filas, columnas, v);
        coche.setPosicion(v);
        mapa.setDestino(d);
        
        if(opcion) //  manual obstaculos
        { 
            
            // system("clear");

            cout << endl << "\E[93mDETERMINACIÓN DE OBSTÁCULOS.\E[93m"<<endl;

            do
            {
                cout << endl << "\E[91m-> (Introduzca \E[97m0 0\E[91m para salir) \E[91m" << endl;      
                cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m de un obstáculo: \E[97m";      
                cin >> o.first;
                cout  << "\E[94m- Introduzca la posición \E[97mj\E[94m de un obstáculo: \E[97m";      
                cin >> o.second;
                               
                if(d.first > 0 && d.second > 0 && d.first < (filas - 1) && d.second < (columnas - 1) && o != v && o != d && '#' != mapa.getMapa()[mapa.getMapaPos(o.first, o.second)].getValor())   // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
                {                                                                                                           // Arriba, Izquierda, abajo y derecha, además de que no esté en la posición del vehículo ni del destino.
                    mapa.rellenarManual(o.first, o.second, '#');  
                    // system("clear");                                                                                        // Guarda en la posición pair 'o' un obstáculo, '#'.                                                                           
                }

                else
                {
                    cout << endl << "\E[31m--> Error de posición: Introduzca el obstáculo en una posición válida. \E[31m" << endl;
                }
            } 
            while ((o.first != 0) && (o.second != 0));                                                                      // Si ambas posiciones del pair 'o' son 0, se sale del bucle.
                
            for(int i = 1; i < (filas - 1); i++)       
            {
                for (int j = 1; j < (columnas - 1); j++)
                {
                    if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
                    {
                        mapa.rellenarMovimientos(i, j);     
                    }
                }
            }
        }
        else // Caso aleatorios 
        {               
            cout << endl << "\E[93mDETERMINACIÓN DE OBSTÁCULOS.\E[93m"<<endl;
            do
            {
                do
                {
                    cout << endl << "\E[94mIntroduza el \E[97mporcentaje\E[94m de obstaculos que desee: \E[97m";    // El usuario introduce un %
                } 
                while(casosInt(porcentajes_obstaculos));

                if(porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100)
                {
                    cout << endl << "\E[31m--> Error: Introduzca un porcentaje dentro del rango \E[97m0-100\E[31m.\E[39m" << endl;  // Error rango
                }
                
            } while (porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100);  // Hasta < 0 o > 100
            

            int tam = ((filas * columnas) * porcentajes_obstaculos) / 100;      // Ejemplo: 10x10 10% tam = 10

            srand(time(NULL)); // Caso random = NULL

            for(int i = 0; i < tam; i++)
            {   
                do
                {
                    o.first = rand() % filas; // caso random first
                    o.second = rand() % filas; // caso random second
                }
                while (o.first <= 0 || o.second <= 0 || o.first >= (filas - 1) || o.second >= (columnas - 1) || o == v || o == d);
                    
                mapa.rellenarManual(o.first, o.second, '#');
            }

            for(int i = 1; i < (filas - 1); i++)       
            {
                for (int j = 1; j < (columnas - 1); j++)
                {
                    if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
                    {
                        //cout << "Posición: (" << i << ", " << j << ')' << endl;
                        mapa.rellenarMovimientos(i, j);     
                    }
                }
            }
        }
    }

    // system("clear");

    mapa.write(cout);   // Al final, se imprime por pantalla el contenido del mapa.    

    vector<pair<int, int>> resultado;

    auto t1 = chrono::high_resolution_clock::now();
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();

    cout << "\E[93m\e[7mA* con heurística Manhattan.\E[93m\e[0m" << endl << endl;
    if(coche.aStar(mapa, 1))
    {
        cout << "\E[95mExiste el camino.\E[95m" << endl;
        t2 = chrono::high_resolution_clock::now();
        opcion = 1;
        

        duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();

        mapa.write(cout);  

        cout << "\E[97m--> La función Manhattan toma: " << "\E[94m" << duration << " milisegundos.\E[94m" << endl;
        cout << "\E[97m--> El tamaño del camino seguido es de: " << "\E[94m" << coche.getCamino().size() <<".\E[94m"<< endl;
        cout << "\E[97m--> Los nodos generados son: " << "\E[94m" << coche.getContNodosGenerados() << ".\E[94m"<< endl << endl;

        // outfile << filas << ' ' << columnas << endl;
        // outfile << coche.getPosicion().first << ' ' << coche.getPosicion().second << endl;
        // outfile << mapa.getDestino().first << ' ' << mapa.getDestino()..second << endl;

        // for(int i = 1; i < (filas - 1); i++)
        // {
        //     for(int j = 1; j < (columnas - 1); j++)
        //     {
        //         if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() == '#')
        //             outfile << i << ' ' << j << endl;
        //     }
        // }
        // outfile.close();
    }
    else
    {
        cout << "\E[31mNo existe solución para este caso expuesto.\E[31m" << endl;
        opcion = 0;
    }

     

    


    // cout << "Reset mapa." << endl;
    mapa.resetMapa(v);
    // mapa.write(cout);
    // cout << "Reset done." << endl;

    t1 = chrono::high_resolution_clock::now();

    cout << endl << "\E[93m\e[7mA* con heurística Euclídea.\E[93m\e[0m" << endl << endl;

    if(coche.aStar(mapa, 0))
    {
        cout << "\E[95mExiste el camino.\E[95m" << endl;
        t2 = chrono::high_resolution_clock::now(); 
        mapa.write(cout); 
        duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();

        cout << "\E[97m--> La función Euclídea toma: " << "\E[94m" << duration << " milisegundos.\E[94m" << endl;
        cout << "\E[97m--> El tamaño del camino seguido es de: " << "\E[94m" << coche.getCamino().size() << ".\E[94m"<< endl;
        cout << "\E[97m--> Los nodos generados son: " << "\E[94m" << coche.getContNodosGenerados() << ".\E[94m"<< endl << endl;
    }
    else
    {
        cout << "\E[31mNo existe solución para este caso expuesto.\E[31m" << endl;
    }

     

    

    // Imprimir el valor de la posición del coche y destino, reset de padres.

    /******************* MODO CREAR MAPAS *******************/

    // pair<int, int> fichero;
    // int iteracion = 1;

    // while(1)
    // {
    //     outfile.open("prueba.txt", ofstream::out | ofstream::trunc);
    //     cout << "Iteración: " << iteracion << endl;
    //     mapa.resetMapaFull();
    //     crearAleatorio(mapa, coche);
    //     for(int i = 1; i < (filas - 1); i++)
    //     {
    //         for(int j = 1; j < (columnas - 1); j++)
    //         {
    //             fichero.first = i;
    //             fichero.second = j;
    //             if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() == '#')
    //                 mapa.getCeldaPos(fichero).setValor('.');
    //         }
    //     }

    //     int tam = ((filas * columnas) * porcentajes_obstaculos) / 100;      // Ejemplo: 10x10 10% tam = 10

    //     srand(time(NULL)); // Caso random = NULL

    //     for(int i = 0; i < tam; i++)
    //     {   
    //         do
    //         {
    //             o.first = rand() % filas; // caso random first
    //             o.second = rand() % filas; // caso random second
    //         }
    //         while (o.first <= 0 || o.second <= 0 || o.first >= (filas - 1) || o.second >= (columnas - 1) || o == coche.getPosicion() || o == mapa.getDestino());
                    
    //         mapa.rellenarManual(o.first, o.second, '#');
    //     }

    //     for(int i = 1; i < (filas - 1); i++)       
    //     {
    //         for (int j = 1; j < (columnas - 1); j++)
    //         {
    //             if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
    //             {
    //                 mapa.rellenarMovimientos(i, j);     
    //             }
    //         }
    //     }

    //     // mapa.resetMapa(coche.getPosicion());

    //     cout << "Mapa first" << endl;
    //     mapa.write(cout);

    //     if(coche.aStar(mapa, 1))
    //     {
    //         opcion = 1;
    //         outfile << filas << ' ' << columnas << endl;
    //         outfile << coche.getPosicion().first << ' ' << coche.getPosicion().second << endl;
    //         outfile << mapa.getDestino().first << ' ' << mapa.getDestino().second << endl;

    //         for(int i = 1; i < (filas - 1); i++)
    //         {
    //             for(int j = 1; j < (columnas - 1); j++)
    //             {
    //                 if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() == '#')
    //                     outfile << i << ' ' << j << endl;
    //             }
    //         }
    //     }
    //     else
    //     {
    //         opcion = 0;
    //     }

    //     cout << "Mapa Manhattan" << endl;
    //     mapa.write(cout);


    //     mapa.resetMapa(coche.getPosicion());


    //     if(coche.aStar(mapa, 0))
    //     {
    //         return 0;
    //     }
    //     cout << "Mapa Euclidean" << endl;
    //     mapa.write(cout);

    //     iteracion++;
    //     getchar();
    // }
    // outfile.close();

    return 0;
}
