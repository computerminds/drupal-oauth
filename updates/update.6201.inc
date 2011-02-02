<?php
// $Id$

/**
 * This update unifies the handling of provider and consumer consumer entries.
 */
function _oauth_common_update_6201() {
  $ret = array();
  // Refresh our schema so that DrupalOAuthConsumer can
  // use drupal_write_record().
  drupal_get_schema('oauth_common_consumer', TRUE);

  if (!class_exists('DrupalOAuthConsumer')) {
    $path = drupal_get_path('module', 'oauth_common');
    require_once DRUPAL_ROOT . '/' . $path . '/lib/OAuth.php';
    require_once DRUPAL_ROOT . '/' . $path . '/includes/DrupalOAuthConsumer.inc';
  }

  // Change the oauth_common_consumer primary key to include the
  // provider_consumer field.
  db_drop_primary_key('oauth_common_consumer');
  db_add_primary_key('oauth_common_consumer', array('consumer_key', 'provider_consumer'));

  // The configuration field will be used to store provider_url, access_endpoint
  // and other configuration data.
  db_add_field('oauth_common_consumer', 'configuration', array(
    'description' => t('Consumer configuration'),
    'type' => 'text',
    'serialized' => TRUE,
    'size' => 'big',
    'not null' => TRUE,
    'object default' => array(),
  ));

  // The consumer type was never used, now its story ends.
  db_drop_field('oauth_common_consumer', 'type');

  // Transfer all DrupalOAuthConsumerTokens to DrupalOAuthConsumer
  $res = db_query('SELECT * FROM {oauth_common_consumer_token}');
  while ($ct = db_fetch_array($res)) {
    $consumer = new DrupalOAuthConsumer($ct['token_key'], $ct['secret'], 'oob', FALSE, array(
      'uid' => $ct['uid'],
      'name' => $ct['provider_url'],
      'configuration' => array(
        'provider_url' => $ct['provider_url'],
        'access_endpoint' => $ct['access_endpoint'],
      ),
    ));
    $consumer->write();
  }

  db_drop_table('oauth_common_consumer_token');

  return $ret;
}
