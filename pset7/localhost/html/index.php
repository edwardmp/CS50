<?php

     /***********************************************************************
     * index.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Display's user's portfolio including realtime stock information.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php"); 

    // retrieve user and stock data from db
    $query = query("SELECT u.*, s.* FROM users u LEFT OUTER JOIN user_stocks s ON u.id = s.user_id WHERE u.id = ?", $_SESSION["id"]);
    
    // if there is at least one stock in portfolio proceed
    if (isset($query[0]["symbol"]))
        // render portfolio
        render("portfolio.php", ["title" => "Portfolio", "stocks" => $query, "cash" => $query[0]["cash"]]);
    else
        apologize("You don't have any stocks in your portfolio. Buy some first!");
?>
