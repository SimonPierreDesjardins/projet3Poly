///////////////////////////////////////////////////////////////////////////////
/// @file ComportementBalayage.h
/// @author Olivier St-Amour
/// @date 2016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_BALAYAGE
#define COMPORETMENT_BALAYAGE

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui impl�mente le comportement de balayage du robot.
///
/// @author Olivier St-Amour, Camille Gendreau
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementBalayage : public ComportementAbstrait
{
public:
	ComportementBalayage();
	ComportementBalayage(TypeComportement comportement);
	ComportementBalayage(const rapidjson::Value& comportementJSON);
	virtual ~ComportementBalayage();

	void initialiser();

	void mettreAJour();

private:
	// definit la rotation en cours.
	int etatRotation{ 0 };

	double angleCible{ 90.0 };

	double deltaAngle{ 0.0 };
};

#endif // COMPORTEMENT_BALAYAGE

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////