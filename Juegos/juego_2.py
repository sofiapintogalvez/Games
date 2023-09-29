import pygame

pygame.init()

white = (255,255,255)
black = (0,0,0)

screen_size = (800,600)
player_witdh = 15
player_height = 90

screen = pygame.display.set_mode(screen_size)
pygame.display.set_caption("BARRAS Y PELOTA")
clock = pygame.time.Clock()

#Jugador 1
player1_x_coor = 50
player1_y_coor = 255
player1_y_speed = 0

#Jugador 2
player2_x_coor = 750 - player_witdh
player2_y_coor = 300 - 45
player2_y_speed = 0

#Pelota
pelota_x = 400
pelota_y = 300
pelota_speed_x = 3
pelota_speed_y = 3

game = True
while game:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game = False
        if event.type == pygame.KEYDOWN:
            #Jugador 1
            if event.key == pygame.K_w:
                player1_y_speed = -3
            if event.key == pygame.K_s:
                player1_y_speed = 3
            #Jugador 2
            if event.key == pygame.K_UP:
                player2_y_speed = -3
            if event.key == pygame.K_DOWN:
                player2_y_speed = 3
        if event.type == pygame.KEYUP:
            #Jugador 1
            if event.key == pygame.K_w:
                player1_y_speed = 0
            if event.key == pygame.K_s:
                player1_y_speed = 0
            #Jugador 2
            if event.key == pygame.K_UP:
                player2_y_speed = 0
            if event.key == pygame.K_DOWN:
                player2_y_speed = 0
        
    if pelota_y > 590 or pelota_y < 10:
        pelota_speed_y *= -1
    if pelota_x > 800 or pelota_x < 0:
        pelota_x = 400
        pelota_y = 300
        pelota_speed_x *= -1
        pelota_speed_y *= -1
    
    #Modifica coordenadas para movimiento jugadores
    player1_y_coor += player1_y_speed
    player2_y_coor += player2_y_speed

    #Movimiento pelota
    pelota_x += pelota_speed_x
    pelota_y += pelota_speed_y

    #Jugadores no se salgan ventana
    if player1_y_coor <= 0:
        player1_y_coor = 0
    elif player1_y_coor >= 600 - player_height:
        player1_y_coor = 600 - player_height
    if player2_y_coor <= 0:
        player2_y_coor = 0
    elif player2_y_coor >= 600 - player_height:
        player2_y_coor = 600 - player_height

    screen.fill(black)
    jugador1 = pygame.draw.rect(screen,white,(player1_x_coor,player1_y_coor,player_witdh,player_height))
    jugador2 = pygame.draw.rect(screen,white,(player2_x_coor,player2_y_coor,player_witdh,player_height))
    pelota = pygame.draw.circle(screen,white,(pelota_x,pelota_y),10)

    #Colisiones
    if pelota.colliderect(jugador1) or pelota.colliderect(jugador2):
        pelota_speed_x *= -1

    pygame.display.flip()
    clock.tick(60)
pygame.quit()