#include "define.h"
#include "CVue.h"
#include "CJoueur.h"
#include "CBalle.h"


using namespace std;

int main(int argc, char** argv)
{

    //___________________________________CREATION FENETRE SDL______________________________________
 
    /* Initialisation simple */
    CVue fenetre(WINDOW_HEIGHT,WINDOW_WIDTH,SEPARATE_PIXELS, FPS, MS);
    fenetre.SDL_Inits();
    fenetre.SDL_InitImg();
    /* Création de la fenêtre */ //on utilisée la version surchagée de fenetre afin d'ajouter un titre 
    char* pTitreFenetre = new char[TAILLE];
    strcpy_s(pTitreFenetre, TAILLE, TITRE_FENETRE);
    fenetre.createWindow(pTitreFenetre);    
   
    
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
    int nb = 1;



    do
    {
        frameStart = SDL_GetTicks();

        fenetre.createTerrain();
        J1.createTexture(pCheminIMG1, fenetre.getPRenderer());
        J2.createTexture(pCheminIMG2, fenetre.getPRenderer());

        balle.createTexture(pCheminIMGBalle, fenetre.getPRenderer());
        balle.checkLimitsBalle(WINDOW_HEIGHT,SEPARATE_PIXELS_LIMITS);
        balle.dplt(colD_C);

        SDL_Rect rect1 = J1.getRectJoueur();
        SDL_Rect rect2 = balle.getRectBalle();

        if (SDL_HasIntersection(&rect1,&rect2)){
            cout<<"collision"<<endl;
        }

        fenetre.affichRendu();

        while (SDL_PollEvent(&events))
        {



            switch (events.type)
            {
                case SDL_QUIT:
                    fenetre.isOpen = SDL_FALSE;
                break;

                case SDL_KEYDOWN :
                    switch (events.key.keysym.sym) {
                        case SDLK_z:
                            J1.setControl(upJ1);
                        break;  
                        case SDLK_s:
                            J1.setControl(downJ1);
                        break;
                        case SDLK_UP:
                            J2.setControl(upJ2);
                        break;
                        case SDLK_DOWN:
                            J2.setControl(downJ2);
                        break;
                        default : 
                            J1.setControl(none);
                            J2.setControl(none);
                        break;
                    }
                break;
            }

            if (J1.getControl()==upJ1) {
                J1.depltHaut(VITESSEDEPLT);
            }
            else if (J1.getControl()==downJ1) {
                J1.depltBas(VITESSEDEPLT,WINDOW_HEIGHT);
            }
            else{
                J1.setControl(none);
            }

            if (J2.getControl() == upJ2) {
                J2.depltHaut(VITESSEDEPLT);
            }
            else if (J2.getControl() == downJ2) {
                J2.depltBas(VITESSEDEPLT,WINDOW_HEIGHT);
            }
            else {
                J2.setControl(none);
            }

            /*
            if (nb==10) {
                fenetre.isOpen = SDL_FALSE;
            }
            */

       
        }
        fenetre.nettoyerEcran();
   
        frameTime = SDL_GetTicks() - frameStart;

        




    } while (fenetre.isOpen);








    //____________________________________LIBERATION MEMOIRE________________________________________

    //libération mémoire 
    delete[] pTitreFenetre;
    //les pointeurs SDL sont libérés dans le destructeur de la classe CVue
    




    




    return 0;
}
