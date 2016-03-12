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

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE = { 3.47, 1.85, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE = { 4.2695, 0.1, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE = { 3.60, -1.80, 5.0 };

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
    
	NoeudAbstrait* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
    NoeudAbstrait* table = arbre->chercher(ArbreRenduINF2990::NOM_TABLE);
	NoeudAbstrait* depart = table->chercher(ArbreRenduINF2990::NOM_DEPART);
    
    visiteur_ = make_unique<VisiteurDetectionRobot>();

	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();

    capteursDistance_[CAPTEUR_DISTANCE_DROITE] = CapteurDistance(POSITION_CAPTEUR_DISTANCE_DROITE, angleRotation_ - 45.0);
    capteursDistance_[CAPTEUR_DISTANCE_CENTRE] = CapteurDistance(POSITION_CAPTEUR_DISTANCE_CENTRE, angleRotation_);
    capteursDistance_[CAPTEUR_DISTANCE_GAUCHE] = CapteurDistance(POSITION_CAPTEUR_DISTANCE_GAUCHE, angleRotation_ + 45.0);
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

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

    // Débugage des capteurs de distance.
    suiveurLigne_.afficher();

    // Débugage des capteurs de distance.
    for (int i = 0; i < N_CAPTEUR_DISTANCE; i++)
    {
        capteursDistance_[i].afficher();
    }

    // Debugage de la boite englobante.
    afficherFormeEnglobante();

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
    mettreAJourCapteurs();
    mettreAJourPosition(dt);
    mettreAJourRectangleEnglobant();
	//Calcul de la résultante de la vitesse relative
	float diffD = vitesseDroite_ - vitesseCouranteDroite_, diffG = vitesseGauche_ - vitesseCouranteGauche_;
	if (diffD < 0)
	{
		diffD = -diffD;
	}
	if (diffG < 0)
	{
		diffG = -diffG;
	}
	if (diffD < (acceleration_ * dt) && vitesseDroite_ == 0)
	{
		vitesseCouranteDroite_ = 0;
	}
	else
	{
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
	}
	if (diffG < (acceleration_*dt) && vitesseGauche_ == 0)
	{
		vitesseCouranteGauche_ = 0;
	}
	else
	{
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
/// @fn void NoeudRobot::obtenirVitesseDroiteCourante() const
///
/// Cette fonction retourne la vitesse du moteur de droite
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de droite.
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::obtenirVitesseDroiteCourante() const
{
	return vitesseCouranteDroite_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::obtenirVitesseGaucheCourante() const
///
/// Cette fonction retourne la vitesse du moteur de gauche
///
/// @param[in] Aucune.
///
/// @return float : vitesse de rotation du moteur de gauche.
///
////////////////////////////////////////////////////////////////////////
float NoeudRobot::obtenirVitesseGaucheCourante() const
{
	return vitesseCouranteGauche_;
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
void NoeudRobot::assignerVitesseDroiteCourante(float vitesse)
{
	vitesseCouranteDroite_ = vitesse;
}
void NoeudRobot::assignerVitesseGaucheCourante(float vitesse)
{
	vitesseCouranteGauche_ = vitesse;
}


CapteurDistance* NoeudRobot::obtenirCapteurDistance(PositionCapteurDistance position)
{
    CapteurDistance* capteur = nullptr;
    if (position < N_CAPTEUR_DISTANCE)
    {
        capteur = &capteursDistance_[position];
    }
    return capteur;
}


void NoeudRobot::afficherFormeEnglobante() const
{
    double hauteur = rectangleEnglobant_.obtenirHauteur();
    double largeur = rectangleEnglobant_.obtenirLargeur();
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3d(largeur / 2.0 + 1.35, hauteur / 2.0, 5.0);
	glVertex3d(-largeur / 2.0 + 1.35, hauteur / 2.0, 5.0);
	glVertex3d(-largeur / 2.0 + 1.35, -hauteur / 2.0, 5.0);
	glVertex3d(largeur / 2.0 + 1.35, -hauteur / 2.0, 5.0);
	glEnd();
    glPopMatrix();
}

void NoeudRobot::mettreAJourCapteurs()
{
	suiveurLigne_.mettreAJourCapteurs(positionRelative_, angleRotation_);
    for (int i = 0; i < N_CAPTEUR_DISTANCE; i++)
    {
        capteursDistance_[i].mettreAJour(positionRelative_, angleRotation_);
    }
}

void NoeudRobot::mettreAJourPosition(const float& dt)
{

}

void NoeudRobot::mettreAJourRectangleEnglobant()
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
