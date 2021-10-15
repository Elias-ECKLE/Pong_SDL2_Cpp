#pragma once
#include "define.h"
#include "CVue.h"


class CBalle {

private :


protected:

	int vitesseDplt;
	int vitesseDpltVertical;

	coords position;
	dimensions taille;

	SDL_Rect rectBalle;
	SDL_Surface* pSurfaceBalle;
	SDL_Texture* pTextureBalle;


public:

	//constructeur :
	CBalle();
	CBalle(int x, int y, int w, int h,int v);
	
	~CBalle();


	//accesseurs :
	coords getPos();
	dimensions getTaille();
	SDL_Rect getRectBalle();
	SDL_Surface* getPSurfaceBalle();
	SDL_Texture* getPTextureBalle();

	//mutateurs :
	void setPos(coords position);
	void setTaille(dimensions taille);
	void setRectBalle(SDL_Rect rect);
	void setPSurfaceBalle(SDL_Surface* surface);
	void setPTextureBalle(SDL_Texture* texture);

	//methodes :
	int createTexture(char* cheminIMG, SDL_Renderer* pRenderer);
	void dpltGauche();
	void dpltDroite();
	void dpltGauche_B();
	void dpltGauche_H();
	void dpltDroite_B();
	void dpltDroite_H();
	void checkLimitsBalle(int nb_windowHeight, int nb_separatePixels);
	void dplt(collider collision);







};