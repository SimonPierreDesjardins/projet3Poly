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
		glColor4d(1.0, 0.2, 0.0, 1.0);
	}
	else
	{
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	glPopMatrix();
	
}

void NoeudLigne::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
