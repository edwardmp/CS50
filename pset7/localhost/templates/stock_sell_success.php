<div class="alert alert-success">
    Succesfully sold <?= $amount_sold ?> shares of <?= $name ?> stock!
</div>

<table class="table table-hover">
    <thead>
        <tr>
            <td>Stock symbol</td>
            <td>Company</td>
            <td>Current trading price</td> 
            <td>Amount of shares sold</td>
            <td>Value of shares sold</td>
            <td>Stock Exchange</td>
        </tr>
    </thead>   
    <tr>
        <td><?= $symbol ?></td>
        <td><?= $name ?></td>
        <td><?= number_format($price, 2) ?></td>
        <td><?= $amount_sold ?></td>
        <td><?= number_format($price * $amount_sold, 2) ?></td>
        <td><?= $stock_exchange ?></td>    
    </tr>
</table> 
