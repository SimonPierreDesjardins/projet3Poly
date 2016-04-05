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
/// Constructeur par défaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::ControleurLumiere()
{

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
/// Fonction qui affiche la lumiere directionelle selon un booléen
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereDirectionnelle()
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
void ControleurLumiere::afficherLumiereSpotGyro(glm::dvec3 positionRobot)
{

	// Positionner la lumière.
	glm::vec4 position{ positionRobot.x, positionRobot.y, positionRobot.z, 1 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 0.0, 0.0, 1.0 };
	GLfloat direction[] = { 1.0, 1.0, -1.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT1, GL_AMBIENT, glm::value_ptr(zeroContribution));

	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);

	// On sature les objets de lumière
	if (lumiereSpotGyro_)
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(zeroContribution));
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
void ControleurLumiere::afficherLumiereSpotRobot(glm::dvec3 positionRobot)
{

	// Positionner la lumière.
	glm::vec4 position{ positionRobot.x, positionRobot.y, positionRobot.z, 0 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 0.0, 1.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT2, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT2, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumière
	if (lumiereSpotRobot_)
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT2, GL_SPECULAR, glm::value_ptr(zeroContribution));
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

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////