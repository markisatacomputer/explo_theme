<?php
/**
 * @file
 * Default theme implementation to display a explo banner.
 *
 * Available variables:
 * - $image
 * - $link
 * - $prelude
 * - $title
 * - $banner_text
 * - $textcolor
 * - $bgcolor
 * - $hposition
 * - $vposition
 * - $width
 *
 */
 ?>
 <div class="container p-0 m-0 <?php print $classes; ?>">
  <div class="row no-gutters">
    <div class="p-4 p-md-5 <?php print $col_classes; ?>">
      <?php print $text_box; ?>
    </div>
    <div class="<?php print $img_col_classes; ?>"><?php print render($img); ?></div>
  </div>
</div>