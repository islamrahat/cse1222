#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
#include"Include/Menu.h"
#include"Include/Ball.h"
#include"Include/Paddle.h"
#include"Include/Brick.h"
using namespace sf;
using namespace std;


int main() {
    
    RenderWindow window(VideoMode::getFullscreenModes()[0], "Wiggado Break", Style::Fullscreen);

    SoundBuffer ballSoundBuff;
    if(!ballSoundBuff.loadFromFile("Assets/ball_collision.wav")) {}
    Sound ballSound;

    SoundBuffer gameOverBuff;
    if(!gameOverBuff.loadFromFile("Assets/gameOverSound.wav")) {}
    Sound gameOverSound;
    gameOverSound.setBuffer(gameOverBuff);
    gameOverSound.setVolume(80);
    bool soundFlag=true;

    SoundBuffer loadSoundBuff;
    if(!loadSoundBuff.loadFromFile("Assets/load.wav")) {}
    Sound loadSound;
    loadSound.setBuffer(loadSoundBuff);
    loadSound.setVolume(80);
    bool loadSoundFlag=true;

    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("Assets/notunLava.png")) {}
    Sprite backgroundSprite(backgroundTexture);

    Texture paddleTexture;
    if(!paddleTexture.loadFromFile("Assets/paddle_gray.png")) {}

    Paddle paddle(paddleTexture);
    paddle.setPosition(350, window.getSize().y-60);

    Ball ball(15);
    ball.setPosition(400, window.getSize().y-100);
    float ballSpeedX=2.5f;
    float ballSpeedY=-2.5f;

    Texture brickTexture;
    if(!brickTexture.loadFromFile("Assets/brick_golden.png")) {}


    for(int i=0; i<numBricksX; i++) {
        for(int j=0; j<numBricksY; j++) {
            Brick brick(brickTexture);
            brick.setPosition(i*(brickWidth+160)+10, j*(brickHeight+80)+20);

            bricks.push_back(brick);
        }
    }


    RectangleShape redLine(Vector2f(window.getSize().x, 50));
    redLine.setFillColor(Color::Red);
    redLine.setPosition(0, window.getSize().y-10);

    bool gameover=false;
    int score=0;

    Font font;
    if(!font.loadFromFile("Assets/ALIEN5.ttf")) {}
    Font PixelFont;
    if(!PixelFont.loadFromFile("Assets/PIXEL.otf")) {}
    Font GameOverFont;
    if(!GameOverFont.loadFromFile("Assets/GameOver.ttf")) {}

    Text scoreText;
    scoreText.setFont(PixelFont);
    scoreText.setCharacterSize(70);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: 0");
    scoreText.setPosition(10, 10);

    Text gameOverText;
    gameOverText.setFont(GameOverFont);
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::Yellow);
    gameOverText.setString("GAME OVER");
    FloatRect gameOverBounds=gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.left+gameOverBounds.width/2, gameOverBounds.top+gameOverBounds.height/2);
    gameOverText.setPosition(window.getSize().x/2, window.getSize().y/2);

    Menu menu(font);

    int menuChoice=0; // 0: No selection, 1: Start Game, 2: About Us, 3: Quit Game

    RectangleShape loadingBar(Vector2f{0,20});
    loadingBar.setFillColor(Color::Red);
    loadingBar.setPosition(Vector2f{0,550});
    float loadingTime=0;

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
                if(event.type==Event::Closed) {
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

    while (window.isOpen() && menuChoice==0) {
        menu.draw(window);
        window.display();
        menuChoice=menu.handleInput(window);
    }

    bool spaceToStart=true;
    float gameStartTime=0;
    RectangleShape gameStartLoad(Vector2f{0,550});
    gameStartLoad.setFillColor(Color::Red);
    gameStartLoad.setSize(Vector2f{1920,200});
    gameStartLoad.setPosition(Vector2f{1920,550});

    if(menuChoice==1) {
        // Start Game
        while (window.isOpen() && !gameover) {
            Event event;
            while (window.pollEvent(event)) {
                if(event.type==Event::Closed) {
                    window.close();
                }
            }
            
            while(gameStartTime<1920)
            {
                if(loadSoundFlag) {loadSound.play(); loadSoundFlag=false;}
                window.clear();
                window.draw(backgroundSprite);
                window.draw(paddle.sprite);
                window.draw(ball.shape);
                for(const auto& brick : bricks) {window.draw(brick.sprite);}
                window.draw(redLine);
                window.draw(gameStartLoad);
                window.display();
                gameStartTime+=2;
                gameStartLoad.move(Vector2f{-2,0});
            }

            if(Keyboard::isKeyPressed(Keyboard::Left) && paddle.sprite.getPosition().x>0) {
                paddle.move(-5, 0);
            }
            if(Keyboard::isKeyPressed(Keyboard::Right) &&
                paddle.sprite.getPosition().x+paddle.sprite.getGlobalBounds().width<window.getSize().x) {
                paddle.move(5, 0);
            }

            if(Keyboard::isKeyPressed(Keyboard::A) && paddle.sprite.getPosition().x>0) {
                paddle.move(-5, 0);
            }
            if(Keyboard::isKeyPressed(Keyboard::D) &&
                paddle.sprite.getPosition().x+paddle.sprite.getGlobalBounds().width<window.getSize().x) {
                paddle.move(5, 0);
            }

            if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                gameover=true;
                menuChoice=0;
            }

            ball.move(ballSpeedX, ballSpeedY);

            if(ball.shape.getPosition().x<0 || ball.shape.getPosition().x+ball.shape.getRadius()*0.1>window.getSize().x) {
                ballSpeedX=-ballSpeedX;
            }
            if(ball.shape.getPosition().y<0) {
                ballSpeedY=-ballSpeedY;
            }

            if(ball.shape.getGlobalBounds().intersects(paddle.sprite.getGlobalBounds())) {
                ballSpeedY=-ballSpeedY;
            }

            for(auto& brick : bricks) {
                if(ball.shape.getGlobalBounds().intersects(brick.sprite.getGlobalBounds())) {
                    brick.setPosition(-100, -100);
                    ballSpeedY=-ballSpeedY;
                    score++;
                    scoreText.setString("Score: "+to_string(score));
                }
            }

            // Check if all bricks are destroyed
            bool allBricksDestroyed=true;
            for(const auto& brick : bricks) {
                if(brick.sprite.getPosition().x != -100 || brick.sprite.getPosition().y != -100) {
                    allBricksDestroyed=false;
                    break;
                }
            }

            if(allBricksDestroyed) {
                gameover=true;
            }

            if(ball.shape.getPosition().y+ball.shape.getRadius()*2>redLine.getPosition().y) {
                gameover=true;
            }

            window.clear();
            window.draw(backgroundSprite);
            window.draw(paddle.sprite);
            window.draw(ball.shape);
            for(const auto& brick : bricks) {
                window.draw(brick.sprite);
            }
            window.draw(redLine);

            if(!gameover) {
                window.draw(scoreText);
            }

            if(gameover) {
                while (window.isOpen()) {
                    Event event;
                    while (window.pollEvent(event)) {
                        if(event.type==Event::Closed) {
                            window.close();
                        }
                        else if(event.type==Event::KeyPressed && event.key.code==Keyboard::Escape) {
                            return 0;
                        }
                    }
                    window.draw(gameOverText);
                    if(soundFlag) {gameOverSound.play(); soundFlag=false;}
                    window.display();
                    window.clear();
                }
            }

            window.display();
        }
    } else if(menuChoice==2) {
        // About Us
        Text aboutUs;
        aboutUs.setFont(font);
        aboutUs.setCharacterSize(50);
        aboutUs.setFillColor(Color::White);
        aboutUs.setString("Authors:\nMd. Samidul Islam (C243008)\nMohammad Rakibul Islam (C243152)\nShahrier Mahmud (C243027)\nMuhammad Rahatul Islam (C243007)");
        aboutUs.setPosition(660, 300);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if(event.type==Event::Closed) {
                    window.close();
                }
                else if(event.type==Event::KeyPressed && event.key.code==Keyboard::Escape) {
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
        } else if(menuChoice==3) {
            // Quit Game
            window.close();
        }

    return 0;
}
