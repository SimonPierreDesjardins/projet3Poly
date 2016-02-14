///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.h
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

class VisiteurAbstrait;

class NoeudSegment : public NoeudAbstrait
{
public:
	NoeudSegment(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudSegment();

	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

//	virtual void mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative);
	
	/// Affiche le segment.
	virtual void afficherConcret() const;

};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////