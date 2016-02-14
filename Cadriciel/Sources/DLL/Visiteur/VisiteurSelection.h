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
#include "Utilitaire.h"
#include <memory>


class VisiteurSelection : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSelection();

	/// Destructeur.
	virtual ~VisiteurSelection();
	
	/// Parcours du noeudTable.
	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudDepart* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudJonction* noeud);

	//Indique si la touche control est appuyee
	void assignerControl(bool ctrlAppuye);
	void assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic);
	bool quadEstDansRectangleElastique(const utilitaire::QuadEnglobant& quad);

private:
	bool ctrlAppuye_ = false;
	double xMinRectangleElastique_;
	double xMaxRectangleElastique_;
	double yMinRectangleElastique_;
	double yMaxRectangleElastique_;
};
#endif // VISITEUR_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////