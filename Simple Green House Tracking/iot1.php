<?php
echo
"<html>
<head>
<title>
Soil IOT
</title>
<style>
h1 {
    text-align: center;
    text-transform: uppercase;
    color: #4CAF50;
}
h2 {
    color: deepblue;
	text-shadow: 1px 0.5px red;
    text-align: center;
}
body {
    color: #4CAF50;
    background-image: url("bhaiya.jpg");
    background-color: orange;
	background-size:     contain;                     
    background-repeat:   repeat;
    background-position: center center;   
}
div {
    font-size: 120%;
    color: DeepBlue;
    text-shadow: 1px 0px gold;
    margin-left: 280px;
	margin-right: 280px;
    border: 0px solid black;
	padding-top: 10px;
    padding-right: 18px;
    padding-bottom: 10px;
    padding-left: 18px;
	background: hsla(0, 100%, 100%, 0.80);
}
</style>
</head>
<body>";
$myfile = fopen("3.txt", "r") or die("Unable to open
file!");
$temp = fread($myfile,filesize("3.txt"));
$arr=explode("\n", $temp); foreach ( $arr as $item ) {
 echo "Moisture: ".$item;
}
fclose($myfile);
 $url1=$_SERVER['REQUEST_URI'];
    header("Refresh: 2; URL=$url1");
echo "</body>
</html>";
?>