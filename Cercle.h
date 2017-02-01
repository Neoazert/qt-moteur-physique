#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Objet_physique.h"
#include "Info_collision.h"


class Cercle : public Objet_physique{

public:
    Cercle(sf::Vector2i souris, sf::RenderWindow *fenetre,float rayon, int vitx, int vity);

    void deplacer(int x, int y);
    void deplacer(sf::Vector2f vec);
    void dessine(sf::RenderWindow *fenetre);
    sf::Vector2f get_pos();
    void set_pos(int x,int y);
    int get_rayon();
    void aplique_gravite();//modif vecteru vitesse vers le bas

    void resou_col(info_collision inf1); // fait en sorte que les objet ne soit pas en colision avec le bord en modifiant le vecteur vitesse
    void resou_col_cercle_cercle(Cercle &c,info_collision inf,sf::RenderWindow &fenetre);
    void set_couleur(sf::Color col);
    void sauvegarde();


    sf::Vector2f vavant;
    sf::Vector2f posavant;


private:
    int m_rayon;
    sf::Vertex m_pos;
    sf::CircleShape m_cercle;


};

#endif // CERCLE_H_INCLUDED
