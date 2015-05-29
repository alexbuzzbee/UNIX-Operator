#/bin/bash

./uop < testscript.txt > output.txt

if cmp --silent expected.txt output.txt; then
  exit 0
else
  exit 1
fi
