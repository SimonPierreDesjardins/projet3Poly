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
	inline void assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic);
	bool quadEstDansRectangleElastique(const utilitaire::QuadEnglobant& quad);

private:
	bool ctrlAppuye_ = false;
	double xMinRectangleElastique_;
	double xMaxRectangleElastique_;
	double yMinRectangleElastique_;
	double yMaxRectangleElastique_;
};

//TODO: enlever le inline.
inline void VisiteurSelection::assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic)
{	
	// Assigner la position min et max en x du rectangle elastique.
	if (positionDeuxiemeClic.x < positionPremierClic.x)
	{
		xMinRectangleElastique_ = positionDeuxiemeClic.x;
		xMaxRectangleElastique_ = positionPremierClic.x;
	}
	else
	{
		xMinRectangleElastique_ = positionPremierClic.x;
		xMaxRectangleElastique_ = positionDeuxiemeClic.x;
	}
	// Assigner la position min et max en y du rectangle elastique.
	if (positionDeuxiemeClic.y < positionPremierClic.y)
	{
		yMinRectangleElastique_ = positionDeuxiemeClic.y;
		yMaxRectangleElastique_ = positionPremierClic.y;
	}
	else
	{
		yMinRectangleElastique_ = positionPremierClic.y;
		yMaxRectangleElastique_ = positionDeuxiemeClic.y;
	}
}

#endif // VISITEUR_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////