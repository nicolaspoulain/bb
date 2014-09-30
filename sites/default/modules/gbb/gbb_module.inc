<?php
/**
 * @file
 *
 * Composition de la page de gestion de module
 *
 */

/**
 * Fonction d'appel aux differents elements composant la page
 */
function gbb_module_view($args = 'NaN') {
  // Charge la feuille des style et les fichiers javascript pour le module
  drupal_add_css(drupal_get_path('module', 'gbb') . '/css/gbb.css',
                 array('group' => CSS_SYSTEM -1 , 'preprocess' => FALSE));
  drupal_add_library('system', 'drupal.collapse');

  // Construction de la page
  $build = array();
  $build['infos_general'] = gbb_infos_general($args);
  $build['color_form']  = render(drupal_get_form('gbb_color_form', $args));
  $build['sec_A'] = "<section>";
  if (user_access('gest_sessions gbb')) {
      $build['organis_form'] = render(drupal_get_form('gbb_organis_form', $args));
  }

  if (user_access('gest_convocs gbb')) {
    $build['sess_stagiaire'] = theme('fieldset', 
                                       array(
                                         'element' => array(
                                           '#attributes' => array(
                                             'class' => array('organisation', 
                                                              'collapsible', )),
                                           '#children' => '',
                                           '#title' => t('Convoc stagiaire ...'),
                                           '#value' => gbb_sess_stagiaire($args),
                                         )
                                       )
                                 );
  }
  $build['attachements'] = render(drupal_get_form('gbb_attachements', $args));
  $build['sec_A_end'] = "</section>";
  $build['sess_formatr'] = render(drupal_get_form('gbb_sess_formatr', $args));

  if (isset($_GET['sess_id'])) {
    $build['sess_edition'] = render(drupal_get_form('gbb_sess_edition', $args));
  };
  $build['convoc_form']  = render(drupal_get_form('gbb_convoc_form', $args));
  $build['bilan_form']   = render(drupal_get_form('gbb_bilan_form',$args));
  return implode('', $build);
}

/**
 * Un tableau à deux lignes qui affiche le dispo et le module
 */
function gbb_infos_general($args) {

  $query = db_select('gbb_gmodu', 'm');
  $query ->join('gbb_gdisp', 'ds', 
                'ds.co_disp = m.co_disp AND ds.co_degre = m.co_degre');
  $query ->leftjoin('gbb_norie', 'n',  'n.co_orie = ds.co_orie');
  $query ->leftjoin('gbb_gdire', 'dr', 
                    'dr.co_modu = m.co_modu AND dr.co_degre = m.co_degre');
  $query ->leftjoin('gbb_gresp', 'r',  
                    'r.co_resp  = dr.co_resp AND r.co_degre = m.co_degre');
  $query ->condition('m.co_modu', arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->fields('m',  array('co_modu', 'lautre', 'duree_prev',
                              'lmoda', 'lform', 'co_anmo'))
         ->fields('ds', array('lobjt', 'id_disp',
                              'co_camp', 'co_andi',))
         ->fields('r',  array('prenom', 'nomu',))
         ->fields('dr', array('co_resp', 'co_tres', 'co_degre',));
  $query ->addField('ds', 'lib', 'libd');
  $query ->addField('m',  'lib', 'libm');
  $query ->addField('n',  'lib_long', 'ori');
  $result = $query->execute();
  if (($result->rowCount() == 0)) return 'Module inconnu';

  // --------------------------------------------------------------------
  // Construction des liens vers liste des stages resp.Orga et resp.Péda
  $TRES = array( 1 => t("Interlocuteur"),
                 2 => t("Resp. orga."),
                 3 => t("Resp. péda.")
    );
  $voir = (    user_access('gest_convocs gbb') 
          and !user_access('gest_sessions gbb'))? 2 : 0;
  $str="";
  foreach ($result as $r) {
    if ($r->co_tres == 1 || $r->co_tres == 2 || $r->co_tres == 3 ) {
      $str .= $TRES[$r->co_tres] . " : ";
      if (!user_access('gest_sessions gbb')) {
                     $str .=  l( " $r->prenom  $r->nomu", 
                        'atraiter',
                        array('attributes' =>  array('class' => 'fa fa-play-circle'
                      ),
                      'query' => array('nomu' => $r->nomu),
                                                     'html' => TRUE));
      } else {
        $str .= l( " $r->prenom $r->nomu", 
                 'liste/14/' . $r->co_degre . '/'. $voir .'/' . $r->nomu,
                        array('attributes' =>  array('class' => 'fa fa-th-list'))
              ) ;
      }
      $str .= "&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;";
    }
  }
  // --------------------------------------------------------------------
  $query = db_select('gbb_evaluation', 'e');
  $query ->condition('e.co_modu', arg(2), '=')
         ->condition('e.co_degre', arg(1), '=')
         ->fields('e',  array('groupe'));
  $result = $query->execute();
  $evalStr  = "Pas d'évaluation remplie.";
  if (($result->rowCount() != 0)) {
    $evalStr  = "Evaluation remplies :";
    foreach ($result as $rr) {
      $evalStr  .= l(' gr'.$rr->groupe,'evaluationview/'.arg(1).'/'.arg(2).'/'.$rr->groupe);
    };
  };
  // --------------------------------------------------------------------
  $query = db_select('gbb_session', 's');
  $query ->condition('s.co_modu', arg(2), '=')
         ->condition('s.co_degre', arg(1), '=')
         ->distinct()
         ->fields('s',  array('groupe'));
  $result = $query->execute();
  $bilanStr  = "Pas de bilan car pas de session active.";
  if (($result->rowCount() != 0)) {
    $bilanStr  = "Bilans :";
    foreach ($result as $rr) {
      $bilanStr  .= l(' gr'.$rr->groupe,'bilanview/'.arg(1).'/'.arg(2).'/'.$rr->groupe);
    };
  };
  // Construction du tableau à trois lignes
  $paf_ou_fil = ($r->co_camp == 'BS')? 'fil' : 'paf';
  $d_ouvert_ou_ferme = ($r->co_andi == '')? '' : 'Ferme';
  $m_ouvert_ou_ferme = ($r->co_anmo == '')? '' : 'Ferme';
  $rows[] = array( 
              array('data' => strtoupper($paf_ou_fil) . '&nbsp;-&nbsp;' . 
                              $r->id_disp . ' ' . $r->libd.$r->co_anmo,
                    'class' => array($paf_ou_fil, $d_ouvert_ou_ferme, "sizel"),
                    'colspan' => '2'),
              array('data' => $evalStr),
            );
  $rows[] = array( 
              array('data' => $r->co_modu . ' ' . $r->libm,
                    'class' => array($m_ouvert_ou_ferme, "sizexl"),
                    'colspan' => '2'),
              array('data' => $bilanStr),
            );
  $rows[] = array(
              array('data' => $str),
              array('data' => t(''),
                    'colspan' => '2'),
  );

  return theme('table', array('rows' => $rows));
}

/**
 * Un tableau qui affiche les détails du module
 */
function gbb_infos_detail($args) {

  if ($args == 'NaN') return "";

  $query = db_select('gbb_gmodu', 'm');
  $query ->join('gbb_gdisp', 'ds', 
                'ds.co_disp = m.co_disp AND ds.co_degre = m.co_degre');
  $query ->leftjoin('gbb_norie', 'n',  'n.co_orie = ds.co_orie');
  $query ->leftjoin('gbb_gdire', 'dr', 
                    'dr.co_modu = m.co_modu AND dr.co_degre = m.co_degre');
  $query ->leftjoin('gbb_gresp', 'r',  
                    'r.co_resp  = dr.co_resp AND r.co_degre = m.co_degre');
  $query ->condition('m.co_modu', arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->fields('m',  array('lautre', 'duree_prev', 'lmoda',
                              'lform', 'lcont', 'lpeda', 'lcibl',))
          ->fields('r', array('prenom', 'nomu',))
          ->fields('dr', array('co_resp', 'co_tres',));
  $query  ->addField('ds', 'lobjt');
  $query  ->addField('n', 'lib_long', 'ori');
  $result = $query->execute();

  if ($result->rowCount() == 0) return 'Hum !';
  $r = $result->fetchAssoc();

  $rows[] = array( array('data' => "Objectif Dispositif"),
                   array('data' => $r['lobjt']),);
  $rows[] = array( array('data' => "Objectif Module"),
                   array('data' => $r['lcont']),);
  $rows[] = array( array('data' => "Objectif pédagogique"),
                   array('data' => $r['lpeda']),);
  $rows[] = array( array('data' => "Cible"),
                   array('data' => $r['lcibl']),);
  $rows[] = array( array('data' => "Orientation"),
                   array('data' => $r['ori']),);
  $rows[] = array( array('data' => "Observation"),
                   array('data' => $r['lautre']),);
  $rows[] = array( array('data' => t("Durée")),
                   array('data' => $r['duree_prev'] . "h"),);
  $rows[] = array( array('data' => t("Modalité")),
                   array('data' => $r['lmoda']),);
  $rows[] = array( array('data' => "Forme"),
                   array('data' => $r['lform']),);
  return theme('table', array('rows' => $rows));
}


/**
 * 
 */
function gbb_color_form($args) {

  $query = db_select('gbb_gmodu_plus', 'm')
     ->condition('m.co_modu', arg(2))
     ->condition('m.co_degre', arg(1))
     ->fields('m', array('color'));
  $value = $query->execute()->fetchField();

  $divid = 'div-field-color-field1-und-0--rgb';
  $id = 'edit-field-color-field1-und-0--rgb'; 

  $settings['value'] = $value;
  $settings['id'] = $id;
  

  $form['f'] = array( '#type' => 'fieldset',
                      '#title' => t('Couleur & Détails'),
                      '#attributes' => array('class' => array('color',
                      'collapsible',
                  'collapsed',  )),
  );

  if (user_access('gest_sessions gbb')) {
  $form['f']['color'] = array(
    '#suffix' => '<div id=' . $divid . '></div>',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'gbb') . '/color_field/color_field.js',
        drupal_get_path('module', 'gbb') . '/color_field/color_field.jquery.js',
        array(
          'data' => array('color_field' => array('#' . $divid => $settings)),
          'type' => 'setting',
        ),
      ),
      'css' => array(drupal_get_path('module', 'gbb') . '/color_field/color_field.css'),
    ),
  );

  $form['f']['colormodule'] = array(
    '#attributes' => array('class' => array('element-invisible'),'id' => $id),
    '#type' => 'token',
    '#default_value' => $value,
    '#size' => 7,
    '#maxlength' => 7,
  );
  $comodu = isset($form_state['values']['comodu'])? 
               $form_state['values']['comodu'] : arg(2);
  $form['f']['comodu'] = array('#type' => 'hidden',
                               '#value' => $comodu );

  $codegre = isset($form_state['values']['codegre'])? 
                $form_state['values']['codegre'] : arg(1);
  $form['f']['codegre'] = array('#type' => 'hidden',
                                '#value' => $codegre );

  $form['f']['submit'] = array(
    '#value' => 'Envoyer',
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => array('inline')),
             );
  }
  $form['f']['details']['#markup']= gbb_infos_detail($args);


  return $form;
}
function gbb_color_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('color' => $form_state['values']['colormodule']))
    ->execute();
}


/**
 * Formulaire d' ** ORGANISATION ** de la formation
 */
function gbb_organis_form($form, &$form_state) {

  // requete sur gbb_gmodu_plus. Le rightjoin sur gbb_gmodu assure un résultat.
  $query = db_select('gbb_gmodu_plus', 'mp');
  $query ->rightjoin('gbb_gmodu', 'm', 
                     'm.co_modu=mp.co_modu AND m.co_degre=mp.co_degre');
  $query ->condition('m.co_modu', arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->fields('mp', array('organisation', 'module_alert', 'prioritaire'));
  $r = $query->execute()->fetchAssoc();

  $form['f'] = array( '#type' => 'fieldset',
                      '#title' => t('Organisation'),
                      '#attributes' => array('class' => array('organisation', 
                                                              'collapsible'  )),
  );

  $html = $r['organisation'];
  $txt = preg_replace('#<br\s*/?>#i', "\n", $html); //ce <? est une ASTUCE
  $form['f']['organisation'] = array(
    '#type' => 'textarea',
    '#title' => t('Journal'),
    '#default_value' => $txt,
    '#ajax' => array(
      'callback' => 'gbb_organis_form_submit',
      'progress' => array('type'    => 'throbber', 
                          'message' => 'Enregistrement...'),
    ),
  );
  $form['f']['envoyer']['#markup']= '<div class="flright">' .
    variable_get('ico_save') . '</div>';

  $form['f']['prioritaire'] = array(
    '#type' => 'checkbox',
    '#title' => t( variable_get('ico_bell') . 
                   'Prioritaire' ),
    '#default_value' => $r['prioritaire'],
    '#ajax' => array(
      'callback' => 'gbb_organis_form_submit',
      'progress' => array('type' => 'throbber',
                          'message' => 'Enregistrement...'),
    ),
  );

  $comodu = isset($form_state['values']['comodu'])? 
               $form_state['values']['comodu'] : arg(2);
  $form['f']['comodu'] = array('#type' => 'hidden',
                               '#value' => $comodu );

  $codegre = isset($form_state['values']['codegre'])? 
                $form_state['values']['codegre'] : arg(1);
  $form['f']['codegre'] = array('#type' => 'hidden',
                                '#value' => $codegre );

 return $form;
}

/**
 * ----> Submit
*/
function gbb_organis_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('organisation' => $form_state['values']['organisation'],
                   'prioritaire' => $form_state['values']['prioritaire']   ))
    ->execute();
}

/**
 * Tableau ** CONVOCATIONS STAGIAIRES ** pour le service adiministratif
*/
function gbb_sess_stagiaire($args) {

  if ($args == 'NaN') return "";

  $query = db_select('gbb_session', 'm');
  $query ->condition('m.co_modu',  arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->condition('m.en_attente', 1, '<>')
         ->leftJoin('gbb_netab_dafor', 'e', 'e.co_lieu = m.co_lieu');
  $query ->fields('m', array('date', 'groupe',
                             'horaires', 'co_lieu' ))
         ->fields('e', array('denom_princ', 'denom_comp',
                             'sigle' ));
  $query ->groupBy('co_lieu');
  $query ->groupBy('date');
  $query ->groupBy('groupe');
  $query ->groupBy('horaires');
  $query ->orderBy('groupe', 'ASC');
  $query ->orderBy('date', 'ASC');
  $result = $query->execute();
  $header = array('date'  => t('Date'),
                  'horaires' => t('Horaires'),
                  'groupe'   => t('Gr'),
                  'etab'     => t('Établissement'),
                  'co_lieu'  => t('RNE'),
  );
  setlocale(LC_TIME, 'fr_FR');
  foreach ($result as $r) {
    $rows[] = array(
                array('data' => utf8_encode(strftime('%a %e %h %Y ',
                                            strtotime($r->date) ))  ),
                array('data' => $r->horaires),
                array('data' => $r->groupe),
                array('data' => $r->denom_princ . ' ' .
                                $r->denom_comp . ' (' . $r->sigle . ')'),
                array('data' => $r->co_lieu),
    );
  }
  if (!isset($rows)) return t('Pas de convocation à traiter pour des stagiaires');
  return theme('table', array('rows' => $rows, 'header' => $header));
}

/**
 * Formulaire des ** ATTACHEMENTS **
*/
function gbb_attachements($form, &$form_state, $args) {
  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fichiers joints'),
    '#attributes' => array('class' => array('attachements', 'collapsible')),
  );

  // -------------------------------------------
  // TODO réécrire avec la couche d'abstraction
  // -------------------------------------------
  $files = db_query("
     SELECT fm.fid, filename, uri, filemime, timestamp
     FROM {gbb_file} AS f
     JOIN {file_managed} AS fm ON fm.fid = f.fid
     WHERE co_modu  = :comodu
       AND co_degre = :codegre
       AND status = 1
     ", array(':codegre' => arg(1),
              ':comodu'  => arg(2)) );
  $icon_directory = variable_get('file_icon_directory', 
                                 drupal_get_path('module', 'file') . '/icons');
  $flist = array();
  foreach ($files as $f) {
    $icon = theme_file_icon(array('file' => $f, 
                            'icon_directory' =>  $icon_directory));
    $date = strftime('%d/%m/%Y à %X', $f->timestamp);
    $flist[$f->fid] = $icon . l($f->filename, 
                                file_create_url($f->uri), 
                                array('attributes' => array('title' => $date)));
  }

  if ( count($flist) > 0 ) {
    $form['f']['files']          = array( '#type'    => 'radios',
                                          '#options' => $flist, );
    $form['f']['supprimer_file'] = array( '#type'    => 'submit',
                                          '#value'   => t('Supprimer'), );
  }

  // Seules les extensions suivantes sont autorisées :
  $extensions = 'jpg jpeg gif png txt rtf doc docx odt xls xlsx ods pdf zip';
  $form['f']['Myfile'] = array(
    '#title' => t('Joindre un fichier à cette page'),
    '#type'  => 'managed_file',
    '#upload_location' => 'public://',
    '#process' => array('gbb_attachements_process'),
    '#upload_validators' => array(
      'file_validate_extensions' => array( $extensions ) ),
  );

  $form['f']['comodu'] = array(  '#type' => 'hidden',
                                '#value' => arg(2)   );
  $form['f']['codegre'] = array( '#type' => 'hidden',
                                '#value' => arg(1), );
  $form['f']['add_file'] = array(
    '#type' => 'submit',
    '#value' => t('Joindre'),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );
  return $form;
}

/**
 * ----> modifie le comportement du formulaire d'attachement
 */
function gbb_attachements_process($element, &$form_state, $form) {

  $element = file_managed_file_process($element, $form_state, $form);
  $element['upload_button']['#access'] = FALSE;
  return $element;
}

/**
 * ----> Submit
 */
function gbb_attachements_submit($form, &$form_state) {

  // TODO : actuellement on écrit dans public:// 
  // il faudrait écrire dans le dir ci_dessous :
  // $dir = drupal_get_path('module', 'gaiabb') . '/files';

  //  if ( !file_prepare_directory($dir) ) {
  //    drupal_set_message( t('WARNING: Server DIR not accessible.'), 'status');
  //  }
  if ( isset($form_state['values']['files']) ) {
    $file = file_load($form_state['values']['files']);
    $file->status |= 'FILE_STATUS_TEMPORARY';
    $file = file_save($file);
    drupal_set_message( t('Le fichier n°@num a été archivé.', 
                        array('@num' => $form_state['values']['files']) ),
                        'warning' );
  } 
  elseif ( $form_state['values']['Myfile'] == '' ) {
    drupal_set_message( t('Echec. Veuillez remplir les champs avant de valider.'),
                        'warning' );
  } 
  else {
    $file = file_load($form_state['values']['Myfile']); // Load via file.fid.
    $file->status = FILE_STATUS_PERMANENT; // Change status to permanent.
    file_save($file);                      // Save.
    db_insert('gbb_file')
      ->fields(array('co_modu'  => $form_state['values']['comodu'],
                     'co_degre' => $form_state['values']['codegre'],
                     'fid'      => $file->fid))
      ->execute();
    drupal_set_message( t('Le nouveau fichier a été enregistré.') );
  }
}

/**
 * Formulaire du ** TABLEAU DES SESSIONS **
 */
function gbb_sess_formatr($form, $form_state, $args) {

  $header = array(
    'date' => t('Date'),
    'icone' => '',
    'horaires' => t('Horaires'),
    'lieu' => t('Lieu'),
    'groupe' => t('Gr'),
    'formateur' => t('Formateur'),
    'duree_prevue' => variable_get('ico_dureePrev'),
    'duree_a_payer' => variable_get('ico_dureeApayer'),
    'TypePaiement' => t('Type pmt'),
  );

  $query = db_select('gbb_session', 's');
  $query ->leftjoin('gbb_gmodu_plus', 'mp', 
                    'mp.co_modu = s.co_modu AND mp.co_degre = s.co_degre');
  $query ->leftjoin('gbb_gresp_dafor', 'r', 
                    'r.co_resp = s.co_resp AND r.co_degre = s.co_degre');
  $query ->leftjoin('gbb_gresp_plus', 'p', 
                    'p.co_resp = s.co_resp');
  $query ->leftjoin('gbb_netab_dafor', 'e',
                    'e.co_lieu = s.co_lieu');
  $query ->leftjoin('users', 'u',
                    'u.uid = s.uid');
  $query ->orderBy('groupe', 'ASC');
  $query ->orderBy('date', 'ASC');
  $query ->orderBy('nomu', 'ASC');
  $query ->condition('s.co_modu', arg(2), '=')
         ->condition('s.co_degre', arg(1), '=')
         ->fields('s', array('sess_id', 'date',
                             'duree_prevue','duree_a_payer', 'type_paiement',
                             'en_attente', 'convoc_sent', 'session_alert',
                             'horaires', 'co_lieu', 'co_resp', 'groupe',
                             'date_modif'))
         ->fields('r', array('prenom', 'nomu', 'co_resp'))
         ->fields('p', array('statut'))
         ->fields('u', array('name'))
         ->fields('e', array('denom_princ', 'denom_comp', 'sigle'));
  // Une condition supplémentaire pour les administratifs
  // afin que les stages en attente ne leur apparaissent pas.
  if (user_access('gest_convocs gbb') && !user_access('gest_sessions gbb')) {
    $query->condition('s.en_attente', 0, '=');
  }
  $result = $query->execute();
  $nb_sessions = $result->rowCount();

  $default = (isset($_GET['sess_id']))? $_GET['sess_id'] : 0;

  $row = array();
  setlocale(LC_TIME, 'fr_FR');
  $date_modif_ts = 0;
  $name = '';

  foreach ($result as $r) {
    $visibilite = ($r->en_attente)? 'grisclair' : '';
    if ($r->en_attente) {
          $icon = variable_get('ico_attente');
    } elseif ($r->session_alert) {
          $icon = variable_get('ico_alert');
    } elseif ($r->convoc_sent) {
          $icon = variable_get('ico_sent');
    } else {
          $icon = variable_get('ico_notAttente');
    };
    $row[$r->sess_id] = array(
      'date' => utf8_encode(strftime('%a %e %h %Y ', strtotime($r->date))),
      'icone' => $icon,
      'horaires' => $r->horaires,
      'lieu' => l( "$r->sigle $r->denom_comp" ,
                   'etablissement/' . $r->co_lieu,
                   array('attributes' => array(
                     'class' => 'anchor-class',
                     'title' => "Voir la fiche",
                   ),
                         'html' => TRUE )
                ),
      'groupe' => $r->groupe,
      'formateur' => (($r->statut)? variable_get('ico_espe') . " " : '')
                . l( "$r->prenom $r->nomu", 
                   'formateur/' . $r->co_resp,
                   array('attributes' => array(
                     'class' => 'anchor-class',
                     'title' => "Voir la fiche",
                   ),
                         'html' => TRUE )
                       )
                       .(($r->statut && user_access('gest_convocs gbb') && !user_access('gest_sessions gbb'))? 
                       '<br/>ATTENTION : intervenant ESPE, ne pas envoyer la convocation':'')
                       ,
      'duree_prevue' => $r->duree_prevue . "h",
      'duree_a_payer' => $r->duree_a_payer . "h",
      'TypePaiement' => $r->type_paiement,
      '#attributes'  => array('class' => array($visibilite)),
    );
    if ($date_modif_ts < strtotime($r->date_modif)) {
        $date_modif_ts = strtotime($r->date_modif);
        $name = $r->name;
    }
  }

  setlocale(LC_TIME, 'fr_FR');
  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sessions - Dernière modifcation : ' .
         utf8_encode(strftime('%A %e %B %Y %T', $date_modif_ts)) . ' par ' . $name),
    '#attributes' => array('class' => array('sessions', 'collapsible')),
  );

  if ($nb_sessions > 0) { // s'il n'y a aucune session, pas de tableau

    $form['f']['table'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#multiple' => TRUE,
      '#options' => $row,
      '#default_value' => ((isset($_GET['sess_id']))? $_GET['sess_id'] : array()),
      '#empty' => t('Aucune session. cliquez sur Ajouter pour en créer.'),
    );
  };
    $form['f']['comodu'] = array(  '#type' => 'hidden',
                                  '#value' => arg(2)   );
    $form['f']['codegre'] = array( '#type' => 'hidden',
                                  '#value' => arg(1)   );
  if (user_access('gest_sessions gbb')) {
    $form['f']['ajouter'] = array(
      '#type' => 'submit',
      '#value' => t('Ajouter'),
      '#submit' => array('gbb_sess_formatr_ajouter_submit'),
    );
    $form['f']['modifier'] = array(
      '#type' => 'submit',
      '#value' => t('Modifier'),
      '#submit' => array('gbb_sess_formatr_modifier_submit'),
    );
    $form['f']['plus'] = array(
      '#type' => 'checkbox',
      '#title' => t('Plus'),
      '#default_value' => 0,
      '#prefix' => '<a name="edit_session_anchor"></a><div class="inline">',
      '#suffix' => '</div>&nbsp;',
    );

    $form['f']['bascule_en_attente'] = array(
      '#type' => 'submit',
      '#value' => t('Attente Y/N'),
      '#submit' => array('gbb_sess_formatr_bascule_en_attente_submit'),
      '#states' => array(    // This #states rule limits visibility
        'visible' => array(  // action to take.
          ':input[name="plus"]' => array('checked' => TRUE),),
      ),
    );
    $form['f']['dupliquer'] = array(
      '#type' => 'submit',
      '#value' => t('Dupliquer'),
      '#submit' => array('gbb_sess_formatr_dupliquer_submit'),
      '#states' => array(    // This #states rule limits visibility
        'visible' => array(  // action to take.
          ':input[name="plus"]' => array('checked' => TRUE),),
      ),
    );
    $form['f']['supprimer'] = array(
      '#type' => 'submit',
      '#value' => t('*Supprimer*'),
      '#submit' => array('gbb_sess_formatr_supprimer_submit'),
      '#states' => array(    // This #states rule limits visibility
        'visible' => array(  // action to take.
          ':input[name="plus"]' => array('checked' => TRUE),),
      ),
    );
  }

  if (user_access('gest_convocs gbb')) {
    $form['f']['convoc_envoyee'] = array(
      '#type' => 'submit',
      '#value' => t('Convocs envoyées'),
      '#submit' => array('gbb_sess_formatr_convoc_submit'),
    );
  }
  return $form;
}

/**
 * ----> Submit
 */
function gbb_sess_formatr_supprimer_submit($form, &$form_state) {
  if (!isset($form_state['values']['table'])
        || $form_state['values']['table'] == 0) {
    drupal_set_message(t('Choisissez la session à supprimer.'),'error');
    return;
 }
  db_delete('gbb_session') // supprime la session
      ->condition('sess_id', $form_state['values']['table'], 'IN')
      ->execute();

  drupal_set_message(t('La session a été supprimée.'));
}

function gbb_sess_formatr_dupliquer_submit($form, &$form_state) {
  if (!isset($form_state['values']['table'])
        || $form_state['values']['table'] == 0) {
    drupal_set_message(t('Choisissez la session à dupliquer.'),'error');
    return;
 }
  $query = db_select('gbb_session', 's') // récupère la session à cloner
         ->fields('s',array('co_resp', 'co_modu',
                            'co_degre', 'co_lieu', 'date', 'date_ts',
                            'groupe', 'horaires', 'type_paiement',
                            'duree_a_payer', 'duree_prevue'))
         ->condition('s.sess_id', $form_state['values']['table'], 'IN');
  global $user;
  $query ->addExpression($user->uid,'uid');
  $query ->addExpression("'".date('Y-m-d H:i:s')."'",'date_modif');

  db_insert('gbb_session')->from($query)->execute(); // clone la session

  $query = db_select('gbb_session', 's');
  $query ->addExpression('MAX(sess_id)', 'newid');
  $result = $query->execute()->fetchAssoc(); // recupère l'id du clone
  drupal_set_message(t('La session a été dupliquée.'.$query));

  $url = url('module/' . $form_state['values']['codegre'] .
                   '/' . $form_state['values']['comodu'],
             array('fragment' => 'edit_session_anchor',
                   'query'    => array('sess_id[' . $result['newid'] . ']'  =>
                                                             $result['newid']),
                   'absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function gbb_sess_formatr_ajouter_submit($form, &$form_state) {
  global $user;
  db_insert('gbb_session')
      ->fields(array( 'co_modu' => arg(2),
                      'co_degre' => arg(1),
                      'uid' => $user->uid,
                      'date_modif' => date('Y-m-d H:i:s'),
                      'date' => date('Y-m-d H:i:s'),
                      'date_ts' => strtotime(date('Y-m-d H:i:s')),
                      ))
      ->execute(); // ajoute une session toute neuve

  $query = db_select('gbb_session', 's');
  $query ->addExpression('MAX(sess_id)', 'newid');
  $result = $query->execute()->fetchAssoc(); // recupère l'id du clone

  drupal_set_message(t('Une nouvelle session a été créée. Vous pouvez l\'éditer'));

  $url = url('module/' . $form_state['values']['codegre'] .
                   '/' . $form_state['values']['comodu'],
             array('fragment' => 'edit_session_anchor',
                   'query'    => array('sess_id[' . $result['newid'] . ']'  =>
                                                             $result['newid']),
                   'absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function gbb_sess_formatr_modifier_submit($form, &$form_state) {
  $nb_sess = 0;
  foreach ($form_state['values']['table'] as $i) {
    if ($i != 0) {
        $nb_sess = $nb_sess + 1;
        $id = $i;
    };
  };
  if ($nb_sess != 1) {
    drupal_set_message(t('Choisissez une unique session à modifier.'),'error');
    return;
 }
  $url = url('module/' . $form_state['values']['codegre'] .
                   '/' . $form_state['values']['comodu'],
             array('fragment' => 'edit_session_anchor',
                   'query' => array('sess_id' => $form_state['values']['table']),
                   'absolute' => TRUE));
  $form_state['redirect'] = $url;
}

function gbb_sess_formatr_convoc_submit($form, &$form_state) {
  foreach ($form_state['values']['table'] as $i) {
    if ($i != 0 ) {
      db_merge('gbb_session') // Marque comme envoyée chaque session cochée
        ->key(array('sess_id'  => $i))
        ->fields(array('convoc_sent' => 1,
                       'session_alert' => 0))
        ->execute();
    }
  }
  drupal_set_message(t('Les convocs ont été marquées comme envoyées.'));
}

function gbb_sess_formatr_bascule_en_attente_submit($form, &$form_state) {
  $url_query= array();
  foreach ($form_state['values']['table'] as $i) {
    if ($i != 0 ) { // on traite seulement les cases cochées
      $query = db_select('gbb_session', 's')
             ->condition('sess_id', $i)
             ->fields('s', array('en_attente','convoc_sent','session_alert'));
      $r = $query->execute()->fetchAssoc(); // recupère les infos de la session
      if ($r['convoc_sent'] != 1  && $r['session_alert'] != 1) {
          // Modifie le statut en_attente SSI convoc_sent = 0 = session_alert
        db_merge('gbb_session')
          ->key(array('sess_id'  => $i))
          ->fields(array('en_attente' => ( ($r['en_attente'])? 0 : 1 ) ))
          ->execute();
      }
    }
    $url_query['sess_id[' . $i . ']'] =  $i;
  };
  drupal_set_message(t('Les convocs ont été basculées enAttente <-> enCours.'));
  $url = url('module/' . $form_state['values']['codegre'] .
                   '/' . $form_state['values']['comodu'],
             array('fragment' => 'edit_session_anchor',
                   'query' => $url_query,
                   'absolute' => TRUE));
  $form_state['redirect'] = $url;
}





/**
 * Formulaire de ** MODIF D'UNE SESSION ** particulière
 */
function gbb_sess_edition($form, $form_state, $args) {

  foreach ($_GET['sess_id'] as $i) { if ($i != 0) $id = $i; };

  if ($id == 0) {
    $form['f'] = array(
      '#type' => 'fieldset',
      '#title' => t('PROBLEME(S) AVEC LA(LES) SESSION(S) CHOISIE(S)' .
                  $r->sess_id ),
      '#attributes' => array('class' => array('eeditsession')),
    );
    return $form;
  }

  // On récupère les valeurs associées à la session pour peupler le formulaire
  $query = db_select('gbb_session', 's');
  $query ->leftjoin('gbb_gresp_dafor', 'r', 
                     'r.co_resp=s.co_resp AND r.co_degre=s.co_degre');
  $query ->leftjoin('gbb_netab_dafor', 'e', 'e.co_lieu=s.co_lieu');
  $query ->condition('sess_id', $id, '=')
         ->fields('s', array('sess_id', 'date', 'horaires', 'groupe',
                             'duree_prevue', 'duree_a_payer', 'type_paiement',
                             'session_alert', 'en_attente', 'convoc_sent'))
         ->fields('r', array('co_resp', 'nomu', 'prenom'))
         ->fields('e', array('co_lieu', 'denom_comp', 'sigle'));
  // le 21 nov 2012
  $result = $query->execute();
  if (($result->rowCount() == 0)) {
    $form['f'] = array(
      '#type' => 'fieldset',
      '#title' => t('PROBLEME(S) AVEC LA(LES) SESSION(S) CHOISIE(S)'),
      '#attributes' => array('class' => array('eeditsession')),
    );
    return $form;
  }
  $r = $result->fetchObject();
  // le 21 nov 2012

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Editer/Ajouter la session n°' . $r->sess_id),
    '#attributes' => array('class' => array('eeditsession')),
  );

/*
  $form['f']['date'] = array(
    '#type' => 'date_popup', 
    '#title' => t('Date'),
    '#default_value' => strftime('%Y-%m-%d %T', strtotime($r->date)),
    '#date_format' => 'y-m-d',
    '#date_label_position' => 'within', // see date_api_elements.inc
    '#date_year_range' => '-1:+1', // Optional, (-3:+3 years is the default).
    '#size' => 10,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
*/

  drupal_add_library('system', 'ui.datepicker');
  drupal_add_js('
    jQuery(document).ready(function(){
      jQuery( ".pickadate" ).datepicker({
        dateFormat: "yy-mm-dd",
        autoSize: true,
        showButtonPanel: true,
        firstDay: 1,
        closeText: "Fermer",
        currentText: "Aujourd\'hui",
        numberOfMonths: 3,
        dayNamesMin: ["Di", "Lu", "Ma", "Me", "Je", "Ve", "Sa"],
        monthNames: ["Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"]
      });
    });', 'inline');
  $form['f']['date'] = array(
    '#type' => 'textfield',
    '#title' => 'Date',
    '#default_value' => $r->date,
    '#size' => 15,
    '#required' => TRUE,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
    '#attributes' => array('class' => array('pickadate')),
  );

  $form['f']['horaires'] = array(
    '#type' => 'textfield',
    '#title' => 'Horaires',
    '#default_value' => $r->horaires,
    '#size' => 20,
    '#maxlength' => 50,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );
  $form['f']['groupe'] = array(
    '#type' => 'textfield',
    '#title' => t('Groupe'),
    '#default_value' => $r->groupe,
    '#size' => 1,
    '#maxlength' => 2,
    '#element_validate' => array('element_validate_integer_positive'),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );

  $form['f']['duree_prevue'] = array(
    '#type' => 'textfield',
    '#title' => variable_get('ico_dureePrev'),
    '#default_value' => $r->duree_prevue,
    '#size' => 6,
    '#maxlength' => 6,
    '#element_validate' => array('element_validate_number'),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );

  $form['f']['duree_a_payer'] = array(
    '#type' => 'textfield',
    '#title' => variable_get('ico_dureeApayer'),
    '#default_value' => $r->duree_a_payer,
    '#size' => 6,
    '#maxlength' => 6,
    '#element_validate' => array('element_validate_number'),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );

  $form['f']['type_paiement'] = array(
    '#type' => 'select',
    '#title' => t('Type de paiement'),
    '#options' => array( 'VAC'  => t('VAC'),
                         'CONV' => t('CONV'),
                         'BDC'  => t('BDC'),
                         'DECH' => t('DECH'),
                         'HSE'  => t('HSE'),
                         'SF'   => t('SF'),  ),
    '#default_value' => $r->type_paiement,
    '#maxlength' => 4,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  // $default_value = ($r->convoc_sent)? 1 : $r->session_alert;
  // mal compris par les conseillers
  $form['f']['session_alert'] = array(
    '#type' => 'checkbox',
    '#title' => variable_get('ico_alert') .
                t(' Alerte'),
    '#default_value' => $r->session_alert,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',
    '#states' => array(
      'visible' => array( // action to take.
        ':input[name="en_attente"]' => array('checked' => FALSE),
      ),
    ),
  );

  if ($r->convoc_sent != 1 || user_access('gest_sessions gbb') ) {
    $form['f']['en_attente'] = array(
      '#type' => 'checkbox',
      '#title' => variable_get('ico_attente') .
                  t('En attente'),
      '#default_value' => $r->en_attente,
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>&nbsp;',
      '#states' => array(    // This #states rule limits visibility
        'visible' => array(  // action to take.
          ':input[name="session_alert"]' => array('checked' => FALSE),
          ':input[name="convoc_sent"]' => array('checked' => FALSE),  ),
      ),
    );
  }
  else {
    $form['f']['en_attente'] = array( '#type'  => 'hidden',
                                      '#value' => 0        );
  }

  if (user_access('gest_convocs gbb')) {
    $form['f']['convoc_sent'] = array(
      '#type' => 'checkbox',
      '#title' => t('Convoc envoyée'),
      '#default_value' => $r->convoc_sent,
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>&nbsp;',
    );
  } 
  else {
    $form['f']['convoc_sent'] = array( '#type'  => 'hidden',
                                       '#value' => $r->convoc_sent  );
  }

  $form['f']['lieu'] = array(
    '#type' => 'textfield',
    '#title' => t('Lieu&nbsp;' . 
                  l( variable_get('ico_etabAdd'),
                     'etablissement/',
                     array('attributes' => array('class' => 'anchor-class'),
                                                 'html' => TRUE))
                ),
    '#description' => t('Lieu manquant ? Contactez C.Muir ou N.Poulain'),
    '#default_value' => t("$r->sigle $r->denom_comp (rne:$r->co_lieu)"),
    '#size' => 50,
    '#maxlength' => 128,
    '#autocomplete_path' => 'autocomp/etablissement',
    '#prefix' => '<br/><div class="inline">',
    '#suffix' => '</div>&nbsp;',
  );
  if (!user_access('gest_etablissements gbb')) {
      $form['f']['lieu']['#title'] = t('Lieu');
  };

  $form['f']['formateur'] = array(
    '#type' => 'textfield',
    '#title' => t('Formateur&nbsp;'), 
    '#description' => t('Formateur manquant ? Ajoutez-le : '
                  . l( variable_get('ico_userAdd'),
                     'formateur/add',
                     array('attributes' => array('class' => 'anchor-class'),
                                                 'html' => TRUE))
                ),
    '#default_value' => t("$r->prenom $r->nomu (id:$r->co_resp)"),
    '#size' => 50,
    '#autocomplete_path' => 'autocomp/formateur',
    '#maxlength' => 50,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
  );

  $form['f']['co_degre'] = array( '#type' => 'hidden',
                                 '#value' => arg(1)  );
  $form['f']['co_modu']  = array( '#type' => 'hidden',
                                 '#value' => arg(2)  );
  $form['f']['sess_id']  = array( '#type' => 'hidden',
                                 '#value' => $r->sess_id );
  $form['f']['submit']  = array(  '#type' => 'submit',
                                 '#value' => t('Enregistrer') );
  return $form;
}

/**
 * ----> Submit
 */
function gbb_sess_edition_submit($form, &$form_state) {
  $replace = array ('\1');
  $pattern = array ('/.*\(rne:(.*)\)/');
  $co_lieu = preg_replace($pattern, $replace,  
                          $form_state['values']['lieu']);
  $pattern = array ('/.*\(id:(.*)\)/');
  $co_resp = preg_replace($pattern, $replace,
                          $form_state['values']['formateur']);
  $sess_id = $form_state['values']['sess_id'];

  $convoc_sent = $form_state['values']['convoc_sent'];
  // si le drapeau est posé sur une session, on fait sauter le convoc-sent
  //  sur cette session ainsi que le module_printed sur le module
  if ($form_state['values']['session_alert']==1) {
    $convoc_sent =  0;
    db_merge('gbb_gmodu_plus')
      ->key(array('co_modu'  => $form_state['values']['co_modu'],
                  'co_degre' => $form_state['values']['co_degre'] ))
      ->fields(array('module_printed' => 0,))
      ->execute();
  };

  global $user;
  db_merge('gbb_session')
      ->key(array('sess_id'  => $sess_id ))
      ->fields(array(
                   'co_modu'       => $form_state['values']['co_modu'],
                   'co_degre'      => $form_state['values']['co_degre'],
                   'groupe'        => $form_state['values']['groupe'],
                   'convoc_sent'   => $convoc_sent,
                   'en_attente'    => $form_state['values']['en_attente'],
                   'session_alert' => $form_state['values']['session_alert'],
                   'horaires'      => $form_state['values']['horaires'],
                   'duree_prevue'  => $form_state['values']['duree_prevue'],
                   'duree_a_payer' => $form_state['values']['duree_a_payer'],
                   'type_paiement' => $form_state['values']['type_paiement'],
                   'date'          => $form_state['values']['date'],
                   'date_ts'       => strtotime($form_state['values']['date']),
                   'co_lieu'       => $co_lieu,
                   'co_resp'       => $co_resp,
                   'uid' => $user->uid,
                   'date_modif' => date('Y-m-d H:i:s'),
                  ))
      ->execute(); // met à jour la session

  drupal_set_message(t("Les modifications ont été prises en compte."));

  $url = url('module/' . $form_state['values']['co_degre'] .
                   '/' . $form_state['values']['co_modu'],
             array('fragment' => 'edit_session_anchor',
                   'query'    => array('sess_id[' . $sess_id . ']' => $sess_id),
                   'absolute' => TRUE));
  $form_state['redirect'] = $url;
}

/**
 * Formulaire de ** CONVOCATIONS INFOS ** à porter ou non sur la convoc
 */
function gbb_convoc_form($form, &$form_state) {

  // requete sur gbb_gmodu_plus. Le rightjoin sur gbb_gmodu assure un résultat.
  $query = db_select('gbb_gmodu_plus', 'mp');
  $query ->rightjoin('gbb_gmodu', 'm',
                     'm.co_modu=mp.co_modu AND m.co_degre=mp.co_degre');
  $query ->condition('m.co_modu', arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->fields('mp', array('convoc_info_off', 'convoc_info_on', 'user_id',
                              'module_printed', 'module_alert', 'date_modification'    ));
  $r = $query->execute()->fetchAssoc();

  $str = "Pas de modif. récente (càd depuis le 17 novembre 2013)";
  if ( isset($r['user_id']) && $r['user_id'] != 0 ) {
    $str = "Dernière modification : ";
    $str.= utf8_encode(strftime('%A %e %B %Y %T', strtotime($r['date_modification'])));
    $str.= " par ". user_load($r['user_id'])->name;
    }

  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Convocation - '. $str),
    '#attributes' => array('class' => array('collapsible', 'convoc')),
  );

  $form['f']['envoyer']['#markup']= '<div class="flright">' .
    variable_get('ico_save') . '</div>';

  if (user_access('gest_convocs gbb')) {
    $form['f']['module_printed'] = array(
      '#type' => 'checkbox',
      '#title' => variable_get('ico_print') .
                  t('Imprimé'),
      '#default_value' => $r['module_printed'],
      '#prefix' => '<div class="inline">',
      '#suffix' => '</div>',
      '#ajax' => array(
        'callback' => 'gbb_convoc_form_module_printed_submit',
        'progress' => array('type' => 'throbber',
                            'message' => 'Enregistrement...')),
    );
  }
  else {
    $form['f']['module_printed'] = array('#type' => 'hidden',
                                         '#value' => $r['module_printed']);
  }

  $form['f']['module_alert'] = array(
    '#type' => 'checkbox',
    '#title' => variable_get('ico_alert') .
                t(' Alerte'),
    '#default_value' => $r['module_alert'],
    '#ajax' => array(
      'callback' => 'gbb_convoc_form_module_alert_submit',
      'progress' => array('type' => 'throbber',
                          'message' => 'Enregistrement...')),
  );

  $html = $r['convoc_info_off'];
  $txtOff = preg_replace('#<br\s*/?>#i', "\n", $html); //ce <? est une ASTUCE
  $form['f']['convoc_info_off'] = array(
    '#type' => 'textarea',
    '#title' => t('Info à ne pas porter sur la convocation'),
    '#default_value' => $txtOff,
    '#cols' => 50,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_convoc_form_convoc_info_off_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
  );

  $html = $r['convoc_info_on'];
  $txtOn = preg_replace('#<br\s*/?>#i', "\n", $html); //ce <? est une ASTUCE
  $form['f']['convoc_info_on'] = array(
    '#type' => 'textarea',
    '#title' => t('Info à porter sur la convocation'),
    '#default_value' => $txtOn,
    '#cols' => 43,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_convoc_form_convoc_info_on_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
  );

  if (    user_access('gest_convocs gbb') 
      && !user_access('gest_sessions gbb')) {
    $form['f']['convoc_info_on']['#type'] = 'markup';
    $form['f']['convoc_info_on']['#cols'] = 100;
    $form['f']['convoc_info_on']['#markup']=  '<div class="inlineEncadre">' .
      '<b>Infos a porter sur la convoc</b><br/>' . nl2br($txtOn) . '</div>';
    $form['f']['convoc_info_off']['#type']= 'markup';
    $form['f']['convoc_info_off']['#cols'] = 100;
    $form['f']['convoc_info_off']['#markup']= '<div class="inlineEncadre">' .
      '<b>Infos a ne pas porter sur la convoc</b><br/>' . nl2br($txtOff) . 
      '</div>';
  };


  $comodu = isset($form_state['values']['comodu'])? 
              $form_state['values']['comodu'] : arg(2);
  $form['f']['comodu'] = array('#type'  => 'hidden',
                               '#value' => $comodu  );

  $codegre = isset($form_state['values']['codegre'])? 
              $form_state['values']['codegre'] : arg(1);
  $form['f']['codegre'] = array('#type' => 'hidden',
                                '#value' => $codegre );

 return $form;
}

/**
 * ----> Submit
 */
function gbb_convoc_form_convoc_info_off_submit(&$form, &$form_state) {
  global $user;
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('convoc_info_off' => $form_state['values']['convoc_info_off'],
                   'date_modification' => date('Y-m-d H:i:s'),
                   'user_id' => $user->uid))
    ->execute();
}
function gbb_convoc_form_convoc_info_on_submit(&$form, &$form_state) {
  global $user;
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('convoc_info_on' => $form_state['values']['convoc_info_on'],
                   'date_modification' => date('Y-m-d H:i:s'),
                   'user_id' => $user->uid))
    ->execute();
}
function gbb_convoc_form_module_alert_submit(&$form, &$form_state) {
  global $user;
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('module_alert' => $form_state['values']['module_alert'],
                   'date_modification' => date('Y-m-d H:i:s'),
                   'user_id' => $user->uid))
    ->execute();
  if ($form_state['values']['module_alert']==1) {
    db_merge('gbb_gmodu_plus')
      ->key(array('co_modu'  => $form_state['values']['comodu'],
                  'co_degre' => $form_state['values']['codegre'] ))
      ->fields(array('module_printed' => 0,
                   'date_modification' => date('Y-m-d H:i:s'),
                   'user_id' => $user->uid))
      ->execute();
  };

 }
function gbb_convoc_form_module_printed_submit(&$form, &$form_state) {
  global $user;
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'] ))
    ->fields(array('module_printed' => $form_state['values']['module_printed'],
                   'date_modification' => date('Y-m-d H:i:s'),
                   'user_id' => $user->uid))
    ->execute();
}


/**
 * Formulaire de ** BILANS INFOS ** Listes d'émargement, bilans etc.
 */
function gbb_bilan_form($form, &$form_state) {

  // requete sur gbb_gmodu_plus. Le rightjoin sur gbb_gmodu assure un résultat.
  $query = db_select('gbb_gmodu_plus', 'mp');
  $query ->rightjoin('gbb_gmodu', 'm', 
                     'm.co_modu=mp.co_modu AND m.co_degre=mp.co_degre');
  $query ->condition('m.co_modu', arg(2), '=')
         ->condition('m.co_degre', arg(1), '=')
         ->fields('mp', array('LE_etat', 'LE_info', 
                              'DSF_etat', 'DSF_info',
                              'DA_date_depot'));
  $r = $query->execute()->fetchAssoc();
 
  $form['f'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dossier'),
    '#attributes' => array('class' => array('dossier', 
                                            'collapsible', 
                                            'convoc')),
  );

  $form['f']['envoyer']['#markup']= '<div class="flright">' . 
    variable_get('ico_save') . '</div>';

  $html = $r['LE_info'];
  $txtOff = preg_replace('#<br\s*/?>#i', "\n", $html);  //ce <? est une ASTUCE 
  $form['f']['LE_info'] = array(
    '#type' => 'textarea',
    '#title' => t('Listes d\'émargement rendues au conseiller'),
    '#default_value' => $txtOff,
    '#cols' => 50,
    '#rows' => 2,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_LE_info_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
  );

  $form['f']['LE_etat_part'] = array(
    '#type' => 'checkbox',
    '#title' => t('Partiellement'),
    '#default_value' => (($r['LE_etat'] == 1)? 1 : 0),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_LE_etat_part_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
   // This #states rule limits visibility to when the $form['f']['en_attente']
   // checkbox is not checked."
    '#states' => array(
      'visible' => array(  // action to take.
         ':input[name="LE_etat_total"]' => array('checked' => FALSE) )),
   );

  $form['f']['LE_etat_total'] = array(
    '#type' => 'checkbox',
    '#title' => t('En totalité'),
    '#default_value' => (($r['LE_etat'] == 2)? 1 : 0),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_LE_etat_total_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
   // This #states rule limits visibility to when the $form['f']['en_attente']
   // checkbox is not checked."
    '#states' => array(
      'visible' => array(  // action to take.
         ':input[name="LE_etat_part"]' => array('checked' => FALSE) )),
   );

  $form['f']['BR']['#markup']= '<br/>';

  $html = $r['DSF_info'];
  $txtOff = preg_replace('#<br\s*/?>#i', "\n", $html); //ce <? est une ASTUCE.
  $form['f']['DSF_info'] = array(
    '#type' => 'textarea',
    '#title' => t('Déclarations de service fait rendues au conseiller'),
    '#default_value' => $txtOff,
    '#cols' => 50,
    '#rows' => 2,
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_DSF_info_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
  );

  $form['f']['DSF_etat_part'] = array(
    '#type' => 'checkbox',
    '#title' => t('Partiellement'),
    '#default_value' => (($r['DSF_etat'] == 1)? 1 : 0),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'gbb_DSF_etat_part_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
   // This #states rule limits visibility to when the $form['f']['en_attente']
   // checkbox is not checked."
    '#states' => array(
      'visible' => array(  // action to take.
         ':input[name="DSF_etat_total"]' => array('checked' => FALSE) )),
   );

  $form['f']['DSF_etat_total'] = array(
    '#type' => 'checkbox',
    '#title' => t('En totalité'),
    '#default_value' => (($r['DSF_etat'] == 2)? 1 : 0),
    '#prefix' => '<div class="inline">',
    '#suffix' => '</div>',
    '#ajax' => array
    (
      'callback' => 'gbb_DSF_etat_total_form_submit',
      'progress' => array('type' => 'throbber', 'message' => 'Enregistrement...'),
    ),
   // This #states rule limits visibility to when the $form['f']['en_attente']
   // checkbox is not checked."
    '#states' => array(
      'visible' => array(  // action to take.
         ':input[name="DSF_etat_part"]' => array('checked' => FALSE),
      ),
    ),
   );

  $form['f']['BR']['#markup']= '<br/>';

  $ddpt = ($r['DA_date_depot'] == '1970-01-01 00:00:00')? '' : $r['DA_date_depot'];

  $form['f']['DA_date_depot'] = array(
    '#type' => 'date_popup', 
    '#title' => t('Date de dépôt du dossier'),
    '#default_value' => $ddpt,
    '#date_format' => 'Y-m-d',
    '#date_label_position' => 'within', 
    '#date_year_range' => '-1:+1', 
    '#ajax' => array(
      'callback' => 'gbb_DA_date_depot_form_submit',
      'progress' => array('type' => 'throbber', 
                          'message' => 'Enregistrement...')),
  );

  $comodu = isset($form_state['values']['comodu'])? 
              $form_state['values']['comodu'] : arg(2);
  $form['f']['comodu'] = array('#type' => 'hidden',
                               '#value' => $comodu  );

  $codegre = isset($form_state['values']['codegre'])? 
               $form_state['values']['codegre'] : arg(1);
  $form['f']['codegre'] = array('#type' => 'hidden',
                                '#value' => $codegre  );
 return $form;
}

/**
 * ----> Submit
 */
function gbb_LE_etat_part_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('LE_etat' => $form_state['values']['LE_etat_part'],))
    ->execute();
}
function gbb_LE_etat_total_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('LE_etat' => $form_state['values']['LE_etat_total'] * 2,))
    ->execute();
}
function gbb_LE_info_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('LE_info' => $form_state['values']['LE_info'],))
    ->execute();
}
function gbb_DSF_etat_part_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('DSF_etat' => $form_state['values']['DSF_etat_part'],))
    ->execute();
}
function gbb_DSF_etat_total_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('DSF_etat' => $form_state['values']['DSF_etat_total'] *2,))
    ->execute();
}
function gbb_DSF_info_form_submit(&$form, &$form_state) {
  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('DSF_info' => $form_state['values']['DSF_info'],))
    ->execute();
}
function gbb_DA_date_depot_form_submit(&$form, &$form_state) {
  $ddpt = $form_state['values']['DA_date_depot'];
  if ($ddpt =='') $ddpt = '1970-01-01 00:00:00'; // 01/01/70 si pas de date

  db_merge('gbb_gmodu_plus')
    ->key(array('co_modu'  => $form_state['values']['comodu'],
                'co_degre' => $form_state['values']['codegre'],))
    ->fields(array('DA_date_depot' => $ddpt ))
    ->execute();
}
