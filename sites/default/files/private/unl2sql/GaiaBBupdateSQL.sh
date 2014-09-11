#!/bin/bash
opt=`getopt :nspgmre: $*`; statut=$?
# Si une option invalide a été trouvée
echo "Usage: `basename $0` [-n nettoyage] [-g get unl files] [-m mysqlInjections] [-r rapport par email]"

HOME="/var/www/bb/sites/default/files/private/unl2sql"
SCPDIR="/home/gaia/martine"
source $HOME/BB-include.sh

touch $HOME/TOUCH

GDISP="gdisp"
GMODU="gmodu"
GRESP="gresp"
GDIRE="gdire"
NCONT="ncont"
NTCAN="ntcan"
NORIE="norie"
GDIOF="gdiof"
GMOOF="gmoof"
NPRAC="nprac"
NPRNA="nprna"
NCAMP="ncamp"

dow=`date +%u` ; dom=`date +%d`
jour=`date +%A`
date=`date +%F--%H-%M`

if test $statut -ne 0; then
  echo "Pour tout lancer : ./`basename $0` -ngm"
  exit $statut
fi

# Traitement de chaque option du script
set -- $opt
while true
do
  # Analyse de l'option reçue - Chaque option sera effacée ensuite via un "shift"
  case "$1" in
    ## **************************************************
    -n) ## * -n * nettoyage
    ## **************************************************
    echo "_N_etttoyage du dossier"
    cd $HOME && rm *.unl *.SQL *.cl2
    shift;;
    ## **************************************************
    -g) ## * -g * recuperation des donnees
    ## **************************************************
    echo "_G_et donnees"
    cp -p $SCPDIR/$GDISP.unl $HOME
    cp -p $SCPDIR/$GMODU.unl $HOME
    cp -p $SCPDIR/$GDIRE.unl $HOME
    cp -p $SCPDIR/$GRESP.unl $HOME
    cp -p $SCPDIR/$NCONT.unl $HOME
    cp -p $SCPDIR/$NTCAN.unl $HOME
    cp -p $SCPDIR/$NORIE.unl $HOME
    cp -p $SCPDIR/$GDIOF.unl $HOME
    cp -p $SCPDIR/$GMOOF.unl $HOME
    cp -p $SCPDIR/$NPRAC.unl $HOME
    cp -p $SCPDIR/$NPRNA.unl $HOME
    cp -p $SCPDIR/$NCAMP.unl $HOME
    cd $HOME && echo `ls -alh *.unl`
    shift;;
    ## **************************************************
    -r) ## * -r * rapport par mail
    ## **************************************************
    if grep -q "ERROR" $HOME/daily.log
    then
      #/usr/bin/mail -s "$(echo -e "ECHEC BB")" nico.poulain@gmail.com marc-emmanuel.argo@ac-paris.fr jean-pierre.charpentrat@ac-paris.fr Isabelle.Cordier@ac-paris.fr christian.muir@ac-paris.fr jean-luc.simonet@ac-paris.fr < $HOME/daily.log
      /usr/bin/mail -s "$(echo -e "ECHEC BB")" nico.poulain@gmail.com < $HOME/daily.log
    else
      #/usr/bin/mail -s "$(echo -e "SUCCÈS BB")" nico.poulain@gmail.com marc-emmanuel.argo@ac-paris.fr jean-pierre.charpentrat@ac-paris.fr Isabelle.Cordier@ac-paris.fr christian.muir@ac-paris.fr jean-luc.simonet@ac-paris.fr < $HOME/daily.log
      /usr/bin/mail -s "$(echo -e "SUCCÈS BB")" nico.poulain@gmail.com < $HOME/daily.log
    fi

    shift;;
    ## **************************************************
    -m) ## * -m * Injections MySQL après amélioration des données
    ## **************************************************
    echo "Injections _M_YSQL après amélioration des données"

    echo -ne "* $NCAMP.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NCAMP 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NCAMP.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NCAMP.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NCAMP 7 $NB_CHAMPS 3 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NCAMP.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NCAMP.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $NPRAC.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NPRAC 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NPRAC.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NPRAC.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NPRAC 6 $NB_CHAMPS 7 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NPRAC.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NPRAC.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $NPRNA.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NPRNA 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NPRNA.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NPRNA.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NPRNA 6 $NB_CHAMPS 30 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NPRNA.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NPRNA.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $GMODU.unl en traitement par unl2sql ...\t\t" | tee $HOME/daily.log
    $HOME/unl2sql.sh $GMODU 39 2>&1 | tee -a $HOME/daily.log && echo "done."  | tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GMODU.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GMODU.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GMODU 40 $NB_CHAMPS 28000 $POIDS`
    if [[ "$TEST" = "ERROR" ]]; then 
      echo -e "\t\t\t\t\t\t\t$TEST"  | tee -a $HOME/daily.log
    else
      echo -ne "* $GMODU.SQL en cours d'injection  .....\t\t\t"  | tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GMODU.SQL 2>&1 | tee -a $HOME/daily.log && echo -e " completed successfully"  | tee -a $HOME/daily.log
    fi

    echo -ne "* $GDISP.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $GDISP 28 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GDISP.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GDISP.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GDISP 29 $NB_CHAMPS 9300 $POIDS`
    if [[ "$TEST" = "ERROR" ]]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $GDISP.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GDISP.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $GRESP.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $GRESP 17 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GRESP.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GRESP.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GRESP 18 $NB_CHAMPS 1200 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $GRESP.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GRESP.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $GDIRE.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $GDIRE 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GDIRE.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GDIRE.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GDIRE 6 $NB_CHAMPS 3200 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $GDIRE.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GDIRE.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $NCONT.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NCONT 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NCONT.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NCONT.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NCONT 6 $NB_CHAMPS 15 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NCONT.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NCONT.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $NTCAN.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NTCAN 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NTCAN.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NTCAN.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NTCAN 6 $NB_CHAMPS 3 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NTCAN.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NTCAN.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $NORIE.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $NORIE 5 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$NORIE.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$NORIE.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $NORIE 6 $NB_CHAMPS 46 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $NORIE.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$NORIE.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $GDIOF.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $GDIOF 25 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GDIOF.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GDIOF.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GDIOF 26 $NB_CHAMPS 4100 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $GDIOF.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GDIOF.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi

    echo -ne "* $GMOOF.unl en traitement par unl2sql ...\t\t" | tee -a $HOME/daily.log
    $HOME/unl2sql.sh $GMOOF 38 2<&1 |tee -a $HOME/daily.log && echo "done." |tee -a $HOME/daily.log
    NB_CHAMPS=`/bin/cat $HOME/$GMOOF.log |/usr/bin/cut -d' ' -f4 |/usr/bin/uniq`
    POIDS=$(/usr/bin/du $HOME/$GMOOF.SQL | /usr/bin/cut -f1)
    TEST=`$HOME/unlChecker.sh $GMOOF 39 $NB_CHAMPS 12900 $POIDS`
    if [ "$TEST" == "ERROR" ]; then 
      echo -e "\t\t\t\t\t\t\t$TEST" |tee -a $HOME/daily.log
    else
      echo -ne "* $GMOOF.SQL en cours d'injection  .....\t\t\t" |tee -a $HOME/daily.log
      /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/$GMOOF.SQL 2>&1 |tee -a $HOME/daily.log && echo -e " completed successfully" |tee -a $HOME/daily.log
    fi
    
    /usr/bin/mysql --user=root --password=$BDDPW $BDD < $HOME/annexes.sql 2>&1 |tee -a $HOME/daily.log && echo -e " annexes.sql injected" |tee -a $HOME/daily.log

    cat $HOME/daily.log >> history.log
    shift;;
  --) # Fin des options - Sortie de boucle
    shift; break;;
esac
done
# Affichage du reste des paramètres s'il y en a
test $# -ne 0 && echo "Il reste encore $# paramètres qui sont $*" || echo "Il n'y a plus de paramètre"

