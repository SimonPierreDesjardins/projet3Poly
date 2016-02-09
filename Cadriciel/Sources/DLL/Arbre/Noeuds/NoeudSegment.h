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
	NoeudSegment(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudSegment();
	virtual void mettreAJourQuadEnglobantConcret();
	
	/// Affiche le segment.
	virtual void afficherConcret() const;

	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////