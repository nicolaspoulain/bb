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
function gbb_bilan_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  //$build['infos_gaia']   = gbb_infos_general($args); // sur page_gest_module.inc
  $build['bilan'] = render(drupal_get_form('gbb_form_bilan' , $args));

  return implode('', $build);
}


/**
 * Formulaire de saisie des conditions ** ENVIRONNEMENT ** du stage
*/
function gbb_form_bilan($form, &$form_state) {

  if (arg(3)=='') return '';

  $query = db_select('gbb_evaluation', 'e');
  $query   ->condition('e.co_degre', arg(1), '=')
           ->condition('e.co_modu', arg(2), '=')
           ->condition('e.groupe', arg(3), '=')
           ->fields('e', array('co_degre',
                               'co_modu',
                               'groupe',
                               'nbConvoques',
                               'moyConvoques',
                               'nbEvalStag',
                               'syntheseEvalSta',
                               'syntheseEvalForm',
                               'condMateriellesAccueil',
                               'besoinsParticip',
                               'besoinsForm',
                               'remqAnalysesRD',
                               ));
  $r = $query->execute()->fetchAssoc();

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bilan des évaluations formateur et stagiaire pour le module ').arg(2).t(' groupe ').arg(3),
  );
  $form['f']['co_degre'] = array('#type' => 'hidden','#value' => arg(1));
  $form['f']['co_modu'] = array('#type' => 'hidden','#value' => arg(2));
  $form['f']['groupe'] = array('#type' => 'hidden','#value' => arg(3));
  $form['f']['nbConvoques'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de convoqués sur module'),
    '#default_value' => (($r['nbConvoques']=='')? 0 : $r['nbConvoques']),
    '#size' => 4,
    '#maxlength' => 20,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
  );
  $form['f']['moyConvoques'] = array(
    '#type' => 'textfield',
    '#title' => t('Moyenne des présents sur module'),
    '#default_value' => (($r['moyConvoques']=='')? 0 : $r['moyConvoques']),
    '#size' => 4,
    '#maxlength' => 20,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
  );
  $form['f']['nbEvalStag'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre d\'évaluations stagiaires '),
    '#default_value' => (($r['nbEvalStag']=='')? 0 : $r['nbEvalStag']),
    '#size' => 4,
    '#maxlength' => 20,
    '#prefix' => '&nbsp;<div class="inline">',
    '#suffix' => '</div><br/>',
  );
  $form['f']['syntheseEvalSta'] = array(
    '#type' => 'textarea',
    '#title' => t('Synthèse des évaluations stagiaires'),
    '#default_value' => $r['syntheseEvalSta'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['syntheseEvalForm'] = array(
    '#type' => 'textarea',
    '#title' => t('Synthèse de la fiche évaluation formateur'),
    '#default_value' => $r['syntheseEvalForm'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['condMateriellesAccueil'] = array(
    '#type' => 'textarea',
    '#title' => t('Conditions matérielles et accueil'),
    '#default_value' => $r['condMateriellesAccueil'],
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
    '#title' => t('Besoins identifiés par le formateur :'),
    '#default_value' => $r['besoinsForm'],
    '#size' => 40,
    '#rows' => 3,
    '#maxlength' => 1000,
  );
  $form['f']['remqAnalysesRD'] = array(
    '#type' => 'textarea',
    '#title' => t('Remarques et analyse du conseiller'),
    '#default_value' => $r['remqAnalysesRD'],
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
function gbb_form_bilan_submit($form, &$form_state) {

// Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_evaluation')
    ->key(array('co_degre' => $form_state['values']['co_degre'],
                'co_modu'  => $form_state['values']['co_modu'],
                'groupe'   => $form_state['values']['groupe'],
             ))
    ->fields(array('nbConvoques'            => $form_state['values']['nbConvoques'],
                   'moyConvoques'           => $form_state['values']['moyConvoques'],
                   'nbEvalStag'             => $form_state['values']['nbEvalStag'],
                   'syntheseEvalSta'        => $form_state['values']['syntheseEvalSta'],
                   'syntheseEvalForm'       => $form_state['values']['syntheseEvalForm'],
                   'condMateriellesAccueil' => $form_state['values']['condMateriellesAccueil'],
                   'besoinsParticip'        => $form_state['values']['besoinsParticip'],
                   'besoinsForm'            => $form_state['values']['besoinsForm'],
                   'remqAnalysesRD'         => $form_state['values']['remqAnalysesRD'],
             ))
    ->execute();
  drupal_set_message(t('Enregistrement effectué.'));
}


