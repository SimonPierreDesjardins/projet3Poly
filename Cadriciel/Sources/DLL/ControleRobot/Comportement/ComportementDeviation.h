///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_DEVIATION
#define COMPORTEMENT_DEVIATION

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementDeviation
/// @brief Classe qui implémente le comportement de deviation du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementDeviation : public ComportementAbstrait
{
public:
	ComportementDeviation();
	ComportementDeviation(TypeComportement prochainComportement);
	ComportementDeviation(const rapidjson::Value& comportementJSON);
	ComportementDeviation(TypeComportement prochainComportement, double angleMax);
	virtual ~ComportementDeviation();

	void initialiser();

	void mettreAJour();

	void setAngleMaxRotation(double angle);

	virtual void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	virtual void fromJson(const rapidjson::Value& comportementJSON);

private:
	double maxAngle;
	double deltaAngle{ 0.0 };
};

#endif // COMPORTEMENT_DEVIATION

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
