///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.cpp
/// @author Simon-Pierre Desjardins
/// @date 2016-04-1
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "ControleurLumiere.h"
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::ControleurLumiere()
///
/// Constructeur par d�faut
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
/// Destructeur par d�faut
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
/// Fonction qui affiche la lumiere ambiante globale selon un bool�en
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereAmbianteGlobale()
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
/// Fonction qui affiche la lumiere directionelle selon un bool�en
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereDirectionnelle()
{
	// Positionner la lumi�re.
	glm::vec4 position{ 1, 1, 1, 0 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumi�re
	if (lumiereDirectionnelle_)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereSpotGyro(glm::dvec3 positionRobot)
///
/// Fonction qui affiche la lumiere du spot gyrophare selon un bool�en
///
/// @param[in] positionRobot : la position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereSpotGyro()
{
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT2, GL_POSITION, positionSpotGyro_);
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT2, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumi�re
	if (lumiereSpotGyro_)
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT2, GL_SPECULAR, glm::value_ptr(zeroContribution));

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, orientationSpotGyro_);
	glLightfv(GL_LIGHT2, GL_POSITION, positionSpotGyro_);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereSpotGyro(glm::dvec3 positionRobot)
///
/// Fonction qui affiche la lumiere du spot robot selon un bool�en
///
/// @param[in] positionRobot : la position courante du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereSpotRobot()
{
	// Positionner la lumi�re.

	//glm::vec4 position{ 0.0, 0.0, 5.0, 1.0 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };
	GLfloat direction[] = { 0.0, 0.0, -1.0 };
	//glm::vec4 position{0.0, 0.0, 15.0, 1.0};
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT1, GL_POSITION, /*glm::value_ptr(position)*/positionSpotRobot_);

	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT1, GL_AMBIENT, glm::value_ptr(zeroContribution));

	// On sature les objets de lumi�re
	if (lumiereSpotRobot_)
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(zeroContribution));

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);


}

void ControleurLumiere::animer(const glm::dvec3& positionRobot, float dt)
{
	positionSpotRobot_[0] = positionRobot.x;
	positionSpotRobot_[1] = positionRobot.y;
	positionSpotRobot_[2] = positionRobot.z + 15;
	positionSpotRobot_[3] = 1.0;

	positionSpotGyro_[0] = positionRobot.x;
	positionSpotGyro_[1] = positionRobot.y;
	positionSpotGyro_[2] = positionRobot.z + 5.0;
	positionSpotGyro_[3] = 1.0;

	compteur_ += 225 * dt;
	compteur_ = compteur_ % 360;
	orientationSpotGyro_[0] += glm::cos(utilitaire::DEG_TO_RAD(compteur_));
	orientationSpotGyro_[1] += glm::sin(utilitaire::DEG_TO_RAD(compteur_));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereAmbianteGlobale(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re ambiante
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
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
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re directionelle
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
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
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re du spot gyro
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
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
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re du spot robot
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereSpotRobot(bool estIllumine)
{
	lumiereSpotRobot_ = estIllumine;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////