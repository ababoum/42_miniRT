#! /bin/bash

echo "1) Inexistant file"
./miniRT lala.rt
echo "2) Forbidden file"
./miniRT scenes/tests/ko_forbidden.rt
echo "3) Two cameras file"
./miniRT scenes/tests/2cams.rt
echo "4) Two ambiances file"
./miniRT scenes/tests/2ambs.rt
echo "5) Zero camera file"
./miniRT scenes/tests/0cam.rt
echo "6) Zero ambiance file"
./miniRT scenes/tests/0amb.rt
echo "7) Zero light file"
./miniRT scenes/tests/0light.rt


