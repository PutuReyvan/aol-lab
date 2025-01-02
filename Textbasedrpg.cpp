#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// Generalized struct for resources
typedef struct {
    char name[20];
    int count;
} Resource;

typedef struct{
	int hp;
	int def;
	int atk;
	int xp;
	int level;
}Player;

typedef struct{
	char name[50];
	int hp;
	int def;
	int atk;
}Mob;

// Function prototypes

/*function buat bagian login -rey
*/
void loginMenu();
void registerUser();
int loginUser();

/*function buat stats etc -rey
*/
void gainXP(Player* player, int xpGain);
void levelUp(Player* player);
void showStats(Player *player);
void cheatCode(Player *player);

/*function buat battle -rey*/
int calcDamage(int atk, int def);
void battle(Player *player);
Mob getRandomMob();

void mainMenu();
void miningMenu(Player *player);
void fishingMenu(Player *player);
void woodMenu(Player *player);
void activity(Resource *resource, Player* player);

Resource copper = {"Copper", 0};
Resource coal = {"Coal", 0};
Resource cod = {"Ikan Kod", 0};
Resource cakalang = {"Ikan Cakalang", 0};
Resource tuna = {"Ikan Tuna", 0};
Resource cemara = {"Kayu Cemara", 0};
Resource jati = {"Kayu Jati", 0};
Resource oak = {"Kayu Oak", 0};

Mob mobs[] = {
    {"Goblin", 50, 15, 5},
    {"Orc", 80, 20, 10},
    {"Troll", 120, 25, 15},
    {"Slime", 30, 5, 4},
    {"Lizardman", 150, 35, 10},
    {"Lycan", 60, 15, 40}
};

int mobcount = sizeof(mobs)/sizeof(mobs[0]);

// Main function
int main() {
    int choice, login;
    int run = 1;
    int isAuth = 0;
	
	Player player= {100, 5, 2, 0, 1};
	
	while(!isAuth){
		loginMenu();
    	printf("Enter your choice: ");
    	scanf("%d", &login);
    	
    	switch(login){
    		case 1:
    			if(loginUser()){
    				isAuth = 1;
				}else{
					printf("Username or password doesnt match... Try again\n");
					Sleep(2000);
				}
    			break;
    		case 2:
    			registerUser();
    			break;
    		default:
    			printf("Invalid choice");
    			Sleep(2000);
    			system("cls");
		}
	}


    while (run) {
	    mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: miningMenu(&player); break;
            case 2: fishingMenu(&player); break;
            case 3: woodMenu(&player); break;
            case 4: showStats(&player); break; // Exit
            case 5: battle(&player); break; // Exit
            case 6: run = 0; break; // Exit
            case 666: cheatCode(&player); break;
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
    puts("[3] Wood Cutting");
    puts("[4] Stats");
    puts("[5] Battle");
    puts("[6] Exit");
    puts("====================================");
}

void loginMenu(){
	system("cls");
	puts("===============Text-based RPG=============");
	puts("[1]. Login");	
	puts("[2]. Register");
	puts("==========================================");	
}

void registerUser(){
	char usn[50], password[50];
	
	FILE *file = fopen("data.csv", "a");
	if(file == NULL){
		printf("Error unable to open file\n");
		Sleep(2000);
		return;
	}
	
	printf("Enter your username (Without space) : ");
	scanf("%s", &usn); getchar();
	
	printf("Enter your password : ");
	scanf("%s", &password); getchar();
	
	fprintf(file, "%s,%s\n", usn, password);
	fclose(file);
	
	printf("Successfull. You can login now\n");
	printf("Press enter to continue...\n");getchar();
	
}

int loginUser(){
	char usn[50], password[50];
	char fileUsn[50], filePassword[50];
	
	FILE *file = fopen("data.csv", "r");
	if(file == NULL){
		printf("Error unable to open file\n");
		Sleep(2000);
		return 0;
	}
	
	printf("Enter your username (Without space) : ");
	scanf("%s", &usn); getchar();
	
	printf("Enter your password : ");
	scanf("%s", &password); getchar();
	
	while(fscanf(file, "%49[^,],%49[^\n]\n", fileUsn, filePassword) == 2){
		if (strcmp(usn, fileUsn) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            printf("Login successful! Welcome back, %s.\n", usn);
            Sleep(2000);
            return 1; // Login successful
        }
	}
	
	fclose(file);
    return 0; // Login failed
}

int calcDamage(int atk, int def){
	int damage = atk - def/2;
	return damage >= 0 ? damage : 1;
}

Mob getRandomMob(){
	srand(time(NULL));
	return mobs[rand() % mobcount];
}

void battle(Player *player){
	Mob mob = getRandomMob();
	char choice;
	
	system("cls");
	printf("A wild %s appears! (HP: %d, ATK: %d, DEF: %d)\n", 
        mob.name, mob.hp, mob.atk, mob.def);
    printf("Do you wish to fight? (Y/N): ");
    scanf(" %c", &choice); getchar();

    if (choice == 'N' || choice == 'n') {
        printf("You chose to avoid the fight. Returning to main menu...\n");
        Sleep(2000);
        return;
    }
	
	while(player->hp > 0 && mob.hp > 0){
		int pDamage = calcDamage(player->atk, mob.def);
		mob.hp -= pDamage;
		printf("You hit the %s for %d damage! (%s HP: %d)\n", 
                mob.name, pDamage, mob.name, mob.hp > 0 ? mob.hp : 0);
                
        if(mob.hp <= 0){
        	printf("Congratulations, you defeated a %s!\n", mob.name);
        	printf("You gained 100 XP and 5 Gold...");
        	player->xp += 100;
        	Sleep(2000);
        	break;
		}
        
		int mDamage = calcDamage(mob.atk, player->def);
		player->hp -= mDamage;
		
		printf("The %s hits you for %d damage! (Your HP: %d)\n", 
                mob.name, mDamage, player->hp > 0 ? player->hp : 0);

        if (player->hp <= 0) {
            printf("You were defeated by the %s...\n", mob.name);
            Sleep(2000);
            return;
        }
	
        printf("Press enter to continue...."); getchar();
	}
	
}

void gainXP(Player* player, int xpGain){
	player->xp += xpGain;
	
	if(player->xp >= (player->level*150)){
		levelUp(player);
	}
}

void cheatCode(Player *player){
	player->hp = 999999;
	player->atk = 999999;
	player->def = 999999;
	printf("Successfully applied cheat code. Now you're a Demon...\n"); Sleep(2000);
}

void showStats(Player *player) {
    system("cls");
    printf("====== Player Stats ======\n");
    printf("HP: %d\n", player->hp);
    printf("Attack: %d\n", player->atk);
    printf("Defense: %d\n", player->def);
    printf("XP: %d/%d\n", player->xp, player->level*150);
    printf("==========================\n");
    printf("Press Enter to return to the menu...\n");
    getchar();
}

void levelUp(Player* player){
	player->level++;
	player->hp += 10;
	player->atk += 2;
	player->def += 2;
	
	printf("You've levelled up!\n");
	printf("Press enter to continue..."); getchar();
	
}

// Mining menu
void miningMenu(Player *player) {
    int choice;

    system("cls");
    puts("Choose a mining option:");
    puts("[1] Copper");
    puts("[2] Coal");
    puts("[3] Exit to Main Menu");
    printf(">> ");
    scanf("%d", &choice); getchar();

    switch (choice) {
        case 1: activity(&copper, player); break;
        case 2: activity(&coal, player); break;
        case 3: return;
        default:
            printf("Invalid choice. Returning to the main menu...\n");
            Sleep(2000);
    }
}

// Fishing menu
void fishingMenu(Player *player) {
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
        case 1: activity(&cod, player); break;
        case 2: activity(&cakalang, player); break;
        case 3: activity(&tuna, player); break;
        case 4: return;
        default:
            printf("Invalid choice. Returning to the main menu...\n");
            Sleep(2000);
    }
}

void woodMenu(Player *player){
	int choice;
	
 	system("cls");
    puts("Choose a woodcutting option:");
    puts("[1] Kayu Oak");
    puts("[2] Kayu Cemara");
    puts("[3] Kayu Jati");
    puts("[4] Exit");   
    printf(">> ");
	scanf("%d", &choice); getchar();
	
	switch(choice){
		case 1: activity(&oak, player); break;
		case 2: activity(&cemara, player); break;
		case 3: activity(&jati, player); break;
		case 4: return;
	    default:
            printf("Invalid choice. Returning to the main menu...\n");
            Sleep(2000);
	}
}

// General activity function
void activity(Resource *resource, Player* player) {
    system("cls");
    
    while (1) {
        puts("Press Q to stop");
        puts("");
        Sleep(3000);
        
        system("cls");
        resource->count++;
        printf("You got 1 %s, Total: %d\n", resource->name, resource->count);
        
        gainXP(player, 10);
        
        // Check for quit condition
        if (kbhit()) { 
            int ch = getch(); 
            if (ch == 'q' || ch == 'Q') {
                break;  
            }
        }
    }
    
    printf("Activity stopped. Final count:\n");
    printf("%s: %d\n", resource->name, resource->count);
    printf("Press Enter to return to the menu...\n");
    getchar();
}