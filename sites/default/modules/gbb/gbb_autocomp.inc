<?php

/**
 * Fonctions d' ** AUTOCOMPLETE AJAX ETABLISSEMENTS **
 */
function _gbb_autocompetab($string) {

  $matches = array();
  $result = db_select('gbb_netab_dafor', 'c')
    ->fields('c', array('co_lieu', 'denom_comp', 'sigle'))
    ->condition('denom_comp', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();
  foreach ($result as $r) {
    $etab = $r->denom_comp . ' ' . $r->sigle . ' (rne:' . $r->co_lieu . ')';
    $matches[$etab] = $etab;
  }
  $count = $result->rowCount();
  if ($count > 9) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}

/**
 * Fonctions d' ** AUTOCOMPLETE AJAX FORMATEURS **
 */
function _gbb_autocompform($string) {

  $matches = array();
  $result = db_select('gbb_gresp_dafor', 'c')
    ->fields('c', array('co_resp', 'nomu', 'prenom'))
    ->condition('nomu', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();

  if (strpos($string,'++')) {
  $result = db_select('gbb_gresp_dafor', 'c')
    ->fields('c', array('co_resp', 'nomu', 'prenom'))
    ->condition('nomu', '%' . db_like(str_replace("++","",$string)) . '%', 'LIKE')
    ->execute();
  }
  foreach ($result as $r) {
    $formatr = $r->prenom . ' ' . $r->nomu . ' (id:' . $r->co_resp . ')';
    $matches[$formatr] = $formatr;
  }
  $count = $result->rowCount();
  if ($count > 9 && !strpos($string,'++')) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}

/**
 * Fonctions d' ** AUTOCOMPLETE AJAX RESPONSABLES **
 */
function _gbb_autocompresp($string) {

  $matches = array();
  $result = db_select('gbb_gresp', 'c')
    ->fields('c', array('nomu'))
    ->condition('nomu', '%' . db_like($string) . '%', 'LIKE')
    ->distinct()
    ->range(0, 10)
    ->execute();
  foreach ($result as $r) {
    $matches[$r->nomu] = $r->nomu;
  }
  $count = $result->rowCount();
  if ($count > 9) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}
/**
 * Fonctions d' ** AUTOCOMPLETE AJAX STAGES **
 */
function _gbb_autocompstage($string) {

  $matches = array();
  $query = db_select('gbb_gdisp', 'd');
  $query  ->leftjoin('gbb_gmodu', 'm', 'm.co_disp = d.co_disp');
  $query  ->addField('d', 'id_disp', 'id_disp');
  $query  ->addField('d', 'lib', 'lib');
  $query  ->addField('m', 'lib', 'libmodu');
  $query  ->addField('m', 'co_modu', 'co_modu');
  $query  ->condition('id_disp', db_like('14') . '%', 'LIKE')
    ->condition(db_or()->condition('id_disp', '%' . db_like($string) . '%', 'LIKE')
    ->condition('m.lib', '%' . db_like($string) . '%', 'LIKE')
    ->condition('m.co_modu', '%' . db_like($string) . '%', 'LIKE')
  )
  ->distinct()
  ->range(0, 10);
  $result = $query->execute();
  foreach ($result as $r) {
    $matches[$r->co_modu] = $r->id_disp."/".$r->co_modu." ".$r->libmodu;
  }
  $count = $result->rowCount();
  if ($count > 9) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}



/**
 * Fonctions d' ** AUTOCOMPLETE AJAX FORMATEURS **
 */
function _gbb_autocompformatr2($string) {

  $matches = array();
  $result = db_select('gbb_gresp_dafor', 'c')
    ->fields('c', array('co_resp', 'nomu', 'prenom'))
    ->condition('nomu', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10)
    ->execute();
  if (strpos($string,'++')) {
    $result = db_select('gbb_gresp_dafor', 'c')
      ->fields('c', array('co_resp', 'nomu', 'prenom'))
      ->condition('nomu', '%' . db_like(str_replace("++","",$string)) . '%', 'LIKE')
      ->execute();
  }
  foreach ($result as $r) {
    $matches[$r->co_resp] = $r->prenom . ' ' . $r->nomu;
  }
  $count = $result->rowCount();
  if ($count > 9 && !strpos($string,'++')) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}

