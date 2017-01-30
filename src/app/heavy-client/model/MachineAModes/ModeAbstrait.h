///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_ABSTRAIT_H
#define MODE_ABSTRAIT_H

#include <memory>
#include "glm\glm.hpp"
#include <Windows.h>
#include <Windowsx.h>
#include "ModeEnum.cs"



///////////////////////////////////////////////////////////////////////////
/// @class ModeAbstraitC:\Users\Olivier St-Amour\Documents\Polytechnique\hiver_2016\inf2990-06\Cadriciel\Sources\InterfaceGraphique\Program.cs
/// @brief Classe qui repr�sente le mode abstrait de notre machine � modes
///
///        Cette classe s'occupe de d�clarer les fonctions qui seront impl�ment�s 
///	       dans les �tats d�riv�s.
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeAbstrait
{
public:
	//Constructeur par d�faut
	ModeAbstrait();
	//Destructeur
	virtual ~ModeAbstrait();

	//Gestion du syst�me de chargement et de sauvegarde
	virtual void sauvegarder();
	virtual void charger();

	virtual void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	inline int obtenirTypeMode();


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ModeSimulation::preChangementDeProfil()
	///
	/// Fonction appel�e avant qu'il y ait changement de profil pour arr�ter les acc�s.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	virtual void preChangementDeProfil(){}; 	// Dans le but d'�viter un downcast, la gestion de changement de profil se trouve ici.

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ModeSimulation::preChangementDeProfil()
	///
	/// Fonction appel�e apr�s qu'il y ait changement de profil pour reprendre la simulation sans probl�me.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	virtual void postChangementDeProfil(){};

	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);
	virtual void gererMoletteSouris(const int & delta);

protected:
	int typeMode_;
	bool clicDroitEnfonce_{ false };
	static glm::ivec2 currentPosition_;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ModeAbstrait::obtenirTypeMode()
///
/// Cette fonction retourne le type de mode de l'attribut typeMode_.
///
///
/// @return int typeMode_.
///
////////////////////////////////////////////////////////////////////////
inline int ModeAbstrait::obtenirTypeMode()
{
	return typeMode_;
}

#endif /// MODE_ABSTRAIT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////