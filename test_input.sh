#! /bin/bash

echo "1) Two cameras file"
./miniRT scenes/parsing_tests/2cams.rt
echo "2) Two ambiances file"
./miniRT scenes/parsing_tests/2ambs.rt
echo "3) Two lights file"
./miniRT scenes/parsing_tests/2lights.rt
echo "4) Zero camera file"
./miniRT scenes/parsing_tests/0cam.rt
echo "5) Zero ambiance file"
./miniRT scenes/parsing_tests/0amb.rt
echo "6) Zero light file"
./miniRT scenes/parsing_tests/0light.rt
