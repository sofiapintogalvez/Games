import pygame
import random
import math
from pygame import mixer

pygame.init()

L = 800
A = 600
ventana = pygame.display.set_mode((L,A))

icon_juego = pygame.image.load("Imagenes/ic_juego.jpg")
fondo_juego = pygame.image.load("Imagenes/fondo2.jpg")
nave_juego = pygame.image.load("Imagenes/nave.png")
marc_juego = pygame.image.load("Imagenes/marciano5.png")
bala_juego = pygame.image.load("Imagenes/bala.png")

mixer.music.load("Sonidos/sonido_fondo.mp3")
mixer.music.play(-1)

pygame.display.set_icon(icon_juego)
pygame.display.set_caption("Primer Juego")

nave_p_i_L = L//2-(nave_juego.get_size()[0]//2)
nave_p_i_A = A-nave_juego.get_size()[1]

marc_p_i_L = random.randint(0,L-marc_juego.get_size()[0])
marc_p_i_A = random.randint(0,A//3)

bala_p_i_L = nave_p_i_L
bala_p_i_A = nave_p_i_A

nave_t_c_L = 0
marc_t_c_L = 0.3
marc_t_c_A = 10
bala_t_c_A = 0.3
bala_estado = "Listo"

puntaje = 0
tipo_letra = pygame.font.Font("freesansbold.ttf",28)
tipo_letra_go = pygame.font.Font("freesansbold.ttf",43)
letra_p_i_L = 10
letra_p_i_A = 10

def nave(x,y):
    ventana.blit(nave_juego,(x,y))

def marc(x,y):
    ventana.blit(marc_juego,(x,y))

def disparar_bala(x,y):
    global bala_estado
    bala_estado = "disparado"
    ventana.blit(bala_juego,(x,y))

def hubo_colision(x1,x2,y1,y2):
    distancia = math.sqrt(math.pow(x1-x2,2) + math.pow(y1-y2,2))
    return True if distancia < 50 else False

def mostrar_puntaje(x,y):
    puntaje_render = tipo_letra.render("Score: " + str(puntaje), True, (255,255,255))
    ventana.blit(puntaje_render,(x,y))

def mostrar_fin():
    fin_render = tipo_letra_go.render("GAME OVER", True, (255,255,255))
    x = L//2 - (fin_render.get_size()[0]//2)
    y = A//2 - (fin_render.get_size()[1]//2)
    ventana.blit(fin_render,(x,y))

correr = True
while correr:
    ventana.blit(fondo_juego,(0,0))
    for evento in pygame.event.get():
        if evento.type == pygame.QUIT:
            correr = False
        if evento.type == pygame.KEYDOWN:
            if evento.key == pygame.K_LEFT:
                nave_t_c_L -= 0.4
            if evento.key == pygame.K_RIGHT:
                nave_t_c_L += 0.4
            if evento.key == pygame.K_SPACE:
                if bala_estado == "Listo":
                    sonido_bala = mixer.Sound("Sonidos/bala.wav")
                    sonido_bala.play()
                    bala_p_i_L = nave_p_i_L + (nave_juego.get_size()[0]//2 - bala_juego.get_size()[0]//2)
                    disparar_bala(bala_p_i_L,bala_p_i_A)
        if evento.type == pygame.KEYUP:
            if (evento.key == pygame.K_LEFT) or (evento.key == pygame.K_RIGHT):
                nave_t_c_L = 0

    nave_p_i_L+=nave_t_c_L
    if nave_p_i_L <= 0:
        nave_p_i_L = 0
    elif nave_p_i_L >= L-nave_juego.get_size()[0]:
        nave_p_i_L = L-nave_juego.get_size()[0]
    nave(nave_p_i_L,nave_p_i_A)
    
    if marc_p_i_A + marc_juego.get_size()[1] >= nave_p_i_A:
        marc_p_i_A = A
        mostrar_fin()
        
    marc_p_i_L+=marc_t_c_L
    if marc_p_i_L <= 0:
        marc_t_c_L += 0.3
        marc_p_i_A += marc_t_c_A
    elif marc_p_i_L >= L-marc_juego.get_size()[0]:
        marc_t_c_L = -0.3
        marc_p_i_A += marc_t_c_A
    marc(marc_p_i_L,marc_p_i_A)

    if bala_p_i_A <= 0:
       bala_p_i_A = nave_p_i_A
       bala_estado = "Listo"
    if bala_estado == "disparado":
        disparar_bala(bala_p_i_L,bala_p_i_A)
        bala_p_i_A -= bala_t_c_A
    
    colision = hubo_colision(bala_p_i_L,marc_p_i_L,bala_p_i_A,marc_p_i_A)
    if colision:
        sonido_explo = mixer.Sound("Sonidos/explosion.wav")
        sonido_explo.play()
        puntaje += 1
        bala_estado = "Listo"
        bala_p_i_A = nave_p_i_A
        marc_p_i_L = random.randint(0,L-marc_juego.get_size()[0])
        marc_p_i_A = random.randint(0,A//3)

    mostrar_puntaje(letra_p_i_L,letra_p_i_A)
    pygame.display.update()