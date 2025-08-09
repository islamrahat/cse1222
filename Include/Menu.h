#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

class Menu {
public:
    Text startText;
    Text aboutUsText;
    Text quitText;

    Menu(Font& font) {
        startText.setFont(font);
        startText.setCharacterSize(40);
        startText.setFillColor(Color::White);
        startText.setString("Start Game");
        startText.setPosition(860, 300);

        aboutUsText.setFont(font);
        aboutUsText.setCharacterSize(40);
        aboutUsText.setFillColor(Color::White);
        aboutUsText.setString("About Us");
        aboutUsText.setPosition(860, 400);

        quitText.setFont(font);
        quitText.setCharacterSize(40);
        quitText.setFillColor(Color::White);
        quitText.setString("Quit Game");
        quitText.setPosition(860, 500);
    }

    void draw(RenderWindow& window)
    {
        window.draw(startText);
        window.draw(aboutUsText);
        window.draw(quitText);
    }

    int handleInput(RenderWindow& window)
    {

        Event event;
        while (window.pollEvent(event))
        {
            if(event.type==Event::Closed) {
                window.close();
            } else if(event.type==Event::MouseButtonPressed) {
                Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));

                if(startText.getGlobalBounds().contains(mousePosition)) {
                    return 1; // Start Game
                } else if(aboutUsText.getGlobalBounds().contains(mousePosition)) {
                    return 2; // About Us
                } else if(quitText.getGlobalBounds().contains(mousePosition)) {
                    return 3; // Quit Game
                }
            } else if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::Escape) {
                    return 4; // Return to main menu
                }
            }
        }

        return 0; 
    }
};