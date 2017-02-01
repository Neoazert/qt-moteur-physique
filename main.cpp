#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <QPushButton>

#include "Objet.h"
#include "Cercle.h"
#include "constantes.h"
#include "Info_collision.h"
#include "collision.h"
#include "DisplayUI.h"
#include "coord.h"

#include "QtWidgets/qwidget.h"
#include "QtWidgets/qapplication.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);





    sf::RenderWindow fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "Moteur Physique");
    fenetre.setPosition(sf::Vector2i(350, 50));


    vector<Cercle> tab_cercle;
    vector<Objet> tab_objets;
    coord last_mouse_click;
    last_mouse_click.x =50;
    last_mouse_click.y =50;

    buttonStatut stat;



    DisplayUI ui(&stat,&fenetre,&tab_cercle,&tab_objets,&last_mouse_click);
    ui.show();



    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (fenetre.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event evenement;
        while (fenetre.pollEvent(evenement))
        {

            // évènement "fermeture demandée" : on ferme la fenêtre
            switch(evenement.type)
            {
                case sf::Event::Closed :
                    fenetre.close();
                    exit(0);
                    break;

                case sf::Event::MouseButtonPressed :

                    if (evenement.mouseButton.button == sf::Mouse::Left)
                    {

                      last_mouse_click.x = evenement.mouseButton.x;
                      last_mouse_click.y = evenement.mouseButton.y;


                        if(stat.mode == 1)
                        {
                          Cercle crcl(sf::Mouse::getPosition(fenetre), &fenetre,stat.rayon,5,5);
                          crcl.setCoeff_elasticite(stat.elasticite +0.01);
                          crcl.set_masse(stat.masse);
                          tab_cercle.push_back(crcl);
                         }



                        else if(stat.mode == 2)
                        {

                          Objet obj(sf::Mouse::getPosition(fenetre), &fenetre);
                          if(obj.get_termine() == true){
                                sf::Vector2f v(1,1);
                                obj.set_vitesse(v);
                                obj.set_vitesse_angulaire(0.06);
                                obj.set_masse(1);
                                obj.setCoeff_elasticite(1);
                                tab_objets.push_back(obj);

                            }
                        }

                        else if(stat.mode == 3)
                        {
                            sf::Vector2i souris = sf::Mouse::getPosition(fenetre);
                            std::vector<sf::Vertex> tab;
                            sf::Vertex point;

                            point.position.x = souris.x;
                            point.position.y = souris.y;
                            tab.push_back(point);

                            point.position.x += stat.longueur;
                            tab.push_back(point);

                            point.position.y += stat.longueur;
                            tab.push_back(point);

                            point.position.x -= stat.longueur;
                            tab.push_back(point);

                            point.position.y -= stat.longueur;
                            tab.push_back(point);

                            Objet obj(tab);

                            sf::Vector2f v(1,1);
                            obj.set_vitesse(v);
                            obj.set_vitesse_angulaire(0.06);
                            obj.set_masse(1);
                            obj.setCoeff_elasticite(1);
                            tab_objets.push_back(obj);

                        }

                        else if(stat.mode == 4)
                        {
                            sf::Vector2i souris = sf::Mouse::getPosition(fenetre);
                            std::vector<sf::Vertex> tab;
                            sf::Vertex point;

                            point.position.x = souris.x;
                            point.position.y = souris.y;
                            tab.push_back(point);

                            point.position.x += stat.longueur;
                            tab.push_back(point);

                            point.position.y += stat.largeur;
                            tab.push_back(point);

                            point.position.x -= stat.longueur;
                            tab.push_back(point);

                            point.position.y -= stat.largeur;
                            tab.push_back(point);

                            Objet obj(tab);

                            sf::Vector2f v(1,1);
                            obj.set_vitesse(v);
                            obj.set_vitesse_angulaire(0.06);
                            obj.set_masse(1);
                            obj.setCoeff_elasticite(1);
                            tab_objets.push_back(obj);

                        }




                         }

                      }









            }




        fenetre.clear(sf::Color::Blue);
        for(int i=0; i<tab_objets.size(); i++) tab_objets[i].dessine(&fenetre);

        for(int i=0; i<tab_cercle.size(); i++) tab_cercle[i].dessine(&fenetre);


         //cout <<   tab_objets.size() << endl;


        if(clock.getElapsedTime().asMilliseconds() - elapsed.asMilliseconds() > 30 && !stat.pause){

            //Cercle
            for(int i=0; i<tab_cercle.size(); i++)
            {


            ///######################### GRAVITY #########################

            if (stat.gravite)
                tab_cercle[i].aplique_gravite();


           ///######################### GRAVITY #########################


                tab_cercle[i].deplacer(tab_cercle[i].get_vitesse());
                collision_cercle_bord(tab_cercle[i]);
                for(int j=0; j<tab_cercle.size(); j++)
                {
                    if(i!=j) collision_cercle_cercle(tab_cercle[i], tab_cercle[j],fenetre);
                }
                tab_cercle[i].dessine(&fenetre);
            }

            //Polygone
            for(int i=0; i<tab_objets.size(); i++){
                tab_objets[i].deplacer(tab_objets[i].get_vitesse());
                tab_objets[i].rotation();
                collision_polygone_bord(tab_objets[i], fenetre);

                //colision cercle polygone
                for(int j=0; j<tab_cercle.size(); j++)
                {
                    tab_objets[i].collision_cercle(tab_cercle[j],fenetre);
                }
            }



            elapsed = clock.getElapsedTime();

        }

        //limite temps a metre dans un truc a la bien




        fenetre.display();




    }

    for(int i = 0;i<tab_cercle.size();i++){
        free(&tab_cercle[i]);
    }
    exit(0);
    return app.exec();
}
