#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

#include "FacadeModele.h"
#include "CapteurDistance.h"
#include "SuiveurLigne.h"


VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}


VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot)
    : robot_(robot)
{
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();
}


VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}


void VisiteurDetectionRobot::visiter(ArbreRendu* arbre)
{
    arbre->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


void VisiteurDetectionRobot::visiter(NoeudTable* table)
{
    robot_->verifierCollision(table);
    int nEnfants = table->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
    {
        table->chercher(i)->accepterVisiteur(this);
    }
}


void VisiteurDetectionRobot::visiter(NoeudLigne* ligne)
{
    suiveurLigne_->verifierDetection(ligne);
}


void VisiteurDetectionRobot::visiter(NoeudPoteau* poteau)
{
    robot_->verifierCollision(poteau);
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(poteau);
    }
}


void VisiteurDetectionRobot::visiter(NoeudMur* mur)
{
    robot_->verifierCollision(mur);
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(mur);
    }
}