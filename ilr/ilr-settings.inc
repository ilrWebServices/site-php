<?php
/**
 * @file
 * Code to include the correct setting-php.inc file for any given Drupal installation.
 */

/**
 * This file, running within the context of a local development environment, stubs out the 
 * behavior of ilr-setting.inc on Acquia Cloud Hosting. There it allows the dame code base to 
 * run simultaneously on all three servers (dev, staging, prod). In the local environment, it
 * pairs up a specific Drupal installation with its database connection settings. 
 */

# Find the drupal root directory (minus the trailing 'docroot') from the current path
# This assumes that Apache's web root is /var/www/ and won't work otherwise
if (! isset($thisMultisite)) $thisMultisite = '';
if (strlen($thisMultisite) == 0) {
  $drupal_root = preg_replace("/\/var\/www/", "", realpath(''));
  $drupal_root = preg_replace("/\/docroot.*/", "", $drupal_root);
} else {
  $drupal_root = preg_replace("/\/var\/www/", "", $thisMultisite);
  $drupal_root = preg_replace("/\/docroot/", "", $drupal_root);
}

#$drupal_root = preg_replace("/docroot.*/", "", $drupal_root);

# Build the path where the include file should be
$include_path = '/var/www/site-php/ilr' . $drupal_root . '/settings-php.inc';
if (file_exists($include_path)) {
  require($include_path);
}
else { 
  # If the include files hasn't been created yet, display a message and don't let anything else happen until it has.
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en" dir="ltr">
  <head>
    <title>Provide a database include for setting.php | Drupal</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css" media="all">
      @import url("modules/system/system.base.css?0");
      @import url("modules/system/system.admin.css?0");
      @import url("modules/system/system.menus.css?0");
      @import url("modules/system/system.messages.css?0");
      @import url("modules/system/system.theme.css?0");
      @import url("modules/system/system.maintenance.css?0");
      @import url("themes/seven/reset.css?0");
      @import url("themes/seven/style.css?0");
    </style>
  </head>
  <body class="maintenance-page in-maintenance db-offline one-sidebar sidebar-first">
    <div class="section">
      <div id="messages">
        <div class="section clearfix">
          <div class="messages error">
            <h2 class="element-invisible">Error message</h2>
            <?php
              print 'There was a problem initializing Drupal. Drupal can\'t load because database settings have not been provided. <br />Please create a database settings file at <em class="placeholder">' . $include_path .  '</em> and try again.';
            ?>
          </div>
        </div>
      </div> <!-- /.section, /#messages -->
    </div>
  </body>
</html>
<?php
exit;
}
?>
