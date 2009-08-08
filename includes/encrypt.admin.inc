<?php
// $Id$

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
function encrypt_admin_settings() {
  // Initialize to just see if any funny business is going on
  encrypt_initialize();

  // Get formatted methods
  drupal_add_css(drupal_get_path('module', 'encrypt') . '/encrypt.css');
  $methods = theme('encrypt_admin_list', encrypt_get_methods('full', TRUE));

  // Define Form
  $form['encrypt_default'] = array(
    '#type' => 'radios',
    '#title' => t('Default Encrypt Method'),
    '#description' => t('Define the default encryption method for the site.  Since encryption methods are stored with strings, this can be changed even after you have stored encrypted data.'),
    '#options' => $methods,
    '#default_value' => variable_get('encrypt_default', ENCRYPT_DEFAULT_METHOD),
  );

  // Make a system setting form and return
  return system_settings_form($form);
}
