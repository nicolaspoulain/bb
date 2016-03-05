<?php
/**
 * @file
 *
 * Composition de la page de gestion des évaluations
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 * affichant une liste de responsables et les stages qui leur
 * associes
 */
function gbb_offres_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  $build['search'] = render(drupal_get_form('gbb_offres_filter',$args));
  $build['tab'] = gbb_offres_tab($args);

  return implode('', $build);
}

function gbb_offres_filter($form, &$form_state, $args) {
  $form['#method'] = 'get';
  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('▁ ▂ ▄ ▅ ▆ ▇ █  FILTRER █ ▇ ▆ ▅ ▄ ▂ ▁'),
    '#attributes' => array('class' => array('collapsible', 
                                            'collapsed')),
  );

  $form['f']['co_orie'] = array(
    '#type' => 'textfield',
    '#title' => t('Orientation'),
    '#default_value' => (isset($_GET['co_orie']))? $_GET['co_orie'] : '',
    '#description' => t('p.ex.:PR70'),
    '#size' => 20, 
  );
   $form['f']['no_offre'] = array(
    '#type' => 'textfield',
    '#title' => t('NoOffre'),
    '#default_value' => (isset($_GET['no_offre']))? $_GET['no_offre'] : '',
    '#description' => t('p.ex.:20140020'),
    '#size' => 20, 
  );
   $form['f']['nomu'] = array(
    '#type' => 'textfield',
    '#title' => t('Resp. (dispo)'),
    '#default_value' => (isset($_GET['nomu']))? $_GET['nomu'] : '',
    '#description' => t('p.ex.:CORDIER'),
    '#size' => 20, 
  );
   $form['f']['nomu2'] = array(
    '#type' => 'textfield',
    '#title' => t('Resp. (module)'),
    '#default_value' => (isset($_GET['nomu2']))? $_GET['nomu2'] : '',
    '#description' => t('p.ex.:BESNARD'),
    '#size' => 20, 
  );
   $form['f']['co_tpla'] = array(
    '#type' => 'textfield',
    '#title' => t('Type de plan'),
    '#default_value' => (isset($_GET['co_tpla']))? $_GET['co_tpla'] : '',
    '#description' => t('p.ex.:S'),
    '#size' => 20, 
  );
  $form['f']['submit_co_modu'] = array(
    '#type' => 'submit',
    '#value' => 'Envoyer',
  );
  $form['some_text'] = array(
      '#markup' => '<p>À propos de «Position» : Pour chaque orientation, classer les offres de 1 (indispensable) à 500 (non retenue). Ex-aequo autorisés.</p>'
    );

  return $form;
}

/**
 * ----> Submit
 */
function gbb_offres_filter_submit($form, &$form_state) {

  $form_state['redirect'] = array(
    // $path
    '/offres_edit',
    // $options
    array('query' => array('key' => 'value')),
  );
}



function gbb_offres_tab($args) {

  $header = array(
    'nomu' => t('Interlocuteur dispo'),
    'co_tpla' => t('Type de Plan'),
    'co_orie' => t('Code Orientation'),
    array('data' => t('Position'), 'class' => 'jaune'),
    'no_offre' => t('No Offre/ Code Module'),
    'libl' => t('Titre'),
    'nomu2' => t('Resp. péda.'),
    array('data' => t('Offreurs spécifiques'), 'class' => 'jaune'),
    array('data' => t('Nouv. offreur'), 'class' => 'jaune'),
    array('data' => t('Offre nouvelle'), 'class' => 'jaune'),
    array('data' => t('Pub. Dés.'), 'class' => 'jaune'),
    array('data' => t('Anim. Péda.'), 'class' => 'jaune'),
    #'lmoda' => t('Modalités'),
    #'lcomm' => t('Commentaires (GAIA)'),
    'nb_groupe' => t('Nbre groupe'),
    'nb_eff_groupe' => t('Effectif groupe'),
    'duree_prev' => t('Duree prév. (h)'),
    array('data' => t('Nbre HP'), 'class' => 'jaune'),
    array('data' => t('Nbre vac.'), 'class' => 'jaune'),
    array('data' => t('Taux vac.'), 'class' => 'jaune'),
    // array('data' => t('taux en € Vac'), 'class' => 'jaune'),
    array('data' => t('HT2'), 'class' => 'jaune'),
    #array('data' => t('Hors CDC'), 'class' => 'jaune'),
    array('data' => t('Priorité Nat.'), 'class' => 'jaune'),
    array('data' => t('Priorité Aca.'), 'class' => 'jaune'),
    array('data' => t('&nbsp;&nbsp;&nbsp;Observations&nbsp;&nbsp;&nbsp;'), 'class' => 'jaune'),
  );
  // Number of records (or nodes, in our case) to show per page.
  $count = 20;

  $query = db_select('gbb_gdiof', 'd');
  $query ->leftjoin('gbb_gmoof', 'm',
                    'd.co_offre = m.co_offre');
  $query ->leftjoin('gbb_gdiof_dafor', 'dd',
                    'm.co_omodu = dd.co_omodu');
  $query ->leftjoin('gbb_gresp', 'r',
                    'd.co_resp = r.co_resp AND r.co_degre = 2');
  $query ->leftjoin('gbb_gresp', 'r2',
                    'm.co_resp = r2.co_resp AND r2.co_degre = 2');
  $query ->condition('d.no_offre', '20160000', '>')
         ->fields('d', array('no_offre', 'co_tpla', 'co_orie'))
         ->fields('m', array('libl', 'co_omodu', 'lmoda', 'lcomm','nb_groupe','duree_prev','nb_eff_groupe'))
         ->fields('r', array('nomu'));
  $query ->addField('r2', 'nomu', 'nomu2');
  $query ->fields('dd', array('nb_hp','nb_vac','taux','ht2','iufm',
                              'nouv_offreur','prio_nat','prio_aca','offre_new',
                              'pub_des','anim_peda','comment','position' ));
  $query = $query->extend('PagerDefault')->limit($count);
  $query ->distinct();

  if (isset($_GET['co_orie']) && $_GET['co_orie']!='') $query ->condition('d.co_orie', $_GET['co_orie'], 'LIKE');
  if (isset($_GET['no_offre']) && $_GET['no_offre']!='') $query ->condition('d.no_offre', $_GET['no_offre'], '=');
  if (isset($_GET['nomu']) && $_GET['nomu']!='') $query ->condition('r.nomu', $_GET['nomu'], 'LIKE');
  if (isset($_GET['nomu2']) && $_GET['nomu2']!='') $query ->condition('r2.nomu', $_GET['nomu2'], 'LIKE');
  if (isset($_GET['co_tpla']) && $_GET['co_tpla']!='') $query ->condition('d.co_tpla', $_GET['co_tpla'], 'LIKE');

  $result = $query->execute();
  $nb_off = $result->rowCount();

  $rows = array();
  foreach ($result as $r) {
    $hp = render(drupal_get_form('gbb_offres_nb_hp_form',
                                $r->nb_hp, $r->co_omodu)) ;
    $vac = render(drupal_get_form('gbb_offres_nb_vac_form',
                                $r->nb_vac, $r->co_omodu)) ;
    $taux = render(drupal_get_form('gbb_offres_taux_form',
                                $r->taux, $r->co_omodu)) ;
    $ht2 = render(drupal_get_form('gbb_offres_ht2_form',
                                $r->ht2, $r->co_omodu)) ;
    $prio_nat = render(drupal_get_form('gbb_offres_prio_nat_form',
                                $r->prio_nat, $r->co_omodu)) ;
    $prio_aca = render(drupal_get_form('gbb_offres_prio_aca_form',
                                $r->prio_aca, $r->co_omodu)) ;
    $offre_new = render(drupal_get_form('gbb_offres_offre_new_form',
                                $r->offre_new, $r->co_omodu)) ;
    $comment = render(drupal_get_form('gbb_offres_comment_form',
                                $r->comment, $r->co_omodu)) ;
    
    $position = render(drupal_get_form('gbb_offres_position_form',
                                $r->position, $r->co_omodu)) ;
    $iufm = render(drupal_get_form('gbb_offres_iufm_form',
                                $r->iufm, $r->co_omodu)) ;
    $nouv_offreur = render(drupal_get_form('gbb_offres_nouv_offreur_form',
                                $r->nouv_offreur, $r->co_omodu)) ;
    $pub_des = render(drupal_get_form('gbb_offres_pub_des_form',
                                $r->pub_des, $r->co_omodu)) ;
    $anim_peda = render(drupal_get_form('gbb_offres_anim_peda_form',
                                $r->anim_peda, $r->co_omodu)) ;

    $rows[] = array(
                array('data' => $r->nomu),
                array('data' => $r->co_tpla),
                array('data' => $r->co_orie),
                array('data' => $position),
                array('data' => $r->no_offre.' / '.$r->co_omodu),
                array('data' => l($r->libl,'offre_detail/'.$r->co_omodu,array('attributes' => array('target'=>'_blank')))),
                array('data' => $r->nomu2),
                array('data' => $iufm),
                array('data' => $nouv_offreur),
                array('data' => $offre_new),
                array('data' => $pub_des),
                array('data' => $anim_peda),
                #array('data' => $r->lmoda),
                #array('data' => $r->lcomm),
                array('data' => $r->nb_groupe),
                array('data' => $r->nb_eff_groupe),
                array('data' => $r->duree_prev),
                array('data' => $hp),
                array('data' => $vac),
                array('data' => $taux),
                array('data' => $ht2),
                #array('data' => $hors_cdc),
                array('data' => $prio_nat),
                array('data' => $prio_aca),
                array('data' => $comment),
              );
  }
  $output = theme('table', 
                  array('header' => $header,
                        'rows'   => $rows
                  ));
  return $output . theme('pager', array('tags' => array()));
}

function gbb_offres_nb_hp_form($form, &$form_state, $nb_hp, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['nb_hp'] = array(
    '#type' => 'textfield', '#size' => 1,
    '#default_value' => (isset($nb_hp))? (int)$nb_hp: '0',
    '#ajax' => array(
      'callback' => 'gbb_offres_nb_hp_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_nb_hp_form_submit($form, &$form_state) {
  $val = is_numeric($form_state['values']['nb_hp'])? $form_state['values']['nb_hp']:0;
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('nb_hp'  => $val,
  ))->execute();
}

function gbb_offres_position_form($form, &$form_state, $position, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['position'] = array(
    '#type' => 'textfield', '#size' => 1,
    '#default_value' => (isset($position))? (int)$position : '0',
    '#ajax' => array(
      'callback' => 'gbb_offres_position_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_position_form_submit($form, &$form_state) {
  $val = is_numeric($form_state['values']['position'])? $form_state['values']['position']:0;
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('position'  => $val,
  ))->execute();
}

function gbb_offres_nb_vac_form($form, &$form_state, $nb_vac, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['nb_vac'] = array(
    '#type' => 'textfield', '#size' => 1,
    '#default_value' => (isset($nb_vac))? (int)$nb_vac: '0',
    '#ajax' => array(
      'callback' => 'gbb_offres_nb_vac_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_nb_vac_form_submit($form, &$form_state) {
  $val = is_numeric($form_state['values']['nb_vac'])? $form_state['values']['nb_vac']:0;
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('nb_vac'  => $val, 
  ))->execute();
}

function gbb_offres_taux_form($form, &$form_state, $taux, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['taux'] = array(
    '#type' => 'select',
    '#options' => array('0'=>'0','42'=>'42','52'=>'52','56'=>'56','59'=>'59','70'=>'70'),
    '#default_value' => (int)$taux,
    '#ajax' => array(
      'callback' => 'gbb_offres_taux_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_taux_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('taux'  => $form_state['values']['taux'],
  ))->execute();
}

function gbb_offres_ht2_form($form, &$form_state, $ht2, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['ht2'] = array(
    '#type' => 'textfield', '#size' => 1,
    '#default_value' => (isset($ht2))? (int)$ht2: '0',
    '#ajax' => array(
      'callback' => 'gbb_offres_ht2_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_ht2_form_submit($form, &$form_state) {
  $val = is_numeric($form_state['values']['ht2'])? $form_state['values']['ht2']:0;
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('ht2'  => $val,
  ))->execute();
}

function gbb_offres_hors_cdc_form($form, &$form_state, $hors_cdc, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['hors_cdc'] = array(
    '#type' => 'checkbox', '#size' => 1,
    '#default_value' => $hors_cdc,
    '#ajax' => array(
      'callback' => 'gbb_offres_hors_cdc_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_hors_cdc_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('hors_cdc'  => $form_state['values']['hors_cdc'],
  ))->execute();
}

function gbb_offres_prio_nat_form($form, &$form_state, $prio_nat, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['prio_nat'] = array(
    '#type' => 'select', 
    '#options' => array('0'=>'-',
    'T0'=>'T0','T1'=>'T1','T2'=>'T2','T3'=>'T3','T4'=>'T4',
    'T5'=>'T5','T6'=>'T6','T7'=>'T7','T8'=>'T8','T9'=>'T9',
    'TA'=>'TA',
    'U0'=>'U0','U1'=>'U1','U2'=>'U2','U3'=>'U3','U4'=>'U4',
    'U5'=>'U5','U6'=>'U6','U7'=>'U7','U8'=>'U8','U9'=>'U9',
    'UA'=>'UA', 
    'V1'=>'V1','V2'=>'V2','V3'=>'V3','V4'=>'V4','V5'=>'V5',
    'V6'=>'V6','V7'=>'V7','V8'=>'V8','V9'=>'V9',
    'VA'=>'VA','VB'=>'VB',),
    '#default_value' => $prio_nat,
    '#ajax' => array(
      'callback' => 'gbb_offres_prio_nat_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_prio_nat_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('prio_nat'  => $form_state['values']['prio_nat'],
  ))->execute();
}

function gbb_offres_prio_aca_form($form, &$form_state, $prio_aca, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['prio_aca'] = array(
    '#type' => 'select',
    '#options' => array('-','1','2', '3','4','5'),
    '#default_value' => (is_numeric($prio_aca)? $prio_aca : '0'),
    '#ajax' => array(
      'callback' => 'gbb_offres_prio_aca_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_prio_aca_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('prio_aca'  => $form_state['values']['prio_aca'],
  ))->execute();
}

function gbb_offres_offre_new_form($form, &$form_state, $offre_new, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['offre_new'] = array(
    '#type' => 'checkbox', '#size' => 1,
    '#default_value' => $offre_new,
    '#ajax' => array(
      'callback' => 'gbb_offres_offre_new_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_offre_new_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('offre_new'  => $form_state['values']['offre_new'],
  ))->execute();
}

function gbb_offres_comment_form($form, &$form_state, $comment, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['comment'] = array(
    '#type' => 'textarea', 
    '#cols' => 20, '#rows' => 2,
    '#default_value' => $comment,
    '#ajax' => array(
      'callback' => 'gbb_offres_comment_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_comment_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('comment' => $form_state['values']['comment'],
  ))->execute();
}

function gbb_offres_iufm_form($form, &$form_state, $iufm, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['iufm'] = array(
    #'#type' => 'checkbox', '#size' => 1,
    '#type' => 'select',
    '#options' => array('0'=>'Choisir','ESPE'=>'ESPE','Paris1'=>'Paris1',
                  'Paris3'=>'Paris3','Paris4'=>'Paris4','Paris5'=>'Paris5',
                  'Paris6'=>'Paris6','Paris7'=>'Paris7','Paris8'=>'Paris8',
                  'Paris10'=>'Paris10','CNAM'=>'CNAM','CANOPE'=>'CANOPE',
    'Autres.'=>'Autres org'),
    '#default_value' => $iufm,
    '#ajax' => array(
      'callback' => 'gbb_offres_iufm_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_iufm_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('iufm'  => $form_state['values']['iufm'],
  ))->execute();
}


function gbb_offres_nouv_offreur_form($form, &$form_state, $nouv_offreur, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['nouv_offreur'] = array(
    '#type' => 'checkbox', '#size' => 1,
    '#default_value' => $nouv_offreur,
    '#ajax' => array(
      'callback' => 'gbb_offres_nouv_offreur_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_nouv_offreur_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('nouv_offreur'  => $form_state['values']['nouv_offreur'],
  ))->execute();
}


function gbb_offres_pub_des_form($form, &$form_state, $pub_des, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['pub_des'] = array(
    '#type' => 'checkbox', '#size' => 1,
    '#default_value' => $pub_des,
    '#ajax' => array(
      'callback' => 'gbb_offres_pub_des_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_pub_des_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('pub_des'  => $form_state['values']['pub_des'],
  ))->execute();
}


function gbb_offres_anim_peda_form($form, &$form_state, $anim_peda, $co_omodu) {
  $form['f']['co_omodu']  = array('#type' => 'hidden','#value' => $co_omodu );
  $form['f']['anim_peda'] = array(
    '#type' => 'checkbox', '#size' => 1,
    '#default_value' => $anim_peda,
    '#ajax' => array(
      'callback' => 'gbb_offres_anim_peda_form_submit',
      'progress' => array('type' => 'throbber', 'message' => '')),);
  return $form;
}
function gbb_offres_anim_peda_form_submit($form, &$form_state) {
  db_merge('gbb_gdiof_dafor')
    ->key(array('co_omodu' => $form_state['values']['co_omodu']))
    ->fields(array('anim_peda'  => $form_state['values']['anim_peda'],
  ))->execute();
}

