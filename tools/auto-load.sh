#!/bin/bash
echo
echo "=========================================================================================="
echo
echo "                    ___ _    ___  ___ ___ ___  _     ___   _ _____  "
echo "                   | __| |  / _ \| _ \_ _| _ \/_\   / __| /_\_   _| "
echo "                   | _|| |_| (_) |   /| ||  _/ _ \  \__ \/ _ \| |   "
echo "                   |_| |____\___/|_|_\___|_|/_/ \_\ |___/_/ \_\_|   "
echo "                                                                    "
echo
echo "                    Automated Load System for Floripasat Project"
echo
echo "=========================================================================================="
echo
echo "How to use: .../auto-load.sh projectName projectWorkspace/"
echo
echo "Sample usage: ./auto-load.sh mcu-msp430f6659-blink1 /code/workspace_v6_1_3/"
echo

# Reference: http://processors.wiki.ti.com/index.php/Projects_-_Command_Line_Build/Create
#            http://processors.wiki.ti.com/index.php/Debug_Server_Scripting/Step_By_Step

if [ $# -lt "2" ]           # Test to see if there are 2 arguments
then
  echo "ERROR! Missing path argument!"
  echo "Usage: "$0" project_path"
  exit 1
fi 

PROJECT_NAME=$1
WORKSPACE_PATH=$2
LOADTI_PATH='/code/sdk/ti/ccsv6/ccs_base/scripting/examples/loadti/'

# - Load project
CMD_LOAD=$LOADTI_PATH'loadti.sh -a -c '$WORKSPACE_PATH''$PROJECT_NAME'/targetConfigs/*.ccxml '$WORKSPACE_PATH''$PROJECT_NAME'/Debug/*.out'

echo
echo "------------------------------------ LOADING PROJECT -------------------------------------"
echo
echo $CMD_LOAD
echo
$CMD_LOAD
echo
echo "----------------------------------- LOADING COMPLETED ------------------------------------"
echo
echo "=========================================================================================="
echo
