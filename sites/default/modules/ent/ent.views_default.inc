<?php
/**
 * @file
 * ent.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ent_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'formateurs';
  $view->description = 'Liste des formateurs disponibles dans la table locale gbb_resp_dafor + gbb_resp_plus';
  $view->tag = 'GaiaBB';
  $view->base_table = 'gbb_gmodu';
  $view->human_name = 'Liste des formateurs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Liste des formateurs';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'stable gbb';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'co_resp' => 'co_resp',
    'nomu' => 'nomu',
    'prenom' => 'prenom',
    'mel' => 'mel',
    'tel' => 'tel',
    'decharge' => 'decharge',
    'statut' => 'statut',
  );
  $handler->display->display_options['style_options']['default'] = 'nomu';
  $handler->display->display_options['style_options']['info'] = array(
    'co_resp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nomu' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'prenom' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mel' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tel' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'decharge' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'statut' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Champ: gbb_gresp_dafor: co_resp */
  $handler->display->display_options['fields']['co_resp']['id'] = 'co_resp';
  $handler->display->display_options['fields']['co_resp']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['co_resp']['field'] = 'co_resp';
  $handler->display->display_options['fields']['co_resp']['label'] = '';
  $handler->display->display_options['fields']['co_resp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['co_resp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['co_resp']['separator'] = '';
  /* Champ: gbb_gresp_dafor: nomu */
  $handler->display->display_options['fields']['nomu']['id'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['nomu']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['label'] = 'Nom';
  $handler->display->display_options['fields']['nomu']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nomu']['alter']['path'] = 'formateur/[co_resp]';
  /* Champ: gbb_gresp_dafor: prenom */
  $handler->display->display_options['fields']['prenom']['id'] = 'prenom';
  $handler->display->display_options['fields']['prenom']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['prenom']['field'] = 'prenom';
  $handler->display->display_options['fields']['prenom']['label'] = 'Prénom';
  /* Champ: gbb_gresp_dafor: mel */
  $handler->display->display_options['fields']['mel']['id'] = 'mel';
  $handler->display->display_options['fields']['mel']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['mel']['field'] = 'mel';
  $handler->display->display_options['fields']['mel']['label'] = 'email';
  $handler->display->display_options['fields']['mel']['hide_empty'] = TRUE;
  /* Champ: gbb_gresp_dafor: tel */
  $handler->display->display_options['fields']['tel']['id'] = 'tel';
  $handler->display->display_options['fields']['tel']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['tel']['field'] = 'tel';
  $handler->display->display_options['fields']['tel']['hide_empty'] = TRUE;
  /* Champ: gbb_gresp_plus: decharge */
  $handler->display->display_options['fields']['decharge']['id'] = 'decharge';
  $handler->display->display_options['fields']['decharge']['table'] = 'gbb_gresp_plus';
  $handler->display->display_options['fields']['decharge']['field'] = 'decharge';
  $handler->display->display_options['fields']['decharge']['label'] = 'Déch';
  $handler->display->display_options['fields']['decharge']['suffix'] = 'h';
  /* Champ: gbb_gresp_plus: Statut(IUFM) */
  $handler->display->display_options['fields']['statut']['id'] = 'statut';
  $handler->display->display_options['fields']['statut']['table'] = 'gbb_gresp_plus';
  $handler->display->display_options['fields']['statut']['field'] = 'statut';
  $handler->display->display_options['fields']['statut']['label'] = 'IUFM?';
  $handler->display->display_options['fields']['statut']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['statut']['alter']['text'] = 'IUFM';
  $handler->display->display_options['fields']['statut']['empty'] = '-';
  $handler->display->display_options['fields']['statut']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['statut']['separator'] = '';
  /* Sort criterion: gbb_gresp_dafor: nomu */
  $handler->display->display_options['sorts']['nomu']['id'] = 'nomu';
  $handler->display->display_options['sorts']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['sorts']['nomu']['field'] = 'nomu';
  /* Filter criterion: gbb_gresp_dafor: nomu */
  $handler->display->display_options['filters']['nomu']['id'] = 'nomu';
  $handler->display->display_options['filters']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['filters']['nomu']['field'] = 'nomu';
  $handler->display->display_options['filters']['nomu']['operator'] = 'longerthan';
  $handler->display->display_options['filters']['nomu']['value'] = '1';
  $handler->display->display_options['filters']['nomu']['expose']['operator_id'] = 'nomu_op';
  $handler->display->display_options['filters']['nomu']['expose']['label'] = 'nomu';
  $handler->display->display_options['filters']['nomu']['expose']['operator'] = 'nomu_op';
  $handler->display->display_options['filters']['nomu']['expose']['identifier'] = 'nomu';
  $handler->display->display_options['filters']['nomu']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: gbb_gresp_dafor: nomu */
  $handler->display->display_options['filters']['nomu_1']['id'] = 'nomu_1';
  $handler->display->display_options['filters']['nomu_1']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['filters']['nomu_1']['field'] = 'nomu';
  $handler->display->display_options['filters']['nomu_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['nomu_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['nomu_1']['expose']['operator_id'] = 'nomu_1_op';
  $handler->display->display_options['filters']['nomu_1']['expose']['label'] = 'Nom';
  $handler->display->display_options['filters']['nomu_1']['expose']['operator'] = 'nomu_1_op';
  $handler->display->display_options['filters']['nomu_1']['expose']['identifier'] = 'nomu_1';
  $handler->display->display_options['filters']['nomu_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'views_formateurs';
  $translatables['formateurs'] = array(
    t('Master'),
    t('Liste des formateurs'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
    t('.'),
    t('Nom'),
    t('Prénom'),
    t('email'),
    t('tel'),
    t('Déch'),
    t(','),
    t('h'),
    t('IUFM?'),
    t('IUFM'),
    t('-'),
    t('nomu'),
    t('Page'),
    t('more'),
  );
  $export['formateurs'] = $view;

  $view = new view();
  $view->name = 'interventions';
  $view->description = 'Liste des stages sur lesquels intervient un formateur';
  $view->tag = 'GaiaBB';
  $view->base_table = 'gbb_gmodu';
  $view->human_name = 'Interventions ';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Interventions FIL';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'nomu_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'nomu' => 'nomu',
    'en_attente' => 'en_attente',
    'en_attente_1' => 'en_attente_1',
    'convoc_sent' => 'convoc_sent',
    'date_ts' => 'date_ts',
    'horaires' => 'horaires',
    'co_modu' => 'co_modu',
    'lib' => 'lib',
    'duree_prevue' => 'duree_prevue',
    'duree_a_payer' => 'duree_a_payer',
    'nomu_1' => 'nomu_1',
  );
  $handler->display->display_options['style_options']['default'] = 'co_modu';
  $handler->display->display_options['style_options']['info'] = array(
    'nomu' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'en_attente' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'en_attente_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'convoc_sent' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date_ts' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'horaires' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'co_modu' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'lib' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'duree_prevue' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'duree_a_payer' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nomu_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Rien à afficher.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Champ: gbb_gresp_dafor: nomu */
  $handler->display->display_options['fields']['nomu']['id'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['nomu']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['label'] = '';
  $handler->display->display_options['fields']['nomu']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu']['element_label_colon'] = FALSE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente']['id'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['label'] = '';
  $handler->display->display_options['fields']['en_attente']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_pause.png">';
  $handler->display->display_options['fields']['en_attente']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['empty_zero'] = TRUE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente_1']['id'] = 'en_attente_1';
  $handler->display->display_options['fields']['en_attente_1']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente_1']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente_1']['label'] = '';
  $handler->display->display_options['fields']['en_attente_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['text'] = '&nbsp;';
  $handler->display->display_options['fields']['en_attente_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente_1']['empty'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_play_blue.png">';
  $handler->display->display_options['fields']['en_attente_1']['empty_zero'] = TRUE;
  /* Champ: gbb_session: convoc_sent */
  $handler->display->display_options['fields']['convoc_sent']['id'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['convoc_sent']['field'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['label'] = 'Statut';
  $handler->display->display_options['fields']['convoc_sent']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['convoc_sent']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/convoc_sent.png">';
  $handler->display->display_options['fields']['convoc_sent']['empty'] = '[en_attente] [en_attente_1]';
  $handler->display->display_options['fields']['convoc_sent']['empty_zero'] = TRUE;
  /* Champ: gbb_session: date_ts */
  $handler->display->display_options['fields']['date_ts']['id'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['date_ts']['field'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['label'] = 'Date';
  $handler->display->display_options['fields']['date_ts']['alter']['text'] = '[en_attente][en_attente_1][date_ts]';
  $handler->display->display_options['fields']['date_ts']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_ts']['custom_date_format'] = 'l d F Y';
  $handler->display->display_options['fields']['date_ts']['timezone'] = 'Europe/Paris';
  /* Champ: gbb_session: horaires */
  $handler->display->display_options['fields']['horaires']['id'] = 'horaires';
  $handler->display->display_options['fields']['horaires']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['horaires']['field'] = 'horaires';
  /* Champ: gbb_gmodu: co_modu */
  $handler->display->display_options['fields']['co_modu']['id'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['co_modu']['field'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['label'] = 'Module';
  $handler->display->display_options['fields']['co_modu']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['co_modu']['alter']['path'] = 'module/2/[co_modu]';
  /* Champ: gbb_gmodu: lib */
  $handler->display->display_options['fields']['lib']['id'] = 'lib';
  $handler->display->display_options['fields']['lib']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['lib']['field'] = 'lib';
  $handler->display->display_options['fields']['lib']['label'] = 'Libellé';
  /* Champ: gbb_session: duree_prevue */
  $handler->display->display_options['fields']['duree_prevue']['id'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_prevue']['field'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['label'] = 'Durée prév';
  /* Champ: gbb_session: duree_a_payer */
  $handler->display->display_options['fields']['duree_a_payer']['id'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_a_payer']['field'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['label'] = 'D. à payer';
  /* Champ: gbb_gresp: nomu */
  $handler->display->display_options['fields']['nomu_1']['id'] = 'nomu_1';
  $handler->display->display_options['fields']['nomu_1']['table'] = 'gbb_gresp';
  $handler->display->display_options['fields']['nomu_1']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu_1']['label'] = '';
  $handler->display->display_options['fields']['nomu_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['text'] = '<h1>Responsable : [nomu_1]</h1>';
  $handler->display->display_options['fields']['nomu_1']['element_type'] = 'h1';
  $handler->display->display_options['fields']['nomu_1']['element_label_colon'] = FALSE;
  /* Sort criterion: gbb_session: date_ts */
  $handler->display->display_options['sorts']['date_ts']['id'] = 'date_ts';
  $handler->display->display_options['sorts']['date_ts']['table'] = 'gbb_session';
  $handler->display->display_options['sorts']['date_ts']['field'] = 'date_ts';
  $handler->display->display_options['sorts']['date_ts']['granularity'] = 'day';
  /* Sort criterion: gbb_session: horaires */
  $handler->display->display_options['sorts']['horaires']['id'] = 'horaires';
  $handler->display->display_options['sorts']['horaires']['table'] = 'gbb_session';
  $handler->display->display_options['sorts']['horaires']['field'] = 'horaires';
  /* Contextual filter: gbb_session: co_resp */
  $handler->display->display_options['arguments']['co_resp']['id'] = 'co_resp';
  $handler->display->display_options['arguments']['co_resp']['table'] = 'gbb_session';
  $handler->display->display_options['arguments']['co_resp']['field'] = 'co_resp';
  $handler->display->display_options['arguments']['co_resp']['default_action'] = 'default';
  $handler->display->display_options['arguments']['co_resp']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['co_resp']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['co_resp']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['co_resp']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['co_resp']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['co_resp']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: gbb_gdisp: id_disp */
  $handler->display->display_options['filters']['id_disp']['id'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['table'] = 'gbb_gdisp';
  $handler->display->display_options['filters']['id_disp']['field'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['operator'] = 'starts';
  $handler->display->display_options['filters']['id_disp']['value'] = '12';
  $handler->display->display_options['filters']['id_disp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['id_disp']['expose']['operator_id'] = 'id_disp_op';
  $handler->display->display_options['filters']['id_disp']['expose']['label'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['expose']['operator'] = 'id_disp_op';
  $handler->display->display_options['filters']['id_disp']['expose']['identifier'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['id_disp']['group_info']['label'] = 'Année';
  $handler->display->display_options['filters']['id_disp']['group_info']['identifier'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['group_info']['optional'] = FALSE;
  $handler->display->display_options['filters']['id_disp']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['id_disp']['group_info']['group_items'] = array(
    1 => array(
      'title' => '2013-2014',
      'operator' => 'starts',
      'value' => '13',
    ),
    2 => array(
      'title' => '2012-2013',
      'operator' => 'starts',
      'value' => '12',
    ),
    3 => array(
      'title' => '2011-2012',
      'operator' => 'starts',
      'value' => '11',
    ),
    4 => array(
      'title' => '2010-2011',
      'operator' => 'starts',
      'value' => '10',
    ),
  );
  /* Filter criterion: gdire: co_tres */
  $handler->display->display_options['filters']['co_tres']['id'] = 'co_tres';
  $handler->display->display_options['filters']['co_tres']['table'] = 'gbb_gdire';
  $handler->display->display_options['filters']['co_tres']['field'] = 'co_tres';
  $handler->display->display_options['filters']['co_tres']['value']['value'] = '3';
  /* Filter criterion: gbb_gdisp: co_camp */
  $handler->display->display_options['filters']['co_camp']['id'] = 'co_camp';
  $handler->display->display_options['filters']['co_camp']['table'] = 'gbb_gdisp';
  $handler->display->display_options['filters']['co_camp']['field'] = 'co_camp';
  $handler->display->display_options['filters']['co_camp']['value'] = 'BS';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'interventions';

  /* Display: Bloc FIL */
  $handler = $view->new_display('block', 'Bloc FIL', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: gbb_gresp_dafor: nomu */
  $handler->display->display_options['fields']['nomu']['id'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['nomu']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['label'] = '';
  $handler->display->display_options['fields']['nomu']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu']['element_label_colon'] = FALSE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente']['id'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['label'] = '';
  $handler->display->display_options['fields']['en_attente']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_pause.png">';
  $handler->display->display_options['fields']['en_attente']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['empty_zero'] = TRUE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente_1']['id'] = 'en_attente_1';
  $handler->display->display_options['fields']['en_attente_1']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente_1']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente_1']['label'] = '';
  $handler->display->display_options['fields']['en_attente_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['text'] = '&nbsp;';
  $handler->display->display_options['fields']['en_attente_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente_1']['empty'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_play_blue.png">';
  $handler->display->display_options['fields']['en_attente_1']['empty_zero'] = TRUE;
  /* Champ: gbb_session: convoc_sent */
  $handler->display->display_options['fields']['convoc_sent']['id'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['convoc_sent']['field'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['label'] = 'Statut';
  $handler->display->display_options['fields']['convoc_sent']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['convoc_sent']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/convoc_sent.png">';
  $handler->display->display_options['fields']['convoc_sent']['empty'] = '[en_attente] [en_attente_1]';
  $handler->display->display_options['fields']['convoc_sent']['empty_zero'] = TRUE;
  /* Champ: gbb_session: date_ts */
  $handler->display->display_options['fields']['date_ts']['id'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['date_ts']['field'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['label'] = 'Date';
  $handler->display->display_options['fields']['date_ts']['alter']['text'] = '[en_attente][en_attente_1][date_ts]';
  $handler->display->display_options['fields']['date_ts']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_ts']['custom_date_format'] = 'l d F Y';
  $handler->display->display_options['fields']['date_ts']['timezone'] = 'Europe/Paris';
  /* Champ: gbb_session: horaires */
  $handler->display->display_options['fields']['horaires']['id'] = 'horaires';
  $handler->display->display_options['fields']['horaires']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['horaires']['field'] = 'horaires';
  /* Champ: gbb_gmodu: co_modu */
  $handler->display->display_options['fields']['co_modu']['id'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['co_modu']['field'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['label'] = 'Module';
  $handler->display->display_options['fields']['co_modu']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['co_modu']['alter']['path'] = 'module/2/[co_modu]';
  /* Champ: gbb_gmodu: lib */
  $handler->display->display_options['fields']['lib']['id'] = 'lib';
  $handler->display->display_options['fields']['lib']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['lib']['field'] = 'lib';
  $handler->display->display_options['fields']['lib']['label'] = 'Libellé';
  /* Champ: gbb_session: duree_prevue */
  $handler->display->display_options['fields']['duree_prevue']['id'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_prevue']['field'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['label'] = 'Durée prév';
  /* Champ: gbb_session: duree_a_payer */
  $handler->display->display_options['fields']['duree_a_payer']['id'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_a_payer']['field'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['label'] = 'D. à payer';
  /* Champ: gbb_gresp: nomu */
  $handler->display->display_options['fields']['nomu_1']['id'] = 'nomu_1';
  $handler->display->display_options['fields']['nomu_1']['table'] = 'gbb_gresp';
  $handler->display->display_options['fields']['nomu_1']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu_1']['label'] = '';
  $handler->display->display_options['fields']['nomu_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['text'] = '<h1>Responsable FIL : [nomu_1]</h1>';
  $handler->display->display_options['fields']['nomu_1']['element_type'] = 'h1';
  $handler->display->display_options['fields']['nomu_1']['element_label_colon'] = FALSE;

  /* Display: Bloc PAF */
  $handler = $view->new_display('block', 'Bloc PAF', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Interventions PAF';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: gbb_gresp_dafor: nomu */
  $handler->display->display_options['fields']['nomu']['id'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['table'] = 'gbb_gresp_dafor';
  $handler->display->display_options['fields']['nomu']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu']['label'] = '';
  $handler->display->display_options['fields']['nomu']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu']['element_label_colon'] = FALSE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente']['id'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente']['label'] = '';
  $handler->display->display_options['fields']['en_attente']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_pause.png">';
  $handler->display->display_options['fields']['en_attente']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['en_attente']['empty_zero'] = TRUE;
  /* Champ: gbb_session: en_attente */
  $handler->display->display_options['fields']['en_attente_1']['id'] = 'en_attente_1';
  $handler->display->display_options['fields']['en_attente_1']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['en_attente_1']['field'] = 'en_attente';
  $handler->display->display_options['fields']['en_attente_1']['label'] = '';
  $handler->display->display_options['fields']['en_attente_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['en_attente_1']['alter']['text'] = '&nbsp;';
  $handler->display->display_options['fields']['en_attente_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['en_attente_1']['empty'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_play_blue.png">';
  $handler->display->display_options['fields']['en_attente_1']['empty_zero'] = TRUE;
  /* Champ: gbb_session: convoc_sent */
  $handler->display->display_options['fields']['convoc_sent']['id'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['convoc_sent']['field'] = 'convoc_sent';
  $handler->display->display_options['fields']['convoc_sent']['label'] = 'Statut';
  $handler->display->display_options['fields']['convoc_sent']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['convoc_sent']['alter']['text'] = '<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/convoc_sent.png">';
  $handler->display->display_options['fields']['convoc_sent']['empty'] = '[en_attente] [en_attente_1]';
  $handler->display->display_options['fields']['convoc_sent']['empty_zero'] = TRUE;
  /* Champ: gbb_session: date_ts */
  $handler->display->display_options['fields']['date_ts']['id'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['date_ts']['field'] = 'date_ts';
  $handler->display->display_options['fields']['date_ts']['label'] = 'Date';
  $handler->display->display_options['fields']['date_ts']['alter']['text'] = '[en_attente][en_attente_1][date_ts]';
  $handler->display->display_options['fields']['date_ts']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_ts']['custom_date_format'] = 'l d F Y';
  $handler->display->display_options['fields']['date_ts']['timezone'] = 'Europe/Paris';
  /* Champ: gbb_session: horaires */
  $handler->display->display_options['fields']['horaires']['id'] = 'horaires';
  $handler->display->display_options['fields']['horaires']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['horaires']['field'] = 'horaires';
  /* Champ: gbb_gmodu: co_modu */
  $handler->display->display_options['fields']['co_modu']['id'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['co_modu']['field'] = 'co_modu';
  $handler->display->display_options['fields']['co_modu']['label'] = 'Module';
  $handler->display->display_options['fields']['co_modu']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['co_modu']['alter']['path'] = 'module/2/[co_modu]';
  /* Champ: gbb_gmodu: lib */
  $handler->display->display_options['fields']['lib']['id'] = 'lib';
  $handler->display->display_options['fields']['lib']['table'] = 'gbb_gmodu';
  $handler->display->display_options['fields']['lib']['field'] = 'lib';
  $handler->display->display_options['fields']['lib']['label'] = 'Libellé';
  /* Champ: gbb_session: duree_prevue */
  $handler->display->display_options['fields']['duree_prevue']['id'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_prevue']['field'] = 'duree_prevue';
  $handler->display->display_options['fields']['duree_prevue']['label'] = 'Durée prév';
  /* Champ: gbb_session: duree_a_payer */
  $handler->display->display_options['fields']['duree_a_payer']['id'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['table'] = 'gbb_session';
  $handler->display->display_options['fields']['duree_a_payer']['field'] = 'duree_a_payer';
  $handler->display->display_options['fields']['duree_a_payer']['label'] = 'D. à payer';
  /* Champ: gbb_gresp: nomu */
  $handler->display->display_options['fields']['nomu_1']['id'] = 'nomu_1';
  $handler->display->display_options['fields']['nomu_1']['table'] = 'gbb_gresp';
  $handler->display->display_options['fields']['nomu_1']['field'] = 'nomu';
  $handler->display->display_options['fields']['nomu_1']['label'] = '';
  $handler->display->display_options['fields']['nomu_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nomu_1']['alter']['text'] = '<h1>Responsable PAF : [nomu_1]</h1>';
  $handler->display->display_options['fields']['nomu_1']['element_type'] = 'h1';
  $handler->display->display_options['fields']['nomu_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: gbb_gdisp: id_disp */
  $handler->display->display_options['filters']['id_disp']['id'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['table'] = 'gbb_gdisp';
  $handler->display->display_options['filters']['id_disp']['field'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['operator'] = 'starts';
  $handler->display->display_options['filters']['id_disp']['value'] = '12';
  $handler->display->display_options['filters']['id_disp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['id_disp']['expose']['operator_id'] = 'id_disp_op';
  $handler->display->display_options['filters']['id_disp']['expose']['label'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['expose']['operator'] = 'id_disp_op';
  $handler->display->display_options['filters']['id_disp']['expose']['identifier'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['id_disp']['group_info']['label'] = 'Année';
  $handler->display->display_options['filters']['id_disp']['group_info']['identifier'] = 'id_disp';
  $handler->display->display_options['filters']['id_disp']['group_info']['optional'] = FALSE;
  $handler->display->display_options['filters']['id_disp']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['id_disp']['group_info']['group_items'] = array(
    1 => array(
      'title' => '2013-2014',
      'operator' => 'starts',
      'value' => '13',
    ),
    2 => array(
      'title' => '2012-2013',
      'operator' => 'starts',
      'value' => '12',
    ),
    3 => array(
      'title' => '2011-2012',
      'operator' => 'starts',
      'value' => '11',
    ),
    4 => array(
      'title' => '2010-2011',
      'operator' => 'starts',
      'value' => '10',
    ),
  );
  /* Filter criterion: gdire: co_tres */
  $handler->display->display_options['filters']['co_tres']['id'] = 'co_tres';
  $handler->display->display_options['filters']['co_tres']['table'] = 'gbb_gdire';
  $handler->display->display_options['filters']['co_tres']['field'] = 'co_tres';
  $handler->display->display_options['filters']['co_tres']['value']['value'] = '2';
  /* Filter criterion: gbb_gdisp: co_camp */
  $handler->display->display_options['filters']['co_camp']['id'] = 'co_camp';
  $handler->display->display_options['filters']['co_camp']['table'] = 'gbb_gdisp';
  $handler->display->display_options['filters']['co_camp']['field'] = 'co_camp';
  $handler->display->display_options['filters']['co_camp']['operator'] = '!=';
  $handler->display->display_options['filters']['co_camp']['value'] = 'BS';
  $translatables['interventions'] = array(
    t('Master'),
    t('Interventions FIL'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Rien à afficher.'),
    t('<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_pause.png">'),
    t('.'),
    t(','),
    t('&nbsp;'),
    t('<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/control_play_blue.png">'),
    t('Statut'),
    t('<img src="http://www.ent-paris.fr/gbbdr/sites/default/modules/gbb/images/convoc_sent.png">'),
    t('[en_attente] [en_attente_1]'),
    t('Date'),
    t('[en_attente][en_attente_1][date_ts]'),
    t('horaires'),
    t('Module'),
    t('Libellé'),
    t('Durée prév'),
    t('D. à payer'),
    t('<h1>Responsable : [nomu_1]</h1>'),
    t('Tout'),
    t('id_disp'),
    t('Année'),
    t('Page'),
    t('more'),
    t('Bloc FIL'),
    t('<h1>Responsable FIL : [nomu_1]</h1>'),
    t('Bloc PAF'),
    t('Interventions PAF'),
    t('<h1>Responsable PAF : [nomu_1]</h1>'),
  );
  $export['interventions'] = $view;

  $view = new view();
  $view->name = 'liste_des_etablissements';
  $view->description = 'Liste des formateurs disponibles';
  $view->tag = 'GaiaBB';
  $view->base_table = 'gbb_gmodu';
  $view->human_name = 'Liste des etablissements';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Liste des établissements';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'stable gbb';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nomu' => 'nomu',
    'prenom' => 'prenom',
    'mel' => 'mel',
    'tel' => 'tel',
  );
  $handler->display->display_options['style_options']['default'] = 'nomu';
  $handler->display->display_options['style_options']['info'] = array(
    'nomu' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'prenom' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mel' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tel' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Champ: gbb_netab_dafor: sigle */
  $handler->display->display_options['fields']['sigle']['id'] = 'sigle';
  $handler->display->display_options['fields']['sigle']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['sigle']['field'] = 'sigle';
  $handler->display->display_options['fields']['sigle']['exclude'] = TRUE;
  /* Champ: gbb_netab_dafor: denom_comp */
  $handler->display->display_options['fields']['denom_comp']['id'] = 'denom_comp';
  $handler->display->display_options['fields']['denom_comp']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['denom_comp']['field'] = 'denom_comp';
  $handler->display->display_options['fields']['denom_comp']['label'] = 'Nom';
  $handler->display->display_options['fields']['denom_comp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['denom_comp']['alter']['text'] = '[denom_comp] ([sigle])';
  /* Champ: gbb_netab_dafor: co_lieu */
  $handler->display->display_options['fields']['co_lieu']['id'] = 'co_lieu';
  $handler->display->display_options['fields']['co_lieu']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['co_lieu']['field'] = 'co_lieu';
  $handler->display->display_options['fields']['co_lieu']['label'] = 'Code étab.';
  $handler->display->display_options['fields']['co_lieu']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['co_lieu']['alter']['path'] = 'etablissement/[co_lieu]';
  /* Champ: gbb_netab_dafor: cp */
  $handler->display->display_options['fields']['cp']['id'] = 'cp';
  $handler->display->display_options['fields']['cp']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['cp']['field'] = 'cp';
  $handler->display->display_options['fields']['cp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['cp']['separator'] = '';
  /* Champ: gbb_netab_dafor: adr */
  $handler->display->display_options['fields']['adr']['id'] = 'adr';
  $handler->display->display_options['fields']['adr']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['adr']['field'] = 'adr';
  $handler->display->display_options['fields']['adr']['label'] = 'Adresse';
  $handler->display->display_options['fields']['adr']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['adr']['alter']['text'] = '[adr] ([cp])';
  /* Champ: gbb_netab_dafor: tel */
  $handler->display->display_options['fields']['tel_1']['id'] = 'tel_1';
  $handler->display->display_options['fields']['tel_1']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['tel_1']['field'] = 'tel';
  /* Champ: gbb_netab_dafor: mel */
  $handler->display->display_options['fields']['mel_1']['id'] = 'mel_1';
  $handler->display->display_options['fields']['mel_1']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['mel_1']['field'] = 'mel';
  /* Champ: gbb_netab_dafor: fax */
  $handler->display->display_options['fields']['fax']['id'] = 'fax';
  $handler->display->display_options['fields']['fax']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['fields']['fax']['field'] = 'fax';
  $handler->display->display_options['fields']['fax']['exclude'] = TRUE;
  /* Sort criterion: gbb_netab_dafor: denom_comp */
  $handler->display->display_options['sorts']['denom_comp']['id'] = 'denom_comp';
  $handler->display->display_options['sorts']['denom_comp']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['sorts']['denom_comp']['field'] = 'denom_comp';
  /* Filter criterion: gbb_netab_dafor: denom_comp */
  $handler->display->display_options['filters']['denom_comp']['id'] = 'denom_comp';
  $handler->display->display_options['filters']['denom_comp']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['filters']['denom_comp']['field'] = 'denom_comp';
  $handler->display->display_options['filters']['denom_comp']['operator'] = 'contains';
  $handler->display->display_options['filters']['denom_comp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['denom_comp']['expose']['operator_id'] = 'denom_comp_op';
  $handler->display->display_options['filters']['denom_comp']['expose']['label'] = 'Nom';
  $handler->display->display_options['filters']['denom_comp']['expose']['description'] = 'Entrez quelques lettres du nom de l\'établissement';
  $handler->display->display_options['filters']['denom_comp']['expose']['operator'] = 'denom_comp_op';
  $handler->display->display_options['filters']['denom_comp']['expose']['identifier'] = 'denom_comp';
  $handler->display->display_options['filters']['denom_comp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: gbb_netab_dafor: co_lieu */
  $handler->display->display_options['filters']['co_lieu']['id'] = 'co_lieu';
  $handler->display->display_options['filters']['co_lieu']['table'] = 'gbb_netab_dafor';
  $handler->display->display_options['filters']['co_lieu']['field'] = 'co_lieu';
  $handler->display->display_options['filters']['co_lieu']['operator'] = 'longerthan';
  $handler->display->display_options['filters']['co_lieu']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'vueLetablissement';
  $translatables['liste_des_etablissements'] = array(
    t('Master'),
    t('Liste des établissements'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
    t('sigle'),
    t('Nom'),
    t('[denom_comp] ([sigle])'),
    t('Code étab.'),
    t('cp'),
    t('.'),
    t('Adresse'),
    t('[adr] ([cp])'),
    t('tel'),
    t('mel'),
    t('fax'),
    t('Entrez quelques lettres du nom de l\'établissement'),
    t('Page'),
    t('more'),
  );
  $export['liste_des_etablissements'] = $view;

  return $export;
}
