#pragma once
#include "define.h"
#include "CVue.h"


class CBalle {

private :


protected:

	coords position;
	dimensions taille;

	SDL_Surface* pSurfaceBalle;
	SDL_Texture* pTextureBalle;


public:

	//constructeur :
	CBalle();
	CBalle(int x, int y, int w, int h);
	
	~CBalle();


	//accesseurs :
	coords getPos();
	dimensions getTaille();
	SDL_Surface* getPSurfaceBalle();
	SDL_Texture* getPTextureBalle();

	//mutateurs :
	void setPos(coords position);
	void setTaille(dimensions taille);
	void setPSurfaceBalle(SDL_Surface* surface);
	void setPTextureBalle(SDL_Texture* texture);

	//methodes :
	int createTexture(char* cheminIMG, SDL_Renderer* pRenderer);







};