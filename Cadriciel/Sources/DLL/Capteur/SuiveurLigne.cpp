////////////////////////////////////////////////////////////////////////////////
/// @file   SuiveurLigne.cpp
/// @author Olivier St-Amour
/// @date   2016-03-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////

#include "SuiveurLigne.h" 

#include "CapteurOptique.h" 
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "rapidjson\filewritestream.h"

const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_DROITE{ 4.8523, -0.853, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_CENTRE{ 4.8523,  0.070, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_GAUCHE{ 4.8523,  0.995, 0.0 };

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::SuiveurLigne()
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
SuiveurLigne::SuiveurLigne()
{
    initialiser();
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::SuiveurLigne()
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
SuiveurLigne::SuiveurLigne(bool estActif)
{
    initialiser();
	estActif_ = estActif;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::SuiveurLigne(const rapidjson::Value& capteurJSON)
///
/// Constructeur par défaut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
SuiveurLigne::SuiveurLigne(const rapidjson::Value& capteurJSON)
{
    initialiser();
	estActif_ = capteurJSON.MemberBegin()->value.GetBool();
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::~SuiveurLigne()
///
/// Destructeur. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////////////
SuiveurLigne::~SuiveurLigne()
{
}

void SuiveurLigne::initialiser()
{
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_DROITE));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_CENTRE));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_GAUCHE));
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::obtenirEtatCapteurs() const
///
/// Permet d'obtenir l'état des capteurs sous la forme d'un entier de 8 bits.
/// Les 3 premiers bits indiquent la détection d'une ligne pour chaque capteur.
///
/// @return L'état des 3 capteurs sur 3 bits.
///
////////////////////////////////////////////////////////////////////////////////
uint8_t SuiveurLigne::obtenirEtatCapteurs() const
{
	uint8_t etat = 0;
	if (capteursOptique_[CAPTEUR_OPTIQUE_DROIT].ligneEstDetectee())
	{
		etat |= 0x01; // 001
	}
	if (capteursOptique_[CAPTEUR_OPTIQUE_CENTRE].ligneEstDetectee())
	{
		etat |= 0x02; // 010
	}
	if (capteursOptique_[CAPTEUR_OPTIQUE_GAUCHE].ligneEstDetectee())
	{
		etat |= 0x04; // 100
	}
	return etat;
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn SuiveurLigne::obtenirEtatCapteurs() const
///
/// Méthode qui met à jour la position et l'état des 3 capteurs optiques.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void SuiveurLigne::mettreAJourCapteurs(const glm::dvec3& positionRobot, const double& angleRobot)
{
	for (int i = 0; i < capteursOptique_.size(); i++)
	{
		capteursOptique_[i].mettreAJourPosition(positionRobot, angleRobot);
	}
}

void SuiveurLigne::afficher() const
{
    for (int i = 0; i < capteursOptique_.size(); i++)
    {
        capteursOptique_[i].afficher();
    }
}


void SuiveurLigne::verifierDetection(NoeudLigne* ligne)
{
    if (!estActif_) return;

    for (int i = 0; i < capteursOptique_.size(); i++)
    {
        capteursOptique_[i].verifierDetection(ligne);
    }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void SuiveurLigne::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
///
/// Cette fonction obtient les valeurs à sauvegarder pour le capteur en JSON
///
/// @param[in] writer : Le stream dans lequel le JSON est écrit
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SuiveurLigne::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	writer.Key("estActif");
	writer.Bool(estActif_);
}


void SuiveurLigne::assignerActif(bool estActif){
	estActif_ = estActif;
}

/////////////////////////////////////////////////////////////////////////////////
/// @}
/////////////////////////////////////////////////////////////////////////////////
