#!/bin/bash
# usage : $ ./BB-logs.sh FILE CHAMPS_ATTENDUS CHAMPS POIDS_MIN POIDS
# Verification de validite de FILE.SQL

HOME="/var/www/gbbdr/sites/default/files/private/unl2sql"
X=`date -r $HOME/$1.unl +'%F'`
Y=`date +'%F'`

if [ "$2" != "$3" ] || [ $4 -ge $5 ] || [ $X != $Y ] ; then
  echo "ERROR"
  echo "    `date +"%R"` ; **ERR** ; `date -r $HOME/$1.unl +'%d/%m'`=`date +'%d/%m'`;$3=$2;$5>$4"  >>  $HOME/daily.log
else
  echo "    `date +"%R"`;OK;`date -r $HOME/$1.unl +'%d/%m'`=`date +'%d/%m'` ;$3=$2;$5>$4"  >>  $HOME/daily.log
fi
