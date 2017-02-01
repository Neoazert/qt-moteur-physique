#include "Objet.h"
#include "constantes.h"
#include "coord.h"
#include<math.h>
#include <windows.h>

using namespace std;

Objet::Objet()
{
    coeff_elasticite = 1;
    m_couleur = sf::Color::Green;

}

Objet::Objet(sf::Vector2i souris, sf::RenderWindow *fenetre)
{

    /*CE CONSTRUCTEUR PREND EN PARAMETRE LES COORD DE LA SOURIS (POUR POSER LE PREMIER POINT) PUIS
    A CHAQUE CLIC GAUCHE, UN POINT EST CREE AUX COORDONNEES DE LA SOURIS. LORSQUE L'UTILISATEUR
    FAIS UN CLICK DROIT, LE zPREMIER ET LE DERNIER POINTS SONT RELIES ET LA CONSTRUCTION SE TERMINE*/

    Objet();

    m_vertices.push_back(sf::Vertex((sf::Vector2f)souris, m_couleur));

    m_nb_points = m_vertices.size();

    construire(souris, fenetre);


    calcul_cg();
}


Objet::Objet(std::vector<sf::Vertex> tab)
{
    Objet();

    for(int i=0; i<tab.size(); i++){
        tab[i].color = m_couleur;
        m_vertices.push_back(tab[i]);
    }

    m_nb_points = m_vertices.size();

    calcul_cg();
}



void Objet::construire(sf::Vector2i souris, sf::RenderWindow *fenetre)
{

    bool continuer = true;

    sf::Vertex *pts_commun;

    int i =0;

    sf::Event evenement;

    sf::Vertex temoin;

    sf::Vector2f vecteur;

    while(continuer)
    {
        while (fenetre->pollEvent(evenement))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            switch(evenement.type)
            {
                case sf::Event::Closed :

                    fenetre->close();
                    break;

                case sf::Event::MouseButtonPressed :

                    if (evenement.mouseButton.button == sf::Mouse::Left) // click gauche -> ajout d'un point
                    {
                        vecteur = (sf::Vector2f)(sf::Mouse::getPosition(*fenetre));
                        if (m_nb_points > 2)
                        {
                            while(pts_commun == NULL && i < m_nb_points-2)
                            {
                                pts_commun = se_croise(m_vertices[i], m_vertices[i+1], m_vertices[m_nb_points-1], vecteur);
                                i ++;
                            }
                        }
                        if (pts_commun == NULL) m_vertices.push_back(sf::Vertex(vecteur, m_couleur));
                    }

                    if (evenement.mouseButton.button == sf::Mouse::Right) // click droite -> finalisation de l'objet
                    {
                        vecteur.x = m_vertices[0].position.x;
                        vecteur.y = m_vertices[0].position.y;

                        if (m_nb_points > 2)
                        {
                            i=1;
                            while(pts_commun == NULL && i < m_nb_points-2)
                            {
                                pts_commun = se_croise(m_vertices[i], m_vertices[i+1], m_vertices[m_nb_points-1], vecteur);
                                i ++;
                            }
                        }

                        if(pts_commun == NULL)
                        {
                            m_vertices.push_back(m_vertices[0]);
                            fenetre->draw(&m_vertices[0], m_vertices.size(), sf::LinesStrip);
                            m_termine = true;
                        }

                        else m_termine = false;

                        continuer = false;
                    }
                    break;


            }
        }
         m_nb_points = m_vertices.size();
         dessine(fenetre);
         fenetre->display();
         pts_commun = NULL;
         i=0;
    }
}





void Objet::dessine(sf::RenderWindow *fenetre)
{
    fenetre->draw(&m_vertices[0], m_vertices.size(), sf::LinesStrip);
    if (m_vertices.size() == 1)fenetre->draw(&m_vertices[0], 1, sf::Points);
    fenetre->draw(&m_centre, 1, sf::Points);

}




void Objet::calcul_cg()
{
    /// CALCUL DU CENTRE DE GRAVITE D'UN POLYGONE NON CROISES GRACE A CE COURS : http://math.15873.pagesperso-orange.fr/page9.htm ///

    int aire=0, centre_x=0, centre_y=0;


    if(m_nb_points > 3)
    {
        for(int i=0;i<m_nb_points-1;i++)
        {
            aire += m_vertices[i].position.x*m_vertices[i+1].position.y - m_vertices[i+1].position.x*m_vertices[i].position.y;
            centre_x += (m_vertices[i].position.x*m_vertices[i+1].position.y - m_vertices[i+1].position.x*m_vertices[i].position.y)*(m_vertices[i].position.x + m_vertices[i+1].position.x);
            centre_y += (m_vertices[i].position.x*m_vertices[i+1].position.y - m_vertices[i+1].position.x*m_vertices[i].position.y)*(m_vertices[i].position.y + m_vertices[i+1].position.y);
        }

        aire = aire/2;
        m_centre.position.x = centre_x/(6*aire);
        m_centre.position.y = centre_y/(6*aire);
    }

    else if(m_nb_points == 3)
    {
        m_centre.position.x = (m_vertices[0].position.x + m_vertices[1].position.x)/2;
        m_centre.position.y = (m_vertices[0].position.y + m_vertices[1].position.y)/2;
    }

    else m_centre.position = m_vertices[0].position;

    m_centre.color = m_couleur;

}




sf::Vertex * Objet::se_croise(sf::Vertex p1, sf::Vertex p2, sf::Vertex p3, sf::Vertex p4)
{

    /*CETTE FONCTION RETOURNE UN POINTEUR SUR sf::Vertex CONTENANT LES COORDONNEES DU POINT
    D'INTERSECTION DES SEGMENTS [p1p2] ET [p3p4] OU NULL SI LES SEGMENTS NE SE COUPENT PAS */

    sf::Vertex *ret = NULL;

    float coeffD1 = (p2.position.y - p1.position.y) / (p2.position.x - p1.position.x); //coefficient directeur de la droite passant par p1 et p2
    float coeffD2 = (p4.position.y - p3.position.y) / (p4.position.x - p3.position.x); //coefficient directeur de la droite passant par p3 et p4

    float ordorigineD1 = p1.position.y - (coeffD1 * p1.position.x); //ordonnee a l'origine de la droite passant par p1 et p2
    float ordorigineD2 = p3.position.y - (coeffD2 * p3.position.x); //ordonnee a l'origine de la droite passant par p3 et p4

    if (coeffD1 != coeffD2) //si les droites ne sont pas paralleles
    {
        float xcommun=(ordorigineD2-ordorigineD1)/(coeffD1-coeffD2); //calcul de l'abscisse du point d'intersection des 2 droites
        if (xcommun >= p1.position.x && xcommun <= p2.position.x || xcommun <= p1.position.x && xcommun >= p2.position.x) // si l'abscisse en commun est compris entre p1 et p2
        {
            if (xcommun >= p3.position.x && xcommun <= p4.position.x || xcommun <= p3.position.x && xcommun >= p4.position.x) // et entre p3 et p4
            {
                sf::Vector2f vectem(xcommun, coeffD1*xcommun+ordorigineD1); //creation d'un vecteur contenant le point d'intersection des 2 segments
                sf::Vertex temoin(vectem);
                ret = &temoin;
            }
        }
    }

    return ret;
}


bool Objet::get_termine() {return m_termine;}


vector<sf::Vertex> &Objet::get_vertices() {return m_vertices;}



void Objet::collision_cercle(Cercle &crcl,sf::RenderWindow &fenetre)
{


    int rayon = crcl.get_rayon();
    sf::Vector2f pos = crcl.get_pos();
    sf::Vector2f centre;

    centre.x = pos.x + rayon;
    centre.y = pos.y + rayon;

    for (int i=0; i<m_vertices.size()-1; i++)
    {
        //cout << i << "   " << m_vertices.size() <<endl;
        float coeff = (m_vertices[i+1].position.y - m_vertices[i].position.y) / (m_vertices[i+1].position.x - m_vertices[i].position.x);
        float ordorigine = m_vertices[i].position.y - (coeff * m_vertices[i].position.x);

        float A = 1 + coeff*coeff;
        float B = 2 * (coeff*(ordorigine-centre.y)-centre.x);
        float C = centre.x * centre.x + (ordorigine-centre.y)*(ordorigine-centre.y) - rayon * rayon;
        float delta = B * B - 4 * A * C;

        if (delta > 0)
        {
            float x1 = (-B - (float)sqrt(delta)) / (2 * A);
            float y1 = coeff * x1 + ordorigine;


            float x2 = (-B + sqrt(delta)) / (2 * A);
            float y2 = coeff * x2 + ordorigine;

            if (x1 >= m_vertices[i].position.x && x1 <= m_vertices[i+1].position.x || x1 <=  m_vertices[i].position.x && x1 >=  m_vertices[i+1].position.x
                || x2 >= m_vertices[i].position.x && x2 <= m_vertices[i+1].position.x || x2 <=  m_vertices[i].position.x && x2 >=  m_vertices[i+1].position.x){

                sf::Vector2f vitesse_relative = crcl.get_vitesse() - vitesse;

                //si deja en cours de séparation on ne fait rien
                if(vitesse_relative.x<0 && vitesse_relative.y <0) return;

                float x = (x1+x2)/2;
                float y = (y1+y2)/2;

                sf::Vertex collision;
                collision.position.x = x;
                collision.position.y = y;


                //RESOLUTION ****************************************************************************************************************
                //***************************************************************************************************************************


                float dx = m_vertices[i].position.x - m_vertices[i+1].position.x;
                float dy = m_vertices[i].position.y - m_vertices[i+1].position.y;




                float longeur_vect = sqrt( pow(x + dy,2) +pow(y - dx,2) );

                float normal_x ;
                float normal_y ;


                //TENTATIVE DEBUG INVERSION NORMAL

                float x1 = x;
                float x2 = -dy + x;

                float y1 = y;
                float y2 = dx + y;


                // y = alpha*x + beta
                float alpha = (y2-y1)/(x2-x1);
                float beta = y1 - alpha*x1;

                float px = crcl.get_pos().x + crcl.get_rayon();
                float py = crcl.get_pos().y + crcl.get_rayon();


                float equation = alpha*px + beta - py;

                cout << "eq " << equation << endl ;

                normal_x = dy /longeur_vect;
                normal_y = -dx/longeur_vect;

                float dot_prod = crcl.get_vitesse().x * normal_x + crcl.get_vitesse().y * normal_y;

                float cercle_projection_x = crcl.get_vitesse().x - 2*dot_prod*normal_x ;
                float cercle_projection_y= crcl.get_vitesse().y - 2*dot_prod*normal_y;

                if(equation <0.01 && equation>-0.01){
                    //cout << "SISI TOI MEME TU RPZ LE TIECAR" << endl;

                    //cercle_projection_y = -cercle_projection_y;


                }
                else{
                    //cout << "GO MAC DO ?" << endl;

                    //cercle_projection_x = -cercle_projection_x;

                }

                //TENTATIVE DEBUG INVERSION NORMAL



                /*
                 normal_x = -dy /longeur_vect;
                 normal_y = dx/longeur_vect;*/





                //set_vitesse
                //set_vitesse(cercle_projection_x,cercle_projection_y);

                sf::Vertex normal;
                normal.position.x = normal_x;
                normal.position.y = normal_y;
                resou_col_polygone_cercle(collision, crcl, normal);

                dot_prod = get_vitesse().x * normal_x + get_vitesse().y * normal_y;

                float pol_projection_x = get_vitesse().x - 2*dot_prod*normal_x ;
                float pol_projection_y= get_vitesse().y - 2*dot_prod*normal_y;


                crcl.set_vitesse(-pol_projection_x,-pol_projection_y);





                ////DEBUG ////////////////////////////////////////////////////////////
                ///ANGLE COLISION

                sf::Vertex azer1[2];

                sf::Vertex a;
                sf::Vertex b;
                a.color = sf::Color::Blue;
                b.color = sf::Color::Cyan;

/*
                a.position.x = -dy + x;
                a.position.y = dx + y;

                b.position.x = dy +x;
                b.position.y = -dx +y;
*/

                a.position.x = x;
                a.position.y = y;

                b.position.x = normal_x*300 + x;
                b.position.y = normal_y*300 + y;



                azer1[0] =a;
                azer1[1] =b;

                sf::Vertex azer2[2];

                sf::Vertex a2;
                sf::Vertex b2;
                a2.color = sf::Color::Red;
                b2.color = sf::Color::Red;


                a2.position.x = crcl.get_pos().x + crcl.get_rayon();
                a2.position.y = crcl.get_pos().y + crcl.get_rayon();

                b2.position.x = crcl.get_vitesse().x *5 + crcl.get_pos().x +crcl.get_rayon();
                b2.position.y = crcl.get_vitesse().y *5 + crcl.get_pos().y +crcl.get_rayon();

                azer2[0] =a2;
                azer2[1] =b2;




                fenetre.draw(&azer1[0], 2, sf::LinesStrip);
                fenetre.draw(&azer2[0], 2, sf::LinesStrip);


                fenetre.display();


                //Sleep(1000);

                ////DEBUG ////////////////////////////////////////////////////////////



                //float normal_x =



                //float vit_x = crcl.get_vitesse().x - 2*(crcl.get_vitesse().x * )





                //RESOLUTION ****************************************************************************************************************
                //***************************************************************************************************************************

            }
        }
        else if (delta == 0)
        {
            float x = -B / (2 * A);
            float y = coeff * x + ordorigine;


        }
    }


    //test resolution  :




 }


void Objet::resou_col_polygone_bord(int indice_point, sf::Vertex normal, sf::RenderWindow &fenetre)
{
   /* float rayon = calcul_rayon(m_vertices[indice_point]);
    float vit = sqrt(pow(vitesse.x,2) + pow(vitesse.y,2));
    float moment_inertie = masse*pow(vit,2);

    sf::Vertex torquevec;
    torque.position.x = -m_centre.position.y*vitesse_angulaire;
    torque.position.y = m_centre.position.x*vitesse_angulaire;

    vitesse_angulaire += torque*(1.0f/moment_inertie);*/



    sf::Vertex rap;
    rap.position.x = m_vertices[indice_point].position.x -m_centre.position.x;
    rap.position.y = m_vertices[indice_point].position.y -m_centre.position.y;

    float vp_x = get_vitesse().x + (-vitesse_angulaire*rap.position.y);
    float vp_y = get_vitesse().y + (vitesse_angulaire*rap.position.x);




    // normal impulse
    float inertia = get_masse()*pow(calcul_rayon(m_vertices[indice_point]),2);

    float j_nume = -(coeff_elasticite + 1)*(vp_x*normal.position.x+vp_y*normal.position.y);
    float j_deno =  1/get_masse()+(pow(rap.position.x*normal.position.y -rap.position.y*normal.position.x, 2)/inertia);

    float j = j_nume / j_deno;




    sf::Vertex jn;
    float jn_x = j * normal.position.x;
    float jn_y = j * normal.position.y;


   // cout << jn_y/inertia << endl;
    set_vitesse(get_vitesse().x+jn_x,get_vitesse().y+jn_y);

    float nouvelle_angulaire = (rap.position.x*jn_y - rap.position.y*jn_x);
    set_vitesse_angulaire(get_vitesse_angulaire()+nouvelle_angulaire/inertia);

    //system("pause");



    sf::Vertex azer1[2];
    sf::Vertex az, er;

    az.color = sf::Color::Blue;
    er.color = sf::Color::Cyan;

    az.position.x = m_vertices[indice_point].position.x;
    az.position.y = m_vertices[indice_point].position.y;

    er.position.x = m_vertices[indice_point].position.x+normal.position.x*300;
    er.position.y = m_vertices[indice_point].position.y+normal.position.y*300;

    azer1[0] = az;
    azer1[1] = er;



     fenetre.draw(&azer1[0], 2, sf::LinesStrip);

     fenetre.display();









}


void Objet::resou_col_polygone_cercle(sf::Vertex point, Cercle a, sf::Vertex normal)
{
   /* float rayon = calcul_rayon(point);
    float vit = sqrt(pow(vitesse.x,2) + pow(vitesse.y,2));
    float moment_inertie = 1*pow(vit,2);
    float torque = rayon*vitesse_angulaire ;

    vitesse_angulaire += torque*(1.0f/moment_inertie);
    //vitesse_angulaire = -vitesse_angulaire;
    cout << torque*(1.0f/moment_inertie) << endl;

    sf::Vertex torquevec;
    torque.position.x = -m_centre.position.y*vitesse_angulaire;
    torque.position.y = m_centre.position.x*vitesse_angulaire;




    //
    a.vel = a.vel + jn / a.mass;
    a.r_vel = a.r_vel + cross(r,jn) / a.i;

    var vp = a.vel + cross(a.r_vel, a.r) - b.vel - cross(b.r_vel, b.r);
    var vp_p = dot(vp,n); // negative val = moving towards each other

    if (vp_p >= 0) { // do they move apart?
        return false;
    }

    // normal impulse
    var j = - e * vp_p / (
                1/a.mass + cross(a.r,n)^2 / a.i +
                1/b.mass + cross(b.r,n)^2 / b.i
            );
    var jn = j * n;
    //
    a.vel = a.vel + jp / a.mass;
    a.r_vel = a.r_vel + cross(a.r,jn) / a.i;
    b.vel = b.vel - jp / b.mass;
    b.r_vel = b.r_vel - cross(b.r,jn) / b.i;*/



    sf::Vertex rap;
    rap.position.x = point.position.x -m_centre.position.x;
    rap.position.y = point.position.y -m_centre.position.y;

    sf::Vertex rbp;
    rbp.position.x = point.position.x -a.get_pos().x+a.get_rayon();
    rbp.position.y = point.position.y -a.get_pos().y+a.get_rayon();

    float vp_x = get_vitesse().x + (-vitesse_angulaire*rap.position.y);
    float vp_y = get_vitesse().y + (vitesse_angulaire*rap.position.x);


    float vab1_x = vp_x-a.get_vitesse().x;
    float vab1_y = vp_y-a.get_vitesse().y;

    // normal impulse
    float inertia = get_masse()*pow(calcul_rayon(point),2);
    float inertib = a.get_masse()*pow(a.get_rayon(),2);

    float j_nume = -(coeff_elasticite + 1)*(vab1_x*normal.position.x+vab1_y*normal.position.y);
    float j_deno =  1/get_masse()+1/a.get_masse() +
            (pow(rap.position.x*normal.position.y -rap.position.y*normal.position.x, 2)/inertia) + (pow(rbp.position.x*normal.position.y -rbp.position.y*normal.position.x, 2)/inertib);

    float j = j_nume / j_deno;




    sf::Vertex jn;
    float jn_x = j * normal.position.x;
    float jn_y = j * normal.position.y;



    set_vitesse(get_vitesse().x+jn_x,get_vitesse().y+jn_y);

    float nouvelle_angulaire = (rap.position.x*jn_y - rap.position.y*jn_x);
    set_vitesse_angulaire(get_vitesse_angulaire()+nouvelle_angulaire/inertia);

    cout << nouvelle_angulaire << endl;



}









 //mouvement
void Objet::deplacer(sf::Vector2f vec){

    for(int i =0;i<m_nb_points;i++){

        m_vertices[i].position.x = m_vertices[i].position.x + vec.x;
        m_vertices[i].position.y = m_vertices[i].position.y + vec.y;
    }

    m_centre.position.x = m_centre.position.x +vec.x;
    m_centre.position.y = m_centre.position.y +vec.y;


}

void Objet::rotation(){

    //angle = angle * (M_PI / 180);

    float x;
    float y;

    float angle = vitesse_angulaire;

    for(int i =0;i<m_nb_points;i++){

        x  = cos(angle)*(m_vertices[i].position.x- m_centre.position.x) - sin(angle)*(m_vertices[i].position.y-m_centre.position.y) +  m_centre.position.x ;
        y  = sin(angle)*(m_vertices[i].position.x- m_centre.position.x) + cos(angle)*(m_vertices[i].position.y-m_centre.position.y) +  m_centre.position.y ;


        m_vertices[i].position.x =x;
        m_vertices[i].position.y =y;






    }

}



float Objet::calcul_rayon(sf::Vertex point){

    int rayon = sqrt(pow(point.position.x - m_centre.position.x,2) + pow(point.position.y - m_centre.position.y,2));
    return rayon;
}


