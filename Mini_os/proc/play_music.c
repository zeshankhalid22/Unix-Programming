#include <stdlib.h>
#include <stdio.h>

int main() {
    char* music_paths[] = {
        "../proc/Music/295-Sidhu-Moose-Wala.mp3",
        "../proc/Music/arcade.mp3",
        "../proc/Music/gulab.mp3",
        "../proc/Music/ek-villain.mp3"
    };

    printf("Select a song to play:\n");
    printf("1. 295\n");
    printf("2. Arcade\n");
    printf("3. Akhya Gulab\n");
    printf("4. Ek Villan\n");
    printf("5. Exit\n\t> ");

    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
        printf("Invalid choice\n");
        return 0;
    }

    char command[1024];
    snprintf(command, sizeof(command), "/usr/bin/vlc %s", music_paths[choice - 1]);
    system(command);
    return 0;
}