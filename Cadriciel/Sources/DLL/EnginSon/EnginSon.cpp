#include "EnginSon.h"
#include <windows.h>
#include <mmsystem.h>
#include <locale>
#include <codecvt>

const std::string EnginSon::CHEMIN_SONS = "./Sons/";
std::unique_ptr<EnginSon> EnginSon::instance_{ nullptr };

EnginSon::EnginSon(){
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(3, FMOD_INIT_NORMAL, NULL);
	nomsSons_ = { { "On_the_Ground_60s.wav", "avancer_reculer.wav", "avancer_reculer.wav",
					"avancer_reculer.wav", "avancer_reculer.wav", "avancer_reculer.wav",
					"Frying_Pan_Hit.wav", "Frying_Pan_Impact.wav", "knock.wav" } };
	for (int i = 0; i < sons_.size(); i++)
	{
		m_pSystem->createSound((CHEMIN_SONS + nomsSons_.at(i)).c_str(), FMOD_HARDWARE, 0, &sons_.at(i));
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

	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &musiqueChannel);
}

void EnginSon::jouerSonRobot(typeSon son, double vitesse){
	SoundClass pSound = sons_.at(son);
	pSound->setMode(FMOD_LOOP_NORMAL);
	pSound->setLoopCount(-1);

	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, true, &robotChannel);

	robotChannel->setVolume(vitesse / 60.0);

	robotChannel->setPaused(false);
}

void EnginSon::jouerCollision(typeSon son){
	SoundClass pSound = sons_.at(son);
	pSound->setMode(FMOD_LOOP_OFF);

	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &collisionChannel);
}

void EnginSon::stopMusique(){
	musiqueChannel->stop();
}

void EnginSon::stopRobotSon(){
	robotChannel->stop();
}

void EnginSon::stopCollisionSon(){
	collisionChannel->stop();
}