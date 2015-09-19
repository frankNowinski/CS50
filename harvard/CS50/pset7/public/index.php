<?php

    // configuration
    require("../includes/config.php"); 
    
    // Query current shares
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    
    foreach($rows as $row)
    {
        // Query Yahoo Finance
        $stock = lookup($row["symbol"]);
        
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }                                      
    }  
    
    $users = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

    // Render portfolio
    render("portfolio.php", ["positions" => $positions,"title" => "Portfolio", "users" => $users]);

?>

