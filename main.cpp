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

#include <string>
#include <cstdlib>

bool casos_int(int& valor)   // Cuando haces una entrada revisa la entrada
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

int main(void)
{
    bool opcion;
    int filas, columnas, porcentajes_obstaculos, numero_porcentajes;
    fstream ficheroEntrada; // Variable que almacena el fichero del que se lee
    string nombreFichero;   // Variable que almacena el nombre del fichero para después abrirlo
    Mapa_t mapa;            // Mapa vacío
    
//    system("clear");
    cout << "\n\e[1m\e[36m¿Desea leer desde fichero? (0 NO, 1 SI): \e[1m\e[36m"; // Si el usuario presiona 1 lee desde fichero, no está hecho de momento la opción manual
    cin >> opcion;
    
    if(opcion)
    {
        do
        { 
            cout << endl << "\E[33m- Introduzca el nombre del fichero: \E[33m";        // filas -> naranja 
            cin >> nombreFichero;

            ficheroEntrada.open(nombreFichero.c_str(), fstream::in);    // Se abre el fichero de entrada
            if(ficheroEntrada.is_open())    // Comprobamos que el fichero se haya abierto bien
            {
                ficheroEntrada >> filas >> columnas;    // Las dos primeras líneas del fichero son las filas y las columnas, las almacenamos en sus respectivas variables

                mapa.setMapa(filas, columnas, ficheroEntrada);  // Se pasa al método setMapa lo necesario para construir todo el mapa sin punto de salida ni de llegada
            }
            else    // En caso de error al abrir el fichero se indica al usuario y termina la ejecución del programa
            {
                cout << endl << "\E[31m--> Error: El fichero no existe o no tiene permisos\E[39m" << endl;
            }
        }    
        while(ficheroEntrada.is_open() != 1);
    }
    
    else    // Opción manual, falta por hacerse
    {      
        cout << endl << "\e[1m\e[36mDIMENSIONES DEL TABLERO.\e[1m\e[36m" << endl;       // cian negrita    

        do
        {
            cout << endl << "\E[33m- Introduzca el número de filas de la tabla: \E[33m";        // filas -> naranja
        } 
        while (casos_int(filas));

        do
        {
            cout << endl << "\E[33m- Introduzca el número de columnas de la tabla: \E[33m";      // columnas -> naranja
        } 
        while (casos_int(columnas));

        mapa.setN(filas);
        mapa.setM(columnas);
        mapa.setMapa(filas, columnas);

        bool opcion2;
        pair<int, int> o, v, d;     // obstáculo, vehículo y destino

        cout << endl << "Desea introducir manualmente los obstáculos o generarlos aleatoriamente (0 Manual, 1 Aleatorio): ";      // columnas -> naranja
        cin >> opcion2;

        if(!opcion2) //  manual obstaculos
        {   
            cout << endl << "DETERMINACIÓN DEL VEHÍCULO."<<endl;
            do
            {
                cout << endl << "\E[33m- Introduzca la posición i del vehículo: \E[33m";      // filas -> naranja
                cin >> v.first;
                cout << endl << "\E[33m- Introduzca la posición j del vehículo: \E[33m";      // columnas -> naranja
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
            
            cout << endl << "DETERMINACIÓN DEL DESTINO." << endl;
            do
            {
                cout << endl << "\E[33m- Introduzca la posición i del destino: \E[33m";      // filas -> naranja
                cin >> d.first;
                cout << endl << "\E[33m- Introduzca la posición j del destino: \E[33m";      // columnas -> naranja
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
                       

            system("clear");

            cout << endl << "DETERMINACIÓN DE OBSTÁCULOS."<<endl;

            do
            {
                cout << endl << "\E[33m- (Introduzca 0 0 para salir) \E[33m";      // columnas -> naranja
                cout << endl << "\E[33m- Introduzca la posición i de un obstáculo: \E[33m";      // columnas -> naranja
                cin >> o.first;
                cout << endl << "\E[33m- Introduzca la posición j de un obstáculo: \E[33m";      // columnas -> naranja
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
                    if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '$')
                    {
                        mapa.rellenarMovimientos(i, j);     
                    }
                }
            }
        }
        else // Caso aleatorios 
        {   
            cout << endl << "DETERMINACIÓN DE OBSTÁCULOS."<<endl;
            do
            {
                do
                {
                    cout << endl << "\E[31mIntroduza el porcentaje de obstaculos que desee: \E[39m";
                } 
                while(casos_int(porcentajes_obstaculos));

                if(porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100)
                {
                    cout << endl << "\E[31mIntroduzca un porcentaje dentro del rango 0-100.\E[39m" << endl;
                }
                
            } while (porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100);
            
            int tam = ((filas * columnas) * porcentajes_obstaculos) / 100; //10x10 10% tam=10

            srand(time(NULL));

            for(int i = 0; i < tam; i++)
            {   
                o.first = rand() % tam; // caso random
                o.second = rand() % tam; // caso random

                mapa.rellenarManual(o.first, o.second, '#');

                //Falta rellenar casos errores
            }
        }
    }

    mapa.write(cout);   // Al final, se imprime por pantalla el contenido del mapa.

    // system("clear");
	// cout<<endl<<"\E[45mPOSICIÓN INICIAL DEL VEHÍCULO.\E[45m"<< endl;

    return 0;

}