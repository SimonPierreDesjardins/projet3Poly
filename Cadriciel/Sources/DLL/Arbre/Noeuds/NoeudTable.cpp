///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"
#include "VisiteurAbstrait.h"

#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn RectangleEnglobant* NoeudTable::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour la table.
///
/// @return Pointeur  sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////

RectangleEnglobant* NoeudTable::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const RectangleEnglobant* NoeudTable::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour la table.
///
/// @return Pointeur const sur un rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
const RectangleEnglobant* NoeudTable::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de mettre a jour la forme englobante de la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;

    double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;

    glm::dvec3 positionRectangle = { positionCourante_.x + positionBoiteX, positionCourante_.y + positionBoiteY, 0.0 };
    rectangleEnglobant_.mettreAJour(positionRectangle, angleRotation_, hauteur, largeur);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	glColor4f(1, 1, 1, 1);
    glTranslated(0.0, 0.0, -2.0);
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();

    //rectangleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
