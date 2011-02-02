<?php
// $Id$

/**
 * This update either creates a authorization levels table, or transfers the
 * authorization levels table from the services_oauth module.
 */
function _oauth_common_update_6001() {
  $ret = array();
  if (db_table_exists('services_oauth_authorization_levels')) {
    db_query("ALTER TABLE {services_oauth_authorization_levels} RENAME TO {oauth_authorization_levels}") ;
  }
  else {
    db_create_table('oauth_authorization_levels', _oauth_common_oauth_authorization_levels_6001());
  }
  return $ret;
}

function _oauth_common_oauth_authorization_levels_6001() {
  return array(
    'description' => t('Stores the different authorization levels that are available for access tokens.'),
    'fields' => array(
      'name' => array(
        'description' => t('The computer-readable name of the authorization level.'),
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
      'title' => array(
        'description' => t('The localizable title of the authorization level.'),
        'type' => 'varchar',
        'length' => 100,
        'not null' => TRUE,
      ),
      'description' => array(
        'description' => t('The localizable description of the authorization level.'),
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    ),
    'primary key' => array('name'),
  );
}
