<?php

$plugin = array(
  'title' => t('File'),
  'description' => t('Use a file to store the encryption key.'),
  'callback' => 'encrypt_get_file_key',
);

/**
 * Callback method to return the encryption key from a file.
 */
function encrypt_get_file_key() {
  // TODO: Something here.
  return '';
}
