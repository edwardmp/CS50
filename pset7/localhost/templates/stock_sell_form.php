<div id="sell_placeholder">
    <p id="spinner">
        <img src="/img/spinner.gif" alt="Loading.."/>
    </p>
</div>

<form id="sell_form">
    <div class="row">
        <div class="col-md-6 col-md-offset-3">
            <div class="form-group">
                <input class="form-control" autofocus name="symbol" id="symbol" placeholder="Stock ticker symbol" type="text" value="<?= (isset($symbol)) ? $symbol : "" ?>"/>
            </div>
            <div class="form-group">
                <input class="form-control" name="amount_sold" id="amount_sold" placeholder="Amount of stock to be sold" type="text" value="<?= (isset($shares_amount)) ? $shares_amount : "" ?>"/>
            </div>        
            <div class="form-group">
                <input type="submit" name="submit" id="sell_submit" class="btn btn-primary btn-lg btn-block" value="Sell stock" />
            </div>
            <input type="hidden" name="id" id="id" value="<?= (isset($id)) ? $id : NULL ?>"/>
        </div>
    </div>
</form>
