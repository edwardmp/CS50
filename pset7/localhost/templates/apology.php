<div class="row">
    <div class="col-md-6 col-md-offset-3">  
        <div class="panel panel-warning">
            <div class="panel-heading">
                <h3 class="panel-title">Sorry!</h3>
            </div>
            <div class="panel-body">
                <?= htmlspecialchars($message) ?>
            </div>
        </div>
    </div>
</div>

<? 
if (!isset($_SESSION["id"])):
?>
    <a href="javascript:history.go(-1);">Back</a>
<? endif ?>
