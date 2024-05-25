#include <iostream>
#include "include/shell.h"
#include "include/my_commands.h"

using namespace std;

void command_menu() {
    int choice;
    cout << "1. ls\n"
            "2. user info\n"
            "3. Special Pattern\n"
            "4. Run custom command\n"
            "5. Affect\n"
            "6. Hard ware info\n";

    cout << "\t > ";
    cin >> choice;

    // system command runs in kernel mode

    if (choice == 1) {
        run_ls();
    } else if (choice == 2) {
        system("alacritty -e bash -c '../scripts/user_info.sh; exec bash'");
    }
    else if (choice == 3) {
        system("alacritty -e bash -c '../scripts/special_pattern.sh; exec bash'");
    }
    else if (choice == 4) {
        string command;
        cout << "Enter your custom command $ ";
        cin.ignore();
        getline(cin, command);
        string fullCommand = "alacritty -e bash -c '" + command + "; exec bash'";
        system(fullCommand.c_str());
    }
    else if (choice==5) {
        system("alacritty -e bash -c '../scripts/affect.sh; exec bash'");
    }
    else if (choice==6) {
        system("alacritty -e bash -c '../scripts/hardware_info.sh; exec bash'");
    }
    else {
        cout << "Invalid choice\n";
    }
}