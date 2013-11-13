<div id="quote_content">
    <table class="table table-hover">
        <thead>
            <tr>
                <td>Stock symbol</td>
                <td>Company</td>
                <td>Current trading price</td> 
                <td>Change in percent</td>
                <td>Stock Exchange</td>
            </tr>
        </thead>   
        <tr>
            <td><?= $symbol ?></td>
            <td><?= $name ?></td>
            <td><?= number_format($price, 2) ?></td>
            <td><span class="<?= ($change_percent >= 0.00) ? "positive_roi" : "negative_roi" ?>"><?= $change_percent ?></td>
            <td><?= $stock_exchange ?></td>    
        </tr>
    </table>
</div>
