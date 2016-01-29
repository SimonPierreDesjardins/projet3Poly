///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneNoire.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDSEGMENT_H__
#define __ARBRE_NOEUDS_NOEUDSEGMENT_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class NoeudSegment : public NoeudAbstrait
{

public:

	/// Constructeur
	NoeudSegment(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudSegment();

	/// Affiche la table.
	virtual void afficherConcret() const;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////