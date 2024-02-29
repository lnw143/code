import pygame
import random

# 初始化Pygame
pygame.init()

# 设置游戏窗口
win_width = 800
win_height = 600
win = pygame.display.set_mode((win_width, win_height))
pygame.display.set_caption("小游戏")

# 设置游戏变量
player_x = 50
player_y = 50
player_width = 50
player_height = 50
player_speed = 5

enemy_x = 700
enemy_y = 50
enemy_width = 50
enemy_height = 50
enemy_speed = 3

# 游戏主循环
running = True
while running:
    pygame.time.delay(50)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        player_x -= player_speed
    if keys[pygame.K_RIGHT]:
        player_x += player_speed
    if keys[pygame.K_UP]:
        player_y -= player_speed
    if keys[pygame.K_DOWN]:
        player_y += player_speed

    # 更新敌人位置
    enemy_x -= enemy_speed
    if enemy_x <= 0:
        enemy_x = 800
        enemy_y = random.randint(50, 550)

    # 绘制游戏场景
    win.fill((255, 255, 255))
    pygame.draw.rect(win, (255, 0, 0), (player_x, player_y, player_width, player_height))
    pygame.draw.rect(win, (0, 0, 255), (enemy_x, enemy_y, enemy_width, enemy_height))
    pygame.display.update()

pygame.quit()