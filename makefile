all: main.o menu.o option.o background.o sauvegarde.o Personne.o minimap.o story.o enigme.o enigme_IA.o enig_fichier.o enemie.o XO.o
	gcc main.o menu.o option.o background.o sauvegarde.o Personne.o minimap.o story.o enigme.o enigme_IA.o enig_fichier.o enemie.o XO.o -o Game -lSDL -lSDL_image  -lSDL_ttf -lSDL_mixer 


clean:
	rm -rf *.o

mrproper:
	rm -rf Jeu
