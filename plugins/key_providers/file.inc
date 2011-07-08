<?php

$plugin = array(
  'title' => t('File'),
  'description' => t('Use a file to store the encryption key.'),
  'key callback' => 'encrypt_get_file_key',
  'settings form' => 'encrypt_file_key_settings_form',
);

/**
 * Callback method to return the encryption key from a file.
 */
function encrypt_get_file_key($settings) {
  if (file_exists($settings['path'])) {
    return file_get_contents($settings['path']);
  } else {
    drupal_set_message(t('The directory %dir does not exist! Encrypt cannot retrieve encryption key.', array('%dir' => $settings['path'])), 'error');
    return;
  }
}

/**
 * Settings form for our key provider.
 */
function encrypt_file_key_settings_form() {
  $form = array();

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Key File'),
  );

  return $form;
}
