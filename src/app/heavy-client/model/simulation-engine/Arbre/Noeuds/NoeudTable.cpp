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
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(uint32_t id, const std::string& typeNoeud)
	: NoeudComposite{ id, typeNoeud }
{
	type_ = TABLE_ENTITY;
	physics_.scale = { 2, 2, 1 }; //A changer si on veut modifier la taille de la table, il faudra alors faire fromJson sur la table dans le chargement de la carte.
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
	largeur *= physics_.scale.x;
	hauteur *= physics_.scale.y;

    /*double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;


	/// Demander a oli pourquoi faire ca au lieu de prendre la position courante


    glm::dvec3 positionRectangle = { physics_.absolutePosition.x + positionBoiteX, physics_.absolutePosition.y + positionBoiteY, 0.0 };
    */
	rectangleEnglobant_.mettreAJour(physics_.absolutePosition, physics_.rotation.z, hauteur, largeur);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du mod�le.
	//glColor4f(1, 1, 1, 1);
	glScaled(physics_.scale.x, physics_.scale.y, 1.0);
	vbo_->dessiner();


	// Restauration de la matrice.
	glPopMatrix();


    //rectangleEnglobant_.afficher(physics_.absolutePosition);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
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
