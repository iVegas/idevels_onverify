<?php
/**
 * @file
 * Admin functionality for module.
 */

/**
 * Implements hook_form().
 */
function idevels_onverify_form($form, &$form_state) {
  $form['userid'] = [
    '#type' => 'textfield',
    '#title' => t('What is Your User ID?'),
    '#description' => t('userid - Your user id assigned by onverify.com'),
    '#default_value' => idevels_onverify_get_userid(),
    '#size' => 10,
    '#maxlength' => 10,
    '#required' => TRUE,
    '#weight' => 10,
  ];
  $form['apipass'] = [
    '#type' => 'textfield',
    '#title' => t('What is Your Api Password?'),
    '#description' => t('apipass - Your api password assigned by onverify.com'),
    '#default_value' => idevels_onverify_get_apipass(),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#weight' => 20,
  ];
  $form['https'] = [
    '#type' => 'checkbox',
    '#title' => t('Use https protocol?'),
    '#default_value' => idevels_onverify_use_https(),
    '#description' => t('@host...', ['@host' => _idevels_onverify_get_base_url()]),
    '#weight' => 30,
  ];
  $form['debug'] = [
    '#type' => 'radios',
    '#title' => t('Debug mode'),
    '#default_value' => idevels_onverify_get_debug_status(),
    '#options' => [
      '0' => t('Disabled'),
      '1' => t('Enabled'),
    ],
    '#weight' => 40,
  ];
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
    '#validate' => ['idevels_onverify_form_validate'],
    '#submit' => ['idevels_onverify_form_submit'],
    '#weight' => 100,
  ];
  return $form;
}

/**
 * Validation callback for idevels_onverify_form().
 */
function idevels_onverify_form_validate($form, &$form_state) {
  _idevels_onverify_check_input_id('userid', $form_state['values']['userid']);
  _idevels_onverify_check_input_id('apipass', $form_state['values']['apipass']);
}

/**
 * Submit callback for idevels_onverify_form().
 */
function idevels_onverify_form_submit($form, &$form_state) {
  variable_set('idevels_onverify_userid', $form_state['values']['userid']);
  variable_set('idevels_onverify_apipass', $form_state['values']['apipass']);
  variable_set('idevels_onverify_https',
    (intval($form_state['values']['https']) !== 1) ? 0 : 1);
  variable_set('idevels_onverify_debug_enabled', $form_state['values']['debug']);
}
