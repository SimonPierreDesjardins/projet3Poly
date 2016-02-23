///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.h
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_SIMULATION_H
#define MODE_SIMULATION_H

#include <memory>
#include "glm\glm.hpp"
#include "ModeAbstrait.h"
#include "ControleRobot.h"
#include <unordered_map>

class ProfilUtilisateur;

//////////////////////////////////////////////////////////////////////////
/// @class ModeSimulation
/// @brief Classe qui représente le mode simulation de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode simulation
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeSimulation : public ModeAbstrait
{
public:

	//Constructeur par défaut
	ModeSimulation();

	//Destructeur
	virtual ~ModeSimulation();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_;
};

#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////