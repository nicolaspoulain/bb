<?php
# vim: foldmarker=(,) foldmethod=marker :

/**
 * Implement hook_views_data().
 *
 * Describe table "gbb_session" so that it can be used by views
 *
 * Pour les handlers (filed, sort, filter..)
 * http://api.drupal.org/api/views/views.api.php/group/views_handlers/7
 */

function gbb_views_data() {

  // --------------------------------------------------------
  // gbb_gmodu
  // --------------------------------------------------------

  $data['gbb_gmodu']['table'] = array(
    'group' => t('gbb_gmodu'),
    'base' => array(
      'field' => 'co_modu',
      'title' => t('GaiaBB'),
      'help' => t('Tables du module GaiaBB.'),
    ),
  );
  $data['gbb_gmodu']['co_modu'] = array(
    'title' => t('co_modu'),
    'help' => t('Code du module'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['co_degre'] = array(
    'title' => t('co_degre'),
    'help' => t('Code degré'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['co_anmo'] = array(
    'title' => t('co_anmo'),
    'help' => t('Code du type d\'annulation'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['lib'] = array(
    'title' => t('lib'),
    'help' => t('Libellé'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['lcont'] = array(
    'title' => t('lcont'),
    'help' => t('Contenu litteral'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['lpeda'] = array(
    'title' => t('lpeda'),
    'help' => t('Objectif pedagogique'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['lmoda'] = array(
    'title' => t('lmoda'),
    'help' => t('Modalité'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['lform'] = array(
    'title' => t('lform'),
    'help' => t('Forme'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['cout_p_fonc'] = array(
    'title' => t('cout_p_fonc'),
    'help' => t('Coût prévisionnel de fonctionnement par groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['cout_p_prest'] = array(
    'title' => t('cout_p_prest'),
    'help' => t('Coût prévisionnel de prestation par groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['cout_p_excep'] = array(
    'title' => t('cout_p_excep'),
    'help' => t('Coût prévisionnel des frais exceptionnels'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['nb_groupe'] = array(
    'title' => t('nb_groupe'),
    'help' => t('Nombre de groupes possible'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['nb_eff_groupe'] = array(
    'title' => t('nb_eff_groupe'),
    'help' => t('Effectif par groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['duree_prev'] = array(
    'title' => t('duree_prev'),
    'help' => t('Duree prevue'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['nb_place_prev'] = array(
    'title' => t('nb_place_prev'),
    'help' => t('Nombre de places prevues'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['nb_h_interv'] = array(
    'title' => t('nb_h_interv'),
    'help' => t('Nombre heures intervention'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu']['co_prna'] = array(
    'title' => t('co_prna'),
    'help' => t('Priorite nationale : code'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['co_prac'] = array(
    'title' => t('co_prac'),
    'help' => t('Priorite academique : code'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['lcibl'] = array(
    'title' => t('lcibl'),
    'help' => t('Cible litterale'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['co_cibl'] = array(
    'title' => t('co_cibl'),
    'help' => t('Code du public cible'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['co_etab_dem'] = array(
    'title' => t('co_etab_dem'),
    'help' => t('RNE de l etablissement demandeur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu']['dt_crea'] = array(
    'title' => t('dt_crea'),
    'help' => t('Date création'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // GBB_NPRAC
  // --------------------------------------------------------

  $data['gbb_nprac']['table'] = array(
    'group' => t('gbb_gmodu'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_prac',
        'field' => 'co_prac',
      ),
    ),
  );
  $data['gbb_nprac']['lib_court'] = array(
    'title' => t('nprac.lib_court'),
    'help' => t('Priorite academique : libellé court'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_nprac']['lib_long'] = array(
    'title' => t('nprac.lib_long'),
    'help' => t('Priorite academique : libellé long'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );


  // --------------------------------------------------------
  // GBB_NPRNA
  // --------------------------------------------------------

  $data['gbb_nprna']['table'] = array(
    'group' => t('gbb_gmodu'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_prna',
        'field' => 'co_prna',
      ),
    ),
  );
  $data['gbb_nprna']['lib_court'] = array(
    'title' => t('nprna.lib_court'),
    'help' => t('Priorite nationale : libellé court'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_nprna']['lib_long'] = array(
    'title' => t('nprna.lib_long'),
    'help' => t('Priorite nationale : libellé long'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // GBB_GMODU_TAXONOMY
  // --------------------------------------------------------

  $data['gbb_gmodu_taxonomy']['table'] = array(
    'group' => t('gbb_gmodu_taxnomy'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_gmodu_taxonomy.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gmodu_taxonomy']['tid'] = array(
    'title' => t('tid'),
    'help' => t('tid'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmodu_taxonomy']['weight'] = array(
    'title' => t('weight'),
    'help' => t('weight'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // TAXONOMY_TERM_DATA
  // --------------------------------------------------------

  $data['taxonomy_term_data3']['table'] = array(
    'group' => t('taxonomy_term_data3'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'taxonomy_term_data',
        'left_table' => 'gbb_gmodu_taxonomy',
        'left_field' => 'tid',
        'field' => 'tid',
      ),
    ),
  );
  $data['taxonomy_term_data3']['name'] = array(
    'title' => t('name'),
    'help' => t('Nom du terme de taxonomie'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['taxonomy_term_data3']['vid'] = array(
    'title' => t('vid'),
    'help' => t('Identifiant du vocabulaire'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );


  // --------------------------------------------------------
  // gbb_session
  // --------------------------------------------------------

  $data['gbb_session']['table'] = array(
    'group' => t('gbb_session'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_session.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_session']['co_resp'] = array(
    'title' => t('co_resp'),
    'help' => t('Code du responsable'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['date_ts'] = array(
    'title' => t('date_ts'),
    'help' => t('Date TS'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort_date'),
    'filter' => array('handler' => 'date_views_filter_handler_simple'), 
  );
  $data['gbb_session']['horaires'] = array(
    'title' => t('horaires'),
    'help' => t('Horaires'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_session']['type_paiement'] = array(
    'title' => t('type_paiement'),
    'help' => t('Type de paiement'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_session']['groupe'] = array(
    'title' => t('groupe'),
    'help' => t('Groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['duree_a_payer'] = array(
    'title' => t('duree_a_payer'),
    'help' => t('Duree à payer'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['duree_prevue'] = array(
    'title' => t('duree_prevue'),
    'help' => t('Durée prévue'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['session_alert'] = array(
    'title' => t('session_alert'),
    'help' => t('Changement important sur la session BOOL'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['convoc_sent'] = array(
    'title' => t('convoc_sent'),
    'help' => t('La convocation a été envoyée BOOL'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['en_attente'] = array(
    'title' => t('en_attente'),
    'help' => t('La session est en attente BOOL'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_session']['co_lieu'] = array(
    'title' => t('co_lieu'),
    'help' => t('Code lieu (RNE)'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gmodu_plus
  // --------------------------------------------------------

  $data['gbb_gmodu_plus']['table'] = array(
    'group' => t('gbb_gmodu_plus'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_gmodu_plus.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gmodu_plus']['module_alert'] = array(
    'title' => t('module_alert'),
    'help' => t('Changement important sur le module'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu_plus']['module_printed'] = array(
    'title' => t('module_printed'),
    'help' => t('Imprimé'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmodu_plus']['organisation'] = array(
    'title' => t('organisation'),
    'help' => t('Organisation du module'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
 
  // --------------------------------------------------------
  // gbb_gdire table de liaison, pas de champ à extraire
  // --------------------------------------------------------

  $data['gbb_gdire_orga']['table'] = array(
    'group' => t('gdire_orga'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'gbb_gdire', 
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_gdire_orga.co_degre = gbb_gmodu.co_degre AND gbb_gdire_orga.co_tres=2',
        'type' => 'INNER',
      ),
    ),
  );
  $data['gbb_gdire_peda']['table'] = array(
    'group' => t('gdire_peda'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'gbb_gdire', 
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_gdire_peda.co_degre = gbb_gmodu.co_degre AND gbb_gdire_peda.co_tres=3',
        'type' => 'INNER',
      ),
    ),
  );

  $data['gbb_gdire']['table'] = array(
    'group' => t('gdire'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_gdire.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gdire']['co_tres'] = array(
    'title' => t('co_tres'),
    'help' => t('Code trésorerie'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gresp
  // --------------------------------------------------------

  $data['gbb_gresp_orga']['table'] = array(
    'group' => t('gbb_gmodu'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'gbb_gresp',
        'left_table' => 'gbb_gdire_orga',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp_orga.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gresp_orga']['nomu'] = array(
    'title' => t('gresp.nomu orga'),
    'help' => t('Nom du responsable organisationnel'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp_peda']['table'] = array(
    'group' => t('gbb_gmodu'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'gbb_gresp',
        'left_table' => 'gbb_gdire_peda',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp_peda.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gresp_peda']['nomu'] = array(
    'title' => t('gresp.nomu peda'),
    'help' => t('Nom du responsable pédagogique'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gresp']['table'] = array(
    'group' => t('gbb_gresp'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_gdire',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp.co_degre = gbb_gmodu.co_degre',
      ),
      'gbb_gdiof' => array(
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp.co_degre = 2',
      ),
    ),
  );

  $data['gbb_gresp2']['table'] = array(
    'group' => t('gbb_gresp2'),
    'join' => array(
      'gbb_gdiof' => array(
        'table' => 'gbb_gresp',
        'left_table' => 'gbb_gmoof',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp2.co_degre = 2',
      ),
    ),
  );
  $data['gbb_gresp']['nomu'] = array(
    'title' => t('nomu'),
    'help' => t('Nom du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp2']['nomu'] = array(
    'title' => t('nomu'),
    'help' => t('Nom du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gresp']['prenom'] = array(
    'title' => t('prenom'),
    'help' => t('Prenom du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp2']['prenom'] = array(
    'title' => t('prenom'),
    'help' => t('Prenom du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gresp']['qualite'] = array(
    'title' => t('Qualité'),
    'help' => t('Qualité du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp2']['qualite'] = array(
    'title' => t('Qualité'),
    'help' => t('Qualité du responsable'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp2']['co_degre'] = array(
    'title' => t('Degré'),
    'help' => t('Degré du responsable'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gresp_plus
  // --------------------------------------------------------


  $data['gbb_gresp_plus']['table'] = array(
    'group' => t('gbb_gresp_plus'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_session',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
      ),
    ),
  );
  $data['gbb_gresp_plus']['decharge'] = array(
    'title' => t('decharge'),
    'help' => t('Decharge'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  $data['gbb_gresp_plus']['statut'] = array(
    'title' => t('Statut(IUFM)'),
    'help' => t('1=IUFM'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gresp_dafor
  // --------------------------------------------------------

  $data['gbb_gresp_dafor']['table'] = array(
    'group' => t('gbb_gresp_dafor'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_session',
        'left_field' => 'co_resp',
        'field' => 'co_resp',
        'extra' => 'gbb_gresp_dafor.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gresp_dafor']['co_resp'] = array(
    'title' => t('co_resp'),
    'help' => t('Code du formateur'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gresp_dafor']['nomu'] = array(
    'title' => t('nomu'),
    'help' => t('Nom du formateur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp_dafor']['prenom'] = array(
    'title' => t('prenom'),
    'help' => t('Prénom du formateur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp_dafor']['tel'] = array(
    'title' => t('tel'),
    'help' => t('Télephone du formateur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gresp_dafor']['mel'] = array(
    'title' => t('mel'),
    'help' => t('Mail du formateur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // gbb_gdisp
  // --------------------------------------------------------

  $data['gbb_gdisp']['table'] = array(
    'group' => t('gbb_gdisp'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_gdire',
        'left_field' => 'co_disp',
        'field' => 'co_disp',
        'extra' => 'gbb_gdisp.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_gdisp']['id_disp'] = array(
    'title' => t('id_disp'),
    'help' => t('Identifiant du dispositif'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['lib'] = array(
    'title' => t('lib'),
    'help' => t('Libellé du dispositif'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['co_camp'] = array(
    'title' => t('co_camp'),
    'help' => t('Code de la campagne'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['co_tcan'] = array(
    'title' => t('co_tcan'),
    'help' => t('Code du type de candidature'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['co_tpla'] = array(
    'title' => t('co_tpla'),
    'help' => t('Code type plan'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['co_orie'] = array(
    'title' => t('co_orie'),
    'help' => t('Code orientation'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['lobjt'] = array(
    'title' => t('lobjt'),
    'help' => t('Objectif litteral'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdisp']['co_andi'] = array(
    'title' => t('co_andi'),
    'help' => t('Code annulation dispo'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // GBB_NTCAN
  // --------------------------------------------------------

  $data['gbb_ntcan']['table'] = array(
    'group' => t('gbb_ntcan'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_gdisp',
        'left_field' => 'co_tcan',
        'field' => 'co_tcan',
      ),
    ),
  );
  $data['gbb_ntcan']['lib_court'] = array(
    'title' => t('lib_court'),
    'help' => t('Candidature libellé court'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_ntcan']['lib_long'] = array(
    'title' => t('lib_long'),
    'help' => t('Candidature libellé long'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // GBB_NCAMP
  // --------------------------------------------------------

  $data['gbb_ncamp']['table'] = array(
    'group' => t('gbb_ncamp'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_gdisp',
        'left_field' => 'co_camp',
        'field' => 'co_camp',
      ),
    ),
  );
  $data['gbb_ncamp']['lib_court'] = array(
    'title' => t('lib_court'),
    'help' => t('Campagne libellé court'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_ncamp']['lib_long'] = array(
    'title' => t('lib_long'),
    'help' => t('Campagne libellé long'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );


  // --------------------------------------------------------
  // GBB_NORIE
  // --------------------------------------------------------

  $data['gbb_norie']['table'] = array(
    'group' => t('gbb_norie'),
    'join' => array(
      'gbb_gmodu' => array(
        #'table' => 'taxonomy_term_data',
        'left_table' => 'gbb_gdisp',
        'left_field' => 'co_orie',
        'field' => 'co_orie',
      ),
    ),
  );
  $data['gbb_norie']['lib_court'] = array(
    'title' => t('lib_court'),
    'help' => t('Orientation libellé court'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );


  // --------------------------------------------------------
  // gbb_netab_dafor
  // --------------------------------------------------------

  $data['gbb_netab_dafor']['table'] = array(
    'group' => t('gbb_netab_dafor'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_table' => 'gbb_session',
        'left_field' => 'co_lieu',
        'field' => 'co_lieu',
      ),
    ),
  );

  $data['gbb_netab_dafor2']['table'] = array(
    'group' => t('gbb_netab_dafor2'),
    'join' => array(
      'gbb_gdiof' => array(
        'table' => 'gbb_netab_dafor',
        'left_table' => 'gbb_gmoof',
        'left_field' => 'co_etab_dem',
        'field' => 'co_lieu',
      ),
    ),
  );
  $data['gbb_netab_dafor3']['table'] = array(
    'group' => t('gbb_netab_dafor3'),
    'join' => array(
      'gbb_gmodu' => array(
        'table' => 'gbb_netab_dafor',
        'left_field' => 'co_etab_dem',
        'field' => 'co_lieu',
      ),
    ),
  );
  $data['gbb_netab_dafor']['denom_comp'] = array(
    'title' => t('denom_comp'),
    'help' => t('Dénomination complémentaire'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor2']['denom_comp'] = array(
    'title' => t('denom_comp'),
    'help' => t('Dénomination complémentaire'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor3']['denom_comp'] = array(
    'title' => t('denom_comp'),
    'help' => t('Dénomination complémentaire'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['sigle'] = array(
    'title' => t('sigle'),
    'help' => t('Sigle (CLG, LP, LGT,...)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor2']['sigle'] = array(
    'title' => t('sigle'),
    'help' => t('Sigle (CLG, LP, LGT,...)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor3']['sigle'] = array(
    'title' => t('sigle'),
    'help' => t('Sigle (CLG, LP, LGT,...)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['adr'] = array(
    'title' => t('adr'),
    'help' => t('Adresse'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['co_lieu'] = array(
    'title' => t('co_lieu'),
    'help' => t('code_lieu (RNE)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['cp'] = array(
    'title' => t('cp'),
    'help' => t('Code postal'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_netab_dafor2']['cp'] = array(
    'title' => t('cp'),
    'help' => t('Code postal'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_netab_dafor3']['cp'] = array(
    'title' => t('cp'),
    'help' => t('Code postal'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_netab_dafor']['tel'] = array(
    'title' => t('tel'),
    'help' => t('Telephone'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['fax'] = array(
    'title' => t('fax'),
    'help' => t('Fax'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_netab_dafor']['mel'] = array(
    'title' => t('mel'),
    'help' => t('Adresse eMail'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // gbb_evaluation
  // --------------------------------------------------------

  $data['gbb_evaluation']['table'] = array(
    'group' => t('gbb_evaluation'),
    'join' => array(
      'gbb_gmodu' => array(
        'left_field' => 'co_modu',
        'field' => 'co_modu',
        'extra' => 'gbb_evaluation.co_degre = gbb_gmodu.co_degre',
      ),
    ),
  );
  $data['gbb_evaluation']['groupe'] = array(
    'title' => t('groupe'),
    'help' => t('groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['satisAccueil'] = array(
    'title' => t('satisAccueil'),
    'help' => t('satisAccueil'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commAccueil'] = array(
    'title' => t('commAccueil'),
    'help' => t('commAccueil'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisSalle'] = array(
    'title' => t('satisSalle'),
    'help' => t('satisSalle'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commSalle'] = array(
    'title' => t('commSalle'),
    'help' => t('commSalle'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisMatos'] = array(
    'title' => t('satisMatos'),
    'help' => t('satisMatos'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commMatos'] = array(
    'title' => t('commMatos'),
    'help' => t('commMatos'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['rencontrePrep'] = array(
    'title' => t('rencontrePrep'),
    'help' => t('rencontrePrep'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisEffectif'] = array(
    'title' => t('satisEffectif'),
    'help' => t('satisEffectif'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commEffectif'] = array(
    'title' => t('commEffectif'),
    'help' => t('commEffectif'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisAssiduite'] = array(
    'title' => t('satisAssiduite'),
    'help' => t('satisAssiduite'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commAssiduite'] = array(
    'title' => t('commAssiduite'),
    'help' => t('commAssiduite'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisCooper'] = array(
    'title' => t('satisCooper'),
    'help' => t('satisCooper'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commCooper'] = array(
    'title' => t('commCooper'),
    'help' => t('commCooper'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisPrerequis'] = array(
    'title' => t('satisPrerequis'),
    'help' => t('satisPrerequis'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['commPrerequis'] = array(
    'title' => t('commPrerequis'),
    'help' => t('commPrerequis'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['satisObjectifs'] = array(
    'title' => t('satisObjectifs'),
    'help' => t('satisObjectifs'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['questionsTraitees'] = array(
    'title' => t('questionsTraitees'),
    'help' => t('questionsTraitees'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['pointsForts'] = array(
    'title' => t('pointsForts'),
    'help' => t('pointsForts'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['ameliorations'] = array(
    'title' => t('ameliorations'),
    'help' => t('ameliorations'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['genants'] = array(
    'title' => t('genants'),
    'help' => t('genants'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['besoinsParticip'] = array(
    'title' => t('besoinsParticip'),
    'help' => t('besoinsParticip'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['besoinsForm'] = array(
    'title' => t('besoinsForm'),
    'help' => t('besoinsForm'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['nbConvoques'] = array(
    'title' => t('nbConvoques'),
    'help' => t('nbConvoques'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['moyConvoques'] = array(
    'title' => t('moyConvoques'),
    'help' => t('moyConvoques'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['nbEvalStag'] = array(
    'title' => t('nbEvalStag'),
    'help' => t('nbEvalStag'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_evaluation']['syntheseEvalSta'] = array(
    'title' => t('syntheseEvalSta'),
    'help' => t('syntheseEvalSta'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['syntheseEvalForm'] = array(
    'title' => t('syntheseEvalForm'),
    'help' => t('syntheseEvalForm'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['condMateriellesAccueil'] = array(
    'title' => t('condMateriellesAccueil'),
    'help' => t('condMateriellesAccueil'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_evaluation']['remqAnalysesRD'] = array(
    'title' => t('remqAnalysesRD'),
    'help' => t('remqAnalysesRD'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // gbb_gdiof
  // --------------------------------------------------------

  $data['gbb_gdiof']['table'] = array(
    'group' => t('gbb_gdiof'),
    'base' => array(
      'field' => 'co_offre', 
      'title' => t('GaiaBB_OFFRES'), 
      'help' => t('Tables des offres GaiaBB.'),
    ),
  );
  $data['gbb_gdiof']['co_tpla'] = array(
    'title' => t('co_tpla'),
    'help' => t('Code type plan'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof']['co_orie'] = array(
    'title' => t('co_orie'),
    'help' => t('Code orientation'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof']['libl'] = array(
    'title' => t('libl'),
    'help' => t('Libellé du didpositif offre'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof']['no_offre'] = array(
    'title' => t('no_offre'),
    'help' => t('Numéro de l offre'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gdiof_dafor
  // --------------------------------------------------------

  $data['gbb_gdiof_dafor']['table'] = array(
    'group' => t('gbb_gdiof_dafor'),
    'join' => array(
      'gbb_gdiof' => array(
        'left_table' => 'gbb_gmoof',
        'left_field' => 'co_omodu',
        'field' => 'co_omodu',
      ),
    ),
  );
  $data['gbb_gdiof_dafor']['nb_hp'] = array(
    'title' => t('nb_hp'),
    'help' => t('Heures Poste, sur décharge'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof_dafor']['nb_vac'] = array(
    'title' => t('nb_vac'),
    'help' => t('Nbre vacations (dont ex-HSE)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof_dafor']['nb_gr'] = array(
    'title' => t('nb_gr'),
    'help' => t('nombre de groupes prévus'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gdiof_dafor']['hors_cdc'] = array(
    'title' => t('hors_cdc'),
    'help' => t('Hors CDC'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gdiof_dafor']['prio_nat'] = array(
    'title' => t('prio_nat'),
    'help' => t('Priorité nationale'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof_dafor']['prio_aca'] = array(
    'title' => t('prio_aca'),
    'help' => t('Priorité académique'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gdiof_dafor']['offre_new'] = array(
    'title' => t('offre_new'),
    'help' => t('Offre Nouvelle (p/r an dernier)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gdiof_dafor']['comment'] = array(
    'title' => t('Comment'),
    'help' => t('Observations'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gdiof_dafor']['iufm'] = array(
    'title' => t('iufm'),
    'help' => t('IUFM (O/N)'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  $data['gbb_gdiof_dafor']['nouv_offreur'] = array(
    'title' => t('nouv_offreur'),
    'help' => t('Nouv. ofreur (O/N)'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  $data['gbb_gdiof_dafor']['pub_des'] = array(
    'title' => t('pub_des'),
    'help' => t('Public désigné'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  $data['gbb_gdiof_dafor']['position'] = array(
    'title' => t('position'),
    'help' => t('Position'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // gbb_gmoof
  // --------------------------------------------------------

  $data['gbb_gmoof']['table'] = array(
    'group' => t('gbb_gmoof'),
    'join' => array(
      'gbb_gdiof' => array(
        'left_field' => 'co_offre',
        'field' => 'co_offre',
      ),
    ),
  );
  $data['gbb_gmoof']['co_omodu'] = array(
    'title' => t('co_omodu'),
    'help' => t('CODE ??'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['libl'] = array(
    'title' => t('libl'),
    'help' => t('Libellé long'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmoof']['duree_prev'] = array(
    'title' => t('duree_prev'),
    'help' => t('Durée prévue'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['nb_eff_groupe'] = array(
    'title' => t('nb_eff_groupe'),
    'help' => t('Effectif groupe'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['nb_groupe'] = array(
    'title' => t('nb_groupe'),
    'help' => t('Nbre de groupes'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['cout_p_prest'] = array(
    'title' => t('cout_p_prest'),
    'help' => t('Cout previsionnel de la prestation'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['cout_p_fonc'] = array(
    'title' => t('cout_p_fonc'),
    'help' => t('Cout previsionnel de fonctionnement'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['cout_p_excep'] = array(
    'title' => t('cout_p_excep'),
    'help' => t('Cout previsionnel exceptionnel'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );
  $data['gbb_gmoof']['lcont'] = array(
    'title' => t('lcont'),
    'help' => t('Lcont'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmoof']['lpeda'] = array(
    'title' => t('lpeda'),
    'help' => t('Libellé pédagogique'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmoof']['lmoda'] = array(
    'title' => t('lmoda'),
    'help' => t('Modalité'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  $data['gbb_gmoof']['dt_crea'] = array(
    'title' => t('dt_crea'),
    'help' => t('Date création'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmoof']['co_etab_dem'] = array(
    'title' => t('co_etab_dem'),
    'help' => t('RNE de l etablissement demandeur'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // GBB_NCONT
  // --------------------------------------------------------

  $data['gbb_ncont']['table'] = array(
    'group' => t('gbb_ncont'),
    'join' => array(
      'gbb_gdiof' => array(
        'left_table' => 'gbb_gmoof',
        'left_field' => 'co_cont',
        'field' => 'co_cont',
      ),
    ),
  );
  $data['gbb_ncont']['lib_court'] = array(
    'title' => t('lib_court'),
    'help' => t('Libellé du contenu (court)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // --------------------------------------------------------
  // GBB_GMOOF_TAXONOMY
  // --------------------------------------------------------

  $data['gbb_gmoof_taxonomy']['table'] = array(
    'group' => t('gbb_gmoof_taxnomy'),
    'join' => array(
      'gbb_gdiof' => array(
        'left_table' => 'gbb_gmoof',
        'left_field' => 'co_omodu',
        'field' => 'co_omodu',
      ),
    ),
  );
  $data['gbb_gmoof_taxonomy']['tid'] = array(
    'title' => t('tid'),
    'help' => t('tid'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['gbb_gmoof_taxonomy']['weight'] = array(
    'title' => t('weight'),
    'help' => t('weight'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // --------------------------------------------------------
  // TAXONOMY_TERM_DATA
  // --------------------------------------------------------

  $data['taxonomy_term_data2']['table'] = array(
    'group' => t('taxonomy_term_data2'),
    'join' => array(
      'gbb_gdiof' => array(
        'table' => 'taxonomy_term_data',
        'left_table' => 'gbb_gmoof_taxonomy',
        'left_field' => 'tid',
        'field' => 'tid',
      ),
    ),
  );
  $data['taxonomy_term_data2']['name'] = array(
    'title' => t('name'),
    'help' => t('Nom du terme de taxonomie'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );
  $data['taxonomy_term_data2']['vid'] = array(
    'title' => t('vid'),
    'help' => t('Identifiant du vocabulaire'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  return $data;
}
