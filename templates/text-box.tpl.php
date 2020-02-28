<?php
/**
 * @file
 * Default theme implementation to display a explo banner with text overlay.
 *
 * Available variables:
 * - $image
 * - $link
 * - $prelude
 * - $title
 * - $banner_text
 * - $textcolor
 * - $bgcolor
 * - $linkcolor
 * - $opacity
 */
 ?>
  <div class="<?php print $classes; ?>">
    <span class="prelude"><?php print $prelude; ?></span>
    <h1 class="display-4"><?php print $title; ?></h1>
    <p class="lead my-3"><?php print $text; ?></p>
    <?php print render($link); ?>
  </div>
