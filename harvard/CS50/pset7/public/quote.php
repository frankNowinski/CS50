<?php 

    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Reject unpopulated fields
        if (empty($_POST["symbol"]))
            apologize("Please enter a stock ticker.");

        // Store stock
        $stock = (lookup($_POST["symbol"]));
            
        if ($stock === false)
            apologize("Invalid stock.");
          
        else
            render("quote_result.php", ["symbol" => strtoupper($stock["symbol"]), "name" => $stock["name"], "price" => $stock["price"]]);
        
    }
    else
        render("quote_form.php", ["title" => "Quote"]);
?> 