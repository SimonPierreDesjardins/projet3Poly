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
#include "ArbreRenduINF2990.h"

#include "RectangleEnglobant.h"

#include "EnginSon.h"




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
NoeudTruck::NoeudTruck(uint32_t id, const std::string& typeNoeud, ArbreRendu* arbre)
	: NoeudRobot{ id, typeNoeud, arbre}
{
	type_ = TRUCK_ENTITY;
	positionDepart();

	std::shared_ptr<NoeudAbstrait> roueGauche2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);

	ajouter(roueGauche2);
	ajouter(roueDroite2);

	roueGauche2_ = std::static_pointer_cast<NoeudRoues>(roueGauche2).get();
	roueDroite2_ = std::static_pointer_cast<NoeudRoues>(roueDroite2).get();

		
	roueGauche_->getPhysicsComponent().relativePosition = { 1.5, -0.47, 1.0 };
	roueGauche_->getPhysicsComponent().scale = { 1.25f, 1.25f, 1.25f };
	roueGauche2_->getPhysicsComponent().relativePosition = { -2.2, -0.47, 1.0 };
	roueGauche2_->getPhysicsComponent().scale = { 1.25f, 1.25f, 1.25f };
	roueDroite_->getPhysicsComponent().relativePosition = { 1.5, 0.5, 1.0 };
	roueDroite_->getPhysicsComponent().scale = { 1.25f, 1.25f, 1.25f };
	roueDroite2_->getPhysicsComponent().relativePosition = { -2.2, 0.5, 1.0 };
	roueDroite2_->getPhysicsComponent().scale = { 1.25f, 1.25f, 1.25f };
	

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

	glRotatef(physics_.rotation.z, 0.0, 0.0, 1.0);


	//controleurLumiere_->afficherLumiereSpotRobot();
	/*if (mode_ != PERSONALIZE && mode_ != PIECES)  //empêche lumiere spot et capteurs pour personnaliser

	{
		controleurLumiere_->afficherLumiereSpotGyro();
	}*/

	// Affichage du modï¿½le.
	vbo_->dessiner();

	// Appel ï¿½ la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();


	/*
	if (mode_ != PERSONALIZE && mode_ != PIECES)

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
	*/

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
void NoeudTruck::suivreCamera(vue::Vue* vue)
{

	if (vue->estPremierePersonne())
	{
		vue::Camera* camera = vue->obtenirCamera();
		glm::dvec3 positionRectangle = rectangleEnglobant_.obtenirPositionCentre();

		camera->assignerPosition(positionRectangle + glm::dvec3{ 0.0, 0.0, 4.0 });

		glm::dvec3 positionVise{ cos(physics_.rotation.z * PI / 180), sin(physics_.rotation.z * PI / 180), 5.0 };
		camera->assignerPointVise(positionRectangle + positionVise);

		camera->assignerPosition(positionRectangle - glm::dvec3{ cos(physics_.rotation.z * PI / 180) * 4, sin(physics_.rotation.z * PI / 180) * 4, -5.0 }); 
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
	double vLeft = leftEngine.getTangentialVelocity();
	double vRight = rightEngine.getTangentialVelocity();

	roueGauche_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueGauche_->setVitesseCourante(vLeft);

	roueGauche2_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueGauche2_->setVitesseCourante(vLeft);

	roueDroite_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueDroite_->setVitesseCourante(vRight);

	roueDroite2_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueDroite2_->setVitesseCourante(vRight);
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTruck::initialisationCouleurs(float* roues, float* modele)
///
/// Cette fonction permet dinitialiser les couleurs des roues et du modele
///
/// @param[in] float* de couleurs des roues et du modele
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTruck::initialisationCouleurs(int* roues, int* modele)
{
	couleur_[0] = (float)modele[0] / (float)255;
	couleur_[1] = (float)modele[1] / (float)255;
	couleur_[2] = (float)modele[2] / (float)255;
	couleur_[3] = (float)modele[3] / (float)255;
	roueDroite_->initialisationCouleurs(roues);
	roueDroite2_->initialisationCouleurs(roues);
	roueGauche_->initialisationCouleurs(roues);
	roueGauche2_->initialisationCouleurs(roues);
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
