#!/bin/bash

set -eu

errors=0
for exefile in $* ; do
  echo -n "$exefile: "
  expected_stdout_file=${exefile/.out/.stdout}
  status=0
  stdout=$(./$exefile) || status=$?
  if [[ "$status" -ne 0 ]]; then
    errors=$((errors+1))
    echo "NG"
    echo "exit status is not zero"
  elif stdout_diff=$(diff $expected_stdout_file <(echo "$stdout")) ; then
    echo "OK"
  else
    echo "NG"
    echo "stdout is not expected contents"
    echo "$stdout_diff"
  fi
done

if [[ "$errors" -eq 0 ]]; then
  echo all examples finished
else
  echo "$errors example(s) are failed"
  exit 1
fi
