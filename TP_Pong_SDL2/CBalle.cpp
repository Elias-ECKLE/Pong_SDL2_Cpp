#include "CBalle.h"

CBalle::CBalle()
{
	this->position.x = 0;
	this->position.y = 0;
	this->taille.w = 0;
	this->taille.h = 0;

	this->vitesseDplt = 0;
	this->vitesseDpltVertical = 0;

	this->rectBalle= { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceBalle = NULL;
	this->pTextureBalle = NULL;

}

CBalle::CBalle(int x, int y, int w, int h, int v)
{
	this->position.x = x;
	this->position.y = y;
	this->taille.w = w;
	this->taille.h = h;

	this->vitesseDplt = v;
	this->vitesseDpltVertical = v;

	this->rectBalle = { this->position.x,this->position.y, this->taille.w, this->taille.h };
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

SDL_Rect CBalle::getRectBalle()
{
	return this->rectBalle;
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

void CBalle::setRectBalle(SDL_Rect rect)
{
	this->rectBalle = rect;
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
	rectBalle = dst_IMG;
	SDL_RenderCopy(pRenderer, pTextureBalle, NULL, &rectBalle);

	return 0;
}

void CBalle::dpltGauche()
{
	this->position.x -= this->vitesseDplt;
	
}

void CBalle::dpltDroite()
{
	this->position.x += this->vitesseDplt;
}

void CBalle::dpltGauche_B()
{
	this->position.x -= this->vitesseDplt;
	this->position.y += this->vitesseDpltVertical;
}

void CBalle::dpltGauche_H()
{
	this->position.x -= this->vitesseDplt;
	this->position.y -= this->vitesseDpltVertical;

}

void CBalle::dpltDroite_B()
{
	this->position.x += this->vitesseDplt;
	this->position.y += this->vitesseDpltVertical;
}

void CBalle::dpltDroite_H()
{
	this->position.x += this->vitesseDplt;
	this->position.y -= this->vitesseDpltVertical;
}

void CBalle::checkLimitsBalle(int nb_windowHeight, int nb_separatePixels)
{
	if (this->position.y <= 0) {
		this->vitesseDpltVertical = this->vitesseDpltVertical * -1;
	}
	if (this->position.y>=nb_windowHeight-nb_separatePixels) {
		this->vitesseDpltVertical = this->vitesseDpltVertical * -1;
	}
}

void CBalle::dplt(collider collision)
{
	switch (collision) {
		case colG_H :
			this->dpltDroite_B();
		break;

		case colG_C :
			this->dpltDroite();
		break;

		case colG_B:
			this->dpltDroite_H();
		break;


		case colD_H:
			this->dpltGauche_B();
		break;
		
		case colD_C:
			this->dpltGauche();
		break;

		case colD_B:
			this->dpltGauche_H();
		break;



	}
}
