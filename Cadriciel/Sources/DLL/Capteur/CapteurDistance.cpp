#include <glm/glm.hpp>

#include "Utilitaire.h"

#include "CapteurDistance.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "NoeudPoteau.h"
#include "NoeudMur.h"

const double CapteurDistance::LARGEUR = 2.0;
const double CapteurDistance::MAX_HAUTEUR_TOTALE = 30.0;

CapteurDistance::CapteurDistance()
{
}


CapteurDistance::~CapteurDistance()
{
}

CapteurDistance::CapteurDistance(const glm::dvec3& positionCapteur, const double& angle)
{ 
    glm::dvec3 positionDanger = positionCapteur;
    const double HAUTEUR_DEFAUT = 15.0;
    positionDanger.x += HAUTEUR_DEFAUT / 2.0; 
    glm::dvec3 positionSecuritaire = positionDanger;
    positionSecuritaire.x += HAUTEUR_DEFAUT;

    utilitaire::calculerPositionApresRotation(positionCapteur, positionDanger, angle);
    zoneDanger_ = RectangleEnglobant(positionCapteur, angle, LARGEUR, HAUTEUR_DEFAUT);

}

// Méthodes permettant de mettre à jour l'état du capteur.
void CapteurDistance::verifierDetection(NoeudPoteau* poteau)
{
    CercleEnglobant cerclePoteau = poteau->obtenirCercleEnglobant();
    if (etat_ != DETECTION_ZONE_DANGER)
    {
        bool danger = zoneDanger_.calculerIntersection(cerclePoteau);
        if (!danger)
        {
            if (etat_ != DETECTION_ZONE_SECURITAIRE)
            {
                bool securitaire = zoneSecuritaire_.calculerIntersection(cerclePoteau);
                if (securitaire)
                {
                    etat_ = DETECTION_ZONE_SECURITAIRE;
                }
                else
                {
                    etat_ = AUCUNE_DETECTION;
                }
            }
        }
        else 
        {
            etat_ = DETECTION_ZONE_DANGER;
        }
    }
}

void verifierDetection(NoeudMur* noeud)
{

}
void CapteurDistance::mettreAJourPosition(const glm::dvec3& positionRobot, const double& angleRotationRobot)
{

}
