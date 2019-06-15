//
//  GAME.cpp
//  Batalla Por La Princesa
//
//  Created by Cristian David Gómez Muñoz on 6/14/19.
//  Copyright © 2019 Cristian Gómez, David Cortes y Ricardo Marino. All rights reserved.
//

#include <iostream> // Librería para salida y entrada de datos.
#include <cstdlib> // Librerias para la generación de números aleatorios.
#include <ctime>
#include <conio.h> // Librería para interactuar con el usauario.
#include <wchar.h> // Libreria para agregar caracteres de impresión en consola.

using namespace std;

//-----------------------------------------------------------------------------TABLERO--------------------------------------------------------------------------------------------------------------
//Función tableroGrafico: Despliega el tablero en pantalla
//Parámetros(Vector tablero)
void tableroGrafico( char *posicionTablero )
{
    int k = 0;    //k es el índice que recorre el vector
    
    //Imprime el tablero
    for( int i = 0;i < 8;i++ )
    {
        for( int j = 0;j < 8;j++ )
        {
            cout << '[' << *( posicionTablero + k ) << ']';
            k++;
        }
        cout << endl;
    }
    
}

//------------------------------------------------------------------------------DADOS---------------------------------------------------------------------------------------------------------------
//Función dado: determina el número del dado que saca cada jugador.
//Parámetros(Posición actual, turno, variable para guardar el número del dado)
int dado(int posicionActual, int turno, int numeroDelDadoObtenido)
{
    // Si es el turno 1 o 2
    if( turno < 3 )
    {
        posicionActual = rand() % 64;           //Asigna un numero aleatorio entre 0 y 63 a la posición actual
        posicionActual = posicionActual + 1;    //Le suma 1 a la posición actual para que su rango sea de 1 a 64
        return posicionActual;                  //retorna la posición actual
    }
    else
    {
        numeroDelDadoObtenido = rand() % 8;                   //Asigna un numero aleatorio de 0 a 7 a la variable que guarda el numero del dado
        numeroDelDadoObtenido = numeroDelDadoObtenido + 1;    //Le suma 1 a la variable anterior para que su rango sea de 1 a 8
        return numeroDelDadoObtenido;                         //retorna el numero del dado
    }
}

//-----------------------------------------------------------------------------POSICION-------------------------------------------------------------------------------------------------------------
//Función obtenerPosicion: Determina la posible nueva posición
//Parámetros( Posición actual, Numero del dado )
int obtenerPosicion( int posicionActual,int numeroDelDadoObtenido )
{
    int nuevaPosicionPosible = 0;
    
    //Aplica determinada suma a la posición actual y la almacena en nuevaPosicionPosible.
    //La suma correspondiente está dada por el número del dado segun el valor que tendria en el vector tablero
    switch( numeroDelDadoObtenido )
    {
        case 1: nuevaPosicionPosible = posicionActual - 15;
            break;
        case 2: nuevaPosicionPosible = posicionActual - 6;
            break;
        case 3: nuevaPosicionPosible = posicionActual + 10;
            break;
        case 4: nuevaPosicionPosible = posicionActual + 17;
            break;
        case 5: nuevaPosicionPosible = posicionActual + 15;
            break;
        case 6: nuevaPosicionPosible = posicionActual + 6;
            break;
        case 7: nuevaPosicionPosible = posicionActual - 10;
            break;
        case 8: nuevaPosicionPosible = posicionActual - 17;
            break;
    }
    
    //Si la posible nueva posición es menor que 65 y mayor a 0 la retorna
    //Si incumple alguna de estas condiciones retorna 1000
    if( nuevaPosicionPosible < 65 )
    {
        if( 0 < nuevaPosicionPosible )
        {
            return nuevaPosicionPosible;
        }
        else
        {
            return 1000;
        }
    }
    else
    {
        return 1000;
    }
}

//Función posicionValida: Determina si la jugada que se va a hacer es valida
//Parámetros( Posición actual, Número del dado, Posible nueva posición )
int posicionValida( int posicionActual,int numeroDelDadoObtenido,int nuevaPosicionPosible )
{
    bool validez = false;       // validez del movimiento
    int z = posicionActual;     // "z" nos dice la fila en la que esta la posición actual
    
    
    //El siguiente ciclo toma la posición actual y convierte a z en el múltiplo de 8 que hay en la fila en la que se encuentra.
    while( z % 8 != 0)
    {
        z = z + 1;
    }
    
    //Evalúa el número del dado que saco el jugador y valida si esta jugada se
    //puede hacer si y solo si está dentro de los siguientes intervalos:
    //1 y 8: (z-24 , z-26]
    //2 y 7: (z-16 , z-8]
    //3 y 6: (z , z+8]
    //4 y 5: (z+8, z+16]
    //Si se puede hacer asigna true a valida
    switch( numeroDelDadoObtenido )
    {
        case 1: if( z - 24 < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z - 16 )
            {
                validez = true;
            }
        }
            break;
        case 2: if( z - 16 < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z - 8 )
            {
                validez = true;
            }
        }
            break;
        case 3: if( z < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z + 8)
            {
                validez = true;
            }
        }
            break;
        case 4: if( z + 8 < nuevaPosicionPosible)
        {
            if( nuevaPosicionPosible <= z + 16 )
            {
                validez = true;
            }
        }
            break;
        case 8: if( z - 24 < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z - 16)
            {
                validez = true;
            }
        }
            break;
        case 7: if( z - 16 < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z - 8 )
            {
                validez = true;
            }
        }
            break;
        case 6: if( z < nuevaPosicionPosible )
        {
            if( nuevaPosicionPosible <= z + 8 )
            {
                validez = true;
            }
        }
            break;
        case 5: if( z + 8 < nuevaPosicionPosible)
        {
            if( nuevaPosicionPosible <= z + 16 )
            {
                validez = true;
            }
        }
            break;
    }
    
    //Si la jugada es valida retorna 1 si no 0
    if ( validez == false )
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}

//MOVIMIENTO NO VALIDO
//Funcion movimientoInvalido: Cambia el numero del dado cuando la jugada no se puede hacer
//Parametros( Numero del dado )
int movimientoInvalido( int numeroDelDadoObtenido )
{
    //Si el número del dado que saco el jugador es menor a 9, le suma 1 al número
    //del dado para luego repetir el ciclo de código con el nuevo número de dado
    if( numeroDelDadoObtenido < 9 )
    {
        cout << "EL MOVIMIENTO NO ES POSIBLE: " << numeroDelDadoObtenido << endl;
        numeroDelDadoObtenido = numeroDelDadoObtenido + 1;
    }
    
    //Si el número del dado que saco el jugador es 8, toma el número del
    //dado como 1, para luego repetir el ciclo de código con este nuevo número
    if( numeroDelDadoObtenido == 9)
    {
        numeroDelDadoObtenido = 1;
    }
    
    return numeroDelDadoObtenido;     //Devuelve el nuevo numero del dado
}

//---------------------------------------------------------------------INTERACCION CON EL USUARIO---------------------------------------------------------------------------------------------------
//Funcion continuar: Dada para que el usuario avance en el juego
void continuar()
{
    
    //Crea una variable "tecla" y le asigna el valor de una tecla del teclado en codigo ASCII
    char tecla = char(0);
    
    //El siguiente ciclo se repite mientras que la variable tecla sea diferente de la flecha arriba en ASCII (72)
    while( tecla != char(72) )
    {
        tecla = getch();            //La función getch recibe la tecla que uno toca en el teclado y la retorna en codigo ASCII
        if( tecla == char(72) )
        {
            break;
        }
    }
}

//Funcion limpiarPantalla: Usada para limpiar la pantalla
int limpiarPantalla()
{
    continuar();
    system( "cls" );
    return 0;
}

//__________________________________________________________________________________________________________________________________________________________________________________________________
//---------------------------------------------------------------------------------JUEGO------------------------------------------------------------------------------------------------------------
int main()
{
    setlocale( LC_ALL, "" );//FUNCIÓN PARA ESCRIBIR CON TILDES LAS IMPRESIONES EN PANTALLA
    srand( static_cast<unsigned int>(time(NULL)));//SEMILLA PARA GENERACIÍON DE NUMEROS ALEATORIOS
    
    //1. DECLARACION DE VARIABLES Y VECTORES:
    
    int posicionDeGawain = 0, posicionDeDietrich = 0;
    int lanzamientoDeGawain = 0, lanzamientoDeDietrich = 0;        // número del 1 al 8 que cada jugador obtiene al tirar el dado.
    int turno = 0;                                                 // indica en que turno se está actualmente.
    int nuevaPosicionPosible;
    int validezDeLaJugada;                                         // indica si la jugada se puede hacer o no.
    int contador;                                                  // determina la cantidad de veces seguidas que un jugador no puede realizar un movimiento.
    int winner = 0;                                                // indica quién ganó.
    int jugadaDeGawain = 0, jugadaDeDietrich = 0;
    bool win = false;                                              //indica si alguien gano.
    bool flag = false;                                             //indica si el jugador terminó o no terminó su turno.
    
    
    //Vectores:
    int jugadasDeGawain[32];                            // Almacena las jugadas del jugador 1 (lanzamientosDeGawain) que se hacen y son válidas en el orden que se hacen.
    int *apuntadorJugadasDeGawain;
    apuntadorJugadasDeGawain = new int[32];
    apuntadorJugadasDeGawain = &jugadasDeGawain[0];
    if( apuntadorJugadasDeGawain == NULL )
    {
        cout << "No hay memoria disponible" << endl;
        exit( 2 );
    }
    
    int jugadasDeDietrich[32];                          // Almacena las jugadas del jugador 2 (lanzamientosDeDietrich) que se hacen y son válidas en el orden que se hacen.
    int *apuntadorJugadasDeDietrich;
    apuntadorJugadasDeDietrich = new int[32];
    apuntadorJugadasDeDietrich = &jugadasDeDietrich[0];
    if( apuntadorJugadasDeDietrich == NULL )
    {
        cout << "No hay memoria disponible" << endl;
        exit( 2 );
    }
    
    char posicionesDelTablero[64];                     // Almacena los datos del tablero que se verán en pantalla.
    char *apuntadorPosicionDelTablero;
    apuntadorPosicionDelTablero = new char[64];
    apuntadorPosicionDelTablero = &posicionesDelTablero[0];
    if( apuntadorPosicionDelTablero == NULL )
    {
        cout << "No hay memoria disponible" << endl;
        exit( 2 );
    }
    
    //2. CONSTRUCCION DEL TABLERO:
    //Este ciclo toma el vector tablero y a cada espacio que tiene le asigna un carácter ' '.
    for( int i = 0;i < 64;i++)
    {
        *( apuntadorPosicionDelTablero + i ) = ' ';
    }
    
    //3.INTRODUCCION AL JUEGO
    
    //Se explica el funcionamiento del juego
    cout << "BIENVENIDO A BATALLA POR LA PRINCESA\n\n"
    << "1.Para avanzar en el juego oprima la flecha arriba.\n"
    << "2.Si un movimiento no es posible se le avisará junto con el dado que sacó.\n\n" << endl;
    
    //Primer turno del jugador 1
    cout << "\nA CONTINUACIÓN LANCE EL DADO QUE DARÁ LA POSICIÓN INICIAL DEL CABALLERO GAWAIN EN EL TABLERO";
    continuar();                                                                //Función que para el juego hasta que se oprima la flecha arriba
    turno = turno + 1;                                                          //Suma 1 a la variable turno
    cout << "Turno: " << turno << endl;                                         //Imprime la variable turno (TURNO 1)
    posicionDeGawain = dado( posicionDeGawain, turno, lanzamientoDeGawain);     //toma un numero de1 1 al 64 mediante la función dado() y la asigna al jugador 1
    cout << "LA POSICIÓN DE GAWAIN ES " << posicionDeGawain << "\n\n" << endl;  //Imprime la posición del jugador 1
    *( apuntadorPosicionDelTablero + (posicionDeGawain - 1) ) = 'G';            //Toma la posición actual del jugador 1 y le asigna la letra G a esa posicion en el vector tablero
    tableroGrafico( apuntadorPosicionDelTablero );                              //Imprime el tablero actualizado
    limpiarPantalla();                                                          //Limpia pantalla
    
    //Primer turno del jugador 2
    cout<< "\nAHORA LANCE EL DADO QUE DARÁ LA POSICIÓN INICIAL DEL CABALLERO DIETRICH EN EL TABLERO" << endl;
    continuar();                                                                    //Función que para el juego hasta que se oprima la flecha arriba
    turno = turno + 1;                                                              //Suma 1 a la variable turno
    cout << "Turno: " << turno << endl;                                             //Imprime la variable turno (TURNO 2)
    posicionDeDietrich = dado( posicionDeDietrich, turno, posicionDeDietrich );     //toma un numero de1 1 al 64 mediante la función dado() y la asigna al jugador 1
    
    //Este siclo evalúa si el jugador 1 y el jugador 2 están en la misma posición y si es así pone al jugador 2 en la posición del jugador 1 más uno
    if( posicionDeGawain == posicionDeDietrich )
    {
        posicionDeDietrich++;
    }
    cout << "LA POSICIÓN DE DIETRICH ES "<< posicionDeDietrich << "\n\n\n\n"<< endl;   //Imprime la posición del jugador 1
    *( apuntadorPosicionDelTablero + (posicionDeDietrich - 1) ) = 'D';                 //Toma la posición actual del jugador 2 y le asigna la letra G a esa posicion en el vector tablero
    tableroGrafico(apuntadorPosicionDelTablero);                                       //Imprime el tablero actualizado
    limpiarPantalla();                                                                 //Limpia pantalla
    
    
    //SE EXPLICA COMO FUNCIONARA EL JUEGO A PARTIR DE AHORA
    cout << "\nA PARTIR DE ESTE MOMENTO SE JUGARÁ CON UN DADO DE OCHO CARAS QUE DICTARÁ LA "
    << "SIGUENTE POSICIÓN DEL JUGADOR SEGUN LOS MOVIMIENTOS DEL CABALLO EN EL AJEDREZ\n\n" << endl;
    
    //4. JUEGO
    while( win == false )
    {
        // Este ciclo se repite hasta que uno de los dos jugadores gane y contiene lo que se hara durante el turno 3 hasta que un jugador se queda sin movimientos
        limpiarPantalla();                                              //Limpiar pantalla
        contador = 0;                                                   //Asigna el valor cero al contador de movimientos no validos
        cout << "\nTurno: " << turno << endl;                           //Imprime el turno actual
        
        //Para saber a que jugador le toca se hace la operación turno modulo dos.
        //Luego si es 1 es porque turno es impar y por tanto le toca al jugador 2 y si es 0 es porque el número es par y le toca al jugador 1
        switch( turno % 2 )
        {
            //TURNO DEL JUGADOR 1
            case 0: //Si turno modulo dos es uno, ejecuta el siguiente código
                cout << "\nTURNO DEL CABALLERO GAWAIN" << endl;
                srand( static_cast<unsigned int>(time(NULL)));
                lanzamientoDeGawain = dado( posicionDeGawain, turno, lanzamientoDeGawain);         //Adquiere un número del 1 al 8 (Se lanza el dado)
                jugadaDeGawain++;
                
                //Ciclo que se repite hasta que el jugador termine su turno, llámese ciclo de turno
                while( flag == false )
                {
                    continuar();               //Función que para el juego hasta que se oprima la flecha arriba
                    contador++;                //Suma 1 al contador
                    if(contador>8)
                    {
                        //Si el contador suma 8 errores ejecuta las siguientes tres líneas
                        win=true;                   //Indica que alguien gano
                        flag=true;                  //termina el turno
                        winner = 2;                 //Indica que el jugador 2 gano
                    }
                    nuevaPosicionPosible = obtenerPosicion( posicionDeGawain, lanzamientoDeGawain );         //Haya la posible nueva posición del jugador 1
                    if( nuevaPosicionPosible < 65 )
                    {
                        //Si la posible nueva posición es menor a 65 continua con el código
                        validezDeLaJugada =posicionValida( posicionDeGawain, lanzamientoDeGawain, nuevaPosicionPosible); //Valida la nueva posible posición a ver si se puede hacer
                        if (validezDeLaJugada == 1)
                        {
                            //Si la posible nueva posición es válida continua con el código
                            if( nuevaPosicionPosible != posicionDeDietrich)
                            {
                                //Si la nueva posible posición es diferente al de la posición actual del jugador 2, continua con el código
                                if( *( apuntadorPosicionDelTablero + ( nuevaPosicionPosible - 1) ) == ' ')
                                {
                                    //Si al evaluar la posible nueva posición en el vector tablero corresponde al carácter ' ', continua con el código
                                    *(apuntadorPosicionDelTablero + ( posicionDeGawain - 1) )= 'X';    //Toma la posición actual del jugador 1 en el vector tablero y le asigna el carácter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                    posicionDeGawain = nuevaPosicionPosible;                           //Asigna el valor de la posible nueva posición a la posición actual
                                    *( apuntadorPosicionDelTablero + ( posicionDeGawain - 1) ) = 'G';  //Toma la nueva posición actual del jugador 1 en el vector tablero y le asigna el carácter 'G'. Que en el tablero indica la posición de Gowin
                                    flag = true;                      //termina el turno
                                    *( apuntadorJugadasDeGawain + ( jugadaDeGawain - 1 )) = lanzamientoDeGawain;           //Agrega al vector jugadas el número de dado que saco el jugador 1 para moverse a la nueva posición
                                    //Se imprime lo que paso en el tablero de forma escrita
                                    cout << "Se movió a " << posicionDeGawain << "\n"
                                    << "Dado: " << lanzamientoDeGawain << endl;
                                }
                                else
                                {
                                    //Si al evaluar la posible nueva posición en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                                    lanzamientoDeGawain = movimientoInvalido( lanzamientoDeGawain );
                                }
                            }
                            else
                            {
                                //Si el jugador 1 cae en la posicion del jugador 2
                                posicionesDelTablero[ posicionDeGawain - 1 ] = 'X';              //Toma la posición actual del jugador 1 en el vector tablero y le asigna el carácter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                posicionDeGawain = nuevaPosicionPosible;                           //Asigna el valor de la posible nueva posición a la posición actual
                                posicionesDelTablero[ posicionDeGawain - 1 ] = 'G';              //Toma la nueva posición actual del jugador 1 en el vector tablero y le asigna el carácter 'G'. Que en el tablero indica la posición de Gowin
                                flag = true;                      //termina el turno
                                *( apuntadorJugadasDeGawain + ( jugadaDeGawain - 1) )= lanzamientoDeGawain;        //Agrega al vector jugadas el número de dado que saco el jugador 1 para moverse a la nueva posición
                                //Se imprime lo que paso en el tablero de forma escrita
                                cout << "Se movió a la posición de DIETRICH" << posicionDeGawain << endl;
                                cout << "Dado: "<< lanzamientoDeGawain << endl;
                                win = true;                       //Indica que alguien gano
                                winner = 1;                     //Indica que el jugador 1 gano
                            }
                        }
                        else
                        {
                            //Si la nueva posición no es valida, vuelve a tirar el dado
                            lanzamientoDeGawain = movimientoInvalido( lanzamientoDeGawain );
                        }
                    }
                    else
                    {
                        //Si x es menor o igual a 64 vuelve a tirar el dado
                        lanzamientoDeGawain = movimientoInvalido(lanzamientoDeGawain );
                    }
                }
                break;
                
                
            //TURNO DEL JUGADOR 2
            case 1:
                //Si turno modulo dos es 0, ejecuta el siguiente código
                cout << "\nTURNO DEL CABALLERO DIETRICH" << endl;
                srand( static_cast<unsigned int>(time(NULL)));            //Adquiere un número del 1 al 8 (Se lanza el dado)
                lanzamientoDeDietrich = dado(posicionDeDietrich , turno, lanzamientoDeDietrich);   //Ciclo que se repite hasta que el jugador termine su turno, llámese ciclo de turno
                jugadaDeDietrich++;
                while( flag == false )
                {
                    continuar();                     //Función que para el juego hasta que se oprima la flecha arriba
                    contador++;                 //Suma 1 al contador
                    if( contador > 8 )
                    {
                        //Si el contador suma 8 errores ejecuta las siguientes tres líneas
                        win = true;                   //Indica que alguien gano
                        flag = true;                  //termina el turno
                        winner = 1;                   //Indica que el jugador 1 gano
                    }
                    nuevaPosicionPosible = obtenerPosicion( posicionDeDietrich, lanzamientoDeDietrich);         //Haya la posible nueva posición del jugador 1
                    if( nuevaPosicionPosible < 65)
                    {
                        //Si la posible nueva posición es menor a 65 continua con el código
                        validezDeLaJugada = posicionValida( posicionDeDietrich, lanzamientoDeDietrich, nuevaPosicionPosible); //Valida la nueva posible posición a ver si se puede hacer
                        if (validezDeLaJugada == 1)
                        {
                            //Si la posible nueva posición es válida continua con el código
                            if( nuevaPosicionPosible != posicionDeGawain)
                            {
                                //Si la nueva posible posición es diferente al de la posición actual del jugador 1, continua con el código
                                if( *( apuntadorPosicionDelTablero + ( nuevaPosicionPosible - 1) ) == ' ')
                                {
                                    //Si al evaluar la posible nueva posición en el vector tablero corresponde al carácter ' ', continua con el código
                                    *( apuntadorPosicionDelTablero + ( posicionDeDietrich - 1 ) ) = 'X';              //Toma la posición actual del jugador 2 en el vector tablero y le asigna el carácter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                    posicionDeDietrich = nuevaPosicionPosible;                           //Asigna el valor de la posible nueva posición a la posición actual
                                    *( apuntadorPosicionDelTablero + ( posicionDeDietrich - 1 ) ) = 'D';
                                    flag = true;                      //termina el turno
                                    *( apuntadorJugadasDeDietrich + (jugadaDeDietrich - 1) ) = lanzamientoDeDietrich; //Agrega al vector jugadas el número de dado que saco el jugador 2 para moverse a la nueva posición
                                    //Se imprime lo que paso en el tablero de forma escrita
                                    cout << "Se movió a " << posicionDeDietrich
                                    << "\nDado: " << lanzamientoDeDietrich << endl;
                                }
                                else
                                {
                                    //Si al evaluar la posible nueva posición en el vector tablero NO corresponde al caracter ' ', vuelve a tirar el dado
                                    lanzamientoDeDietrich = movimientoInvalido( lanzamientoDeDietrich );
                                }
                            }
                            else
                            {
                                //Si el jugador 2 cae en la posición del jugador 1
                                *( apuntadorPosicionDelTablero + ( posicionDeDietrich - 1 ) ) = 'X';              //Toma la posición actual del jugador 2 en el vector tablero y le asigna el caracter 'X'. Que en el tablero indicara que no se pueden mover a ese sitio
                                posicionDeDietrich = nuevaPosicionPosible;                           //Asigna el valor de la posible nueva posición a la posición actual
                                *( apuntadorPosicionDelTablero + ( posicionDeDietrich - 1 ) ) = 'D';
                                flag = true;                      //termina el turno
                                *( apuntadorJugadasDeDietrich + ( jugadaDeDietrich - 1) ) = lanzamientoDeDietrich;           //Agrega al vector jugadas el número de dado que saco el jugador 2 para moverse a la nueva posición
                                //Se imprime lo que paso en el tablero de forma escrita
                                cout << "Se movió a la posición de GAWAIN " << posicionDeDietrich
                                << "\nDado: " << lanzamientoDeDietrich << endl;
                                win = true;                       //Indica que alguien gano
                                winner = 2;                       //Indica que el jugador 2 gano
                            }
                        }
                        
                        else
                        {
                            //Si la nueva posición no es valida, vuelve a tirar el dado
                            lanzamientoDeDietrich = movimientoInvalido( lanzamientoDeDietrich );
                        }
                    }
                    else
                    {
                        //Si x es menor o igual a 64 vuelve a tirar el dado
                        lanzamientoDeDietrich = movimientoInvalido( lanzamientoDeDietrich );
                    }
                }
                break;
        }
        flag = false;                                   //Asigna false a la variable flat para que el turno se pueda ejecutar correctamente el código del siguiente jugador
        tableroGrafico( apuntadorPosicionDelTablero );  //Imprime el tablero
        
        //Imprime el vector que contiene las jugadas de Gawain de forma lineal y separando cada número por comas
        cout << "Jugadas Gawain: ";
        for( int i = 0;i <= jugadaDeGawain;i++ )
        {
            if ( ( *( apuntadorJugadasDeGawain + i ) < 9) && ( 0 < *( apuntadorJugadasDeGawain + i) ) )
            {
                //Valida que el numero del dado almacenado en el vector jugadasG este entre 0 y 9
                cout << *( apuntadorJugadasDeGawain + i) << ", ";
            }
        }
        cout << "\n";
        
        //Imprime el vector que contiene las jugadas de Dietrich forma lineal y separando cada número por comas
        cout << "Jugadas Dietrich: ";
        for( int i = 0;i < jugadaDeDietrich;i++ )
        {
            if ( ( *( apuntadorJugadasDeDietrich + i) < 9 ) && ( 0 < *( apuntadorJugadasDeDietrich + i) ) )
            {
                //Valida que el numero del dado almacenado en el vesctor jugadasD este entre 0 y 9
                cout << *( apuntadorJugadasDeDietrich + i) << ", ";
            }
        }
        cout << "\n";
    }
    
    //5. GANADOR:
    cout << "\n\n\n";
    //Evalúa si gano el jugador 1 y si es así lo muestra en pantalla
    if ( winner == 1 )
    {
        cout << "\n\nDIETRICH HA PERDIDO\nGAWAIN HA GANADO EL AMOR DE LA PRINCESA" << endl;
    }
    //Evalúa si gano el jugador 1 y si es así lo muestra en pantalla
    if ( winner == 2 )
    {
        cout << "\n\nGAWAIN HA PERDIDO\nDIETRICH HA GANADO EL AMOR DE LA PRINCESA" << endl;
    }
    continuar(); //Función que para el juego hasta que se oprima la flecha arriba
    
    delete( apuntadorJugadasDeDietrich );
    delete( apuntadorJugadasDeGawain );
    delete( apuntadorPosicionDelTablero );
    return 0;
    
}

