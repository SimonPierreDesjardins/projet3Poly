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
#include "ControleurLumiere.h"
#include "GL/glew.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Noeud repr�sentant la table, c'est � dire la zone de simulation.
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

    virtual RectangleEnglobant* obtenirFormeEnglobante();
    virtual const RectangleEnglobant* obtenirFormeEnglobante() const;

    virtual void mettreAJourFormeEnglobante();

	/// Affiche la table.
	virtual void afficherConcret() const;
	/// Accepter un visiteur.
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
    RectangleEnglobant rectangleEnglobant_;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////