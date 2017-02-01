#ifndef DISPLAYUI_H
#define DISPLAYUI_H

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QTabWidget>
#include <QSlider>
#include <QLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Objet.h"
#include "Cercle.h"
#include "constantes.h"
#include "Info_collision.h"
#include "collision.h"

struct buttonStatut{
    int mode;
    bool gravite;
    float puissance_gravie;
    int rayon;
    int masse;
    float elasticite;
    int longueur;
    int largeur;
    int vitesse_x;
    int vitesse_y;
    bool pause;
};


class DisplayUI:public QWidget{

    Q_OBJECT

public:
    DisplayUI(buttonStatut *stat, sf::RenderWindow *fenetre, std::vector<Cercle> *tab_cercle, std::vector<Objet> *tab_objets, coord *last_mouse_click);

public slots:
    void ajoutCercle(int radius_int, int weight_int, double elasticite, QString vitesse);
    void ajoutCarre(double elasticite, QString vitesse);
    void ajoutRectangle(double elasticite, QString vitesse);
    void ajoutPoly(double elasticite, QString vitesse);
    void desactiverGravite();
    void ralentir(int v);
    void aide_sl();

private :
    QVBoxLayout *fenetre_lay, *general_lay, *cercle_lay, *poly_lay, *poly_grp_lay;
    QTabWidget *tabs;
    QWidget *general, *cercle, *poly;
    QSlider *radius_slid, *weight_slid, *vitesse;
    QLabel *radius_lab, *weight_lab, *elasticite_crcl_lab, *vitesse_crcl_lab, *weight, *radius, *elasticite_poly_lab, *vitesse_poly_lab;
    QPushButton *cercle_but, *libre, *carre, *rect, *gravite, *aide;
    QButtonGroup *poly_grp;
    QLineEdit *vitesse_crcl,*vitesse_poly;
    QDoubleSpinBox *elasticite_crcl, *elasticite_poly;

    std::vector<Cercle> *tab_cercle;
    std::vector<Objet> *tab_objets;
    coord *last_mouse_click;

    sf::RenderWindow *fenetre;

    buttonStatut *stat;
};



#endif // DISPLAYUI_H
