<?php

/**
 * @file
 * ctools content type to render a single banner.
 *
 * This should be able to be configured so that the banner can be rendered
 * in any banner style that exists and is themed.
 *
 * The banner image will come from either a image field or the banners field.
 */

$plugin = array(
  'title' => t('Banner'),
  'content_types' => 'explo_banner_content_type',
  'single' => TRUE,
  'render callback' => 'explo_banner_content_type_render',
  'icon' => 'icon_example.png',
  'description' => t('Banner - works with node image field or banner field.'),
  'edit form' => 'explo_banner_content_type_edit_form',
  'admin title' => 'explo_banner_content_type_admin_title',

  // Presents a block which is used in the preview of the data.
  // Pn Panels this is the preview pane shown on the panels building page.
  'admin info' => 'explo_banner_content_type_admin_info',
  'category' => array(t('Explo'), -9),
);

function explo_banner_content_type_admin_title($subtype, $conf, $context = NULL) {
  $output = t('Banner');

  return $output;
}

/**
 * Callback to provide administrative info (the preview in panels when building
 * a panel).
 *
 */
function explo_banner_content_type_admin_info($subtype, $conf, $context = NULL) {
  $block = array(
    '#markup' => '<pre>'.var_export($conf, TRUE).'</pre>',
  );
  return $block;
}

/**
 * Run-time rendering of the body of the block (content type)
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time
 * @param $args
 * @param $context
 *   Context - in this case we don't have any
 *
 * @return
 *   An object with at least title and content members
 */
function explo_banner_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = "";

  //  These are the same across all themes
  $vars = array(
    'image' => file_load($conf['image']),
    'link_text' => $conf['link_text'],
    'link_url' => $conf['link_url'],
    'prelude' => $conf['prelude'],
    'title' => $conf['title'],
    'banner_text' => $conf['banner_text'],
  );

  //  These are per component style
  switch ($conf['banner_style']) {
    case 'explo_banner_text_box_large':
      $vars = $vars+array(
        'bgcolor' => $conf['tbl_bgcolor'],
        'textcolor' => $conf['tbl_textcolor'],
        'hposition' => $conf['tbl_hposition'],
        'width' => $conf['tbl_width'],
        'vposition' => $conf['tbl_vposition'],
      );
      break;

    case 'explo_banner_text_box_small':
      $vars = $vars+array(
        'bgcolor' => $conf['tbs_bgcolor'],
        'hposition' => $conf['tbs_hposition'],
        'opacity' => $conf['tbs_opacity'],
      );
      break;

    case 'explo_banner_text_overlay':
      $vars = $vars+array(
        'width' => $conf['to_width'],
        'hposition' => $conf['to_hposition'],
        'vposition' => $conf['to_vposition'],
      );
      break;

  }

  //  Render the banner.
  $block->content = theme($conf['banner_style'], $vars);

  return $block;
}

function _explo_banner_content_type_banner_options($banner) {
  $bwrap = entity_metadata_wrapper('field_collection_item', $banner);
  $content = $bwrap->field_content->value();
  return ($content->title) ? $content->title : FALSE;
}
function _explo_banner_content_type_banner_nodes($banner) {
  $bwrap = entity_metadata_wrapper('field_collection_item', $banner);
  $content = $bwrap->field_content->value();
  return ($content->nid) ? $content->nid : FALSE;
}

/**
 * 'Edit' callback for the content type.
 * This example just returns a form.
 */
function explo_banner_content_type_edit_form($form, &$form_state) {
  //  @see https://api.drupal.org/api/drupal/includes%21form.inc/function/form_load_include/7.x
  form_load_include($form_state, 'inc', 'explo_theme', 'plugins/content_types/explo_banner');

  $conf = $form_state['conf'];
  $bgcolor_options = array(
    '' => '',
    'black' => 'black',
    'fog' => 'fog',
    'flamingo' => 'flamingo',
    'quartz' => 'quartz',
    'cloud' => 'cloud',
    'seafoam' => 'seafoam',
    'pollen' => 'pollen',
    'smoke' => 'smoke',
    'salmon' => 'salmon',
    'lavender' => 'lavender',
    'manatee' => 'manatee',
    'lime' => 'lime',
    'tumeric' => 'tumeric',
    'wood' => 'wood',
    'lava' => 'lava',
    'rose' => 'rose',
    'ocean' => 'ocean',
    'grass' => 'grass',
    'sun' => 'sun',
    'steel' => 'steel',
    'fire' => 'fire',
    'plum' => 'plum',
    'sapphire' => 'sapphire',
    'emerald' => 'emerald',
    'saffron' => 'saffron',
    'charcoal' => 'charcoal',
    'clay' => 'clay',
    'eggplant' => 'eggplant',
    'space' => 'space',
    'forest' => 'forest',
    'persimmion' => 'persimmion',
    'white-bg' => 'white',
    'dark-gray' => 'dark gray',
  );

  $form['required'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'required-wrapper',
    ),
  );
  $form['required']['image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Banner Image'),
    '#description' => t('Please make sure this is at least 1200x480'),
    '#default_value' => !empty($conf['image']) ? $conf['image'] : '',

    '#type'          => 'media',
    '#title'         => t('Banner Image'),
    '#description'   => t('Please make sure this is at least 1200x480'),
    '#theme'         => 'media_widget',
    '#default_value' => !empty($conf['image']) ? $conf['image'] : '',  //the fid
    '#media_options' => array(
      'global' => array(
        'file_directory'  => 'feature_slides',
        'enabledPlugins'  => array(
          'explo_media_browser--banner_browser',
          'upload',
        ),
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize'    => '2 MB',
        'uri_scheme'      => 'public',
        'types'           => array('image'),
        'schemes'         => array(
          'public' => 'public',
        ),
      ),
    ),
  );
  $form['required']['prelude'] = array(
    '#type' => 'textfield',
    '#title' => t('Prelude'),
    '#description' => t(''),
    '#size' => 50,
    '#default_value' => !empty($conf['prelude']) ? $conf['prelude'] : '',
    '#element_validate' => array(),
  );
  $form['required']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t(''),
    '#size' => 50,
    '#default_value' => !empty($conf['title']) ? $conf['title'] : '',
    '#element_validate' => array(),
  );
  $form['required']['link_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Link URL'),
    '#description' => t('This can be an external link or an internal link. (eg. "https://lmgtfy.com" or "/visit")'),
    '#size' => 50,
    '#default_value' => !empty($conf['link_url']) ? $conf['link_url'] : '',
    '#element_validate' => array(),
  );
  $form['required']['link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Link Title'),
    '#size' => 50,
    '#default_value' => !empty($conf['link_text']) ? $conf['link_text'] : '',
    '#element_validate' => array(),
  );
  $form['required']['banner_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Banner Text'),
    '#description' => t(''),
    '#format' => !empty($conf['banner_text']['format']) ? $conf['banner_text']['format'] : 'plain_text',
    '#default_value' => !empty($conf['banner_text']['value']) ? $conf['banner_text']['value'] : '',
    '#element_validate' => array(),
  );
  $form['required']['banner_style'] = array(
    '#type' => 'select',
    '#title' => t('Banner Style'),
    '#description' => t('Please choose one.'),
    '#required' => TRUE,
    '#options' => array(
      'explo_banner_text_box_large' => 'with large text box',
      'explo_banner_text_box_small' => 'with small text box',
      'explo_banner_text_overlay' => 'with text overlay',
    ),
    '#default_value' => !empty($conf['banner_style']) ? $conf['banner_style'] : '',
  );

  //  LARGE TEXT BOX
  $form['explo_banner_text_box_large'] = array(
    '#type' => 'container',
    '#attributes' => array('style' => array('display: flex;')),
    '#states' => array(
      'visible' => array(':input[name="banner_style"]' => array('value' => 'explo_banner_text_box_large')),
    ),
  );
  $form['explo_banner_text_box_large']['tbl_bgcolor'] = array(
    '#type' => 'select',
    '#title' => t('Background Color'),
    '#description' => t('The banners background color.'),
    '#options' => $bgcolor_options,
    '#default_value' => !empty($conf['tbl_bgcolor']) ? $conf['tbl_bgcolor'] : '',
  );
  $form['explo_banner_text_box_large']['tbl_textcolor'] = array(
    '#type' => 'select',
    '#title' => t('Text Color'),
    '#description' => t('The banners background color.'),
    '#options' => array(
      'text-white' => 'white',
      '' => 'black',
    ),
    '#default_value' => !empty($conf['tbl_bgcolor']) ? $conf['tbl_bgcolor'] : '',
  );
  $form['explo_banner_text_box_large']['tbl_hposition'] = array(
    '#type' => 'select',
    '#title' => t('Horizontal Position'),
    '#options' => array(
      'left' => 'left',
      'right' => 'right',
    ),
    '#default_value' => !empty($conf['tbl_hposition']) ? $conf['tbl_hposition'] : '',
  );
  $form['explo_banner_text_box_large']['tbl_vposition'] = array(
    '#type' => 'select',
    '#title' => t('Vertical Position'),
    '#description' => t(''),
    '#options' => array(
      'align-items-start' => 'top',
      'align-items-center' => 'middle',
      'align-items-end' => 'bottom',
    ),
    '#default_value' => !empty($conf['tbl_vposition']) ? $conf['tbl_vposition'] : '',
  );
  $form['explo_banner_text_box_large']['tbl_width'] = array(
    '#type' => 'select',
    '#title' => t('Width'),
    '#options' => array(
      '100%' => '100%',
      '50%' => '50%',
      '33%' => '33%',
      '25%' => '25%',
    ),
    '#default_value' => !empty($conf['tbl_width']) ? $conf['tbl_width'] : '',
  );

  //  SMALL TEXT BOX
  $form['explo_banner_text_box_small'] = array(
    '#type' => 'container',
    '#attributes' => array('style' => array('display: flex;')),
    '#states' => array(
      'visible' => array(':input[name="banner_style"]' => array('value' => 'explo_banner_text_box_small')),
    ),
  );
  $form['explo_banner_text_box_small']['tbs_opacity'] = array(
    '#type' => 'select',
    '#title' => t('Width'),
    '#options' => array(
      '' => '',
      'opacity-100' => '100%',
      'opacity-90' => '90%',
      'opacity-80' => '80%',
      'opacity-70' => '70%',
      'opacity-60' => '60%',
      'opacity-50' => '50%',
    ),
    '#default_value' => !empty($conf['tbs_opacity']) ? $conf['tbs_opacity'] : '',
  );
  $form['explo_banner_text_box_small']['tbs_bgcolor'] = array(
    '#type' => 'select',
    '#title' => t('Background Color'),
    '#description' => t('The banners background color.'),
    '#options' => $bgcolor_options,
    '#default_value' => !empty($conf['tbs_bgcolor']) ? $conf['tbs_bgcolor'] : '',
  );
  $form['explo_banner_text_box_small']['tbs_hposition'] = array(
    '#type' => 'select',
    '#title' => t('Horizontal Position'),
    '#options' => array(
      'left' => 'left',
      'right' => 'right',
    ),
    '#default_value' => !empty($conf['tbs_hposition']) ? $conf['tbs_hposition'] : '',
  );

  //  TEXT OVERLAY
  $form['explo_banner_text_overlay'] = array(
    '#type' => 'container',
    '#attributes' => array('style' => array('display: flex;')),
    '#states' => array(
      'visible' => array(':input[name="banner_style"]' => array('value' => 'explo_banner_text_overlay')),
    ),
  );
  $form['explo_banner_text_overlay']['to_hposition'] = array(
    '#type' => 'select',
    '#title' => t('Horizontal Position'),
    '#options' => array(
      'left' => 'left',
      'middle' => 'middle',
      'right' => 'right',
    ),
    '#default_value' => !empty($conf['to_hposition']) ? $conf['to_hposition'] : '',
  );
  $form['explo_banner_text_overlay']['to_vposition'] = array(
    '#type' => 'select',
    '#title' => t('Vertical Position'),
    '#description' => t(''),
    '#options' => array(
      'align-items-start' => 'top',
      'align-items-center' => 'middle',
      'align-items-end' => 'bottom',
    ),
    '#default_value' => !empty($conf['to_vposition']) ? $conf['to_vposition'] : '',
  );
  $form['explo_banner_text_overlay']['to_width'] = array(
    '#type' => 'select',
    '#title' => t('Width'),
    '#options' => array(
      '100%' => '100%',
      '50%' => '50%',
      '33%' => '33%',
      '25%' => '25%',
    ),
    '#default_value' => !empty($conf['to_width']) ? $conf['to_width'] : '',
  );

  return $form;
}

/*
 *
 */
function explo_banner_content_type_edit_form_submit($form, &$form_state) {
  //  Get all the values nested in our form sections.
  $sections = array(
    'required',
    'explo_banner_text_box_large',
    'explo_banner_text_box_small',
    'explo_banner_text_overlay',
  );
  foreach ($sections as $section) {
    foreach ($form[$section] as $key => $value) {
      # code...
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
