#include "SuiveurLigne.h" 
#include "CapteurOptique.h" 

const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_GAUCHE{ 4.8523,  0.995, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_CENTRE{ 4.8523,  0.070, 0.0 };
const glm::dvec3 SuiveurLigne::POSITION_RELATIVE_DROITE{ 4.8523, -0.853, 0.0 };

SuiveurLigne::SuiveurLigne()
{
	visiteurDetectionLigne_ = std::make_unique<VisiteurDetectionLigne>();
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_GAUCHE, visiteurDetectionLigne_.get()));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_CENTRE, visiteurDetectionLigne_.get()));
	capteursOptique_.push_back(CapteurOptique(POSITION_RELATIVE_DROITE, visiteurDetectionLigne_.get()));
}


SuiveurLigne::~SuiveurLigne()
{
}

bool SuiveurLigne::obtenirEtatCapteur(const PositionCapteur& position)
{
	bool etat = false;
	if (position < capteursOptique_.size())
	{
		etat = capteursOptique_[position].ligneEstDetectee();
	}
	return etat;
}
