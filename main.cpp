#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"elements/ball.h"
#include"elements/paddle.h"
#include"elements/brick.h"
using namespace sf;
#define screenWidth 1280
#define screenHeight 720

int main()
{
    RenderWindow window(VideoMode(screenWidth,screenHeight),"New Window", Style::Default);
    RectangleShape paddle(Vector2f{200.0f,20.0f});
    paddle.setPosition(Vector2f{520.0f,680.0f});
    paddle.setFillColor(Color::Red);

    BallClass newBall;
    PaddleClass newPaddle;
    BrickClass newBrick;

    Clock clock;

    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type==ev.Closed) window.close();
        }

        // Bounds
        if(paddle.getPosition().x<=0) {paddle.setPosition(0.0f,paddle.getPosition().y);}
        if(paddle.getPosition().x>=1080) {paddle.setPosition(1080,paddle.getPosition().y);}

        // Movement
        if(Keyboard::isKeyPressed(Keyboard::A)) paddle.move(Vector2f{-500.0f*deltaTime,0.0f});
        if(Keyboard::isKeyPressed(Keyboard::D)) paddle.move(Vector2f{500.0f*deltaTime,0.0f});
        window.clear();
        window.draw(newBall.bal);
        window.draw(paddle);
        window.display();
    }
}