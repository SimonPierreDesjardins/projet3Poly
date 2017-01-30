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
/// et donner des valeurs par d�faut aux variables membres.
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
/// Cette fonction permet de faire la mise � jour de la forme englobante pour le poteau.
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
    cercleEnglobant_.mettreAJour(positionCourante_, rayon * facteurMiseAEchelle_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::~NoeudPoteau()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
/// Cette fonction effectue le v�ritable rendu de l'objet.
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
		glColor4d(1.0, 0.20, 0.0, 1.0);
        glEnable(GL_COLOR_MATERIAL);
	}

	// Effectuer la mise � �chelle.
	glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, 1);
	
	// Affichage du mod�le.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    //cercleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
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