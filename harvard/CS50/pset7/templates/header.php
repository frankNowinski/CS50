<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.11.1.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>
        <div class="container">
            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
                
                <ul class="nav nav-pills" id="links">
                    <li class="link"><a href="index.php">Portfolio</a></li>
                    <li class="link"><a href="buy.php">Buy</a></li>
                    <li class="link"><a href="sell.php">Sell</a></li>
                    <li class="link"><a href="quote.php">Quote</a></li>
                    <li class="link"><a href="history.php">History</a></li>
                    <li class="link"><a href="logout.php">Log Out</a></li>
                </ul>
            </div>

            <div id="middle">
           
       
                
