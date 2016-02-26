///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionLigne.h
/// @author Olivier St-Amour
/// @date 2016-02-26
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_LIGNE_H
#define VISITEUR_DETECTION_LIGNE_H

#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant à un capteur optique 
///		   de détecter une ligne à une certaine position. 
///
/// @author Olivier St-Amour
/// @date 2016-02-26
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionLigne : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDetectionLigne();
	/// Destructeur.
	virtual ~VisiteurDetectionLigne();

	inline void assignerPositionCapteurOptique(const glm::dvec3& positionCapteur);
	inline bool	ligneEstDetectee();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudLigne* noeud);

private:
	bool ligneEstDetectee_{ false };
	glm::dvec3 positionCapteur_;
};


inline void VisiteurDetectionLigne::assignerPositionCapteurOptique(const glm::dvec3& positionCapteur)
{
	positionCapteur_ = positionCapteur;
}


inline bool	VisiteurDetectionLigne::ligneEstDetectee()
{
	return ligneEstDetectee_;
}

#endif // VISITEUR_DETECTION_LIGNE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////