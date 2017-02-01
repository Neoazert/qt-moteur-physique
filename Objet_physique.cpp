#include "Objet_physique.h"
#include <iostream>
#include "collision.h"

using namespace std;

void Objet_physique::setCoeff_elasticite(float value)
{
    coeff_elasticite = value;
}

Objet_physique::Objet_physique(){

}


void Objet_physique::set_vitesse(sf::Vector2f v){
    vitesse = v;
}

void Objet_physique::set_vitesse(float x,float y){
    sf::Vector2f v(x,y);
    vitesse = v;
}

void Objet_physique::deplacer(int x, int y){
    cout << "erreur class virtuel" << endl;
}

void Objet_physique::ajout_vitesse(double x,double y){
    vitesse.x+=x;
    vitesse.y+=y;

}

void Objet_physique::set_vitesse_angulaire(float nouvelle_vitesse){
    vitesse_angulaire = nouvelle_vitesse;
    //cout << vitesse_angulaire << endl;
}



