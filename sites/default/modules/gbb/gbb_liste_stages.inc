<?php
/**
 * @file
 *
 * Composition de la page de gestion de module
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 * affichant une liste de responsables et les stages qui leur
 * associes
 */
function gbb_liste_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
    array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  drupal_add_js(drupal_get_path('module', 'gbb') . '/js/jquery.dataTables.js',
    array('group' => CSS_DEFAULT, 'every_page' => TRUE));
  drupal_add_js(drupal_get_path('module', 'gbb') . '/js/jquery.dataTables.load.js',
    array('group' => CSS_DEFAULT, 'every_page' => TRUE));

  $build['search'] = render(drupal_get_form('gbb_liste_stages_search',$args));
  $build['choix']  = render(drupal_get_form('gbb_liste_stages_choix', $args));
  $build['liste']  = gbb_liste_stages_liste($args);
  return implode('', $build);
}


/**
 * Fonction d'appel aux deux views d'affichage des stages à
 * traiter
 */
function gbb_atraiter_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css', 
    array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  drupal_add_js(drupal_get_path('module', 'gbb') . '/js/jquery.dataTables.js', 
    array('group' => CSS_DEFAULT, 'every_page' => TRUE));
  drupal_add_js(drupal_get_path('module', 'gbb') . '/js/jquery.dataTables.load.js',
    array('group' => CSS_DEFAULT, 'every_page' => TRUE));

  $build['choix']  = render(drupal_get_form('gbb_atraiter_choix', $args));
  return implode('', $build);
}

/**
 * Formulaire de ** CHOIX D'UN FORMATEUR OU D'UNE ORIENTATION ** 
 */
function gbb_atraiter_choix($form, &$form_state, $args) {

  $query = db_select('gbb_gdire', 'j');
  $query ->rightjoin('gbb_gdisp', 's', 
    'j.co_disp=s.co_disp AND j.co_degre=s.co_degre');
  $query ->join('gbb_gresp', 'r', 
    'j.co_resp=r.co_resp AND j.co_degre=r.co_degre');
  $query ->condition('j.co_degre', 2, '=')
    ->condition('s.id_disp' , '14' . '%', 'LIKE')
    ->fields('j', array('co_resp'))
    ->fields('r', array('nomu'));
  if (arg(3) != 0) { 
    // si un co_tres est spécifié : on trie dessus
    $query->condition('j.co_tres' , 2, '=');
  }
  elseif (!user_access('gest_sessions gbb')  && arg(3) == 0) {
    // si pas de co_tres : resp orga par défaut pour les administratifs
    $query->condition('j.co_tres' , 2, '=');
  }
  else {
    // si pas de co_tres : tout par défaut pour les non administratifs
  };
  $result = $query->execute();

  foreach ($result as $r) {
    $rows[$r->co_resp] = $r->nomu;
  }
  unset($rows['']);
  $rows['0'] = ' ** TOUS ** ';
  asort($rows);

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Service Administratif : Recherche des stages à traiter'),
    '#attributes' => array('class' => array('collapsible',)),
  );

  // ------------
  // Ici on récupère le conseiller par défaut si arg(4) est vide
  // cela pour caler le select sur le bon conseiller
  global $user;
  $user_data = user_load($user->uid);
  $n = $user_data->field_nomu['und']['0']['value'];

  #$query = db_select('field_data_field_nomu', 'u')
  #  ->condition('u.entity_id', $user->uid, '=')
  #  ->fields('u', array('field_nomu_value'));
  $nomu = ( isset($_GET['nomu']) )? $_GET['nomu'] : 'TOUS';
  if ($nomu=="") { $nomu = "TOUS";};


  $form['f']['people'] = array(
    '#type' => 'textfield',
    '#title' => t('Responsable organisationnel'),
    '#default_value' => $nomu,
    '#size' => 20,
    #'#element_validate' => array('_choix_conseiller_validate'),
    '#autocomplete_path' => 'autocomp/responsable',
    '#prefix' => '<br/><div class="ajaxform inline">',
    '#suffix' => '</div>&nbsp;',
  );

  $form['f']['submit'] = array('#type' => 'submit',
    '#value' => 'Envoyer',);

  return $form;
}
/**
 * ----> Submit
 */
function gbb_atraiter_choix_submit($form, &$form_state) {
  $nomu = $form_state['values']['people'];
  if ($nomu=="TOUS") { $nomu = "";};
  $url = url('atraiter',
    array('query' => array(
      'nomu' => $nomu), 
    'absolute' => TRUE)
  );
  $form_state['redirect'] = $url;
}


/**
 * Formulaire de ** FORMULAIRE DE RECHERCHE TOUS AZIMUTS **
 */
function gbb_liste_stages_search($form, &$form_state, $args) {
  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Recherche tous azimuts'),
    '#attributes' => array('class' => array('sessions',
    'recherchestage',
    'collapsible',
    'collapsed')),
  );

  $form['f']['co_modu'] = array(
    '#type' => 'textfield',
    '#title' => t('Rechercher un STAGE'),
    '#description' => t('Saisissez quelques lettres du titre
    (ou chiffres du numéro) pour rechercher un stage'),
    '#autocomplete_path' => 'autocomp/stage',
    '#element_validate' => array('element_validate_integer_positive'),
    '#prefix' => '<div class="ajaxform inline">',
    '#suffix' => '</div>',
    '#size' => 80,
  );
  $form['f']['submit_co_modu'] = array(
    '#type' => 'submit',
    '#value' => 'Envoyer.',
    '#submit' => array('recherche_stage_submit'),
  );

  $form['f']['co_resp'] = array(
    '#type' => 'textfield',
    '#title' => t('Rechercher un FORMATEUR'),
    '#description' => t('Saisissez quelques lettres du nom
    pour rechercher un formateur'),
    '#autocomplete_path' => 'autocomp/formateur2',
    '#prefix' => '<div class="ajaxform inline">',
    '#suffix' => '</div>',
    '#size' => 80,
  );
  $form['f']['submit_co_resp'] = array(
    '#type' => 'submit',
    '#value' => 'Envoyer',
    '#submit' => array('recherche_formatr_submit'),
  );

  return $form;
}

/**
 * ----> Submit du formualire de recherche tous azimuts
 */
function recherche_stage_submit($form, &$form_state) {
  $form_state['redirect'] = url('module/2/' . $form_state['values']['co_modu'],
    array('absolute' => TRUE));
}
function recherche_formatr_submit($form, &$form_state) {
  $replace = array ('\1');
  $pattern = array ('/.*\(id:(.*)\)/');
  $co_resp = preg_replace($pattern, $replace,
                          $form_state['values']['co_resp']);
  $url = url('formateur/' . $co_resp,
                            array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}


/**
 * Formulaire de ** CHOIX D'UN FORMATEUR OU D'UNE ORIENTATION **
 */
function gbb_liste_stages_choix($form, &$form_state, $args) {

  $query = db_select('gbb_gdire', 'j');
  $query ->rightjoin('gbb_gdisp', 's',
    'j.co_disp=s.co_disp AND j.co_degre=s.co_degre');
  $query ->join('gbb_gresp', 'r',
    'j.co_resp=r.co_resp AND j.co_degre=r.co_degre');
  $query ->condition('j.co_degre', arg(2), '=')
    ->condition('s.id_disp' , db_like(arg(1)) . '%', 'LIKE')
    ->fields('j', array('co_resp'))
    ->fields('r', array('nomu'));
  if (arg(3) != 0) {
    // si un co_tres est spécifié : on trie dessus
    $query->condition('j.co_tres' , arg(3), '=');
  }
  $result = $query->execute();

  foreach ($result as $r) {
    $rows[$r->co_resp] = $r->nomu;
  }
  unset($rows['']);
  $rows['0'] = ' ** TOUS ** ';
  asort($rows);

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Recherche par conseiller'),
    '#attributes' => array('class' => array('collapsible',)),
  );

  global $user;
  $user_data = user_load($user->uid);
  $n = $user_data->field_nomu['und']['0']['value'];
  $form['f']['voir_atraiter']['#markup'] = '<p><div class="flotteDroite">'
    .variable_get('ico_notAttente')."&nbsp;"
                     . l( t('Mes stages à traiter'),
                        'atraiter',
                        array('attributes' =>  array('class' => 'anchor-class'
                      ),
                      'query' => array('nomu' => $n),
                                                     'html' => TRUE)) . '</p>'
   .'</div></p>';
  $degre = array(1 => 'Premier degré',
    2 => 'Second degré'  );
  $form['f']['codegre'] = array(
    '#type' => 'select',
    '#title' => t(''),
    '#default_value' => arg(2),
    '#options' => $degre,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  $periode = array(
    08 => '2008-2009',
    09 => '2009-2010',
    10 => '2010-2011',
    11 => '2011-2012',
    12 => '2012-2013',
    13 => '2013-2014',
    14 => '2014-2015'  );
  $form['f']['year'] = array(
    '#type' => 'select',
    '#title' => t(''),
    '#default_value' => arg(1),
    '#options' => $periode,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;&nbsp;',
  );

  $form['f']['voir_ferme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Voir les modules fermés'),
    '#default_value' => (isset($_GET['voir_ferme']))? $_GET['voir_ferme'] : 0,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  // ------------
  // Ici on récupère le conseiller par défaut si arg(4) est vide
  // cela pour caler le select sur le bon conseiller
  global $user;
  $query = db_select('field_data_field_nomu', 'u')
    ->condition('u.entity_id', $user->uid, '=')
    ->fields('u', array('field_nomu_value'));
  $nomu = ( arg(4)=='' )? $query->execute()->fetchField() : arg(4);

  $form['f']['people'] = array(
    '#type' => 'textfield',
    '#title' => t('Conseiller'),
    '#default_value' => $nomu,
    '#size' => 20,
    '#element_validate' => array('_choix_conseiller_validate'),
    '#autocomplete_path' => 'autocomp/responsable',
    '#prefix' => '<br/><div class="ajaxform inline">',
    '#suffix' => '</div>&nbsp;',
  );

  $query = db_select('gbb_norie', 'o');
  $query ->rightjoin('gbb_gdisp', 'd', 'o.co_orie=d.co_orie');
  $query ->condition('d.co_degre', arg(2), '=')
    ->condition('d.id_disp' , db_like(arg(1)) . '%', 'LIKE')
    ->fields('o', array('co_orie', 'lib_long'));
  $orientations = $query->execute();

  foreach ($orientations as $r) {
    $ories[$r->co_orie] = $r->lib_long;
  }
  unset($ories['']);
  $ories['0']='TOUS';
  asort($ories);

  $co_orie = ( arg(5)=='' )? 0 : arg(5);

  if (user_access('gest_sessions gbb')) {
    $tres = array( 0 => 'TOUS',
      // 1 => 'Interlocuteur',
      2 => 'Resp. orga.',
      3 => 'Resp. péda.'  );
    $form['f']['cotres'] = array(
      '#type' => 'select',
      '#title' => t('Rôle'),
      '#default_value' => arg(3),
      '#options' => $tres,
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>',
    );

    $form['f']['coorie'] = array(
      '#type' => 'select',
      '#title' => t('Orientation'),
      '#options' => $ories,
      '#default_value' => $co_orie,
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>',
    );
  } else {
    $form['f']['cotres'] = array('#type' => 'hidden',
      '#value' => 2,      );
    $form['f']['coorie'] = array('#type' => 'hidden',
      '#value' => 0,      );
  };

  $form['f']['submit'] = array('#type' => 'submit',
    '#value' => 'Envoyer',);

  return $form;
}

function _choix_conseiller_validate($element, &$form_state) {
  $query = db_select('gbb_gresp', 'r')
    ->fields('r', array('nomu'))
    ->condition('nomu', $element['#value'], '=')
    ->distinct();
  $num_rows = $query->countQuery()->execute()->fetchField();
  if ($num_rows == 0 && $element['#value'] != 'TOUS') {
    form_error($element, t('Le champ Conseiller ne peut être
      qu\'une des valeurs proposées, et que vous aurez cliquée.'));
  }
}

/**
 * ----> Submit
 */
function gbb_liste_stages_choix_submit($form, &$form_state) {
  $url = url('liste/' . $form_state['values']['year']
    . '/' . $form_state['values']['codegre']
    . '/' . $form_state['values']['cotres']
    . '/' . $form_state['values']['people']
    . '/' . $form_state['values']['coorie'],
    array('query' => array(
      'voir_ferme' => $form_state['values']['voir_ferme']),
    'absolute' => TRUE)
  );
  $form_state['redirect'] = $url;
}

/**
 * Fonction de ** LISTE DES STAGES ** pour un conseiller donné en argument
 */
function gbb_liste_stages_liste($args) {

  $query = db_select('gbb_gmodu', 'm');
  $query ->leftjoin('gbb_gmodu_plus', 'mp',
    'mp.co_modu=m.co_modu AND mp.co_degre=m.co_degre');
  $query ->join('gbb_gdisp', 'd',
    'd.co_disp = m.co_disp AND d.co_degre = m.co_degre');
  $query ->join('gbb_gdire', 'j',
    'j.co_modu = m.co_modu AND j.co_degre = m.co_degre');
  $query ->fields('m',  array('co_modu', 'co_anmo'))
    ->fields('mp', array('module_alert', 'module_printed',
      'prioritaire', 'organisation','color' ))
      ->fields('d',  array('co_disp', 'id_disp', 'co_tcan',
        'co_camp', 'co_andi'));
  $query ->addField('m', 'lib', 'libm');
  $query ->addField('d', 'lib', 'libd');

  // -----------------------------------------------------------------
  // prise en compte de l'année, du degré, du orga/péda et orientation
  // -----------------------------------------------------------------
  $query  ->condition('id_disp',    db_like(arg(1)) . '%', 'LIKE')
    ->condition('m.co_degre', arg(2), '=');
  if (arg(3) && arg(3)!="0") {
    $query->condition('j.co_tres',  arg(3), '='); };
    if (arg(5) && arg(5)!="0") {
      $query->condition('d.co_orie',  arg(5), '='); };

      // -------------------------------------------
      // prise en compte du nom du conseiller
      // -------------------------------------------
      if ( arg(4)=='' ) { // On récupère le nomu par défaut.dans le profil
        global $user;
        $qu = db_select('field_data_field_nomu', 'u')
          ->condition('u.entity_id', $user->uid, '=')
          ->fields('u', array('field_nomu_value'));
        $nomu = $qu->execute()->fetchField();
      } else { $nomu = arg(4); }; // L'URL donne le nomu : on le prend

      if( $nomu != 'TOUS' ) { // On récupère les co_resp correspondants à *nomu
        $tab_resp = db_select('gbb_gresp', 'c')
          ->fields('c', array('co_resp'))
          ->condition('nomu', '' . db_like($nomu) . '', 'LIKE')
          ->condition('co_degre', arg(2), '=')
          ->distinct()
          ->execute()->fetchCol();
        $query->condition('j.co_resp', $tab_resp, 'IN');  // print_r($tab_resp);
      };
      // ----------------------------------------i---
      // prise en compte du voir les stages fermés
      // -------------------------------------------
      if ( !isset($_GET['voir_ferme']) || $_GET['voir_ferme']==0 ) {
        $query->condition('m.co_anmo', '', '=');
        //$query .= 'AND co_anmo = \'\'';
      }

      $query->orderBy('id_disp', 'ASC');
      $query->orderBy('co_modu', 'ASC');
      $query->distinct();
      $result = $query->execute();
      if ($result->rowCount() == 0) return 'Hum !';

      $libd_precedent= '';
      $rows = array();

      foreach ($result as $r) {
        $qdt = db_select('gbb_session', 's');
        $qdt ->fields('s', array('sess_id'))
          ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->condition('s.en_attente', '0', '=');
        $qdt ->addExpression('MIN(date)','dateD');
        $qdt ->addExpression('MAX(date)','dateF');
        $dt = $qdt->execute()->fetchObject();
        $dateD = $dt->dateD;
        $dateF = $dt->dateF;

        $qnea = db_select('gbb_session', 's');
        $qnea ->fields('s', array('sess_id'))
          ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->condition('s.en_attente', '0', '=')
          ->condition('s.convoc_sent', '0', '=');
        $nb_nea = $qnea->execute()->rowCount();

        $qea = db_select('gbb_session', 's');
        $qea ->fields('s', array('sess_id'))
          ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->condition('s.en_attente', '1', '=');
        $nb_ea = $qea->execute()->rowCount();

        $qs = db_select('gbb_session', 's');
        $qs ->fields('s', array('sess_id'))
          ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->condition('s.convoc_sent', '1', '=');
        $nb_s = $qs->execute()->rowCount();

        $qsa = db_select('gbb_session', 's');
        $qsa ->fields('s', array('sess_id'))
          ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->condition('s.session_alert', '1', '=');
        $nb_sa = $qsa->execute()->rowCount();

        $qpj = db_select('gbb_file', 'f');
        $qpj ->join('file_managed', 'fm', 'fm.fid=f.fid');
        $qpj ->fields('f', array('fid'))
          ->condition('f.co_degre', arg(2), '=')
          ->condition('f.co_modu', $r->co_modu, '=')
          ->condition('fm.status', '1', '=');
        $nb_pj = $qpj->execute()->rowCount();

        $dda = db_select('gbb_gmodu_plus', 'mp');
        $dda ->fields('mp', array('DA_date_depot'))
          ->condition('mp.co_degre', arg(2), '=')
          ->condition('mp.co_modu', $r->co_modu, '=');
        $ddt = $dda->execute()->fetchObject();
        $DAdd = ($ddt) ? $ddt->DA_date_depot : "NaN";

        $m_ouvert_ou_ferme = ($r->co_anmo == '')? '' : 'Ferme';
        $options_co_modu = array('attributes' =>
          array('class' => array($m_ouvert_ou_ferme),
            'style' => 'background-color:'.$r->color,
            'id' => 'cool-id'         ),
          'html' => FALSE,
        );
        $d_ouvert_ou_ferme = ($r->co_andi == '')? '' : 'Ferme';
        $can = array(1 => "", 2 => "", 3 => variable_get('ico_pubDes'));
        $candidature = $can[$r->co_tcan];
        $paf_ou_fil = ($r->co_camp == 'BS')? 'fil' : 'paf';
        $libd_class = ($r->co_camp == 'BS')? 'fil' : 'paf';
        $libd_class = ($r->libd == $libd_precedent)? "gris" : $libd_class;

        // Les icônes à afficher
        $session_alert = ($nb_sa == 0)? '' : variable_get('ico_alert');
        $module_alert = ($r->module_alert==0)? '' : variable_get('ico_alert');
        $NOT_en_attente = ($nb_nea == 0)? '' : variable_get('ico_notAttente')
          . "<span class=\"fa blue\">$nb_nea</span> ";
        $en_attente = ($nb_ea == 0)? '' : variable_get('ico_attente')
          . "<span class=\"fa\">$nb_ea</span> ";
        $module_printed = ($r->module_printed)? variable_get('ico_print') : '';
        $prioritaire = (!$r->prioritaire)? '' : variable_get('ico_bell');
        $convoc_sent = ($nb_s == 0)? '' : variable_get('ico_sent')."<span class=\"fa green\">$nb_s</span> ";
        $rsp = db_select('gbb_gdire', 'd');
        $rsp ->fields('d', array('co_resp', 'co_tres', 'co_modu'))
          ->condition('d.co_degre', arg(2), '=')
          ->condition('d.co_tres', 3, '=')
          ->condition('d.co_modu', $r->co_modu, '=');
        $rsp ->leftjoin('gbb_gresp', 'r',
          'r.co_resp  = d.co_resp AND r.co_degre = d.co_degre');
        $rsp ->fields('r', array('nomu', 'prenom'));
        $respo = $rsp->execute()->fetchObject();
        #print_r($respo);
        if ($paf_ou_fil=='paf') {
          if ($respo) {
            $plus = " <i>(R.péda : " . $respo->nomu . ")</i>";
          } else {
            $plus = " <b>R.péda NON SAISI DANS GAIA !!</b>";
          }
        };
        $timer = variable_get('ico_clockGreen');
        if (strtotime($dateD) < time()) { // le premier jour dépassé
          $timer = variable_get('ico_clockRed') ;
        } elseif(strtotime($dateD) < time() + 1296000) { // le premier jour est dans moins de 15 jours.
          $timer = variable_get('ico_clockOrange');
        };
        if ($dateF != '2061-07-16' && strtotime($dateF) < time()) { // le dernier jour jour dépassé donc formation finie
          $timer = variable_get('ico_finish');
        }

        if ($dateD > 0) {
          if ($dateD==$dateF || $dateF=='2061-07-16') {
            $dates = $timer .
              t( "&nbsp;" .
              strftime('%d/%m/%y', strtotime($dateD))) ;
          } else {
            $dates = $timer .
              t( "&nbsp;" .
              strftime('%d/%m/%y', strtotime($dateD)) .
              "&rarr;" .
              strftime('%d/%m/%y', strtotime($dateF)));
          };
        } else { $dates =''; };
        $DA = "";
        if ($DAdd !="NaN" && $DAdd !="1970-01-01 00:00:00") {
          $DA = variable_get('ico_DArendu')
            . " " .strftime('%d/%m/%y', strtotime($DAdd));
        };
        $queryev = db_select('gbb_evaluation', 'e');
        $queryev ->condition('e.co_modu', $r->co_modu, '=')
          ->condition('e.co_degre', arg(2), '=')
          #->fields('e',  array('groupe','syntheseEvalForm'));
          ->fields('e',  array('groupe','remqAnalysesRD'));
        $resultev = $queryev->execute();
        $evalbilan = '';
        if (($resultev->rowCount() != 0)) {
          $evalbilan = variable_get('ico_evals');
          foreach ($resultev as $rrv) {
            #if ($rrv->syntheseEvalForm !='') {
            if ($rrv->remqAnalysesRD !='') {
              $evalbilan = variable_get('ico_bilans');
            };
          };
        };
        $organisation = (strlen($r->organisation)>0) ? variable_get('ico_organisation') : variable_get('ico_organisation-o'); 
        // La liste des sessions pour le module
        $qf = db_select('gbb_session', 's');
        $qf ->leftjoin('gbb_gresp_dafor', 'r',
          'r.co_resp = s.co_resp AND r.co_degre=s.co_degre');
        $qf ->condition('s.co_degre', arg(2), '=')
          ->condition('s.co_modu', $r->co_modu, '=')
          ->fields('r', array('nomu', 'prenom'))
          ->fields('s', array('date', 'en_attente', 'convoc_sent'));
        $fo = $qf->execute();

        $items = array();
        foreach ($fo as $f) {
          $ico = ($f->en_attente)? variable_get('ico_attente') : variable_get('ico_notAttente') ;
          if ($f->convoc_sent) $ico = variable_get('ico_sent');
          $date = date("d/m/y", strtotime($f->date));
          $items[] = "$ico $date - $f->prenom  $f->nomu";
        };
        $formateurs = theme('item_list', array('items' => $items));
        // ------------------------------------------------------------

        $rows[] = array(
          'col0' => array(
            'data' => "<span class='$paf_ou_fil $d_ouvert_ou_ferme'>" .
            "[" . strtoupper($paf_ou_fil) . "] $candidature ".
            $r->id_disp . ' ' . t($r->libd) . '</span> '
          ),
          'col1' => array(
            'data' => //$attachement .
            $module_printed .
            $convoc_sent .
            $session_alert .
            $NOT_en_attente .
            $en_attente .
            //$nb_nea.' '. $nb_s.
            $module_alert .
            $prioritaire,
            'class' => 'nowrap',
          ),
          'col2' => array(
            'data' => $organisation . l( $r->co_modu,
            'module/' . arg(2) . '/' . $r->co_modu,
            $options_co_modu) .
            " <span class='$m_ouvert_ou_ferme'>" .
            #t($r->libm) . $plus . '</span> ',
            #TODO TODO 
            #TODO TODO 
            #TODO TODO 
            #TODO TODO 
            t($r->libm) . '</span> ',
              ),
              'col3' => array(
                'data' => nl2br($r->organisation). $formateurs ,
              ),
              'col4' => array(
                'data' => $dates . $evalbilan . $DA,
              ),
            );
        $libd_precedent = $r->libd;
      }
      $attributes = array('id' => 'table-id',
        'class' => array('display'));
      return theme('table', array('rows' => $rows,
        'attributes' => $attributes));
}
