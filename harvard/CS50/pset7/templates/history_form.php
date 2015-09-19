<table class="table table-striped"> 
    <thead>
        <tr>
            <th>Date</th>
            <th>Transaction Type</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($history as $record): ?>
        
        <tr class="text-left">
            <td><?= date('Y-m-d H:i:s', strtotime($record["time"])) ?></td>
            <td><?= $record["transaction"] ?></td>
            <td><?= $record["symbol"] ?></td>
            <td><?= $record["shares"] ?></td>
            <td><?= number_format($record["price"], 2) ?></td>
        </tr>
        <?php endforeach ?>
    </tbody>
</table>
