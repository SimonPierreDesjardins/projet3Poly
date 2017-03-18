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

#include "FacadeModele.h"

#define coinMinX -48
#define coinMaxX  48
#define coinMinY -24
#define coinMaxY  24


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTeleporteur::NoeudTeleporteur(uint32_t id, const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud et le id du noeud
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTeleporteur::NoeudTeleporteur(uint32_t id, const std::string& typeNoeud)
	: NoeudAbstrait{ id, typeNoeud }
{
	type_ = TELEPORT_ENTITY;
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
	double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
	double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
	rectangleEnglobant_.mettreAJour(positionCourante_, angleRotation_, hauteur, largeur);

	hauteur = glm::abs(boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x);
	largeur = glm::abs(boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y);
	double rayon = hauteur > largeur ? hauteur : largeur;
	rayon = 11;
	cercleEnglobant_.mettreAJour(positionCourante_, rayon);
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
	if (teleporteur_ != nullptr && !teleporteur_->estSelectionne())
	{
		teleporteur_->assignerTeleporteur(nullptr);
		teleporteur_->assignerSelection(true); //permet de supprimer le noeud de la meme paire
		
	}
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
RectangleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
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
const RectangleEnglobant* NoeudTeleporteur::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant* NoeudTeleporteur::obtenirCercleEnglobante()
///
/// Cette fonction permet d'obtenir le cercle englobant pour le teleporteur.
///
/// @return Pointeur sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant* NoeudTeleporteur::obtenirCercleEnglobante()
{
	return &cercleEnglobant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const CercleEnglobant* NoeudTeleporteur::obtenirCercleEnglobante() const
///
/// Cette fonction permet d'obtenir le cercle englobant pour le teleporteur.
///
/// @return Pointeur const  sur un cercle englobant.
///
////////////////////////////////////////////////////////////////////////
const CercleEnglobant* NoeudTeleporteur::obtenirCercleEnglobante() const
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
	
	// Affichage du modèle.
	vbo_->dessiner();

    

	// Restauration de la matrice.
	glPopMatrix();

    //rectangleEnglobant_.afficher(positionCourante_);
	cercleEnglobant_.afficher(positionCourante_);
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTeleporteur::setId(int id)
///
/// Cette fonction attribue un id au téléporteur
///
/// @param[in] id: numéro du téléporteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTeleporteur::setId(int id)
{
	idTeleporteur_ = id;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int NoeudTeleporteur::getId()
///
/// Cette fonction retourne le id du téléporteur
///
/// @param[in] aucun
///
/// @return id du téléporteur
///
////////////////////////////////////////////////////////////////////////
int NoeudTeleporteur::getId()
{
	return idTeleporteur_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTeleporteur::assignerTeleporteur(NoeudAbstrait* teleporteur)
///
/// Cette fonction assigne le teleporteur lie a celui ci
///
/// @param[in] NoeudAbstrait* teleporteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTeleporteur::assignerTeleporteur(NoeudAbstrait* teleporteur)
{
	teleporteur_ = (NoeudTeleporteur*)teleporteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTeleporteur* NoeudTeleporteur::obtenirProchainTeleporteur()
///
/// Cette fonction retourne teleporteur associe a celui-ci
///
/// @param[in] aucun
///
/// @return le noeud teleporteur associe a celui-ci
///
////////////////////////////////////////////////////////////////////////
NoeudTeleporteur* NoeudTeleporteur::obtenirProchainTeleporteur()
{
	return teleporteur_;
}


bool NoeudTeleporteur::collisionTeleporteur()
{
	if (!this->obtenirCercleEnglobante()->calculerEstDansLimites(coinMinX, coinMaxX, coinMinY, coinMaxY))
	{
		return true;
	}
	for (unsigned int i = 0; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->obtenirNombreEnfants() -1; i++) //on vérifie le cercle englobant des autres téléporteurs afin d'éviter d'avoir un téléporter dans ceux-ci
	{
		if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->chercher(i) != this)
		{
			if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->chercher(i)->obtenirNom() == "teleporteur" && ((NoeudTeleporteur*)FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->chercher(i))->obtenirCercleEnglobante()->calculerIntersection(cercleEnglobant_))
			{
				return true;
			}
			else if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->chercher(i)->obtenirFormeEnglobante()->calculerIntersection(cercleEnglobant_))
			{
				return true;
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////