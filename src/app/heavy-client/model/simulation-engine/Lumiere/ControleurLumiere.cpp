///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.cpp
/// @author Simon-Pierre Desjardins
/// @date 2016-04-1
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Utilitaire.h"
#include "ControleurLumiere.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::ControleurLumiere()
///
/// Constructeur par défaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::ControleurLumiere()
{
	for (size_t i = 0; i < 3; i++)
	{
		positionSpotGyro_[i] = 0.0;
		positionSpotRobot_[i] = 0.0;
		orientationSpotGyro_[i] = 0.0;
	}
	positionSpotGyro_[4] = 1.0;
	positionSpotRobot_[4] = 1.0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::ControleurLumiere()
///
/// Destructeur par défaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::~ControleurLumiere()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereAmbianteGlobale()
///
/// Fonction qui affiche la lumiere ambiante globale selon un booléen
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereAmbianteGlobale() const
{
	if (lumiereAmbiante_)
	{
		glm::vec4 ambiant{ 0.5f, 0.5f, 0.5f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}
	else
	{
		glm::vec4 ambiant{ 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereDirectionnelle()
///
/// Fonction qui affiche la lumiere directionelle selon un booléen
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereDirectionnelle() const
{
	// Positionner la lumière.
	glm::vec4 position{ 1, 1, 1, 0 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumière
	if (lumiereDirectionnelle_)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereSpotGyro(glm::dvec3 positionRobot)
///
/// Fonction qui affiche la lumiere du spot gyrophare selon un booléen
///
/// @param[in] positionRobot : la position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereSpotGyro() const
{
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 0.0, 0.0, 1.0 };

	glm::vec4 position{0.0, 0.0, 5.0, 1.0};
	glLightfv(GL_LIGHT2, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT2, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumière
	if (lumiereSpotGyro_ && lumiereSpotRobot_)
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT2, GL_SPECULAR, glm::value_ptr(zeroContribution));

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 7.0);

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, orientationSpotGyro_);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereSpotGyro(glm::dvec3 positionRobot)
///
/// Fonction qui affiche la lumiere du spot robot selon un booléen
///
/// @param[in] positionRobot : la position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereSpotRobot() const
{
	// Positionner la lumière.
	glm::vec3 direction = { 0.2, 0, -1.0 };
	glm::vec4 position{0.0, 0.0, 15.0, 1.0};
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(direction));
    glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(position));

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 0.5, 0.5, 0.5, 1.0 };
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT1, GL_AMBIENT, glm::value_ptr(zeroContribution));

	// On sature les objets de lumière
	if (lumiereSpotRobot_)
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(zeroContribution));

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 55.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 12.0);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::animer(const glm::dvec3& positionRobot)
///
/// Fonction qui permet d'animer les différentes lumières
///
/// @param[in] positionRobot : la position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::animer(const glm::dvec3& positionRobot, float dt)
{
	positionSpotGyro_[0] = positionRobot.x;
	positionSpotGyro_[1] = positionRobot.y;
	positionSpotGyro_[2] = positionRobot.z + 5.0;
	positionSpotGyro_[3] = 1.0;

	if (!estEnPause_)
	{
		compteur_ += dt * 720;
		compteur_ = compteur_ % 360;
	}
	
	orientationSpotGyro_[0] = glm::cos(utilitaire::DEG_TO_RAD(compteur_));
	orientationSpotGyro_[1] = glm::sin(utilitaire::DEG_TO_RAD(compteur_));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereAmbianteGlobale(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumière ambiante
///
/// @param[in] estIllumine : Si vrai, la lumiere est affichée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereAmbianteGlobale(bool estIllumine)
{
	lumiereAmbiante_ = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereDirectionnelle(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumière directionelle
///
/// @param[in] estIllumine : Si vrai, la lumiere est affichée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereDirectionnelle(bool estIllumine)
{
	lumiereDirectionnelle_ = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereSpot(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumière du spot gyro
///
/// @param[in] estIllumine : Si vrai, la lumiere est affichée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereSpotGyro(bool estIllumine)
{
		lumiereSpotGyro_ = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereSpotRobot(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumière du spot robot
///
/// @param[in] estIllumine : Si vrai, la lumiere est affichée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereSpotRobot(bool estIllumine)
{
	lumiereSpotRobot_ = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::setEnPause(bool estEnPause)
///
/// Fonction qui assigne une valeur de vrai ou faux si le programme est en pause
///
/// @param[in] estEnPause : Si vrai, le programme est en pause
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::setEnPause(bool estEnPause)
{
	estEnPause_ = estEnPause;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////