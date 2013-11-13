<div class="alert alert-info">
    Here is your transaction history, newest transactions on top.
</div>

<table class="table table-hover">
    <thead>
        <tr>
            <td>Transaction type</td>
            <td>Symbol</td>
            <td>Shares affected</td> 
            <td>Stock price</td>
            <td>Time of transaction</td>
        </tr>
    </thead>   
    <? foreach ($logs as $log): ?> 
    <tr>
        <td><?= ($log["transaction_type"] == "B") ? "Buy" : "Sell" ?></td>
        <td><?= $log["symbol"] ?></td>
        <td><?= $log["amount"] ?></td>
        <td><?= number_format($log["price"], 2) ?></td>
        <td><?= date("H:i:s d-m-Y", strtotime($log["datetime_stamp"])) ?></td> 
    </tr>
    <? endforeach ?>
</table>
