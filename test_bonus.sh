#! /bin/bash

echo "Camera along axis"
./miniRT_bonus scenes/bonus/specular.rt &
./miniRT_bonus scenes/bonus/bump_map.rt &
./miniRT_bonus scenes/bonus/multispot.rt &
./miniRT_bonus scenes/bonus/chessboard1.rt &
./miniRT_bonus scenes/bonus/chessboard2.rt &
./miniRT_bonus scenes/bonus/cone.rt &
./miniRT_bonus scenes/bonus/mix_bonus.rt &
./miniRT_bonus scenes/bonus/subject_example.rt &
./miniRT_bonus scenes/bonus/subject_example2.rt &
