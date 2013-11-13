/***********************************************************************
 * scripts.js
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Problem Set 7
 *
 * Various javascript functions regarding AJAX.
 **********************************************************************/

jQuery( document ).ready(function( $ ) { 
    
    // update navbar cash balance
    function update_balance() {
        // get the current info
        $.getJSON("/current_balance_ajax.php")
        .done(function(json) {
            var cash = parseFloat(json.cash);
            $("#cash_balance_nav").html(cash.toFixed(2));
        })
        .fail(function( jqxhr, textStatus, error ) {
            var err = textStatus + ", " + error;
            console.log("Request Failed: " + err);
        });  
    };
    
    // run every 10 seconds
    setInterval(function(){update_balance();}, 10000);
    
    // loads current stock information asynchronously in the table
    $('#portfolio > tbody  > tr').each(function() {
    
        var symbol = $(this).find(".symbol").html();  
        var current_trading_price = $(this).find(".current_trading_price");
        var current_worth = $(this).find(".current_worth");
        var shares_amount = $(this).find(".shares_amount").html();
        var current_roi = $(this).find(".current_roi");
        var original_price = $(this).find(".original_price").html();        
        
        // get the current info
        $.getJSON("/current_stockinfo_ajax.php", { symbol : symbol } )
          .done(function(json) {
          
            // cast price to float
            var price = parseFloat(json.price);
            // fadeOut spinner and show price
            current_trading_price.fadeOut( "fast", function() {
                current_trading_price.html(price.toFixed(2));
                current_trading_price.show();   
            });
            
            // calculate new worth
            var worth = json.price * shares_amount;  
            // fadeOut spinner and show worth          
            current_worth.fadeOut( "fast", function() {
                current_worth.html(worth.toFixed(2));
                current_worth.show();  
            });           
            
            var roi = (json.price - original_price) / original_price * 100;
            current_roi.fadeOut( "fast", function() {
                if (roi >= 0)
                    current_roi.html("<span class='positive_roi'>" + roi.toFixed(2) + "%" + "</span");
                else
                    current_roi.html("<span class='negative_roi'>" + roi.toFixed(2) + "%" + "</span");
                current_roi.show();
            });
          })
          .fail(function( jqxhr, textStatus, error ) {
            var err = textStatus + ", " + error;
            console.log("Request Failed: " + err);
        });       
    });
     
    // hide placeholder and spinner initially
    $("#spinner").hide();
           
    // Load stock quote content with AJAX
    $("#quote_form").submit(function(event) {
               
        // show spinner
        $("#spinner").show();
       
        // Stop form from submitting normally
        event.preventDefault();
        // Get some values from elements on the page:
        var $form = $(this),
            symbol = $form.find( "input[name='symbol']" ).val();              
        
        $.post("/quote.php", {symbol : symbol}, function(result){            
            $("#spinner").hide();
            
            $("#quote_placeholder").html(result).fadeIn();
        }, "html");

    });
    
     // Load stock quote content with AJAX
    $("#buy_form").submit(function(event) {
               
        // show spinner
        $("#spinner").show();
       
        // Stop form from submitting normally
        event.preventDefault();
        // Get some values from elements on the page:
        var $form = $(this),
            symbol = $form.find( "input[name='symbol']" ).val(),
            amount_purchased = $form.find( "input[name='amount_purchased']" ).val();              
        
        $.post("/buy.php", {symbol : symbol, amount_purchased: amount_purchased}, function(result){            
            $("#spinner").hide();
            
            $("#buy_placeholder").html(result).fadeIn();
        }, "html");

    });
    
    $("#sell_form").submit(function(event) {  
        // show spinner
        $("#spinner").show();
       
        // stop form from submitting normally
        event.preventDefault();
        // get some values from elements on the page:
        var $form = $(this),
            symbol = $form.find("input[name='symbol']").val(),
            amount_sold = $form.find("input[name='amount_sold']").val();

        // if id is empty, get the selectbox value instead
        var id = $("#id").val();    
        if (id == '' && $("#id option:selected").val() == 0) 
        {  
            id = $("#id option:selected").val(); 
        }                         

        $.post("/sell.php", {symbol : symbol, amount_sold: amount_sold, id : id}, function(result){            
            $("#spinner").hide(); // hide spinner
            
            // remove original form
            $("#sell_form").html(result).fadeIn();
            
            ///$("#sell_placeholder").html(result).fadeIn();
        }, "html");

    });
    
    // Load password change content with AJAX
    $("#change_password_form").submit(function(event) {
               
        // show spinner
        $("#spinner").show();
       
        // stop form from submitting normally
        event.preventDefault();
        // get some values from elements on the page:
        var $form = $(this),
            password = $form.find( "input[name='password']" ).val(),
            password_confirm = $form.find( "input[name='password_confirm']" ).val();              
        
        $.post("/change_password.php", {password : password, password_confirm: password_confirm}, function(result){            
            $("#spinner").hide();
            
            $("#password_placeholder").html(result).fadeIn();
        }, "html");

    });
    
    // Loads funds change content with AJAX
    $("#change_funds_form").submit(function(event) {
               
        // show spinner
        $("#spinner").show();
       
        // stop form from submitting normally
        event.preventDefault();
        // get some values from elements on the page:
        var $form = $(this),
            funds_amount = $form.find( "input[name='funds_amount']" ).val();

        $.post("/deposit_funds.php", {funds_amount : funds_amount}, function(result){            
            $("#spinner").hide();
            
            $("#funds_placeholder").html(result).fadeIn();
        }, "html");

    });
               
    // display suggestions when entering stock symbol
    // source: http://jsfiddle.net/justinobney/S8yyD/
    $("#symbol").autocomplete({
        source: function (request, response) {
            
            // faking the presence of the YAHOO library bc the callback will only work with
            // "callback=YAHOO.Finance.SymbolSuggest.ssCallback"
            var YAHOO = window.YAHOO = {Finance: {SymbolSuggest: {}}};
            
            YAHOO.Finance.SymbolSuggest.ssCallback = function (data) {
                var mapped = $.map(data.ResultSet.Result, function (e, i) {
                    return {
                        label: e.symbol + ' (' + e.name + ')',
                        value: e.symbol
                    };
                });
                response(mapped);
            };
            
            var url = [
                "http://d.yimg.com/autoc.finance.yahoo.com/autoc?",
                "query=" + request.term,
                "&callback=YAHOO.Finance.SymbolSuggest.ssCallback"];

            $.getScript(url.join(""));
        },
        minLength: 2
    }); 
       
});
