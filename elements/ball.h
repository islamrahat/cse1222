#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class BallClass{
public:
    CircleShape bal;
    BallClass() : bal(10.0f)
    {
        cout << "Ball Created" << endl;
        bal.setPosition(20.f,20.0f);
        bal.setFillColor(Color::Green);
    } 
};