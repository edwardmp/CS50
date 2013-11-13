<?php

     /***********************************************************************
     * register.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Let's the user register for a new account.
     **********************************************************************/
     
    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
            apologize("You forgot to fill in an username.");
        else if (empty($_POST["password"]))
            apologize("You forgot to fill in a password.");
        else if (empty($_POST["confirmation"]) || $_POST["password"] != $_POST["confirmation"])
            apologize("Password confirmation is not the same as the entered password.");
        else if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z])[0-9A-Za-z!&@#$%]{6,12}$/', $_POST["password"]))
            apologize("The new password does not meet the requirements. Try again.");
            
        $query = query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
        
        // something went wrong
        if ($query === false)
            trigger_error("Could not insert new user ".$_POST["username"].". Aborting.", E_USER_ERROR);
            
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        
        // log the user in and redirect to index       
        $_SESSION["id"] = $rows[0]["id"];
        $_SESSION["username"] = $_POST["username"];
        redirect("/");                       
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
?>
