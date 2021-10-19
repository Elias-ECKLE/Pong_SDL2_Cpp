#pragma once
#include<iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>




using namespace std;

//____________________________________________________________________RESSOURCES_____________________________________________________________________
//__________________________________________________DEFINITION DE TOUTES LES INFORMATIONS MODIFIABLES _________________________________________________

// affichage �cran 1000x600
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//MAX SCORE 
#define MAX_SCORE 12
#define COEFF_SCORE 1 //valeur d'incr�mentation � chaque pt marqu�

//FPS 
#define FPS 60
#define MS 1000

//delta de pixels entre chaque point dans le filet du terrain et s�paration limite balle
#define SEPARATE_PIXELS 4
#define SEPARATE_PIXELS_LIMITS 20

#define TITRE_FENETRE "Pong"
#define CHEMIN_SPRITE_JOUEUR1 "../Images/barreJ1.png"
#define CHEMIN_SPRITE_JOUEUR2 "../Images/barreJ2.png"
#define CHEMIN_SPRITE_BALLE "../Images/balle.png"
#define CHEMIN_POLICE_TEXT "../Text/zen-dots/ZenDots-Regular.ttf"

//taille des sprites joueur :
#define WIDTHJOUEUR 31
#define HEIGHTJOUEUR 98
#define SEPARATE_BORDSJ1 20
#define SEPARATE_BORDSJ2 43
#define VITESSEDEPLT 35
#define VITESSE_BALLE 3
#define WIDTHBALLE 15
#define HEIGHTBALLE 15


// taille pour allouer de l'espace � des cha�nes de caract�res d�clar�s sous forme de char*
#define TAILLE 45

//taille police :
#define TAILLE_POLICE 9
#define WIDTH_TEXTE 20
#define HEIGHT_TEXTE 40
//couleur du texte :
#define R_COLOR 255
#define G_COLOR 255
#define B_COLOR 255
#define A_OPACITY 255


//__________________________________________________________STRUCTURES ET ENUMERATIONS____________________________________________________________
typedef struct coords {

	int x;
	int y;
}coords;

typedef struct dimensions {
	int w;
	int h;
}dimensions;

enum class controller { up = 1, down=2, idle=0 };

enum class collider {col_H = 1 ,col_C, col_B, none=0};

