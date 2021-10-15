#pragma once
#include "define.h"

using namespace std;

class CVue {



private:
	int nb_separationPixels; // séparation entre chaque pixesl formant le filet du terrain
	SDL_Window* pWindow; //pointeur pointant sur paramètres window



protected:
	int nb_windowHeight;
	int nb_windowWidth;
	bool beginPlay;

	int nb_fps;
	int nb_frameDelay;
	SDL_Renderer* pRenderer;//pointeur pointant sur paramètres renderer



public:
	SDL_bool isOpen;

	//constructeurs
	CVue();
	CVue(int nb_windowHeight, int nb_windowWidth, int nb_SeparatPixels, int nb_fps, int nb_ms);

	//constructeur de copie 
	CVue(CVue &vue);

	//destructeur :
	~CVue();


	//accesseurs 
	SDL_Window* getPWindow()const;
	SDL_Renderer* getPRenderer()const;
	SDL_bool getIsOpen()const;
	
	int getNb_WindowHeight()const;
	int getNb_Fps()const;
	int getNb_FrameDelay()const;
	int getNb_WindowWidth()const;
	bool getBeginPlay()const;


	//mutateurs 
	void setPWindow(SDL_Window* window);
	void setPRenderer(SDL_Renderer* renderer);
	void setIsOpen(SDL_bool open);
	void setNb_WindowHeight(int windowHeight);
	void setNb_WindowWidth(int windowWidth);
	void setBeginPlay(bool isBeginPlay);


	//methodes :
	void SDL_Inits();
	int SDL_InitImg();
	int createWindow();
	int createWindow(char* pTitreFenetre); //surchage afin d'ajouter un titre à la fenetre
	void createTerrain(); //créer le filet séparant le terrain en deux
	void nettoyerEcran();
	void delay(int duree);
	void affichRendu();



};

