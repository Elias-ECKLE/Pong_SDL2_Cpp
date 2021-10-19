#include "define.h"

#include "CVue.h"
#include "CJoueur.h"
#include "CBalle.h"
#include "CText.h"

int initialisation(CVue *fenetre, char* pTitreFenetre);
void handleEvents(CVue* fenetre, CJoueur* J1, CJoueur* J2);
int update(CVue* fenetre, CJoueur* J1, CJoueur* J2, CBalle* balle);
void affichage(CVue* fenetre, CJoueur* J1, CJoueur* J2, CBalle* balle, CText* ScoreJ1, CText* ScoreJ2);


int main(int argc, char** argv)
{

    char* pTitreFenetre = new char[TAILLE];
    strcpy_s(pTitreFenetre, TAILLE, TITRE_FENETRE);

    char* pCheminPoliceTexte = new char[TAILLE];
    strcpy_s(pCheminPoliceTexte, TAILLE, CHEMIN_POLICE_TEXT);

    char* pCheminIMG1 = new char[TAILLE];
    strcpy_s(pCheminIMG1, TAILLE, CHEMIN_SPRITE_JOUEUR1);

    char* pCheminIMG2 = new char[TAILLE];
    strcpy_s(pCheminIMG2, TAILLE, CHEMIN_SPRITE_JOUEUR2);

    char* pCheminIMGBalle = new char[TAILLE];
    strcpy_s(pCheminIMGBalle, TAILLE, CHEMIN_SPRITE_BALLE);

    char* pTexte = new char[TAILLE];
    strcpy_s(pTexte, TAILLE, "Hello World!");


    //___________________________________________ DECLARATION :________________________________________________________
    int WINDOW_X = WINDOW_WIDTH / 2;

    CVue fenetre(WINDOW_HEIGHT, WINDOW_WIDTH, SEPARATE_PIXELS, FPS, MS);
    CText ScoreJ1(WINDOW_X / 2, 10, WIDTH_TEXTE, HEIGHT_TEXTE, pCheminPoliceTexte);
    CText ScoreJ2(WINDOW_WIDTH * 0.75, 10, WIDTH_TEXTE, HEIGHT_TEXTE, pCheminPoliceTexte);
    CJoueur J1(SEPARATE_BORDSJ1, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2, WIDTHJOUEUR, HEIGHTJOUEUR,pCheminIMG1);
    CJoueur J2(WINDOW_WIDTH - SEPARATE_BORDSJ2, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2, WIDTHJOUEUR, HEIGHTJOUEUR,pCheminIMG2);
    CBalle balle(WINDOW_WIDTH / 2 - WIDTHBALLE / 2, WINDOW_HEIGHT / 2, WIDTHBALLE, HEIGHTBALLE, VITESSE_BALLE, pCheminIMGBalle);


    //_________________________________________  INITIALISATION___________________________________________________
    initialisation(&fenetre, pTitreFenetre);



    //____________________________________________BOUCLE DE JEU___________________________________________
    


    do
    {

        //_____________________________________________INPUTS_________________________________________________
        handleEvents(&fenetre, &J1, &J2);

        //____________________________________________ UPDATES_______________________________________________
        update(&fenetre, &J1, &J2, &balle);

        //____________________________________________AFFICHAGES_____________________________________________
        affichage(&fenetre, &J1, &J2, &balle, &ScoreJ1, &ScoreJ2);


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





int initialisation(CVue *fenetre, char* pTitreFenetre) {
    fenetre->SDL_Inits();
    fenetre->SDL_InitImg();
    fenetre->SDL_InitText();
    fenetre->createWindow(pTitreFenetre);

    return 0;
}

void handleEvents(CVue *fenetre, CJoueur* J1, CJoueur* J2) {
    //boucle d'événments afin de gérer l'ensemble des inputs sdl
    while (SDL_PollEvent(&fenetre->events))
    {
        //GESTION DES INPUTS J1 & DE FERMETURE FENETRE
        switch (fenetre->events.type) {
        case SDL_QUIT:
            fenetre->setIsOpen(SDL_FALSE);
            break;

        case SDL_KEYDOWN:
            switch (fenetre->events.key.keysym.sym) {
            case SDLK_z:
                J1->handleEvent(controller::up, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            case SDLK_s:
                J1->handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            default:
                J1->handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            }
            break;

        case SDL_MOUSEMOTION: //on ajoute une catégorie déplacement souris car par défaut elle fait bouger le joueur malgré le cas KEYDOWN
            J1->handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
            break;
        }

        //GESTION DES INPUTS J2
        switch (fenetre->events.type) {
        case SDL_KEYDOWN:
            switch (fenetre->events.key.keysym.sym) {
            case SDLK_UP:
                J2->handleEvent(controller::up, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            case SDLK_DOWN:
                J2->handleEvent(controller::down, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            default:
                J2->handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
                break;
            }
            break;
        case SDL_MOUSEMOTION: //on ajoute une catégorie déplacement souris car par défaut elle fait bouger le joueur malgré le cas KEYDOWN
            J2->handleEvent(controller::idle, VITESSEDEPLT, WINDOW_HEIGHT);
            break;
        }

        // SCORE MAXIMAL ATTEIGNABLE AVT FIN DU JEU
        if (J1->getNbScore() == MAX_SCORE || J2->getNbScore() == MAX_SCORE) {
            fenetre->setIsOpen(SDL_FALSE);
        }

    }
}

int update(CVue* fenetre, CJoueur* J1, CJoueur* J2, CBalle* balle) {

    //Gestion des mécaniques :
       //on regarde s'il y a une collision 
    balle->dpltBalle(J1);
    balle->dpltBalle(J2);
    //selon le résultat on déplace la balle et on check si la balle n'atteint pas les deux bords horizontaux, si oui on inverse sa diretion sur l'axe vertical
    balle->checkLimitsBalle(WINDOW_HEIGHT, SEPARATE_PIXELS_LIMITS);
    //balle->dpltCollision();
    //si un joueur marque chez l'adversaire
    balle->butJoueur(J1, J2, COEFF_SCORE, WINDOW_WIDTH, WINDOW_HEIGHT);
    //si la balle sort du terrain on la respawn
    balle->respawnBalle(fenetre->getPRenderer(), WINDOW_WIDTH, WINDOW_HEIGHT);
    //et on replace les joueurs au centre :
    //J1.respawnJoueur(SEPARATE_BORDSJ1, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2);
    //J2.respawnJoueur(WINDOW_WIDTH - SEPARATE_BORDSJ2, WINDOW_HEIGHT / 2 - HEIGHTJOUEUR / 2);

    return 0;
}

void affichage(CVue *fenetre, CJoueur *J1, CJoueur *J2, CBalle* balle,CText *ScoreJ1, CText *ScoreJ2) {
    //Affichage :
    fenetre->createTerrain();
    J1->createTexture(fenetre->getPRenderer());
    J2->createTexture(fenetre->getPRenderer());
    balle->createTexture(fenetre->getPRenderer());
    ScoreJ1->createTexture(J1->getNbScore(), TAILLE_POLICE, R_COLOR, G_COLOR, B_COLOR, A_OPACITY, fenetre->getPRenderer());
    ScoreJ2->createTexture(J2->getNbScore(), TAILLE_POLICE, R_COLOR, G_COLOR, B_COLOR, A_OPACITY, fenetre->getPRenderer());

    //enfin on affiche les modifs 
    fenetre->affichRendu();

    SDL_Delay(MS / FPS);
    fenetre->nettoyerEcran();

}

