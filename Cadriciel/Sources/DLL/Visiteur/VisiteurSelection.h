///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SELECTION_H
#define VISITEUR_SELECTION_H

#include "VisiteurAbstrait.h"

class VisiteurSelection : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSelection();

	// Constructeur par paramètre.
	VisiteurSelection(const int& x, const int& y);

	/// Destructeur.
	virtual ~VisiteurSelection();

	
	/// Parcours du noeudTable.
	virtual void visiter(NoeudTable* noeud);

	virtual void visiterRectangle(NoeudTable* noeud);

	//Indique si la touche control est appuyee
	void assignerControl(bool estControl);

	bool estDansRectangleElastique(glm::dvec3 coinRectElastMin, glm::dvec3 coinRectElastMax, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4);

private:
	bool estControlAppuye = false;
};

#endif // VISITEUR_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////