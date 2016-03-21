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
/// @fn RectangleEnglobant* NoeudDepart::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le noeud de depart.
///
/// @return Pointeur sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
RectangleEnglobant* NoeudDepart::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const RectangleEnglobant* NoeudDepart::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le noeud de depart.
///
/// @return Pointeur const sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudDepart::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
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

    //rectangleEnglobant_.afficher(positionCourante_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::animer(float dt)
{
    mettreAJourFormeEnglobante();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de mettre a jour la forme englobante du noeud de depart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;

    double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;
    glm::dvec3 positionBoite = { positionBoiteX, positionBoiteY, 0.0 };

    utilitaire::calculerPositionApresRotation(positionBoite, positionBoite, angleRotation_);
    glm::dvec3 positionRectangle = { positionCourante_.x + positionBoite.x, positionCourante_.y + positionBoite.y, 0.0 };

    rectangleEnglobant_.mettreAJour(positionRectangle, angleRotation_, hauteur, largeur);
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
