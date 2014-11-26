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
function gbb_evaluation_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  //$build['infos_gaia']   = gbb_infos_general($args); // sur page_gest_module.inc
  //$build['infos_sessions_pour_ce_groupe']   = gbb_infos_sessions($args); // sur page_gest_module.inc
  $build['environnement'] = render(drupal_get_form('form_environnement' , $args));
  $build['group_participants'] = render(drupal_get_form('form_groupe_participants' , $args));
  $build['formation'] = render(drupal_get_form('form_formation' , $args));

  return implode('', $build);
}

/**
 * Un tableau à deux lignes qui affiche le dispo et le module
 */
function gbb_infos_sessions($args) {

  $query = db_select('gbb_session', 's');
  $query  ->leftjoin('gbb_gresp_dafor', 'r',  'r.co_resp = s.co_resp AND r.co_degre=s.co_degre');
  $query   ->condition('s.co_degre', arg(1), '=')
           ->condition('s.co_modu', arg(2), '=')
           ->condition('s.groupe', arg(3), '=')
           ->distinct()
           ->fields('r', array('nomu', 'prenom'));
  $result = $query->execute();
  $items = array();
  foreach ($result as $r) {
    $items[] = $r->prenom . ' ' . $r->nomu;
  };
  $formateurs = theme('item_list', array('items' => $items));

  $query = db_select('gbb_session', 's');
  $query   ->condition('s.co_degre', arg(1), '=')
           ->condition('s.co_modu', arg(2), '=')
           ->condition('s.groupe', arg(3), '=')
           ->distinct()
           ->fields('s', array('date'));
  $result = $query->execute();
  $items = array();
  setlocale(LC_TIME, 'fr_FR');
  foreach ($result as $r) {
    $items[] = utf8_encode(strftime('%A %e %B %Y ', strtotime($r->date)));
  };
   $dates = theme('item_list', array('items' => $items));

  $header = array('Formateur(s)', 'Date(s)');
  $rows = array();
    $rows[] = array( 
                array('data' => 'Groupe' . arg(3),
                      'colspan' => '2',
                )
              );
  $rows[] = array($formateurs, $dates);

  return theme('table', array('header' => $header, 'rows' => $rows ));;
}


/**
 * Formulaire de saisie des conditions ** ENVIRONNEMENT ** du stage
*/
function form_environnement($form, &$form_state) {

  if (arg(3)=='') return '';

  $query = db_select('gbb_evaluation', 'e');
  $query   ->condition('e.co_degre', arg(1), '=')
           ->condition('e.co_modu', arg(2), '=')
           ->condition('e.groupe', arg(3), '=')
           ->fields('e', array('co_degre',
                               'co_modu', 
                               'groupe',
                               'satisAccueil',
                               'commAccueil',
                               'satisSalle',
                               'commSalle',
                               'satisMatos',
                               'commMatos',
                               'rencontrePrep',
                               ));
  $r = $query->execute()->fetchAssoc();

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Environnement de la formation'),
  );
  $form['f']['co_degre'] = array('#type' => 'hidden','#value' => arg(1));
  $form['f']['co_modu'] = array('#type' => 'hidden','#value' => arg(2));
  $form['f']['groupe'] = array('#type' => 'hidden','#value' => arg(3));
  $form['f']['satisAccueil'] = array(
    '#type' => 'radios',
    '#title' => t('Accueil'),
    '#default_value' => $r['satisAccueil'],
    '#options' => array(1 => t('Satisfaisant'),  0 => t('Non satisfaisant')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commAccueil'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commAccueil'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisAccueil"]' => array('value' => 0),),
    ),
  );
  $form['f']['satisSalle'] = array(
    '#type' => 'radios',
    '#title' => t('Salle'),
    '#default_value' => $r['satisSalle'],
    '#options' => array(1 => t('Satisfaisant'),  0 => t('Non satisfaisant')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commSalle'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commSalle'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisSalle"]' => array('value' => 0),),
    ),
  );

  $form['f']['satisMatos'] = array(
    '#type' => 'radios',
    '#title' => t('Matériel mis à disposition'),
    '#default_value' => $r['satisMatos'],
    '#options' => array(1 => t('Satisfaisant'),  0 => t('Non satisfaisant')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
$form['f']['commMatos'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commMatos'],
    '#size' => 40,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisMatos"]' => array('value' => 0),),
    ),
  );

  $form['f']['rencontrePrep'] = array(
    '#type' => 'radios',
    '#title' => t('Pour les FIL, y a-t-il eu une rencontre préparatoire ?'),
    '#default_value' => $r['rencontrePrep'],
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  $form['f']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Enregistrer',
  );

  return $form;
}

/**
 * ----> Submit
 */
function form_environnement_submit($form, &$form_state) {

// Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_evaluation')
    ->key(array('co_degre' => $form_state['values']['co_degre'],
                'co_modu'  => $form_state['values']['co_modu'],
                'groupe'   => $form_state['values']['groupe'],
             ))
    ->fields(array('satisAccueil' => $form_state['values']['satisAccueil'],
                   'commAccueil'  => $form_state['values']['commAccueil'],
                   'satisSalle'   => $form_state['values']['satisSalle'],
                   'commSalle'    => $form_state['values']['commSalle'],
                   'satisMatos'   => $form_state['values']['satisMatos'],
                   'commMatos'    => $form_state['values']['commMatos'],
                   'rencontrePrep'=> $form_state['values']['rencontrePrep'],
             ))
    ->execute();
  drupal_set_message(t('Enregistrement effectué.'));
}

/**
 * Formulaire de saisie des conditions ** GROUPE DES PARTICIPANTS ** du stage
*/
function form_groupe_participants($form, &$form_state) {

  if (arg(3)=='') return '';

  $query = db_select('gbb_evaluation', 'e');
  $query   ->condition('e.co_degre', arg(1), '=')
           ->condition('e.co_modu', arg(2), '=')
           ->condition('e.groupe', arg(3), '=')
           ->fields('e', array('co_degre',
                               'co_modu', 
                               'groupe',
                               'satisEffectif',
                               'commEffectif',
                               'satisAssiduite',
                               'commAssiduite',
                               'satisCooper',
                               'commCooper',
                               'satisPrerequis',
                               'commPrerequis',
                               ));
  $r = $query->execute()->fetchAssoc();

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Groupe des participants'),
  );
  $form['f']['co_degre'] = array('#type' => 'hidden','#value' => arg(1));
  $form['f']['co_modu'] = array('#type' => 'hidden','#value' => arg(2));
  $form['f']['groupe'] = array('#type' => 'hidden','#value' => arg(3));
  $form['f']['satisEffectif'] = array(
    '#type' => 'radios',
    '#title' => t('Effectif adapté'),
    '#default_value' => $r['satisEffectif'],
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commEffectif'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commEffectif'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisEffectif"]' => array('value' => 0),),
    ),
  );
  $form['f']['satisAssiduite'] = array(
    '#type' => 'radios',
    '#title' => t('Assiduité'),
    '#default_value' => $r['satisAssiduite'],
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commAssiduite'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commAssiduite'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisAssiduite"]' => array('value' => 0),),
    ),
  );
  $form['f']['satisCooper'] = array(
    '#type' => 'radios',
    '#title' => t('Coopération'),
    '#default_value' => $r['satisCooper'],
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commCooper'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commCooper'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisCooper"]' => array('value' => 0),),
    ),
  );
  $form['f']['satisPrerequis'] = array(
    '#type' => 'radios',
    '#title' => t('Prérequis respecté'),
    '#default_value' => $r['satisPrerequis'],
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['commPrerequis'] = array(
    '#type' => 'textfield',
    '#default_value' => $r['commPrerequis'],
    '#size' => 60,
    '#maxlength' => 200,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisPrerequis"]' => array('value' => 0),),
    ),
  );

  $form['f']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Enregistrer',
  );

  return $form;
}

/**
 * ----> Submit
 */
function form_groupe_participants_submit($form, &$form_state) {

// Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_evaluation')
    ->key(array('co_degre' => $form_state['values']['co_degre'],
                'co_modu'  => $form_state['values']['co_modu'],
                'groupe'   => $form_state['values']['groupe'],
             ))
    ->fields(array('satisEffectif'  => $form_state['values']['satisEffectif'],
                   'commEffectif'   => $form_state['values']['commEffectif'],
                   'satisAssiduite' => $form_state['values']['satisAssiduite'],
                   'commAssiduite'  => $form_state['values']['commAssiduite'],
                   'satisCooper'    => $form_state['values']['satisCooper'],
                   'commCooper'     => $form_state['values']['commCooper'],
                   'satisPrerequis' => $form_state['values']['satisPrerequis'],
                   'commPrerequis'  => $form_state['values']['commPrerequis'],
             ))
    ->execute();
  drupal_set_message(t('Enregistrement effectué.'));
}

/**
 * Formulaire de saisie des conditions générales de ** LA FORMATION **
*/
function form_formation($form, &$form_state) {

  if (arg(3)=='') return '';

  $query = db_select('gbb_evaluation', 'e');
  $query   ->condition('e.co_degre', arg(1), '=')
           ->condition('e.co_modu', arg(2), '=')
           ->condition('e.groupe', arg(3), '=')
           ->fields('e', array('co_degre',
                               'co_modu', 
                               'groupe',
                               'satisObjectifs',
                               'questionsTraitees',
                               'pointsForts',
                               'ameliorations',
                               'genants',
                               'besoinsParticip',
                               'besoinsForm',
                               ));
  $r = $query->execute()->fetchAssoc();

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('La formation'),
  );
  $form['f']['co_degre'] = array('#type' => 'hidden','#value' => arg(1));
  $form['f']['co_modu'] = array('#type' => 'hidden','#value' => arg(2));
  $form['f']['groupe'] = array('#type' => 'hidden','#value' => arg(3));
  $form['f']['satisObjectifs'] = array(
    '#type' => 'radios',
    '#title' => t('Avez-vous atteint les objectifs prescrits ?'),
    '#options' => array(1 => t('Oui'),  0 => t('Non')),
    '#default_value' => $r['satisObjectifs'],
  );
  $form['f']['questionsTraitees'] = array(
    '#type' => 'textarea',
    '#title' => t('En cas d\'objectifs non atteints, contenu du stage / questions traitées :'),
    '#default_value' => $r['questionsTraitees'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
    '#states' => array(    // This #states rule limits visibility
      'visible' => array(  // action to take.
        ':input[name="satisObjectifs"]' => array('value' => 0),),
    ),
  );
  $form['f']['pointsForts'] = array(
    '#type' => 'textarea',
    '#title' => t('Quels ont été selon vous les points forts de la formation ?'),
    '#default_value' => $r['pointsForts'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['ameliorations'] = array(
    '#type' => 'textarea',
    '#title' => t('Quels ont été selon vous les points de la formation à améliorer ?'),
    '#default_value' => $r['ameliorations'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['genants'] = array(
    '#type' => 'textarea',
    '#title' => t('Indiquez ce qui éventuellement a gêné votre action :'),
    '#default_value' => $r['genants'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['besoinsParticip'] = array(
    '#type' => 'textarea',
    '#title' => t('Perspectives ou besoins exprimés par les participants :'),
    '#default_value' => $r['besoinsParticip'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['besoinsForm'] = array(
    '#type' => 'textarea',
    '#title' => t('Besoins identifiés par vous :'),
    '#default_value' => $r['besoinsForm'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );

  $form['f']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Enregistrer',
  );

  return $form;
}

/**
 * ----> Submit
 */
function form_formation_submit($form, &$form_state) {

// Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_evaluation')
    ->key(array('co_degre' => $form_state['values']['co_degre'],
                'co_modu'  => $form_state['values']['co_modu'],
                'groupe'   => $form_state['values']['groupe'],
             ))
    ->fields(array('satisObjectifs'  => $form_state['values']['satisObjectifs'],
                   'questionsTraitees'   => $form_state['values']['questionsTraitees'],
                   'pointsForts' => $form_state['values']['pointsForts'],
                   'ameliorations'  => $form_state['values']['ameliorations'],
                   'genants'    => $form_state['values']['genants'],
                   'besoinsParticip'     => $form_state['values']['besoinsParticip'],
                   'besoinsForm' => $form_state['values']['besoinsForm'],
             ))
    ->execute();
  drupal_set_message(t('Enregistrement effectué.'));
}




