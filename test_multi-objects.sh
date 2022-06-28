#! /bin/bash

echo "Multiple objects in the scene"
./miniRT scenes/multi-objects/objects.rt &
./miniRT scenes/multi-objects/objects2.rt &
./miniRT scenes/multi-objects/sphere_cyl.rt