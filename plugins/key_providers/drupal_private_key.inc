<?php

$plugin = array(
  'title' => t('Drupal Private Key'),
  'description' => t('Use Drupal\'s private key from the database.'),
  'key callback' => 'encrypt_get_drupal_private_key',
  'settings form' => NULL,
);

/**
 * Callback method to return Drupal's private key.
 */
function encrypt_get_drupal_private_key() {
  return variable_get('drupal_private_key', '');
}