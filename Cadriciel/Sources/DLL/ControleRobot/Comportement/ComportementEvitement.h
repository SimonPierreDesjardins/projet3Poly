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

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui implémente le comportement d'évitement du robot.
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

	void setAngleMaxRotation();

	void setTempsMaxReculons();

	virtual void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	virtual void fromJson(const rapidjson::Value& comportementJSON);

private:
	double maxTemps;
	double deltaTemps{ 0.0 };

	double maxAngle;
	double deltaAngle{ 0.0 };

};

#endif // COMPORTEMENT_EVITEMENT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////