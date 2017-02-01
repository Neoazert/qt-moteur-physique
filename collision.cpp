#include "collision.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


int collision_polygone_bord(Objet &obj, sf::RenderWindow &fenetre){

    std::vector<sf::Vertex> vertex = obj.get_vertices();

    int haut = 0;
    int bas = 0;
    int gauche = 0;
    int droite = 0;

    int point_coll = -1;

    for(int i=0; i<vertex.size(); i++){
        if(vertex[i].position.y > vertex[bas].position.y)
            bas = i;
        if(vertex[i].position.y < vertex[haut].position.y)
            haut = i;
        if(vertex[i].position.x > vertex[droite].position.x)
            droite = i;
        if(vertex[i].position.x < vertex[gauche].position.x)
            gauche = i;
    }

    sf::Vertex normal;

        //bas
        if(vertex[bas].position.y>HAUTEUR_FENETRE){

            if(obj.get_vitesse().y>0){ //pour ne pas corige la trajectoir si elle est deja en cour de correction
                //obj.set_vitesse( obj.get_vitesse().x, -obj.get_vitesse().y );
            point_coll = bas;

            normal.position.x = 0;
            normal.position.y = -1;
            }
        }

        //haut
        if(vertex[haut].position.y<0){
            if(obj.get_vitesse().y<0){ //pour ne pas corige la trajectoir si elle est deja en cour de correction
                //obj.set_vitesse( obj.get_vitesse().x, -obj.get_vitesse().y );
            point_coll = haut;

            normal.position.x = 0;
            normal.position.y = 1;
            }
        }


        //gauche
        if(vertex[gauche].position.x<0){

             if(obj.get_vitesse().x<0){ //pour ne pas corige la trajectoir si elle est deja en cour de correction
                //obj.set_vitesse( -obj.get_vitesse().x, obj.get_vitesse().y );

             point_coll = gauche;
             normal.position.x = 1;
             normal.position.y = 0;
             }
        }

        //droite
        if(vertex[droite].position.x>LARGEUR_FENETRE){
            if(obj.get_vitesse().x>0){ //pour ne pas corige la trajectoir si elle est deja en cour de correction
                //obj.set_vitesse( -obj.get_vitesse().x, obj.get_vitesse().y );
                point_coll = droite;

                normal.position.x = -1;
                normal.position.y = 0;
            }


        }

       if(point_coll != -1) obj.resou_col_polygone_bord(point_coll, normal, fenetre);



        return point_coll;



}

void collision_cercle_bord(Cercle &crcl1)
{
    int rayon = crcl1.get_rayon();
    sf::Vector2f pos = crcl1.get_pos();
    info_collision ret;
    ret.existe = false;

    ret.bCOl = AUCUN;

    if(pos.x< 0)
    {
        ret.existe = true;

        ret.pts_collision.p1.x = pos.x;
        ret.pts_collision.p1.y = pos.y;

        ret.pts_collision.p2.x = 0;
        ret.pts_collision.p2.y = pos.y;

        ret.bCOl = BGAUCHE;

        //crcl1.set_pos(0,crcl1.get_pos().y);

        crcl1.resou_col(ret);



    }

    if (pos.y < 0)
    {
        ret.existe = true;

        ret.pts_collision.p1.x = pos.x;
        ret.pts_collision.p1.y = pos.y;

        ret.pts_collision.p2.x = pos.x;
        ret.pts_collision.p2.y = 0;

        ret.bCOl = BHAUT;

        //crcl1.set_pos(crcl1.get_pos().x,0);

        crcl1.resou_col(ret);
    }

    if (pos.x + 2*rayon > LARGEUR_FENETRE)
    {
        ret.existe = true;

        ret.pts_collision.p1.x = pos.x;
        ret.pts_collision.p1.y = pos.y;

        ret.pts_collision.p2.x = LARGEUR_FENETRE;
        ret.pts_collision.p2.y = pos.y;


        ret.bCOl = BDROITE;

        //crcl1.set_pos(LARGEUR_FENETRE- 2*rayon,crcl1.get_pos().y);

        crcl1.resou_col(ret);

    }

    if (pos.y + 2*rayon > HAUTEUR_FENETRE)
    {
        ret.existe = true;

        ret.pts_collision.p1.x = pos.x;
        ret.pts_collision.p1.y = pos.y;

        ret.pts_collision.p2.x = pos.x;
        ret.pts_collision.p2.y = HAUTEUR_FENETRE;

        ret.bCOl = BBAS;

        //crcl1.set_pos(crcl1.get_pos().x,HAUTEUR_FENETRE - 2*rayon);

        crcl1.resou_col(ret);


    }




}



info_collision collision_cercle_cercle(Cercle &crcl1, Cercle &crcl2,sf::RenderWindow &fenetre)
{
    info_collision ret;
    ret.existe = false;

    int rayon1 = crcl1.get_rayon();
    sf::Vector2f pos1 = crcl1.get_pos();

    int rayon2 = crcl2.get_rayon();
    sf::Vector2f pos2 = crcl2.get_pos();

    sf::Vector2f centre1;
    sf::Vector2f centre2;

    centre1.x = pos1.x + rayon1;
    centre1.y = pos1.y + rayon1;

    centre2.x = pos2.x + rayon2;
    centre2.y = pos2.y + rayon2;

    sf::Vector2f vitesse1 = crcl1.get_vitesse();
    sf::Vector2f vitesse2 = crcl2.get_vitesse();


    int longueur_centres = sqrt((centre2.x-centre1.x)*(centre2.x-centre1.x) + (centre2.y-centre1.y)*(centre2.y-centre1.y));




    if (longueur_centres < rayon1 + rayon2)
    {





    sf::Vector2f vitesse_relative = crcl2.get_vitesse() - crcl1.get_vitesse();

    sf::Vector2f normal;
    normal.x = centre2.x -centre1.x;
    normal.y = centre2.y -centre1.y;

    double n_normal = sqrt(normal.x*normal.x + normal.y*normal.y );

    normal.x /= n_normal;
    normal.y /= n_normal;

    double vitesse_long_normal = normal.x*vitesse_relative.x + normal.y*vitesse_relative.y;

    //cout << "vitesse_long_normal" << vitesse_long_normal << endl;


    const float percent = 0.8; // usually 20% to 80%
    const float slop = 0.1; // usually 0.01 to 0.1

    double penetration =  rayon1+rayon2 - longueur_centres;

    //cout << "penetration" << penetration << endl;

    sf::Vector2f correction;
    correction.x = max( penetration - slop, 0.0) / (1/crcl1.get_masse() + 1/crcl2.get_masse()) * percent *normal.x;
    correction.y = max( penetration - slop, 0.0 ) / (1/crcl1.get_masse() + 1/crcl2.get_masse()) * percent *normal.y;



    if(penetration - slop<0)
        cout << penetration - slop << endl;




    if(vitesse_long_normal < 0)
        crcl1.resou_col_cercle_cercle(crcl2, ret, fenetre);

/*
    crcl1.deplacer( - 1/crcl1.get_masse() * correction.x, - 1/crcl1.get_masse() * correction.y);
    crcl2.deplacer(  1/crcl2.get_masse() * correction.x,    1/crcl2.get_masse() * correction.y);

*/






    }

    return ret;
}





