////////////////////////////////////////////////////////////////////////////////
/// @file   CapteurOptique.cpp
/// @author Olivier St-Amour
/// @date   2016-03-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////

#include "CapteurOptique.h"

#include <glm/glm.hpp>

#include "Utilitaire.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudLigne.h"

const double CapteurOptique::RAYON_CERCLE_ENGLOBANT = 0.4;

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::CapteurOptique()
///
/// Constructeur par d�faut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::CapteurOptique()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::CapteurOptique(const glm::dvec3& positionRelative) 
///
/// Constructeur par param�tres
///
/// @param[in] positionRelative : La positon relative du capteur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::CapteurOptique(const glm::dvec3& positionRelative)
    : positionRelative_(positionRelative) 
{
    cercleEnglobant_ = CercleEnglobant({ 0.0, 0.0, 0.0 }, RAYON_CERCLE_ENGLOBANT);
}
 
////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::~CapteurOptique()
///
/// Destructeur
///
/// @param[in] Aucun.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::~CapteurOptique()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::mettreAJourPosition(const glm::dvec3& positionRobot, 
///                                         const double& angleRotationRobot)
///
/// M�thode permettant de faire la mise � jour la position courante du capteur. 
///
/// @param[in] positionRobot : La positon du robot. 
///
/// @param[in] angleRotationRobot : L'angle de rotation du robot.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurOptique::mettreAJour(const glm::dvec3& positionRobot, 
                                 const double&     angleRotationRobot)
{
	glm::dvec3 positionApresRotation = { 0.0, 0.0, 0.0 };
	utilitaire::calculerPositionApresRotation(positionRelative_, 
                                              positionApresRotation, 
                                              angleRotationRobot);
    positionCourante_ = positionApresRotation + positionRobot;
    ligneEstDetectee_ = false;
    cercleEnglobant_.assignerPositionCentre(positionCourante_);
}


////////////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurOptique::afficher() const
///
/// M�thode permettant d'afficher le capteur dans la sc�ne � des fins de 
/// d�bogage. Le capteur est rouge lorsqu'il d�tecte une linge, si non il est
/// noire.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurOptique::afficher() const
{
    glPushMatrix();
	if (ligneEstDetectee_)
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glColor3f(0.0, 0.0, 0.0);
	}

	glTranslated(positionRelative_.x, positionRelative_.y, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-0.1, -0.1, 5.0);
	glVertex3d(0.1, -0.1, 5.0);
	glVertex3d(0.1, 0.1, 5.0);
	glVertex3d(-0.1, 0.1, 5.0);
	glEnd();

    cercleEnglobant_.afficher(positionCourante_);

	glPopMatrix();

}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurOptique::verifierDetection(NoeudLigne* ligne)
///
/// Cette m�thode permet de faire la v�rification de la d�tection d'une ligne
/// � l'aide de sa forme englobante. 
///
/// @param[in] ligne : Un pointeur sur une ligne.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurOptique::verifierDetection(NoeudLigne* ligne)
{
	NoeudAbstrait* enfant = nullptr;
    unsigned int n = ligne->obtenirNombreEnfants();
	RectangleEnglobant rectangle;
	for (unsigned int i = 0; i < n && !ligneEstDetectee_; i++)
	{
		enfant = ligne->chercher(i);
		ligneEstDetectee_ = enfant->obtenirFormeEnglobante()->calculerIntersection(cercleEnglobant_);
	}
}

/////////////////////////////////////////////////////////////////////////////////
/// @}
/////////////////////////////////////////////////////////////////////////////////
