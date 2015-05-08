#!/bin/bash
echo -e " clean du premier  \n"
make clean
for i in  $@
do
chemin=$i
echo -e " le chemin est  $i \n"
cd $chemin
echo -e "\n\n\n\n \t clean  dans le dossier $chemin  \n"
make clean
echo -e "\n \n retour au dossier d'origine\n"
cd ..
done

