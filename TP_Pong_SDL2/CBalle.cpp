#include "CBalle.h"

CBalle::CBalle()
{
	this->position.x = 0;
	this->position.y = 0;
	this->taille.w = 0;
	this->taille.h = 0;

	this->vitesseDpltX = 0;
	this->vitesseDpltY = 0;
	this->collisionBalleJoueur = collider::none;
	this->pCheminIMGBalle = NULL;

	this->rectBalle= { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceBalle = NULL;
	this->pTextureBalle = NULL;

}

CBalle::CBalle(int x, int y, int w, int h, int v, char* pCheminIMGBalle)
{
	this->position.x = x;
	this->position.y = y;
	this->taille.w = w;
	this->taille.h = h;

	this->vitesseDpltX = v;
	this->vitesseDpltY = v;
	this->collisionBalleJoueur = collider::none;
	this->pCheminIMGBalle = pCheminIMGBalle;

	this->rectBalle = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	this->pSurfaceBalle = NULL;
	this->pTextureBalle = NULL;
}

CBalle::~CBalle()
{
	if (this->pTextureBalle) {
		SDL_FreeSurface(this->pSurfaceBalle);
		SDL_DestroyTexture(this->pTextureBalle);
	}

	cout << "Destruction CJoueur faite" << endl;
}

coords CBalle::getPos()
{
	return this->position;
}

int CBalle::getXPos()
{
	return this->position.x;
}

int CBalle::getYPos()
{
	return this->position.y;
}

dimensions CBalle::getTaille()
{
	return this->taille;
}

int CBalle::getWTaille()
{
	return this->taille.w;
}

int CBalle::getHTaille()
{
	return this->taille.h;
}

SDL_Rect CBalle::getRectBalle()
{
	return this->rectBalle;
}

collider CBalle::GetColBalleJoueur()
{
	return this->collisionBalleJoueur;
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





int CBalle::createTexture(SDL_Renderer* pRenderer)
{
	this->pSurfaceBalle = IMG_Load(this->pCheminIMGBalle);

	if (!this->pSurfaceBalle) {
		SDL_Log("Unable to set surface: %s", SDL_GetError());
		return 1;
	}
	else {
		this->pTextureBalle = SDL_CreateTextureFromSurface(pRenderer, pSurfaceBalle);

		if (!this->pTextureBalle) {
			SDL_Log("Unable SDL_CreatetextureFromSurface_Balle %s", SDL_GetError());
			return 1;
		}
	}
	SDL_Rect dst_IMG = { this->position.x,this->position.y, this->taille.w, this->taille.h };
	rectBalle = dst_IMG;
	SDL_RenderCopy(pRenderer, pTextureBalle, NULL, &rectBalle);

	return 0;
}

int CBalle::respawnBalle(SDL_Renderer* pRenderer, int nb_WindowWidth, int nb_WindowHeight)
{

	int returnError = 0;
	int centreXBalle = this->position.x + this->taille.w / 2;
	int centreXTerrain = nb_WindowWidth / 2 - this->taille.w / 2;
	int centreYTerrain = nb_WindowHeight / 2 - this->taille.h / 2;

	//si la balle sort du terrain alors on respawn
	if (centreXBalle <0 || centreXBalle> nb_WindowWidth) {

		returnError = this->createTexture(pRenderer);
		this->position.x = centreXTerrain;
		this->position.y = centreYTerrain;
		cout << "respawn balle" << endl;
		this->inversDirection();
	}

	return returnError;
}






void CBalle::checkLimitsBalle(int nb_windowHeight, int nb_separatePixels)
{
	if (this->position.y <= 0) {
		this->vitesseDpltY = this->vitesseDpltY * -1;
	}
	if (this->position.y>=nb_windowHeight-nb_separatePixels) {
		this->vitesseDpltY = this->vitesseDpltY * -1;
	}
}



collider CBalle::dpltBalle(CJoueur* joueur)
{
	SDL_Rect rectBalle = this->rectBalle;
	SDL_Rect rectJoueur = joueur->getRectJoueur();

	int balleYCentre = this->position.y + this->taille.h / 2;
	int joueurYCentre = joueur->getYPos() + joueur->getHTaille() / 2;
	//int joueur2YCentre = joueur2->getYPos() + joueur2->getHTaille() / 2;

	if (this->position.x >= joueur->getXPos() && this->position.x <= joueur->getXPos() + joueur->getWTaille() && this->position.y >= joueur->getYPos() && this->position.y <= joueur->getYPos() + joueur->getHTaille()) { //si collision alors 

		dpltX();
		dpltY();
		int d = joueurYCentre - this->position.y; //distance entre le centre du paddle et l'impact de la balle dessus
		this->vitesseDpltX += d * 0.1;
		this->inversDirection();
	}
	else {
		dpltX();
	}


	
	return this->collisionBalleJoueur;
}

void CBalle::dpltX()
{
	this->position.x += this->vitesseDpltX;
}

void CBalle::dpltY()
{
	this->position.y += this->vitesseDpltY;
}



void CBalle::butJoueur(CJoueur* J1, CJoueur* J2, int ptScore, int nb_WindowWidth, int nb_WindowHeight)
{
	int returnError = 0;
	int centreXBalle = this->position.x + this->taille.w / 2;
	int centreXTerrain = nb_WindowWidth / 2 - this->taille.w / 2;
	int centreYTerrain = nb_WindowHeight / 2 - this->taille.h / 2;

	//si la balle sort du terrain alors on ajoute un pt à l'adversaire
	if (centreXBalle <0) {
		J2->addScore(ptScore);
	}
	if (centreXBalle > nb_WindowWidth) {
		J1->addScore(ptScore);
	}

}
void CBalle::inversDirection()
{
	//on inverse la direction de la balle (notamment à chaque collision avec un joueur :
	this->vitesseDpltX= this->vitesseDpltX * -1;	

}



