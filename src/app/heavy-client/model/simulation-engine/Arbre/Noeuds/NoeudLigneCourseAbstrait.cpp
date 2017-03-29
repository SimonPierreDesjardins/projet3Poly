///////////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneCourseAbstrait.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudLigneCourseAbstrait.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

#include "FacadeModele.h"




////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneCourseAbstrait::NoeudLigneCourseAbstrait(uint32_t id, const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud et le id du noeud
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneCourseAbstrait::NoeudLigneCourseAbstrait(uint32_t id, const std::string& typeNoeud)
	: NoeudComposite{ id, typeNoeud }
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneCourseAbstrait::~NoeudLigneCourseAbstrait()
///
/// Ce destructeur désallouee la liste d'affichage du ligne course.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneCourseAbstrait::~NoeudLigneCourseAbstrait()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneCourseAbstrait::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise à jour de la forme englobante pour la ligne de course.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneCourseAbstrait::mettreAJourFormeEnglobante()
{
	double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
	double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
	rectangleEnglobant_.mettreAJour(positionCourante_, angleRotation_, hauteur, largeur);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant* NoeudLigneCourseAbstrait::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le ligne course.
///
/// @return Pointeur const  sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant* NoeudLigneCourseAbstrait::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const RectangleEnglobant* NoeudLigneCourseAbstrait::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le ligne course.
///
/// @return Pointeur const  sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudLigneCourseAbstrait::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneCourseAbstrait::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneCourseAbstrait::afficherConcret() const
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
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotated(angleRotation_, 0, 0, 1);
	
	// Affichage du modèle.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    rectangleEnglobant_.afficher(positionCourante_);
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudLigneCourseAbstrait::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudLigneCourseAbstrait::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////