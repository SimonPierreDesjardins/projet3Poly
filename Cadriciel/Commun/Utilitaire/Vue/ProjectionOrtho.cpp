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


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
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
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
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
	/// Permet de faire un zoom in selon l'incrément de zoom.
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

			currentZoom_ -= 1 / incrementZoom_;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out de 10% selon l'incrément de zoom.
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
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		if (coinMax.x < 100 || coinMax.y < 100)
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
	/// Cette fonction permet d'appliquer la fenêtre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propriétés de la
	/// fenêtre.
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
	/// Permet de faire un zoom in sur un rectangle déterminé par deux coins.
	/// Ainsi la région délimitée par le rectangle deviendra la fenêtre
	/// virtuelle.  La fenêtre résultante est ajustée pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// À IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle délimité par deux coins.
	/// Ainsi la fenêtre virtuelle avant le zoom sera placée à l'interieur de
	/// la région délimité par le rectangle.  La fenêtre résultante est ajustée
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxième coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// À IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de déplacer la fenêtre virtuelle en @a x et en @a y.  Les
	/// déplacement doivent être exprimés en proportion de la fenêtre virtuelle.
	///
	/// @param[in]  deplacementX : le déplacement en @a x.
	/// @param[in]  deplacementY : le déplacement en @a y.
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
	/// Permet de translater la fenêtre virtuelle en fonction d'un déplacement
	/// en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Le déplacement en coordonnées de clôture.
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
	/// Permet de centrer la fenêtre virtuelle sur un point de l'écran. Le
	/// point de l'écran est convertit en coordonnées virtuelles et il devient
	/// le centre de la fenêtre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// À IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
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

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
