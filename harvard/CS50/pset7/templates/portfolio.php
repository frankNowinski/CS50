<table class="table table-striped">
    <thead>
        <tr>
            <th class="text-center">Name </th>
            <th class="text-center">Symbol </th>
            <th class="text-center">Shares </th>
            <th class="text-center">Price </th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($positions as $position): ?>
        
            <tr>
                <td><?= $position["name"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
            </tr>
            
        <?php endforeach ?>      
        <tr>
            <td colspan="3"><strong>CASH</strong></td>
            <td><strong>$<?= number_format($users[0]["cash"], 2) ?></strong></td>
        </tr>
    </tbody>
</table>
        



