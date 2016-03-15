///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Camille Gendreau
/// @date 2016-01-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDTABLE_H__
#define __ARBRE_NOEUDS_NOEUDTABLE_H__

#include "NoeudComposite.h"
#include "VisiteurAbstrait.h"
#include "RectangleEnglobant.h"
#include "GL/glew.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Noeud représentant la table, c'est à dire la zone de simulation.
///
/// @author Camille Gendreau
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{

public:
	/// Constructeur
	NoeudTable(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTable();
	/// Affiche la table.
	virtual void afficherConcret() const;
	/// Accepter un visiteur.
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

	inline RectangleEnglobant obtenirRectangleEnglobant() const;
private:
    RectangleEnglobant rectangleEnglobant_;
};

inline RectangleEnglobant NoeudTable::obtenirRectangleEnglobant() const
{
	return rectangleEnglobant_;
}
#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////