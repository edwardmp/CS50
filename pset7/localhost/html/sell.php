<?php

     /***********************************************************************
     * sell.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Let's the user sell owned stocks.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php");
    
    // if stock lookup requested
    if (isset($_POST["symbol"]))
    {
        // sanity checks
        if (empty($_POST["symbol"]) || !preg_match('/^[a-zA-Z0-9\.^]+$/', $_POST["symbol"]))
            apologize("The symbol you entered is not alphanumerical. Only alphanumeric characters and dots are allowed. Try again.", true);
        else if (!preg_match("/^\d+$/", $_POST["amount_sold"]))
            apologize("The amount of shares to be sold is not a whole number.", true);
        else if (empty($_POST["amount_sold"]) || $_POST["amount_sold"] <= 0)
            apologize("The amount of shares to be sold is empty or negative. Try again.", true);
        
        // lookup current stock information
        if (($stock = lookup($_POST["symbol"])))
        {          
            if (empty($_POST["id"]))
            {
                $stocks = query("SELECT * FROM user_stocks WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $stock["symbol"]);
                if (count($stocks) > 0)
                {
                    render("stock_sell_pick_owned_stock_form.php", ["title" => "Choose which owned stock of ".$stock["symbol"]." to sell", "stocks" => $stocks, "shares_amount" => $_POST["amount_sold"]], true);
                    exit;
                }
            }
             
            // checks if user actually owns this stock         
            $query_select = query("SELECT shares_amount, id FROM user_stocks WHERE user_id = ? AND id = ? LIMIT 1", $_SESSION["id"], $_POST["id"]);
            if (!$query_select)
                apologize("You are trying to sell ".$stock["name"]." stock you don't own.", true);
            
            // start updating database               
            query("START TRANSACTION;");
            $sell_price = $_POST["amount_sold"] * $stock["price"];
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $sell_price, $_SESSION["id"]);
            $query_update = query("UPDATE user_stocks SET shares_amount = shares_amount - ? WHERE user_id = ? AND id = ?", $_POST["amount_sold"], $_SESSION["id"], $_POST["id"]);
            
            // delete stock row if amount is 0
            if (($query_select[0]["shares_amount"] - $_POST["amount_sold"]) == 0)
                $query_delete = query("DELETE FROM user_stocks WHERE id = ?", $query_select[0]["id"]);
            else if (($query_select[0]["shares_amount"] - $_POST["amount_sold"]) < 0)
            {
                query("ROLLBACK;");
                apologize("Amount of shares owned is less than amount sold. Try again.", true);
            }
            
            // if something went wrong, rollback
            if (($query_update && !is_array($query_update)))
            {
                apologize("Something went seriously wrong in updating the database..", true);
                query("ROLLBACK;");
            }
            else
                query("COMMIT;");  
                  
            render("stock_sell_success.php", array_merge(["title" => "Succesfully sold stock of ".$stock["name"].""], $stock, $_POST), true);
        
        }
        else
        {
            apologize("We couldn't get any info on the stock symbol ".$_POST["symbol"]." you supplied.", true);
        }
               
    }
    // render stock lookup form
    else
    {      
        $stocks_owned = query("SELECT COUNT(*) as amount FROM user_stocks WHERE user_id = ?", $_SESSION["id"]);
        
        // if user has no stocks, display message
        if ($stocks_owned[0]["amount"] == 0)
            apologize("You can't sell stocks because you don't own any at the moment. Buy some first!'");
        // if id is set in the URL, we can fill in some form data
        else if (isset($_GET["id"]))
        {
            $query = query("SELECT * FROM user_stocks WHERE user_id = ? AND id = ? LIMIT 1", $_SESSION["id"], $_GET["id"]);
            render("stock_sell_form.php", ["title" => "Sell stocks", "symbol" => $query[0]["symbol"], "shares_amount" => $query[0]["shares_amount"], "id" => $_GET["id"]]);
        }
        else
            render("stock_sell_form.php", ["title" => "Sell stocks"]);
    }
?>
