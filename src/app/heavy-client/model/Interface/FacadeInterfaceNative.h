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

	__declspec(dllexport) void __cdecl assignerComportementSuivreLigne(int comportementSuivant);
	__declspec(dllexport) void __cdecl assignerComportementBalayage(int comportementSuivant);
	__declspec(dllexport) void __cdecl assignerComportementDeviation(int comportementSuivant, double angle, int typeDeviation);
	__declspec(dllexport) void __cdecl assignerComportementEvitement(int comportementSuivant, double angle, double duree, int typeEvitement);

	__declspec(dllexport) void __cdecl assignerCapteurDistance(bool estActif, int comportementDanger, double distanceDanger, int comportementSecuritaire, double distanceSecuritaire, int indexCapteur);

	__declspec(dllexport) void __cdecl assignerSuiveurLigne(bool estActif);

	__declspec(dllexport) void __cdecl assignerOptionsDebogages(bool debogageActif, bool debogageComportements, bool debogageEclairage, bool debogageCapteurs);

	__declspec(dllexport) void __cdecl assignerConfigureHandles(HWND handle, int ctrl);

	__declspec(dllexport) void __cdecl modifierToucheCommande(char touche, int commande);

	__declspec(dllexport) void __cdecl obtenirNomProfilDefaut(char* chemin, int longueur);
	__declspec(dllexport) void __cdecl obtenirNomDernierProfil(char* chemin, int longueur);
	__declspec(dllexport) void __cdecl chargerDernierProfil();

	__declspec(dllexport) void __cdecl assignerProfils();

	__declspec(dllexport) void __cdecl sauvegarderProfil(char* nomProfil);

	__declspec(dllexport) void __cdecl changerProfil(char* nomProfil);

	__declspec(dllexport) char __cdecl obtenirToucheCommande(int commande);

	__declspec(dllexport) void __cdecl assignerAffichageComportement(bool afficherDebugComportement);
	__declspec(dllexport) void __cdecl assignerAffichageEclairage(bool afficherDebugEclairage);
	__declspec(dllexport) void __cdecl assignerAffichageCapteurs(bool afficherDebugCapteurs);

	__declspec(dllexport) void __cdecl obtenirCheminProfils(char* chemin, int longueur);
	__declspec(dllexport) void __cdecl obtenirExtensionProfils(char* chemin, int longueur);

	__declspec(dllexport) void __cdecl supprimerProfil(char* nomProfil);

	__declspec(dllexport) int* __cdecl obtenirLimitesParametres();

	__declspec(dllexport) void __cdecl assignerVueOrtho();
	__declspec(dllexport) void __cdecl assignerVueOrbite();
	__declspec(dllexport) void __cdecl assignerVuePremierePersonne();

	__declspec(dllexport) int __cdecl obtenirTypeVue();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////