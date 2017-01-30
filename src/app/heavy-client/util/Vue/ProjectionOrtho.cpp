////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrtho.h"
#include <iostream>
#include <algorithm>


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre,
		bool perspective) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, perspective },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		if (currentZoom_ > zoomInMax_){
			double ajoutX, ajoutY, fx, fy;
			fx = xMaxFenetre_ - xMinFenetre_;
			fy = yMaxFenetre_ - yMinFenetre_;
			ajoutX = ((1 / incrementZoom_)*fx - fx)*0.5;
			ajoutY = ((1 / incrementZoom_)*fy - fy)*0.5;
			xMinFenetre_ -= ajoutX;
			xMaxFenetre_ += ajoutX;
			yMinFenetre_ -= ajoutY;
			yMaxFenetre_ += ajoutY;

			currentZoom_ -= incrementZoom_;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out de 10% selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		if (currentZoom_ < zoomOutMax_){
			double ajoutX, ajoutY, fx, fy;
			fx = xMaxFenetre_ - xMinFenetre_;
			fy = yMaxFenetre_ - yMinFenetre_;
			ajoutX = (fx*incrementZoom_ - fx)*0.5;
			ajoutY = (fy*incrementZoom_ - fy)*0.5;
			xMinFenetre_ -= ajoutX;
			xMaxFenetre_ += ajoutX;
			yMinFenetre_ -= ajoutY;
			yMaxFenetre_ += ajoutY;

			currentZoom_ += incrementZoom_;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
	///                       nouvelle cl�ture
	/// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
	///                       nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		if (coinMax.x < 100 && coinMax.y < 100)
			return;

		//translater(glm::ivec2(-(coinMax.y - xMaxCloture_), -(coinMax.x - yMaxCloture_)));
		double dx, dy;
		dx = double(coinMax.x - xMaxCloture_) / xMaxCloture_;
		dy = double(coinMax.y - yMaxCloture_) / yMaxCloture_;
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		//Redimensionnement fenetre virtuelle
		double ajoutX, ajoutY;

		ajoutX = dx*(xMaxFenetre_-xMinFenetre_)*0.5;
		ajoutY = dy*(yMaxFenetre_-yMinFenetre_)*0.5;

		yMinFenetre_ -= ajoutY;
		yMaxFenetre_ += ajoutY;
		xMaxFenetre_ += ajoutX;
		xMinFenetre_ -= ajoutX;

		ajusterRapportAspect();
		mettreAJourCloture();
		mettreAJourProjection();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle d�termin� par deux coins.
	/// Ainsi la r�gion d�limit�e par le rectangle deviendra la fen�tre
	/// virtuelle.  La fen�tre r�sultante est ajust�e pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// S'assurer que coin 1 est le coin sup�rieur droit pour les op�rations
		//dimensions du rectum
		double w = std::abs(coin2.x - coin1.x);
		double h = std::abs(coin2.y - coin1.y);

		//dimensions de la fenetre
		double W = xMaxFenetre_ - xMinFenetre_;
		double H = yMaxFenetre_ - yMinFenetre_;

		//ratio fenetre
		double R = W / H;
		//ratio rectangle
		double r = w / h;
		
		// convertir coin sup�rieur gauche en position fenetre virtuelle
		double decalageX = double(std::min(coin1.x, coin2.x)) / xMaxCloture_*W;
		double decalageY = double(std::min(coin1.y, coin2.y)) / yMaxCloture_*H;

		//Trouver nouvelles dimensions de la fenetre
		if (R > r){
			H = h / yMaxCloture_*H;
			// Deduire W
			W = R*H;
		}
		else{
			W = w / xMaxCloture_*W;
			// Deduire H
			H = W / R;
		}

		//Appliquer les transformations a la fenetre
		yMaxFenetre_ -= decalageY;
		yMinFenetre_ = yMaxFenetre_ - H;
		
		xMinFenetre_ += decalageX;
		xMaxFenetre_ = xMinFenetre_ + W;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle d�limit� par deux coins.
	/// Ainsi la fen�tre virtuelle avant le zoom sera plac�e � l'interieur de
	/// la r�gion d�limit� par le rectangle.  La fen�tre r�sultante est ajust�e
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{

		//dimensions du rectum
		double w = std::abs(coin2.x - coin1.x);
		double h = std::abs(coin2.y - coin1.y);

		//dimensions de la fenetre
		double W = (xMaxFenetre_ - xMinFenetre_);
		double H = (yMaxFenetre_ - yMinFenetre_);

		//ratio fenetre
		double R = W / H;

		//ratio rectangle
		double r = w / h;

		double decalageX = 0.0;
		double decalageY = 0.0;

		//Trouver nouvelles dimensions de la fenetre
		if (R > r){

			//Rajuster le d�calage en Y pour centrer
			decalageY += (1 / r - 1 / R)*W / 2;

			//Transformer W
			W = xMaxCloture_ / w*W;
			//d�duire H par ratio
			H = W / R;

		}
		else{
			
			//Rajuster le d�calage en X pour centrer
			decalageX += (r - R)*H / 2;

			//Transformer H
			H = yMaxCloture_/h *H;
			// Deduire W par ratio
			W = H*R;
		}

		// convertir coin1 en position fenetre virtuelle
		decalageX += double(std::min(coin1.x, coin2.x)) / xMaxCloture_*W;
		decalageY += double(std::min(coin1.y, coin2.y)) / yMaxCloture_*H;

		//Appliquer les transformations a la fenetre
		yMaxFenetre_ += decalageY;
		yMinFenetre_ = yMaxFenetre_ - H;

		xMinFenetre_ -= decalageX;
		xMaxFenetre_ = xMinFenetre_ + W;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de d�placer la fen�tre virtuelle en @a x et en @a y.  Les
	/// d�placement doivent �tre exprim�s en proportion de la fen�tre virtuelle.
	///
	/// @param[in]  deplacementX : le d�placement en @a x.
	/// @param[in]  deplacementY : le d�placement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
			xMinFenetre_ += deplacementX;
			xMaxFenetre_ += deplacementX;
			yMinFenetre_ += deplacementY;
			yMaxFenetre_ += deplacementY;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fen�tre virtuelle en fonction d'un d�placement
	/// en coordonn�es de cl�ture.
	///
	/// @param[in]  deplacement : Le d�placement en coordonn�es de cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	{
		double deplacementX, deplacementY, fx, fy, cx, cy;
		fx = (xMaxFenetre_ - xMinFenetre_);
		fy = (yMaxFenetre_ - yMinFenetre_);
		cx = (xMaxCloture_ - xMinCloture_);
		cy = (yMaxCloture_ - yMinCloture_);
		deplacementX = (double(deplacement.x) / cx*fx);
		deplacementY = (double(deplacement.y) / cy*fy);

		translater(deplacementX, deplacementY);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fen�tre virtuelle sur un point de l'�cran. Le
	/// point de l'�cran est convertit en coordonn�es virtuelles et il devient
	/// le centre de la fen�tre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// � IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{

		GLdouble fx, fy, cx, cy, ratioCloture, ratioFenetre, ajout;
		fx = (xMaxFenetre_ - xMinFenetre_);
		fy = (yMaxFenetre_ - yMinFenetre_);
		cx = (xMaxCloture_ - xMinCloture_);
		cy = (yMaxCloture_ - yMinCloture_);

		ratioCloture = cx / cy;
		ratioFenetre = fx / fy;
		if (fx * cy < fy * cx){
			ajout = (ratioCloture - ratioFenetre)*fx*0.5;
			xMinFenetre_ -= ajout;
			xMaxFenetre_ += ajout;
		}
		else{
			ajout = (1 /ratioCloture - 1 / ratioFenetre)*fy*0.5;
			yMinFenetre_ -= ajout;
			yMaxFenetre_ += ajout;
		}
	}

	glm::ivec2 ProjectionOrtho::obtenirCentreVue(){
		return glm::ivec2((xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
