///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2016-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
//
// Ce constructeur ne fait qu'appeler la version de la classe et base
// et donner des valeurs par d�faut aux variables membres.
//
// @param[in] id : L'identifiant du noeud.
// @param[in] typeNoeud : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(uint32_t id, const std::string& typeNoeud)
	: NoeudAbstrait{ id, typeNoeud }
{
	type_ = WALL_ENTITY;
	physics_.rotation.z = 0.0;
	physics_.scale.x = 1.0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant* NoeudMur::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante d'un mur.
///
/// @return Pointeur sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant* NoeudMur::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const RectangleEnglobant* NoeudMur::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante d'un mur.
///
/// @return Pointeur sur un rectangle englobant const.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudMur::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::animer(float dt)
{
    mettreAJourFormeEnglobante();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise � jour de la forme englobante pour le mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::mettreAJourFormeEnglobante()
{

	physics_.absolutePosition = physics_.relativePosition;

    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
    largeur *= physics_.scale.x;
	rectangleEnglobant_.mettreAJour({ physics_.absolutePosition.x, 
		                              physics_.absolutePosition.y, 
		                              physics_.absolutePosition.z }, 
		                              physics_.rotation.z, hauteur, largeur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne()) 
    {
        glDisable(GL_COLOR_MATERIAL);
		glColor4f(selectionColor_.x, selectionColor_.y, selectionColor_.z, selectionColor_.w);
        glEnable(GL_COLOR_MATERIAL);
	}

	//Ajustement du mur avant la cr�ation
	glRotated(physics_.rotation.z, 0, 0, 1);
	
	glScaled(physics_.scale.x, 1.0, 1.0);

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();

    //rectangleEnglobant_.afficher(physics_.absolutePosition);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

