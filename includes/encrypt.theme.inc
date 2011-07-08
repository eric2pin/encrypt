<?php

/**
 * @file
 * This file holds the theme functions for encrypt module
 *
 * @ingroup encrypt
 */

/**
 * Theme function admin method listing
 *
 * This function themes the list of methods for the admin view.
 *
 * @param $items
 *   Array of methods
 * @return
 *   Array of similar put themed titles
 */
function theme_encrypt_admin_list($items = array()) {
  $output = array();

  // Check methods
  if (!is_array($items)) {
    return $output;
  }

  // Go through methods
  foreach ($items as $name => $item) {
    $output[$name] = '
      <span class="encrypt-admin-list-item">
        <span class="encrypt-admin-list-item-label">' . $item['title'] . '</span> -
        <span class="encrypt-admin-list-item-description">
        ' . $item['description'] . '
        </span>
      </span>
    ';
  }

  return $output;
}
