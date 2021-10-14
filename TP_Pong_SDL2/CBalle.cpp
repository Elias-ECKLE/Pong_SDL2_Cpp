#include "CBalle.h"

CBalle::CBalle()
{
	this->position.x = 0;
	this->position.y = 0;
	this->taille.w = 0;
	this->taille.h = 0;

	this->pSurfaceBalle = NULL;
	this->pTextureBalle = NULL;

}

CBalle::CBalle(int x, int y, int w, int h)
{
	this->position.x = x;
	this->position.y = y;
	this->taille.w = w;
	this->taille.h = h;

	this->pSurfaceBalle = NULL;
	this->pTextureBalle = NULL;
}

CBalle::~CBalle()
{
	if (this->pTextureBalle) {
		SDL_DestroyTexture(this->pTextureBalle);
	}
	cout << "Destruction CJoueur faite" << endl;
}

coords CBalle::getPos()
{
	return this->position;
}

dimensions CBalle::getTaille()
{
	return this->taille;
}

SDL_Surface* CBalle::getPSurfaceBalle()
{
	return this->pSurfaceBalle;
}

SDL_Texture* CBalle::getPTextureBalle()
{
	return this->pTextureBalle;
}

void CBalle::setPos(coords position)
{
	this->position = position;
}

void CBalle::setTaille(dimensions taille)
{
	this->taille = taille;
}

void CBalle::setPSurfaceBalle(SDL_Surface* surface)
{
	this->pSurfaceBalle = surface;
}

void CBalle::setPTextureBalle(SDL_Texture* texture)
{
	this->pTextureBalle = texture;
}





int CBalle::createTexture(char* cheminIMG, SDL_Renderer* pRenderer)
{
	this->pSurfaceBalle = IMG_Load(cheminIMG);

	if (!this->pSurfaceBalle) {
		SDL_Log("Unable to set surface: %s", SDL_GetError());
		return 1;
	}
	else {
		this->pTextureBalle = SDL_CreateTextureFromSurface(pRenderer, pSurfaceBalle);
		SDL_FreeSurface(this->pSurfaceBalle);

		if (!this->pTextureBalle) {
			SDL_Log("Unable SDL_CreatetextureFromSurface %s", SDL_GetError());
			return 1;
		}
	}
	SDL_Rect dst_IMG = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	SDL_RenderCopy(pRenderer, pTextureBalle, NULL, &dst_IMG);

	return 0;
}
