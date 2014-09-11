<?php
/**
 * @file
 *
 * Composition de la page de gestion des établissements
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 * affichant une liste de responsables et les stages qui leur
 * associes
 */
function gbb_etablissement_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM-1, 'preprocess' => FALSE)
  );
  // Construction de la page
  $build = array();
  $build['filtre'] = render(drupal_get_form('gbb_etablissement_filtre', $args));
  $build['fiche']  = render(drupal_get_form('gbb_etablissement_fiche' , $args));

  return implode('', $build);
}

/**
 * Formulaire de ** CHOIX ** de l'établissement à éditer
 */

function gbb_etablissement_filtre($form, &$form_state) {

  // requete sur gbb_gmodu_plus. Le rightjoin sur gbb_gmodu assure un résultat.
  $query = db_select('gbb_netab_dafor', 'e')
         ->fields('e', array('co_lieu',
                             'denom_comp',
                             'sigle'))
         ->orderBy('denom_comp', 'DESC');
  $result = $query->execute();

  foreach ($result as $r) {
    $rows[$r->co_lieu] = $r->denom_comp . ' (' . $r->sigle . ')';
  }
  unset($rows['']);
  if (user_access('gest_etablissements gaiabb')) {
    $rows['add'] = '  ** AJOUTER UN ETABLISSEMENT **';
  };
  asort($rows);

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choix de la fiche établissement à éditer'),
  );

  $form['f']['colieu'] = array(
    '#type' => 'select',
    '#default_value' => arg(1),
    '#options' => $rows,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  $form['f']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Envoyer',
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * ----> Submit
 */
function gbb_etablissement_filtre_submit($form, &$form_state) {

  $url = url('etablissement/' . $form_state['values']['colieu'],
                            array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}


/**
 * Formulaire de ** MODIFICATION ** de la fiche formateur
*/
function gbb_etablissement_fiche($form, &$form_state) {

  if (arg(1)=='') return '';

  $query = db_select('gbb_netab_dafor', 'e');
  $query ->condition('e.co_lieu', arg(1), '=')
         ->fields('e', array('co_lieu', 
                             'denom_comp',
                             'sigle',
                             'adr',
                             'cp',
                             'tel',
                             'fax',
                             'mel',
             ));
  $record = $query->execute()->fetchObject();

  if (arg(1)=='add'){
    $record->co_lieu = '';
    $record->denom_comp = '';
    $record->sigle = '';
    $record->adr = '';
    $record->cp = '';
    $record->tel = '';
    $record->fax = '';
    $record->mel = '';
  }

  $form['f'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Fiche établissement'),
  );

  $form['f']['colieu'] = array(
    '#type' => 'textfield',
    '#title' => t('RNE (non modifiable)'),
    '#description' => t('Pour ajout ou modification de fiche,'),
    '#default_value' => $record->co_lieu,
    '#size' => 40,
    '#maxlength' => 128,
    '#disabled' => TRUE,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['sigle'] = array(
    '#type' => 'select',
    '#title' => t('Sigle'),
    '#description' => t('contacter'),
    '#default_value' => $record->sigle,
    '#disabled' => TRUE,
    '#options' => drupal_map_assoc(array('', 'CLG', 'LP', 'LYC', 'CIO', 'LPO', 
                                         'LGT', 'LG', 'EREA', 'LT', 'SEGPA', 
                                         'SEP', 'ECOLE', 'UNIV', 'EXT', 'LYC_METIER', 'CRDP',
    )),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );
  $form['f']['denomcomp'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom (non modifiable)'),
    '#description' => t('Catherine Laigle ou Christian Muir'),
    '#default_value' => $record->denom_comp,
    '#size' => 40,
    '#maxlength' => 128,
    '#disabled' => TRUE,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  if (user_access('gest_etablissements gaiabb')) {
    $form['f']['colieu']['#title' ] = t('RNE');
    $form['f']['colieu']['#disabled' ] = FALSE;
    $form['f']['colieu']['#required' ] = TRUE;
    $form['f']['sigle']['#title' ] = t('Sigle');
    $form['f']['sigle']['#disabled' ] = FALSE;
    $form['f']['sigle']['#required' ] = TRUE;
    $form['f']['denomcomp']['#title' ] = t('Nom');
    $form['f']['denomcomp']['#disabled' ] = FALSE;
    $form['f']['denomcomp']['#required' ] = TRUE;
  }
  $form['f']['adr'] = array(
    '#type' => 'textfield',
    '#title' => t('Adresse'),
    '#default_value' => $record->adr,
    '#size' => 40,
    '#maxlength' => 128,
  );
  $form['f']['mel'] = array(
    '#type' => 'textfield',
    '#title' => t('email'),
    '#default_value' => $record->mel,
    '#size' => 40,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['tel'] = array(
    '#type' => 'textfield',
    '#title' => t('Téléphone'),
    '#default_value' => $record->tel,
    '#size' => 40,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#default_value' => $record->fax,
    '#size' => 40,
    '#maxlength' => 128,
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
function gbb_etablissement_fiche_submit($form, &$form_state) {

  // Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_netab_dafor')
    ->key(array('co_lieu'  => $form_state['values']['colieu'],
             ))
    ->fields(array('co_lieu'   => $form_state['values']['colieu'],
                   'sigle'     => $form_state['values']['sigle'],
                   'denom_comp'=> $form_state['values']['denomcomp'],
                   'adr'       => $form_state['values']['adr'],
                   'mel'       => $form_state['values']['mel'],
                   'tel'       => $form_state['values']['tel'],
                   'fax'       => $form_state['values']['fax'],
             ))
    ->execute();

  $url = url('etablissement/' . $form_state['values']['colieu'],
                            array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}
