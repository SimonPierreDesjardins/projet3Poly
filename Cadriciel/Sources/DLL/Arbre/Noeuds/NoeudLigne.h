///////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.h
/// @author Frederic Gregoire
/// @date 2016-01-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDLIGNE_H__
#define __ARBRE_NOEUDS_NOEUDLIGNE_H__

#include "NoeudComposite.h"
#include "GL/glew.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudLigne
/// @brief Noeud de l'objet englobant tous les segments et jonctions d'une ligne noire
///
/// @author 
/// @date 2016-01-20
///////////////////////////////////////////////////////////////////////////
class NoeudLigne: public NoeudComposite
{
public:

	/// Constructeur
	NoeudLigne(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudLigne();
	/// Affiche la table.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:

};

#endif //__ARBRE_NOEUDS_NOEUDLIGNE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////