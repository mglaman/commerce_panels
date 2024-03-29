<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Order changed date'),
  'icon' => 'icon_order.png',
  'description' => t('The date the referenced order was changed.'),
  'required context' => new ctools_context_required(t('Commerce Order'), 'commerce_order'),
  'category' => t('Commerce Order'),
  'defaults' => array(
    'format' => 'small',
  ),
);

/**
 * Render the custom content type.
 */
function commerce_panels_commerce_order_changed_content_type_render($subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  // Get a shortcut to the node.
  $commerce_order = clone $context->data;

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'commerce_order_changed';
  $block->title   = t('changed date');
  $block->content = format_date($commerce_order->changed, $conf['format']);
  $block->delta   = $commerce_order->order_id;

  return $block;
}

/**
 * Returns an edit form for custom type settings.
 */
function commerce_panels_commerce_order_changed_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $date_types = array();

  foreach (system_get_date_types() as $date_type => $definition) {
    $date_types[$date_type] = format_date(REQUEST_TIME, $date_type);
  }
  $form['format'] = array(
    '#title' => t('Date format'),
    '#type' => 'select',
    '#options' => $date_types,
    '#default_value' => $conf['format'],
  );
  return $form;
}

/**
 * Submit handler for the custom type settings form.
 */
function commerce_panels_commerce_order_changed_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a type.
 */
function commerce_panels_commerce_order_changed_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" changed date', array('@s' => $context->identifier));
}
