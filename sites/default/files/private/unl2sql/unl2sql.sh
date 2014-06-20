#!/bin/bash
# usage : $ ./unl2sql.sh FILE N
# Creation du fichier FILE.SQL depuis FILE.unl possedant N champs
# Exemple : $ ./unl2sql.sh gmoof 39

HOME="/var/www/gbbdr/sites/default/files/private/unl2sql"
SCPDIR="/home/gaia/martine"

# Conversion UTF8 -> latin1
cd $HOME && iconv -f UTF-8 -t ISO-8859-15 $1.unl -o $1.unl_cleaned
# Suppression des espaces multiples et echappement des quotes
cd $HOME && sed -i "s/ \( \)*/ /g" $1.unl_cleaned
cd $HOME && sed -i "s/'/\\\'/g" $1.unl_cleaned

if [ "$1" == "gdisp" ]; then
  # Remplace 12345|12ABCD0560 par A_A_A_A12345|12ABCD0560
  cd $HOME && sed -i "s/^-*\([0-9]\{1,5\}|[0-9][0-9][0-9A-Z]\{4\}[0-9]\{4\}|\)/A_A_A_A\1/" $1.unl_cleaned
  # cas particuliers (bizarreries gaia)
  cd $HOME && sed -i "s/^\(4885| |SELENE\)/A_A_A_A\1/" $1.unl_cleaned
  cd $HOME && sed -i "s/^\(1036| |SELENE\)/A_A_A_A\1/" $1.unl_cleaned
fi
if [ "$1" == "gmodu" ]; then
  # Remplace 12345|67891|B| par A_A_A_A12345|67891|
  cd $HOME && sed -i "s/^-*\([0-9]\{1,5\}|[0-9]\{1,5\}|[A-Z]\{0,1\}|\)/A_A_A_A\1/" $1.unl_cleaned
fi
if [ "$1" == "gdiof" ]; then
  # Remplace 12345|20141234 par A_A_A_A12345|20141234
  cd $HOME && sed -i "s/^-*\([0-9]\{1,5\}|[0-9]\{8\}|\)/A_A_A_A\1/" $1.unl_cleaned
fi
if [ "$1" == "gmoof" ]; then
  # Remplace 12345|67891 par A_A_A_A12345|67891
  cd $HOME && sed -i "s/^-*\([0-9]\{1,5\}|[0-9]\{1,5\}|\)/A_A_A_A\1/" $1.unl_cleaned
  # cas particuliers (bizarreries gaia)
  cd $HOME && sed -i "s/^\(359|-1|PAREIL\)/A_A_A_A\1/" $1.unl_cleaned
fi

if [ "$1" == "gdisp" ] || [ "$1" == "gmodu" ] || [ "$1" == "gdiof" ] || [ "$1" == "gmoof" ]; then
  cd $HOME && sed -i "s/|$//g" $1.unl_cleaned				# remplace |\n par \n
  cd $HOME && tr '\012' ' ' < $1.unl_cleaned > $1.cl2	# supprime les \n 
  cd $HOME && sed -i 's/A_A_A_A/\o174\n/g' $1.cl2		# remplace AAAA par |\n
  cd $HOME && sed '1d' $1.cl2 > $1.unl_cleaned      # supprime la ligne 1
  cd $HOME && echo "|" >> $1.unl_cleaned            # le pipe final
  cd $HOME && rm $1.cl2 
fi

# Affichage du resultat et fichier de log
cd $HOME && awk -F'|' '{ print "ligne " NR " a " NF " champs" }' $1.unl_cleaned > $1.log

# Creation du fichier d'injection SQL
cd $HOME && cut -d'|' -f1-$2 --output-delimiter="','" $1.unl_cleaned > $1.SQL
cd $HOME && sed -i "s/^/INSERT INTO gbb_$1 VALUES ('/" $1.SQL
cd $HOME && sed -i "s/$/');/" $1.SQL
cd $HOME && sed -i "s/INSERT INTO $1 VALUES ('','');//" $1.SQL
cd $HOME && echo "TRUNCATE TABLE gbb_$1 ;" > $1.SQL2
cd $HOME && cat $1.SQL >> $1.SQL2
cd $HOME && mv $1.SQL2 $1.SQL
