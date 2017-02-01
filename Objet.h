#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Info_collision.h"
#include "Cercle.h"
#include "Objet_physique.h"

#include <iostream>
class Objet : public Objet_physique{
public:
    Objet(std::vector<sf::Vertex> tab);
    Objet(sf::Vector2i souris, sf::RenderWindow *fenetre);
    Objet();
    void construire(sf::Vector2i souris, sf::RenderWindow *fenetre);
    void dessine(sf::RenderWindow *fenetre);
    sf::Vertex * se_croise(sf::Vertex p1, sf::Vertex p2, sf::Vertex p3, sf::Vertex p4);
    bool get_termine();
    std::vector<sf::Vertex> &get_vertices();
    void collision_cercle(Cercle &crcl,sf::RenderWindow &fenetre);

    //mouvement du polygone
    void deplacer(sf::Vector2f vec);
    void rotation();

    void resou_col_polygone_bord(int indice_point, sf::Vertex normal, sf::RenderWindow &fenetre);

    void resou_col_polygone_cercle(sf::Vertex point, Cercle a, sf::Vertex normal);





private:
    std::vector<sf::Vertex> m_vertices;
    sf::Vertex m_centre;
    int m_nb_points;
    bool est_fixe, m_termine;
    sf::Color m_couleur;


    void calcul_cg();
    float calcul_rayon(sf::Vertex point);


};

#endif // OBJET_H_INCLUDED
