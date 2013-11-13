<?php

     /***********************************************************************
     * current_balance_ajax.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Retrieves current cash balance and returns it in JSON format.
     * This is used in the navbar through an AJAX call.
     **********************************************************************/
      
    // configuration
    require("../includes/config.php");
    
    // sanity checks
    if (!empty($_SESSION["id"]))
    {
        // lookup info
        $balance = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // encode it and print it back
        print(json_encode($balance[0]));
    }
    else
        print(json_encode(array("data" => "Error with retrieving balance")));
?>
