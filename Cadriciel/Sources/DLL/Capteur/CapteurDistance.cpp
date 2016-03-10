#include "CapteurDistance.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "NoeudPoteau.h"
#include "NoeudMur.h"


CapteurDistance::CapteurDistance()
{
}


CapteurDistance::~CapteurDistance()
{
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
