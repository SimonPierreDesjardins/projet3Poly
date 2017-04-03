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

	//Menu personalize
	__declspec(dllexport) bool __cdecl getUsingDefaultMaterialForPiece(int piece);
	__declspec(dllexport) void __cdecl setUsingDefaultMaterialForPiece(int piece, bool value);
	__declspec(dllexport) void __cdecl changePieceColor(int piece, int a, int r, int g, int b);
	__declspec(dllexport) int* __cdecl getPieceColor(int piece);
	__declspec(dllexport) void __cdecl setModele(char *modele);
	__declspec(dllexport) void __cdecl getModele(char* chemin, int longueur);
	__declspec(dllexport) void __cdecl setMusic(char* path);
	__declspec(dllexport) void __cdecl getMusic(char* path, int size);
	__declspec(dllexport) void __cdecl getDefaultMusic(char* path, int size);
	
	// Network
	__declspec(dllexport) bool __cdecl connectToServer(char* hostName, char* port);
	__declspec(dllexport) void __cdecl createProfile(char* profileName);
	__declspec(dllexport) void __cdecl authenticate(char* profileName);
	__declspec(dllexport) void __cdecl disconnectFromServer();
	__declspec(dllexport) bool __cdecl isConnected();
	__declspec(dllexport) void __cdecl sendMessage(char* message, int size);
	__declspec(dllexport) void __cdecl uploadMap(char* filePath);
	typedef int(__stdcall * CallbackDisconnect)();
	__declspec(dllexport) void __cdecl SetCallbackForDisconnect(CallbackDisconnect disconnectHandler);
	__declspec(dllexport) void __cdecl GotDisconnected();
	typedef int(__stdcall * CallbackConnectionSuccess)();
	__declspec(dllexport) void __cdecl SetCallbackForConnectionSuccess(CallbackConnectionSuccess connectionSuccessHandler);
	__declspec(dllexport) void __cdecl connectionWasSuccess();
	typedef int(__stdcall * CallbackConnectionFail)();
	__declspec(dllexport) void __cdecl SetCallbackForConnectionFail(CallbackConnectionFail connectionFailHandler);
	__declspec(dllexport) void __cdecl connectionWasFail();

	// Map management
	__declspec(dllexport) void __cdecl createMap(char* mapName, int mapNamesize, char* password, int passwordSize, char mapType, char isPrivate);
	__declspec(dllexport) void __cdecl joinMap(int mapId);
	__declspec(dllexport) void __cdecl leaveMap();

	//Edition Tutorial
	typedef int(__stdcall * Callback)();
	__declspec(dllexport) void __cdecl SetCallback(Callback function);
	__declspec(dllexport) void __cdecl ChangeEditionTutorialState();
	__declspec(dllexport) void __cdecl UpdateEditionTutorialState(int currentState);
	__declspec(dllexport) void __cdecl UnselectCurrentTool();
	__declspec(dllexport) void __cdecl UnselectAllObjects();
	__declspec(dllexport) void __cdecl SelectAllTutorialObjects();
	__declspec(dllexport) bool __cdecl getEditionTutorialState();
	__declspec(dllexport) void __cdecl setEditionTutorialState(bool completed);

	//Simulation Tutorial
	__declspec(dllexport) bool __cdecl getSimulationTutorialState();
	__declspec(dllexport) void __cdecl setSimulationTutorialState(bool completed);

	//Chat System
	typedef void(__stdcall * CallbackForChat)(const unsigned char* text, int size);
	__declspec(dllexport) void __cdecl SetCallbackForChat(CallbackForChat handler);
	__declspec(dllexport) void __cdecl TestCallback(std::string message);

	//Map System
	typedef void(__stdcall * CallbackForNewMap)(const unsigned char* text, int size, bool connectionState, int mode, int nbPlayers, int id);
	__declspec(dllexport) void __cdecl SetCallbackForNewMap(CallbackForNewMap addNewMap);
	__declspec(dllexport) void __cdecl AddMap(const std::string& name, bool isPrivate, bool connectionState, int mode, int nbPlayers, int id);

	//Application saved settings
	__declspec(dllexport) void __cdecl LoadApplicationSettings();
	__declspec(dllexport) void __cdecl SaveApplicationSettings();
}

#endif // __FACADE_INTERFACE_NATIVE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////