///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.h
/// @author Simon-Pierre Desjardins
/// @date 2016-04-01
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef CONTROLEUR_LUMIERE_H
#define CONTROLEUR_LUMIERE_H


class ModeAbstrait;
///////////////////////////////////////////////////////////////////////////
/// @class ControleurLumiere
/// @brief Classe qui permet de faire l'affichage de la lumière
///
///        Cette classe permet de faire l'affichage de la lumière 
///	       
/// 
/// @author Simon-Pierre Desjardins
/// @date 2016-04-01
///////////////////////////////////////////////////////////////////////////
class ControleurLumiere
{
public:
	ControleurLumiere();
	~ControleurLumiere();

	void afficherLumiereAmbianteGlobale();

private:

	ModeAbstrait* mode_{ nullptr };

	bool lumiereDirectionnelle{ true };
	bool lumiereAmbiante{ true };
	bool lumiereSpot{ true };


};




#endif // CONTROLEUR_LUMIERE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////