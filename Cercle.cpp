#include "Cercle.h"
#include "collision.h"
#include "Info_collision.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

Cercle::Cercle(sf::Vector2i souris, sf::RenderWindow *fenetre, float rayon, int vitx, int vity)
{

    m_cercle.setRadius(rayon);
    souris.x -=rayon;
    souris.y -=rayon;

    m_rayon = rayon;

    m_cercle.setPosition((sf::Vector2f)souris);

    cout << m_cercle.getRadius() << endl;
    //fenetre->draw(m_cercle);

    vitesse.x =vitx;
    vitesse.y =vity;

    vavant = vitesse;
    posavant = get_pos();

    coeff_elasticite = 0.6;

    masse =1;
    m_cercle.setFillColor(sf::Color::Black);

    m_cercle.setOutlineColor(sf::Color::Green);
    m_cercle.setOutlineThickness(-1);

}

void Cercle::deplacer(int x, int y)
{
    m_cercle.move(x,y);

}
void Cercle::deplacer(sf::Vector2f vec) {m_cercle.move(vec.x,vec.y);}


 void Cercle::set_pos(int x,int y){

     m_cercle.setPosition(trunc(x),trunc(y));

 };

 void Cercle::sauvegarde()
 {
     vavant = vitesse;
     posavant = get_pos();
 }





void Cercle::dessine(sf::RenderWindow *fenetre)
{
    fenetre->draw(m_cercle);
}

int Cercle::get_rayon() {return m_cercle.getRadius();}

sf::Vector2f Cercle::get_pos()
{
    return m_cercle.getPosition();
}

void Cercle::resou_col(info_collision inf1){

    if(inf1.bCOl == BBAS){


        double maxY = HAUTEUR_FENETRE - 2*get_rayon();
        double t = (maxY - get_pos().y + get_rayon() );
        double newX = get_pos().x + get_vitesse().x*t;
        set_pos(get_pos().x,maxY);
        vitesse.y = - vitesse.y*coeff_elasticite;

    }

    if(inf1.bCOl == BHAUT){


        double minY = 0;
        double t = (minY - get_pos().y + get_rayon() );
        double newX = get_pos().x + get_vitesse().x*t;
        set_pos(get_pos().x,minY);
        vitesse.y = - vitesse.y*coeff_elasticite;

    }


    if(inf1.bCOl == BGAUCHE){


        double minX = 0;
        double t = (minX + get_pos().x - get_rayon() );
        double newX = get_pos().y + get_vitesse().y*t;
        set_pos(minX,get_pos().y);
        vitesse.x = - vitesse.x*coeff_elasticite;

    }

    if(inf1.bCOl == BDROITE){


        double maxX = LARGEUR_FENETRE - 2*get_rayon();
        double t = (maxX - get_pos().y + get_rayon() );
        double newX = get_pos().x + get_vitesse().x*t;
        set_pos(maxX,get_pos().y);
        vitesse.x = - vitesse.x*coeff_elasticite;

    }

    /*

    if(inf1.bCOl == BBAS ||inf1.bCOl == BHAUT) vitesse.y = - vitesse.y*coeff_elasticite;

    if(inf1.bCOl == BGAUCHE ||inf1.bCOl == BDROITE) vitesse.x = - vitesse.x*coeff_elasticite;*/

}


void Cercle::set_couleur(sf::Color col) {m_cercle.setFillColor(col);}


void Cercle::aplique_gravite(){

        ajout_vitesse(0,1);

}
void Cercle::resou_col_cercle_cercle(Cercle &c,info_collision inf,sf::RenderWindow &fenetre){


    /// @source formules : http://www.lucidarme.me/?p=2582

    //angle alpha et beta

    double alpha1 = atan2( c.get_pos().y + c.get_rayon() - get_pos().y - get_rayon(), c.get_pos().x + c.get_rayon() - get_pos().x -get_rayon() );
    double alpha2= atan2( get_pos().y + get_rayon() - c.get_pos().y -c.get_rayon(), get_pos().x+ get_rayon()- c.get_pos().x -c.get_rayon());

    double beta1= atan2(vitesse.y,vitesse.x);
    double beta2 = atan2(c.get_vitesse().y,c.get_vitesse().x);

    //angle gama
    double gama1 = beta1 - alpha1 ;
    double gama2 = beta2 - alpha2 ;


    //calcule des normes de vecteur

    double norrme_vitesse1 = sqrt(vitesse.x*vitesse.x + vitesse.y*vitesse.y);
    double norrme_vitesse2 = sqrt(c.get_vitesse().x * c.get_vitesse().x + c.get_vitesse().y* c.get_vitesse().y) ;


    double norme_u12 = norrme_vitesse1 * cos(gama1);
    double norme_u11 = norrme_vitesse1 * sin(gama1);

    double norme_u21 = norrme_vitesse2 * cos(gama2);
    double norme_u22 = norrme_vitesse2 * sin(gama2);


    //norme vecteur vitesse après colision

    double norm_v1_ap_col = ( (masse - c.get_masse() )* norme_u12 - 2* c.get_masse() * norme_u21 ) / (masse + c.get_masse() );
    double norm_v2_ap_col = ( (masse - c.get_masse() )* norme_u21 + 2* masse* norme_u12  )         / (masse + c.get_masse() );

    //aplication elasicité
    norm_v1_ap_col*=coeff_elasticite;
    norm_v2_ap_col*=c.get_coeff_elasticite();

    if(get_pos().x+get_rayon() == c.get_pos().x+c.get_rayon() && get_pos().y+get_rayon() == c.get_pos().y+c.get_rayon())
    {

        deplacer(-vitesse.x/5, -vitesse.y/5);
        c.deplacer(-c.get_vitesse().x/5, -c.get_vitesse().y/5);
    }

    //calcule dus nouveaux vecteurs vitesse
    //1
    ///sauvegarde();
    vitesse.x = norme_u11*-sin(alpha1) + norm_v1_ap_col * cos(alpha1);
    vitesse.y = norme_u11* cos(alpha1) + norm_v1_ap_col * sin(alpha1);

    //2
    sf::Vector2f vitesse_ap_2;
    vitesse_ap_2.x = norme_u22 * -sin(alpha2) - norm_v2_ap_col*cos(alpha2);
    vitesse_ap_2.y = norme_u22 * cos(alpha2) - norm_v2_ap_col*sin(alpha2);
    ///c.sauvegarde();
    c.set_vitesse(vitesse_ap_2);



   /* /// ----------------
    // on separe les 2 cercle

        double v1X;
        double v1Y;
        double v2X;
        double v2Y;

        double vecteur_sur_axe_du_cercle_x = (get_pos().x + get_rayon() - inf.pt_col.x);
        double vecteur_sur_axe_du_cercle_y = (get_pos().y + get_rayon() - inf.pt_col.y);

        double norme_pt_col = sqrt(  vecteur_sur_axe_du_cercle_x * vecteur_sur_axe_du_cercle_x +
                                          vecteur_sur_axe_du_cercle_y* vecteur_sur_axe_du_cercle_y );


        double directionX = vecteur_sur_axe_du_cercle_x/ norme_pt_col;
        double directionY = vecteur_sur_axe_du_cercle_y / norme_pt_col;

        double distance_col_rayonX = directionX* get_rayon() ;
        double distance_col_rayonY = directionY* get_rayon() ;

        //vecteur 1
        v1X = distance_col_rayonX - vecteur_sur_axe_du_cercle_x ;
        v1Y = distance_col_rayonY - vecteur_sur_axe_du_cercle_y ;

        double vecteur_sur_axe_du_cercle_x2 = (c.get_pos().x + c.get_rayon() - inf.pt_col.x);
        double vecteur_sur_axe_du_cercle_y2 = (c.get_pos().y + c.get_rayon() - inf.pt_col.y);

        double norme_pt_col2 = sqrt(  vecteur_sur_axe_du_cercle_x2 * vecteur_sur_axe_du_cercle_x2 +
                                           vecteur_sur_axe_du_cercle_y2* vecteur_sur_axe_du_cercle_y2 );

        double directionX2 = vecteur_sur_axe_du_cercle_x2/ norme_pt_col2;
        double directionY2 = vecteur_sur_axe_du_cercle_y2 / norme_pt_col2;

        double distance_col_rayonX2 = directionX2* c.get_rayon() ;
        double distance_col_rayonY2 = directionY2* c.get_rayon() ;


        //vecteur 2
        v2X = distance_col_rayonX2 - vecteur_sur_axe_du_cercle_x2 ;
        v2Y = distance_col_rayonY2 - vecteur_sur_axe_du_cercle_y2 ;*/



        //resolution bonne norme des vecteur

        ///-----------------








        /*///DEBUG AFFICHAGE

        sf::Vertex azer1[2];
        sf::Vertex azer2[2];

        sf::Vertex l;
        sf::Vertex l2;
        l.color = sf::Color::Magenta;
        l2.color = sf::Color::Magenta;


        l.position.x = get_pos().x + get_rayon();
        l.position.y = get_pos().y + get_rayon();

        l2.position.x = c.get_pos().x + c.get_rayon();
        l2.position.y = c.get_pos().y + c.get_rayon();



        sf::Vertex m;
        sf::Vertex m2;
        m.color = sf::Color::Magenta;
        m2.color = sf::Color::Magenta;


        m.position.x =v1X + get_pos().x + get_rayon();
        m.position.y =v1Y + get_pos().y + get_rayon();

        m2.position.x = v2X +c.get_pos().x + c.get_rayon();;
        m2.position.y = v2Y +c.get_pos().y + c.get_rayon();;

        azer1[0] = l;
        azer1[1] = m;

        azer2[0] = l2;
        azer2[1] = m2;


        sf::Vertex ptcolision;
        ptcolision.position.x = inf.pt_col.x ;
        ptcolision.position.y = inf.pt_col.y ;

        ptcolision.color = sf::Color::Red;

        fenetre.draw(azer1, 2, sf::Lines);
        fenetre.draw(azer2, 2, sf::Lines);
        fenetre.draw(&ptcolision, 2, sf::Points);
        fenetre.display();

        system("PAUSE");
        ///Fin temp*/

        //if (get_pos().y + 2*get_rayon() != HAUTEUR_FENETRE) v1Y--; //SOUSTRACTION GRAVITE
        //if (c.get_pos().y + 2*c.get_rayon() != HAUTEUR_FENETRE) v2Y--; //SOUSTRACTION GRAVITE
        //deplacer(v1X,v1Y);
        //c.deplacer(v2X ,v2Y);








    /*///AFIICHAGE calc

     //on calcule le vecteur normal a la colision
    //Le vecteur (-y, x) est perpendiculaire à (x,y)
    vecteur vec_norm_col;

    vec_norm_col.p1 = inf.pts_collision.p1;

    double longeur = sqrt( (inf.pts_collision.p2.y - inf.pts_collision.p1.y )*(inf.pts_collision.p2.y - inf.pts_collision.p1.y )
                          + (inf.pts_collision.p2.x - inf.pts_collision.p1.x )*(inf.pts_collision.p2.x - inf.pts_collision.p1.x ));

    //cout << "longeur " << longeur<<  endl;

    vec_norm_col.p2.x = inf.pts_collision.p1.x - double(inf.pts_collision.p2.y - inf.pts_collision.p1.y )/longeur;
    vec_norm_col.p2.y = inf.pts_collision.p1.y + double(inf.pts_collision.p2.x - inf.pts_collision.p1.x )/longeur;


    int debugtempX = inf.pts_collision.p1.x - double(inf.pts_collision.p2.y - inf.pts_collision.p1.y );//
    int debugtempY = inf.pts_collision.p1.y + double(inf.pts_collision.p2.x - inf.pts_collision.p1.x );//



    //on calcule la reflexion du vecteur par raport a la perpendiculaire du vecteur orthorgonal a la colision
    //par raport au vecteur vitesse, on prend comme origine le point du cercle
    coord vec_refl;
    // formule sur : https://asalga.wordpress.com/2012/09/23/understanding-vector-reflection-visually/


    /// @TODO https://www.khanacademy.org/math/linear-algebra/matrix_transformations/lin_trans_examples/v/introduction-to-projections



    ///DEBUG AFFICHAGE

    sf::Vertex v1;
    sf::Vertex v2;

    sf::Vertex a;
    sf::Vertex b;

    a.position.x = inf.pts_collision.p1.x;
    a.position.y = inf.pts_collision.p1.y;

    b.position.x = inf.pts_collision.p2.x;
    b.position.y = inf.pts_collision.p2.y;

    a.color = sf::Color::Red;
    b.color = sf::Color::Red;



    v1.position.x = vec_norm_col.p1.x;
    v1.position.y = vec_norm_col.p1.y;

    v2.position.x = debugtempX;
    v2.position.y = debugtempY;



    v1.color = sf::Color::Green;
    v2.color = sf::Color::Green;


    sf::Vertex r1;
    sf::Vertex r2;


    r1.position.x = m_cercle.getPosition().x + m_rayon;
    r1.position.y = m_cercle.getPosition().y + m_rayon;

    r2.position.x = m_cercle.getPosition().x + m_rayon + vitesse.x*50;
    r2.position.y = m_cercle.getPosition().y + m_rayon + vitesse.y*50;

    r1.color = sf::Color::Blue;
    r2.color = sf::Color::Blue;



    sf::Vertex tab[2] {v1,v2};
    sf::Vertex tab2[2] {a,b};
    sf::Vertex tab3[2] {r1,r2};

    fenetre.draw(&tab[0], 2, sf::Lines);
    fenetre.draw(&tab2[0], 2, sf::Lines);
    fenetre.draw(&tab3[0], 2, sf::Lines);


    fenetre.display();

    system("PAUSE");*/

}


