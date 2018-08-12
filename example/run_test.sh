#!/bin/bash

set -eu

for exefile in $* ; do
  echo run $exefile
  ./$exefile
done
