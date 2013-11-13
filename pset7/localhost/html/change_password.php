<?php 
 
     /***********************************************************************
     * change_password.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Let's user change his password.
     **********************************************************************/
  
    // configuration
    require("../includes/config.php"); 
    
    // when form is submitted
    if(isset($_POST["password"]))
    {    
        // sanity checks
        if (empty($_POST["password"]))
            apologize("The password can't be empty. Try again.", true);
        else if($_POST["password"] != $_POST["password_confirm"])
            apologize("The confirmation password is not the same as the new password! Try again.", true);
        else if (!preg_match('/^(?=.*\d)(?=.*[A-Za-z])[0-9A-Za-z!&@#$%]{6,12}$/', $_POST["password"]))
            apologize("The new password does not meet the requirements. Try again.", true);
        
        // update users table
        $change_password_sql = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);        
        // if 1 row affected, everything's OK
        if (count($change_password_sql == 1))
            render("change_password_success.php", ["title" => "Succesfully changed password"], true);
        else
            apologize("Something went wrong while updating your password. It has not been changed yet. Please try again later.", true);
    }
    else
        render("change_password_form.php", ["title" => "Change your password"]);
?>
