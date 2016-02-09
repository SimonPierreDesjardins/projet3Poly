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
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int  obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport) void assignerEtat(int etat);
	__declspec(dllexport) void assignerMode(int mode);
	__declspec(dllexport) double obtenirAngleRotation();
	__declspec(dllexport) void repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	__declspec(dllexport) double obtenirAngleRotation();
	__declspec(dllexport) double obtenirFacteurGrandeur();
	__declspec(dllexport) double obtenirPositionRelativeX();
	__declspec(dllexport) double obtenirPositionRelativeY();

	__declspec(dllexport) void assignerAngleRotation(double angle);
	__declspec(dllexport) void assignerFacteurGrandeur(double facteurGrandeur);
	__declspec(dllexport) void assignerPositionRelativeX(double positionRelativeX);
	__declspec(dllexport) void assignerPositionRelativeY(double positionRelativeY);
}
#endif // __FACADE_INTERFACE_NATIVE_H__
