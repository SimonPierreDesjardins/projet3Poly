///////////////////////////////////////////////////////////////////////////
/// @file EtatAbstrait.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_ABSTRAIT_H
#define ETAT_ABSTRAIT_H

#include <memory>
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class ArbreRendu;
namespace vue
{
	class Vue;
};

enum Etat
{
	SELECTION,
	DEPLACEMENT,
	ROTATION,
	MISE_A_ECHELLE,
	DUPLICATION,
	CREATION_POTEAU,
	CREATION_MUR,
	CREATION_LIGNE_NOIRE,
	ZOOM
};

///////////////////////////////////////////////////////////////////////////
/// @class EtatAbstrait
/// @brief Classe qui représente l'état abstrait de notre machine à états
///
///        Cette classe s'occupe de déclarer les fonctions qui seront implémentés 
///	       dans les états dérivés.
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class EtatAbstrait
{
public:
	EtatAbstrait();
	virtual ~EtatAbstrait();

	// Gestion de la souris
	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);
	virtual void gererMoletteSouris(const int & delta);

	// Gestion du symbole du curseur.
	void gererPositionCurseur(const glm::dvec3& position);
	virtual void gererPositionCurseurConcret(const bool& pointeurEstSurTable);
	virtual void assignerSymboleCurseur();

	// Gestion de touches
	virtual void gererToucheEchappe();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererTouchePlus();
	virtual void gererToucheMoins();
	virtual void gererToucheAltEnfoncee();
	virtual void gererToucheAltRelachee();
	inline Etat obtenirTypeEtat() const;

protected:
	virtual void reinitialiser();

	Etat typeEtat_{ SELECTION };

	ArbreRendu* arbre_{ nullptr };
	vue::Vue* vue_{ nullptr };

	bool estClickDrag();
	bool curseurEstSurTable_{ true };
	bool enCreation_{ false };

	bool toucheCtrlEnfonce_{ false };
	bool toucheAltEnfonce_{ false };
	bool clicGaucheEnfonce_{false};
	bool clicDroitEnfonce_{false};

	int ancienX_{ 0 };
	int ancienY_{ 0 };
	glm::ivec2 anchor{glm::ivec2()};
	static glm::ivec2 currentPosition_;
};

inline Etat EtatAbstrait::obtenirTypeEtat() const
{
	return typeEtat_;
}

#endif /// ETAT_ABSTRAIT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
