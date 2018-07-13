//
// Created by Adam Stelmaszyk on 18.04.2018.
//

#include "atomy.h"
#include <iostream>

atomy::atomy() {}

using namespace sf;

void atomy::active(float t_X, float t_Y, float ballRadious, float ballVelocity1)
{

    //srand(time(NULL));
    this->ballRadious=ballRadious;

    shape.setPosition(t_X,t_Y);
    shape.setRadius(this->ballRadious);
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(this->ballRadious,this->ballRadious);
    ballVelocity=ballVelocity1;
    velocity.y=(std::rand() / float(RAND_MAX))*2-1;
    velocity.x=(std::rand() / float(RAND_MAX))*2-1;


}

void atomy::draw(RenderTarget &target, RenderStates state) const
{
    target.draw(this->shape);
}

void atomy::updatePositionplus()
{
    shape.move(velocity);


    if(this->left() <0)
    {
        velocity.x = abs(ballVelocity);
    }else if(this->right() > 800)
    {
        velocity.x =-abs(ballVelocity);
    }



    if(this->top() <0)
    {
        velocity.y =abs(ballVelocity);
    }else if(this->bottom() > 800)
    {
        velocity.y =-abs(ballVelocity);
    }


}

void atomy::updatePositionminus()
{
    shape.move(velocity);


    std::cout<<"Pozycja :"<<shape.getPosition().x<<std::endl;
    if(shape.getPosition().x <0)
    {
        std::cout<<"Pozycja :"<<shape.getPosition().x<<std::endl;
        velocity.x = abs(ballVelocity);
        std::cout<<velocity.x<<std::endl;
    }else if(shape.getPosition().x > 800)
    {
        velocity.x = -abs(ballVelocity);
    }



    if(shape.getPosition().y <0)
    {
        velocity.y = abs(ballVelocity);
    }else if(shape.getPosition().y > 800)
    {
        velocity.y = -abs(ballVelocity);
    }


}

float atomy::left()
{
    return this->shape.getPosition().x - shape.getRadius();
}


float atomy::right()
{
    return this->shape.getPosition().x + shape.getRadius();
}

float atomy::top()
{
    return this->shape.getPosition().y - shape.getRadius();
}

float atomy::bottom()
{
    return this->shape.getPosition().y + shape.getRadius();
}



void atomy::moveDown()
{
    this->velocity.y = ballVelocity;
}
void atomy::moveUp()
{
    this->velocity.y = -ballVelocity;
}
void atomy::moveRight()
{
    this->velocity.x = ballVelocity;
}
void atomy::moveLeft()
{
    this->velocity.x = -ballVelocity;
}


Vector2f atomy::getPosition()
{
    return shape.getPosition();
}

float atomy::abs(float liczba)
{
    if( liczba<0)
    {
        return -liczba;
    }
    else
    {
        return liczba;
    }
}