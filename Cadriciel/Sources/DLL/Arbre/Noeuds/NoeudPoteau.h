///////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDPOTEAU_H__
#define __ARBRE_NOEUDS_NOEUDPOTEAU_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

//class VisiteurAbstrait;

class NoeudPoteau : public NoeudAbstrait
{

public:

	/// Constructeur
	NoeudPoteau(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPoteau();

	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual utilitaire::BoiteEnglobante obtenirBoiteEnglobanteCourante() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////