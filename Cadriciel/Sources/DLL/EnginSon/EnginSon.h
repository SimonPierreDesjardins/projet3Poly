///////////////////////////////////////////////////////////////////////////
/// @file EnginSon.h
/// @author Philippe Marcotte
/// @date 2016-03-29
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef ENGIN_SON_H__
#define ENGIN_SON_H__

#include <string>
#include <memory>
#include "fmod.hpp"
#include <array>

enum typeSon {
	MUSIQUE,
	AVANCER_RECULER,
	TOURNER,
	DEVIATION,
	CHANGEMENT_MANUEL,
	CHANGEMENT_AUTOMATIQUE,
	COLLISION_POTEAU,
	COLLISION_MUR,
	COLLISION_TABLE
};

class EnginSon{
private:
	typedef FMOD::Sound* SoundClass;

	EnginSon(const EnginSon&) = delete;
	/// Opérateur d'assignation désactivé.
	EnginSon& operator =(const EnginSon&) = delete;
	static const std::string CHEMIN_SONS;
	static std::unique_ptr<EnginSon> instance_;

	FMOD::System *m_pSystem;

	std::array<SoundClass, 9> sons_;

	std::array<std::string, 9> nomsSons_;

	std::array<int, 9> channels_;

	FMOD::Channel* musiqueChannel;

	FMOD::Channel* robotChannel;

	FMOD::Channel* collisionChannel;

	FMOD::Channel* obtenirChannel(typeSon son);

public:
	EnginSon();
	~EnginSon();
	static EnginSon* obtenirInstance();
	static void libererInstance();
	void jouerMusique();
	void jouerSonRobot(typeSon son, double puissance);
	void jouerCollision(typeSon son);
	void stopMusique();
	void stopRobotSon();
	void stopCollisionSon();
};


#endif
///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////