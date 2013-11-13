<?php 
 
     /***********************************************************************
     * deposit_funds.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Let's user deposit additional funds.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php"); 
    
    // when form is submitted
    if(isset($_POST["funds_amount"]))
    {    
        // sanity checks
        if (empty($_POST["funds_amount"]))
            apologize("Funds amount can't be empty. Try again.", true);
        else if ($_POST["funds_amount"] <= 0)
            apologize("You must deposit more than 0 cash.", true);
        
        // update users table
        $change_cash_sql = query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["funds_amount"], $_SESSION["id"]);        
        // if 1 row affected, everything's OK
        if (count($change_cash_sql == 1))
            render("change_funds_success.php", ["title" => "Succesfully changed cash balance"], true);
        else
            apologize("Something went wrong while updating your cash balance. It has not been changed yet. Please try again later.", true);
    }
    else
        render("change_funds_form.php", ["title" => "Change your cash balance"]);
?>
