<?php

     /***********************************************************************
     * logout.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Logs the user out, destroys session data.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php"); 

    // log out current user, if any
    logout();

    // redirect user
    redirect("/");

?>
