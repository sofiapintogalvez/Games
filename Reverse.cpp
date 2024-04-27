// Hacer el juego Reverse con punteros

#include <iostream>
#include <cstdlib>

using namespace std;

void print(char(*A)[8])
{
    int n{ 0 };

    cout << "   0   1   2   3   4   5   6   7\n";
    for (char(*p)[8] = A; p < A + 8; p++)
    {
        cout << n << " | ";
        for (char* q = *p; q < *(p + 1); q++)
            cout << *q << " | ";
        cout << endl;
        n++;
    }
}

bool Fin(char(*A)[8])
{
    for (char(*p)[8] = A; p < A + 8; p++)
    {
        for (char* q = *p; q < *(p + 1); q++)
        {
            if (*q == ' ')
                return false;
        }
    }
    return true;
}

void Arriba(char(*A)[8], int fil, int col, char player)
{
    for (char f = fil - 1; f >= 0; f--)
    {
        if (*(*(A + f) + col) == player)
        {
            for (char f2 = fil - 1; f2 > f; f2--)
                *(*(A + f2) + col) = player;
            break;
        }
        else if (*(*(A + f) + col) == ' ')
            break;
    }
}

void Abajo(char(*A)[8], int fil, int col, char player)
{
    for (char f = fil + 1; f < 8; f++)
    {
        if (*(*(A + f) + col) == player)
        {
            for (char f2 = fil + 1; f2 < f; f2++)
                *(*(A + f2) + col) = player;
            break;
        }
        else if (*(*(A + f) + col) == ' ')
            break;
    }
}

void Izquierda(char(*A)[8], int fil, int col, char player)
{
    for (char c = col - 1; c >= 0; c--)
    {
        if (*(*(A + fil) + c) == player)
        {
            for (char c2 = col - 1; c2 > c; c2--)
                *(*(A + fil) + c2) = player;
            break;
        }
        else if (*(*(A + fil) + c) == ' ')
            break;
    }
}

void Derecha(char(*A)[8], int fil, int col, char player)
{
    for (char c = col + 1; c < 8; c++)
    {
        if (*(*(A + fil) + c) == player)
        {
            for (char c2 = col + 1; c2 < c; c2++)
                *(*(A + fil) + c2) = player;
            break;
        }
        else if (*(*(A + fil) + c) == ' ')
            break;
    }
}

bool Posicion(char(*A)[8], int fil, int col, char player)
{
    if (*(*(A + fil) + col) != ' ')
        return false;
    *(*(A + fil) + col) = player;

    Izquierda(A, fil, col, player);
    Derecha(A, fil, col, player);
    Arriba(A, fil, col, player);
    Abajo(A, fil, col, player);

    return true;
}

void Puntaje(char(*A)[8], int& x, int& o)
{
    x = 0;
    o = 0;

    for (char* p = *A; p < *(A + 8); p++)
    {
        if (*p == 'x')
            x++;

        else if (*p == 'o')
            o++;
    }
}

int main()
{
    int fila, columna, ptj_x, ptj_o;
    char jugador{ 'x' };

    char A[8][8] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', 'x', 'o', ' ', ' ', ' '},
                     {' ', ' ', ' ', 'o', 'x', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    print(A);
    Puntaje(A, ptj_x, ptj_o);
    cout << "\n\tX = " << ptj_x << "\tO = " << ptj_o << "\n\n";

    do
    {
        cout << "Turno jugador " << jugador << "\n\n";
        cout << "Ingrese fila: ";
        cin >> fila;
        cout << "Ingrese columna: ";
        cin >> columna;

        if (Posicion(A, fila, columna, jugador))
        {
            if (jugador == 'x')
                jugador = 'o';
            
            else
                jugador = 'x';
        }

        system("cls");
        print(A);
        Puntaje(A, ptj_x, ptj_o);
        cout << "\n\tX = " << ptj_x << "\tO = " << ptj_o << "\n\n";
    } while (!Fin(A));

    if (ptj_x > ptj_o)
        cout << "\nGanaron las x\n";
    else if (ptj_o > ptj_x)
        cout << "\nGanaron las o\n";
    else
        cout << "\nEmpate\n";
}