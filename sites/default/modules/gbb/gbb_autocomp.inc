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
  $query  ->leftjoin('gbb_gmodu', 'm', 'm.co_disp = d.co_disp AND m.co_degre=d.co_degre');
  $query  ->addField('d', 'id_disp', 'id_disp');
  $query  ->addField('d', 'lib', 'lib');
  $query  ->addField('m', 'lib', 'libmodu');
  $query  ->addField('m', 'co_modu', 'co_modu');
  $query  ->addField('m', 'co_degre');
  $query  ->condition('id_disp', db_like('17') . '%', 'LIKE')
    ->condition('m.co_degre', db_like('2') . '%', 'LIKE')
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
function _gbb_autocompform($string) {

  $matches = array();
  $query = db_select('gbb_gresp_dafor', 'c');
  $query  ->leftjoin('gbb_gresp_plus', 'p', 'c.co_resp = p.co_resp');
  $query  ->addField('d', 'lib', 'lib');
  $query  ->addField('c', 'co_resp', 'co_resp');
  $query  ->addField('c', 'nomu', 'nomu');
  $query  ->addField('c', 'prenom', 'prenom');
  $query  ->addField('p', 'decharge', 'decharge');
  $query  ->condition('nomu', '%' . db_like($string) . '%', 'LIKE')
    ->range(0, 10);
  $result = $query->execute();

  if (strpos($string,'++')) {
  $result = db_select('gbb_gresp_dafor', 'c')
    ->fields('c', array('co_resp', 'nomu', 'prenom'))
    ->condition('nomu', '%' . db_like(str_replace("++","",$string)) . '%', 'LIKE')
    ->execute();
  }
  foreach ($result as $r) {
    $formatr = $r->prenom . ' ' . $r->nomu . $r->decharge>0 .' (id:' . $r->co_resp . ')';
    $matches[$formatr] = $formatr;
  }
  $count = $result->rowCount();
  if ($count > 9 && !strpos($string,'++')) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}


/**
 * Fonctions d' ** AUTOCOMPLETE AJAX FORMATEURS **
 */
function _gbb_autocompformatr2($string) {

  $matches = array();
  $pieces = explode(" ",$string);
  $query = db_select('gbb_gresp_dafor', 'c')
         ->fields('c', array('co_resp', 'nomu', 'prenom'));
  // $query = db_select('gbb_gresp_dafor', 'c');
  $query  ->leftjoin('gbb_gresp_plus', 'p', 'c.co_resp = p.co_resp');
  // $query  ->addField('d', 'lib', 'lib');
  // $query  ->addField('c', 'co_resp', 'co_resp');
  // $query  ->addField('c', 'nomu', 'nomu');
  // $query  ->addField('c', 'prenom', 'prenom');
  $query  ->addField('p', 'decharge', 'decharge');
  $query ->condition('nomu', '%'   . db_like($pieces[0]) . '%', 'LIKE');
  if (isset($pieces[1])) $query ->condition('prenom', '%' . db_like($pieces[1]) . '%', 'LIKE');
  $result = $query ->range(0, 10) ->execute();
  #dpm( $query->__toString() . '\n');
  if (strpos($string,'++')) {
    $result = db_select('gbb_gresp_dafor', 'c')
      ->fields('c', array('co_resp', 'nomu', 'prenom'))
      ->condition('nomu', '%' . db_like(str_replace("++","",$string)) . '%', 'LIKE')
      ->execute();
  }
  foreach ($result as $r) {
    $dec = ($r->decharge >0)?' **'.(int) $r->decharge.'h** ':" ";
    $formatr = $r->nomu . $dec . $r->prenom . ' (id:' . $r->co_resp . ')';
    $matches[$formatr] = $formatr;
    #$matches[$r->co_resp] =$r->nomu . ' ' . $r->prenom ;
  }
  $count = $result->rowCount();
  if ($count > 9 && !strpos($string,'++')) $matches[' '] = '..... Et bien d\'autres .....';
  drupal_json_output($matches);
}

