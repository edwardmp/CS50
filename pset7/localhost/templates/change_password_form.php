<div class="row">
    <div class="col-md-6 col-md-offset-3">  
        <div class="panel panel-info">
            <div class="panel-heading">
                <h3 class="panel-title">Password requirements</h3>
            </div>
            <div class="panel-body">
                The new password may contain letters and numbers but must contain at least 1 number and 1 letter. Other than letters and numbers, the following characters are allowed &amp;@#$%. Password must be 6-12 characters in length.
            </div>
        </div>
    </div>
</div>

<div id="password_placeholder">
    <p id="spinner">
        <img src="/img/spinner.gif" alt="Loading.." />
    </p>
</div>

<form id="change_password_form">
      <div class="row">
        <div class="col-md-6 col-md-offset-3">          
            <div class="form-group">
                <input class="form-control" autofocus name="password" placeholder="Enter new password" type="password"/>
            </div>
            <div class="form-group">
                <input class="form-control" name="password_confirm" placeholder="Confirm new password" type="password"/>
            </div>        
            <div class="form-group">
                <input type="submit" name="submit" class="btn btn-warning btn-lg btn-block" value="Change password"/>
            </div>
        </div>      
    </div>
</form>
