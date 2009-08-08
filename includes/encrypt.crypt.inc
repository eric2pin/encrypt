<?php
// $Id$

/**
 * @file
 * This file holds the ffunctions necessary to encrypt and decrypt
 *
 * @ingroup encrypt
 */

/**
 * Get Encryption Methods
 *
 * @param $format
 *   String of format to return.  Can be the following:
 *   - "simple": A simple key/balue pair for selects
 *   - "full": An array of all method data
 * @param $reset
 *   Boolean of whether to invoke modules again
 * @return
 *   Formatted array
 */
function encrypt_get_methods($format = 'simple', $reset = FALSE) {
  static $methods = array();
  static $simple = array();
  static $full = array();

  // Check format
  if (empty($methods) || $reset == TRUE) {
    // Invoke the encrypt_method_info hook
    $methods = module_invoke_all('encrypt_method_info');
  }

  // Check if format variable has data
  if (empty(${$format}) || ($reset == TRUE)) {
    $return = array();

    // Go through results
    foreach ($methods as $name => $method) {
      // Determine how to format data
      switch ($format) {
        case 'simple':
          $return[$name] = $method['title'];
          break;

        case 'full':
          $return[$name] = $method;
          break;

      }
    }

    return $return;
  }
  else {
    return ${$format};
  }
}

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
  $methods = encrypt_get_methods('full');
  $encryption_array = array();
  $processed = '';

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
  $processed = call_user_func($methods[$method]['callback'], $op, $text, $options);

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
