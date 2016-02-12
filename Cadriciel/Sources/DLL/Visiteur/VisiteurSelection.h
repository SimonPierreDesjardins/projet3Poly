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

	virtual void visiterRectangle(NoeudTable* noeud);

	//Indique si la touche control est appuyee
	void assignerControl(bool ctrlAppuye);
	inline void assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic);
	bool estDansRectangleElastique(glm::dvec3 coinRectElastMin, glm::dvec3 coinRectElastMax, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4);

private:
	bool ctrlAppuye_ = false;
	glm::dvec3 coinsRectangleElastique[4];
};


inline void VisiteurSelection::assignerPositionRectElast(const glm::dvec3& positionPremierClic, const glm::dvec3& positionDeuxiemeClic)
{
	coinsRectangleElastique[0] = positionDeuxiemeClic;
	coinsRectangleElastique[1].x = positionPremierClic.x;
	coinsRectangleElastique[1].y = positionDeuxiemeClic.y;
	coinsRectangleElastique[2] = positionPremierClic;
	coinsRectangleElastique[3].x = positionDeuxiemeClic.x;
	coinsRectangleElastique[3].y = positionDeuxiemeClic.y;
}

#endif // VISITEUR_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////