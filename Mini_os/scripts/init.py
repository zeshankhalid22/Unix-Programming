import os
import time
import sys
from pyfiglet import Figlet
from termcolor import colored

# Function to hide cursor
def hide_cursor():
    if os.name == 'nt':
        os.system('cls')
        os.system('echo off')
    else:
        sys.stdout.write("\033[?25l")
        sys.stdout.flush()

# Function to show cursor
def show_cursor():
    if os.name == 'nt':
        os.system('echo on')
    else:
        sys.stdout.write("\033[?25h")
        sys.stdout.flush()

# Function for printing animated text
def print_animated_text(text, color, delay=0.05):
    for char in text:
        print(colored(char, color), end='', flush=True)
        time.sleep(delay)
    print()

# Initialize Figlet with fonts
f_large = Figlet(font='slant')
f_medium = Figlet(font='digital')

# Hide cursor
hide_cursor()

# Clear the terminal screen
os.system('cls' if os.name == 'nt' else 'clear')

# Generate Figlet text for OS name in large font
os_name = f_large.renderText('WELCOME TO MINI OPERATING SYSTEM')

# Animation for OS name
print_animated_text(os_name, 'red', 0.005)

# Wait for a moment
time.sleep(10)

# Clear the terminal screen
os.system('cls' if os.name == 'nt' else 'clear')

# Print "Developed By" section with animation
developers = "Developed By:"
print_animated_text(f_large.renderText(developers), 'yellow', 0.01)

# Animation for developers' names
developers_names = [
    "ZEESHAN KHALID",
    "ANEEB Javeid",
    "ZUBAIR ALI"
]
for name in developers_names:
    print_animated_text(f_medium.renderText(name), 'green', 0.01)

# Wait for a moment
time.sleep(10)

# Clear the terminal screen
os.system('cls' if os.name == 'nt' else 'clear')

# Print "Supervised By" section with animation
supervisor = "UNDER THE SUPERVISION OF:"
print_animated_text(f_large.renderText(supervisor), 'blue', 0.005)
supervisorN = "PROFESSOR MAHZAIB YOUNUS"
print_animated_text(f_large.renderText(supervisorN), 'yellow', 0.005)

# Wait for a moment
time.sleep(5)

# Show cursor
show_cursor()