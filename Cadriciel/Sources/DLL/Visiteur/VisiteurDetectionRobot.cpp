#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

#include "CapteurDistance.h"
#include "SuiveurLigne.h"


VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}


VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot, 
    SuiveurLigne* suiveurLigne, CapteurDistance capteurDistance[3])
        : robot_(robot), suiveurLigne_(suiveurLigne), capteursDistance_(capteurDistance)
{
}


VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}


void VisiteurDetectionRobot::visiter(ArbreRendu* noeud)
{
    noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


void VisiteurDetectionRobot::visiter(NoeudTable* noeud)
{
    int nEnfants = noeud->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
    {
        noeud->chercher(i)->accepterVisiteur(this);
    }
}


void VisiteurDetectionRobot::visiter(NoeudLigne* noeud)
{
    suiveurLigne_->verifierDetection(noeud);
}


void VisiteurDetectionRobot::visiter(NoeudPoteau* noeud)
{
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_[i].verifierDetection(noeud);
    }
}


void VisiteurDetectionRobot::visiter(NoeudMur* noeud)
{
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_[i].verifierDetection(noeud);
    }
}