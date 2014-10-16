<?php
/**
 * @file
 *
 * Composition de la page de gestion des formateurs
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 * affichant une liste de responsables et les stages qui leur
 * associes
 */

function gbb_formateur_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE)
  );
  // Construction de la page
  $build = array();
  $build['filtre'] = render(drupal_get_form('gbb_formateur_filtre' , $args));
  $build['fiche']  = render(drupal_get_form('gbb_formateur_fiche' , $args));
  $build['stages'] = theme('fieldset',
                           array(
                             'element' => array(
                               '#attributes' => array(
                                 'class' => array('details'),
                               ),
                               '#children' => '',
                               '#title' => t('Graphique de répartition des heures'),
                               '#value' => gbb_formateur_stages($args),
                             )
                           )
                     );
  return implode('', $build);
}

/**
 * Formulaire de ** CHOIX ** du formateur à éditer
 */

function gbb_formateur_filtre($form, &$form_state) {

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choix de la fiche formateur à éditer'),
  );
  $form['f']['co_resp'] = array(
    '#type' => 'textfield',
    '#default_value' => arg(1),
    '#title' => t('Rechercher un FORMATEUR... ou retournez à la <a href="../views_liste_formateurs">liste des formateurs <i class="fa fa-user fa-fw"></i></a>'),
    '#description' => t('Saisissez quelques lettres du nom
    pour rechercher un formateur. '),
    '#autocomplete_path' => 'autocomp/formateur2',
    '#prefix' => '<div class="ajaxform inline">',
    '#suffix' => '</div>',
    '#size' => 80,
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
function gbb_formateur_filtre_submit($form, &$form_state) {
  $replace = array ('\1');
  $pattern = array ('/.*\(id:(.*)\)/');
  $co_resp = preg_replace($pattern, $replace,
                          $form_state['values']['co_resp']);
  $url = url('formateur/' . $co_resp,
                            array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}


/**
 * Formulaire de ** MODIFICATION ** de la fiche formateur
*/

function gbb_formateur_fiche($form, &$form_state) {

  if (arg(1)=='') return '';
  $query = db_select('gbb_gresp_dafor', 'r');
  $query ->leftjoin('gbb_gresp_plus', 'rp', 'r.co_resp=rp.co_resp');
  $query ->condition('r.co_resp', arg(1), '=')
         ->fields('r',  array('co_resp', 
                              'nomu',
                              'prenom',
                              'mel',
                              'tel'))
         ->fields('rp', array('discipline',
                              'resp_dafor',
                              'decharge',
                              'grade',
                              'statut',
                              'divers'));
  $r = $query->execute();
  if ($r->rowCount() == 0) {
    $record = array('nomu'=>'', 'prenom'=>'',
                    'prenom' =>'', 'mel'=>'', 'tel'=>'',
                    'discipline'=>'', 'resp_dafor'=>'',
                    'grade'=>'', 'decharge'=>'', 'divers'=>'');
  } else {
    $record =  $r->fetchAssoc();
  };

  if (arg(1)=='add'){ //TODO : reprendre cette ligne !!
    $record['co_resp'] = db_query("SELECT MAX(co_resp)+1 as max_id FROM gbb_gresp_dafor")
                         ->fetchField();
  }
  $record['co_degre'] = '2';

  $form['f'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Fiche formateur (Nom, prénom, adresse, décharge etc...)'),
  );

  $form['f']['co_resp'] = array(
    '#type' => 'hidden',
    '#value' => $record['co_resp'],
  );
  $form['f']['codegre'] = array(
    '#type' => 'hidden',
    '#value' => $record['co_degre'],
  );
  $form['f']['nomu'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom'),
    '#default_value' => $record['nomu'],
    '#size' => 40,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#disabled' => (($record['co_resp'] == "1")? TRUE : FALSE),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['prenom'] = array(
    '#type' => 'textfield',
    '#title' => t('Prénom'),
    '#default_value' => $record['prenom'],
    '#size' => 40,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#disabled' => (($record['co_resp'] == "1")? TRUE : FALSE),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['statut'] = array(
    '#type' => 'checkbox',
    '#title' => t('IUFM'),
    '#default_value' => (isset($record['statut']) && $record['statut']==1) ? 1 : 0,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div><br/>',
  );
  $form['f']['mel'] = array(
    '#type' => 'textfield',
    '#title' => t('email'),
    '#default_value' => $record['mel'],
    '#size' => 40,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['tel'] = array(
    '#type' => 'textfield',
    '#title' => t('Téléphone'),
    '#default_value' => $record['tel'],
    '#size' => 40,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div><br/>',
  );
  $form['f']['discipline'] = array(
    '#type' => 'textfield',
    '#title' => t('Discipline'),
    '#default_value' => $record['discipline'],
    '#size' => 40,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['grade'] = array(
    '#type' => 'select',
    '#title' => t('Grade'),
    '#default_value' => $record['grade'],
    '#options' => drupal_map_assoc(array(
                    '', 'NOMENCLATURE', 'VACATAIRE', 'CONTRACTUEL', 'MA',
                    'PEGC', 'PLP', 'CERTIFIE', 'AGREGE', 'INST', 'PE', 'COP',
                    'CPE', 'INF', 'MED', 'ING', 'ASU', 'CASU', 'AS', 'PERDIR',
                    'IA-IPR', 'IEN-EG', 'IEN-ET', 'IEN-CC', 'CC', 'PREC',
                    'PRCE', 'PRAG', 'MC', 'PR', 'ASSOCIATION', 'ENTREPRISE',
                    'UNIVERSITE', 'INTERVENANT-XT',
    )),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );
  $form['f']['decharge'] = array(
    '#type' => 'textfield',
    '#title' => t('Décharge (h)'),
    '#default_value' => $record['decharge'],
    '#size' => 10,
    '#element_validate' => array('element_validate_number'),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );
  $form['f']['resp_dafor'] = array(
    '#type' => 'textfield',
    '#title' => t('Responsable DAFOR'),
    '#default_value' => $record['resp_dafor'],
    '#size' => 10,
    '#maxlength' => 128,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  $form['f']['divers'] = array(
    '#type' => 'textarea',
    '#title' => t('Divers'),
    '#default_value' => $record['divers'],
    '#rows' =>2,
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
function gbb_formateur_fiche_submit($form, &$form_state) {
  $query = db_select('gbb_gresp_dafor', 'r');
  $query ->condition('r.nomu', $form_state['values']['nomu'], '=')
         ->condition('r.prenom', $form_state['values']['prenom'], '=')
         ->fields('r',  array('nomu'));
  $nb = $query->execute()->rowCount();
  //if ( $nb > 0 ) {
  //  drupal_set_message( t('Ce formateur existe déjà dans la base.') );
  //  return;
  //}

  // Merge Queries : http://drupal.org/node/310085
  db_merge('gbb_gresp_dafor')
    ->key(array('co_resp'  => $form_state['values']['co_resp'],
             ))
    ->fields(array('nomu'     => $form_state['values']['nomu'],
                   'prenom'   => $form_state['values']['prenom'],
                   'mel'      => $form_state['values']['mel'],
                   'tel'      => $form_state['values']['tel'],
                   'co_degre' => $form_state['values']['codegre'],
             ))
    ->execute();
  if ($form_state['values']['decharge']=='') {
      $form_state['values']['decharge']='0.0';
  };
  db_merge('gbb_gresp_plus')
    ->key(array('co_resp'  => $form_state['values']['co_resp'],
             ))
    ->fields(array('discipline' => $form_state['values']['discipline'],
                   'resp_dafor' => $form_state['values']['resp_dafor'],
                   'decharge'   => $form_state['values']['decharge'],
                   'grade'      => $form_state['values']['grade'],
                   'statut'     => $form_state['values']['statut'],
                   'divers'     => $form_state['values']['divers'],
             ))
    ->execute();

  $url = url('formateur/' . $form_state['values']['co_resp'],
                            array('absolute' => TRUE));
  $form_state['redirect'] = $url;
}


/**
 * Un tableau qui affiche les détails des interventions du formateur
 */
function gbb_formateur_stages($args) {


  $annee = '14';
  if ($args == 'NaN') return "Vide";
  if (arg(1) == 'add') return "";

  $query = db_select('gbb_session', 's');
  $query ->leftjoin('gbb_gmodu', 'm', 
                    'm.co_modu = s.co_modu AND m.co_degre = s.co_degre'
           );
  $query ->leftjoin('gbb_gresp_plus', 'r',  'r.co_resp = s.co_resp');
  $query ->leftjoin('gbb_gdisp', 'd', 
                    'd.co_disp = m.co_disp AND d.co_degre = s.co_degre'
           );
  $query ->condition('s.co_resp', arg(1), '=')
         ->condition('s.co_degre', '2', '=')
         ->condition('id_disp', db_like($annee) . '%', 'LIKE')
         ->fields('r', array('decharge',))
         ->distinct();
  $query ->addExpression('SUM(duree_prevue)', 'sumprevue');
  $query ->addExpression('SUM(duree_a_payer)', 'sumapayer');
  $r = $query->execute()->fetchObject();

  //**** les vacations **************
  $query = db_select('gbb_session', 's');
  $query ->leftjoin('gbb_gmodu', 'm', 
                    'm.co_modu = s.co_modu AND m.co_degre = s.co_degre'
           );
  $query ->leftjoin('gbb_gdisp', 'd', 
                    'd.co_disp = m.co_disp AND d.co_degre = s.co_degre'
           );
  $query ->condition('s.co_resp', arg(1), '=')
         ->condition('s.co_degre', '2', '=')
         ->condition('s.type_paiement', 'VAC', 'LIKE')
         ->condition('id_disp', db_like($annee) . '%', 'LIKE')
         ->distinct();
  $query ->addExpression('SUM(duree_a_payer)', 'sumapayervac');
  $r2 = $query->execute()->fetchObject();

  //**** la decharge **************
  $query = db_select('gbb_session', 's');
  $query ->leftjoin('gbb_gmodu', 'm', 
                    'm.co_modu = s.co_modu AND m.co_degre = s.co_degre'
           );
  $query ->leftjoin('gbb_gdisp', 'd', 
                    'd.co_disp = m.co_disp AND d.co_degre = s.co_degre'
           );
  $query ->condition('s.co_resp', arg(1), '=')
         ->condition('s.co_degre', '2', '=')
         ->condition('s.type_paiement', 'DECH', 'LIKE')
         ->condition('id_disp', db_like($annee) . '%', 'LIKE')
         ->distinct();
  $query ->addExpression('SUM(duree_a_payer)', 'sumapayerdec');
  $r3 = $query->execute()->fetchObject();

  //_________________________
  if (isset($r)) {
    $chart = array(
      '#type' => 'chart',
      '#chart_type' => 'bar',
      '#title' => t('Année 20').$annee,
      '#stacking' => TRUE,
    );
    $chart['decharge'] = array(
      '#type' => 'chart_data',
      '#data' => array(27*$r->decharge,0,0),
      '#title' => t(' '),
      '#suffix' => 'h',
    );
    $chart['Prevue'] = array(
      '#type' => 'chart_data',
      '#data' => array(0, $r->sumprevue, 0),
      '#title' => t(' '),
      '#suffix' => 'h',
    );
    $chart['ApayerDech'] = array(
      '#type' => 'chart_data',
      '#title' => t('en déch.'),
      '#data' => array(0, 0, $r3->sumapayerdec),
      '#suffix' => 'h',
    );
    $chart['ApayerVac'] = array(
      '#type' => 'chart_data',
      '#title' => t('en vac.'),
      '#data' => array(0, 0, $r2->sumapayervac),
      '#suffix' => 'h',
    );
    $chart['ApayerAutres'] = array(
      '#type' => 'chart_data',
      '#data' => array(0, 0, $r->sumapayer-$r3->sumapayerdec-$r2->sumapayervac),
      '#title' => t('autres'),
      '#suffix' => 'h',
    );
    $chart['xaxis'] = array(
      '#type' => 'chart_xaxis',
      '#labels' => array('Décharge', 'Durée à payer', 'Durée payée'),
      '#suffix' => 'h',
    );
    $output = drupal_render($chart);
    return $output;
  }

}

