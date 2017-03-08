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
#include "NoeudRobot.h"

/// Repr�sente les sons possibles
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
	/// Repr�sente un objet de type son
	typedef FMOD::Sound* SoundClass;

	/// Constructeur par copie d�sactiv�
	EnginSon(const EnginSon&) = delete;

	/// Op�rateur d'assignation d�sactiv�.
	EnginSon& operator =(const EnginSon&) = delete;

	/// Chemin vers le dossier contenant les sons
	static const std::string CHEMIN_SONS;

	/// Instance du singleton
	static std::unique_ptr<EnginSon> instance_;

	/// R�f�rence vers le syst�me FMOD
	FMOD::System *systeme_;

	/// Tableau contenant les 9 sons possibles
	std::array<SoundClass, 9> sons_;

	/// Tableau contenant les noms des 9 sons possibles
	std::array<std::string, 9> nomsSons_;

	/// Channel jouant la musique en boucle
	FMOD::Channel* musiqueChannel;

	/// Channel jouant les sons de moteur du robot
	FMOD::Channel* robotChannel;

	/// Channel jouant les sons de collision
	FMOD::Channel* collisionChannel;

	/// Channel jouant les sons associ�s au changement de mode du robot
	FMOD::Channel* changerModeChannel;

	/// Repr�sente le dernier son de moteur du robot
	typeSon dernierSonRobot;

	/// Joue le son associ� � un changement de mode du robot
	void changerMode(typeSon son);

	/// Arr�te les sons de moteur du robot
	void stopRobotSon();

public:
	/// Constructeur par d�faut
	EnginSon();

	/// Destructeur
	~EnginSon();

	/// Retourne l'instance du singleton
	static EnginSon* obtenirInstance();

	/// Libere l'instance du singleton
	static void libererInstance();

	/// Joue la musique
	void jouerMusique();

	/// Joue les sons de moteur du robot
	void jouerSonRobot(typeSon son);

	/// Joue les sons de collision
	void jouerCollision(typeSon son);

	/// Arr�te la musique
	void stopMusique();

	/// Retourne r�f�rence vers le syst�me de son
	inline FMOD::System* obtenirSystemeSon();
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline FMOD::System* EnginSon::obtenirSystemeSon()
///
/// Retourne une r�f�rence vers le syst�me
///
/// @return R�f�rence vers le syst�me
///
////////////////////////////////////////////////////////////////////////
inline FMOD::System* EnginSon::obtenirSystemeSon(){
	return systeme_;
}


#endif
///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////