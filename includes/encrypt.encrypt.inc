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

  // If there is no method, assume we will be using the default.
  if (!$method) {
    $method = variable_get('encrypt_encryption_method', 'default');
  }

  // Check text
  if ($text === '') {
    return $processed;
  }

  // Call callback function for encryption and decryption.
  $encryption_method = encrypt_get_encryption_method($method);
  $function = ctools_plugin_get_function($encryption_method, 'encrypt callback');
  $processed = call_user_func($function, $op, $text, $key, $options);

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
