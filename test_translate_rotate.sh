#! /bin/bash

echo "Translate and rotate"
./miniRT scenes/translation_rotation/cylinder_before.rt &
./miniRT scenes/translation_rotation/cylinder_after.rt &
./miniRT scenes/translation_rotation/sphere_before.rt &
./miniRT scenes/translation_rotation/sphere_after.rt