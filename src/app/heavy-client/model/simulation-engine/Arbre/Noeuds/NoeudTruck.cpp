///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTruck.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
/// @version 1.0
///
/// @addtogroup log3900 LOG3900
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTruck.h"


#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "NoeudRoues.h"
#include "NoeudPoteau.h"
#include "NoeudMur.h"
#include "NoeudTable.h"

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include "RectangleEnglobant.h"

#include "EnginSon.h"
#include "Camera.h"



#define PI 3.14159265

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTruck::NoeudTruck(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par dï¿½faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTruck::NoeudTruck(uint32_t id, const std::string& typeNoeud)
	: NoeudRobot{ id, typeNoeud }
{
	type_ = TRUCK_ENTITY;
	profil_->setModele("truck");
	positionDepart();

	std::shared_ptr<NoeudAbstrait> roueGauche2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);


	ajouter(roueGauche2);
	ajouter(roueDroite2);

	roueGauche2_ = std::static_pointer_cast<NoeudRoues>(roueGauche2).get();
	roueDroite2_ = std::static_pointer_cast<NoeudRoues>(roueDroite2).get();
	roueDroite_->assignerPositionRelative({ 1.5, 0.5, 1.0 });
	roueGauche_->assignerPositionRelative({ 1.5, -0.47, 1.0 });
	roueGauche2_->assignerPositionRelative({ -2.2, -0.47, 1.0});
	roueDroite2_->assignerPositionRelative({ -2.2, 0.5, 1.0 });

	roueGauche2_->setRightWheel(false);
	roueDroite2_->setRightWheel(true);

	positionnerRoues();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTruck::~NoeudTruck()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTruck::~NoeudTruck()
{
	glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));
	glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0, 0.0, 0.0, 0.0)));

	if ((table_ != nullptr) && (roueGauche_ != nullptr))
		effacer(roueGauche_);
	if ((table_ != nullptr) && (roueDroite_ != nullptr))
		effacer(roueDroite_);
	if ((table_ != nullptr) && (roueGauche2_ != nullptr))
		effacer(roueGauche2_);
	if ((table_ != nullptr) && (roueDroite2_ != nullptr))
		effacer(roueDroite2_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTruck::afficherConcret() const
///
/// Cette fonction effectue le vï¿½ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();



	if (!estCouleurDefaut_)
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(couleur_[1], couleur_[2], couleur_[3], couleur_[0]);
		glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDisable(GL_COLOR_MATERIAL);
		glColor4f(0.980392158f, 0.721568644f, 0.0235294122f, 1.0f);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

	controleurLumiere_->afficherLumiereSpotRobot();
	if (mode_ != PERSONALIZE && mode_ != PIECES && mode_ != COURSE)  //empêche lumiere spot et capteurs pour personnaliser
	{
		controleurLumiere_->afficherLumiereSpotGyro();
	}

	// Affichage du modï¿½le.
	vbo_->dessiner();

	// Appel ï¿½ la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	if (mode_ != PERSONALIZE && mode_ != PIECES && mode_ != COURSE)
	{
		if (profil_->obtenirOptionDebogage(DEBOGAGE_CAPTEURS))
		{
			// Débugage des capteurs de distance.
			for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
			{
				capteursDistance_->at(i).afficher();
			}
		}
	}

	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// void NoeudTruck::suivreCamera()
///
/// Cette méthode positionne la caméra première personne en fonction de la 
/// position courante du truck
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::suivreCamera()
{
	vue::Vue* vue = FacadeModele::obtenirInstance()->obtenirVue();

	if (vue->estPremierePersonne())
	{
		vue::Camera* camera = vue->obtenirCamera();
		glm::dvec3 positionRectangle = rectangleEnglobant_.obtenirPositionCentre();

		camera->assignerPosition(positionRectangle + glm::dvec3{ 0.0, 0.0, 4.0 });

		glm::dvec3 positionVise{ cos(angleRotation_* PI / 180), sin(angleRotation_* PI / 180), 5.0 };
		camera->assignerPointVise(positionRectangle + positionVise);

		camera->assignerPosition(positionRectangle - glm::dvec3{ cos(angleRotation_* PI / 180) * 4, sin(angleRotation_* PI / 180) * 4, -5.0 }); 
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeNoeudTruckudF1::positionnerRoues()
///
/// Cette fonctione permet de positionner les roues du robot par rapport ï¿½
/// son angle de rotation et sa position relative.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::positionnerRoues()
{
	roueGauche_->assignerAngleRotation(angleRotation_);
	roueGauche2_->assignerAngleRotation(angleRotation_);

	roueGauche_->setVitesseCourante(vitesseCouranteGauche_);
	roueGauche2_->setVitesseCourante(vitesseCouranteGauche_);

	roueDroite_->assignerAngleRotation(angleRotation_);
	roueDroite2_->assignerAngleRotation(angleRotation_);

	roueDroite_->setVitesseCourante(vitesseCouranteDroite_);
	roueDroite2_->setVitesseCourante(vitesseCouranteDroite_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTruck::assignColors()
///
/// Cette fonctione permet dassigner les couleurs au robot et aux roues
///
/// @param[in] modele , alpha, red, green and blue
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::assignerCouleurs(int modele, int a, int r, int g, int b)
{
	if (modele == WHEELS)
	{
		roueDroite_->assignerCouleurs(modele, a, r, g, b);
		roueGauche_->assignerCouleurs(modele, a, r, g, b);
		roueDroite2_->assignerCouleurs(modele, a, r, g, b);
		roueGauche2_->assignerCouleurs(modele, a, r, g, b);
	}
	else if (modele == BODY)
	{
		couleur_[0] = (float)a / (float)255;
		couleur_[1] = (float)r / (float)255;
		couleur_[2] = (float)g / (float)255;
		couleur_[3] = (float)b / (float)255;
		estCouleurDefaut_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTruck::setCouleurDefault(int piece, bool default)
///
/// Cette fonction permet de remettre la couleur par default
///
/// @param[in] bool true si par default et int indiquant la piece
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::setCouleurDefault(int piece, bool default)
{
	if (piece == WHEELS)
	{
		roueDroite_->setCouleurDefault(piece, default);
		roueGauche_->setCouleurDefault(piece, default);
		roueDroite2_->setCouleurDefault(piece, default);
		roueGauche2_->setCouleurDefault(piece, default);
	}
	else if (piece == BODY)
	{
		estCouleurDefaut_ = default;
	}

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
