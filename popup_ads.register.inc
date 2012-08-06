<?php 
/**
 *  Implements hook_menu() 
 *  to provide the configuration page and signup page
 */
function popup_ads_menu() {
  $items = array();
   
  $items['admin/settings/popup_ads'] = array(
    'title' => t('Popup Ads Settings'), 
    'description' => t('Configure the way that the SignUp popup window works.'), 
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('popup_ads_admin_settings'),
    'access arguments' => array('administer signup wall'), 
    'type' => MENU_NORMAL_ITEM,
  );
  
  return $items; 
}

/**
 *  Implements hook_perm() 
 *  used to determine who can access the signup wall settings page
 */
function popup_ads_perm() {
  return array('administer signup wall');
}

/**
 * Create the admin settings form for the signup popup
 */
function popup_ads_admin_settings() {
  $nodetypes = node_get_types('names');

  $form = array();

  $form['popup_ads_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Signup Popup'),
    '#default_value' => variable_get('popup_ads_enabled', FALSE),
    '#description' => t('Should signup popup be shown at all.')
  );

  $form['popup_ads_cookie_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Life Expectancy'),
    '#default_value' => variable_get('popup_ads_cookie_duration', 1800000),
    '#description' => t('How long till the pop up should appear again on the visitor\'s computer.  This value must be set in milliseconds.')
  );

  $form['types']['popup_ads_node_types'] = array(
   '#type' => 'checkboxes', 
   '#title' => t('Excluded Node Types'), 
   '#default_value' => variable_get('popup_ads_node_types', array()),
   '#options' => $nodetypes,
   '#description' => t('Which node types will show a signup wall page when navigated to by anonymous users.'),
  );

  $form['popup_ads_excluded_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Excluded Roles'),
    '#description' => t('Check each role to exclude.'),
    '#default_value' => variable_get('popup_ads_excluded_roles', array()),
    '#options' => user_roles(),
  );

  $form['popup_ads_excluded_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#description' => t('Enter one page per line as Drupal paths. The "*" character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page.'),
    '#default_value' => variable_get('popup_ads_excluded_pages', 'admin/*'),
  );

  return system_settings_form($form);
}

/**
 *  Validates values from system configuration form
 */
function popup_ads_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['popup_ads_cookie_duration'])) {
    form_set_error('text', t('Cookie life expentancy must be a number.'));
  }
}