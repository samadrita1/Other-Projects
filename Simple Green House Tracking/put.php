<?php
$data1 = $_GET['name'];

$myfile = fopen("3.txt", "w+") or die("Unable to open file!");
fwrite($myfile, $data1);\

fclose($myfile);
echo "1";
?>