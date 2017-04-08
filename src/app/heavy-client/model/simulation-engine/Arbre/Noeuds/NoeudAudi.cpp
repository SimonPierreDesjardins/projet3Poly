///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAudi.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-02-22
/// @version 1.0
///
/// @addtogroup log3900 LOG3900
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAudi.h"


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
/// @fn NoeudAudi::NoeudAudi(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAudi::NoeudAudi(uint32_t id, const std::string& typeNoeud, ArbreRendu* arbre)
	: NoeudRobot{ id, typeNoeud, arbre }
{
	//profil_->setModele("audi");
	positionDepart();

	std::shared_ptr<NoeudAbstrait> roueGauche2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite2 = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);


	ajouter(roueGauche2);
	ajouter(roueDroite2);

	roueGauche2_ = std::static_pointer_cast<NoeudRoues>(roueGauche2).get();
	roueDroite2_ = std::static_pointer_cast<NoeudRoues>(roueDroite2).get();

	roueGauche_->getPhysicsComponent().relativePosition = { 2.5,  -0.2, 0.7 };
	roueGauche_->getPhysicsComponent().scale = { 0.95f, 0.95f, 0.85f };
	roueGauche2_->getPhysicsComponent().relativePosition = { -3.1,  -0.2, 0.7 };
	roueGauche2_->getPhysicsComponent().scale = { 0.95f, 0.95f, 0.85f };
	roueDroite_->getPhysicsComponent().relativePosition = { 2.5, 0.2, 0.7 };
	roueDroite_->getPhysicsComponent().scale = { 0.95f, 0.95f, 0.85f };
	roueDroite2_->getPhysicsComponent().relativePosition = { -3.1,  0.2, 0.7 };
	roueDroite2_->getPhysicsComponent().scale = { 0.95f, 0.95f, 0.85f };

	roueGauche2_->setRightWheel(false);
	roueDroite2_->setRightWheel(true);

	positionnerRoues();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAudi::~NoeudAudi()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAudi::~NoeudAudi()
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
/// @fn void NoeudAudi::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::afficherConcret() const
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
		glColor4f(0.0862745121f, 0.407843143f, 0.701960802f, 1.0f);
		glEnable(GL_COLOR_MATERIAL);
	}

	glRotatef(physics_.rotation.z, 0.0, 0.0, 1.0);

	//controleurLumiere_->afficherLumiereSpotRobot();
	/*if (mode_ != PERSONALIZE && mode_ != PIECES)  //empêche lumiere spot et capteurs pour personnaliser
	{
		controleurLumiere_->afficherLumiereSpotGyro();
	}*/

	// Affichage du modèle.
	vbo_->dessiner();

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	/*
	// Débugage des capteurs de distance.
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
/// void NoeudAudi::suivreCamera()
///
/// Cette méthode positionne la caméra première personne en fonction de la 
/// position courante du audi
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::suivreCamera(vue::Vue* vue)
{

	if (vue->estPremierePersonne())
	{
		vue::Camera* camera = vue->obtenirCamera();
		glm::dvec3 positionRectangle = rectangleEnglobant_.obtenirPositionCentre();

		camera->assignerPosition(positionRectangle + glm::dvec3{ 0.0, 0.0, 4.0 });

		glm::dvec3 positionVise{ cos(physics_.rotation.z * PI / 180), 
			                     sin(physics_.rotation.z * PI / 180), 3.0 };
		camera->assignerPointVise(positionRectangle + positionVise);

		camera->assignerPosition(positionRectangle - glm::dvec3{ cos(physics_.rotation.z * PI / 180) * 3, 
			                     sin(physics_.rotation.z * PI / 180) * 3, -3.0 });
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAudi::positionnerRoues()
///
/// Cette fonctione permet de positionner les roues du robot par rapport à
/// son angle de rotation et sa position relative.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::positionnerRoues()
{
	roueGauche_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueGauche_->setVitesseCourante(vitesseCouranteGauche_);

	roueGauche2_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueGauche2_->setVitesseCourante(vitesseCouranteGauche_);

	roueDroite_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueDroite_->setVitesseCourante(vitesseCouranteDroite_);

	roueDroite2_->getPhysicsComponent().rotation.z = physics_.rotation.z;
	roueDroite2_->setVitesseCourante(vitesseCouranteDroite_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAudi::assignColors()
///
/// Cette fonctione permet dassigner les couleurs au robot et aux roues
///
/// @param[in] modele , alpha, red, green and blue
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::assignerCouleurs(int modele, int a, int r, int g, int b)
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
/// @fn void NoeudAudi::setCouleurDefault(int piece, bool default)
///
/// Cette fonction permet de remettre la couleur par default
///
/// @param[in] bool true si par default et int indiquant la piece
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::setCouleurDefault(int piece, bool default)
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
/// @fn void NoeudAudi::initialisationCouleurs(float* roues, float* modele)
///
/// Cette fonction permet dinitialiser les couleurs des roues et du modele
///
/// @param[in] float* de couleurs des roues et du modele
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudAudi::initialisationCouleurs(int* roues, int* modele)
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
