#!/bin/bash

echo "-----------------------------------------"
echo "Automated Build and Program system for embedded devices"
echo "-----------------------------------------"
echo

# Reference: http://processors.wiki.ti.com/index.php/Projects_-_Command_Line_Build/Create

if [ $# -lt "2" ]
then
  echo "ERROR! Missing path argument!"
  echo "Usage: "$0" project_path"
  exit 1
fi 

PROJECT_NAME=$1
PROJECT_PATH=$2
COMPILER_PATH='/code/sdk/ti/ccsv6/eclipse/eclipse'
PROGRAMMER_PATH='/code/sdk/ti/MSPFlasher_1.3.9'

# hex file generation must be enabled in CCSV6 GUI
# http://processors.wiki.ti.com/index.php/Generating_and_Loading_MSP430_Binary_Files
OUTPUT_BIN_PATH=$PROJECT_PATH'/Debug/'$PROJECT_NAME'.txt'

# - Clean all project:
CMD_CLEAN=$COMPILER_PATH' -noSplash -data '$PROJECT_PATH' -application com.ti.ccstudio.apps.projectBuild -ccs.workspace -ccs.clean'

# - Build all projects (active configuration):
CMD_BUILD=$COMPILER_PATH' -noSplash -data '$PROJECT_PATH' -application com.ti.ccstudio.apps.projectBuild -ccs.workspace'

export LD_LIBRARY_PATH=$PROGRAMMER_PATH    #required before programming
CMD_PROGRAM=$PROGRAMMER_PATH'/MSP430Flasher -z [RESET] -v -w '$OUTPUT_BIN_PATH

echo
echo "CLEANING PROJECT"
echo $CMD_CLEAN
$CMD_CLEAN
echo "CLEANING COMPLETED"

echo
echo "BUILDING PROJECT"
echo $CMD_BUILD
$CMD_BUILD
echo "BUILDING COMPLETED"

echo
echo "PROGRAMMING PROJECT"

echo $CMD_PROGRAM
$CMD_PROGRAM
echo "PROGRAMMING COMPLETED"

