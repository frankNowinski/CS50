<?php 
    
    // configuration
    require("../includes/config.php");
    
    // If user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
        render("pass_form.php", ["title" => "Register"]);

    // Else if user reached page via POST 
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Reject unpopulated fields
        if (empty($_POST["username"]) || empty($_POST["old_password"]) || empty($_POST["new_password"]) || empty($_POST["confirmation"]))
            apologize("Please fill in all the required fields.");
            
        // Query users information
        $rows = query("SELECT * FROM users WHERE id = ? AND username = ?", $_SESSION["id"], $_POST["username"]);
        
        // Confirm if user exist in database
        if(count($rows) != 1)
            apologize("A user by that name does not exist.");
        else
            $row = $rows[0];
  
        // Check if the username and pw match that of which are in the database
        if ($row["username"] == $_POST["username"] && crypt($_POST["old_password"], $row["hash"]) == $row["hash"])
        {
            if ($_POST["new_password"] == $_POST["confirmation"])
            {    
                // Update new password
                $update = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $_SESSION["id"]);
                          
                if ($update === false)
                    apologize("Error changing password.");

                // Redirect to homepage upon completion
                $id = $rows[0]["id"];    
                $_SESSION["id"] = $id;
                redirect("index.php");   
            }
            else
                apologize("Your new password and confirmation password do not match.");
        } 
        else
            apologize("The username and password do not match.");                   
    } 
?>
