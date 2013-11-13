<form id="sell_form">
    <div class="row">
        <div class="col-md-6 col-md-offset-3">
           <div class="form-group">
                <input class="form-control" type="text" value="<?= $stocks[0]["symbol"] ?> (<?= $stocks[0]["company"] ?>)" disabled/>
                <input class="form-control" name="symbol" id="symbol" type="hidden" value="<?= $stocks[0]["symbol"] ?>"/>
            </div>
            <div class="form-group">
               <select class="form-control" autofocus name="id" id="id">
                <option value="0">Select out of which owned stock you want to sell</option>
                <? foreach($stocks as $stock): ?>
                <option value="<?= $stock["id"] ?>"><?= $stock["shares_amount"] ?> shares, bought for <?= number_format($stock["share_price"], 2) ?> on <?= date("l d-m-Y", strtotime($stock["transaction_timestamp"])) ?> at <?= date("H:i:s", strtotime($stock["transaction_timestamp"])) ?></option>
                <? endforeach ?>
               </select>
            </div>
            <div class="form-group">
                <input class="form-control" name="amount_sold" id="amount_sold" placeholder="Amount of stock to be sold" type="text" value="<?= (isset($shares_amount)) ? $shares_amount : "" ?>"/>
            </div>        
            <div class="form-group">
                <input type="submit" name="submit" id="sell_submit" class="btn btn-primary btn-lg btn-block" value="Sell stock" />
            </div>
        </div>
    </div>
</form>
