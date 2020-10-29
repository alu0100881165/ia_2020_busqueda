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

#include "mapa.hpp"
#include "coche.hpp"

#include <string>
#include <cstdlib>

bool casosInt(int& valor)   // Cuando haces una entrada revisa la entrada
{
    cin >> valor;
    bool casos = cin.good(); // Devuelve 0 si la secuencia no existe 
    if (!casos)
    {
        system("clear");

        cin.clear();    // Limpiamos
        cin.ignore();   // Eliminamos el contenido
        cout << endl << "\E[31mLa respuesta no ha sido un numero\E[39m" << endl;
    }

    return !casos;
}

pair<int, int> crearVehiculo(Mapa_t mapa, int filas, int columnas)
{
    pair<int, int> v;
    cout << endl << "\E[33mDETERMINACIÓN DEL VEHÍCULO.\E[33m"<<endl;
        do
        {
            cout << endl << "\E[96m- Introduzca la posición i del vehículo: \E[97m";      // filas -> naranja
            cin >> v.first;
            cout << "\E[96m- Introduzca la posición j del vehículo: \E[97m";      // columnas -> naranja
            cin >> v.second;

            if(v.first > 0 && v.second > 0 && v.first < (filas - 1) && v.second < (columnas - 1))           // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
            {                                                                                               // Arriba, izquierda, abajo y derecha.
                mapa.rellenarManual(v.first, v.second, '&');                                                // Guarda en la posición pair 'v' el vehículo, '&'               
            }
            else
            {
                cout << endl << "\E[31m--> Error de posición: Introduzca el vehículo en una posición viable (no en los bordes). \E[31m" << endl;
            }
        } 
        while (v.first <= 0 || v.second <= 0 || v.first >= (filas - 1) || v.second >= (columnas - 1));      // if(-1)
    
    return v;
}

pair<int, int> crearDestino(Mapa_t mapa, int filas, int columnas, pair<int, int> v)
{
    pair<int, int> d;

    cout << endl << "\E[33mDETERMINACIÓN DEL DESTINO.\E[33m" << endl;
        do
        {
            cout << endl << "\E[96m- Introduzca la posición i del destino: \E[97m";      // filas -> naranja
            cin >> d.first;
            cout <<  "\E[96m- Introduzca la posición j del destino: \E[97m";      // columnas -> naranja
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

    cout << "\nPractica 1: INTELIGENCIA ARTIFICIAL. PRÁCTICA DE BÚSQUEDA.\n";
    //do
    //{
        cout << "\n\E[32m¿Desea leer desde fichero? \e[35m(0 NO, 1 SI)\e[35m: \E[97m"; // Si el usuario presiona 1 lee desde fichero, no está hecho de momento la opción manual
        cin >> opcion;
        
        system("clear");
    //}
    //while (opcion !=0 || opcion != 1);
    
    if(opcion)
    {
        do
        { 
            cout << endl << "\E[33m- Introduzca el nombre del fichero: \E[97m";        // filas -> naranja 
            cin >> nombreFichero;

            ficheroEntrada.open(nombreFichero.c_str(), fstream::in);    // Se abre el fichero de entrada
            if(ficheroEntrada.is_open())    // Comprobamos que el fichero se haya abierto bien
            {
                ficheroEntrada >> filas >> columnas;    // Las dos primeras líneas del fichero son las filas y las columnas, las almacenamos en sus respectivas variables

                mapa.setMapa(filas, columnas, ficheroEntrada);  // Se pasa al método setMapa lo necesario para construir todo el mapa sin punto de salida ni de llegada
            }
            else    // En caso de error al abrir el fichero se indica al usuario y termina la ejecución del programa
            {
                cout << endl << "\E[31m--> Error: El fichero no existe o no tiene permisos\E[31m" << endl;
            }
        }    
        while(ficheroEntrada.is_open() != 1);
    }
    
    else    // Opción manual, falta por hacerse
    {      
        cout << endl << "\E[33mDIMENSIONES DEL TABLERO.\E[33m" << endl;       // cian negrita    

        do
        {
            cout << endl << "\E[96m- Introduzca el número de filas de la tabla \e[32m(>= 4): \E[97m";        // filas -> naranja
        } 
        while (casosInt(filas) || filas < 4);

        do
        {
            cout << "\E[96m- Introduzca el número de columnas de la tabla \e[32m(>= 4): \E[97m";      // columnas -> naranja
        } 
        while (casosInt(columnas) || columnas < 4);

        mapa.setN(filas);
        mapa.setM(columnas);
        mapa.setMapa(filas, columnas);

        bool opcion2;

        cout << endl << "\E[32m¿Desea introducir manualmente los obstáculos o generarlos aleatoriamente? \e[35m(0 Manual, 1 Aleatorio)\e[35m: \E[97m";      // columnas -> naranja
        cin >> opcion2;

        v = crearVehiculo(mapa, filas, columnas);
        d = crearDestino(mapa, filas, columnas, v);
        coche.setPosicion(v);

        if(!opcion2) //  manual obstaculos
        {   
            system("clear");

            cout << endl << "\E[33mDETERMINACIÓN DE OBSTÁCULOS.\E[33m"<<endl;

            do
            {
                cout << endl << "\E[33m- (Introduzca 0 0 para salir) \E[33m";      // columnas -> naranja
                cout << endl << "\E[96m- Introduzca la posición i de un obstáculo: \E[97m";      // columnas -> naranja
                cin >> o.first;
                cout  << "\E[96m- Introduzca la posición j de un obstáculo: \E[97m";      // columnas -> naranja
                cin >> o.second;
                               
                if(d.first > 0 && d.second > 0 && d.first < (filas - 1) && d.second < (columnas - 1) && o != v && o != d)   // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
                {                                                                                                           // Arriba, Izquierda, abajo y derecha, además de que no esté en la posición del vehículo ni del destino.
                    mapa.rellenarManual(o.first, o.second, '#');                                                            // Guarda en la posición pair 'o' un obstáculo, '#'.                                                                           
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
            cout << endl << "\E[33mDETERMINACIÓN DE OBSTÁCULOS.\E[33m"<<endl;
            do
            {
                do
                {
                    cout << endl << "\E[96mIntroduza el porcentaje de obstaculos que desee: \E[97m";    // El usuario introduce un %
                } 
                while(casosInt(porcentajes_obstaculos));

                if(porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100)
                {
                    cout << endl << "\E[31m--> Error: Introduzca un porcentaje dentro del rango 0-100.\E[39m" << endl;  // Error rango
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
        }
    }

    //system("clear");
    mapa.write(cout);   // Al final, se imprime por pantalla el contenido del mapa.
    coche.write(cout); // Imprimr por pantalla el coche

    return 0;
}