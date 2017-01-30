///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.cpp
/// @author Camille Gendreau
/// @date 2016-02-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudJonction.h"
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
NoeudJonction::NoeudJonction(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
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
NoeudJonction::~NoeudJonction()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudJonction::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le poteau.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant* NoeudJonction::obtenirFormeEnglobante()
{
    return &cercleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudJonction::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour la jonction.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const CercleEnglobant* NoeudJonction::obtenirFormeEnglobante() const
{
    return &cercleEnglobant_;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudJonction::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudJonction::animer(float dt)
{
    mettreAJourFormeEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudJonction::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise � jour de la forme englobante pour le jonction.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudJonction::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
    double rayon = hauteur > largeur ? largeur : hauteur;
    rayon /= 2;
    cercleEnglobant_.mettreAJour(positionCourante_, rayon);
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
void NoeudJonction::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (selectionne_) 
    {
        glDisable(GL_COLOR_MATERIAL);
		glColor4d(1.0, 0.20, 0.0, 1.0);
        glEnable(GL_COLOR_MATERIAL);
	}

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();

    //cercleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudJonction::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudJonction::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
