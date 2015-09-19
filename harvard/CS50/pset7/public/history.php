<?php 

    require("../includes/config.php");
    
    // Query users cash
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]); 

    // Render history form 
    render("history_form.php", ["title" => "History", "history" => $rows]);
        
?> 
             
        
        
