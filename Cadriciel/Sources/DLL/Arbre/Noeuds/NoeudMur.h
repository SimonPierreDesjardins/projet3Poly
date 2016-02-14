///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDMUR_H__
#define __ARBRE_NOEUDS_NOEUDMUR_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigne
/// @brief Noeud des murs servant d'obstacles au robot.
///
/// @author Frédéric Grégoire
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudAbstrait
{

public:

	/// Constructeur
	NoeudMur(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMur();

	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative);
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////