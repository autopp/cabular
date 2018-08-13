#!/bin/bash

set -eu

errors=0
for exefile in $* ; do
  echo -n "$exefile: "
  status=0
  stdout=$(./$exefile) || status=$?
  if [[ "$status" -eq 0 ]]; then
    echo "OK"
  else
    errors=$((errors+1))
    echo "NG"
  fi
done

if [[ "$errors" -eq 0 ]]; then
  echo all examples finished
else
  echo "$errors example(s) are failed"
  exit 1
fi
