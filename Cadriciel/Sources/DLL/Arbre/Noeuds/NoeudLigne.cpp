///////////////////////////////////////////////////////////////////////////////
/// @file NoeudLigne.cpp
/// @author Frederic Gregoire
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudLigne.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigne::NoeudLigne(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::NoeudLigne(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigne::~NoeudLigne()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigne::~NoeudLigne()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::afficherConcret() const
{
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4f(1.0f, 0.2f, 0.0f, 1.0f);
	}
	else
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	glPopMatrix();
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

/*
void NoeudLigne::mettreAJourQuadEnglobantConcret()
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
