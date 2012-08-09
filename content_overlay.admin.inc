<?php 
/**
 * Create the admin settings form for the signup popup
 */
function content_overlay_admin_settings() {
  $nodetypes = node_get_types('names');

  $form = array();

  $form['content_overlay_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Content Overlay'),
    '#default_value' => variable_get('content_overlay_enabled', FALSE),
    '#description' => t('Enable content overlay on your site.')
  );

  $form['content_overlay_cookie_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Life Expectancy'),
    '#default_value' => variable_get('content_overlay_cookie_duration', 1800),
    '#description' => t('How long till the pop up should appear again on the visitor\'s computer.  This value must be set in seconds.')
  );


  $form['content_overlay_overlay_content'] = array(
    '#type' => 'textarea',
    '#title' => t('Content Overlay Content'),
    '#description' => t('The content you would like to use here.  HTML is allowed.'),
    '#default_value' => variable_get('content_overlay_overlay_content', ''),
  );

  $form['content_overlay_box_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Box Width'),
    '#default_value' => variable_get('content_overlay_box_width', '700px'),
    '#description' => t('The width of the overlay box.  Include the measurement (e.g. px, em)'),
  );

  $form['content_overlay_box_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Box Height'),
    '#default_value' => variable_get('content_overlay_box_height', '450px'),
    '#description' => t('The height of the overlay box. Include the measurement (e.g. px, em)'),
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

  // Verify if width is correct
  preg_match('/^(\d+(px|em|ex|pt|in|pc|mm|cm))$/', $form_state['values']['content_overlay_box_width'], $width);
  if (!$width) {
    form_set_error('text', t('Your box width is invalid (perhaps try "700px" or "80em")'));
  }

  // Verify if height is correct
  preg_match('/^(\d+(px|em|ex|pt|in|pc|mm|cm))$/', $form_state['values']['content_overlay_box_height'], $height);
  if (!$height) {
    form_set_error('text', t('Your box height is invalid (perhaps try "700px" or "80em")'));
  }
}