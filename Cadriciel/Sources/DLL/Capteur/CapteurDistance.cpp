////////////////////////////////////////////////////////////////////////////////
/// @file   CapteurDistance.cpp
/// @author Olivier St-Amour
/// @date   2016-03-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurDistance::CapteurDistance()
///
/// Constructeur par défaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurDistance::CapteurDistance()
{
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurDistance::CapteurDistance(const glm::dvec3& positionRelative, const double& angleRelatif)
///
/// Constructeur par paramètres.
///
/// @param[in] positionRelative : La position relative à la position du robot.
///
/// @param[in] angleRelatif : L'angle relatif à l'angle de rotation du robot.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurDistance::CapteurDistance(const glm::dvec3& positionRelative, const double& angleRelatif)
    : positionRelative_(positionRelative), angleRelatif_(angleRelatif)
{ 
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurDistance::~CapteurDistance()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurDistance::~CapteurDistance()
{
}


////////////////////////////////////////////////////////////////////////////////
///
/// void CapteurDistance::verifierDetection(NoeudPoteau* poteau)
///
/// Cette méthode permet de faire la vérification de la détection sur un poteau
/// à l'aide de sa forme englobante. La détection en zone de danger est priorisée
/// sur la détection en zone sécuritaire.
///
/// @param[in] poteau : Un pointeur sur un poteau.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurDistance::verifierDetection(NoeudPoteau* poteau)
{
    RectangleEnglobant rectangle = poteau->obtenirRectangleEnglobant();
    // Si le capteur se trouve déjà en détection de zone de danger, 
    // on le laisse dans cet état.
    if (etat_ != DETECTION_ZONE_DANGER)
    {
        bool danger = zoneDanger_.calculerIntersection(rectangle);
        if (!danger)
        {
            // Si le poteau n'est pas en zone de danger et on se trouve 
            // déjà en détection de zone sécuritaire, on le laisse dans cet état.
            if (etat_ != DETECTION_ZONE_SECURITAIRE) 
            {
                bool securitaire = zoneSecuritaire_.calculerIntersection(rectangle);
                if (!securitaire) 
                {
                    etat_ = AUCUNE_DETECTION;
                } 
                else 
                {
                    etat_ = DETECTION_ZONE_SECURITAIRE;
                }
            }
        }
        else 
        {
            etat_ = DETECTION_ZONE_DANGER;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
///
/// void CapteurDistance::verifierDetection(NoeudMur* mur)
///
/// Cette méthode permet de faire la vérification de la détection sur un mur
/// à l'aide de sa forme englobante. La détection en zone de danger est priorisée
/// sur la détection en zone sécuritaire.
///
/// @param[in] mur : Un pointeur sur un mur.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurDistance::verifierDetection(NoeudMur* mur)
{
    RectangleEnglobant rectangle = mur->obtenirRectangleEnglobant();
    // Si le capteur se trouve déjà en détection de  zone de danger,
    // on le laisse dans cet état.
    if (etat_ != DETECTION_ZONE_DANGER)
    {
        bool danger = zoneDanger_.calculerIntersection(rectangle);
        if (!danger)
        {
            // Si le poteau n'est pas en zone de danger et on se trouve 
            // déjà en détection de zone sécuritaire, on le laisse dans cet état.
            if (etat_ != DETECTION_ZONE_SECURITAIRE) 
            {
                bool securitaire = zoneSecuritaire_.calculerIntersection(rectangle);
                if (!securitaire) 
                {
                    etat_ = AUCUNE_DETECTION;
                } 
                else 
                {
                    etat_ = DETECTION_ZONE_SECURITAIRE;
                }
            }
        }
        else 
        {
            etat_ = DETECTION_ZONE_DANGER;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurDistance::mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot)
///
/// Cette méthode permet de faire la mise à jour du rectangle englobant du
/// capteur.
///
/// @param[in] positionRobot : La position courante du robot.
///
/// @param[in] angleRotationRobot : L'angle de rotation courant du robot.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurDistance::mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot)
{
    // Calculer la courante position du capteur.
    utilitaire::calculerPositionApresRotation(positionRelative_, positionCapteur_, angleRotationRobot);
    positionCapteur_ += positionRobot;

    // Calculer la position des zones du capteur.
    glm::dvec3 positionDanger = { 0.0, 0.0, 0.0 };
    glm::dvec3 positionSecuritaire{ 0.0, 0.0, 0.0 };

    positionDanger.x = (largeurDanger_ / 2.0);
    positionSecuritaire.x = (largeurDanger_ + largeurSecuritaire_ / 2.0);

    double angleCourant = angleRelatif_ + angleRotationRobot;
    utilitaire::calculerPositionApresRotation(positionDanger, positionDanger, angleCourant);
    utilitaire::calculerPositionApresRotation(positionSecuritaire, positionSecuritaire, angleCourant);

    positionDanger += positionCapteur_;
    positionSecuritaire += positionCapteur_;

    zoneDanger_.mettreAJour(positionDanger, angleCourant, HAUTEUR, largeurDanger_);
    zoneSecuritaire_.mettreAJour(positionSecuritaire, angleCourant, HAUTEUR, largeurSecuritaire_);

    etat_ = AUCUNE_DETECTION;
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurDistance::afficher() const
///
/// Méthode permettant d'afficher le capteur dans la scène à des fins de 
/// débogage. La zone de danger est jaune et la zone sécuritaire est verte quand
/// il n'y a pas de détection. S'il y a un détection, les zones deviennt rouge.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
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

    //Dessiner la zone sécuritaire.
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
    glColor4f(0.0, 0.0, 0.0, 1.0);
}

/////////////////////////////////////////////////////////////////////////////////
/// @}
/////////////////////////////////////////////////////////////////////////////////
