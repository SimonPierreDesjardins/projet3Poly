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
#include "FacadeModele.h"

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
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* depart = table->chercher(0);
	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();
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


	float angle = angleRotation_;

	glRotatef(angle, 0.0, 0.0, 1.0);
	
	//Debugage du suiveur de ligne.
	// Capteur optique gauche.
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslated(4.8523, 0.995, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(-0.1, -0.1, 5.0);
	glVertex3d(0.1, -0.1, 5.0);
	glVertex3d(0.1, 0.1, 5.0);
	glVertex3d(-0.1, 0.1, 5.0);
	glEnd();
	glPopMatrix();
	
	// Capteur optique centre.
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslated(4.8523, 0.07, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(-0.1, -0.1, 5.0);
	glVertex3d(0.1, -0.1, 5.0);
	glVertex3d(0.1, 0.1, 5.0);
	glVertex3d(-0.1, 0.1, 5.0);
	glEnd();
	glPopMatrix();

	// Capteur optique droite.
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslated(4.8523, -0.853, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(-0.1, -0.1, 5.0);
	glVertex3d(0.1, -0.1, 5.0);
	glVertex3d(0.1, 0.1, 5.0);
	glVertex3d(-0.1, 0.1, 5.0);
	glEnd();
	glPopMatrix();

	glColor4f(0.0, 0.0, 0.0, 1.0);

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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::animer(float dt)
///
/// Cette fonction calcule les changements effectuer aux attributs du robot selon les
/// vitesses des moteurs de droite et de gauche
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::animer(float dt)
{
	//Calcul de la résultante de la vitesse relative
	if (vitesseDroite_ < 0)
	{
		if (vitesseCouranteDroite_ > vitesseDroite_)
		{
			vitesseCouranteDroite_ -= acceleration_ * dt;
		}
		else// if (vitesseCouranteDroite_ < vitesseDroite_)
		{
			//vitesseCouranteDroite_ = 0;
			vitesseCouranteDroite_ += acceleration_ * dt;
		}
	}
	else
	{
		if (vitesseCouranteDroite_ < vitesseDroite_)
		{
			vitesseCouranteDroite_ += acceleration_ * dt;
		}
		else// if (vitesseCouranteDroite_ > vitesseDroite_)
		{
			//vitesseCouranteDroite_ = 0;
			vitesseCouranteDroite_ -= acceleration_ * dt;
		}
	}
	if (vitesseGauche_ < 0)
	{
		if (vitesseCouranteGauche_ > vitesseGauche_)
		{
			vitesseCouranteGauche_ -= acceleration_ * dt;
		}
		else// if (vitesseCouranteGauche_ < vitesseGauche_)
		{
			//vitesseCouranteGauche_ = 0;
			vitesseCouranteGauche_ += acceleration_ * dt;
		}
	}
	else
	{
		if (vitesseCouranteGauche_ < vitesseGauche_)
		{
			vitesseCouranteGauche_ += acceleration_ * dt;
		}
		else// if (vitesseCouranteGauche_ > vitesseGauche_)
		{
			//vitesseCouranteGauche_ = 0;
			vitesseCouranteGauche_ -= acceleration_ * dt;
		}
	}
	float relativeGaucheDroite = vitesseCouranteGauche_ + vitesseCouranteDroite_;

	//Calcul de la différence entre les vitesses de gauche et droite
	vitesseRotation_ = vitesseCouranteDroite_ - vitesseCouranteGauche_;

	//Calculs des nouvelles positions et du nouvel angle
	angleRotation_ += dt * vitesseRotation_;
	positionRelative_.x += dt * relativeGaucheDroite / 10 * cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += dt * relativeGaucheDroite / 10 * sin(utilitaire::DEG_TO_RAD(angleRotation_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirVitesseDroite() const
///
/// Cette fonction retourne la vitesse du moteur de droite
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de droite.
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::obtenirVitesseDroite() const
{
	return vitesseDroite_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirVitesseGauche() const
///
/// Cette fonction retourne la vitesse du moteur de gauche
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de gauche.
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::obtenirVitesseGauche() const
{
	return vitesseGauche_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseDroite() const
///
/// Cette modifie la vitesse de rotation du moteur de droite.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::assignerVitesseDroite(float vitesse)
{
	vitesseDroite_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseGauche() const
///
/// Cette modifie la vitesse de rotation du moteur de gauche.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner au moteur de gauche.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::assignerVitesseGauche(float vitesse)
{
	vitesseGauche_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::assignerVitesseRotation() const
///
/// Cette modifie la vitesse de rotation angulaire.
///
/// @param[in] vitesse : vitesse que l'on souhaite assigner à l'attribut vitesseRotation_.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::assignerVitesseRotation(float vitesse)
{
	vitesseRotation_ = vitesse;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
