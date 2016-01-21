///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneNoire.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDLIGNENOIRE_H__
#define __ARBRE_NOEUDS_NOEUDLIGNENOIRE_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class NoeudLigneNoire : public NoeudComposite{

public:

	/// Constructeur
	NoeudLigneNoire(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudLigneNoire();

	/// Affiche la table.
	virtual void afficherConcret() const;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////