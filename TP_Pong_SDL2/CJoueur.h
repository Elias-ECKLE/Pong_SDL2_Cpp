#pragma once
#include "define.h"
#include "CVue.h"

//une classe pour le joueur

class CJoueur{

private:


protected:
	int nb_score;
	coords position;
	dimensions taille;
	controller control;

	SDL_Surface *pSurfaceJoueur;
	SDL_Texture *pTextureJoueur;



public:

	//constructeur :
	CJoueur();
	CJoueur(int x, int y, int w, int h);

	//constructeur de copie :
	CJoueur(CJoueur& joueur);
	//destructeur :
	~CJoueur();


	//accesseurs :
	int getNbScore();
	coords getPos();
	dimensions getTaille();
	controller getControl();
	SDL_Surface* getPSurfaceJoueur();
	SDL_Texture* getPTextureJoueur();

	//mutateurs :
	void setNbScore(int nb_score);
	void setPos(coords position);
	void setTaille(dimensions taille);
	void setControl(controller controls);
	void setPSurfaceJoueur(SDL_Surface* surfaceJ);
	void setPTextureJoueur(SDL_Texture* tectureJ);


	//methodes :
	int createTexture(char* cheminIMG, SDL_Renderer* pRenderer);
	void depltHaut(int vitesse);
	void depltBas(int vitesse,int nb_WindowHeight);

	

};
