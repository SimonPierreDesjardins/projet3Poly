#include "SuiveurLigne.h" 
#include "CapteurOptique.h" 

const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_GAUCHE{ 4.8523,  0.995, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_CENTRE{ 4.8523,  0.070, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_DROITE{ 4.8523, -0.853, 0.0 };

SuiveurLigne::SuiveurLigne()
{
	visiteurDetectionLigne_ = std::make_unique<VisiteurDetectionLigne>();
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_DROITE, visiteurDetectionLigne_.get()));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_CENTRE, visiteurDetectionLigne_.get()));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_GAUCHE, visiteurDetectionLigne_.get()));
}

SuiveurLigne::~SuiveurLigne()
{
}

uint8_t SuiveurLigne::obtenirEtatCapteurs() const
{
	uint8_t etat = 0;
	if (capteursOptique_[CAPTEUR_OPTIQUE_DROIT].ligneEstDetectee())
	{
		etat |= 0x01;
		
	}
	if (capteursOptique_[CAPTEUR_OPTIQUE_CENTRE].ligneEstDetectee())
	{
		etat |= 0x02;
	}
	if (capteursOptique_[CAPTEUR_OPTIQUE_GAUCHE].ligneEstDetectee())
	{
		etat |= 0x04;
	}
	return etat;
}

void SuiveurLigne::mettreAJourCapteurs(const glm::dvec3& positionRobot, const double& angleRobot)
{
	for (int i = 0; i < capteursOptique_.size(); i++)
	{
		capteursOptique_[i].mettreAJourEtat(positionRobot, angleRobot);
	}
}