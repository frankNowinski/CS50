<?php 

    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Reject unpopulated fields
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
            apologize("Please populate both fields.");
    
        // Lookup stock ticker of the share you want to sell
        $stock = (lookup($_POST["symbol"]));
            
        if ($stock === false)
            apologize("Invalid stock.");
        
        // Verify integer was inputted
        if (!preg_match("/^\d+$/", $_POST["shares"]))
            apologize("Must enter positive integer");
          
        else
        {
            // Set transaction type
            $transaction = 'BUY';
            
            // Cost of share
            $cost = $stock["price"] * $_POST["shares"];
            
            // Query cash
            $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            if ($cash < $cost)
                apologize("Insufficient funds.");
            
            else 
            {
                // Insert stock into portfolio
                $query = query("INSERT INTO portfolio(id, symbol, shares) VALUES(?, ?, ?)
                    ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"]);
                
                if ($query === false)
                    apologize("Error adding stocks to your portfolio.");
                
                // Update users cash
                $cash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
                
                $_SESSION["cash"] -= $cost;
                
                // Update history
                $history = query("INSERT INTO history(id, transaction, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?, NOW())", $_SESSION["id"], $transaction, strtoupper($stock["symbol"]), $_POST["shares"], $stock["price"]);
                
                redirect("/");                        
            }      
        }
    }     
    else
        render("buy_form.php", ["title" => "Buy"]);
?> 
             
        
        
