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
  function get_cookie(name) {
    var cookieName = name + "=";
    var cookieData = document.cookie.split(';');
    for(var i = 0; i < cookieData.length; i++) {
      var c = cookieData[i];
      while (c.charAt(0)==' ') {
        c = c.substring(1, c.length);
      }
      if (c.indexOf(cookieName) == 0) {
        return c.substring(cookieName.length,c.length);
      }
    }
    return null;
  }
  
  $(document).ready( function() {
    $('#mask, .window').hide();
    $('#mask, .window .close').click(function() {
      $('#mask, .window').hide();
    });

    $(window).resize(function() {
      var box = $('#content-overlay .window');

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
	  if (get_cookie('content-overlay-visited') == null) {console.log(document.cookie);
		  launch_popup('#content-overlay .window');
		  var date = new Date();
      var duration = Drupal.settings.content_overlay.cookie_duration * 1;
		  date.setTime(date.getTime() + duration);
		  document.cookie = 'content-overlay-visited=TRUE; path=/; expires=' + date.toGMTString() + ';';
    }
  });
})(jQuery);
