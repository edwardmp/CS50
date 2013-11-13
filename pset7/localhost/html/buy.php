<?php

     /***********************************************************************
     * buy.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Let's the user buy stocks.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php");
    
    // if stock lookup requested
    if (isset($_POST["symbol"]))
    {
        // sanity checks
        if (empty($_POST["symbol"]) || !preg_match('/^[a-zA-Z0-9\.^]+$/', $_POST["symbol"]))
            apologize("The symbol you entered is not alphanumerical. Only alphanumeric characters and dots are allowed. Try again.", true);
        else if (!preg_match("/^\d+$/", $_POST["amount_purchased"]))
            apologize("The amount of shares to be purchased is not a whole number. Try again.", true);
        else if (empty($_POST["amount_purchased"]) || $_POST["amount_purchased"] <= 0)
            apologize("The amount of shares to be purchased is empty or negative. Try again.", true);
        
        // retrieve current stock info   
        if (($stock = lookup($_POST["symbol"])))
        {          
            // checks if user has enough cash to proceed
            $query_select = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            $buy_price = $_POST["amount_purchased"] * $stock["price"];
            if ($query_select[0]["cash"] < $buy_price)
                apologize("You don't have enough cash to buy this amount of stocks", true);
            
            // start updating database
            query("START TRANSACTION;");
            $query_update = query("UPDATE users SET cash = cash - ? WHERE id = ?", $buy_price, $_SESSION["id"]);
            $query_insert = query("INSERT INTO user_stocks (user_id, symbol, company, stock_exchange, shares_amount, share_price) VALUES(?, ?, ?, ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $stock["name"], $stock["name"], $_POST["amount_purchased"], $stock["price"]);
            
            // if something went wrong rollback
            if (($query_update && !is_array($query_update)) || ($query_insert && !is_array($query_insert)))
            {
                apologize("Something went seriously wrong in updating the database.. Try again later.", true);
                query("ROLLBACK;");
            }
            else
                query("COMMIT;"); 
                
            render("stock_buy_success.php", array_merge(["title" => "Succesfully bought stock of ".$stock["name"].""], $stock, $_POST), true);
        }
        else
        {
            apologize("We couldn't get any info on the stock symbol ".$_POST["symbol"]." you supplied.", true);
        }
               
    }
    // render stock lookup form
    else
    {
        render("stock_buy_form.php", ["title" => "Buy stocks"]);
    }
?>
