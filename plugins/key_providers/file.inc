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
  // If the file doesn't exist, just abort.
  if (!file_exists($settings['path'])) {
    drupal_set_message(t('The directory %dir does not exist! Encrypt cannot retrieve encryption key.', array('%dir' => $settings['path'])), 'error');
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
    '#default_value' => isset($defaults['path']) ? $defaults['path'] : '',
    // '#element_validate' => array('encrypt_file_key_path_validate'),
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
    form_error($element, t('The directory %dir does not exist.', array('%dir' => $element['#value'])));
  }
}
