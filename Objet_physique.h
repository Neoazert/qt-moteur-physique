#ifndef OBJET_PHYSIQUE_H_INCLUDED
#define OBJET_PHYSIQUE_H_INCLUDED

#include "coord.h"
#include "vecteur.h"
#include "Objet_physique.h"
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


/*
Objet mère de tout les autres objets qui permettrons la gestion de la physique
*/

class Objet_physique {

protected:

    //coord pos;
    sf::Vector2f vitesse;
    float vitesse_angulaire;
    float coeff_elasticite;
    double masse;

public :

    Objet_physique();

    inline float get_coeff_elasticite(){return coeff_elasticite;}

    void deplacer(int x, int y);

    void set_vitesse(sf::Vector2f v);
    inline sf::Vector2f get_vitesse(){return vitesse;}
    inline float get_vitesse_angulaire(){return vitesse_angulaire;}
    inline int get_masse(){return masse;}
    inline void set_masse(int m){masse = m;}

    void ajout_vitesse(double x,double y);
    void set_vitesse(float x,float y);

    void set_vitesse_angulaire(float nouvelle_vitesse);


    void setCoeff_elasticite(float value);
};


#endif // OBJET_PHYSIQUE_H_INCLUDED
