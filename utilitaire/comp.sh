#!/bin/bash
echo -e " creation du premier execitable \n"
make
for i in  $@
do
chemin=$i
echo -e " le chemin est  $i \n"
cd $chemin
echo -e "\n\n\n\n \t creation de l'executable dans le dossier $chemin  \n"
make 
echo -e "\n \n retour au dossier d'origine\n"
cd ..
done

