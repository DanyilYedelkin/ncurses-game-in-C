/* Hi, I'm Danyil Yedelkin. I want to show you my game and I think it will be much more atmospheric if you play the game and listen to soundtracks from the game The Witcher 3 :D 
music for relaxing during the passage of my game https://www.youtube.com/watch?v=_8URgTk_9eY&ab_channel=EpicMusicMix 

In the end You can find the code of my second game, please, I will be very happy if You check my second game, because I sat over it for a long time...
*/
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


struct CelyPredmet{
    /* create a new positions for our character and barrels of Whiskey */
    int PervoyePolozenie;
    int VtoroyePolozenie;

    /* variable of the symbols, which we get from numbers */
    char symbol;
    chtype barrelWhiskey;
};

/* create our functions */
void painting();
void MapSetUp(int *sirina, int *visota, int *massive, int PervoyePolozenie, int VtoroyePolozenie, int nomerKarti, chtype cvet);
void MakeLevel(int level);
int MakeScreen();
void moving(int input);
int Gameplay(int input, int level);
void text();
void WelcomeMessage();
void EndMessage();


/* the main function */
//======================================================================================================================================================================================
int main(int argc, char* argv[]){

    if(argc != 2){
        printf("Wrong number of parameters.\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "w");
    
    if(fp == NULL){
        printf("Error opening file.\n");
        fclose(fp);
        return 1;
    }

    int level = 0;
    int input;
    int moves = 0;
    int numberLevels = 0;

    /* Needed to output unicode characters */
    setlocale(LC_ALL, "");

    MakeScreen();

    while((input = getch()) != 10){

    }

    clear();

    text();
    MakeLevel(level);

    /* we will play until don't entered 'q' */
    while(1){
        timeout(300);
        Gameplay(input, level);
        if((input = getch()) == 'q'){
            break;
        }
        if(input == 'r' || input == 't' || input == 'y' || input == 'u' || input == 'i'){
            numberLevels++;
        } else if(input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'W' || input == 'A' || input == 'S' || input == 'D'){
            moves++;
        }
    }


    fprintf(fp, "Number of moves: %d", moves);
    fclose(fp);

    fp = fopen(argv[1], "r");
    
    if(fp == NULL){
        printf("Error opening file.\n");
        fclose(fp);
        return 1;
    }

    char words[10000];

    for(int i = 0; i < 10000; i++){
        words[i] = fgetc(fp);
        if(words[i] == EOF){
            words[i] = '\0';
            break;
        }
    }
    fclose(fp);

    clear();
    EndMessage();
    while(1){
        timeout(500);
        EndMessage();
        mvprintw(14, 49, "%s", words);
        attron(COLOR_PAIR(5));
        mvprintw(15, 45, "--------------------------");
        attroff(COLOR_PAIR(5));
        mvprintw(16, 46, "Number of map changes: %d", numberLevels);

        if((input = getch()) == 'q'){
            break;
        }
    }

    endwin();
    return 0;
}
//=====================================================================================================================================================================================
/* our functions */
int MakeScreen(){
    initscr();
    if(!has_colors()){
        endwin();
        printf("Eroor initialising colors.n");
        exit(1);
    }

    start_color();
    curs_set(0);
    painting();
    keypad(stdscr, TRUE);

    WelcomeMessage();

    return 1;
}
void painting(){
    /* stoled and changed the code from the website https://tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/#WHERETOGETIT */
    /* create colors, where is 1-5 is number, the second place is color of object and the third place is color of background*/
    //painting walls
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    //painting holes
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    //painting character
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    //painting barrels
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}
void WelcomeMessage(){

    clear();
    /* write and paint the main name of the game */
    attron(COLOR_PAIR(3));
    mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
    mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
    mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __       ");
    mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|  ");
    mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
    mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_|         ");
    mvprintw(6, 25, "                                __/ |                                             ");
    mvprintw(6, 25, "                               |___/                                    ");

    mvprintw(0, 2, " *    .        *       o");
    mvprintw(1, 2, "     |    o        .");
    mvprintw(2, 2, "    -O-       .    ");
    mvprintw(3, 2, "     |  *       *   ");
    mvprintw(4, 2, " *       .        .  |");
    mvprintw(5, 2, "       o      *     -O-");
    mvprintw(6, 2, ". *        .         |  .");
    mvprintw(7, 2, "     *  .     o  .");

    mvprintw(0, 97, "   *   . _.._   .   .");
    mvprintw(1, 97, "    .  .' .-'`    o");
    mvprintw(2, 97, " o    /  /  .");
    mvprintw(3, 97, "      |  |    *   .");
    mvprintw(4, 97, "   *  \\  \\   .   .");
    mvprintw(5, 97, " .     '._'-._   *  ");
    mvprintw(6, 97, "     *    ```   o    .");
    attroff(COLOR_PAIR(3));

    //============================================================
    /* write and paint decorations of the game */
    attron(COLOR_PAIR(1));
    mvprintw(8, 85, "  ,   A           {}");
    mvprintw(9, 85, " / \\, | ,        .--.");
    mvprintw(10, 85, "|    =|= >      /.--.\\");
    mvprintw(11, 85, " \\ /` | `       |====|");
    mvprintw(12, 85, "  `   |         |`::`|");
    mvprintw(13, 85, "      |     .-;`\\..../`;_.-^-._");
    mvprintw(14, 85, "     /\\/   /  |...::..|`   :   `|");
    mvprintw(15, 85, "     |:'\\ |   /'''::''|   .:.   |");
    mvprintw(16, 85, "      \\ /\\;-,/\\   ::  |..:::::..|");
    mvprintw(17, 85, "      |\\ <` >  >._::_.| ':::::' |");
    mvprintw(18, 85, "      | `\"\"`  /   ^^  |   ':'   |");
    mvprintw(19, 85, "      |       |       \\    :    /");
    mvprintw(20, 85, "      |       |        \\   :   /");
    mvprintw(21, 85, "      |       |___/\\___|`-.:.-`");
    mvprintw(22, 85, "      |        \\_ || _/    `");
    mvprintw(23, 85, "      |        <_ >< _>");
    mvprintw(24, 85, "      |        |  ||  |");
    mvprintw(25, 85, "      |        |  ||  |");
    mvprintw(26, 85, "      |       _\\.:||:./_");
    mvprintw(27, 85, "      |      /____/\\____\\");
    attroff(COLOR_PAIR(1));

    //==========================================================

    attron(COLOR_PAIR(1));
    mvprintw(8, 25, "                                  |>>>");
    mvprintw(9, 25, "                                  |");
    mvprintw(10, 25, "                    |>>>      _  _|_  _         |>>>");
    mvprintw(11, 25, "                    |        |;| |;| |;|        |");
    mvprintw(12, 25, "                _  _|_  _    \\\\.    .  /    _  _|_  _");
    mvprintw(13, 25, "               |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|");
    mvprintw(14, 25, "               \\\\..      /    ||;   . |    \\\\.    .  /");
    mvprintw(15, 25, "                \\\\.  ,  /     ||:  .  |     \\\\:  .  /");
    mvprintw(16, 25, "                 ||:   |_   _ ||_ . _ | _   _||:   |");
    mvprintw(17, 25, "                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |");
    mvprintw(18, 25, "                 ||:   ||.    .     .      . ||:  .|");
    mvprintw(19, 25, "                 ||: . || .     . .   .  ,   ||:   |       \\,/");
    mvprintw(20, 25, "                 ||:   ||:  ,  _______   .   ||: , |            /`\\");
    mvprintw(21, 25, "                 ||:   || .   /+++++++\\    . ||:   |");
    mvprintw(22, 25, "                 ||:   ||.    |+++++++| .    ||: . |");
    mvprintw(23, 25, "              __ ||: . ||: ,  |+++++++|.  . _||_   |");
    mvprintw(24, 25, "     ____--`~    '--~~__|.    |+++++__|----~    ~`---,            | ___");
    mvprintw(25, 25, "-~--~                   ~---__|,--~'                  ~~----_____-|'   `~--");
    attroff(COLOR_PAIR(1));

    //===================================================

    attron(COLOR_PAIR(1));
    mvprintw(8, 5, "              {}");
    mvprintw(9, 5, "             .--.");
    mvprintw(10, 5, "            /.--.\\");
    mvprintw(11, 5, "            |====|");
    mvprintw(12, 5, "            |`::`|");
    mvprintw(13, 5, "        .-;`\\..../`;_.-^-._");
    mvprintw(14, 5, " /\\\\   /  |...::..|`   :   `|");
    mvprintw(15, 5, " |:'\\ |   /'''::''|   .:.   |");
    mvprintw(16, 5, "@|\\ /\\;-,/\\   ::  |..:::::..|");
    mvprintw(17, 5, "`||\\ <` >  >._::_.| ':::::' |");
    mvprintw(18, 5, " || `\" \"` /   ^^  |   ':'   |");
    mvprintw(19, 5, " ||       |       \\    :    /");
    mvprintw(20, 5, " ||       |        \\   :   /");
    mvprintw(21, 5, " ||       |___/\\___|`-.:.-`");
    mvprintw(22, 5, " ||        \\_ || _/    `");
    mvprintw(23, 5, " ||        <_ >< _>");
    mvprintw(24, 5, " ||        |  ||  |");
    mvprintw(25, 5, " ||        |  ||  |");
    mvprintw(26, 5, " ||       _\\.:||:./_");
    mvprintw(27, 5, " \\/      /____/\\____\\");
    attroff(COLOR_PAIR(1));

    //=================================================
    /* write and paint the text of the start menu */
    attron(COLOR_PAIR(5));
    mvprintw(13, 45, "Hey you, you're finally awake.");
    mvprintw(14, 42, "You were trying to cross the border?");
    mvprintw(15, 41, "Walked right into that imperial ambush,");
    mvprintw(16, 43, "like us and that thief over there.");
    attroff(COLOR_PAIR(5));
    mvprintw(18, 42, "Press ENTER to escape with the rest");
    attron(COLOR_PAIR(3));
    mvprintw(27, 45, "Game created by Danyil Yedelkin");
    attroff(COLOR_PAIR(3));
}
void text(){
    /* create a text */
    attron(COLOR_PAIR(3));
    mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
    mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
    mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __       ");
    mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|      ");
    mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
    mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_|         ");
    mvprintw(6, 25, "                                __/ |                                             ");
    mvprintw(7, 25, "                               |___/                                    ");
    attroff(COLOR_PAIR(3));
    mvprintw(0, 2, " *    .        *       o");
    mvprintw(1, 2, "     |    o        .");
    mvprintw(2, 2, "    -O-       .    ");
    mvprintw(3, 2, "     |  *       *   ");
    mvprintw(4, 2, " *       .        .  |");
    mvprintw(5, 2, "       o      *     -O-");
    mvprintw(6, 2, ". *        .         |  .");
    mvprintw(7, 2, "     *  .     o  .");

    mvprintw(0, 97, "   *   . _.._   .   .");
    mvprintw(1, 97, "    .  .' .-'`    o");
    mvprintw(2, 97, " o    /  /  .");
    mvprintw(3, 97, "      |  |    *   .");
    mvprintw(4, 97, "   *  \\  \\   .   .");
    mvprintw(5, 97, " .     '._'-._   *  ");
    mvprintw(6, 97, "     *    ```   o    .");

    attron(COLOR_PAIR(5));
    mvprintw(7, 24, "Dungeon levels:");
    mvprintw(8, 25, "               ");
    mvprintw(9, 23, "First level:  'r'");
    mvprintw(10, 23, "Second level: 't'");
    mvprintw(11, 23, "Third level:  'y'");
    mvprintw(12, 23, "Fourth level: 'u'");
    mvprintw(13, 23, "Fifth level:  'i'");
    mvprintw(14, 23, "");

    mvprintw(15, 23, "==================");

    mvprintw(16, 23, "");
    mvprintw(17, 24, "Knight control:");
    mvprintw(18, 23, "");
    mvprintw(19, 23, "'W', 'KEY_UP' - step up");
    mvprintw(20, 23, "'A', 'KEY_LEFT' - step left");
    mvprintw(21, 23, "'S', 'KEY_DOWN' - step down");
    mvprintw(22, 23, "'D', 'KEY_RIGHT' - step right");
    mvprintw(24, 3, "Click 'q' to see Sovngarde");
    mvprintw(25, 3, "Click a symbol of your level to restart");
    mvprintw(27, 3, "Enjoy solving puzzles :D");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(3));
    mvprintw(28, 3, "Game created by Danyil Yedelkin");
    attroff(COLOR_PAIR(3));
    //===========================================================================
    /* history */
    attron(COLOR_PAIR(2));
    mvprintw(7, 65, "History");
    attroff(COLOR_PAIR(2));

    mvprintw(8, 43, "The imperial soldiers wanted to execute you, like the rest of the");
    mvprintw(9, 43, "prisoners. But the dragon attacked the settlement, where the");
    mvprintw(10, 43, "execution was carried out, and you and the rest of the");
    mvprintw(11, 43, "Stormcloak Soldiers were able to escape. But not for long...");
    mvprintw(12, 43, "You and Ralof were able to close together in the castle room.");
    mvprintw(13, 43, "But the Imperial soldiers were looking for you");
    mvprintw(14, 43, " ");
    mvprintw(15, 43, "Ralof: We'll meet again in Sovngarde, brother. Looks like we're the only");
    mvprintw(16, 43, "ones who made it. That thing was a dragon. No doubt. Just like the children's");
    mvprintw(17, 43, "stories and the legends. The harbingers of the End Times. We better get");
    mvprintw(18, 43, "moving. Come here, let me see if I can get those bindings off. There you");
    mvprintw(19, 43, "go. May as well take Gunjar's gear...he won't be needing it anymore.");
    mvprintw(20, 43, "Alright, get that armor on and give that axe a few swings. I'm going to");
    mvprintw(21, 43, "see if I can find some way out of here. This one's locked. Let's see");
    mvprintw(22, 43, "about that gate. Damn. No way to open this from our side.");
    mvprintw(23, 43, " ");
    mvprintw(24, 43, "Imperial Captain: Come on, soldier! Keep moving!");
    mvprintw(25, 43, " ");
    mvprintw(26, 43, "Ralof: It's the Imperials! Take cover!");

    attron(COLOR_PAIR(3));
    mvprintw(27, 50, "* You must move the barrels '@' to the doors 'x',");
    mvprintw(28, 53, "so the Imperial Soldiers can't catch you *");
    attroff(COLOR_PAIR(3));
}
void EndMessage(){
    /* create a random */
    srand(time(NULL));

    int randomColor0 = 0;
    int randomColor1 = 1;
    int random = rand()%3;

    attron(COLOR_PAIR(3));
    mvprintw(0, 2, " *    .        *       o");
    mvprintw(1, 2, "     |    o        .");
    mvprintw(2, 2, "    -O-       .    ");
    mvprintw(3, 2, "     |  *       *   ");
    mvprintw(4, 2, " *       .        .  |");
    mvprintw(5, 2, "       o      *     -O-");
    mvprintw(6, 2, ". *        .         |  .");
    mvprintw(7, 2, "     *  .     o  .");

    mvprintw(0, 97, "   *   . _.._   .   .");
    mvprintw(1, 97, "    .  .' .-'`    o");
    mvprintw(2, 97, " o    /  /  .");
    mvprintw(3, 97, "      |  |    *   .");
    mvprintw(4, 97, "   *  \\  \\   .   .");
    mvprintw(5, 97, " .     '._'-._   *  ");
    mvprintw(6, 97, "     *    ```   o    .");
    attroff(COLOR_PAIR(3));

    /* we will have a random color for the main name of the game */
    if(randomColor0 == random){

        attron(COLOR_PAIR(3));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __ ");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                    ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(3));

    } else if(randomColor1 == random){

        attron(COLOR_PAIR(5));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                   ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(5));

    } else{

        attron(COLOR_PAIR(2));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                  ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(2));

    }

    //============================================================
    /* create and paint decorations for end menu */
    attron(COLOR_PAIR(1));
    mvprintw(8, 85, "  ,   A           {}");
    mvprintw(9, 85, " / \\, | ,        .--.");
    mvprintw(10, 85, "|    =|= >      /.--.\\");
    mvprintw(11, 85, " \\ /` | `       |====|");
    mvprintw(12, 85, "  `   |         |`::`|");
    mvprintw(13, 85, "      |     .-;`\\..../`;_.-^-._");
    mvprintw(14, 85, "     /\\/   /  |...::..|`   :   `|");
    mvprintw(15, 85, "     |:'\\ |   /'''::''|   .:.   |");
    mvprintw(16, 85, "      \\ /\\;-,/\\   ::  |..:::::..|");
    mvprintw(17, 85, "      |\\ <` >  >._::_.| ':::::' |");
    mvprintw(18, 85, "      | `\"\"`  /   ^^  |   ':'   |");
    mvprintw(19, 85, "      |       |       \\    :    /");
    mvprintw(20, 85, "      |       |        \\   :   /");
    mvprintw(21, 85, "      |       |___/\\___|`-.:.-`");
    mvprintw(22, 85, "      |        \\_ || _/    `");
    mvprintw(23, 85, "      |        <_ >< _>");
    mvprintw(24, 85, "      |        |  ||  |");
    mvprintw(25, 85, "      |        |  ||  |");
    mvprintw(26, 85, "      |       _\\.:||:./_");
    mvprintw(27, 85, "      |      /____/\\____\\");
    attroff(COLOR_PAIR(1));

    //==========================================================

    attron(COLOR_PAIR(1));
    mvprintw(8, 25, "                                  |>>>");
    mvprintw(9, 25, "                                  |");
    mvprintw(10, 25, "                    |>>>      _  _|_  _         |>>>");
    mvprintw(11, 25, "                    |        |;| |;| |;|        |");
    mvprintw(12, 25, "                _  _|_  _    \\\\.    .  /    _  _|_  _");
    mvprintw(13, 25, "               |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|");
    mvprintw(14, 25, "               \\\\..      /    ||;   . |    \\\\.    .  /");
    mvprintw(15, 25, "                \\\\.  ,  /     ||:  .  |     \\\\:  .  /");
    mvprintw(16, 25, "                 ||:   |_   _ ||_ . _ | _   _||:   |");
    mvprintw(17, 25, "                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |");
    mvprintw(18, 25, "                 ||:   ||.    .     .      . ||:  .|");
    mvprintw(19, 25, "                 ||: . || .     . .   .  ,   ||:   |       \\,/");
    mvprintw(20, 25, "                 ||:   ||:  ,  _______   .   ||: , |            /`\\");
    mvprintw(21, 25, "                 ||:   || .   /+++++++\\    . ||:   |");
    mvprintw(22, 25, "                 ||:   ||.    |+++++++| .    ||: . |");
    mvprintw(23, 25, "              __ ||: . ||: ,  |+++++++|.  . _||_   |");
    mvprintw(24, 25, "     ____--`~    '--~~__|.    |+++++__|----~    ~`---,            | ___");
    mvprintw(25, 25, "-~--~                   ~---__|,--~'                  ~~----_____-|'   `~--");
    attroff(COLOR_PAIR(1));

    //===================================================

    attron(COLOR_PAIR(1));
    mvprintw(8, 5, "              {}");
    mvprintw(9, 5, "             .--.");
    mvprintw(10, 5, "            /.--.\\");
    mvprintw(11, 5, "            |====|");
    mvprintw(12, 5, "            |`::`|");
    mvprintw(13, 5, "        .-;`\\..../`;_.-^-._");
    mvprintw(14, 5, " /\\\\   /  |...::..|`   :   `|");
    mvprintw(15, 5, " |:'\\ |   /'''::''|   .:.   |");
    mvprintw(16, 5, "@|\\ /\\;-,/\\   ::  |..:::::..|");
    mvprintw(17, 5, "`||\\ <` >  >._::_.| ':::::' |");
    mvprintw(18, 5, " || `\" \"` /   ^^  |   ':'   |");
    mvprintw(19, 5, " ||       |       \\    :    /");
    mvprintw(20, 5, " ||       |        \\   :   /");
    mvprintw(21, 5, " ||       |___/\\___|`-.:.-`");
    mvprintw(22, 5, " ||        \\_ || _/    `");
    mvprintw(23, 5, " ||        <_ >< _>");
    mvprintw(24, 5, " ||        |  ||  |");
    mvprintw(25, 5, " ||        |  ||  |");
    mvprintw(26, 5, " ||       _\\.:||:./_");
    mvprintw(27, 5, " \\/      /____/\\____\\");
    attroff(COLOR_PAIR(1));

    //=================================================


    attron(COLOR_PAIR(5));
    mvprintw(10, 42, "I used to be an adventurer like you,");
    mvprintw(11, 43, "Then I took an arrow in the knee");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(3));
    mvprintw(26, 41, "A Nord's last thought should be of home...");
    mvprintw(27, 47, "Click 'q' to see Sovngarde");
    attroff(COLOR_PAIR(3));
}
void MapSetUp(int *sirina, int *visota, int *massive, int PervoyePolozenie, int VtoroyePolozenie, int nomerKarti, chtype cvet){
    /* the idea for creating maps was taken from the site https://www.codeproject.com/Questions/1144186/Map-creating-using-ncurses */
    /* checking map */
    while(1){
        if(nomerKarti >= 0){
            /* check number of map */
            if(nomerKarti == 0){

                /* create a map in array with numbers, which we will decode*/
                /* where is 1 is a wall, 0 is a floor, 3 is a barrel, 4 is a character */
                int karta1[11][17] = {
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
                    {1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},   
                    {1,1,1,1,1,0,0,3,1,1,1,1,1,1,1,1,1},  
                    {1,1,1,0,0,3,0,3,0,1,1,1,1,1,1,1,1}, 
                    {1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1},  
                    {1,0,0,0,1,0,1,1,0,1,1,1,0,0,2,2,1},  
                    {1,0,3,0,0,3,0,0,0,0,0,0,0,0,2,2,1}, 
                    {1,1,1,1,1,0,1,1,1,0,1,4,1,0,0,2,1},  
                    {1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1},  
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}  
                };

                /* take a size of map */
                int originalHeight = 11;
                int originalWidth = 17;

                *sirina = originalWidth;
                *visota = originalHeight;

                *massive = karta1[PervoyePolozenie][VtoroyePolozenie];
                break;
            } else if(nomerKarti == 1){ /* check number of map */

                /* create a map in array with numbers, which we will decode*/
                /* where is 1 is a wall, 0 is a floor, 3 is a barrel, 4 is a character */
                int karta2[11][17] = {
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1},
                    {1,1,1,0,0,1,3,0,0,0,0,0,0,0,1,1,1},
                    {1,1,1,0,3,3,0,0,0,0,0,0,1,0,1,1,1},
                    {1,1,1,4,0,0,1,3,0,0,0,3,1,0,1,1,1},
                    {1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1},
                    {1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1},
                    {1,1,1,1,0,0,0,2,2,2,2,2,0,0,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                };

                /* take a size of map */
                int originalHeight = 11;
                int originalWidth = 17;
        
                *sirina = originalWidth;
                *visota = originalHeight;

                *massive = karta2[PervoyePolozenie][VtoroyePolozenie];
                break;
            } else if(nomerKarti == 2){ /* check number of map */   

                /* create a map in array with numbers, which we will decode*/
                /* where is 1 is a wall, 0 is a floor, 3 is a barrel, 4 is a character */
                int karta3[11][17] = {
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,0,0,1,2,0,0,1,1,1,1},
                    {1,1,1,1,1,1,0,0,3,0,2,2,2,1,1,1,1},
                    {1,1,1,1,1,0,0,3,0,1,0,0,2,1,1,1,1},
                    {1,1,1,1,1,0,1,1,3,1,0,0,1,1,1,1,1},
                    {1,1,1,1,0,0,0,3,0,0,0,3,0,1,1,1,1},
                    {1,1,1,1,0,0,0,1,0,0,0,0,0,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,4,0,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                };

                /* take a size of map */
                int originalHeight = 11;
                int originalWidth = 17;
        
                *sirina = originalWidth;
                *visota = originalHeight;

                *massive = karta3[PervoyePolozenie][VtoroyePolozenie];
                break;
            } else if(nomerKarti == 3){ /* check number of map */   

                /* create a map in array with numbers, which we will decode*/
                /* where is 1 is a wall, 0 is a floor, 3 is a barrel, 4 is a character */
                int karta4[11][17] = {
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,0,4,0,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,0,3,0,0,0,0,0,3,0,1,1,1},
                    {1,1,1,1,1,1,3,1,1,1,1,2,1,0,1,1,1},
                    {1,1,1,1,1,0,0,0,0,0,2,2,2,0,1,1,1},
                    {1,1,1,1,1,0,3,0,3,0,1,2,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                };

                /* take a size of map */
                int originalHeight = 11;
                int originalWidth = 17;
        
                *sirina = originalWidth;
                *visota = originalHeight;

                *massive = karta4[PervoyePolozenie][VtoroyePolozenie];
                break;
            } else if(nomerKarti == 4){ /* check number of map */   

                /* create a map in array with numbers, which we will decode*/
                /* where is 1 is a wall, 0 is a floor, 3 is a barrel, 4 is a character */
                int karta5[11][17] = {
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,0,2,2,0,1,1,1,1,1,1},
                    {1,1,1,1,0,0,3,0,0,0,3,0,0,1,1,1,1},
                    {1,1,1,1,0,1,0,2,2,2,3,1,0,1,1,1,1},
                    {1,1,1,1,0,1,0,0,1,0,0,1,0,1,1,1,1},
                    {1,1,1,1,0,1,3,3,1,1,1,1,0,1,1,1,1},
                    {1,1,1,1,0,0,0,0,4,0,0,0,0,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                };

                /* take a size of map */
                int originalHeight = 11;
                int originalWidth = 17;
        
                *sirina = originalWidth;
                *visota = originalHeight;

                *massive = karta5[PervoyePolozenie][VtoroyePolozenie];
                break;
            }
        } else{
            break;
        }
    }
}
/* a number of barrels and a character */
struct CelyPredmet predmet[10] = {

};
void MakeLevel(int level){
    /* clear a map after changed and restard levels */
    clear();

    int randomColor0 = 0;
    int randomColor1 = 1;
    int random = rand()%3;

    attron(COLOR_PAIR(3));
    mvprintw(0, 2, " *    .        *       o");
    mvprintw(1, 2, "     |    o        .");
    mvprintw(2, 2, "    -O-       .    ");
    mvprintw(3, 2, "     |  *       *   ");
    mvprintw(4, 2, " *       .        .  |");
    mvprintw(5, 2, "       o      *     -O-");
    mvprintw(6, 2, ". *        .         |  .");
    mvprintw(7, 2, "     *  .     o  .");

    mvprintw(0, 97, "   *   . _.._   .   .");
    mvprintw(1, 97, "    .  .' .-'`    o");
    mvprintw(2, 97, " o    /  /  .");
    mvprintw(3, 97, "      |  |    *   .");
    mvprintw(4, 97, "   *  \\  \\   .   .");
    mvprintw(5, 97, " .     '._'-._   *  ");
    mvprintw(6, 97, "     *    ```   o    .");
    attroff(COLOR_PAIR(3));

    /* we will have a random color for the main name of the game */
    if(randomColor0 == random){
        attron(COLOR_PAIR(3));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __ ");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__| ");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                   ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(3));
    } else if(randomColor1 == random){
        attron(COLOR_PAIR(5));
       mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __ ");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__| ");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                      ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(5));
    } else{
        attron(COLOR_PAIR(2));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __ ");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__| ");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_|  ");
        mvprintw(6, 25, "                                __/ |                                      ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(2));
    }

    /* create a text about moving and rooms */
    attron(COLOR_PAIR(5));
    mvprintw(7, 22, "Castle rooms:");
    mvprintw(8, 23, "               ");
    mvprintw(9, 21, "First room:  'r'");
    mvprintw(10, 21, "Second room: 't'");
    mvprintw(11, 21, "Third room:  'y'");
    mvprintw(12, 21, "Fourth room: 'u'");
    mvprintw(13, 21, "Fifth room:  'i'");
    mvprintw(14, 21, "");

    mvprintw(15, 21, "==================");

    mvprintw(16, 21, "");
    mvprintw(17, 22, "Knight control:");
    mvprintw(18, 21, "");
    mvprintw(19, 21, "'W'- step up");
    mvprintw(20, 21, "'A'- step left");
    mvprintw(21, 21, "'S'- step down");
    mvprintw(22, 21, "'D'- step right");

    mvprintw(24, 3, "Click 'q' to see Sovngarde");
    mvprintw(25, 3, "Click a symbol of your level to restart");
    mvprintw(27, 3, "Enjoy solving puzzles :D");
    attroff(COLOR_PAIR(5));

    /* Dame developer :D */
    attron(COLOR_PAIR(3));
    mvprintw(28, 3, "Game created by Danyil Yedelkin");
    attroff(COLOR_PAIR(3));

    //===========================================================================
    /* history */
    attron(COLOR_PAIR(2));
    mvprintw(7, 65, "History");
    attroff(COLOR_PAIR(2));

    mvprintw(8, 43, "The imperial soldiers wanted to execute you, like the rest of the");
    mvprintw(9, 43, "prisoners. But the dragon attacked the settlement, where the");
    mvprintw(10, 43, "execution was carried out, and you and the rest of the");
    mvprintw(11, 43, "Stormcloak Soldiers were able to escape. But not for long...");
    mvprintw(12, 43, "You and Ralof were able to close together in the castle room.");
    mvprintw(13, 43, "But the Imperial soldiers were looking for you");
    mvprintw(14, 43, " ");
    mvprintw(15, 43, "Ralof: We'll meet again in Sovngarde, brother. Looks like we're the only");
    mvprintw(16, 43, "ones who made it. That thing was a dragon. No doubt. Just like the children's");
    mvprintw(17, 43, "stories and the legends. The harbingers of the End Times. We better get");
    mvprintw(18, 43, "moving. Come here, let me see if I can get those bindings off. There you");
    mvprintw(19, 43, "go. May as well take Gunjar's gear...he won't be needing it anymore.");
    mvprintw(20, 43, "Alright, get that armor on and give that axe a few swings. I'm going to");
    mvprintw(21, 43, "see if I can find some way out of here. This one's locked. Let's see");
    mvprintw(22, 43, "about that gate. Damn. No way to open this from our side.");
    mvprintw(23, 43, " ");
    mvprintw(24, 43, "Imperial Captain: Come on, soldier! Keep moving!");
    mvprintw(25, 43, " ");
    mvprintw(26, 43, "Ralof: It's the Imperials! Take cover!");

    attron(COLOR_PAIR(3));
    mvprintw(27, 50, "* You must move the barrels '@' to the gates 'x',");
    mvprintw(28, 53, "so the Imperial Soldiers can't catch you *");
    attroff(COLOR_PAIR(3));

    /* creating variables */
    int x_pointer = 0;
    int y_pointer = 0;
    int height = 1;
    int width = 1;
    int map;
    int barrel = 0;
    int character = 0;
    char floor = '-';
    char wall = '#';
    char barrels = '@';
    char characters = 'D';
    char hole = 'x';

    /* build our map */
    // height of map
    for(y_pointer = 0; y_pointer < height; y_pointer++){ 
        // width of map
        for(x_pointer = 0; x_pointer < width; x_pointer++){ 

            /* activate our map */
            MapSetUp(&width, &height, &map, y_pointer, x_pointer, level, COLOR_PAIR(7));

            /* check map */
            switch(map){
                case 0:{
                    /* decode our map and paint it */
                    if(1){
                        attron(COLOR_PAIR(4));
                        mvaddch(y_pointer + 9, x_pointer + 3, floor);
                        /* where is y_pointer - is y position, x-pointer - x position and a floor*/
                        attroff(COLOR_PAIR(4));
                        break;
                    }
                } 
                case 1:{
                    /* decode our map and paint it */
                    if(1){
                        attron(COLOR_PAIR(1));
                        mvaddch(y_pointer + 9, x_pointer + 3, wall);
                        /* where is y_pointer - is y position, x-pointer - x position and a wall */
                        attroff(COLOR_PAIR(1));
                        break;
                    }
                }
                case 2:{
                    /* decode our map and paint it */
                    if(1){
                        attron(COLOR_PAIR(2));
                        mvaddch(y_pointer + 9, x_pointer + 3, hole);
                        /* where is y_pointer - is y position, x-pointer - x position and a hole */ 
                        attroff(COLOR_PAIR(2));
                        break;
                    } 
                }
                case 3:{
                    /* decode our map and paint it */
                    if(1){
                        attron(COLOR_PAIR(4));
                        /* where is y_pointer - is y position, x-pointer - x position and floor */
                        mvaddch(y_pointer + 9, x_pointer + 3, floor);
                        attroff(COLOR_PAIR(4));

                        /* add quantity of barrels of Whiskey */
                        barrel++;

                        /* create a barrel in the place we need, where y_pointer is a new Y position and x_pointer is a new X position */
                        predmet[barrel].barrelWhiskey = mvinch(y_pointer + 9, x_pointer + 3);

                        /* create a symbol for our barrel */
                        predmet[barrel].symbol = barrels;

                        /* create a X and Y positions for our barrel */
                        predmet[barrel].PervoyePolozenie = x_pointer + 3;
                        predmet[barrel].VtoroyePolozenie = y_pointer + 9;

                        attron(COLOR_PAIR(5));
                        /* add our barrel in the position, which we need, and paint it */
                        mvaddch(predmet[barrel].VtoroyePolozenie, predmet[barrel].PervoyePolozenie, barrels);
                        attroff(COLOR_PAIR(5));
                        break;
                    }
                }
                case 4:{
                    /* decode our map and paint it */
                    if(1){
                        attron(COLOR_PAIR(4));
                        /* where is y_pointer - is y position, x-pointer - x position and floor */
                        mvaddch(y_pointer + 9, x_pointer + 3, floor);
                        attroff(COLOR_PAIR(4));

                        /* create a character in the place we need, where y_pointer is a new Y position and x_pointer is a new X position */
                        predmet[0].barrelWhiskey = mvinch(y_pointer + 9, x_pointer + 3);

                        /* create a symbol for our character */
                        predmet[0].symbol = characters;

                        /* create a X and Y positions for our barrel */
                        predmet[0].PervoyePolozenie = x_pointer + 3;
                        predmet[0].VtoroyePolozenie = y_pointer + 9;

                        attron(COLOR_PAIR(3));
                        /* add our barrel in the position, which we need, and paint it */
                        mvaddch(predmet[0].VtoroyePolozenie, predmet[0].PervoyePolozenie, characters);
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                }
            }
        }
    }
    /* moving our character into a current position */
    move(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie);
}
void moving(int input){
    int character = 0;

    /* create random and some variables */
    int randomColor0 = 0;
    int randomColor1 = 1;
    int random = rand()%3;

    attron(COLOR_PAIR(3));
    mvprintw(0, 2, " *    .        *       o");
    mvprintw(1, 2, "     |    o        .");
    mvprintw(2, 2, "    -O-       .    ");
    mvprintw(3, 2, "     |  *       *   ");
    mvprintw(4, 2, " *       .        .  |");
    mvprintw(5, 2, "       o      *     -O-");
    mvprintw(6, 2, ". *        .         |  .");
    mvprintw(7, 2, "     *  .     o  .");

    mvprintw(0, 97, "   *   . _.._   .   .");
    mvprintw(1, 97, "    .  .' .-'`    o");
    mvprintw(2, 97, " o    /  /  .");
    mvprintw(3, 97, "      |  |    *   .");
    mvprintw(4, 97, "   *  \\  \\   .   .");
    mvprintw(5, 97, " .     '._'-._   *  ");
    mvprintw(6, 97, "     *    ```   o    .");
    attroff(COLOR_PAIR(3));

    /* we will have a random color for the main name of the game */
    if(randomColor0 == random){

        attron(COLOR_PAIR(3));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__| ");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                  ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(3));

    } else if(randomColor1 == random){

        attron(COLOR_PAIR(5));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__| ");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                      ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(5));

    } else{

        attron(COLOR_PAIR(2));
        mvprintw(0, 25, " _____ _            _____ _                   _ _       _        ");
        mvprintw(1, 25, "|_   _| |          /  ___| |                 (_) |     | |  ");
        mvprintw(2, 25, "  | | | |__   ___  \\ `--.| | ___   ___      ___| |_ ___| |__   ___ _ __");
        mvprintw(3, 25, "  | | | '_ \\ / _ \\  `--. \\ |/ / | | \\ \\ /\\ / / | __/ __| '_ \\ / _ \\ '__|");
        mvprintw(4, 25, "  | | | | | |  __/ /\\__/ /   <| |_| |\\ V  V /| | || (__| | | |  __/ |   ");
        mvprintw(5, 25, "  \\_/ |_| |_|\\___| \\____/|_|\\_\\__,  | \\_/\\_/ |_|\\__\\___|_| |_|\\___|_| ");
        mvprintw(6, 25, "                                __/ |                                      ");
        mvprintw(6, 25, "                               |___/                                    ");
        attroff(COLOR_PAIR(2));

    }


    /* stoled and changed the code from the website https://coderoad.ru/48229214/%D0%9F%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-%D1%81%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB%D0%B0-%D0%B8%D0%B7-%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%BD%D1%8B%D1%85-%D0%BA%D0%BE%D0%BE%D1%80%D0%B4%D0%B8%D0%BD%D0%B0%D1%82-%D0%B2-%D0%BE%D0%BA%D0%BD%D0%B5-ncurses */
    /* a variable to check postion in the north (up) */
    //int lookUp = 0;
    int lookUp = mvinch(predmet[character].VtoroyePolozenie - 1, predmet[character].PervoyePolozenie) & A_CHARTEXT;

    /* a variable to check postion in the west (left) */
    //int lookleft = 0;
    int lookleft = mvinch(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie - 1) & A_CHARTEXT;

    /* a variable to check postion in the south (down) */
    //int lookDown = 0;
    int lookDown = mvinch(predmet[character].VtoroyePolozenie + 1, predmet[character].PervoyePolozenie) & A_CHARTEXT;

    /* a variable to check postion in the east (right) */
    //int lookRight = 0;
    int lookRight = mvinch(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie + 1) & A_CHARTEXT;

    /* a variable to check postion in the north (double up) */
    //int lookUpDouble = 0;
    int lookUpDouble = mvinch(predmet[character].VtoroyePolozenie - 2, predmet[character].PervoyePolozenie) & A_CHARTEXT;

    /* a variable to check postion in the west (double left) */
    //int lookLeftDouble = 0;
    int lookLeftDouble = mvinch(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie - 2) & A_CHARTEXT;

    /* a variable to check postion in the south (double down) */
    //int lookDownDouble = 0;
    int lookDownDouble = mvinch(predmet[character].VtoroyePolozenie + 2, predmet[character].PervoyePolozenie) & A_CHARTEXT;

    /* a variable to check postion in the east (double right) */
    //int lookRightDouble = 0;
    int lookRightDouble = mvinch(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie + 2) & A_CHARTEXT;

    char floor = '-';
    char wall = '#';
    char barrels = '@';
    char hole = 'x';

    /* delete symbols after a character, when he/she is walking */
    for(int i = 0; i < 6; i++){
        mvaddch(predmet[i].VtoroyePolozenie, predmet[i].PervoyePolozenie, predmet[i].barrelWhiskey);
    }

    /* check our input (W, A, S, D). All this is for walking */
    switch(input){
        /* first checking: KEY_UP, w, W - are for walk to up */
        case KEY_UP: //unreadable command in the game(when we are moving in the game, our another variable doesn't read this command)
        case 'w':
        case 'W':
        /* check if front block is '#' in the ASCII table */
        if(lookUp != wall){ 
            if(lookUp == barrels && lookUpDouble == floor){  // checking of symbol

                predmet[character].VtoroyePolozenie--;

                for(int i = 1; i < 6; i++){
                    if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                        if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                            predmet[i].VtoroyePolozenie--;
                        }
                    }
                }

            } else if(lookUp == barrels && lookUpDouble == hole){
                
                predmet[character].VtoroyePolozenie--;

                for(int i = 1; i < 6; i++){
                    if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                        if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                            predmet[i].VtoroyePolozenie--;
                        }
                    }
                }

            } else if(lookUp != barrels){
                /* check if front block is '@' in the ASCII table */

                predmet[character].VtoroyePolozenie--;
            }
        }
        break;

        /* second checking: KEY_LEFT, a, A - are for walk to left */
        case KEY_LEFT: //unreadable command in the game(when we are moving in the game, our another variable doesn't read this command)
        case 'a':
        case 'A':
            /* check if front block is '#' in the ASCII table */
            if(lookleft != wall){
                if(lookleft == barrels && lookLeftDouble == floor){   // checking of symbol
                    
                    predmet[character].PervoyePolozenie--;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].PervoyePolozenie--;
                            }
                        }
                    }
                } else if(lookleft == barrels && lookLeftDouble == hole){
                     
                    predmet[character].PervoyePolozenie--;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].PervoyePolozenie--;
                            }
                        }
                    }
                } else if(lookleft != barrels){

                    predmet[character].PervoyePolozenie--;
                } 
            }
        break;

        /* third checking: KEY_DOWN, s, S - are for walk to down */
        case KEY_DOWN: //unreadable command in the game(when we are moving in the game, our another variable doesn't read this command)
        case 's':
        case 'S':
            /* check if front block is '#' in the ASCII table */
            if(lookDown != wall){
                if(lookDown == barrels && lookDownDouble == floor){  // checking of symbol
                    
                    predmet[character].VtoroyePolozenie++;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].VtoroyePolozenie++;
                            }
                        }
                    }
                } else if(lookDown == barrels && lookDownDouble == hole){
                    
                    predmet[character].VtoroyePolozenie++;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].VtoroyePolozenie++;
                            }
                        }
                    }
                } else if(lookDown != barrels){
                    

                    predmet[character].VtoroyePolozenie++;
                }
            }
        break;

        /* fourth checking: KEY_RIGHT, d, D - are for walk to right */
        case KEY_RIGHT: //unreadable command in the game(when we are moving in the game, our another variable doesn't read this command)
        case 'd':
        case 'D':
            
            if(lookRight != wall){
                if(lookRight == barrels && lookRightDouble == floor){   // checking of symbol
                    
                    predmet[character].PervoyePolozenie++;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].PervoyePolozenie++;
                            }
                        }
                    }
                } else if(lookRight == barrels && lookRightDouble == hole){
                    
                    predmet[character].PervoyePolozenie++;

                    for(int i = 1; i < 6; i++){
                        if(predmet[i].PervoyePolozenie == predmet[character].PervoyePolozenie){
                            if(predmet[i].VtoroyePolozenie == predmet[character].VtoroyePolozenie){
                                predmet[i].PervoyePolozenie++;
                            }
                        }
                    }
                } else if(lookRight != barrels){
                    

                    predmet[character].PervoyePolozenie++;
                }
            }
        break;

        default:{
            break;
        }
    }  
}
/* the function, which help us to play */
int Gameplay(int input, int level){
    int character = 0;
    /* activate our function of moving character */
    moving(input);

    /* create a variable for our teleportation our character to the original place */
    bool backTeleportation = false;

    /* check our input of restar map and switch to the next map */ 
    switch(input){
        /* if we entered 'r', the map will be restart */
        case 'r':{ // the first map
            level = 0;
            backTeleportation = true;
            MakeLevel(level);
            break;
        }
        case 't':{ // the second map
            level = 1;
            backTeleportation = true;
            MakeLevel(level);
            break;
        }
        case 'y':{ // the third map
            level = 2;
            backTeleportation = true;
            MakeLevel(level);
            break;
        }
        case 'u':{ // the fourth map
            level = 3;
            backTeleportation = true;
            MakeLevel(level);
            break;
        }
        case 'i':{ // the fifth map
            level = 4;
            backTeleportation = true;
            MakeLevel(level);
            break;
        }
        
        /* if we entered something else */
        default:{
            break;
        }        
    }

    /* stoled and changed the code from the website https://tldp.org/HOWTO/html_single/NCURSES-Programming-HOWTO/#WHERETOGETIT */
    if(backTeleportation == false){

        for(int i = 0; i < 6; i++){
            predmet[i].barrelWhiskey = mvinch(predmet[i].VtoroyePolozenie, predmet[i].PervoyePolozenie);

            if(i == character){
                attron(COLOR_PAIR(3));
                mvaddch(predmet[i].VtoroyePolozenie, predmet[i].PervoyePolozenie, predmet[i].symbol);
                attroff(COLOR_PAIR(3));
            } else{
                attron(COLOR_PAIR(5));
                mvaddch(predmet[i].VtoroyePolozenie, predmet[i].PervoyePolozenie, predmet[i].symbol);
                attroff(COLOR_PAIR(5));
            }
        }

        move(predmet[character].VtoroyePolozenie, predmet[character].PervoyePolozenie);
        return level;
    } else{
        backTeleportation = false;
        return level;
    }
}



/* THE SECOND GAME */

/* Hello, it's my second game. For its creation I used many literature, such as
http://ilinblog.ru/article.php?id_article=49
https://www.youtube.com/watch?v=Q9zkiOClyEo&t=6s&ab_channel=Vectozavr
https://www.youtube.com/watch?v=xW8skO7MFYw&ab_channel=javidx9
https://www.purplealienplanet.com/node/20
https://habr.com/ru/post/187720/

and many another resources :D

for Compile you need to use this:   gcc gamer.c $(ncursesw5-config --cflags) -o gamer -lncursesw -lm
*/

/*
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include <math.h>

void MakeScreen();
void painting();


// create our main function 
int main()
{
    // creating a console screen size X (columns) 
    int ShirinaKarty;
    // creating console screen size Y (rows)   
    int VisotaKarty;   
    // creating World dimensions            
    int mapWidth = 16;       
    int mapHeight = 16;

    // creating a player start position 
    float PervoyePolozenie = 8.0f;   
    float VtoroyePolozenie = 8.0f;
    // ceating a player start rotation 
    float TreteyePolozenie = 2.0f;      
    // creating a field of view    
    float zrenie = 3.14159f / 2.0f; 
    // creating a maximum rendering distance 
    float distancia = 16.0f; 

    char stena = '#';

    int vichod = 1;

    // creating a world map, where '#' - wall, '.' - space 
    char karta[] =                   
    "################\
     #..............#\
     #..............#\
     #...########...#\
     #.......#..#...#\
     #..........#...#\
     #..............#\
     #...########...#\
     #...#...#..#...#\
     #...#...#..#...#\
     #..............#\
     #..............#\
     #...########...#\
     #..............#\
     #..............#\
     ################";


    // Needed to output unicode characters 
    setlocale(LC_ALL, "");
    
    // Initialize ncurses screen
    MakeScreen();
    getmaxyx(stdscr, VisotaKarty, ShirinaKarty);   

    // creating a game function
    while(vichod == 1)
    {    
        for(int colona = 0; colona < ShirinaKarty; colona++)
        {
            // for each column, calculate the projected ray angle into world space
            float dalnostZrenia = (TreteyePolozenie - zrenie / 2.0f) + ((float)colona / (float)ShirinaKarty) * zrenie;            
            float rastoyanie = 0.0f;
            
            int StenkaVLob = 0;
            
            // creating unit vector for ray in player space 
            float ZrenieX = sinf(dalnostZrenia); 
            float ZrenieY = cosf(dalnostZrenia);
            
            // find distance to wall
            while(!StenkaVLob && rastoyanie < distancia)   
            {
                // crate resolution 
                rastoyanie = rastoyanie + 0.5f;
                
                int proverkaColony = (int)(PervoyePolozenie + ZrenieX * rastoyanie);

                int proverkaRow = (int)(VtoroyePolozenie + ZrenieY * rastoyanie);
                
                // test our code if ray is out of bounds 
                if(proverkaColony < 0 || (proverkaColony > mapWidth + 1) || proverkaRow < 0 || (proverkaRow > mapHeight + 1)){
                    StenkaVLob = 1;
                    rastoyanie = distancia;
                } else{
                    if(karta[proverkaColony * mapWidth + proverkaRow] == stena){
                        StenkaVLob = 1;
                    }
                }
            }    
            
            // calculate distance to ceiling and floor 
            int ceiling = (float)(VisotaKarty / 2.0f) - VisotaKarty / ((float)rastoyanie);
            int floor = VisotaKarty - ceiling;
            
            // shader walls based on distance 
            const wchar_t* shade;

            // if we close to the wall 
            if(rastoyanie <= distancia / 4.0){
                shade = L"\x2588";
            } 
            // if we further to the wall 
            else if(rastoyanie <= distancia / 3.0){
                shade = L"\x2593";

            } else if(rastoyanie <= distancia / 2.0){
                shade = L"\x2592";

            } else if(rastoyanie <= distancia){
                shade = L"\x2591";

            } else{
                shade = L" ";

            }
            
            for(int row = 0; row < VisotaKarty; row++){

                if(ceiling  + 1 > row){
                    mvaddch(row, colona, '`');

                } else if(row > ceiling  && row < floor + 1){
                    mvaddwstr(row, colona, shade);

                } else{
                    // Shade floor based on distance
                    float b = 1.0f - (((float)row - VisotaKarty / 2.0f) / ((float)VisotaKarty / 2.0f));
                    
					if (b < 0.25){
                        shade = L"#";

                    } else if (b < 0.5){
                        shade = L"x";

                    } else if (b < 0.75){
                        shade = L".";

                    } else if (b < 0.9){
                        shade = L"-";

                    } else{
                        shade = L" ";

                    }
                    
                    mvaddwstr(row, colona, shade);
                }
            }
            
            refresh();
        }
        
        int input;
        
        switch((input = getch())){

            // Move forward and collisions 
            case KEY_UP:
            case 'W':
            case 'w': 
                PervoyePolozenie = PervoyePolozenie + sinf(TreteyePolozenie) * 0.5f;

                VtoroyePolozenie = VtoroyePolozenie + cosf(TreteyePolozenie) * 0.5f;
                
                if(karta[(int)PervoyePolozenie * mapWidth + (int)VtoroyePolozenie] == stena)
                {
                    PervoyePolozenie = PervoyePolozenie - sinf(TreteyePolozenie) * 0.5f;

                    VtoroyePolozenie = VtoroyePolozenie - cosf(TreteyePolozenie) * 0.5f;
                } 
                
                break;
            
            case KEY_DOWN:
            case 'S':
            case 's':
                // Move backward and collisions 
                PervoyePolozenie = PervoyePolozenie - sinf(TreteyePolozenie) * 0.5f;
                VtoroyePolozenie = VtoroyePolozenie - cosf(TreteyePolozenie) * 0.5f;
                
                if(karta[(int)PervoyePolozenie * mapWidth + (int)VtoroyePolozenie] == stena){
                    PervoyePolozenie = PervoyePolozenie + sinf(TreteyePolozenie) * 0.5f;

                    VtoroyePolozenie = VtoroyePolozenie + cosf(TreteyePolozenie) * 0.5f;
                }
                
                break;
            
            case KEY_LEFT:
            case 'A':
            case 'a': 
                // Rotate left 
                TreteyePolozenie = TreteyePolozenie - 0.1f;

                break;

            case KEY_RIGHT:
            case 'D':
            case 'd':
            // Rotate right 
                TreteyePolozenie = TreteyePolozenie + 0.1f;

                break;
        
            default:{
                // Any key to exit
                vichod = 0;

                break;
            }
        }    
    }
    
    attroff(COLOR_PAIR(1));

    endwin();        
}

void MakeScreen(){
    // Needed to output unicode characters 
    setlocale(LC_ALL, "");
    
    // Initialize ncurses screen 
    initscr();
    noecho();
    curs_set(0);
    painting();
    keypad(stdscr, TRUE);
}
void painting(){
    start_color();
    init_color(COLOR_GREEN, 0, 700, 200);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	attron(COLOR_PAIR(1));
}

*/