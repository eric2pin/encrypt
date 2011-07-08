<?php

/**
 * @file
 * This file holds the functions for the encrypt Admin settings.
 *
 * @ingroup encrypt
 */

/**
 * Menu callback; displays the encrypt module settings page.
 *
 * @see system_settings_form()
 */
function encrypt_admin_settings($form, &$form_state) {
  $form = array();

  // Get formatted methods
  $methods = encrypt_get_encryption_methods();

  // Define Form
  $form['encrypt_encryption_method'] = array(
    '#type' => 'radios',
    '#title' => t('Default Encrypt Method'),
    '#description' => t('Define the default encryption method for the site. Since encryption methods are stored with the data, this can be changed even after you have stored encrypted data.'),
    '#options' => theme('encrypt_admin_list', $methods),
    '#default_value' => variable_get('encrypt_encryption_method', ENCRYPT_DEFAULT_METHOD),
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'encrypt') . '/encrypt.css',
      ),
    ),
  );

  // Get all key providers and format them for a a form.
  $providers = encrypt_get_key_providers();
  $provider = variable_get('encrypt_key_provider', 'drupal_private_key');

  $form['encrypt_key_provider'] = array(
    '#type' => 'radios',
    '#title' => t('Key Provider'),
    // TODO: Warning about changing this value.
    '#description' => t('Select the method by which encrypt will retrieve an encryption key.'),
    '#options' => theme('encrypt_admin_list', $providers),
    '#default_value' => $provider,
    '#ajax' => array(
      'method' => 'replace',
      'callback' => 'encrypt_key_providers_additional_settings_ajax',
      'wrapper' => 'encrypt-key-providers-additional-settings',
    ),
  );

  $form['key_settings_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="encrypt-key-providers-additional-settings">',
    '#suffix' => '</div>',
  );
  /** 
   * This is sort of tricky.
   * If the user has changed the key provider in the form, render the additional settings for that provider.
   * Otherwise, render for the current provider.
   */
  if (isset($form_state['values']['encrypt_key_provider']) && $form_state['values']['encrypt_key_provider'] !== $provider) {
    $provider = $form_state['values']['encrypt_key_provider'];
  }
  $settings_form_method = ctools_plugin_get_function($providers[$provider], 'settings form');
  if ($settings_form_method) {
    $form['key_settings_wrapper']['key_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional Key Provider Settings'),
    );
    $form['key_settings_wrapper']['key_settings']['encrypt_key_provider_' . $provider . '_settings'] = array('#tree' => TRUE) + call_user_func($settings_form_method);
  }

  // Make a system setting form and return
  return system_settings_form($form);
}

/**
 * Callback for AJAX form re-rendering.
 */
function encrypt_key_providers_additional_settings_ajax($form, $form_state) {
  return $form['key_settings_wrapper'];
}
