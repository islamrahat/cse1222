#include<SFML/Graphics.hpp>
#include"elements/ball.h"
#include"elements/paddle.h"
#include"elements/brick.h"
using namespace sf;
#define screenWidth 1280
#define screenHeight 720

int main()
{
    RenderWindow window(VideoMode(screenWidth,screenHeight),"New Window", Style::Default);
    RectangleShape square(Vector2f{200.0f,20.0f});
    square.setPosition(Vector2f{520.0f,680.0f});
    square.setFillColor(Color::Red);

    Ball newBall;
    Paddle newPaddle;
    Brick newBrick;

    while(window.isOpen())
    {
        Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type==ev.Closed) window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::A)) square.move(Vector2f{-0.20f,0.0f});
        if(Keyboard::isKeyPressed(Keyboard::D)) square.move(Vector2f{0.20f,0.0f});
        window.clear();
        window.draw(square);
        window.display();
    }
}