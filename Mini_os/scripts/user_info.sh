#!/bin/bash

echo "-------------------------"
echo "User Information"
echo "Username: $(whoami)"
echo "Home Directory: $HOME"
echo "Shell: $SHELL"
echo "Groups: $(groups)"
echo "Logged In Users: $(who)"
echo "-------------------------"

sleep 5