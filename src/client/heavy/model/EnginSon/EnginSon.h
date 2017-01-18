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

/// Représente les sons possibles
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
	/// Représente un objet de type son
	typedef FMOD::Sound* SoundClass;

	/// Constructeur par copie désactivé
	EnginSon(const EnginSon&) = delete;

	/// Opérateur d'assignation désactivé.
	EnginSon& operator =(const EnginSon&) = delete;

	/// Chemin vers le dossier contenant les sons
	static const std::string CHEMIN_SONS;

	/// Instance du singleton
	static std::unique_ptr<EnginSon> instance_;

	/// Référence vers le système FMOD
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

	/// Channel jouant les sons associés au changement de mode du robot
	FMOD::Channel* changerModeChannel;

	/// Représente le dernier son de moteur du robot
	typeSon dernierSonRobot;

	/// Joue le son associé à un changement de mode du robot
	void changerMode(typeSon son);

	/// Arrête les sons de moteur du robot
	void stopRobotSon();

public:
	/// Constructeur par défaut
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

	/// Arrête la musique
	void stopMusique();

	/// Retourne référence vers le système de son
	inline FMOD::System* obtenirSystemeSon();
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline FMOD::System* EnginSon::obtenirSystemeSon()
///
/// Retourne une référence vers le système
///
/// @return Référence vers le système
///
////////////////////////////////////////////////////////////////////////
inline FMOD::System* EnginSon::obtenirSystemeSon(){
	return systeme_;
}


#endif
///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////