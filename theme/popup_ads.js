(function ($){
  /**
   *  Creates popup and instantiates functions post-render
   */
  function launch_popup(id) {
    // Get the screen height and width
    var maskHeight = $(document).height();
    var maskWidth = $(window).width();
    
    // Set height and width to mask to fill up the whole screen
    $('#mask').css({
        'width': maskWidth,
        'height': maskHeight
    });

    // Transition effect
    $('#mask').fadeIn(1000);
    $('#mask').fadeTo("slow", 0.8);

    // Get the window height and width
    var winH = $(window).height();
    var winW = $(window).width();
    
    // Set the popup window to center
    $(id).css('top', winH / 2 - $(id).height() / 2);
    $(id).css('left', winW / 2 - $(id).width() / 2);

    // Transition effect
    $(id).fadeIn(2000);
  }

  /**
   *  String parsing function - basically find the cookie with the right name and grab its value
   */
  function get_cookie(c_name){
    if (document.cookie.length > 0){
      var c_start = document.cookie.indexOf(c_name + "=");
      if (c_start != -1){
        c_start = c_start + c_name.length + 1;console.log(c_start);
        c_end = document.cookie.indexOf(";", c_start);console.log(document.cookie.substring(c_start, c_end));
        if (c_end == -1){
           c_end = document.cookie.length;
         }
        return document.cookie.substring(c_start, c_end);
      }
    }
    return false;
  }
  
  $(document).ready( function() {$('#mask, .window').hide();
    $('#mask, .window .close').click(function() {
      $('#mask, .window').hide();
    });

    $(window).resize(function() {
      var box = $('#popup-ads .window');

      // Get the screen height and width
      var maskHeight = $(document).height();
      var maskWidth = $(window).width();

      // Set height and width to mask to fill up the whole screen
      $('#mask').css({
        'width': maskWidth,
        'height': maskHeight
      });

      // Get the window height and width
      var winH = $(window).height();
      var winW = $(window).width();

      // Set the popup window to center
      box.css('top', winH / 2 - box.height() / 2);
      box.css('left', winW / 2 - box.width() / 2);
    });

    // If cookie is expired, display the pop up
	  if (!get_cookie('popup-ads-visited')) {
		  launch_popup('#popup-ads .window');
		  var date = new Date();
      var duration = Drupal.settings.popup_ads.cookie_duration * 1;
		  date.setTime(date.getTime() + duration);
		  document.cookie = 'popup-ads-visited=TRUE; path=/; expires=' + date.toGMTString() + ';';
    }
  });
})(jQuery);
