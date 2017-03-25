///////////////////////////////////////////////////////////////////////////////
/// @file NoeudSegment.cpp
/// @author Olivier St-Amour
/// @date 2016-02-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "NoeudSegment.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"
#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
//
// @fn NoeudSegment::NoeudSegment(uint32_t id, const std::string& typeNoeud)
//
// Ce constructeur ne fait qu'appeler la version de la classe et base
// et donner des valeurs par défaut aux variables membres.
//
// @param[in] id : L'identifiant du noeud.
// @param[in] typeNoeud : Le type du noeud.
//
// @return Aucune (constructeur).
//
////////////////////////////////////////////////////////////////////////
NoeudSegment::NoeudSegment(uint32_t id, const std::string& typeNoeud)
	: NoeudAbstrait(id, typeNoeud)
{
	type_ = SEGMENT_ENTITY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegment::~NoeudSegment()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegment::~NoeudSegment()
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le segment.
///
/// @return Pointeur sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le segment.
///
/// @return Pointeur const  sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::animer(float dt)
{
    mettreAJourFormeEnglobante();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise à jour de la forme englobante pour le segment.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
    largeur *= facteurMiseAEchelle_;
    rectangleEnglobant_.mettreAJour(positionCourante_, angleRotation_, hauteur, largeur);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (selectionne_)
    {
        glDisable(GL_COLOR_MATERIAL);
		glColor4f(selectionColor_.x, selectionColor_.y, selectionColor_.z, selectionColor_.w);
        glEnable(GL_COLOR_MATERIAL);
	}

	//Ajustement du mur avant la création
	glRotated(angleRotation_, 0, 0, 1);
	glScaled(facteurMiseAEchelle_, 1, 1);

	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////