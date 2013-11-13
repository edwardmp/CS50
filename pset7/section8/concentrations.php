<?php

/****************************************************************************
 * concentrations.php
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Loops through words in file and creates selectbox for every input line.
 ***************************************************************************/

$file = "concentrations.txt";

if (isset($file))
{
    if (file_exists($file))
    {
        if ($lineArray = array_unique(file($file, FILE_SKIP_EMPTY_LINES | FILE_IGNORE_NEW_LINES)))
        {
            print('<select name="concentration">' . "\n");
            sort($lineArray);
            foreach ($lineArray as $key => $line)
                print("\t" . '<option value="' . ($key+1) .'">' . $line . "</option>\n");

            print('</select>' . "\n");
        }
    }
    else
        printf("File %s does not exist. Aborting.\n", $file);
}
?>
