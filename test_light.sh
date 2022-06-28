#! /bin/bash

echo "Light/Shade configurations"
./miniRT scenes/light/sphere_left.rt &
./miniRT scenes/light/sphere_right.rt &
./miniRT scenes/light/sphere_right_shifted.rt &
./miniRT scenes/light/shade1.rt &
./miniRT scenes/light/shade2.rt