///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTeleporteur.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTeleporteur.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTeleporteur::NoeudTeleporteur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTeleporteur::NoeudTeleporteur(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTeleporteur::animer(float dt)
///
/// Cette fonction permet d'appeler la mise a jour lors de l'animation.
///
/// param[in] dt : intervalle de temps en float
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudTeleporteur::animer(float dt)
{
    mettreAJourFormeEnglobante();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de faire la mise à jour de la forme englobante pour le teleporteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTeleporteur::mettreAJourFormeEnglobante()
{
    double hauteur = glm::abs(boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x);
    double largeur = glm::abs(boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y);
    double rayon = hauteur > largeur ? hauteur : largeur;
    rayon /= 2.0;
    cercleEnglobant_.mettreAJour(positionCourante_, rayon * facteurMiseAEchelle_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTeleporteur::~NoeudTeleporteur()
///
/// Ce destructeur désallouee la liste d'affichage du teleporteur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTeleporteur::~NoeudTeleporteur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le teleporteur.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante()
{
    return &cercleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le teleporteur.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const CercleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante() const
{
    return &cercleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTeleporteur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTeleporteur::afficherConcret() const
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
		glColor4f(0.0862745121f, 0.407843143f, 0.701960802f, 1.0f);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotated(angleRotation_, 0, 0, 1);
	// Effectuer la mise à échelle.
	glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, facteurMiseAEchelle_);
	
	// Affichage du modèle.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    //cercleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTeleporteur::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTeleporteur::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////