<?php

/**
 * @file
 * Plugin definition for the File key provider.
 */

$plugin = array(
  'title' => t('File'),
  'description' => t('Use a file to store the encryption key.'),
  'key callback' => 'encrypt_get_file_key',
  'settings form' => 'encrypt_file_key_settings_form',
  'submit callback' => 'encrypt_file_key_settings_form_submit',
);

/**
 * Callback method to return the encryption key from a file.
 */
function encrypt_get_file_key($settings) {
  // If the file doesn't exist, just abort.
  if (!file_exists($settings['path'])) {
    drupal_set_message(t('The file %dir does not exist! Encrypt cannot retrieve encryption key.', array('%dir' => $settings['path'])), 'error');
    return;
  }

  switch ($settings['method']) {
    case 'file_contents':
      return file_get_contents($settings['path']);
    case 'md5':
      return md5_file($settings['path']);
  }
}

/**
 * Settings form for our key provider.
 */
function encrypt_file_key_settings_form($defaults) {
  $form = array();

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Key File'),
    '#description' => t('Filepath may be absolute (e.g. %abs) or relative to the Drupal directory (e.g. %rel).', array(
      '%abs' => '/var/www',
      '%rel' => '../../keys',
    )),
    '#default_value' => isset($defaults['path']) ? $defaults['path'] : '',
    '#element_validate' => array('encrypt_file_key_path_validate'),
    '#required' => TRUE,
  );
  $form['method'] = array(
    '#type' => 'select',
    '#title' => t('Method'),
    '#options' => array(
      'file_contents' => t('File Contents'),
      'md5' => t('MD5'),
    ),
    '#default_value' => isset($defaults['method']) ? $defaults['method'] : 'file_contents',
  );

  return $form;
}

/**
 * Validate key path.
 */
function encrypt_file_key_path_validate($element, &$form_state, $form) {
  if (!file_exists($element['#value'])) {
    form_error($element, t('The file %dir does not exist.', array('%dir' => $element['#value'])));
  }
}

/**
 * Submit callback for the settings form.
 */
function encrypt_file_key_settings_form_submit($form, $form_state) {
  // TODO: Save the key file.
}
