///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author Olivier St-Amour
/// @date 2016-01-29
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H

#include "VisiteurAbstrait.h"

class VisiteurRotation : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurRotation();

	// Constructeur par paramètre.
	VisiteurRotation(const int& x, const int& y);

	/// Destructeur.
	virtual ~VisiteurRotation();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigneNoire* noeud);

private:
	void calculerCentreSelection(NoeudAbstrait* noeud);
	glm::dvec3 centreSelection_;
};


#endif // VISITEUR_ROTATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////