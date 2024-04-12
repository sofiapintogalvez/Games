#include <iostream>
#include "LibOso.h"

int main()
{   
    char tablero[5][5] = {
                            {' ', ' ', ' ', ' ', ' '}, 
                            {' ', ' ', ' ', ' ', ' '}, 
                            {' ', ' ', ' ', ' ', ' '}, 
                            {' ', ' ', ' ', ' ', ' '}, 
                            {' ', ' ', ' ', ' ', ' '}
                        };
    int turno{1};
    char jugador{'1'};
    int puntaje_1{0}, puntaje_2{0}, puntaje_bot{0};
    int menu;

    identificacion_alumno();

    std::cout << "\n\x1B[3;36m          MENU\n";
    std::cout << "(1) Jugador vs. Jugador\n";
    std::cout << "(2) Bot vs. Jugador\x1B[m\n";
    std::cout << "\nIngrese modo de juego: ";
    std::cin >> menu;

    if(menu == 1)
    {
        jugador_vs_jugador(tablero, turno, jugador, puntaje_1, puntaje_2);
    }
    else
    {
        bot_vs_jugador(tablero, turno, jugador, puntaje_bot, puntaje_2);
    }

	return 0;
}