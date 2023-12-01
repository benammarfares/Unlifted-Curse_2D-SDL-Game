#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Personne.h"
#include "background.h"
#include "enemie.h"
#include "minimap.h"
#include "enigme_IA.h"
#include "enigme.h"//aleatoire sans fichier
#include "menu.h"
#include "option.h"
#include "enig_fichier.h"
#include "sauvegarde.h"
#include "story.h"


int arduinoWriteData(int x);
int arduinoReadData(int *x);
int checkCollidsionBoundingBox(SDL_Rect a, SDL_Rect b);

int main( int argc, char *argv[ ] )
{

int directionSDL=0; //0:standby 1 : moving right 2 : moving left
int directionArduino=0; //0:standby 1 : moving right 2 : moving left

int game=1;
char received;
int collisionRightSide = 0;
int collisionLeftSide = 0;


SDL_Event event;
SDL_Surface *screen=NULL,*perso=NULL,*crack=NULL;
SDL_Rect positionperso,poscrack1,poscrack2;


//init Link with arduino
system("stty -F /dev/ttyACM0 9600 -parenb cs8 -cstopb");



    //init SDL Video
    SDL_Init(SDL_INIT_VIDEO);

    perso=IMG_Load("perso.jpg");
    crack=IMG_Load("obstacle.png");
    screen = SDL_SetVideoMode(600, 300, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    positionperso.x=20;
    positionperso.y=150;
    positionperso.w=perso->w;
    positionperso.h=perso->h;

    poscrack1.x=590;
    poscrack1.y=0;
    poscrack1.w=crack->w;
    poscrack1.h=crack->h;

    poscrack2.x=10;
    poscrack2.y=0;
    poscrack2.w=crack->w;
    poscrack2.h=crack->h;

    if(screen == NULL)
    {
        printf("Erreur Loading Image background.bmp\n");
        return EXIT_FAILURE;
    }

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
    while (game)
    {
      //input from SDL
      while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                game = 0;
                break;
            case SDL_KEYDOWN:
            {

                if (event.key.keysym.sym == SDLK_RIGHT)
                  directionSDL = 1;

                if (event.key.keysym.sym == SDLK_LEFT)
                  directionSDL = 2;

            }
            break;
            case SDL_KEYUP:
              directionSDL=0;
            break;

            }
          }
          //input from arduino
		.............
	     switch (received)
		{
		.......
		.......
		.......
		}

            //update ( from SDL events and ARDUINO events)

            //check collision
            if(positionperso.x+positionperso.w<poscrack1.x)
                collisionRightSide=0;
            else
                collisionRightSide=1;
            if(positionperso.x > poscrack2.x + poscrack2.w)
                collisionLeftSide=0;
            else
                collisionLeftSide=1;


            if(collisionRightSide == 1){
              printf("\n COLLISION RIGHT SENDING 1 TO SERIAL");
              //........................

            } else if(collisionLeftSide == 1){
              printf("\n COLLISION LEFT SENDING 2 TO SERIAL");
            //..........................

            } else {
            printf("\n NO COLLISION SENDING 0 TO SERIAL");
            //..........................
            }

            if((directionSDL == 1 ) && !collisionRightSide){
                 positionperso.x += 1;

            }
            if ((directionSDL == 2 ) && !collisionLeftSide){
              positionperso.x -= 1;
            }

            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255,255, 255));
            SDL_BlitSurface(perso ,NULL, screen, &positionperso );
            SDL_BlitSurface(crack ,NULL, screen, &poscrack1 );
            SDL_BlitSurface(crack ,NULL, screen, &poscrack2 );
            SDL_Flip( screen );
            //printf("\nReceived from Arduino :%d ",received);
    }


    SDL_FreeSurface(perso);
    SDL_FreeSurface(crack);
    SDL_Quit();
    return 0;
}


int arduinoWriteData(int x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;

    f=fopen(chemin,"w");
    if(f == NULL)
        return(-1);

    fprintf(f,"%d",x);
    fclose(f);

    return(0);
}

int arduinoReadData(int *x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;
    char c;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);

    fscanf(f,"%d",x);

    fclose(f);

    return(0);
}

