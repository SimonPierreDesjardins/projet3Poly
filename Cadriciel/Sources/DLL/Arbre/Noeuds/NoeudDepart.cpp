///////////////////////////////////////////////////////////////////////////////
/// @file NoeudDepart.cpp
/// @author Frédéric Grégoire
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudDepart.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::NoeudDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::NoeudDepart(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	estDuplicable_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::~NoeudDepart()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::~NoeudDepart()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne()) {
		glColor4d(1.0, 0.20, 0.0, 1.0);
	}
	else {
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}

	glRotated(angleRotation_, 0, 0, 1);

	// Affichage du modèle.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudDepart::animer(float dt)
{
    mettreAJourFormeEnglobante();
}

void NoeudDepart::mettreAJourFormeEnglobante()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
