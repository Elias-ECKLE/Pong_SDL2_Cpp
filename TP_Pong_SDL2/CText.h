#pragma once
#include "define.h"

class CText {

private:

protected:
	char* pCheminText;

	coords position;
	dimensions taille;

	TTF_Font* pFont;
	SDL_Surface* pSurfaceText;
	SDL_Texture* pText;
	SDL_Rect rectText;

public:

	//constructeur destructeur
	CText();
	CText(int x, int y, int w, int h, char* pCheminText);
	~CText();

	//accesseurs 
	int getPosX();
	int getPosY();
	int getTailleW();
	int getTailleH();
	TTF_Font* getPFont();
	SDL_Texture* getPText();
	SDL_Rect getRectText();

	//mutateurs 
	void setPFont(TTF_Font* font);
	void setPText(SDL_Texture* texture);
	void setRectText(SDL_Rect rect);


	//methodes
	int createTexture(int scoreJoueur, int taillePolice, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer);




};