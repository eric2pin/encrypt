<?php

$plugin = array(
  'title' => t('Test Method'),
  'description' => t('This is just a test encryption method.'),
  'encrypt callback' => 'encrypt_test_encryption_methods_test',
);

/**
 * Callback for encryption.
 * We'll just return the text, since we're not concerned with testing encryption.
 */
function encrypt_test_encryption_methods_test($op = 'encrypt', $text = '', $options = array()) {
  return $text;
}
