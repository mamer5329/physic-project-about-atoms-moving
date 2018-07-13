//
// Created by Adam Stelmaszyk on 18.04.2018.
//

#include "doswiadczenie.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

doswiadczenie::doswiadczenie(float t_X, float t_Y, int liczba_atomy)  : nWindow(VideoMode(t_X,t_Y),"Doswiadczenie")
{
    srand(time(NULL));
    liczba_atmow=1;
    point.setRadius(2);
    point.setFillColor(Color::Red);

    for(int i=0; i<liczba_atomy; i++)
    {
        liczba_atmow=liczba_atmow*2;
    }
    std::cout<<liczba_atmow<<std::endl;
    R=2*liczba_atomy+1;
    P=liczba_atomy+(1-(liczba_atomy%2));
    this->liczba_atomy=liczba_atomy;


   liczba_w_indeksach_R = new int * [R];
    for(int i=0; i<R; i++)
    {
        liczba_w_indeksach_R[i]=new int [R];
    }



    liczba_w_indeksach_P = new int * [P];
    for(int i=0; i<P; i++)
    {
        liczba_w_indeksach_P[i]=new int [P];
    }
    for(int i=0; i<P; i++)
    {
        for(int j=0; j<P; j++)
        {
            liczba_w_indeksach_P[i][j]=0;
        }
    }


    atomy1=new atomy[liczba_atmow];
    for(int i=0; i<liczba_atmow; i++)
    {
        float pozycja_x = std::rand() % 800;
        float pozycja_y = std::rand() % 800;
        float szybkosc=1;

        int max_R=2*R;
         do{
            szybkosc = (std::rand() / float(RAND_MAX))*2-1;
        }while(szybkosc==0);
        atomy1[i].active(10, pozycja_y, 2, szybkosc);
    }

    text=new sf::Text[liczba_atmow];
    Wartosci=new sf::Text[liczba_atmow];
    Ped=new sf::Text[liczba_atmow];
    wartosc_x_atom= new std::string [liczba_atmow];
    wartosc_y_atom= new std::string [liczba_atmow];
    ped_x_atom= new std::string [liczba_atmow];
    ped_y_atom= new std::string [liczba_atmow];
    napisy();

    nWindow.setVerticalSyncEnabled(true);
    //nWindow.setFramerateLimit(10);
    for(int i=0; i<4; i++) 
    {
        Wypisz[i].setFillColor(Color::White);
        Wypisz[i].setPosition(900,600);
        Wypisz[i].setCharacterSize(30);
    }
    clock.restart();

    if (!font.loadFromFile("/Users/adamstelmaszyk/CLionProjects/projekt_na_fizyke/arial.ttf"))
    {
        std::cout<<"Czcionka"<<std::endl;

    }


    for(int i=0; i<5; i++) {

        Wypisz[i].setFillColor(Color::White);
        Wypisz[i].setFont(font);
    }

}



void doswiadczenie::run()
{
    while(nWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}


void doswiadczenie::processEvents()
{
    sf::Event event;
    while(nWindow.pollEvent(event))
    {
        if(event.type==sf::Event::Closed)
        {
            nWindow.close();
        }
    }
}

void doswiadczenie::update()
{


    for(int i=0 ;i<liczba_atmow; i++)
    {
        atomy1[i].updatePositionplus();
    }
    positionR();
    positionP();
    int liczba=clock.getElapsedTime().asSeconds();
    //if(liczba%2==0) {
        updateWartos();
    //}
    entropia();
}

void doswiadczenie::render()
{
    nWindow.clear();
    for(int i=0; i<4; i++) {

        nWindow.draw(Wypisz[i]);
    }
    for(int i=0; i<liczba_atmow; i++)
    {

        nWindow.draw(atomy1[i]);
    }
    long long lnP=0;
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<R; j++)
        {
            if(liczba_w_indeksach_R[i][j]>0)
            {
                lnP-=liczba_w_indeksach_R[i][j]*log(float(liczba_w_indeksach_R[i][j]))-liczba_w_indeksach_R[i][j];
            }

        }
    }
    lnP +=liczba_atmow*log(float(liczba_atmow))-liczba_atmow;

    nazwa.push_back(lnP);
    point.setPosition(900,700);

    for(int i=0; i<nazwa.size(); i++)
    {
        point.setPosition(point.getPosition().x,700-nazwa[i]/200);
        nWindow.draw(point);
        point.setPosition(point.getPosition().x+0.05,point.getPosition().y);
        int cos=clock.getElapsedTime().asSeconds();
        for(int j=0; j<5; j++)
        {



            if (nazwa[i] == (nazwa[nazwa.size() - 1]) && nazwa[i] > 0 && a[j] == 0 && (cos%12)==0 && liczba_1!=cos) {
                std::cout<<cos<<std::endl;
                int liczba = nazwa[i];
                Wypisz[j].setString(std::to_string(liczba));
                Wypisz[j].setCharacterSize(10);
                Wypisz[j].setPosition(850, point.getPosition().y - 3);
                a[j] = 1;
                liczba_1=cos;
            }
        }



    }

    /*for(int i=0; i<liczba_atmow; i++)
    {
        nWindow.draw(text[i]);
        nWindow.draw(Wartosci[i]);
        nWindow.draw(Ped[i]);
    }*/
    /*for(int i=0; i<R; i++) {
        for (int j = 0; j < R; j++)
        {
            nWindow.draw(Nazwa_komorki_tekst_R[i][j]);
            nWindow.draw(Liczba_w_indekcie_R[i][j]);


        }
    }
    for(int i=0; i<P; i++) {
        for (int j = 0; j < P; j++)
        {
            nWindow.draw(Nazwa_komorki_tekst_P[i][j]);
            nWindow.draw(Liczba_w_indekcie_P[i][j]);


        }
    }*/

    nWindow.display();
}

void doswiadczenie::positionR()
{
    int wartosc_jednej_kratki=800/R;
    int x,y;

    for(int i=0; i<R; i++)
    {
        for(int j=0; j<R; j++)
        {
            //std::cout<<"liczba i ... j "<<i<<"..."<<j<<std::endl;
            liczba_w_indeksach_R[i][j]=0;
            //std::cout<<liczba_w_indeksach_R[i][j]<<std::endl;
        }
    }

    for(int i=0; i<liczba_atmow; i++)
    {

        int komorka_x=0;
        int komorka_y=0;
        for( x=wartosc_jednej_kratki; x<810; x=x+wartosc_jednej_kratki)
        {
            if(atomy1[i].getPosition().x<x)
            {
                wartosc_x_atom[i]= std::to_string((komorka_x+1));
                break;
            }
            komorka_x=komorka_x+1;
        }

        for( y=wartosc_jednej_kratki; y<810; y=y+wartosc_jednej_kratki)
        {
            if(atomy1[i].getPosition().y<y)
            {
                wartosc_y_atom[i]= std::to_string((komorka_y+1));
                break;
            }
            komorka_y=komorka_y+1;
        }



        //std::cout<<std::endl;
        //std::cout<<std::endl;
        //std::cout<<"KOmorka x i y"<<komorka_x<<"..."<<komorka_y<<std::endl;
        if(komorka_x<R && komorka_y<R)
        {
            liczba_w_indeksach_R[komorka_x][komorka_y]=liczba_w_indeksach_R[komorka_x][komorka_y]+1;
            //std::cout << liczba_w_indeksach_R[komorka_x][komorka_y] << std::endl;
        }
    }
}

void doswiadczenie::positionP()
{
    int wartosc_jednej_kratki=800/P;
    int x,y;

    for(int i=0; i<P; i++)
    {
        for(int j=0; j<P; j++)
        {
            //std::cout<<"liczba i ... j "<<i<<"..."<<j<<std::endl;
            liczba_w_indeksach_P[i][j]=0;
            //std::cout<<liczba_w_indeksach_R[i][j]<<std::endl;
        }
    }


    for(int i=0; i<liczba_atmow; i++)
    {

        int komorka_x=0;
        int komorka_y=0;
        for( x=wartosc_jednej_kratki; x<810; x=x+wartosc_jednej_kratki)
        {
            if(atomy1[i].getPosition().x<x)
            {
                ped_x_atom[i]= std::to_string((komorka_x+1));


                break;
            }
            komorka_x=komorka_x+1;
        }

        for( y=wartosc_jednej_kratki; y<810; y=y+wartosc_jednej_kratki)
        {
            if(atomy1[i].getPosition().y<y)
            {
                ped_y_atom[i]= std::to_string((komorka_y+1));
                break;
            }
            komorka_y=komorka_y+1;
        }



        if(komorka_x<P && komorka_y<P)
        {
            liczba_w_indeksach_P[komorka_x][komorka_y]=liczba_w_indeksach_P[komorka_x][komorka_y]+1;
            //std::cout << liczba_w_indeksach_R[komorka_x][komorka_y] << std::endl;
        }
    }

}



void doswiadczenie::updateWartos()
{
    for(int i=0; i<liczba_atmow; i++)
    {
        Wartosci[i].setString(wartosc_x_atom[i]+" "+wartosc_y_atom[i]);
        Ped[i].setString(ped_x_atom[i]+" "+ped_y_atom[i]);
    }
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<R; j++)
        {
            std::string wyraz;
            wyraz=std::to_string(liczba_w_indeksach_R[i][j]);
            Liczba_w_indekcie_R[i][j].setString(wyraz);


        }
    }

    for(int i=0; i<P; i++)
    {
        for (int j = 0; j < P; j++)
        {
            std::string wyraz;
            wyraz=std::to_string(liczba_w_indeksach_P[i][j]);
            Liczba_w_indekcie_P[i][j].setString(wyraz);
        }
    }
}



void doswiadczenie::napisy() {
    if (!font.loadFromFile("/Users/adamstelmaszyk/CLionProjects/projekt_na_fizyke/arial.ttf"))
    {
        std::cout<<"Czcionka"<<std::endl;

    }

    int liczba=800/liczba_atmow;
    int liczba1=0;
    for(int i=0; i<liczba_atmow; i++)
    {
        text[i].setFont(font);
        text[i].setFillColor(sf::Color::White);
        std::string wyraz="Kulka nr: "+std::to_string(i+1);
        text[i].setString(wyraz);
        text[i].setPosition(sf::Vector2f(880,(0+liczba1)));
        text[i].setStyle(sf::Text::Bold);
        text[i].setCharacterSize(10);

        Wartosci[i].setFont(font);
        Wartosci[i].setFillColor(sf::Color::White);
        Wartosci[i].setStyle(sf::Text::Bold);
        Wartosci[i].setCharacterSize(10);
        Wartosci[i].setPosition(sf::Vector2f(980,(0+liczba1)));

        Ped[i].setFont(font);
        Ped[i].setFillColor(sf::Color::White);
        Ped[i].setStyle(sf::Text::Bold);
        Ped[i].setCharacterSize(10);
        Ped[i].setPosition(sf::Vector2f(1030,(0+liczba1)));
        liczba1=liczba+liczba1;
    }

    Liczba_w_indekcie_R= new sf::Text *[R];

    for(int i=0; i<R; i++)
    {
        Liczba_w_indekcie_R[i]=new Text [R];
    }

    Nazwa_komorki_tekst_R= new sf::Text *[R];
    for(int i=0; i<R; i++)
    {
        Nazwa_komorki_tekst_R[i]=new Text [R];
    }

    int liczba2=800/(R*R);
    int x1=1080, x2=1140;
    liczba1=0;
    int nastepna_linia=0;
    int przesuniecie=0;
    for(int i=0; i<R; i++)
    {
        if(i!=0 && i%6==0)
        {
            nastepna_linia=1;
            przesuniecie=1030;
            liczba1=0;
        } else{
            nastepna_linia=0;
            przesuniecie=0;
        }
         x1=x1+przesuniecie;
        x2=x2+przesuniecie;
        for(int j=0; j<R; j++)
        {
            Nazwa_komorki_tekst_R[i][j].setFont(font);
            Nazwa_komorki_tekst_R[i][j].setFillColor(sf::Color::White);
            Nazwa_komorki_tekst_R[i][j].setStyle(sf::Text::Bold);
            Nazwa_komorki_tekst_R[i][j].setCharacterSize(10);

            std::cout<<przesuniecie<<std::endl;
            Nazwa_komorki_tekst_R[i][j].setPosition(sf::Vector2f(x1,((liczba1)*2)));
            std::string wyraz="Poj: "+std::to_string(i+1)+":"+std::to_string(j+1);
            Nazwa_komorki_tekst_R[i][j].setString(wyraz);


            Liczba_w_indekcie_R[i][j].setFont(font);
            Liczba_w_indekcie_R[i][j].setFillColor(sf::Color::White);
            Liczba_w_indekcie_R[i][j].setStyle(sf::Text::Bold);
            Liczba_w_indekcie_R[i][j].setCharacterSize(10);

            Liczba_w_indekcie_R[i][j].setPosition(sf::Vector2f(x2,((liczba1)*2)));
            liczba1=liczba2+liczba1;
        }

    }


    Liczba_w_indekcie_P= new sf::Text *[P];

    for(int i=0; i<P; i++)
    {
        Liczba_w_indekcie_P[i]=new Text [P];
    }

    Nazwa_komorki_tekst_P= new sf::Text *[P];
    for(int i=0; i<P; i++)
    {
        Nazwa_komorki_tekst_P[i]=new Text [P];
    }


    int liczba3=800/(P*P);
    x1=1180, x2=1240;
    liczba1=0;
    nastepna_linia=0;
    przesuniecie=0;
    for(int i=0; i<P; i++)
    {
        if(i!=0 && i%6==0)
        {
            nastepna_linia=1;
            przesuniecie=1030;
            liczba1=0;
        } else{
            nastepna_linia=0;
            przesuniecie=0;
        }
        x1=x1+przesuniecie;
        x2=x2+przesuniecie;
        for(int j=0; j<P; j++)
        {
            Nazwa_komorki_tekst_P[i][j].setFont(font);
            Nazwa_komorki_tekst_P[i][j].setFillColor(sf::Color::White);
            Nazwa_komorki_tekst_P[i][j].setStyle(sf::Text::Bold);
            Nazwa_komorki_tekst_P[i][j].setCharacterSize(10);

            std::cout<<przesuniecie<<std::endl;
            Nazwa_komorki_tekst_P[i][j].setPosition(sf::Vector2f(x1,((liczba1)*2)));
            std::string wyraz="Poj: "+std::to_string(i+1)+":"+std::to_string(j+1);
            Nazwa_komorki_tekst_P[i][j].setString(wyraz);


            Liczba_w_indekcie_P[i][j].setFont(font);
            Liczba_w_indekcie_P[i][j].setFillColor(sf::Color::White);
            Liczba_w_indekcie_P[i][j].setStyle(sf::Text::Bold);
            Liczba_w_indekcie_P[i][j].setCharacterSize(10);

            Liczba_w_indekcie_P[i][j].setPosition(sf::Vector2f(x2,((liczba1)*2)));
            liczba1=liczba2+liczba1;
        }

    }

}


void doswiadczenie::entropia()
{
    long long lnP=0;
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<R; j++)
        {
            if(liczba_w_indeksach_R[i][j]>0)
            {
                lnP-=liczba_w_indeksach_R[i][j]*log(float(liczba_w_indeksach_R[i][j]))-liczba_w_indeksach_R[i][j];
            }

        }
    }
    lnP +=liczba_atmow*log(float(liczba_atmow))-liczba_atmow;
    std::cout<<lnP<<std::endl;
    nazwa.push_back(lnP);
    point.setPosition(900,700);
    for(int i=0; i<nazwa.size(); i++)
    {
        point.setPosition(point.getPosition().x,700+lnP/10000);
        nWindow.draw(point);
        point.setPosition(point.getPosition().x+0.5,point.getPosition().y);

    }

}