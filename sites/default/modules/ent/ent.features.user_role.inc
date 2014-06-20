<?php
/**
 * @file
 * ent.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ent_user_default_roles() {
  $roles = array();

  // Exported role: D_admi.
  $roles['D_admi'] = array(
    'name' => 'D_admi',
    'weight' => 3,
  );

  // Exported role: D_cons.
  $roles['D_cons'] = array(
    'name' => 'D_cons',
    'weight' => 4,
  );

  // Exported role: D_form.
  $roles['D_form'] = array(
    'name' => 'D_form',
    'weight' => 5,
  );

  // Exported role: D_plus.
  $roles['D_plus'] = array(
    'name' => 'D_plus',
    'weight' => 7,
  );

  // Exported role: D_test.
  $roles['D_test'] = array(
    'name' => 'D_test',
    'weight' => 6,
  );

  return $roles;
}
