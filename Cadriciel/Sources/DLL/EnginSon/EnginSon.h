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
	ARRETER_SON = -1,
	MUSIQUE,
	AVANCER_RECULER_SON,
	TOURNER_SON,
	DEVIATION_SON,
	CHANGEMENT_MANUEL_SON,
	CHANGEMENT_AUTOMATIQUE_SON,
	COLLISION_POTEAU_SON,
	COLLISION_MUR_SON,
	COLLISION_TABLE_SON
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

	FMOD::Channel* changerModeChannel;

	FMOD::Channel* obtenirChannel(typeSon son);

	typeSon dernierSonRobot;

	void changerMode(typeSon son);

public:
	EnginSon();
	~EnginSon();
	static EnginSon* obtenirInstance();
	static void libererInstance();
	void jouerMusique();
	void jouerSonRobot(typeSon son);
	
	void jouerCollision(typeSon son);
	void stopMusique();
	void stopRobotSon();
	void stopCollisionSon();
	FMOD::System* obtenirSystem(){ return m_pSystem; };
};


#endif
///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////