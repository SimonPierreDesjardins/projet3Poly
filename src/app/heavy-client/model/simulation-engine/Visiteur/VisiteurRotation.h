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

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotation
/// @brief Visiteur permettant d'effectuer la rotation d'un objet
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurRotation : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurRotation();

	/// Destructeur.
	virtual ~VisiteurRotation();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudDepart* noeud);

private:

	void assignerNouvellePositionRelative(NoeudAbstrait* noeud);
	
	void calculerCentreSelection(NoeudAbstrait* noeud);
	glm::dvec3 centreSelection_;
};

#endif // VISITEUR_ROTATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////