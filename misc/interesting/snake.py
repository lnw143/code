import turtle
import random
import time

window = turtle.Screen()
window.title("Snake Game")
window.bgcolor("white")
window.setup(width=600, height=600)
window.tracer(0)

head = turtle.Turtle()
head.shape("circle")
head.color("cyan")
head.penup()
head.goto(0, 0)
head.direction = "stop"
# head.

food = turtle.Turtle()
food.shape("circle")
food.color("red")
food.penup()
food.goto(random.randint(-290, 290), random.randint(-290, 290))

segments = []


def go_up():
    if head.direction != "down":
        head.direction = "up"


def go_down():
    if head.direction != "up":
        head.direction = "down"


def go_left():
    if head.direction != "right":
        head.direction = "left"


def go_right():
    if head.direction != "left":
        head.direction = "right"


window.listen()
window.onkey(go_up, "w")
window.onkey(go_down, "s")
window.onkey(go_left, "a")
window.onkey(go_right, "d")


def move():
    if head.direction == "up":
        y = head.ycor()
        head.sety(y + 5)

    if head.direction == "down":
        y = head.ycor()
        head.sety(y - 5)

    if head.direction == "left":
        x = head.xcor()
        head.setx(x - 5)

    if head.direction == "right":
        x = head.xcor()
        head.setx(x + 5)


game_is_on = True
while game_is_on:
    window.update()

    if head.xcor() > 290 or head.xcor() < -290 or head.ycor() > 290 or head.ycor() < -290:
        game_is_on = False
        print("Game Over")
        print("Score: ", len(segments))

    if head.distance(food) < 20:
        
        x = random.randint(-290, 290)
        y = random.randint(-290, 290)
        food.goto(x, y)

        new_segment = turtle.Turtle()
        new_segment.shape("circle")
        new_segment.color("cyan")
        new_segment.penup()
        segments.append(new_segment)

    for index in range(len(segments)-1, 0, -1):
        x = segments[index-1].xcor()
        y = segments[index-1].ycor()
        segments[index].goto(x, y)

    if len(segments) > 0:
        x = head.xcor()
        y = head.ycor()
        segments[0].goto(x, y)

    move()
    time.sleep(0.01)

window.mainloop()
