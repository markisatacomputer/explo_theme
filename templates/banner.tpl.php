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
 <div class="jumbotron p-4 p-md-5 <?php print $classes; ?>" style="<?php print $style; ?>">
  <div class="row <?php print $row_classes; ?>">
    <div class="<?php print $col_classes; ?>">
      <?php print $text_box; ?>
    </div>
  </div>
</div>
