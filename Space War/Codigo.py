import random
import pygame

pygame.init()
pygame.mixer.init()

#Colores
black = (0,0,0)
white = (255,255,255)
green = (0,255,0)

#Dimensiones, nombre y fps ventana
width = 1280
height = 720
screen = pygame.display.set_mode((width,height))
pygame.display.set_caption("SPACE WAR")
clock = pygame.time.Clock()

#Imagenes y sonido
background = pygame.image.load("Imagenes/espacio0.png").convert()
icon = pygame.image.load("Imagenes/icono.jpeg")
laser_sound = pygame.mixer.Sound("Sonidos/laser.ogg")
explotion_sound = pygame.mixer.Sound("Sonidos/explosion.wav")
pygame.mixer.music.load("Sonidos/musica_fondo.mp3")
pygame.mixer.music.set_volume(0.2)
pygame.mixer.music.play(loops=-1)

#Pantalla inicio
def show_go_screen():
    screen.blit(background,(0,0))
    pygame.display.set_icon(icon)
    draw_text(screen,"SPACE WAR",65,width//2,height//4)
    draw_text(screen,"Based on Real Events, Imposible",27,width//2,height//2)
    draw_text(screen,"Press Key to Start",20,width//2,height*3/4)
    pygame.display.flip()
    waiting = True
    while waiting:
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.KEYUP:
                waiting = False

#Texto
def draw_text(surface,text,size,x,y):
    font = pygame.font.SysFont("impact",size)
    text_surface = font.render(text,True,white)
    text_rect = text_surface.get_rect()
    text_rect.midtop = (x,y)
    surface.blit(text_surface,text_rect)

#Barra de vida
def draw_shield_bar(surface,x,y,percentage):
    bar_lenght = 100
    bar_height = 10
    fill = (percentage/100) * bar_lenght
    border = pygame.Rect(x,y,bar_lenght,bar_height)
    fill = pygame.Rect(x,y,fill,bar_height)
    pygame.draw.rect(surface,green,fill)
    pygame.draw.rect(surface,white,border,2)

class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("Imagenes/nave.png").convert()
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.centerx = width // 2
        self.rect.bottom = height - 10
        self.speed_x = 0
        self.speed_y = 0
        self.shield = 100
    
    def update(self):
        self.speed_x = 0
        self.speed_y = 0
        keystate = pygame.key.get_pressed()
        if keystate[pygame.K_LEFT]:
            self.speed_x = -5
        if keystate[pygame.K_RIGHT]:
            self.speed_x = 5
        if keystate[pygame.K_UP]:
            self.speed_y = -5
        if keystate[pygame.K_DOWN]:
            self.speed_y = 5

        if self.rect.right > width:
            self.rect.right = width
        if self.rect.left < 0:
            self.rect.left = 0
        if self.rect.bottom > height:
            self.rect.bottom = height
        if self.rect.top < 0:
            self.rect.top = 0

        self.rect.x += self.speed_x
        self.rect.y += self.speed_y
    
    def shoot(self):
        bullet = Bullet("Imagenes/bala1.png",self.rect.centerx,self.rect.top)
        all_sprites.add(bullet)
        bullets.add(bullet)
        laser_sound.play()
    
    def shoot2(self):
        bullet2 = Bullet("Imagenes/laser2.png",self.rect.centerx,self.rect.top)
        all_sprites.add(bullet2)
        bullets.add(bullet2)
        laser_sound.play()

class Enemies(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("Imagenes/enemigo.png").convert()
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.x = random.randint(0,width)
        self.rect.y = random.randint(0,height//3)
        self.t_c_x = 5
        self.t_c_y = 1
    
    def update(self):
        if self.rect.right > width:
            self.t_c_x = -5
            Enemies.shoot(self)
        if self.rect.left < 0:
            Enemies.shoot(self)
            self.t_c_x = 5
        
        if self.rect.bottom > height - 200:
            self.t_c_y = -1
            Enemies.shoot(self)
        if self.rect.top < 0:
            self.t_c_y = 1
            Enemies.shoot(self)
        
        if self.rect.x == width//2:
            Enemies.shoot(self)
        if self.rect.y == height//2:
            Enemies.shoot(self)
        
        self.rect.x += self.t_c_x
        self.rect.y += self.t_c_y
    
    def shoot(self):
        bullet_enemie = Bullet_enemies_boss("Imagenes/bala2.png",self.rect.centerx,self.rect.bottom)
        all_sprites.add(bullet_enemie)
        bullets_enemie.add(bullet_enemie)

class Meteor(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = random.choice(meteor_images)
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.x = random.randrange(width - self.rect.width)
        self.rect.y = random.randrange(-140, -100)
        self.speedx = random.randrange(-5,5)
        self.speedy = random.randrange(1,10)

    def update(self):
        self.rect.x += self.speedx
        self.rect.y += self.speedy
        if self.rect.top > height + 10 or self.rect.left < -40 or self.rect.right > width + 40:
            self.rect.x = random.randrange(width - self.rect.width)
            self.rect.y = random.randrange(-100,-40)
            self.speedx = random.randrange(-5,5)
            self.speedy = random.randrange(1,10)

class Boss(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("Imagenes/boss.png").convert()
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.centerx = width//2
        self.rect.y = 3
        self.t_c_x = 5
        self.shield = 1000

    def update(self):
        if self.rect.right > width:
            self.t_c_x = -5
            Boss.shoot(self)
        if self.rect.left < 0:
            self.t_c_x = 5
            Boss.shoot(self)
        
        if self.rect.x == width//2 or self.rect.x == width//4:
            Boss.shoot(self)
        
        self.rect.x += self.t_c_x
    
    def shoot(self):
        bullet_boss = Bullet_enemies_boss("Imagenes/laser1.png",self.rect.centerx,self.rect.bottom)
        all_sprites.add(bullet_boss)
        bullets_boss.add(bullet_boss)

class Bullet(pygame.sprite.Sprite):
    def __init__(self,img,x,y):
        super().__init__()
        self.image = pygame.image.load(img).convert()
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.y = y
        self.rect.centerx = x
        self.speedy = -10
    
    def update(self):
        self.rect.y += self.speedy
        if self.rect.bottom < 0:
            self.kill()

class Bullet_enemies_boss(pygame.sprite.Sprite):
    def __init__(self,img,x,y):
        super().__init__()
        self.image = pygame.image.load(img).convert()
        self.image.set_colorkey(black)
        self.rect = self.image.get_rect()
        self.rect.y = y
        self.rect.centerx = x
        self.speedy = 10
    
    def update(self):
        self.rect.y += self.speedy
        if self.rect.bottom > height + 300:
            self.kill()

class Explosion(pygame.sprite.Sprite):
    def __init__(self,center):
        super().__init__()
        self.image = explosion_anim[0]
        self.rect = self.image.get_rect()
        self.rect.center = center
        self.frame = 0
        self.last_update = pygame.time.get_ticks()
        self.frame_rate = 50 #velocidad explosion

    def update(self):
        now = pygame.time.get_ticks()
        if now - self.last_update > self.frame_rate:
            self.last_update = now
            self.frame += 1
            if self.frame == len(explosion_anim):
                self.kill()
            else:
                center = self.rect.center
                self.image = explosion_anim[self.frame]
                self.rect = self.image.get_rect()
                self.rect.center = center

#Crear lista de imagenes meteoros
meteor_images = []
meteor_list = ["Imagenes/meteorGrey_big1.png","Imagenes/meteorGrey_big2.png","Imagenes/meteorGrey_big3.png","Imagenes/meteorGrey_big4.png",
				"Imagenes/meteorGrey_med1.png","Imagenes/meteorGrey_med2.png","Imagenes/meteorGrey_small1.png","Imagenes/meteorGrey_small2.png",
				"Imagenes/meteorGrey_tiny1.png","Imagenes/meteorGrey_tiny2.png"]
for img in meteor_list:
    meteor_images.append(pygame.image.load(img).convert())

#Explosiones
explosion_anim = []
for i in range(9):
    file = "Imagenes/regularExplosion0{}.png".format(i)
    img = pygame.image.load(file).convert()
    img.set_colorkey(black)
    img_scale = pygame.transform.scale(img,(70,70))
    explosion_anim.append(img_scale)

#Bucle principal
m = 0
cambiar_disparo = 1
cont = 0
cont2 = 0
game = True
run = True
while run:
    if game:
        show_go_screen()

        game = False

        #Listas de sprites
        all_sprites = pygame.sprite.Group()
        meteor_list = pygame.sprite.Group()
        bullets = pygame.sprite.Group( )
        bullets_enemie = pygame.sprite.Group()
        enemies_list = pygame.sprite.Group()
        bullets_boss = pygame.sprite.Group()

        player = Player()
        all_sprites.add(player)

        score = 0
        
        #Meteoros en pantalla
        for meteor in range(15):
            meteor = Meteor()
            all_sprites.add(meteor)
            meteor_list.add(meteor)

    #Presionar teclas
    clock.tick(60)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_TAB:
                cambiar_disparo += 1
            if event.key == pygame.K_SPACE and (cambiar_disparo%2 == 0):
                player.shoot2()
            elif event.key == pygame.K_SPACE and (cambiar_disparo%2 != 0):
                player.shoot()
    
    all_sprites.update()
    
    #Enemigos en pantalla
    if cont < 20:
        if len(meteor_list) == 0:
            if len(enemies_list) < 20:
                enemie = Enemies()
                all_sprites.add(enemie)
                enemies_list.add(enemie)
                cont += 1
            if len(enemies_list) > 0:
                enemie.shoot()
                
    #Colisiones enemigos-laser
    else:
        hits = pygame.sprite.groupcollide(enemies_list,bullets,True,True)
        for hit in hits:
            score += 10
            explotion_sound.play()
            explosion = Explosion(hit.rect.center)
            all_sprites.add(explosion)
            enemie.kill()

        #Colisiones jugador-enemigo
        if len(enemies_list) != 0:
            hits = pygame.sprite.spritecollide(player,enemies_list,True)
            for hit in hits:
                player.shield -= 10
                enemie = Enemies()
                all_sprites.add(enemie)
                enemies_list.add(enemie)

    #Boss en pantalla
    if cont2 < 1:
        if len(enemies_list) == 0 == len(meteor_list):
            boss = Boss()
            all_sprites.add(boss)  
            cont2 += 1
            boss.shoot()

    #Colisiones laser-boss
    else:
        hits = pygame.sprite.spritecollide(boss,bullets,True)
        for hit in hits:
            boss.shield -= 25
            score += 50
            explotion_sound.play()
            explosion = Explosion(hit.rect.center)
            all_sprites.add(explosion)
            if boss.shield == 0:
                screen.fill(black,(0,0))
                boss.kill()
                score += 500        

    #Colisiones meteoro-laser
    hits = pygame.sprite.groupcollide(meteor_list,bullets,True,True)
    if score <= 300:
        for hit in hits:
            score += 5
            explotion_sound.play()
            explosion = Explosion(hit.rect.center)
            all_sprites.add(explosion)
            meteor = Meteor()
            all_sprites.add(meteor)
            meteor_list.add(meteor)
    else:
        for hit in hits:
            score += 5
            explotion_sound.play()
            explosion = Explosion(hit.rect.center)
            all_sprites.add(explosion)

    #Colisiones jugador-meteoro
    hits = pygame.sprite.spritecollide(player,meteor_list,True)
    for hit in hits:
        player.shield -= 5
        meteor = Meteor()
        all_sprites.add(meteor)
        meteor_list.add(meteor)

    #Colisiones laser-enemigos-jugador
    hits = pygame.sprite.spritecollide(player,bullets_enemie,True)
    for hit in hits:
        player.shield -= 15
    
    #Colisiones laser-boss-jugador
    hits = pygame.sprite.spritecollide(player,bullets_boss,True)
    for hit in hits:
        player.shield -= 25
    
    #Fondo en movimiento
    m_relative = m % background.get_rect().height
    screen.blit(background,(0,m_relative - background.get_rect().height))
    if m_relative < height:
        screen.blit(background,(0,m_relative))
    m -= 5

    #Mostrar todos los sprites-imagenes
    all_sprites.draw(screen)

    #Mostrar score
    draw_text(screen,"Total Score: " + str(score),25,95,height-40)

    #Barra de vida
    draw_text(screen,"Life",15,1135,height-30)
    draw_shield_bar(screen,1155,height-25,player.shield)

    #Game over
    if player.shield <= 0:
        for i in range(500):
            screen.blit(background,(0,0))
            draw_text(screen,"GAME OVER",50,width//2,height//2)

    pygame.display.flip()
    
pygame.quit()