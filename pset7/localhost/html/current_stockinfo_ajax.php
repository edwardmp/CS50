<?php

     /***********************************************************************
     * current_stockinfo_ajax.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Retrieves current stock information and returns it in JSON format.
     * This is used in the portfolio through an AJAX call.
     **********************************************************************/
      
    // configuration
    require("../includes/config.php");
    
    // sanity checks
    if (!empty($_GET["symbol"]) && preg_match('/^[a-zA-Z0-9\.]+$/', $_GET["symbol"]))
    {
        // lookup info
        $stock = lookup($_GET["symbol"]);
        
        // encode it and print it back
        print(json_encode($stock));
    }
    else
        print(json_encode(array("data" => "Error with symbol" . $_GET["symbol"])));
?>
