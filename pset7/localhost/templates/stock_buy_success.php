<div class="alert alert-success">
    Succesfully bought <?= $amount_purchased ?> shares of <?= $name ?> stock!
</div>

<table class="table table-hover">
    <thead>
        <tr>
            <td>Stock symbol</td>
            <td>Company</td>
            <td>Current trading price</td> 
            <td>Amount of shares purchased</td>
            <td>Current value of shares purchased</td>
            <td>Stock Exchange</td>
        </tr>
    </thead>   
    <tr>
        <td><?= $symbol ?></td>
        <td><?= $name ?></td>
        <td><?= number_format($price, 2) ?></td>
        <td><?= $amount_purchased ?></td>
        <td><?= number_format($price * $amount_purchased, 2) ?></td>
        <td><?= $stock_exchange ?></td>    
    </tr>
</table>   
