#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
#include"Include/Menu.h"
#include"Include/Ball.h"
#include"Include/Paddle.h"
#include"Include/Brick.h"
#include<thread>
using namespace sf;
using namespace std;


int main() {
    
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Wiggado Break", Style::Fullscreen);


    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Assets/lava.png")) {}
    Sprite backgroundSprite(backgroundTexture);

    Texture paddleTexture;
    if (!paddleTexture.loadFromFile("Assets/paddle_gray.png")) {}

    Paddle paddle(paddleTexture);
    paddle.setPosition(350, window.getSize().y - 60);

    Ball ball(15);
    ball.setPosition(400, window.getSize().y - 100);
    float ballSpeedX = 2.5f;
    float ballSpeedY = -2.5f;

    Texture brickTexture;
    if (!brickTexture.loadFromFile("Assets/brick_golden.png")) {}


    for (int i = 0; i < numBricksX; ++i) {
        for (int j = 0; j < numBricksY; ++j) {
            Brick brick(brickTexture);
            brick.setPosition(i * (brickWidth + 160) + 10, j * (brickHeight + 80) + 20);

            bricks.push_back(brick);
        }
    }


    RectangleShape redLine(Vector2f(window.getSize().x, 50));
    redLine.setFillColor(Color::Red);
    redLine.setPosition(0, window.getSize().y - 10);

    bool gameover = false;
    int score = 0;

    Font font;
    if (!font.loadFromFile("Assets/ALIEN5.ttf")) {}

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(80);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: 0");
    scoreText.setPosition(10, 10);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::White);
    gameOverText.setString("Game Over");
    FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2, gameOverBounds.top + gameOverBounds.height / 2);
    gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    Menu menu(font);

    int menuChoice = 0; // 0: No selection, 1: Start Game, 2: About Us, 3: Quit Game

    RectangleShape loadingBar(Vector2f{0,20});
    loadingBar.setFillColor(Color::Red);
    loadingBar.setPosition(Vector2f{0,550});
    float loadingTime = 0;

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
        if(loadingTime>1920) break;
        loadingBar.setSize(Vector2f{loadingTime,200});
        loadingTime++;
        window.clear();
        window.draw(loadingBar);
        window.display();
    }

    while (window.isOpen() && menuChoice == 0) {
        menu.draw(window);
        window.display();
        menuChoice = menu.handleInput(window);
    }

    if (menuChoice == 1) {
        // Start Game
        while (window.isOpen() && !gameover) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left) && paddle.sprite.getPosition().x > 0) {
                paddle.move(-5, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) &&
                paddle.sprite.getPosition().x + paddle.sprite.getGlobalBounds().width < window.getSize().x) {
                paddle.move(5, 0);
            }

            if (Keyboard::isKeyPressed(Keyboard::A) && paddle.sprite.getPosition().x > 0) {
                paddle.move(-5, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::D) &&
                paddle.sprite.getPosition().x + paddle.sprite.getGlobalBounds().width < window.getSize().x) {
                paddle.move(5, 0);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Return to main menu
                gameover = true;
                return 0;
                menuChoice = 0;
            }

            ball.move(ballSpeedX, ballSpeedY);

            if (ball.shape.getPosition().x < 0 || ball.shape.getPosition().x + ball.shape.getRadius() * 0.1 > window.getSize().x) {
                ballSpeedX = -ballSpeedX;
            }
            if (ball.shape.getPosition().y < 0) {
                ballSpeedY = -ballSpeedY;
            }

            if (ball.shape.getGlobalBounds().intersects(paddle.sprite.getGlobalBounds())) {
                ballSpeedY = -ballSpeedY;
            }

            for (auto& brick : bricks) {
                if (ball.shape.getGlobalBounds().intersects(brick.sprite.getGlobalBounds())) {
                    brick.setPosition(-100, -100);
                    ballSpeedY = -ballSpeedY;

                    // Increase score when the ball hits a brick
                    score++;
                    // Update the score text
                    scoreText.setString("Score: " + to_string(score));
                }
            }

            // Check if all bricks are destroyed
            bool allBricksDestroyed = true;
            for (const auto& brick : bricks) {
                if (brick.sprite.getPosition().x != -100 || brick.sprite.getPosition().y != -100) {
                    allBricksDestroyed = false;
                    break;
                }
            }

            if (allBricksDestroyed) {
                gameover = true;
            }

            if (ball.shape.getPosition().y + ball.shape.getRadius() * 2 > redLine.getPosition().y) {
                gameover = true;
                scoreText.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 40);
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(paddle.sprite);
            window.draw(ball.shape);
            for (const auto& brick : bricks) {
                window.draw(brick.sprite);
            }
            window.draw(redLine);

            if (!gameover) {
                window.draw(scoreText);
            }

            if (gameover) {
                window.draw(gameOverText);
            }

            window.display();
        }
    } else if (menuChoice == 2) {
        // About Us
        Text aboutUs;
        aboutUs.setFont(font);
        aboutUs.setCharacterSize(50);
        aboutUs.setFillColor(Color::White);
        aboutUs.setString("Authors:\nCmidul\nBruhKib\nXopnil\nBruhHat");
        aboutUs.setPosition(860, 300);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                    return 0;
                }
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(aboutUs);

            // Draw "Back" text
            Text backText;
            backText.setFont(font);
            backText.setCharacterSize(30);
            backText.setFillColor(Color::White);
            backText.setString("Back (Press ESC)");
            backText.setPosition(1620, 20);
            window.draw(backText);

            window.display();
        }
        } else if (menuChoice == 3) {
            // Quit Game
            window.close();
        }

    return 0;
}
