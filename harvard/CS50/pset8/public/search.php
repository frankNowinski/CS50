<?php

    require(__DIR__ . "/../includes/config.php");
    
    // Get parameters, omit whitespace 
    $params = array_map('trim', explode(",", urldecode($_GET["geo"])));
    
    // Remove "US param, as all addresses are in the US
    if (($index = array_search("US", $params)) !== false)
    {
        unset($params[$index]);
    }
    
    // Build SQL statement
    $sql = "SELECT * FROM places WHERE ";
    for ($i = 0, $count = count($params); $i < $count; $i++)
    {
        // Assume it's a postal code if it is numeric
        if (is_numeric($params[$i]))
        {
            $sql .= 'postal_code LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%"';
        }
        // Search by place name, City or State
        else
        {
            $sql .= '(place_name LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%" OR ' .
            (strlen($params[$i]) <= 2 ? 'admin_code1 LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%" OR ' : "") .
            'admin_name1 LIKE "' . htmlspecialchars($params[$i], ENT_QUOTES) . '%")';
        }
        
        if ($i < ($count - 1)) 
            $sql .= " AND ";
    }
            
    // numerically indexed array of places
    $places = query($sql);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
