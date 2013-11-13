<div class="row">
    <div class="col-md-4 col-md-offset-4">  
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

<form class="form-signin" action="register.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="username" placeholder="Username" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="Password" type="password"/>
        </div>
         <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Password confirmation" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-primary btn-lg btn-block">Register</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="login.php">login</a>
</div>
