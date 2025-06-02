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
    RectangleShape square(Vector2f{100.0f,100.0f});
    square.setPosition(Vector2f{590.0f,310.0f});
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
        if(Keyboard::isKeyPressed(Keyboard::A)) square.move(Vector2f{-0.10f,0.0f});
        if(Keyboard::isKeyPressed(Keyboard::D)) square.move(Vector2f{0.10f,0.0f});
        if(Keyboard::isKeyPressed(Keyboard::W)) square.move(Vector2f{0.0f,-0.10f});
        if(Keyboard::isKeyPressed(Keyboard::S)) square.move(Vector2f{0.0f,0.10f});
        window.clear();
        window.draw(square);
        window.display();
    }
}