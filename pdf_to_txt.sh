#!/bin/bash

# Modules
if ! command -v tqdm &> /dev/null
then
    pip install tqdm
fi

if ! command -v pdfinfo &> /dev/null
then
    sudo apt-get install poppler-utils
fi

# Colors
Red='\033[0;31m'
White='\033[0;37m'
Green='\033[0;32m'
Line_below_text='\033[4m'
Line_not_below_text='\033[0m'

# Import File PDF
if [ $# -eq 0 ]
then
    echo -e "${Red}Error!:${Line_below_text} Invalid arguments.${Line_not_below_text}\nUsage: ./pdf_to_txt.sh 'Your file pdf'"
    exit 1
fi

if [[ ! $1 == *.pdf ]]
then
    echo -e "${Red}Error!:${Line_below_text} Invalid file type.${Line_not_below_text}"
    exit 1
fi

if [ ! -f "$1" ]
then
    echo -e "${Red}Error!:${Line_below_text} File not found.${Line_not_below_text}"
    exit 1
fi

# Extract the file name for file.txt
if [[ "$1" == */* ]]
then
    save_as=$(basename "${1%.*}.txt")
else
    save_as=$(basename "${1%.*}.txt")
fi

# Convert PDF to file.txt
if ! command -v pdftotext &> /dev/null
then
    echo -e "${Red}Error!:${Line_below_text} pdftotext command not found.${Line_not_below_text}"
    exit 1
fi

num_all_pages=$(pdfinfo "$1" | grep -o "Pages: *[0-9]*" | grep -o "[0-9]*")

if [[ -z "$num_all_pages" ]]
then
    echo -e "${Red}Error!:${Line_below_text} Unable to determine number of pages.${Line_not_below_text}"
    exit 1
fi

trap ctrl_c INT

ctrl_c() {
    rm "$save_as"
    echo -e "\n${Red}Error!:${Line_below_text} Cancelled by user.${Line_not_below_text}"
    exit 1
}

pdftotext "$1" "$save_as"

if [ $? -eq 0 ]
then
    echo -e "${Green}Successfully converted PDF to text file.${Line_not_below_text}"
else
    echo -e "${Red}Error!:${Line_below_text} Unable to convert PDF to text file.${Line_not_below_text}"
fi
