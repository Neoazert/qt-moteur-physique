#ifndef INFO_COLLISION_H_INCLUDED
#define INFO_COLLISION_H_INCLUDED

#include "vecteur.h"
#include "coord.h"

enum bord{AUCUN,BHAUT,BBAS,BGAUCHE,BDROITE};

struct info_collision{
    bool existe;
    bord bCOl;
    vecteur pts_collision;
    coord pt_col;


};

#endif // INFO_COLLISION_H_INCLUDED
