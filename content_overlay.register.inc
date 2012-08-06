<?php 
/**
 *  Implements hook_menu() 
 *  to provide the configuration page and signup page
 */
function content_overlay_menu() {
  $items = array();
   
  $items['admin/settings/content_overlay'] = array(
    'title' => t('Content Overlay Settings'), 
    'description' => t('Configuration options for content overlay.'), 
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('content_overlay_admin_settings'),
    'access arguments' => array('administer signup wall'), 
    'type' => MENU_NORMAL_ITEM,
  );
  
  return $items; 
}

/**
 *  Implements hook_perm() 
 *  used to determine who can access the signup wall settings page
 */
function content_overlay_perm() {
  return array('administer content_overlay');
}

/**
 * Create the admin settings form for the signup popup
 */
function content_overlay_admin_settings() {
  $nodetypes = node_get_types('names');

  $form = array();

  $form['content_overlay_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Signup Popup'),
    '#default_value' => variable_get('content_overlay_enabled', FALSE),
    '#description' => t('Should signup popup be shown at all.')
  );

  $form['content_overlay_cookie_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Life Expectancy'),
    '#default_value' => variable_get('content_overlay_cookie_duration', 1800000),
    '#description' => t('How long till the pop up should appear again on the visitor\'s computer.  This value must be set in milliseconds.')
  );

  $form['types']['content_overlay_node_types'] = array(
   '#type' => 'checkboxes', 
   '#title' => t('Excluded Node Types'), 
   '#default_value' => variable_get('content_overlay_node_types', array()),
   '#options' => $nodetypes,
   '#description' => t('Which node types will show a signup wall page when navigated to by anonymous users.'),
  );

  $form['content_overlay_excluded_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Excluded Roles'),
    '#description' => t('Check each role to exclude.'),
    '#default_value' => variable_get('content_overlay_excluded_roles', array()),
    '#options' => user_roles(),
  );

  $form['content_overlay_excluded_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#description' => t('Enter one page per line as Drupal paths. The "*" character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page.'),
    '#default_value' => variable_get('content_overlay_excluded_pages', 'admin/*'),
  );

  return system_settings_form($form);
}

/**
 *  Validates values from system configuration form
 */
function content_overlay_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['content_overlay_cookie_duration'])) {
    form_set_error('text', t('Cookie life expentancy must be a number.'));
  }
}