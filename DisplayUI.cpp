#include "DisplayUI.h"

using namespace  std;

DisplayUI::DisplayUI(buttonStatut* s,sf::RenderWindow *fenetre ,std::vector<Cercle> *tab_cercle,std::vector<Objet> *tab_objets,coord *last_mouse_click):QWidget()
{

    stat = s;

    stat->puissance_gravie = 1;
    stat->gravite = false;

    stat->pause = false;

    this->tab_cercle = tab_cercle;
    this->tab_objets = tab_objets;
    this->last_mouse_click = last_mouse_click;



    setWindowTitle("Options");
    setFixedHeight(400);
    setFixedWidth(300);
    move(50,50);
    fenetre_lay = new QVBoxLayout();
    aide = new QPushButton("Aide");
    QObject::connect(aide, SIGNAL(clicked()), this, SLOT(aide_sl()));
    fenetre_lay->addWidget(aide);
    tabs = new QTabWidget;
    general = new QWidget();
    general_lay = new QVBoxLayout();
    gravite = new QPushButton("Activer/Desactiver la gravite");
    general_lay->addWidget(gravite);
    QObject::connect(gravite, SIGNAL(clicked()), this, SLOT(desactiverGravite()));
    vitesse = new QSlider(Qt::Horizontal);
    vitesse->setMinimum(0);
    vitesse->setMaximum(1);
    vitesse->setValue(1);
    general_lay->addWidget(vitesse);
    QObject::connect(vitesse, SIGNAL(valueChanged(int)), this, SLOT(ralentir(int)));
    vitesse->setToolTip("Vitesse");
    general->setLayout(general_lay);
    cercle = new QWidget();
    cercle_lay = new QVBoxLayout();
    radius_lab = new QLabel();
    radius_lab->setText("Rayon");
    radius = new QLabel();
    radius->setNum(1);
    radius_slid = new QSlider(Qt::Horizontal);
    radius_slid->setMinimum(1);
    cercle_lay->addWidget(radius_lab);
    cercle_lay->addWidget(radius);
    cercle_lay->addWidget(radius_slid);
    QObject::connect(radius_slid, SIGNAL(valueChanged(int)), radius, SLOT(setNum(int)));
    weight_lab = new QLabel();
    weight_lab->setText("Poids");
    weight = new QLabel();
    weight->setNum(1);
    weight_slid = new QSlider(Qt::Horizontal);
    weight_slid->setMinimum(1);
    cercle_but = new QPushButton("Insérer");
    cercle_lay->addWidget(weight_lab);
    cercle_lay->addWidget(weight);
    cercle_lay->addWidget(weight_slid);
    QObject::connect(weight_slid, SIGNAL(valueChanged(int)), weight, SLOT(setNum(int)));
    elasticite_crcl_lab = new QLabel();
    elasticite_crcl_lab->setText("Elasticite");
    elasticite_crcl = new QDoubleSpinBox();
    cercle_lay->addWidget(elasticite_crcl_lab);
    cercle_lay->addWidget(elasticite_crcl);
    vitesse_crcl_lab = new QLabel("Vitesse (Dx,Dy)");
    vitesse_crcl= new QLineEdit();
    vitesse_crcl->setInputMask("(000,000)");
    cercle_lay->addWidget(vitesse_crcl_lab);
    cercle_lay->addWidget(vitesse_crcl);
    cercle_lay->addWidget(cercle_but);
    QObject::connect(cercle_but, &QPushButton::clicked, this, [this]{ajoutCercle((radius->text()).toInt(), (weight->text()).toInt(), elasticite_crcl->value(), vitesse_crcl->text());});
    cercle->setLayout(cercle_lay);
    tabs->addTab(cercle, "Cercle");
    poly = new QWidget();
    poly_lay = new QVBoxLayout();
    libre = new QPushButton("Polygones libres");
    carre = new QPushButton("Inserer un carre");
    carre->setToolTip("Cliquer sur l'emplacement de deux sommets opposes");
    rect = new QPushButton("Inserer un rectangle");
    elasticite_poly_lab = new QLabel();
    elasticite_poly_lab->setText("Elasticite");
    elasticite_poly = new QDoubleSpinBox();
    poly_lay->addWidget(elasticite_poly_lab);
    poly_lay->addWidget(elasticite_poly);
    vitesse_poly_lab = new QLabel("Vitesse (Dx,Dy)");
    vitesse_poly= new QLineEdit();
    vitesse_poly->setInputMask("(000,000)");
    poly_lay->addWidget(vitesse_poly_lab);
    poly_lay->addWidget(vitesse_poly);
    poly_lay->addWidget(libre);
    QObject::connect(libre, &QPushButton::clicked, this, [this]{ajoutPoly(elasticite_poly->value(), vitesse_poly->text());});
    poly_lay->addWidget(carre);
    QObject::connect(carre, &QPushButton::clicked, this, [this]{ajoutCarre(elasticite_poly->value(), vitesse_poly->text());});
    poly_lay->addWidget(rect);
    QObject::connect(rect, &QPushButton::clicked, this, [this]{ajoutRectangle(elasticite_poly->value(), vitesse_poly->text());});
    poly->setLayout(poly_lay);
    tabs->addTab(poly, "Polygone");
    fenetre_lay->addWidget(tabs);
    fenetre_lay->addWidget(general);
    setLayout(fenetre_lay);


}

void DisplayUI::ajoutCercle(int radius, int weight, double elasticite, QString vitesse)
 {


    stat->mode = 1;
    stat->masse = weight;
    stat->rayon = radius;
    stat->elasticite = elasticite;
    cout << "ela : " << stat->elasticite << endl;
    stat->vitesse_x = vitesse.mid(1, 3).split(",").at(0).toInt();
    stat->vitesse_y = vitesse.mid(1, 3).split(",").at(1).toInt();

 }
void DisplayUI::ajoutCarre(double elasticite, QString vitesse)
 {
     stat->mode = 3;
     stat->longueur = 100;
     stat->elasticite = elasticite;
     stat->vitesse_x = vitesse.mid(1, 3).split(",").at(0).toInt();
     stat->vitesse_y = vitesse.mid(1, 3).split(",").at(1).toInt();
 }
void DisplayUI::ajoutRectangle(double elasticite, QString vitesse)
 {
    stat->mode = 4;
    stat->longueur = 125;
    stat->largeur = 25;
    stat->elasticite = elasticite;
    stat->vitesse_x = vitesse.mid(1, 3).split(",").at(0).toInt();
    stat->vitesse_y = vitesse.mid(1, 3).split(",").at(1).toInt();
 }
void DisplayUI::ajoutPoly(double elasticite, QString vitesse)
 {
    stat->mode = 2;
    stat->elasticite = elasticite;
    stat->vitesse_x = vitesse.mid(1, 3).split(",").at(0).toInt();
    stat->vitesse_y = vitesse.mid(1, 3).split(",").at(1).toInt();
 }
void DisplayUI::desactiverGravite()
 {

    QMessageBox msgBox;
    msgBox.setWindowTitle("Hello");
    msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
    msgBox.exec();

    if(stat->gravite)
        stat->gravite =false;
    else
        stat->gravite =true;

    cout << " la grav :" << stat->gravite << endl;


 }
void DisplayUI::ralentir(int v)
 {
       if(v == 0){
           stat->pause = true;
       } else {
           stat->pause = false;
       }
 }

void DisplayUI::aide_sl(){
    QMessageBox first;
    first.setWindowTitle("Présentation générale");
    first.setText("<center>"
                  "<p>"
                  "Vous venez de démarrer un logiciel inconnu et vous êtes perdu ...<br> Pas de souci, je vais vous renseigner.<br>"
                  "Je suis un moteur physique réalisé en C++à l'aide des bibliothèques SFML et QT.<br>"
                  "Je suis l'oeuvre de Thomas BOURG, Lucas MAGNANA, Quincy MBAPE EYOKE et Thomas COUTELIER.<br>"
                  "Je suis le fruit d'un long et laborieux projet mené d'une main de maitre par Christophe JALOUX au sein de l'IUT Lyon 1 pendant l'année 2016-2017."
                  "</p>"
                  "</center>");
    first.exec();
    QMessageBox second;
    second.setWindowTitle("Aspect");
    second.setText("<center>"
                   "<p>"
                   "Je suis constitué de deux fenêtres séparées en trois parties.<br>"
                   "La fenêtre avec le fond bleu est l'espace de simulation :c'est ici que les différents objets créés intéragiront.<br>"
                   "La deuxième fenêtre, plus petite, est mon interface, mon panneau de contrôle si vous préférez.<br>"
                   "<br>"
                   "En partie basse, vous retrouvez mes fonctionnalités les plus générales:<br>"
                   "- activer ou désactiver la gravité,<br>"
                   "- mettre en pause et modifier la vitesse de la simulation."
                   "</p>"
                   "</center>");
    second.exec();
    tabs->setCurrentIndex(0);
    QMessageBox third;
    third.setWindowTitle("Cercle");
    third.setText("<center>"
                  "<p>"
                  "Sur mon premier onglet ... Vous trouverez tout ce qu'il vous faut pour insérez des cercles<br>"
                  "Vous choisissez la taille,<br>"
                  "le rayon,<br>"
                  "l'élasticité,<br>"
                  "et la vitesse initiale.<br>"
                  "Puis vous cliquez sur INSERER et un cercle apparaitra quand vous cliquerez dans la zone de dessin."
                  "</p>"
                  "</center>");
    third.exec();
    tabs->setCurrentIndex(1);
    QMessageBox fourth;
    fourth.setWindowTitle("Polygone");
    fourth.exec();
}
