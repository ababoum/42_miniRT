#! /bin/bash

echo "Camera along axis"
./miniRT scenes/camera/scene_x.rt &
./miniRT scenes/camera/scene_y.rt &
./miniRT scenes/camera/scene_z.rt &
./miniRT scenes/camera/scene_rand.rt