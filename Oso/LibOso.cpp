#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LibOso.h"

void identificacion_alumno()
{
    std::system("cls");            // Comando para borrar todo el contenido de la pantalla
    std::cout << "\x1B[H";          // Codigo para colocar el cursor en el canto superior izquierdo
    std::cout << "\x1B[3;35m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"   
    std::cout << "/***************************************************/" << std::endl; 
    std::cout << "\x1B[m";             // Resetear color a valor por defecto
    std::cout << "Universidad Catolica San Pablo" << std::endl; 
    std::cout << "Escuela Profesional de Ciencia de la Computacion" << std::endl; 
    std::cout << "Curso de Ciencia de la Computacion I" << std::endl; 
    std::cout << "Prof. D.Sc. Manuel Eduardo Loaiza Fernandez" << std::endl;
    std::cout << "Alumnos: Sofia Alejandra Pinto Galvez y Lucius Matheo Caldenhoven Loayza" << std::endl;
    std::cout << "Arequipa 2023 - I" << std::endl; 
    std::cout << "\x1B[3;35m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"   
    std::cout << "/***************************************************/" << std::endl;
    std::cout << "\x1B[m";             // Resetear color a valor por defecto
}

void letras_aleatorias(char tablero[5][5])
{
    srand(time(0));
    int accion{0};

    do
    {
        int rand_fila = std::rand() % 5;
        int rand_columna = std::rand() % 5;
        int rand_letra = 1 + (std::rand() % 2);
        char letra;

        if(rand_letra == 1)
        {
            letra = 'S';
        }
        else
        {
            letra = 'O';
        }

        if(tablero[rand_fila][rand_columna] == ' ')
        {
            tablero[rand_fila][rand_columna] = letra;
            accion++;
        }
    }
    while(accion < 5); 
}

void imprimir_tablero(char tablero[5][5])
{           
    std::cout<< "\x1B[3;34m    A   B   C   D   E\x1B[m\n";
    for(int f=0; f<5; f++)
    {
        std::cout << "\x1B[3;34m" << f+1 << "\x1B[m";
        for(int c=0; c<5; c++)
        {
            std::cout << "\x1B[3;33m | \x1B[m" << tablero[f][c];
        }
        std::cout << "\x1B[3;33m |\x1B[m\n";
    }
}

char escoger_letra()
{
    char opcion;

    std::cout << "Ingrese letra (O-S): ";
    std::cin >> opcion;
    return opcion;
}

bool ingresar_jugada(char tablero[5][5], int fil, char col, char let)
{
    if(tablero[fil][col] == ' ')
    {
        tablero[fil][col] = let;
        return false;
    }
    else
    {
        return true;
    }
}

void aumentar_puntaje(char tablero[5][5], int f, int c, int &out_puntaje)
{
    if(tablero[f][c] == 'S')
    {
        if(tablero[f][c-1] == 'O' && tablero[f][c+1] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c] == 'O' && tablero[f+1][c] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c-1] == 'O' && tablero[f+1][c+1] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c+1] == 'O' && tablero[f+1][c-1] == 'O')
        {
            out_puntaje++;
        }
    }
    else
    {
        if(tablero[f][c-1] == 'S' && tablero[f][c-2] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f][c+1] == 'S' && tablero[f][c+2] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c] == 'S' && tablero[f-2][c] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f+1][c] == 'S' && tablero[f+2][c] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c-1] == 'S' && tablero[f-2][c-2] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f+1][c+1] == 'S' && tablero[f+2][c+2] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f-1][c+1] == 'S' && tablero[f-2][c+2] == 'O')
        {
            out_puntaje++;
        }
        if(tablero[f+1][c-1] == 'S' && tablero[f+2][c-2] == 'O')
        {
            out_puntaje++;
        }
    }
}

bool mas_punto_bot(char tablero[5][5], int &p_bot)
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {  
            if(tablero[i][j] == 'S')
            {
                if(tablero[i][j-1] == 'O' && tablero[i][j+1] == ' ')
                {
                    if(j+1<5)
                    {  
                        tablero[i][j+1] = 'O';
                        aumentar_puntaje(tablero, i, j+1, p_bot);
                        return true;
                    }
                }
                else if(tablero[i][j-1] == ' ' && tablero[i][j+1] == 'O')
                {
                    if(j-1>=0)
                    {
                        tablero[i][j-1] = 'O';
                        aumentar_puntaje(tablero, i, j-1, p_bot);
                        return true;
                    }
                }
                else if(tablero[i-1][j] == 'O' && tablero[i+1][j] == ' ')
                {
                    if(i+1<5)
                    {
                        tablero[i+1][j] = 'O';
                        aumentar_puntaje(tablero, i+1, j, p_bot);
                        return true;
                    }
                }
                else if(tablero[i-1][j] == ' ' && tablero[i+1][j] == 'O')
                {
                    if(i-1>=0)
                    {
                        tablero[i-1][j] = 'O';
                        aumentar_puntaje(tablero, i-1, j, p_bot);
                        return true;
                    }
                }
                else if(tablero[i-1][j-1] == 'O' && tablero[i+1][j+1] == ' ')
                {
                    if(i+1<5 && j+1<5)
                    {
                        tablero[i+1][j+1] = 'O';
                        aumentar_puntaje(tablero, i+1, j+1, p_bot);
                        return true;
                    }    
                }
                else if(tablero[i-1][j-1] == ' ' && tablero[i+1][j+1] == 'O')
                {
                    if(i-1>=0 && j-1>=0)
                    {
                        tablero[i-1][j-1] = 'O';
                        aumentar_puntaje(tablero, i-1, j-1, p_bot);
                        return true;
                    }
                }
                else if(tablero[i-1][j+1] == 'O' && tablero[i+1][j-1] == ' ')
                {
                    if (i+1<5 && j-1>=0)
                    {
                        tablero[i+1][j-1] = 'O';
                        aumentar_puntaje(tablero, i+1, j-1, p_bot);
                        return true;
                    }
                }
                else if(tablero[i-1][j+1] == ' ' && tablero[i+1][j-1] == 'O')
                {
                    if(i-1>=0 && j+1<5)
                    {
                        tablero[i-1][j+1] = 'O';
                        aumentar_puntaje(tablero, i-1, j+1, p_bot);
                        return true;
                    }
                }
            }
            if (tablero[i][j] == ' ')
            {
                if(tablero[i][j-1] == 'O' && tablero[i][j+1] == 'O')
                {
                    tablero[i][j] = 'S';
                    aumentar_puntaje(tablero, i, j, p_bot);
                    return true;
                }
                if(tablero[i+1][j] == 'O' && tablero[i-1][j] == 'O')
                {
                    tablero[i][j] = 'S';
                    aumentar_puntaje(tablero, i, j, p_bot);
                    return true;
                }
                if(tablero[i+1][j+1] == 'O' && tablero[i-1][j-1] == 'O')
                {
                    tablero[i][j] = 'S';
                    aumentar_puntaje(tablero, i, j, p_bot);
                    return true;
                }
                if(tablero[i+1][j-1] == 'O' && tablero[i-1][j+1] == 'O')
                {
                    tablero[i][j] = 'S';
                    aumentar_puntaje(tablero, i, j, p_bot);
                    return true;
                }
            }
        }
    }
    return false;
}

void imprimir_puntaje_jugador(int p_1, int p_2)
{
    std::cout << "\n\x1B[3;31m" << "JUGADOR 1 => " << p_1 << "  " << "JUGADOR 2 => " << p_2 << "\x1B[m\n\n";
}

void imprimir_puntaje_bot(int p_1, int p_2)
{
    std::cout << "\n\x1B[3;31m" << "BOT => " << p_1 << "  " << "JUGADOR => " << p_2 << "\x1B[m\n\n";
}

void jugador_vs_jugador(char tablero[5][5], int turno, char jugador, int p_1, int p_2)
{   
    int fila;
    char columna;
    char letra;

    identificacion_alumno();
    letras_aleatorias(tablero);
    imprimir_tablero(tablero);
    std::cout << "\nPOR FAVOR INGRESE LOS DATOS EN LETRAS MAYUSCULAS\n\n";

    do
    {
        bool ocupado{false};

        std::cout << "Turno jugador " << jugador << "\n";

        std::cout << "\nIngrese fila (1-5): ";
        std::cin >> fila;
        std::cout << "Ingrese columna (A-E): ";
        std::cin >> columna;
        letra = escoger_letra();

        if(fila>5 || fila<1)
        {
            std::cout << "\nUPS! No existe fila\n";
            continue;
        }
        if(columna>69 || columna<65)
        {
            std::cout << "\nUPS! No existe columna\n";
            continue;
        }

        fila = fila-1;
        columna = columna-65;

        ocupado = ingresar_jugada(tablero, fila, columna, letra);

        identificacion_alumno();
        imprimir_tablero(tablero);

        if(ocupado)
        {
            std::cout << "\nUPS! Esta casilla esta ocupada\n";
            continue;
        }
        else
        {
            if(turno%2 == 1)
            {
                aumentar_puntaje(tablero, fila, columna, p_1);
                imprimir_puntaje_jugador(p_1, p_2);
            }
            else
            {
                aumentar_puntaje(tablero, fila, columna, p_2);
                imprimir_puntaje_jugador(p_1, p_2);
            }
        }

        if(turno%2 == 1)
        {
            jugador = '2';
        }
        else
        {
            jugador = '1';
        }

        if(turno == 20)
        {
            if(p_1 > p_2)
            {
                std::cout << "Ganador jugador 1!\n";
                break;
            }
            else if(p_2 > p_1)
            {
                std::cout << "Ganador jugador 2!\n";
                break;
            }
            else
            {
                std::cout << "EMPATE! Nadie gano\n";
                break;
            }
        }
        turno++;
    }
    while(turno <= 20);
}

void bot_vs_jugador(char tablero[5][5], int turno, char jugador, int p_bot, int p_2)
{
    int fila;
    char columna;
    char letra;

    identificacion_alumno();
    imprimir_tablero(tablero);

    srand(time(0));

    do
    {
        bool ocupado{false};

        if(turno%2 == 1)
        {
            ocupado = mas_punto_bot(tablero, p_bot);

            if(ocupado == false)
            {
                int rand_fila = std::rand() % 5;
                int rand_columna = std::rand() % 5;
                int rand_letra = 1 + (std::rand() % 2);
                char bot_let;

                if(rand_letra == 1)
                {
                    bot_let = 'S';
                }
                else
                {
                    bot_let = 'O';
                }

                ocupado = ingresar_jugada(tablero, rand_fila, rand_columna, bot_let);

                if(ocupado)
                {
                    continue;
                }
            }

            identificacion_alumno();
            imprimir_tablero(tablero);
            imprimir_puntaje_bot(p_bot, p_2);
        }
        else
        {
            std::cout << "\nPOR FAVOR INGRESE LOS DATOS EN LETRAS MAYUSCULAS\n\n";
            std::cout << "\nJugador ingrese fila (1-5): ";
            std::cin >> fila;
            std::cout << "Jugador ingrese columna (A-E): ";
            std::cin >> columna;
            letra = escoger_letra();

            fila = fila-1;
            columna = columna-65;

            ocupado = ingresar_jugada(tablero, fila, columna, letra);

            identificacion_alumno();
            imprimir_tablero(tablero);

            if(ocupado)
            {
                std::cout << "\nUPS! Esta casilla esta ocupada\n";
                continue;
            }
            else
            {
                aumentar_puntaje(tablero, fila, columna, p_2);
                imprimir_puntaje_jugador(p_bot, p_2);
            }
        }

        if(turno == 25)
        {
            if(p_bot > p_2)
            {
                std::cout << "Ganador bot!\n";
                break;
            }
            else if(p_2 > p_bot)
            {
                std::cout << "Ganador jugador!\n";
                break;
            }
            else
            {
                std::cout << "EMPATE! Nadie gano\n";
                break;
            }
        }
        turno++;
    }
    while(turno <= 25);
}