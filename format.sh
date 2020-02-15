#!C:/Windows/system32/cmd.exe"

for i in $(find ./285R-TowerTakeover/src/ -iname "*.cpp"); do clang-format -i -style=google $i || true
done

for i in $(find ./285R-TowerTakeover/include/devices/ -iname "*.hpp"); do clang-format -i -style=google $i || true
done

for i in $(find ./285R-TowerTakeover/include/comp/ -iname "*.hpp"); do clang-format -i -style=google $i || true
done