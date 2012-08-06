//creating a closure to prevent namespacing issues with our get_cookie function
(function ($){
  /**
   *  String parsing function - basically find the cookie with the right name and grab its value
   */
  function get_cookie(c_name){
    if (document.cookie.length>0){
      var c_start = document.cookie.indexOf(c_name + "=");
      if (c_start != -1){
        c_start = c_start + c_name.length+1;
        c_end = document.cookie.indexOf(";",c_start);
        if (c_end==-1){
           c_end = document.cookie.length;
         }
        return document.cookie.substring(c_start,c_end);
      }
    }
    return false;
  }
  
  
  /**
   *  This js will only be included on pages where the user could leave from and see the signup wall
   *
   *  Check to see if the user meets the requirements to see the signup wall
   *  If they're anonymous and do meet the requirements, add a cookie to get past
   *  Varnish.  We'll handler the rest of the logic on the backend.
   */
  $(document).ready( function() {
    var countdate = new Date();
    countdate.setTime(countdate.getTime()+(2592000000000));

    if(Drupal.settings.signup_wall.signup){
      //update the count to see the signup wall    
      if(!get_cookie('signup-wall-count')){
        document.cookie = 'signup-wall-count=1; path=/; expires='+countdate.toGMTString()+';';
      } else if (!$(document.body).hasClass('page-signup') && $(document.body).hasClass('not-front') && !get_cookie('signup-wall-visited') &&
                   $(document.body).hasClass('not-logged-in') && get_cookie('signup-wall-count') < 2) {
        var signupcount = get_cookie('signup-wall-count');
        signupcount++;	
        document.cookie = 'signup-wall-count='+signupcount+'; path=/; expires='+countdate.toGMTString()+';';
      }
    }

    // We need to set a cookie to say that the user is on a page in which the next page could need to show the wall
    if (Drupal.settings.signup_wall.ad && !$(document.body).hasClass('page-signup') && !get_cookie('signup-wall-session-seen') ) {
        document.cookie = 'SESS00000000000000000000000000000000=45454adf453534; path=/;';
    } //show the signup wall
    else if(Drupal.settings.signup_wall.signup && !$(document.body).hasClass('page-signup') && !get_cookie('signup-wall-visited') &&
       $(document.body).hasClass('not-logged-in') && !get_cookie('SESS00000000000000000000000000000000') && get_cookie('signup-wall-count') > 1){
      document.cookie = 'SESS00000000000000000000000000000000=45454adf453534; path=/;';
    }
    
    // Refresh the signup-wall-visited cookie which is used to determine which version of the signupwall they see
    if(get_cookie('signup-wall-visited')){
      var date = new Date();
      date.setTime(date.getTime()+(36000000000));
      document.cookie = 'signup-wall-visited=TRUE; path=/; expires='+date.toGMTString()+';'; 
    }
    
  }); 
})(jQuery);

