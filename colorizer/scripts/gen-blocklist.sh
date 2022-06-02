#!/bin/bash

# generates list of MC assets with a 0|1 following the name
# eg. slime_block.png 0
# output file meant to be used by cp-textures.sh

# usage
# assets have to be unziped from the version folder
# gen-blocklist.sh /minecraft/assets/folder ./blocklist.txt

blocks_dir=$1
out_file=$2

block_files=$(ls ${blocks_dir})

str=""

for f in $block_files; do
    str+="${f} 0\n"
done

touch $out_file

echo -e $str > $out_file