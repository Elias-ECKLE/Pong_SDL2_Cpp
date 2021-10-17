#include "CText.h"
#include <charconv>

CText::CText()
{
	this->position.x = 0;
	this->position.y = 0;
	this->taille.w = 0;
	this->taille.h = 0;

	this->pFont = NULL;
	this->pText = NULL;
	this->pSurfaceText = NULL;
	this->rectText = { this->position.x,this->position.y, this->taille.w, this->taille.h };
}

CText::CText(int x, int y, int w, int h)
{
	this->position.x = x;
	this->position.y = y;
	this->taille.w = w;
	this->taille.h = h;

	this->pFont = NULL;
	this->pText = NULL;
	this->pSurfaceText = NULL;
	this->rectText = { this->position.x,this->position.y, this->taille.w, this->taille.h };
}

CText::~CText()
{

	if (this->pText) {
		SDL_DestroyTexture(this->pText);
	}
	std::cout << "Destruction CText faite" << std::endl;

}

int CText::getPosX()
{
	return this->position.x;
}

int CText::getPosY()
{
	return this->position.y;
}

int CText::getTailleW()
{
	return this->taille.w;
}

int CText::getTailleH()
{
	return this->taille.h;
}

TTF_Font* CText::getPFont()
{
	return this->pFont;
}

SDL_Texture* CText::getPText()
{
	return this->pText;
}

SDL_Rect CText::getRectText()
{
	return this->rectText;
}

void CText::setPFont(TTF_Font* font)
{
	this->pFont = font;
}

void CText::setPText(SDL_Texture* texture)
{
	this->pText = texture;
}

void CText::setRectText(SDL_Rect rect)
{
	this->rectText = rect;
}

int CText::createTexture(const char* cheminPolice, int nbScore, int taillePolice, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* pRenderer)
{

	char num_char[10 + sizeof(char)];
	sprintf_s(num_char, "%d", nbScore);
	//std::printf("num_char: %s \n", num_char);

	SDL_Color color = { r, g, b};
	this->pFont = TTF_OpenFont(cheminPolice,taillePolice);
	this->pSurfaceText = TTF_RenderText_Solid(pFont, num_char, color);

	if (pFont==nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
	}

	if (!this->pSurfaceText) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
		return 1;
	}
	else {
		this->pText = SDL_CreateTextureFromSurface(pRenderer, this->pSurfaceText);
		SDL_FreeSurface(this->pSurfaceText);

		if (!this->pText) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
			return 1;
		}
		else {
			SDL_QueryTexture(this->pText, nullptr, nullptr, &this->taille.w, &this->taille.h);
			SDL_RenderCopy(pRenderer, pText, NULL, &this->rectText);
		}
	}

	TTF_CloseFont(pFont);
	return 0;
}
