//
// Created by Adam Stelmaszyk on 18.04.2018.
//

#pragma once

#include <SFML/Graphics.hpp>

class atomy: public sf::Drawable
{
public:
    atomy();
    ~atomy()= default;

    void active(float t_X, float t_Y,float ballRadious, float ballVelocity1);

    void updatePositionplus();
    void updatePositionminus();


    float left();
    float right();
    float top();
    float bottom();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    sf::Vector2f getPosition();

private:
    sf::CircleShape shape;
    int ballRadious;
    float zmienna;
    float ballVelocity;
    float abs(float liczba);
    float t_X;
    float t_Y;
    sf::Vector2f velocity;
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override ;







};



