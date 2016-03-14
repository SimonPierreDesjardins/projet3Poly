///////////////////////////////////////////////////////////////////////////
/// @file NoeudRouest.h
/// @author Frédéric Grégoire
/// @date 2016-03-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudRoues.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"
#include "FacadeModele.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoues::NoeudRoues(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRoues::NoeudRoues(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* depart = table->chercher(0);
	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();

	parent_ = table->chercher(ArbreRenduINF2990::NOM_ROBOT);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRoues::~NoeudRoues()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRoues::~NoeudRoues()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRoues::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRoues::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}