<?php

$plugin = array(
  'title' => t('PHP Secure Communications Library (phpseclib)'),
  'description' => t('Uses the !link library. This method is only preferable if you cannot install mcrypt.', array('!link' => l('phpseclib', 'http://phpseclib.sourceforge.net/'))),
  'encrypt callback' => '_encrypt_encryption_methods_phpseclib',
  'dependencies' => '_encrypt_phpseclib_dependencies',
);

/**
 * Callback for Encrypt implementation: Mcrypt
 *
 * This method uses a PHPs mcrypt extension and AES-256
 */
function _encrypt_encryption_methods_phpseclib($op = 'encrypt', $text = '', $key, $options = array()) {
  $processed_text = '';

  if ($path = libraries_get_path('phpseclib')) {
    // Include the AES file and instantiate.
    require_once($path . '/Crypt/AES.php');
    $aes = new Crypt_AES();

    $aes->setKey($key);

    $processed_text = $aes->{$op}($text);
  }

  return trim($processed_text);
}

/**
 * Callback to see if the MCrypt library is present.
 */
function _encrypt_phpseclib_dependencies() {
  $errors = array();

  if (!module_exists('libraries')) {
    $errors[] = t('You must download and install the !link module.', array('!link' => l('Libraries API', 'http://drupal.org/project/libraries')));
  }
  if (!file_exists('sites/all/libraries/phpseclib') && !file_exists(conf_path() . '/phpseclib')) {
    $errors[] = t('You must download the !link library and place it in either sites/all/libraries or sites/yourdomain/libraries.', array('!link' => 'http://phpseclib.sourceforge.net/'));
  }

  return $errors;
}
