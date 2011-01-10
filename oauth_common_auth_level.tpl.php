<?php
// $Id: oauth_common_auth_level.tpl.php,v 1.2 2011/01/10 22:22:29 voxpelli Exp $

$element['left'] = array(
  '#prefix' => '<div class="oauth-common-left-panel">',
  '#suffix' => '</div>',
);
$element['right'] = array(
  '#prefix' => '<div class="oauth-common-right-panel">',
  '#suffix' => '</div>',
);

$children = element_children($element);
foreach ($children as $key) {
  if (isset($element[$key]['#oauth_common_panel'])) {
    switch ($element[$key]['#oauth_common_panel']) {
      case 'left':
        $element['left'][$key] = $element[$key];
        unset($element[$key]);
        break;
      case 'right':
        $element['right'][$key] = $element[$key];
        unset($element[$key]);
        break;
    }
  }
}
?>

<div class="oauth-common-auth-level">
  <?php print drupal_render($element); ?>
  <div class="clear"></div>
</div>
