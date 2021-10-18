#include "define.h"
#include "CVue.h"
#include "CJoueur.h"
#include "CBalle.h"
#include "CText.h"


using namespace std;

int main(int argc, char** argv)
{

    //___________________________________CREATION FENETRE SDL______________________________________
 
    /* Initialisation simple */
    CVue fenetre(WINDOW_HEIGHT,WINDOW_WIDTH,SEPARATE_PIXELS, FPS, MS);
    fenetre.SDL_Inits();
    fenetre.SDL_InitImg();
    fenetre.SDL_InitText();
    /* Création de la fenêtre */ //on utilisée la version surchagée de fenetre afin d'ajouter un titre 
    char* pTitreFenetre = new char[TAILLE];
    strcpy_s(pTitreFenetre, TAILLE, TITRE_FENETRE);
    fenetre.createWindow(pTitreFenetre);   


    //______________________________________GENERATION TEXTE_______________________________________
    char* pCheminPoliceTexte = new char[TAILLE];
    strcpy_s(pCheminPoliceTexte, TAILLE, CHEMIN_POLICE_TEXT);
    char* pTexte = new char[TAILLE];
    strcpy_s(pTexte, TAILLE, "Hello World!");

    //texte J1
    int WINDOW_X = WINDOW_WIDTH / 2;
    CText ScoreJ1(WINDOW_X/2,10,WIDTH_TEXTE,HEIGHT_TEXTE);
    //texte J2
    CText ScoreJ2(WINDOW_WIDTH*0.75, 10, WIDTH_TEXTE, HEIGHT_TEXTE);

   
    
    //_______________________________GENERATIONS DES DEUX JOUEURS__________________________________
    
    // J1
    CJoueur J1(SEPARATE_BORDSJ1, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2, WIDTHJOUEUR, HEIGHTJOUEUR);
    char* pCheminIMG1 = new char[TAILLE];
    strcpy_s(pCheminIMG1, TAILLE, CHEMIN_SPRITE_JOUEUR1);
 
    //J2
    CJoueur J2(WINDOW_WIDTH-SEPARATE_BORDSJ2,WINDOW_HEIGHT / 2-HEIGHTJOUEUR/2, WIDTHJOUEUR, HEIGHTJOUEUR);
    char* pCheminIMG2 = new char[TAILLE];
    strcpy_s(pCheminIMG2, TAILLE, CHEMIN_SPRITE_JOUEUR2);



    //_________________________________GENERATION DE LA BALLE______________________________________
    CBalle balle(WINDOW_WIDTH / 2 - WIDTHBALLE / 2, WINDOW_HEIGHT / 2, WIDTHBALLE, HEIGHTBALLE, VITESSE_BALLE);
    char* pCheminIMGBalle = new char[TAILLE];
    strcpy_s(pCheminIMGBalle, TAILLE, CHEMIN_SPRITE_BALLE);



    

    //_____________________________________BOUCLE DE JEU___________________________________________
    SDL_Event events;
    Uint32 frameStart;
    int frameTime;
    //int nb = 1;
    balle.inversDirection();

    do
    {
        frameStart = SDL_GetTicks();


        //Affichage :
        fenetre.createTerrain();
        J1.createTexture(pCheminIMG1, fenetre.getPRenderer());
        J2.createTexture(pCheminIMG2, fenetre.getPRenderer());
        balle.createTexture(pCheminIMGBalle, fenetre.getPRenderer());
        ScoreJ1.createTexture(pCheminPoliceTexte, J1.getNbScore(), TAILLE_POLICE, R_COLOR, G_COLOR, B_COLOR, A_OPACITY, fenetre.getPRenderer());
        ScoreJ2.createTexture(pCheminPoliceTexte, J2.getNbScore(), TAILLE_POLICE, R_COLOR, G_COLOR, B_COLOR, A_OPACITY, fenetre.getPRenderer());


        //Gestion des mécaniques :
        //on regarde s'il y a une collision 
        balle.collision(J1, J2);
        //selon le résultat on déplace la balle et on check si la balle n'atteint pas les deux bords horizontaux, si oui on inverse sa diretion sur l'axe vertical
        balle.checkLimitsBalle(WINDOW_HEIGHT, SEPARATE_PIXELS_LIMITS);
        balle.dpltCollision();
        //si un joueur marque chez l'adversaire
        balle.butJoueur(J1, J2, COEFF_SCORE, WINDOW_WIDTH, WINDOW_HEIGHT);
        //si la balle sort du terrain on la respawn
        balle.respawnBalle(pCheminIMGBalle, fenetre.getPRenderer(), WINDOW_WIDTH,WINDOW_HEIGHT);
        //et on replace les joueurs au centre :
        //J1.respawnJoueur(SEPARATE_BORDSJ1, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2);
        //J2.respawnJoueur(WINDOW_WIDTH - SEPARATE_BORDSJ2, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2);


        //enfin on affiche les modifs 
        fenetre.affichRendu();


        //boucle d'événments afin de gérer l'ensemble des inputs sdl
        while (SDL_PollEvent(&events))
        {
            //GESTION DES INPUTS J1 & DE FERMETURE FENETRE
            switch (events.type){
                case SDL_QUIT:
                    fenetre.setIsOpen(SDL_FALSE);
                break;

                case SDL_KEYDOWN :
                    switch (events.key.keysym.sym) {
                        case SDLK_z:
                            J1.handleEvent(controller::up,VITESSEDEPLT,WINDOW_HEIGHT);
                        break;  
                        case SDLK_s:
                            J1.handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                        default:
                            J1.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    }
                break;

                case SDL_MOUSEMOTION : //on ajoute une catégorie déplacement souris car par défaut elle fait bouger le joueur malgré le cas KEYDOWN
                    J1.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            }

            //GESTION DES INPUTS J2
            switch (events.type) {
                case SDL_KEYDOWN:
                    switch (events.key.keysym.sym) {
                    case SDLK_UP:
                        J2.handleEvent(controller::up, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    case SDLK_DOWN:
                        J2.handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    default:
                        J2.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                        break;
                    }
                break;
                case SDL_MOUSEMOTION: //on ajoute une catégorie déplacement souris car par défaut elle fait bouger le joueur malgré le cas KEYDOWN
                    J2.handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
             }

           // SCORE MAXIMAL ATTEIGNABLE AVT FIN DU JEU
            if (J1.getNbScore()==MAX_SCORE || J2.getNbScore()==MAX_SCORE) {
                fenetre.setIsOpen(SDL_FALSE);
            }
            
        }


        //SDL_Delay(MS / FPS);

        fenetre.nettoyerEcran();
        frameTime = SDL_GetTicks() - frameStart;

    } while (fenetre.getIsOpen());




    //____________________________________LIBERATION MEMOIRE________________________________________

    //libération mémoire 
    delete[] pTitreFenetre;
    delete[] pCheminIMG1;
    delete[] pCheminIMG2;
    delete[] pCheminIMGBalle;
    delete[] pTexte;
    delete[] pCheminPoliceTexte;
    //les pointeurs SDL sont libérés dans le destructeur de la classe CVue
    




    




    return 0;
}
