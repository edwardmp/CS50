<?php 

     /***********************************************************************
     * quote.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Retrieves current stock information.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php"); 
    
    // if stock lookup requested
    if (isset($_POST["symbol"]))
    {
        // sanity check
        if (empty($_POST["symbol"]) || !preg_match('/^[a-zA-Z0-9\.^]+$/', $_POST["symbol"]))
            apologize("The symbol you entered is not alphanumerical. Only alphanumeric characters and dots are allowed. Try again.", true);
        
        // lookup stock information
        if (($stock = lookup($_POST["symbol"])))
            render("stock_lookup_display.php", array_merge(["title" => "Stock information for company ".$stock["name"].""], $stock), true);
        else
            apologize("We couldn't get any info on the stock symbol ".$_POST["symbol"]." you supplied.", true);             
    }
    // render stock lookup form
    else
    {
        render("stock_lookup.php", ["title" => "Lookup stock information"]);
    }


?>
