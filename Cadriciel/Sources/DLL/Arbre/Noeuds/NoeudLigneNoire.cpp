///////////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneNoire.cpp
/// @author Frederic Gregoire
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudLigneNoire.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneNoire::NoeudLigneNoire(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneNoire::NoeudLigneNoire(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneNoire::~NoeudLigneNoire()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneNoire::~NoeudLigneNoire()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneNoire::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneNoire::afficherConcret() const
{
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		glColor4f(0.0, 1.0, 0.0, 1.0);
	}

	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	glPopMatrix();
	
}

void NoeudLigneNoire::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

/*
void NoeudLigneNoire::mettreAJourQuadEnglobantConcret()
{
	for (int i = 0; i < enfants_.size(); i++)
	{
		enfants_[i]->mettreAJourQuadEnglobant();
	}
}
*/
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
