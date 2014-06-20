f (Drupal.jsEnabled) {
      $(document).ready(function () {
              $('div.toggle_area').find('div.toggle_content').hide().end().find('div.toggle_label').click(function() {
                        $(this).next().slideToggle();
                            });
                });
}
