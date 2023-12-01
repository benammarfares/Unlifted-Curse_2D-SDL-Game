
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>




int afficher_story(SDL_Surface *screen) {

int done=1;
SDL_Surface *image[2];
SDL_Rect pos;
SDL_Event event;

/*int vol=120;
Mix_Music *music;
music= Mix_LoadMUS("Game/Menu/background-music.mp3");
Mix_VolumeMusic(vol);
Mix_PlayMusic(music,-1);*/

putenv("SDL_VIDEO_CENTERED = 1");

    //load icon

SDL_WM_SetCaption("UNDIFINED CURSE", NULL);
// load menu


int v1=0;
pos.x = 0;
pos.y = 0;

image[0]=IMG_Load("./Game ress/Story/page-1.png");
image[1]=IMG_Load("./Game ress/Story/page-2.png");
image[2]=IMG_Load("./Game ress/Story/page-3.png");


if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
printf("error : %s", Mix_GetError());

while(done){

int  t=0;
SDL_WaitEvent(&event);
SDL_BlitSurface(image[v1], NULL,screen,&pos);
SDL_Flip(screen);
switch(event.type){
    case SDL_QUIT:
        done= 0;
    break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
        case SDLK_ESCAPE:
           SDL_Delay(400);
           return 1;
break;

case SDLK_RIGHT:

 if (v1==0 && t==0){
v1=1;
t=1;
}

else  if (v1==1 && t==0){

v1=2;
t=1;
}

break;


case SDLK_LEFT:
if (v1==2 && t==0) {

v1=1;
t=1;
}
else if (v1==1 && t==0) {

v1=0;
t=1;
}
break ;
        }
break;
}

}
//Mix_FreeMusic(bgm);
SDL_FreeSurface(screen);
SDL_FreeSurface(image[0]);
SDL_FreeSurface(image[1]);
SDL_FreeSurface(image[2]);
//Mix_FreeChunk(soundeffect);
Mix_CloseAudio();



}
