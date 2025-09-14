#!/bin/bash

echo "Creating new project structure..."
mkdir -p includes maps srcs/init srcs/parsing srcs/rendering srcs/events srcs/cleanup
echo "Directory structure created:"
ls -F
echo "---------------------------------"
echo "Project setup is complete! You can now update your Makefile."