#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// Generalized struct for resources
typedef struct {
    char name[20];
    int count;
} Resource;

// Function prototypes
void mainMenu();
void miningMenu();
void fishingMenu();
void activity(Resource *resource);


Resource copper = {"Copper", 0};
Resource coal = {"Coal", 0};
Resource cod = {"Ikan Kod", 0};
Resource cakalang = {"Ikan Cakalang", 0};
Resource tuna = {"Ikan Tuna", 0};

// Main function
int main() {
    int choice;
    int run = 1;

    while (run) {
        mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: miningMenu(); break;
            case 2: fishingMenu(); break;
            case 3: run = 0; break; // Exit
            default:
                printf("Invalid choice. Please try again.\n");
                Sleep(2000);
                system("cls");
        }
    }

    printf("Exiting the program. Thanks for playing!\n");
    return 0;
}

// Main menu display
void mainMenu() {
    system("cls");
    puts("========== Text-Based RPG ==========");
    puts("[1] Mining");
    puts("[2] Fishing");
    puts("[3] Exit");
    puts("====================================");
}

// Mining menu
void miningMenu() {
    int choice;

    system("cls");
    puts("Choose a mining option:");
    puts("[1] Copper");
    puts("[2] Coal");
    puts("[3] Exit to Main Menu");
    printf(">> ");
    scanf("%d", &choice); getchar();

    switch (choice) {
        case 1: activity(&copper); break;
        case 2: activity(&coal); break;
        case 3: return;
        default:
            printf("Invalid choice. Returning to the main menu...\n");
            Sleep(2000);
    }
}

// Fishing menu
void fishingMenu() {
    int choice;

    system("cls");
    puts("Choose a fishing option:");
    puts("[1] Ikan Kod");
    puts("[2] Ikan Cakalang");
    puts("[3] Ikan Tuna");
    puts("[4] Exit to Main Menu");
    printf(">> ");
    scanf("%d", &choice); getchar();

    switch (choice) {
        case 1: activity(&cod); break;
        case 2: activity(&cakalang); break;
        case 3: activity(&tuna); break;
        case 4: return;
        default:
            printf("Invalid choice. Returning to the main menu...\n");
            Sleep(2000);
    }
}

// General activity function
void activity(Resource *resource) {
    system("cls");
    
    while (1) {
        puts("Press Q to stop");
        puts("");
        Sleep(3000);
        
        system("cls");
        resource->count++;
        printf("You got 1 %s, Total: %d\n", resource->name, resource->count);
        
        // Check for quit condition
        if (kbhit()) { 
            int ch = getch(); 
            if (ch == 'q' || ch == 'Q') {
                break;  
            }
        }
    }
    
    printf("Mining stopped. Final count:\n");
    printf("%s: %d\n", resource->name, resource->count);
    printf("Press Enter to return to the menu...\n");
    getchar();
}