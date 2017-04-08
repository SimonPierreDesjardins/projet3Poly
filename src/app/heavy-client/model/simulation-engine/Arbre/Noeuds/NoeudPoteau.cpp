///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPoteau.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
//
// Ce constructeur ne fait qu'appeler la version de la classe et base
// et donner des valeurs par défaut aux variables membres.
//
// @param[in] id :        L'identifiant du noeud.
// @param[in] typeNoeud : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudPoteau::NoeudPoteau(uint32_t id, const std::string& typeNoeud)
	: NoeudAbstrait{ id, typeNoeud }
{
	type_ = POST_ENTITY;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudPoteau::animer(float dt)
{
    mettreAJourFormeEnglobante();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise à jour de la forme englobante pour le poteau.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::mettreAJourFormeEnglobante()
{


	physics_.absolutePosition = physics_.relativePosition;

    double hauteur = glm::abs(boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x);
    double largeur = glm::abs(boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y);
    double rayon = hauteur > largeur ? hauteur : largeur;
    rayon /= 2.0;
	cercleEnglobant_.mettreAJour({ physics_.absolutePosition.x,
								   physics_.absolutePosition.y,
								   physics_.absolutePosition.z },
		                           rayon * physics_.scale.x);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::~NoeudPoteau()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPoteau::~NoeudPoteau()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudPoteau::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le poteau.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant* NoeudPoteau::obtenirFormeEnglobante()
{
    return &cercleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudPoteau::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le poteau.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const CercleEnglobant* NoeudPoteau::obtenirFormeEnglobante() const
{
    return &cercleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::afficherConcret() const
{

	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne()) 
    {
        glDisable(GL_COLOR_MATERIAL);
		glColor4f(selectionColor_.x, selectionColor_.y, selectionColor_.z, selectionColor_.w);
        glEnable(GL_COLOR_MATERIAL);
	}

	// Effectuer la mise à échelle.
	glScaled(physics_.scale.x, physics_.scale.y, physics_.scale.z);
	
	// Affichage du modèle.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    //cercleEnglobant_.afficher(physics_.absolutePosition);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////