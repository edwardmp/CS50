<?php

     /***********************************************************************
     * history.php
     *
     * Edward M. Poot
     * edwardmp@gmail.com
     *
     * Problem Set 7
     *
     * Retrieves transaction history from database.
     **********************************************************************/

    // configuration
    require("../includes/config.php");
    
    $logs = query("SELECT t.* FROM transaction_log t WHERE t.user_id = ? ORDER BY t.id DESC", $_SESSION["id"]);

    if (count($logs) >= 1)
        render("history_table.php", ["title" => "Transaction history", "logs" => $logs]);
    else
        apologize("You haven't sold or bought any shares, so there is transaction history yet."); 
?>
