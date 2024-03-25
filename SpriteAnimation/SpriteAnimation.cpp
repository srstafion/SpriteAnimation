#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Enemy {
private:
    RectangleShape hitbox;
    Sprite enemySprite;
    static Texture enemyTexture;
    IntRect frameRect;
    Clock animationClock;
    int state = 1;
public:
    Enemy(Vector2f position) {
        hitbox.setSize(Vector2f(160, 160));
        hitbox.setFillColor(Color::Green);
        hitbox.setPosition(position);
        enemyTexture.loadFromFile("enemySprites2.png");
        frameRect = IntRect(0, 0, 32, 32);
        enemySprite.setTexture(enemyTexture);
        enemySprite.setScale(5, 5);
        enemySprite.setTextureRect(frameRect);
        enemySprite.setPosition(position);
    }

    FloatRect getGlobalBounds() {
        return hitbox.getGlobalBounds();
    }

    void handleClick() {
        switch (state) {
        case 1:
            state++;
            hitbox.setFillColor(Color::Yellow);
            frameRect.left += 32;
            break;
        case 2:
            state++;
            hitbox.setFillColor(Color::Red);
            frameRect.left += 32;
            break;
        case 3:
            state = 1;
            hitbox.setFillColor(Color::Green);
            frameRect.left = 0;
            break;
        }
        enemySprite.setTextureRect(frameRect);
    }

    void update() {
        if (animationClock.getElapsedTime().asSeconds() >= 1) {
            if (frameRect.top == 32) {
                frameRect.top = 0;
            }
            else frameRect.top += 32;
            enemySprite.setTextureRect(frameRect);
            animationClock.restart();
        }
    }

    void show(RenderWindow& window) {
        window.draw(hitbox);
        window.draw(enemySprite);
    }
};

int main()
{
    RenderWindow window(sf::VideoMode(960, 160), "Click on the Sprites!");
    vector<Enemy> enemies;
    for (int i = 0; i < 6; i++) {
        enemies.push_back(Enemy(Vector2f(i * 160, 0)));
    }
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed
                && event.mouseButton.button == Mouse::Left)
            {
                for (auto& enemy : enemies)
                {
                    Vector2f mousePosition = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (enemy.getGlobalBounds().contains(mousePosition))
                    {
                        enemy.handleClick();
                    }
                }
            }
        }
        window.clear();
        for (auto& i : enemies) {
            i.update();
            i.show(window);
        }
        window.display();
    }
}

Texture Enemy::enemyTexture;