///////////////////////////////////////////////////////////////////////////////
/// @file EnginSon.cpp
/// @author Philippe Marcotte
/// @date 2016-03-29
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "EnginSon.h"
#include <windows.h>
#include <mmsystem.h>
#include <locale>
#include <codecvt>
#include <iostream>

const std::string EnginSon::CHEMIN_SONS = "./Sons/";

std::unique_ptr<EnginSon> EnginSon::instance_{ nullptr };

////////////////////////////////////////////////////////////////////////
///
/// @fn EnginSon::EnginSon()
///
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////////////////
EnginSon::EnginSon(){
	FMOD::System_Create(&systeme_);
	systeme_->init(10, FMOD_INIT_NORMAL, NULL);
	nomsSons_ = { { "musique_simulation.wav", "avancer_reculer.wav", "tourner.wav",
					"deviation.wav", "changement_manuel.wav", "changement_automatique.wav",
					"collision_poteau.wav", "collision_mur.wav", "collision_table.wav", "collision_teleporteur.wav" } };
	for (int i = 0; i < sons_.size(); i++)
	{
		systeme_->createSound((CHEMIN_SONS + nomsSons_.at(i)).c_str(), FMOD_CREATESAMPLE, 0, &sons_.at(i));
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EnginSon::~EnginSon()
///
/// Destructeur
///
////////////////////////////////////////////////////////////////////////
EnginSon::~EnginSon(){
	for each (SoundClass sound in sons_)
	{
		sound->release();
	}

	musiqueChannel->stop();
	robotChannel->stop();
	changerModeChannel->stop();
	collisionChannel->stop();

	systeme_->release();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EnginSon* EnginSon::obtenirInstance()
///
/// Retourne l'instance vers le singleton.
/// Construit une instance dans le cas où il n'y en avait pas déjà.
///
/// @return Référence vers le singleton
///
////////////////////////////////////////////////////////////////////////
EnginSon* EnginSon::obtenirInstance(){
	if (instance_.get() == nullptr)
	{
		instance_ = std::unique_ptr<EnginSon>(new EnginSon());
	}
	return instance_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::libererInstance()
///
/// Libère l'instance du singleton
///
////////////////////////////////////////////////////////////////////////
void EnginSon::libererInstance(){
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::jouerMusique()
///
/// Joue la musique en boucle lors d'une simulation.
///
////////////////////////////////////////////////////////////////////////
void EnginSon::jouerMusique(){
	SoundClass pSound = sons_.at(MUSIQUE);
	pSound->setMode(FMOD_LOOP_NORMAL);
	pSound->setLoopCount(-1);

	systeme_->playSound(FMOD_CHANNEL_FREE, pSound, true, &musiqueChannel);
	musiqueChannel->setVolume(3.0f);
	musiqueChannel->setPaused(false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::jouerSonRobot(typeSon son)
///
/// Arrête le son de moteur complètement ou
/// joue le son de changement de mode ou
/// change le dernier son de moteur joué, arrête le dernier son de moteur de robot 
/// et joue en boucle le son de moteur passé par paramètre.
///
/// @param[in] son : Représente le son de moteur à jouer
///
////////////////////////////////////////////////////////////////////////
void EnginSon::jouerSonRobot(typeSon son){
	if (son == dernierSonRobot)
		return;

	if (son == ARRETER_SON){
		stopRobotSon();
		return;
	}
	else if(son == CHANGEMENT_AUTOMATIQUE_SON || son == CHANGEMENT_MANUEL_SON){
		changerMode(son);
		stopRobotSon();
		return;
	}

	dernierSonRobot = son;
	
	sons_.at(son)->setMode(FMOD_LOOP_NORMAL);
	sons_.at(son)->setLoopCount(-1);
	
	robotChannel->stop();
	systeme_->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &robotChannel);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::changerMode(typeSon son)
///
/// Arrête le dernier son de changement mode et joue le son passé par paramètre.
///
/// @param[in] son : Son de changement de mode
///
////////////////////////////////////////////////////////////////////////
void EnginSon::changerMode(typeSon son){
	changerModeChannel->stop();
	systeme_->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &changerModeChannel);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::jouerCollision(typeSon son)
///
/// Arrête le dernier son de collision et joue le son de collision passé en paramètre
///
/// @param[in] son : Son de collision
///
////////////////////////////////////////////////////////////////////////
void EnginSon::jouerCollision(typeSon son){
	collisionChannel->stop();
	systeme_->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &collisionChannel);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::stopMusique()
///
/// Arrête la musique.
///
/// @return Référence vers le singleton
///
////////////////////////////////////////////////////////////////////////
void EnginSon::stopMusique(){
	musiqueChannel->stop();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EnginSon::stopRobotSon()
///
/// Change le dernier son de moteur de robot joué et arrête le son des moteurs.
///
////////////////////////////////////////////////////////////////////////
void EnginSon::stopRobotSon(){
	dernierSonRobot = ARRETER_SON;
	robotChannel->stop();
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////