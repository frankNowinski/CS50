<?php 

    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Reject unpopulated fields
        if (empty($_POST["symbol"]))
            apologize("Please enter stock symbol.");
            
        // Lookup stock ticker of the share you want to sell
        $stock = lookup($_POST["symbol"]);
            
        if ($stock === false)
            apologize("Invalid stock.");
        
        else
        {
            $transaction = 'SELL';
            
            // Query stock symbol in your portfolio 
            $rows = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["symbol"]));
                
            if (count($rows) == 1)
               $shares = $rows[0]["shares"];
            else 
               apologize("Error locating shares in your portfolio.");
                            
            // Stock price value times the amount of shares to sell 
            $value = $stock["price"] * $_POST["shares"];
                          
            // Delete stocks from users portfolio
            $delete = query("UPDATE portfolio SET shares = shares - ? WHERE id = ? AND symbol = ?", $_POST["shares"], $_SESSION["id"], strtoupper($_POST["symbol"]));
                                    
            if ($delete === false)
                apologize("Error selling shares.");
                
            // Update users cash 
            $cash = query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
                
            // Update cash 
            $_SESSION["cash"] += $value;
                
            // Update history 
            $history = query("INSERT INTO history(id, transaction, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?, NOW())", $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $stock["price"]);
               
            redirect("/");   
        }                      
    }  
    else
    {
        // Query users portfolio
        $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
        
        // Create an array to hold stock symbols
        $stocks = [];
        
        foreach ($rows as $row)
        {
            // Store stock symbol
            $stock_symbol = $row["symbol"];
            
            $stocks[] = $stock_symbol;
        }
     
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);
    }
?>        
