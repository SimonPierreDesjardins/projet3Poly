///////////////////////////////////////////////////////////////////////////////
/// @file ComporterEvitement.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_EVITEMENT
#define COMPORTEMENT_EVITEMENT

#include "ComportementAbstrait.h"
#include <ctime>

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui impl�mente le comportement d'�vitement du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementEvitement : public ComportementAbstrait
{
public:
	ComportementEvitement();
	ComportementEvitement(TypeComportement prochainComportement);
	ComportementEvitement(const rapidjson::Value& comportementJSON);
	ComportementEvitement(TypeComportement prochainComportement, double maxTemps, double maxAngle);
	virtual ~ComportementEvitement();

	void initialiser();

	void mettreAJour();

	void setAngleMaxRotation(double angle);

	void setTempsMaxReculons(double temps);

	inline double obtenirMaxAngle();

	inline double obtenirMaxTemps();

	virtual void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	virtual void fromJson(const rapidjson::Value& comportementJSON);

private:
	// Flag informant le comportement qu'il s'agit d'un �vitement pivot gauche
	bool gauche;

	// Flag dictant au comportement d'ignorer les lignes rencontr�es
	bool ignorerLigne_;

	time_t startTime_;

	// Le nombre de secondes que le comportement force le reculons
	double maxTemps_;

	// L'angle relative a atteindre pour que le pivot soit complet
	double maxAngle_;

	// L'angle absolue a atteindre pour changement de comportment
	double angleCible_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ComportementEvitement::obtenirMaxAngle()
///
/// Retourne l'angle maximal � atteindre lors de l'�vitement
///
/// @return double L'angle maximal � atteindre.
///
////////////////////////////////////////////////////////////////////////
inline double ComportementEvitement::obtenirMaxAngle(){
	return maxAngle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline double ComportementEvitement::obtenirMaxAngle()
///
/// Retourne la dur�e � attendre lors de l'�vitement
///
/// @return double La dur�e � attendre.
///
////////////////////////////////////////////////////////////////////////
inline double ComportementEvitement::obtenirMaxTemps(){
	return maxTemps_;
}

#endif // COMPORTEMENT_EVITEMENT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////