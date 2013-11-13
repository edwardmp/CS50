<?php

/****************************************************************************
 * unique.php
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Prints all unique strings in a given file.
 ***************************************************************************/

if (isset($argv[1]))
{
    if(file_exists($argv[1]))
    {
        if($lineArray = array_unique(file($argv[1], FILE_SKIP_EMPTY_LINES)))
        {
            sort($lineArray);
            foreach ($lineArray as $line)
                print($line);
        }
    }
    else
        printf("File %s does not exist. Aborting.\n", $argv[1]);
}

?>
