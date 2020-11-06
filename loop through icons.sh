#!/bin/bash
# Download screen capture  prosv5 v5 capture USER000x.png

for i in {604..999..1}
  do 
    if [ $i -gt 99 ]
    then
        echo "USER${i}x.bmp"
        prosv5 upload --icon  USER${i}x.bmp
        read -p "Press enter to continue"
    elif [ $i -gt 9 ]
    then
        echo "USER0${i}x.bmp"
        prosv5 upload --icon  USER0${i}x.bmp
        read -p "Press enter to continue"
    else 
        echo "USER00${i}x.bmp"
        prosv5 upload --icon  USER00${i}x.bmp
        read -p "Press enter to continue"
    fi
 done
