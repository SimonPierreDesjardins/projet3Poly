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
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	angleRotation_ = 0.0;
	facteurMiseAEchelle_ = 1.0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
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
/// Cette fonction permet de faire la mise à jour de la forme englobante pour le mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
    largeur *= facteurMiseAEchelle_;
    rectangleEnglobant_.mettreAJour(positionCourante_, angleRotation_, hauteur, largeur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne()) {
		glColor4d(1.0, 0.2, 0.0, 1.0);
	}
	else {
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}

	//Ajustement du mur avant la création
	glRotated(angleRotation_, 0, 0, 1);
	
	glScaled(facteurMiseAEchelle_, 1.0, 1.0);

	// Affichage du modèle.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();

    //rectangleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
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

