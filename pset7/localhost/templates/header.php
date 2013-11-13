<!DOCTYPE html>

<html lang="en">

    <head>
    
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
        <link href="css/bootstrap.min.css" rel="stylesheet"/>
        <link href="css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="css/smoothness/jquery-ui-1.10.3.custom.min.css" rel="stylesheet">
        <link href="css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>Finance - <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>Finance</title>
        <?php endif ?>

        <script src="js/jquery-1.10.2.min.js"></script>
        <script src="js/jquery-ui-1.10.3.custom.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <script src="js/scripts.js"></script>
        
    </head>

    <body>

        <div class="container">

            <? if(isset($_SESSION["id"])): ?>   
                <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
                    <!-- Brand and toggle get grouped for better mobile display -->
                    <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                      <span class="sr-only">Toggle navigation</span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="/">Finance</a>
                    </div>

                    <!-- Collect the nav links, forms, and other content for toggling -->
                    <div class="collapse navbar-collapse navbar-ex1-collapse">
                    <ul class="nav navbar-nav">
                        <li<?= activeMenuElement("index.php")?>><a href="/">Portfolio</a></li>
                        <li<?= activeMenuElement("buy.php")?>><a href="buy.php">Buy stock</a></li>
                        <li<?= activeMenuElement("sell.php")?>><a href="sell.php">Sell stock</a></li>
                        <li<?= activeMenuElement("quote.php")?>><a href="quote.php">Lookup stock price</a></li>
                        <li<?= activeMenuElement("history.php")?>><a href="history.php">Transaction history</a></li>
                    </ul>
                    <ul class="nav navbar-nav navbar-right">                      
                        <li class="navbar-text"><span class="glyphicon glyphicon-user"></span> <?= ucfirst(substr($_SESSION["username"], 0, 15)); ?></li>
                        <li<?= activeMenuElement("deposit_funds.php")?>><a href="deposit_funds.php"><span class="glyphicon glyphicon-usd"></span><span id="cash_balance_nav"><?= $cash_balance ?></span></a></li>
                        <li class="dropdown">

                        <a href="#" class="dropdown-toggle" data-toggle="dropdown"><span class="glyphicon glyphicon-wrench"></span> Account <b class="caret"></b></a>
                        <ul class="dropdown-menu">
                            <li<?= activeMenuElement("change_password.php")?>><a href="change_password.php">Change password</a></li>
                            <li<?= activeMenuElement("logout.php")?>><a href="logout.php">Log out</a></li>
                        </ul>
                      </li>
                    </ul>
                    </div><!-- /.navbar-collapse -->
                </nav>          
            <? endif ?>
            
            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="img/logo.png"/></a>
            </div>

            <div id="middle">
            
