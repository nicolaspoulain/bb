<?php
/**
 * @file
 *
 * Comweight de la page de gestion des évaluations
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 * affichant une liste de responsables et les stages qui leur
 * associes

CREATE TABLE `gbbdr_exp`.`gbb_gmodu_taxonomy` (
`co_modu` INT( 11 ) NOT NULL ,
`tid` INT( 10 ) NOT NULL
) ENGINE = MYISAM ;

INSERT INTO gbb_gmodu_taxonomy (co_modu,tid,weight)
SELECT co_modu,tid,weight FROM gbb_gdiof_dafor
JOIN taxonomy_term_data
ON taxonomy_term_data.name=gbb_gdiof_dafor.disc

 */
function gbb_ctplan_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  $build['tab'] = gbb_ctplan_tab($args);

  return implode('', $build);
}

function gbb_ctplan_tab($args) {
  //print_r(taxonomy_get_vocabularies());
  foreach (taxonomy_get_vocabularies() as $k=>$v) {
    if ($k >= 12) {
      $header[] = array('data' => t($v->name.' '), 'class' => 'gris');
      $class = (preg_match("/multi/",$v->name))? 'topAlignMulti' : 'topAlign';
      $rows[0][] = array('data' => gbb_ctplan_vocab($k),
                         'class'=>$class);
    }
  }
  $output = theme('table',array('header' => $header, 'rows'   => $rows ));
  return $output;
}

  function gbb_ctplan_vocab($vid) {

  $terms = taxonomy_get_tree($vid);
  $terms_select = array();
  foreach ($terms as $term) {
      $terms_select[$term->tid] = str_repeat('— ', $term->depth) . $term->name;
  };
  $check = db_query("SELECT tid,weight FROM {gbb_gmodu_taxonomy}
                                  WHERE co_modu = :co_modu",
                                  array(':co_modu' => arg(1),))
                                  ->fetchAllkeyed();
  foreach ($terms_select as $key=>$val) {
    $pos= array_key_exists($key,$check)? $check[$key] : 1;
    $ischk= array_key_exists($key,$check);
    $rows[] = array(array('data'=>render(drupal_get_form('gbb_ctplan_taxonomy_form',$key,$val,$pos,$ischk,arg(1),arg(2)))));
  }
  $output = theme('table',array('rows'   => $rows,'attributes' => array('id' => 'ctplan-table'.$key) ));
  return $output;
  }

  function gbb_ctplan_taxonomy_form($form, &$form_state, $tid,$voc,$pos,$ischk,$co_modu,$co_degre) {
    $form['f']['co_modu']  = array('#type' => 'hidden','#value' => $co_modu );
    $form['f']['tid']  = array('#type' => 'hidden','#value' => $tid );
    $form['f'][$tid] = array(
      '#type' => 'checkbox',
      '#title' => $voc,
      '#default_value' => $ischk,
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>',
      '#ajax' => array(
        'callback' => 'gbb_ctplan_taxonomy_form_submit',
        'progress' => array('type' => 'throbber', 'message' => '')),
      );
    $form['f']['co_degre'] = array(
      '#type' => 'hidden',
      '#default_value' => $co_degre,
      );
    $form['f']['weight'] = array(
      '#type' => 'textfield',
      '#size' => 2,
      '#default_value' => $pos,
      '#prefix' => '&nbsp;<div class="inline">',
      '#attributes' => array('class' => array('weight')),
      '#suffix' => '</div>',
      '#states' => array(    // This #states rule limits visibility
        'visible' => array(  // action to take.
          ':input[name='.$tid.']' => array('checked' => TRUE),),
      ),
      '#ajax' => array(
        'callback' => 'gbb_ctplan_taxonomy_form_submit',
        'progress' => array('type' => 'throbber', 'message' => '')),
      );
    return $form;
}

function gbb_ctplan_taxonomy_form_submit($form, &$form_state) {
  $tid = $form_state['values']['tid'];
  if ($form_state['values'][$tid] == 0) { // $form_state['values']['disc'][$key] not checked
    db_delete('gbb_gmodu_taxonomy')
        ->condition('co_modu', $form_state['values']['co_modu'] )
        ->condition('tid', $form_state['values']['tid'] )
        ->condition('co_degre', $form_state['values']['co_degre'] )
        ->execute();
  } else {           // $form_state['values']['disc'][$key] was checked
      $nb = db_select('gbb_gmodu_taxonomy','m')
          ->fields('m',array('tid'))
          ->condition('co_modu', $form_state['values']['co_modu'] )
          ->condition('tid', $form_state['values']['tid']  )
          ->condition('co_degre', $form_state['values']['co_degre'] )
          ->execute()->rowCount();
      if ($nb==0) {
        db_insert('gbb_gmodu_taxonomy')
          ->fields(array('co_modu' => $form_state['values']['co_modu'] ,
                             'tid' => $form_state['values']['tid'] ,
                          'weight' => $form_state['values']['weight'],
                        'co_degre' => $form_state['values']['co_degre']
            ))
            ->execute();
      } else {
        db_update('gbb_gmodu_taxonomy')
          ->fields(array('weight'=>$form_state['values']['weight']))
          ->condition('co_modu', $form_state['values']['co_modu'] )
          ->condition('tid', $form_state['values']['tid'] )
          ->condition('co_degre', $form_state['values']['co_degre'] )
          ->execute();
      }
  }
}


/**
 * Affiche le contenu à compiler pour le CTP
 */
function gbb_ctplan_latex_view($args = 'NaN') {

  // Construction de la page
  $build = array();
  $build['tab'] = gbb_ctplan_latex($args);

  return implode('', $build);
}

/**
 * Construit le tableau avec un vocabulaire par colonne
 */
function gbb_ctplan_latex($args) {

  //print_r(taxonomy_get_vocabularies());
  $str = "";
  // $k ---- 2:2Deg  3:IATSS  4:MotsClé  5:1Deg  6: Encadr  7:Interdeg
  $header[] = array('data' => t("CTP").l('('.t('edit').')', '#'), 'class' => 'gris');

  $str .= "<br/>((H0))PREMIER DEGRÉ<br/>";
  $str .= gbb_ctplan_latex_vocab(10);
  // $str .= "<br/>((H0))INTERDEGRÉ<br/>";
  // $str .= gbb_ctplan_latex_vocab(7);
  $str .= "<br/>((H0))SECOND DEGRÉ<br/>";
  $str .= gbb_ctplan_latex_vocab(8);
  $str .= "<br/>((H0))IATSS<br/>";
  $str .= gbb_ctplan_latex_vocab(9);
  $str .= "<br/>((H0))ENCADREMENT<br/>";
  $str .= gbb_ctplan_latex_vocab(11);

  $rows[0][] = array('data' => $str,
                     'class'=>'topAlign');
  $output = theme('table',array('header' => $header, 'rows'   => $rows ));
  return $output;
}

/**
 * Construit le tableau avec une colonne contant les mots du vocabulaire $vid
 */
  function gbb_ctplan_latex_vocab($vid) {

  $terms = taxonomy_get_tree($vid);
  $terms_select = array();
  foreach ($terms as $term) {
    $depth = $term->depth +1;
    $terms_select[$term->tid] = '((H' . $depth .'))' . $term->name . '<br/>';
  };
  foreach ($terms_select as $key=>$val) {
    $query = db_select('gbb_gmodu_taxonomy','t')
          ->condition('tid', $key )
          ->condition('d.id_disp' , '15' . '%', 'LIKE')
          // ->condition('d.co_degre' , 'm.co_degre', '=')
          ->condition('d.co_andi' , '', '=')
          ->condition('m.co_anmo' , '', '=')
          ->condition('weight', 500, '<')
          ->isNotNull('m.libl');
    $query->leftjoin('gbb_gmodu', 'm',
                     't.co_modu = m.co_modu');
    $query->leftjoin('gbb_gdisp', 'd',
                     'm.co_disp = d.co_disp');
    if ($vid == 10) {  // Responsable premier degre
      $query->leftjoin('gbb_gdire', 'gd',
                     'gd.co_modu = m.co_modu AND gd.co_degre=1 AND gd.co_tres=3');
      $query->leftjoin('gbb_gresp', 'rm',
                     'gd.co_resp = rm.co_resp AND rm.co_degre=1');
    } else {          // Responsable second degré
      $query->leftjoin('gbb_gdire', 'gd',
                     'gd.co_modu = m.co_modu AND gd.co_degre=2 AND gd.co_tres=3');
      $query->leftjoin('gbb_gresp', 'rm',
                     'gd.co_resp = rm.co_resp AND rm.co_degre=2');
    }
    $query->fields('t',array('tid'));
    $query->fields('m',array('co_modu','duree_prev','lpeda','lcont','lmoda','lform','lcibl'));
    $query->addField('rm', 'nomu', 'nomu_modu');
    $query->addField('rm', 'prenom', 'prenom_modu');
    $query->addField('rm', 'qualite', 'qualite');
    $query->addField('m', 'libl', 'libmodu');
    $query->addField('m', 'co_modu', 'co_omodu');
    $query->addField('d', 'id_disp', 'no_offre');
    $query->fields('d',array('lib','lobjt','co_tcan','co_tpla'));
    $query->orderBy('weight', 'ASC');
    $list= $query->execute()->fetchAll();

    $str = "";
    $count= 0;
    $no_offre = -1;

    foreach ($list as $f) {
      if ($no_offre != $f->no_offre || $count==3) { 
          //on crée un nouveau tableau si les modules ne sont pas dans le
          //même dispo ou si le tableau a plus de 4 lignes.
        if ($no_offre != -1) $str .= '((13))<br/>';

        $q = $query;
        // Compte le nombre de modules
        $q = db_select('gbb_gmodu','m');
        $q->fields('m',array('co_modu'));
        $q->leftjoin('gbb_gdisp', 'd',
                     'm.co_disp = d.co_disp');
        $q->leftjoin('gbb_gmodu_taxonomy', 't',
                     't.co_modu = m.co_modu');
        $q->condition('weight', 500, '<');
        $q->condition('tid', $f->tid);
        $nbmod = $q->condition('d.id_disp', $f->no_offre)->execute()->rowCount();

        if ($nbmod>1) {
          $str .= '((1))' . $f->no_offre;
        } else {
          $str .= '((1))' . $f->no_offre ."/" . $f->co_omodu;

        }
        if ($f->co_tcan=="3" AND $f->co_tpla=="D") {
          $str .= '((2ID))' . strtoupperFr($f->lib);
        } elseif ($f->co_tcan=="3") {
        $str .= '((2D))' . strtoupperFr($f->lib);
        } elseif ($f->co_tpla=="D") {
        $str .= '((2I))' . strtoupperFr($f->lib);
        } else {
        $str .= '((2))' . strtoupperFr($f->lib);
        }
        // affiche le lib dispo que si modules multiples
        if ($nbmod>1) {
          $str .= '((3))' . $f->lobjt; 
          $str .= '((4))' . $f->co_omodu;
          $str .= '((5))' . strtoupperFr($f->libmodu);
        }
        $count = 0;
      } else { 
        $count = $count+1;
        $str .= '((4))' . $f->co_omodu;
        $str .= '((5))' . strtoupperFr($f->libmodu);
      };
      $str .= '((6))' . $f->duree_prev;
      $str .= '((7))' . $f->prenom_modu.' '.$f->nomu_modu;
      $str .= ($f->qualite == "")? "" : '((8))' . $f->qualite;
      $str .= '((8b))' . $f->lcibl;
      $str .= '((9))' . $f->lpeda;
      $str .= '((10))' . $f->lcont;
      $str .= ($f->lmoda == "" || $f->lmoda =='.' || $f->lmoda ==';')? "" : '((11))' . $f->lmoda;
      $str .= ($f->lform == "" || $f->lform =='.' || $f->lform ==';')? "" : '((12))' . $f->lform;
      $no_offre = $f->no_offre;
    };
    $rows[] = $val." ".$str.(($str=="")? "":'((13))<br/>');
  }
  $output = implode('<br/>',$rows);
  return $output;
  }
/**
 * Construit le doc txt2tags pour imprimer les FIL
 * */
  function gbb_ctplan_latex_fil() {

  $query = db_select('gbb_gmodu','m')
        ->condition('d.id_disp' , '15' . '%', 'LIKE')
        ->condition('d.co_andi' , '', '=')
        ->condition('m.co_anmo' , '', '=')
        ->condition('d.co_camp' , 'BS', 'LIKE');
  $query->leftjoin('gbb_gdisp', 'd',
                   'm.co_disp = d.co_disp');
  // resp PEDA
  $query->leftjoin('gbb_gdire', 'gdpeda',
                 'gdpeda.co_modu = m.co_modu AND gdpeda.co_degre=2 AND gdpeda.co_tres=3');
  $query->leftjoin('gbb_gresp', 'resppeda',
                 'gdpeda.co_resp = resppeda.co_resp AND resppeda.co_degre=2');
  // resp ORGA
  $query->leftjoin('gbb_gdire', 'gdorga',
                 'gdorga.co_modu = m.co_modu AND gdorga.co_degre=2 AND gdorga.co_tres=2');
  $query->leftjoin('gbb_gresp', 'resporga',
                 'gdorga.co_resp = resporga.co_resp AND resporga.co_degre=2');
  $query->leftjoin('gbb_netab_dafor', 'e',
                 'm.co_etab_dem = e.co_lieu');
  $query->fields('m',array('co_modu','duree_prev','lpeda','lcont','lmoda','lform','lcibl'));
  $query->addField('resporga', 'nomu', 'nomuOrga');
  $query->addField('resporga', 'prenom', 'prenomOrga');
  $query->addField('resporga', 'qualite', 'qualiteOrga');
  $query->addField('resppeda', 'nomu', 'nomuPeda');
  $query->addField('resppeda', 'prenom', 'prenomPeda');
  $query->addField('resppeda', 'qualite', 'qualitePeda');
  $query->addField('m', 'lib', 'libmodu');
  $query->addField('m', 'co_modu', 'co_omodu');
  $query->addField('m', 'co_etab_dem', 'co_etab_dem');
  $query->addField('d', 'id_disp', 'no_offre');
  $query->addField('e', 'denom_comp', 'denom_comp');
  $query->addField('e', 'sigle', 'sigle');
  $query->addField('e', 'cp', 'cp');
  $query->fields('d',array('lib','lobjt','co_tcan','co_tpla'));
  // $query->orderBy('denom_comp', 'ASC');
  $query->orderBy('id_disp', 'ASC')->orderBy('cp', 'ASC');
  $list= $query->execute()->fetchAll();

  $str = "";
  $last_iddisp = "";
  $last_cp = "";
  $last_denom_comp = "";

  foreach ($list as $f) {
    if ($last_iddisp != $f->no_offre) {
      $str .= "<br/>((H1)) ".$f->no_offre.' '. strtoupperFr($f->lib) ."<br/>";
      $str .= "((H1bis)) ".$f->lobjt."<br/><br/>";
      $last_cp = 'xx';
    }
    $last_iddisp = $f->no_offre;

    if ($last_cp != $f->cp) {
     $str .= "<br/>((H2)) ".$f->cp."<br/>";
    } else {
     if ($new_iddisp) $str .= "<br/>((H2)) Pas de RNE <br/>";
    }
    $last_cp = $f->cp;
    $new_iddisp = False;

    // if ($last_denom_comp != $f->denom_comp) 
      // $str .= "<br/>((H2)) ".strtoupperFr($f->sigle) .' '. strtoupperFr($f->denom_comp)."<br/>";
    // $last_denom_comp = $f->denom_comp;


    // $str .= '((1))' . $f->no_offre ."/" . $f->co_omodu;
    // $str .= '((2))' . strtoupperFr($f->lib);
    // $str .= '((3))' . $f->lobjt; 
    $str .= '((4))' . $f->co_omodu;
    $str .= '((5))' . strtoupperFr($f->libmodu);
    $str .= '((6))' . $f->duree_prev;
    $str .= '((7))' . $f->lpeda;
    $str .= '((8))' . $f->lcont;
    $str .= ($f->lmoda == "" || $f->lmoda =='.' || $f->lmoda ==';')? "" : '((9))' . $f->lmoda;
    $str .= ($f->lform == "" || $f->lform =='.' || $f->lform ==';')? "" : '((10))' . $f->lform;
    $str .= '((11))' . $f->lcibl;
    $str .= '((12o))' . $f->prenomOrga.' '.$f->nomuOrga;
    $str .= ($f->qualiteOrga == "")? "" : '((12ob))' . $f->qualiteOrga;
    $str .= '((12p))' . $f->prenomPeda.' '.$f->nomuPeda;
    $str .= ($f->qualitePeda == "")? "" : '((12pb))' . $f->qualiteOrga;
    $str .= "((13))<br/>";

  };
  return $str;
  }

function strtoupperFr($string) {
  $string = strtoupper($string);
  $string = str_replace(
    array('é', 'è', 'ê', 'ë', 'à', 'â', 'î', 'ï', 'ô', 'ù', 'û'),
    array('É', 'È', 'Ê', 'Ë', 'À', 'Â', 'Î', 'Ï', 'Ô', 'Ù', 'Û'),
    $string);
  return $string;
}

