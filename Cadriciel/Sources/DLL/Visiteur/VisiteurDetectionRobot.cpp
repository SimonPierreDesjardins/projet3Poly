#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
/// Constructeur par défaut.
VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}


/// Constructeur par paramètres.
VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot, 
    SuiveurLigne* suiveurLigne, CapteurDistance capteurDistance[3])
        : robot_(robot), suiveurLigne_(suiveurLigne), capteursDistance_(capteurDistance)
{
}


/// Destructeur.
VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}


/// Visiter l'arbre de rendu.
void VisiteurDetectionRobot::visiter(ArbreRendu* noeud)
{
    noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


/// Visiter la table.
void VisiteurDetectionRobot::visiter(NoeudTable* noeud)
{
    int nEnfants = noeud->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
    {
        noeud->chercher(i)->accepterVisiteur(this);
    }
}


/// Visiter une ligne.
void VisiteurDetectionRobot::visiter(NoeudLigne* noeud)
{
    suiveurLigne_->verifierDetection(noeud);
}

/// Visiter un poteau.
void VisiteurDetectionRobot::visiter(NoeudPoteau* noeud)
{
}

/// Visiter un mur.
void VisiteurDetectionRobot::visiter(NoeudMur* noeud)
{
}