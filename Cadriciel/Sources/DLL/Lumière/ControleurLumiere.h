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

	void afficherLumiereAmbianteGlobale();
	void afficherLumiereDirectionnelle();
	void afficherLumiereSpotGyro(glm::dvec3 positionRobot);
	void afficherLumiereSpotRobot(glm::dvec3 positionRobot);

	void assignerLumiereAmbianteGlobale(bool estIllumine);
	void assignerLumiereDirectionnelle(bool estIllumine);
	void assignerLumiereSpotGyro(bool estIllumine);
	void assignerLumiereSpotRobot(bool estIllumine);

private:

	ModeAbstrait* mode_{ nullptr };

	bool lumiereDirectionnelle_{ true };
	bool lumiereAmbiante_{ true };
	bool lumiereSpotGyro_{ true };
	bool lumiereSpotRobot_{ true };
};




#endif // CONTROLEUR_LUMIERE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////