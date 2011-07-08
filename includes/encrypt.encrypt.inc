<?php

/**
 * @file
 * This file holds the ffunctions necessary to encrypt and decrypt
 *
 * @ingroup encrypt
 */

/**
 * Private Encrypt and Decrypt
 *
 * Private internal function to Encrypt and Decrypt text.
 *
 * @param $op
 *   Whether to encrypt or decrypt.
 *   - "encrypt": Encrypt text
 *   - "decrypt": Decrypt text
 * @param $text
 *   Text to encrypt
 * @param $options
 *   Array of options for encryption
 * @param $method
 *   String name of method to use.  Uses setting
 *   default if NULL
 * @return
 *   Encrypted text
 */
function _encrypt_decrypt($op = 'encrypt', $text = '', $options = array(), $method = NULL) {
  $encryption_array = array();
  $processed = '';

  // Get the encryption key from the default key provider.
  $key = encrypt_get_key_from_key_provider();

  // Check op
  if ($op !== 'encrypt') {
    $op = 'decrypt';
  }

  // If decrypting we need to get method
  if ($op == 'decrypt') {
    $encryption_array = unserialize($text);
    $method = $encryption_array['method'];
    $text = $encryption_array['text'];
  }

  // Check text
  if ($text === '') {
    return $processed;
  }

  // Check method
  $method = encrypt_check_method($method);
  if ($method === FALSE) {
    return $processed;
  }

  // Call callback function for encryption and decryption.
  $encryption_method = encrypt_get_encryption_method($method);
  $encryption_function = ctools_plugin_get_function($encryption_method, 'encrypt callback');
  $processed = call_user_func($encryption_function, $op, $text, $key, $options);

  // Check for returned value
  if (!empty($processed) && $op == 'encrypt') {
    $encryption_array = array(
      'text' => $processed,
      'method' => $method,
    );
    // Serialize array
    $processed = serialize($encryption_array);
  }

  return $processed;
}

/**
 * Check Method
 *
 * Check if a method is valid for encryption
 *
 * @param $method
 *   Method to check for
 * @return
 *   Method name or FALSE
 */
function encrypt_check_method($method = NULL) {
  $methods = encrypt_get_methods('full');
  $method = (string) $method;

  // Determine method
  if ($method == NULL) {
    $method = variable_get('encrypt_default', ENCRYPT_DEFAULT_METHOD);
  }

  // Make sure its a valid method
  if (!is_array($methods[$method])) {
    watchdog('encrypt', 'Encrypt call with invalid method: %method', array('%method' => $method));
    return FALSE;
  }

  // Make sure theres a valid callback
  if (empty($methods[$method]['callback']) || !function_exists($methods[$method]['callback'])) {
    watchdog('encrypt', 'Encrypt function call is not valid: %function , for method: %method', array('%method' => $method, '%function' => $methods[$method]['callback']));
    return FALSE;
  }

  return $method;
}
