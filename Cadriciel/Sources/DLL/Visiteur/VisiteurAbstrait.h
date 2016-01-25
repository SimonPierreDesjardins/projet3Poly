///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author Olivier St-Amour
/// @date 2016-01-13
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_ABSTRAIT_H
#define VISITEUR_ABSTRAIT_H

#include "FacadeModele.h"
#include "glm\glm.hpp"

class ArbreRendu;
class NoeudPoteau;
class NoeudTable;
class NoeudMur;
class NoeudLigneNoire;
class NoeudRobot;
class NoeudAraignee;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
/// @brief Classe de base du patron visiteur utilisée pour effectuer des
///		   manipulations sur l'arbre de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les visiteurs concrets. 
///
/// @author Olivier St-Amour
/// @date 2016-01-13
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurAbstrait();
	// Constructeur par paramètre.
	VisiteurAbstrait(const int& x, const int& y);
	/// Destructeur.
	virtual ~VisiteurAbstrait();

	inline void assignerPositionRelative(glm::dvec3 positionRelative);
	inline void assignerAngleRotation(float angleRotation);
	inline void assignerFacteurDimension(float facteurDimension);

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigneNoire* noeud);

protected:
	glm::dvec3 positionRelative_;
	float angleRotation_;
	float facteurDimension_;
};


inline void VisiteurAbstrait::assignerPositionRelative(glm::dvec3 positionRelative)
{
	positionRelative_ = positionRelative;
}

inline void VisiteurAbstrait::assignerAngleRotation(float angleRotation)
{
	angleRotation_ = angleRotation;
}

inline void VisiteurAbstrait::assignerFacteurDimension(float facteurDimension)
{
	facteurDimension_ = facteurDimension;
}


#endif // VISITEUR_ABSTRAIT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////