<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" style="width:195px" name="symbol" autofocus>                
                <?php
                    foreach ($stocks as $symbol)
                        echo("<option value='$symbol'>$symbol</option>\n");
                ?>
            </select>
            <br>
            <br>
            <div class="form-group">
                <input class="form-control" type="text" name="shares" placeholder="Shares"/>
            </div>
            <div class="form-group">
                <button type="submit" class="btn btn-default">Sell</button>
            </div> 
        </div>         
    </fieldset>
</form>
