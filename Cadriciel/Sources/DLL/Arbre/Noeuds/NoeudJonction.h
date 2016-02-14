///////////////////////////////////////////////////////////////////////////
/// @file NoeudJonction.h
/// @author Camille Gendreau
/// @date 2016-02-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDJONCTION_H__
#define __ARBRE_NOEUDS_NOEUDJONCTION_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudJonction
/// @brief Noeud de l'objet rendu servant à la liaison de segments de la ligne noire.
///
/// @author Camille Gendreau
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////

class NoeudJonction : public NoeudAbstrait
{

public:

	/// Constructeur
	NoeudJonction(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudJonction();

	/// Affiche la table.
	virtual void afficherConcret() const;
//	virtual void mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative);
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////