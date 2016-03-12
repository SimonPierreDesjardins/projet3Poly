#include <glm/glm.hpp>

#include "Utilitaire.h"

#include "CapteurDistance.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "NoeudPoteau.h"
#include "NoeudMur.h"

const double CapteurDistance::HAUTEUR = 0.75;
const double CapteurDistance::MAX_LARGEUR_TOTALE = 30.0;
const double CapteurDistance::LARGEUR_DEFAUT = 5.0;

CapteurDistance::CapteurDistance()
{
}


CapteurDistance::~CapteurDistance()
{
}

CapteurDistance::CapteurDistance(const glm::dvec3& positionRelative, const double& angleRelatif)
    : positionRelative_(positionRelative), angleRelatif_(angleRelatif)
{ 
    glm::dvec3 positionDanger = positionRelative;
    positionDanger.x += LARGEUR_DEFAUT / 2.0; 
    glm::dvec3 positionSecuritaire = positionDanger;
    positionSecuritaire.x += LARGEUR_DEFAUT;

    utilitaire::calculerPositionApresRotation(positionRelative, positionDanger, angleRelatif);

    zoneDanger_ = RectangleEnglobant(positionDanger, angleRelatif, HAUTEUR, LARGEUR_DEFAUT);
    zoneSecuritaire_ = RectangleEnglobant(positionSecuritaire, angleRelatif, HAUTEUR, LARGEUR_DEFAUT);
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

void CapteurDistance::mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot)
{
    
}

void CapteurDistance::afficher() const
{
    double largeurDanger = zoneDanger_.obtenirLargeur();
    double hauteurDanger = zoneDanger_.obtenirHauteur();

    //Dessiner la zone de danger.
    glPushMatrix();
    if (etat_ == DETECTION_ZONE_DANGER)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(1.0, 1.0, 0.0);
    
	glTranslated(positionRelative_.x, positionRelative_.y, 0.0);        
    glRotated(angleRelatif_, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	glVertex3d(largeurDanger, hauteurDanger / 2.0, 5.0);
	glVertex3d(0.0, hauteurDanger / 2.0, 5.0);
	glVertex3d(0.0, - hauteurDanger / 2.0, 5.0);
	glVertex3d(largeurDanger, - hauteurDanger / 2.0, 5.0);
	glEnd();

    double largeurSecuritaire = zoneSecuritaire_.obtenirLargeur();
    double hauteurSecuritaire = zoneSecuritaire_.obtenirHauteur();

    //Dessiner la zone de danger.
    if (etat_ == DETECTION_ZONE_SECURITAIRE)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.0, 1.0, 0.0);

	glTranslated(largeurDanger, 0.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(largeurSecuritaire, hauteurDanger / 2.0, 5.0);
	glVertex3d(0.0, hauteurDanger / 2.0, 5.0);
	glVertex3d(0.0, - hauteurDanger / 2.0, 5.0);
	glVertex3d(largeurSecuritaire, - hauteurDanger / 2.0, 5.0);
	glEnd();
    glPopMatrix();
}