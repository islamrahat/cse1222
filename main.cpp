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
    int direction = -1;

    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type==ev.Closed) window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape)) {window.close();}

        // Bounds
            // Paddle
        if(paddle.getPosition().x<=0) {paddle.setPosition(0.0f,paddle.getPosition().y);}
        if(paddle.getPosition().x>=1080) {paddle.setPosition(1080,paddle.getPosition().y);}

            // Ball
        if(newBall.ball.getPosition().x<=0) {direction = -direction;}
        if(newBall.ball.getPosition().x>=1260) {direction = -direction;}
        if(newBall.ball.getPosition().y<=0) {direction = -direction;}
        
        newBall.ball.move(0,200.0f*direction*deltaTime);
        if(newBall.ball.getPosition().y>=660.0f)
        {
            if(newBall.ball.getPosition().x>=paddle.getPosition().x \
                && newBall.ball.getPosition().x+10<=paddle.getPosition().x+200.0f)
                {
                    direction = -direction;
                }
            else {window.close();}
        }

        // Movement
        if(Keyboard::isKeyPressed(Keyboard::A)) paddle.move(Vector2f{-500.0f*deltaTime,0.0f});
        if(Keyboard::isKeyPressed(Keyboard::D)) paddle.move(Vector2f{500.0f*deltaTime,0.0f});
        window.clear();
        window.draw(newBall.ball);
        window.draw(paddle);
        window.display();
    }

    RectangleShape loading(Vector2f{0.0f,50.0f});
    loading.setFillColor(Color::Cyan);
    loading.setPosition(0.0f,335.0f);
    int i=0;
    // Outro
    while(window.isOpen())
    {
        Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type==ev.Closed) window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape)) {window.close();}
        
        loading.setSize(Vector2f{i++,335.0f});
    }
}