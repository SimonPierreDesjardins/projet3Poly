///////////////////////////////////////////////////////////////////////////
/// @file Configuration.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <memory>
#include <map>
#include "glm\glm.hpp"
#include "CommandeRobot.h"

//http://www.kbdedit.com/manual/low_level_vk_list.html
///////////////////////////////////////////////////////////////////////////
/// @class Configuration
/// @brief Classe qui représente une configuration, soit du profils de l'usager
///			ou du comportement du robot et option débogage
///
/// @author Frédéric Grégoire
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class Configuration{
public:
	/// Constructeur par défaut
	Configuration();

	//Destructeur
	~Configuration();

	void modifierAvancer(int KeyCode);
	void modifierReculer(int KeyCode);
	void modifierRotationDroite(int KeyCode);
	void modifierRotationGauche(int KeyCode);
	void modifierModeChangement(int KeyCode);

protected:
	std::map<int, Commande > touche_;
};

#endif/// CONFIGURATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

