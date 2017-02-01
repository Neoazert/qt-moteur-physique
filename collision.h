#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Cercle.h"
#include "constantes.h"
#include "Info_collision.h"
#include "Objet.h"

void collision_cercle_bord(Cercle &crcl1);
info_collision collision_cercle_cercle(Cercle &crcl1, Cercle &crcl2,sf::RenderWindow &fenetre);
int collision_polygone_bord(Objet &obj, sf::RenderWindow &fenetre);
#endif // COLLISION_H_INCLUDED
