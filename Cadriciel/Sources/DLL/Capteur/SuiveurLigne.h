///////////////////////////////////////////////////////////////////////////
/// @file SuiveurLigne.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef SUIVEUR_LIGNE_H
#define SUIVEUR_LIGNE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "VisiteurDetectionLigne.h"

class CapteurOptique;
class ArbreRendu;

// Énumération permettant d'associer une position à un index dans le vecteur.
enum PositionCapteur
{
	CAPTEUR_OPTIQUE_DROIT,
	CAPTEUR_OPTIQUE_CENTRE,
	CAPTEUR_OPTIQUE_GAUCHE,
};

// Énumération permettant de différencier les différentes valeurs de retour.
enum EtatSuiveurLigne
{
	AUCUNE,					// 0x000
	DROIT,					// 0x001
	CENTRE,					// 0x010
	CENTRE_DROIT,			// 0x011
	GAUCHE,					// 0x100
	GAUCHE_DROIT,			// 0x101
	GAUCHE_CENTRE,			// 0x110
	GAUCHE_CENTRE_DROIT		// 0x111	
};

///////////////////////////////////////////////////////////////////////////
/// @class SuiveurLigne
/// @brief Classe qui représente le suiveur de ligne. 
///
///        Cette classe s'occupe de gérer la détection de ligne. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class SuiveurLigne
{
public:
	//Constructeur par défaut
	SuiveurLigne();
	//Destructeur
	~SuiveurLigne();
	// Retourne l'état des capteurs optiques sur les 3 premiers bits.
	uint8_t obtenirEtatCapteurs() const;
	void mettreAJourCapteurs(const glm::dvec3& positionRobot, const double& angleRobot);
		
private:
	static const glm::dvec3 POSITION_RELATIVE_GAUCHE;
	static const glm::dvec3 POSITION_RELATIVE_CENTRE;
	static const glm::dvec3 POSITION_RELATIVE_DROITE;

	std::vector<CapteurOptique> capteursOptique_;
	std::unique_ptr<VisiteurDetectionLigne> visiteurDetectionLigne_{ nullptr };
	ArbreRendu* arbre_{ nullptr };
};

#endif // SUIVEUR_LIGNE_H
