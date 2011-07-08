<?php

$plugin = array(
  'title' => t('None'),
  'description' => t('This uses no encryption.  It is not suggested to use this.'),
  'callback' => 'encrypt_encryption_methods_none',
);

/**
 * Callback for Encrypt implementation: none
 */
function encrypt_encrypt_none($op = 'encrypt', $text = '', $key, $options = array()) {
  krumo($key);
  // Check op
  if ($op == 'decrypt') {
    // No encryption
    return $text;
  }
  else {
    // No encryption
    return $text;
  }
}
