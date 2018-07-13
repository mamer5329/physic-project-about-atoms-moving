//
// Created by Adam Stelmaszyk on 18.04.2018.
//


#pragma once

#include <SFML/Graphics.hpp>
#include "atomy.h"
#include <iostream>
class doswiadczenie {
public:
    doswiadczenie(float t_X, float t_Y,int atomy);
    ~doswiadczenie()= default;

    void run();
    void processEvents();
    void update();
    void render();
    void positionR();
    void positionP();
    void napisy();
    void updateWartos();
    void entropia();


private:
    sf::RenderWindow nWindow;
    sf::CircleShape point;
    sf::Clock clock;
    sf::Text *text=new sf::Text[20];
    sf::Text *Wartosci=new sf::Text[20];
    sf::Text *Ped=new sf::Text[20];
    sf::Text ** Liczba_w_indekcie_R= new sf::Text *[2];
    sf::Text ** Nazwa_komorki_tekst_R= new sf::Text *[2];
    sf::Text ** Liczba_w_indekcie_P= new sf::Text *[2];
    sf::Text ** Nazwa_komorki_tekst_P= new sf::Text *[2];
    sf::Text Wypisz[5];
    sf::Font font;
    atomy *atomy1= new atomy[20];
    int liczba_tekstu=2;
    int P=1;
    int R=1;
    std::string * wartosc_x_atom= new std::string [2];
    std::string * wartosc_y_atom= new std::string [2];
    std::string * ped_x_atom= new std::string [2];
    std::string * ped_y_atom= new std::string [2];
    int liczba_1;




    int ** liczba_w_indeksach_R = new int * [2];
    int ** liczba_w_indeksach_P = new int * [2];
    int liczba_atmow;
    int a[5]{0,0,0,0,0};

    std::vector<int>nazwa;
    int liczba_atomy;



};


