<?php 
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {  
        // Confirm that both passwords match
        if ($_POST["password"] != $_POST["confirmation"])
            apologize("Your passwords do not match");
        
        // Populated inputs
        if (!empty($_POST["username"]) && !empty($_POST["password"]))
        {
            $username = $_POST["username"];
            $password = $_POST["password"];
            
            // Determine if username exist
            $rows = query("SELECT * FROM users WHERE id = ?", $_POST["username"]);
            
            if (count($rows) == 1)
                apologize("Username already exists");
            
            else
            {
                // Add username to database
                $query = query("INSERT INTO users (username, hash, cash) VALUES( ?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
                
                if ($query === false)
                    apologize("Error adding user.");

                // Query last inserted user
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                
                if (count($rows) == 1)
                {
                    $id = $rows[0]["id"];
                    
                    // Set session id to registered user
                    $_SESSION["id"] = $id;
                    redirect("/");
                }
            }
        }                
    }

?>
