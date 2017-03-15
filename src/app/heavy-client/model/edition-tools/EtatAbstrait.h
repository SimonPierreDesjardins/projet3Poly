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
#include "glm\glm.hpp"
#include "VisiteurAbstrait.h"
#include "Observable.h"
#include "TypeOfTool.cs"

class ArbreRendu;
namespace vue
{
	class Vue;
};

namespace event_handler
{
	class EventHandler;
}

///////////////////////////////////////////////////////////////////////////
/// @class EtatAbstrait
/// @brief Classe de base pour chaque état
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les états pouvant être présent dans le modèle
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
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

	// Gestion du symbole du curseur.
	void gererPositionCurseur(const glm::dvec3& position);
	virtual void gererPositionCurseurConcret(const bool& pointeurEstSurTable);
	virtual void assignerSymboleCurseur();

	// Gestion de touches
	virtual void gererToucheEchappe();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererToucheAltEnfoncee();
	virtual void gererToucheAltRelachee();

	int getType() { return type_; }
	void setType(Tool toolName) { type_ = toolName; }

protected:
	virtual void reinitialiser();

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

	int type_ = NONE;
};

#endif /// ETAT_ABSTRAIT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
