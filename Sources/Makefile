# Programme creer par Florian lacour le 19/09/14
# ce programme permet de compiler des source en C
# contact :
# creer a l'aide de vim
#version 1.0
#merci



#definition des cibles particuliére
.PHONY: clean,mrpropre

#desactivation ds regles implicite
.suffix:

#definition des variables
cc=gcc
EXEC= main
FlagVoulu= -W  -lm -g -pthread
#nom des fonciton des fonction sans leurs extenssion
#(pour le script mais le fichier en possede une en realiter) nom du main
nomMain=main
main=$(nomMain:=.o)

#nom de la bibliotheque (le .h et  .c doivent avoir le meme nom :) )
# et toujouts ps d'extenssion (pour le script mais le fichier en possede une en realiter)

nomBibliotheque=menu
BibliothequeH=$(nomBibliotheque:=.h)
BibliothequeO=$(nomBibliotheque:=.o)

nomBibliotheque2=echangeur
Bibliotheque2H=$(nomBibliotheque:=.h)
Bibliotheque2O=$(nomBibliotheque:=.o)



# ecplication pour la suite
# $^ => toute les depenance
#$> premiére dependance de la liste de dependance
#$@: nom de la cible
# cible: dependance dependance
# %.o: %c => faire les *.o a l'aide .c quelque soi leur noms




$(EXEC):$(main) menu.o echangeur.o linkedList.o serveur.o voiture.o
	@echo "\n"
	$(cc) $^ -o $(EXEC) $(FlagVoulu)
	@echo "\n \n \n"
#le main necessite le .h donc:
$(main): echangeur.h menu.h linkedList.h structures.h serveur.h voiture.h

%.o: %.c
	@echo "\n"
	@echo "generation de la bibliotheque," $@ "\n grace a la source "  $<

	$(cc) -c $< -o $@  $(FlagVoulu)





#supression des fichier temporaire
clean:
	@echo "destruction de tout le fichier temporaire ( il restera l'executable)"
	rm -rf *.o *.c~ *.h~ Makefile~
#supression de tout les fichier sauf les source
mrpropre : clean
	@echo "destruction de tous sauf les source"
	rm -rf $(EXEC)
run: $(EXEC)
	@echo "\n execution du programme"
	./$(EXEC)
