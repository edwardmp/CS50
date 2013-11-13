<div>
    <div class="alert alert-info">
        <?= ucfirst($_SESSION["username"]) ?>, your cash balance is currently <strong><?= number_format($stocks[0]["cash"], 2) ?></strong>.
    </div>
    <table id="portfolio" class="table table-hover">
        <thead>
            <tr>
                <td>Stock symbol</td>
                <td>Company</td>
                <td>Current trading price</td> 
                <td>Original trading price</td>
                <td>Number of shares</td>
                <td>Original worth of shares</td>
                <td>Current worth of shares</td>
                <td>Return on investment</td>
                <td>Stock Exchange</td>
                <td>Sell stock</td>
            </tr>
        </thead>
        <tbody>
        <?php foreach ($stocks as $stock): ?>   
            <tr>
                <td class="symbol"><?= $stock["symbol"] ?></td>
                <td><?= $stock["company"] ?></td>
                <td class="current_trading_price"><img  class="spinner" alt="Loading.." src="/img/spinner.gif" /></td>
                <td class="original_price"><?= number_format($stock["share_price"], 2) ?></td>
                <td class="shares_amount"><?= $stock["shares_amount"] ?></td>
                <td><?= number_format($stock["shares_amount"] * $stock["share_price"], 2) ?></td>
                <td class="current_worth"><img  class="spinner" alt="Loading.." src="/img/spinner.gif" /></td>
                <td class="current_roi"><img  class="spinner" alt="Loading.." src="/img/spinner.gif" /></td>
                <td><?= $stock["stock_exchange"] ?></td>  
                <td><a href="sell.php?id=<?= $stock["id"] ?>" class="btn btn-default btn-sm btn-block"><span class="glyphicon glyphicon-shopping-cart"></span> Sell</a></td>
            </tr>
       <?php endforeach; ?>
       </tbody>           
    </table>   
</div>
