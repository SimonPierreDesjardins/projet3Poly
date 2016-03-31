#include "EnginSon.h"
#include <windows.h>
#include <mmsystem.h>
#include <locale>
#include <codecvt>
#include <iostream>

const std::string EnginSon::CHEMIN_SONS = "./Sons/";
std::unique_ptr<EnginSon> EnginSon::instance_{ nullptr };

EnginSon::EnginSon(){
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(4, FMOD_INIT_NORMAL, NULL);
	nomsSons_ = { { "On_the_Ground.wav", "avancer_reculer.wav", "avancer_reculer.wav",
					"avancer_reculer.wav", "changement_manuel.wav", "changement_automatique.wav",
					"Frying_Pan_Hit.wav", "Frying_Pan_Impact.wav", "knock.wav" } };
	for (int i = 0; i < sons_.size(); i++)
	{
		m_pSystem->createSound((CHEMIN_SONS + nomsSons_.at(i)).c_str(), FMOD_CREATESAMPLE, 0, &sons_.at(i));
	}
}

EnginSon::~EnginSon(){
	for each (SoundClass sound in sons_)
	{
		sound->release();
	}

	musiqueChannel->stop();
	robotChannel->stop();
	changerModeChannel->stop();
	collisionChannel->stop();

	m_pSystem->release();
}

EnginSon* EnginSon::obtenirInstance(){
	if (instance_.get() == nullptr)
	{
		instance_ = std::unique_ptr<EnginSon>(new EnginSon());
	}
	return instance_.get();
}

void EnginSon::libererInstance(){
	instance_ = nullptr;
}

void EnginSon::jouerMusique(){
	SoundClass pSound = sons_.at(MUSIQUE);
	pSound->setMode(FMOD_LOOP_NORMAL);
	pSound->setLoopCount(-1);

	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, true, &musiqueChannel);
	musiqueChannel->setVolume(3.0f);
	musiqueChannel->setPaused(false);
}

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

	SoundClass sound;
	SoundClass pSound = sons_.at(son);

	dernierSonRobot = son;
	
	sons_.at(son)->setMode(FMOD_LOOP_NORMAL);
	sons_.at(son)->setLoopCount(-1);
	
	robotChannel->stop();
	m_pSystem->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &robotChannel);
}

void EnginSon::changerMode(typeSon son){
	changerModeChannel->stop();
	m_pSystem->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &changerModeChannel);
}

void EnginSon::jouerCollision(typeSon son){
	collisionChannel->stop();
	m_pSystem->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, &collisionChannel);
}

void EnginSon::stopMusique(){
	musiqueChannel->stop();
}

void EnginSon::stopRobotSon(){
	dernierSonRobot = ARRETER_SON;
	robotChannel->stop();
}

void EnginSon::stopCollisionSon(){
	collisionChannel->stop();
}