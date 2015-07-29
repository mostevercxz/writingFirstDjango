#!/bin/bash
# Usage : . ./grep.sh keyword
# desc  : grep keyword at each file in the repository
grep -r $1 ../ -nH
