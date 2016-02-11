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

#include "glm\glm.hpp"

class ArbreRendu;

class NoeudAbstrait;
class NoeudPoteau;
class NoeudTable;
class NoeudMur;
class NoeudLigneNoire;
class NoeudSegment;
class NoeudRobot;
class NoeudAraignee;
class NoeudDuplication;
class NoeudDepart;

namespace modele{
	class Modele3D;
}

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

	/// Destructeur.
	virtual ~VisiteurAbstrait();

	inline void assignerPositionRelative(glm::dvec3 positionRelative);
	inline void assignerAngleRotation(double angleRotation);
	inline void assignerFacteurMiseAEchelle(double facteurDimension);
	inline void assignerEstAffiche(const bool& estAffiche);
	inline NoeudAbstrait* obtenirReferenceNoeud();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigneNoire* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudDuplication* noeud);
	virtual void visiter(NoeudDepart* noeud);

protected:
	glm::dvec3 positionRelative_;
	double angleRotation_;
	double facteurMiseAEchelle_;
	bool estAffiche_{ false };

	modele::Modele3D* referenceModele_;
	NoeudAbstrait* referenceNoeud_;
};



inline void VisiteurAbstrait::assignerPositionRelative(glm::dvec3 positionRelative)
{
	positionRelative_ = positionRelative;
}

inline void VisiteurAbstrait::assignerAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}

inline void VisiteurAbstrait::assignerFacteurMiseAEchelle(double facteurDimension)
{
	facteurMiseAEchelle_ = facteurDimension;
}

inline NoeudAbstrait* VisiteurAbstrait::obtenirReferenceNoeud()
{
	return referenceNoeud_;
}

inline void VisiteurAbstrait::assignerEstAffiche(const bool& estAffiche)
{
	estAffiche_ = estAffiche;
}
#endif // VISITEUR_ABSTRAIT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////