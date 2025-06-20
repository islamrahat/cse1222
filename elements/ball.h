#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#define screenWidth 1280
#define screenHeight 720

class BallClass{
public:
    CircleShape ball;
    BallClass() : ball(10.0f)
    {
        cout << "Ball Created" << endl;
        ball.setPosition(screenWidth/2,660.0f);
        ball.setFillColor(Color::Green);
    } 
};