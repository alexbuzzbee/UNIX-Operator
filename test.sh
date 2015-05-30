#/bin/bash

echo "In directory:"
ls
echo "Running UOP..."
./uop < testscript.txt > output.txt

echo "Checking output..."
if cmp --silent expected.txt output.txt; then
  echo "Success!"
  exit 0
else
  echo "Failed!!!"
  exit 1
fi
