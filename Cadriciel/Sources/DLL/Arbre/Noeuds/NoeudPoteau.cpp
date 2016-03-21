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
///
/// @fn NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
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
    double hauteur = glm::abs(boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x);
    double largeur = glm::abs(boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y);
    double rayon = hauteur > largeur ? hauteur : largeur;
    rayon /= 2.0;
    cercleEnglobant_.mettreAJour(positionCourante_, rayon);
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

	if (estSelectionne()) {
		glColor4d(1.0, 0.2, 0.0, 1.0);
	}
	else {
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}
	// Effectuer la mise à échelle.
	glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, 1);
	
	// Affichage du modèle.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();

    cercleEnglobant_.afficher(positionCourante_);
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