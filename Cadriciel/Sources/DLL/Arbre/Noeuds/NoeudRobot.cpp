///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.cpp
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRobot.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::~NoeudRobot()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::~NoeudRobot()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	glColor4f(0.0, 0.0, 0.0, 1.0);

	bool rotater = false;
	if (!rotater)
	{
		glRotatef(90, 0.0, 0.0, 1.0);
		rotater = true;
	}

	float angle = angleRotation_;
	glRotatef(angle, 0.0, 0.0, 1.0);
	
	// Sauvegarde de la matrice.
	glPushMatrix();
	
	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse déléguer
/// sa tâche à la méthode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour déléguer au concret après)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

void NoeudRobot::animer(float dt)
{
	std::cout << dt << std::endl;

	/*positionRelative_.x += (vitesseDroite_ * dt)*cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += (vitesseDroite_ * dt)*sin(utilitaire::DEG_TO_RAD(angleRotation_));
	angleRotation_ += vitesseRotation_*dt;*/
	float relativeGaucheDroite = vitesseGauche_ + vitesseDroite_;
	//if (relativeGaucheDroite < 0)
	//{ 
	//	relativeGaucheDroite = -relativeGaucheDroite;
	//}
	vitesseRotation_ = vitesseDroite_ - vitesseGauche_;
	angleRotation_ += dt*vitesseRotation_;
	positionRelative_.x += dt*relativeGaucheDroite/10*cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += dt*relativeGaucheDroite/10*sin(utilitaire::DEG_TO_RAD(angleRotation_));
	


}

float NoeudRobot::obtenirVitesseDroite() const
{
	return vitesseDroite_;
}

float NoeudRobot::obtenirVitesseGauche() const
{
	return vitesseGauche_;
}

void NoeudRobot::assignerVitesseDroite(float vitesse)
{
	vitesseDroite_ = vitesse;
}

void NoeudRobot::assignerVitesseGauche(float vitesse)
{
	vitesseGauche_ = vitesse;
}

void NoeudRobot::assignerVitesseRotation(float vitesse)
{
	vitesseRotation_ = vitesse;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
