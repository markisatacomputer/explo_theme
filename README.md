# Exploratorium Theme Implementation
This module is where all new Exploratorium componenets will live in Drupal 7, while we begin the migration and rebuild process.  New componenents are built on top of [Bootstrap 4](https://getbootstrap.com/docs/4.0/) and configured in Drupal using Ctools custom content types within Panels. 

### Component architecture
For each new componenet, there is a set of deliverables:
* hook_theme:  Declare new theme hook.
* theme_preprocess_hook:  Process all the variables for use in template
* template/: template file
* plugins/content_types/: ctools content type include file 

@see https://git.drupalcode.org/project/ctools/tree/7.x-1.x/ctools_plugin_example/plugins/content_types for content_type examples.
