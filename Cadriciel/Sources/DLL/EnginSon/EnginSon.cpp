#include "EnginSon.h"
#include <windows.h>
#include <mmsystem.h>
#include <locale>
#include <codecvt>

const std::string EnginSon::CHEMIN_SONS = "./Sons/";
std::unique_ptr<EnginSon> EnginSon::instance_{ nullptr };

EnginSon::EnginSon(){
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(4, FMOD_INIT_NORMAL, NULL);
	nomsSons_ = { { "On_the_Ground.wav", "avancer_reculer.wav", "avancer_reculer.wav",
					"avancer_reculer.wav", "bike_honk.wav", "bike_horn.wav",
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
	musiqueChannel->setVolume(5);
	musiqueChannel->setPaused(false);

	//m_pSystem->update();
}

void EnginSon::jouerSonRobot(typeSon son, float vitesse){
	SoundClass sound;
	SoundClass pSound = sons_.at(son);
	robotChannel->getCurrentSound(&sound);

	if (sound == pSound)
		return;
	else if (sound != 0)
		robotChannel->stop();
	
	dernierSonRobot = son;
	dernierVolumeSonRobot = vitesse;
	
	pSound->setMode(FMOD_LOOP_NORMAL);
	pSound->setLoopCount(-1);
	
	//m_pSystem->playSound(FMOD_CHANNEL_REUSE, pSound, true, &robotChannel);

	robotChannel->setVolume(0.5f);

	robotChannel->setPaused(false);
}

void EnginSon::changerMode(){
	//SoundClass sound;
	//robotChannel->getCurrentSound(&sound);
	//if(sound != NULL)	stopRobotSon();
	m_pSystem->playSound(FMOD_CHANNEL_FREE, sons_.at(CHANGEMENT_AUTOMATIQUE), false, 0);
}

void EnginSon::jouerCollision(typeSon son){
	//SoundClass pSound = 
	//pSound->setMode(FMOD_LOOP_OFF);
	
	m_pSystem->playSound(FMOD_CHANNEL_FREE, sons_.at(son), false, 0);
}

void EnginSon::stopMusique(){
	musiqueChannel->stop();
}

void EnginSon::stopRobotSon(){
	dernierSonRobot = MUSIQUE;
	robotChannel->stop();
}

void EnginSon::stopCollisionSon(){
	collisionChannel->stop();
}