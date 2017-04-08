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
#include "rapidjson\writer.h"
#include "rapidjson\document.h"

namespace rapidjson {
	class FileWriteStream;
}

class CapteurOptique;
class ArbreRendu;
class NoeudLigne;

// Énumération permettant d'associer une position à un index dans le vecteur.
enum PositionCapteurOptique
{
	CAPTEUR_OPTIQUE_DROIT,
	CAPTEUR_OPTIQUE_CENTRE,
	CAPTEUR_OPTIQUE_GAUCHE,
};

// Énumération permettant de différencier les différentes valeurs de retour.
enum EtatSuiveurLigne
{
	AUCUNE,					// 000
	DROIT,					// 001
	CENTRE,					// 010
	CENTRE_DROIT,			// 011
	GAUCHE,					// 100
	GAUCHE_DROIT,			// 101
	GAUCHE_CENTRE,			// 110
	GAUCHE_CENTRE_DROIT		// 111	
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

	//Constructeur par paramètre
	SuiveurLigne(bool estActif);

	//Constructeur par paramètre
	SuiveurLigne(const rapidjson::Value& capteurJSON);

	//Destructeur
	~SuiveurLigne();


	// Retourne l'état des capteurs optiques sur les 3 premiers bits.
	uint8_t obtenirEtatCapteurs() const;
    // Mettre à jour l'état des capteurs et leur position.
	void mettreAJourCapteurs(const glm::dvec3& positionRobot, const double& angleRobot);

    void verifierDetection(NoeudLigne* jonction);

    void afficher() const;
	void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	void assignerActif(bool estActif);

	inline bool obtenirEstActif();
		
private:
	bool estActif_;

	static const glm::dvec3 POSITION_RELATIVE_GAUCHE;
	static const glm::dvec3 POSITION_RELATIVE_CENTRE;
	static const glm::dvec3 POSITION_RELATIVE_DROITE;

	std::vector<CapteurOptique> capteursOptique_;

    void initialiser();
};

////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool SuiveurLigne::obtenirEstActif()
///
/// Retourne si le suiveur de ligne est actif ou non
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////////////
inline bool SuiveurLigne::obtenirEstActif(){
	return estActif_;
}

#endif // SUIVEUR_LIGNE_H
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////