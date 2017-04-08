///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.h
/// @author Simon-Pierre Desjardins
/// @date 2016-04-01
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef CONTROLEUR_LUMIERE_H
#define CONTROLEUR_LUMIERE_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp" 
#include "GL/glew.h"

class ModeAbstrait;
///////////////////////////////////////////////////////////////////////////
/// @class ControleurLumiere
/// @brief Classe qui permet de faire l'affichage de la lumière
///
///        Cette classe permet de faire l'affichage de la lumière 
///	       
/// 
/// @author Simon-Pierre Desjardins
/// @date 2016-04-01
///////////////////////////////////////////////////////////////////////////
class ControleurLumiere
{
public:
	ControleurLumiere();
	~ControleurLumiere();

	void afficherLumiereAmbianteGlobale() const;
	void afficherLumiereDirectionnelle() const;
	void afficherLumiereSpotGyro() const;
	void afficherLumiereSpotRobot() const;

	void animer(const glm::dvec3& positionRobot, float dt);

	void assignerLumiereAmbianteGlobale(bool estIllumine);
	void assignerLumiereDirectionnelle(bool estIllumine);
	void assignerLumiereSpotGyro(bool estIllumine);
	void assignerLumiereSpotRobot(bool estIllumine);

	void setEnPause(bool estEnPause);

private:

	ModeAbstrait* mode_{ nullptr };

	bool lumiereDirectionnelle_{ true };
	bool lumiereAmbiante_{ true };
	bool lumiereSpotGyro_{ true };
	bool lumiereSpotRobot_{ true };

	glm::dvec4 spotGyro_{ 0.0, 0.0, 0.0, 0.0 };

	GLfloat positionSpotGyro_[4];
	GLfloat positionSpotRobot_[4];
	GLfloat orientationSpotGyro_[3];

	int compteur_{ 0 };
	bool estEnPause_{false};
};




#endif // CONTROLEUR_LUMIERE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////