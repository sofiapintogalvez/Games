def dibujar_base():
    t.penup()
    t.goto(-150,210)
    t.write("Ahorcado", font = ("Century Gothic", 50, "bold"))
    t.penup()
    t.pensize(5)
    t.goto(-240,-75)
    t.pendown()
    t.forward(160)
    t.backward(80)
    t.left(90)
    t.forward(250)
    t.right(90)
    t.forward(200)
    t.right(90)
    t.forward(25)
    t.pensize(1)

def cabeza():
    t.penup()
    x = 45
    y = 98
    t.goto(x-30,y+25)
    t.pendown()
    t.circle(25)

def cuerpo():
    t.penup()
    x = 45
    y = 98 
    t.goto(x-5,y-2)
    t.pendown()
    t.forward(80)

def pierna_derecha():
    t.penup()
    x = 45
    y = 98
    t.goto(x-5,y-81)
    t.pendown()
    t.left(45)
    t.forward(60)

def pierna_izquierda():
    t.penup()
    x = 45
    y = 98
    t.goto(x-5,y-81)
    t.pendown()
    t.right(95)
    t.forward(60)

def brazo_izquierdo():
    t.penup()
    x = 45
    y = 98
    t.goto(x-5,y-10)
    t.pendown()
    t.forward(60)

def brazo_derecho():
    t.penup()
    x = 45
    y = 98
    t.goto(x-5,y-10)
    t.pendown()
    t.right(265)
    t.forward(60)

def soga():
    t.penup()
    x = 45
    y = 98
    t.goto(x-60,y-2)
    t.pensize(3)
    t.setheading(0)
    t.pendown()        
    t.forward(100)

def menu():
    l = ["hola", "futbolista", "perro", "perros", "casa", "casas", "esternocleidomastoideo", "desoxirribonucleico", "electroencefalografista"]
    num = turtle.numinput("Game Menu", "Modo de juego\n(1) para un jugador\n(2) para dos jugadores")
    if num == 2:
        p = turtle.textinput("Player 1", "Ingrese palabra a adivinar:")
        guiones(p)
        ingresar_letras(p)
    elif num == 1:
        w = random.randint(0,len(l)-1)
        p2 = l[w]
        guiones(p2)
        ingresar_letras(p2)
    else:
        a = turtle.Turtle()
        a.hideturtle()
        a.write("No existe opcion", move = False, font = ("Century Gothic", 15, "normal"))
        a.clear()
        menu()

def guiones(p):
    g = turtle.Turtle()
    g.hideturtle()
    g.pensize(2)
    y = -170
    t = 40 if len(p) < 12 else 20
    e = 50 if len(p) < 12 else 30
    e2 = -25 if len(p) < 12 else -15
    for i in range(len(p)):
        g.penup()
        g.goto(e2*len(p)+e*i,y)
        g.pendown()
        g.forward(t)
        g.penup()

def ingresar_letras(p):
    x = 0
    y = -170
    u = turtle.Turtle()
    u.hideturtle()
    u.penup()
    u.goto(x-350,y-100)
    u.write("Usadas: ", move = True, font = ("Century Gothic", 20, "bold"))
    lista = []
    escribir = turtle.Turtle()
    escribir.hideturtle()
    vidas = 0
    ganador = ""
    while True:
        letra = turtle.textinput("Player 2", "Ingrese una letra:")
        m = turtle.Turtle()
        m.hideturtle()
        cont = 0
        if letra not in lista:
            lista.append(letra)
            u.write(f"{letra}, ", move = True, font = ("Century Gothic", 20, "bold"))
            e = 50 if len(p) < 12 else 30
            e2 = -25 if len(p) < 12 else -15
            t_e = 10 if len(p) < 12 else 5
            for i in range(len(p)):
                if p[i] == letra:
                    escribir.penup()
                    escribir.goto(e2*len(p)+e*i+t_e,y)
                    escribir.pendown()
                    escribir.write(letra.upper(), font=("Century Gothic", 20, "bold"))
                    ganador+=letra
                else:
                    cont+=1
            if len(ganador) == len(p):
                u.clear()
                m.penup()
                m.goto(x-210,y-90)
                m.pendown()
                m.color("green")
                m.write("¡GANASTE! Salvaste al ahorcado", font = ("Century Gothic", 20, "bold"))
                break
            if cont == len(p):
                vidas+=1
                if vidas == 1:
                    cabeza()
                if vidas == 2:
                    cuerpo()
                if vidas == 3:
                    pierna_derecha()
                if vidas == 4:
                    pierna_izquierda()
                if vidas == 5:
                    brazo_izquierdo()
                if vidas == 6:
                    brazo_derecho()
            if vidas == 6:
                u.clear()
                m.penup()
                m.goto(x-175,y-90)
                m.pendown()
                m.color("red")
                m.write("¡PERDISTE! Fuiste ahorcado", font = ("Century Gothic", 20, "bold"))
                soga()
                break
        else:
            m.penup()
            m.goto(x+150,y+100)
            m.pendown()
            m.write("¡ERROR! Ya uso esa letra", move = True, font = ("Century Gothic", 15, "normal"))
            m.undo()

import turtle
import random

w = 800
h = 600
t = turtle.Turtle()
v = turtle.Screen()
v.setup(w, h, None, None)
t.hideturtle()

y = 100
t.speed(5)
t.penup()
t.sety(-y)
t.pendown()
t.goto(-390,-y)
t.goto(390,-y)
t.penup()
t.sety(-2*y)
t.pendown()
t.goto(-390,-2*y)

dibujar_base()
menu()
turtle.done()