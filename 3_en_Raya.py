def ingresar_posicion_en_tablero(tabla,jugador):
    while True:
        fila = int(input("Jugador " + jugador + " ingrese fila (entre 0 y 2): "))
        columna = int(input("Jugador " + jugador + " ingrese columna (entre 0 y 2): "))
        print("="*50)
        if (fila < 0 or fila > 2) and (columna < 0 or columna > 2):
            print("Fila y columna no existentes, ingrese de nuevo")
            print()
        elif fila < 0 or fila > 2:
            print("Fila no existente, ingrese de nuevo")
            print()
        elif columna < 0 or columna > 2:
            print("Columna no existente, ingrese de nuevo")
            print()
        elif tabla[fila][columna] != " ":
            print("La posición está ocupada, ingrese de nuevo")
            print()
        else:
            tabla[fila][columna] = jugador
            break

def mostrar_tablero(tabla):
    print("TABLERO")
    for fila in range(len(tabla)):
        for columna in range(len(tabla[fila])):
            print(tabla[fila][columna] + "|", end="")
        print()

def ganador_juego(tabla,jugador):
    cont = 0
    if tabla[0][0] == jugador == tabla[1][1] == tabla[2][2]:
        print("¡FELICIDADES!")
        print("El jugador", jugador, "ganó el juego")
        winner = True
        return winner
    elif tabla[0][2] == jugador == tabla[1][1] == tabla[2][0]:
        print("¡FELICIDADES!")
        print("El jugador", jugador, "ganó el juego")
        winner = True
        return winner
    else:
        for fila in range(len(tabla)):
            for columna in range(len(tabla[fila])):
                if tabla[fila][columna] == jugador:
                    cont += 1
                if cont == 3:
                    print("¡FELICIDADES!")
                    print("El jugador", jugador, "ganó el juego")
                    winner = True
                    return winner
            cont = 0
        for columna in range(len(tabla)):
            for fila in range(len(tabla[columna])):
                if tabla[fila][columna] == jugador:
                    cont += 1
                if cont == 3:
                    print("¡FELICIDADES!")
                    print("El jugador", jugador, "ganó el juego")
                    winner = True
                    return winner
            cont = 0
    for fila in range(len(tabla)):
        for columna in range(len(tabla[fila])):
            if tabla[fila][columna] != " ":
                cont += 1
    if cont == 9:
        print("Se llegó a un empate")
        winner = True
        return winner
    winner = False
    return winner

import random
tablero = [[" ", " ", " "],[" ", " ", " "],[" ", " ", " "]]
jugador_1 = "X"
jugador_2 = "O"
inicio = random.randint(1,2)
if inicio == 1:
    print("Comienza el jugador X")
    print("="*50)
else:
    print("Comienza el jugador O")
    print("="*50)
while True:
    mostrar_tablero(tablero)
    if inicio%2 == 0:
        player = jugador_2
    if inicio%2 != 0:
        player = jugador_1
    ingresar_posicion_en_tablero(tablero,player)
    inicio+=1
    winner = ganador_juego(tablero,player)
    if winner == True:
        mostrar_tablero(tablero)
        break