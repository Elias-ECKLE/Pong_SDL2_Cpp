#pragma once
#include<iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

//__________________________________________________DEFINITION DE TOUTES LES INFORMATIONS MODIFIABLES _________________________________________________

// affichage écran 1000x600
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//FPS 
#define FPS 60
#define MS 1000

//delta de pixels entre chaque point dans le filet du terrain
#define SEPARATE_PIXELS 4

#define TITRE_FENETRE "Pong"
#define CHEMIN_SPRITE_JOUEUR1 "../Images/barreJ1.png"
#define CHEMIN_SPRITE_JOUEUR2 "../Images/barreJ2.png"
#define CHEMIN_SPRITE_BALLE "../Images/balle.png"

//taille des sprites joueur :
#define WIDTHJOUEUR 31
#define HEIGHTJOUEUR 98
#define SEPARATE_BORDSJ1 20
#define SEPARATE_BORDSJ2 43
#define VITESSEDEPLT 13
#define WIDTHBALLE 46
#define HEIGHTBALLE 46

// taille pour allouer de l'espace à des chaînes de caractères déclarés sous forme de char*
#define TAILLE 30 




//__________________________________________________________STRUCTURES ET ENUMERATIONS____________________________________________________________
typedef struct coords {

	int x;
	int y;
}coords;

typedef struct dimensions {
	int w;
	int h;
}dimensions;

typedef enum controller {

    upJ1 = 1,
	downJ1,
	upJ2,
	downJ2,
	none

}controller;

