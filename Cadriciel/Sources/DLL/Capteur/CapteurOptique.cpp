#include <glm/glm.hpp>
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "VisiteurDetectionLigne.h"

#include "CapteurOptique.h"

CapteurOptique::CapteurOptique()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
}

CapteurOptique::~CapteurOptique()
{
}

CapteurOptique::CapteurOptique(const glm::dvec3& positionRelative, VisiteurDetectionLigne* visiteur)
	: positionRelative_(positionRelative), visiteur_(visiteur)
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
}

void CapteurOptique::mettreAJourEtat(const glm::dvec3& positionRobot, const double& angleRotationRobot)
{
	glm::dvec3 positionApresRotation = { 0.0, 0.0, 0.0 };
	utilitaire::calculerPositionApresRotation(positionRelative_, positionApresRotation, angleRotationRobot);
	positionCourante_ = positionRobot + positionApresRotation;
	visiteur_->assignerPositionCapteurOptique(positionCourante_);
	arbre_->accepterVisiteur(visiteur_);
	ligneEstDetectee_ = visiteur_->ligneEstDetectee();
}
