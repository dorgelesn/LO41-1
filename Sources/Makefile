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
FlagVoulu= -W  -lm -g
#nom des fonciton des fonction sans leurs extenssion
#(pour le script mais le fichier en possede une en realiter) nom du main
nomMain=main
main=$(nomMain:=.o)

#nom de la bibliotheque (le .h et  .c doivent avoir le meme nom :) )
# et toujouts ps d'extenssion (pour le script mais le fichier en possede une en realiter)

nomBibliotheque=menu
BibliothequeH=$(nomBibliotheque:=.h)
BibliothequeO=$(nomBibliotheque:=.o)







# ecplication pour la suite
# $^ => toute les depenance
#$> premiére dependance de la liste de dependance
#$@: nom de la cible
# cible: dependance dependance
# %.o: %c => faire les *.o a l'aide .c quelque soi leur noms




$(EXEC):$(main) $(BibliothequeO)

	$(cc) $^ -o $(EXEC) $(FlagVoulu)

#le main necessite le .h donc:
$(main): $(BibliothequeH)

%.o: %.c
	@echo "generation de la bibliotheque," $@ "\n grace a la source"  $<
	$(cc) -c $< -o $@  $(FlagVoulu)





#supression des fichier temporaire
clean:
	@echo "destruction de tout le fichier temporaire ( il restera l'executable)"
	rm -rf *.o
#supression de tout les fichier sauf les source
mrpropre : clean
	@echo "destruction de tous sauf les source"
	rm -rf $(EXEC)
run: $(EXEC)
	@echo "\n execution du programme"
	./$(EXEC)
