///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPiece.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPiece.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPiece::NoeudPiece(uint32_t id, const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud et le id du noeud
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPiece::NoeudPiece(uint32_t id, const std::string& typeNoeud)
	: NoeudAbstrait{ id, typeNoeud }
{
	type_ = COIN_ENTITY;
	physics_.absolutePosition.z = 1.0;
	physics_.relativePosition.z = 1.0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPiece::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise à jour de la forme englobante pour la piece.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPiece::mettreAJourFormeEnglobante()
{
	double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
	double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
	rectangleEnglobant_.mettreAJour(physics_.absolutePosition, physics_.rotation.z, hauteur, largeur);

	hauteur = glm::abs(boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x);
	largeur = glm::abs(boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y);
	double rayon = hauteur > largeur ? hauteur : largeur;
	rayon = 11;
	cercleEnglobant_.mettreAJour(physics_.absolutePosition, rayon);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPiece::~NoeudPiece()
///
/// Ce destructeur désallouee la liste d'affichage du teleporteur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPiece::~NoeudPiece()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudPiece::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le teleporteur.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant* NoeudPiece::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudPiece::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le teleporteur.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudPiece::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudPiece::obtenirCercleEnglobante()
///
/// Cette fonction permet d'obtenir le cercle englobant pour le teleporteur.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant* NoeudPiece::obtenirCercleEnglobante()
{
	return &cercleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudPiece::obtenirCercleEnglobante() const
///
/// Cette fonction permet d'obtenir le cercle englobant pour le teleporteur.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const CercleEnglobant* NoeudPiece::obtenirCercleEnglobante() const
{
	return &cercleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPiece::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPiece::afficherConcret() const
{

	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne()) 
    {
        glDisable(GL_COLOR_MATERIAL);
		glColor4f(1.0f, 0.20f, 0.0f, 1.0f);
        glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(0.797f, 0.8f, 0.0f, 1.0f);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotated(physics_.rotation.z, 0, 0, 1);
	
	// Affichage du modèle.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    //rectangleEnglobant_.afficher(positionCourante_);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPiece::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPiece::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////