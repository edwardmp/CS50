<?php

$var = 7;
printf("Var is a %s\n", gettype($var));

$var = "cs50 rocks!";
printf("Var is a %s\n", gettype($var));

$var = true;
printf("Var is a %s\n", gettype($var));

$var = 3.50;
printf("Var is a %s\n", gettype($var));

$var = ["a" => 1, "b" => 2, "c" => 3];
printf("Var is a %s\n", gettype($var));

$var = fopen("dynamic.php", "r");
printf("Var is a %s\n", gettype($var));

$var = NULL;
printf("Var is a %s\n", gettype($var));

printf(90 + "9 bottles\n");
printf(10 / 7);
printf(7 + true);
?>
