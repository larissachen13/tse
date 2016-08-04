#!/bin/bash
# script to handle comparing two files see TESTING.md for more details'
sort1="$1.sorted"
sort2="$2.sorted"
sort $1 > $sort1
sort $2 > $sort2
diff $sort1 $sort2
