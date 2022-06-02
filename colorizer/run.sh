#!/bin/bash

##### utility functions #####
fatal_error () {
    echo -e "\n\n(!) ERROR\n\n$1\n\nExiting..." >&2
    exit 1
}


##### get path info #####

root_path=$(dirname $(realpath $0)) # absolute path to this script

default_version="1.18.2"

read -e -p "Enter absolute path to .minecraft folder: " mc
mc="${mc/#\~/$HOME}"

if [[ ! -d $mc ]]; then
    fatal_error "Could not find folder at path $mc"
fi

read -e -p "Enter version to extract textures from (hit ENTER to use $default_version): " use_version
 
echo $use_version
if [[ -z $use_version ]]; then
    use_version=$default_version
fi

jar_path="$mc/versions/$use_version/$use_version.jar"

if [[ ! -f $jar_path ]]; then
    fatal_error "Could not find $jar_path, please make sure that $use_version is valid and downloaded"
fi


##### extract textures #####

texture_folder="$root_path/all-${default_version}-textures"
echo -e "\nExtracting texture files..."

mkdir -p $texture_folder && 
unzip -o -q -j $jar_path "assets/minecraft/textures/block/*" -d "$texture_folder" && 
echo -e "DONE" && 

sleep 0.5s

##### copy textures to be used #####

echo -e "\n(1) use default blocklist (blocklist-1.18.2.txt)\n(2) custom path"

default_blocklist_path="$root_path/blocklist-${default_version}.txt"
used_texture_path="$root_path/../textures-$use_version"

while [ "$opts" != "1" ] && [ "$opts" != "2" ]; do

    read -p "[1/2]: " opts

    if [[ "$opts" == "1" ]]; then 
        eval "$root_path/scripts/cp-textures.sh" "$texture_folder" "$default_blocklist_path" "$used_texture_path"
    elif [[ "$opts" == "2" ]];  then
        read -e -p "path to blocklist: " blocklist
        if [[ ! -f $blocklist ]]; then
            fatal_error "$blocklist is not a valid file"
        fi
        eval "$root_path/scripts/cp-textures.sh" "$texture_folder" "$blocklist" "$used_texture_path"
    else
        echo "invalid option"
    fi
done

echo -e "\nDONE\n"

##### run colorizer #####

cd $root_path
make clean > /dev/null

echo -e "building...\n"
make build > /dev/null
$root_path/bin/main $used_texture_path $root_path/../colors.json 500 # create colors.json up 1 from root, algorithm repeats 500 times