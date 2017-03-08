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

// �num�ration permettant d'associer une position � un index dans le vecteur.
enum PositionCapteurOptique
{
	CAPTEUR_OPTIQUE_DROIT,
	CAPTEUR_OPTIQUE_CENTRE,
	CAPTEUR_OPTIQUE_GAUCHE,
};

// �num�ration permettant de diff�rencier les diff�rentes valeurs de retour.
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
/// @brief Classe qui repr�sente le suiveur de ligne. 
///
///        Cette classe s'occupe de g�rer la d�tection de ligne. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class SuiveurLigne
{
public:
	//Constructeur par d�faut
	SuiveurLigne();

	//Constructeur par param�tre
	SuiveurLigne(bool estActif);

	//Constructeur par param�tre
	SuiveurLigne(const rapidjson::Value& capteurJSON);

	//Destructeur
	~SuiveurLigne();


	// Retourne l'�tat des capteurs optiques sur les 3 premiers bits.
	uint8_t obtenirEtatCapteurs() const;
    // Mettre � jour l'�tat des capteurs et leur position.
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
	ArbreRendu* arbre_{ nullptr };

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