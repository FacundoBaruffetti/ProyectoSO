#!/bin/bash

gcc change_permissions.c -o change_permissions
gcc create_directory.c -o create_directory
gcc create_file.c -o create_file
gcc list_directory.c -o list_directory
gcc remove_directory.c -o remove_directory
gcc show_file.c -o show_file
gcc show_help.c -o show_help
gcc MiniShell.c -o MiniShell

./MiniShell
