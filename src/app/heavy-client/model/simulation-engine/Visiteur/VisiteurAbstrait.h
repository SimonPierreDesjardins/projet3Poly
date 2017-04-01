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
class NoeudLigne;
class NoeudSegment;
class NoeudRobot;
class NoeudAraignee;
class NoeudDuplication;
class NoeudDepart;
class NoeudJonction;
class NoeudRoues;
class NoeudSkybox;
class NoeudTeleporteur;
class NoeudPiece;
class NoeudLigneCourseAbstrait;
class NoeudCheckpoint;

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
	inline void assignerPositionRelativeAvant(glm::dvec3 positionRelativeAvant);
	inline void assignerPositionRelativeApres(glm::dvec3 positionRelativeApres);
	inline void assignerAngleRotation(double angleRotation);
	inline void assignerFacteurMiseAEchelle(double facteurDimension);
	inline void assignerEstAffiche(const bool& estAffiche);
	inline void assignerEstDrag(const bool& estDrag);
	inline NoeudAbstrait* obtenirReferenceNoeud();
	inline bool obtenirEstDrag();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudDuplication* noeud);
	virtual void visiter(NoeudDepart* noeud);
	virtual void visiter(NoeudJonction* noeud);
	virtual void visiter(NoeudRobot* noeud);
	virtual void visiter(NoeudRoues* noeud);
	virtual void visiter(NoeudTeleporteur* noeud);
	virtual void visiter(NoeudPiece* noeud);
	virtual void visiter(NoeudLigneCourseAbstrait* noeud);

protected:
	glm::dvec3 positionRelative_{ glm::dvec3() };
	glm::dvec3 positionRelativeAvant_{ glm::dvec3() };
	glm::dvec3 positionRelativeApres_{ glm::dvec3() };

	bool estDrag_{ false };
	double angleRotation_{ 0.0 };
	double facteurMiseAEchelle_{ 0.0 };

	bool estAffiche_{ false };
	NoeudAbstrait* referenceNoeud_{ nullptr };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerPositionRelative(glm::dvec3 positionRelative)
///
/// Fonction qui assigne la positionRelative d'un clic
///
/// @param[in] positionRelative : position du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerPositionRelative(glm::dvec3 positionRelative)
{
	positionRelative_ = positionRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerPositionRelativeAvant(glm::dvec3 positionRelativeAvant)
///
/// Fonction qui assigne la positionRelative d'un clic (lors d'un drag)
///
/// @param[in] positionRelativeAvant : position du clic
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerPositionRelativeAvant(glm::dvec3 positionRelativeAvant)
{
	positionRelativeAvant_ = positionRelativeAvant;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerPositionRelativeApres(glm::dvec3 positionRelativeApres)
///
/// Fonction qui assigne la positionRelative où le clic est relaché.
///
/// @param[in] positionRelativeApres : position où le clic est relaché.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerPositionRelativeApres(glm::dvec3 positionRelativeApres)
{
	positionRelativeApres_ = positionRelativeApres;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerAngleRotation(double angleRotation)
///
/// Fonction qui assigne l'angle de rotation
///
/// @param[in] angleRotation : angle de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerAngleRotation(double angleRotation)
{
	angleRotation_ = angleRotation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerFacteurMiseAEchelle(double facteurDimension)
///
/// Fonction qui assigne le facteur de mise à échelle
///
/// @param[in] facteurDimension : facteur de mise à échelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerFacteurMiseAEchelle(double facteurDimension)
{
	facteurMiseAEchelle_ = facteurDimension;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::obtenirReferenceNoeud()
///
/// Fonction qui retourne la référence d'un noeud
///
/// @param[in] Aucun.
///
/// @return NoeudAbstrait* : le noeud dont on veut la référence.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* VisiteurAbstrait::obtenirReferenceNoeud()
{
	return referenceNoeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerEstAffiche(const bool& estAffiche)
///
/// Fonction qui assigne le booléen estAffiche selon si ... est affiché ou non.
///
/// @param[in] const bool& estAffiche : booléen qui indique si ... est affiché ou non.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerEstAffiche(const bool& estAffiche)
{
	estAffiche_ = estAffiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::assignerEstDrag(const bool& estDrag)
///
/// Fonction qui assigne le booléen estDrag selon s'il s'agit d'un drag ou d'un simple clic.
///
/// @param[in] const bool& estDrag : booléen qui indique s'il s'agit d'un drag ou d'un simple clic.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurAbstrait::assignerEstDrag(const bool& estDrag)
{
	estDrag_ = estDrag;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::obtenirEstDrag()
///
/// Fonction qui retrourne l'attribut estDrag qui indique s'il s'agit d'un drag ou d'un simple clic.
///
/// @param[in] Aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline bool VisiteurAbstrait::obtenirEstDrag()
{
	return estDrag_;
}

#endif // VISITEUR_ABSTRAIT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////