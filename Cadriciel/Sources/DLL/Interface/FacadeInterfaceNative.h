////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

#include <Windows.h>
#include <Windowsx.h>
#include "ComportementAbstrait.h"
#include "CommandeRobot.h"

extern "C"
{
	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void sauvegarder();
	__declspec(dllexport) void charger();
	__declspec(dllexport) void assignerCheminFichierZone(char* chemin);
	__declspec(dllexport) void obtenirCheminFichierZoneDefaut(char* chemin, int longueur);
	__declspec(dllexport) int  obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();

	__declspec(dllexport) void assignerMode(int mode);
	__declspec(dllexport) int obtenirMode();

	__declspec(dllexport) void repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	__declspec(dllexport) bool peutRafraichir();

	__declspec(dllexport) void __cdecl nouvelleTable();
	__declspec(dllexport) void __cdecl suppression();
	__declspec(dllexport) int __cdecl obtenirNombreSelection();
	__declspec(dllexport) bool __cdecl obtenirAutorisationInputClavier();
	__declspec(dllexport) void __cdecl assignerAutorisationInputClavier(bool autorisation);
	__declspec(dllexport) bool __cdecl obtenirAutorisationInputSouris();
	__declspec(dllexport) void __cdecl assignerAutorisationInputSouris(bool autorisation);

	__declspec(dllexport) double obtenirAngleRotation();
	__declspec(dllexport) double obtenirFacteurGrandeur();
	__declspec(dllexport) double obtenirPositionRelativeX();
	__declspec(dllexport) double obtenirPositionRelativeY();

	__declspec(dllexport) void assignerAngleRotation(double angle);
	__declspec(dllexport) void assignerFacteurGrandeur(double facteurMiseAEchelle);
	__declspec(dllexport) void assignerPositionRelativeX(double positionRelativeX);
	__declspec(dllexport) void assignerPositionRelativeY(double positionRelativeY);

	__declspec(dllexport) void __cdecl assignerComportementSuivreLigne(TypeComportement comportementSuivant);
	__declspec(dllexport) void __cdecl assignerComportementBalayage(TypeComportement comportementSuivant);
	__declspec(dllexport) void __cdecl assignerComportementDeviation(TypeComportement comportementSuivant, double angle, TypeComportement typeDeviation);
	__declspec(dllexport) void __cdecl assignerComportementEvitement(TypeComportement comportementSuivant, double angle, double duree, TypeComportement typeEvitement);
	__declspec(dllexport) void __cdecl modifierToucheCommande(const unsigned char& touche, const TypeCommande& commande);

	//__declspec(dllexport) void __cdecl modifierToucheCommande(char touche, int commande);
	__declspec(dllexport) void __cdecl chargerProfilParDefaut();

	__declspec(dllexport) char __cdecl obtenirToucheCommande(int commande);


}

#endif // __FACADE_INTERFACE_NATIVE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////