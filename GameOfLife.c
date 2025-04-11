#ifdef _WIN32
#include <windows.h>
HANDLE hConsole;
COORD cursorPos = {0, 0};
#endif

#ifdef __unix__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#define DEAD '.'
#define ALIVE 'o'
#define BLINKER 0
#define TOAD 1
#define BEACON 2
#define PULSAR 3
#define PENTADECATHLON 4
#define GLIDER 5
#define GOSPER_GLIDER_GUN 6
#define LWSS 7
#define RANDOM 8

#define DEFAULT_SLEEP_TIME 100
#define DEFAULT_MAX_ITER 250
#define DEFAULT_PATTERN 8
#define DEFAULT_DENSITY 2
#define DEFAULT_LOOPWINDOW 5

unsigned int GLOBAL_nlines = 0;
unsigned int GLOBAL_ncolumns = 0;
unsigned int GLOBAL_loopwindow = DEFAULT_LOOPWINDOW;

char **history = NULL;

void gridInit(char **history, int pattern, int density){
    for (int g = 0; g < GLOBAL_loopwindow; g++){
        for (int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
            history[g][i] = DEAD;
        }
    }
    switch (pattern){
    case BLINKER:
        history[1][11] = history[1][12] = history[1][13] = ALIVE;
        break;
    case TOAD:
        history[1][14] = history[1][15] = history[1][16] = history[1][19] = history[1][20] = history[1][21] = ALIVE;
        break;
    case BEACON:
        history[1][7] = history[1][8] = history[1][13] = history[1][22] = history[1][27] = history[1][28] = ALIVE;
        break;
    case PULSAR:
        history[1][22] = history[1][28] = history[1][39] = history[1][45] = history[1][56] = history[1][57] = history[1][61] = history[1][62] = history[1][86] = history[1][87] = history[1][88] = history[1][91] = history[1][92] = history[1][94] = history[1][95] = history[1][98] = history[1][99] = history[1][100] = history[1][105] = history[1][107] = history[1][109] = history[1][111] = history[1][113] = history[1][115] = history[1][124] = history[1][125] = history[1][129] = history[1][130] = history[1][158] = history[1][159] = history[1][163] = history[1][164] = history[1][173] = history[1][175] = history[1][177] = history[1][179] = history[1][181] = history[1][183] = history[1][188] = history[1][189] = history[1][190] = history[1][193] = history[1][194] = history[1][196] = history[1][197] = history[1][200] = history[1][201] = history[1][202] = history[1][226] = history[1][227] = history[1][231] = history[1][232] = history[1][243] = history[1][249] = history[1][260] = history[1][266] = ALIVE;
        break;
    case PENTADECATHLON:
        history[1][37] = history[1][38] = history[1][39] = history[1][49] = history[1][60] = history[1][70] = history[1][71] = history[1][72] = history[1][92] = history[1][93] = history[1][94] = history[1][103] = history[1][104] = history[1][105] = history[1][125] = history[1][126] = history[1][127] = history[1][137] = history[1][148] = history[1][158] = history[1][159] = history[1][160] = ALIVE;
        break;
    case GLIDER:
        history[1][1] = history[1][17] = history[1][30] = history[1][31] = history[1][32] = ALIVE;
        break;
    case GOSPER_GLIDER_GUN:
        history[1][63] = history[1][99] = history[1][101] = history[1][127] = history[1][128] = history[1][135] = history[1][136] = history[1][149] = history[1][150] = history[1][164] = history[1][168] = history[1][173] = history[1][174] = history[1][187] = history[1][188] = history[1][191] = history[1][192] = history[1][201] = history[1][207] = history[1][211] = history[1][212] = history[1][229] = history[1][230] = history[1][239] = history[1][243] = history[1][245] = history[1][246] = history[1][251] = history[1][253] = history[1][277] = history[1][283] = history[1][291] = history[1][316] = history[1][320] = history[1][355] = history[1][356] = ALIVE;
        break;
    case LWSS:
        history[1][31] = history[1][34] = history[1][65] = history[1][91] = history[1][95] = history[1][122] = history[1][123] = history[1][124] = history[1][125] = ALIVE;
        break;
    case RANDOM:
        for (int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
            if (rand() % 10 <= density - 1){
                history[1][i] = ALIVE;
            }
        }
        break;
    }
}

int gridCompare(char **history){
    size_t gridSize = GLOBAL_ncolumns * GLOBAL_nlines * sizeof(char);
    if (gridSize == 0){
        return 0;
    }
    for (int i = 1; i < GLOBAL_loopwindow; i++){
        if (memcmp(history[0], history[i], gridSize) == 0){
            return i;
        }
    }
    return 0;
}

void gridEvolve(char* current, char* next){
	int row, col;
	for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
		row = i / GLOBAL_ncolumns, col = i % GLOBAL_ncolumns;
        int count = 0;
		for(int j = col - 1; j <= col + 1 && count <= 4; j++){
			for(int k = row - 1; k <= row + 1; k++){
				if((j == col && k == row) || (j < 0 || j >= GLOBAL_ncolumns) || (k < 0 || k >= GLOBAL_nlines)){
                    continue;
                }
				if(current[k * GLOBAL_ncolumns + j] == ALIVE) {
                    count++;
                }
			}
		}
		next[i] = count == 3 || (count == 2 && current[i] == ALIVE) ? ALIVE : DEAD;
	}
}

void defineDimensions(int pattern){
    if (pattern == RANDOM){
        GLOBAL_nlines = (GLOBAL_nlines == 0) ? rand() % 16 + 5 : GLOBAL_nlines;
        GLOBAL_ncolumns = (GLOBAL_ncolumns == 0) ? rand() % 31 + 10 : GLOBAL_ncolumns;
    }
    else{
        switch (pattern){
        case BLINKER:
            GLOBAL_nlines = GLOBAL_ncolumns = 5;
            break;
        case TOAD:
        case BEACON:
            GLOBAL_nlines = GLOBAL_ncolumns = 6;
            break;
        case PULSAR:
            GLOBAL_nlines = GLOBAL_ncolumns = 17;
            break;
        case PENTADECATHLON:
            GLOBAL_nlines = 18;
            GLOBAL_ncolumns = 11;
            break;
        case GLIDER:
            GLOBAL_nlines = GLOBAL_ncolumns = 15;
            break;
        case GOSPER_GLIDER_GUN:
            GLOBAL_nlines = 20;
            GLOBAL_ncolumns = 38;
            break;
        case LWSS:
            GLOBAL_nlines = 7;
            GLOBAL_ncolumns = 30;
            break;
        }
    }
}

void gridShow(char *grid){
    if (!grid || GLOBAL_nlines == 0 || GLOBAL_ncolumns == 0){
        return;
    }
    for (int i = 0; i < GLOBAL_nlines; i++){
        fwrite(grid + i * GLOBAL_ncolumns, sizeof(char), GLOBAL_ncolumns, stdout);
        putchar('\n');
    }
}

void slideHistory(char **history){
    if (!history || GLOBAL_loopwindow < 2){
        return;
    }
    char *temp_oldest_buffer = history[GLOBAL_loopwindow - 1];
    for (int g = GLOBAL_loopwindow - 1; g > 0; g--){
        history[g] = history[g - 1];
    }
    history[0] = temp_oldest_buffer;
}

int main(int argc, char **argv){
    srand((unsigned int)time(NULL));

    unsigned int pattern = DEFAULT_PATTERN;
    unsigned int sleepTime = DEFAULT_SLEEP_TIME;
    unsigned int maxNumIters = DEFAULT_MAX_ITER;
    unsigned int density = DEFAULT_DENSITY;
    GLOBAL_loopwindow = DEFAULT_LOOPWINDOW;

    int opt;
    int option_index = 0;

    static struct option long_options[] = {
        {"pattern", required_argument, 0, 'p'},
        {"sleeptime", required_argument, 0, 's'},
        {"maxiterations", required_argument, 0, 'm'},
        {"cols", required_argument, 0, 'c'},
        {"rows", required_argument, 0, 'r'},
        {"density", required_argument, 0, 'd'},
        {"history", required_argument, 0, 'h'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "p:s:m:c:r:d:h:", long_options, &option_index)) != -1){
        switch (opt){
        case 'p':
            pattern = atoi(optarg);
            if (pattern > 8){
                fprintf(stderr, "Error: Pattern must be between 0 and 8.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 's':
            sleepTime = atoi(optarg);
            if (sleepTime > 10000){
                fprintf(stderr, "Error: Sleeptime must be between 0 and 10000 milliseconds.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'm':
            maxNumIters = atoi(optarg);
            if (maxNumIters == 0 || maxNumIters > 100000){
                fprintf(stderr, "Error: Maximum iterations must be between 1 and 100000.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            GLOBAL_ncolumns = atoi(optarg);
            printf("\n%d", GLOBAL_ncolumns);
            if (GLOBAL_ncolumns == 0 || GLOBAL_ncolumns > 100){
                fprintf(stderr, "Error: Number of columns must be between 1 and 100.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'r':
            GLOBAL_nlines = atoi(optarg);
            if (GLOBAL_nlines == 0 || GLOBAL_nlines > 50){
                fprintf(stderr, "Error: Number of rows must be between 1 and 50.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            density = atoi(optarg);
            if (density == 0 || density > 9){
                fprintf(stderr, "Error: Density must be between 1 and 9.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            GLOBAL_loopwindow = atoi(optarg);
            if (GLOBAL_loopwindow < 2 || GLOBAL_loopwindow > 100 || GLOBAL_loopwindow >= maxNumIters){
                fprintf(stderr, "Error: History must be between 2 and 100 or between 2 and maxiterations.\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            fprintf(stderr, "Usage: %s [--pattern <pattern>] [--sleeptime <ms>] [--maxiterations <n>] [--cols <n>] [--rows <n>] [--density <n>] [--history <n>]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (GLOBAL_loopwindow >= maxNumIters){
        fprintf(stderr, "Error: History window size (%u) must be less than max iterations (%u).\n", GLOBAL_loopwindow, maxNumIters);
        exit(EXIT_FAILURE);
    }

    if (optind < argc){
        fprintf(stderr, "Error: Unexpected argument: %s\n", argv[optind]);
        fprintf(stderr, "Usage: %s [--pattern <pattern>] [--sleeptime <ms>] [--maxiterations <n>] [--cols <n>] [--rows <n>] [--density <n>] [--history <n>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
#ifdef __unix__
    sleepTime *= 1000;
#endif
    defineDimensions(pattern);

    history = malloc(GLOBAL_loopwindow * sizeof(char *));
    if (!history){
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < GLOBAL_loopwindow; i++){
        history[i] = malloc(GLOBAL_ncolumns * GLOBAL_nlines * sizeof(char));
        if (!history[i]){
            fprintf(stderr, "Error: Memory allocation failed for history[%d].\n", i);
            exit(EXIT_FAILURE);
        }
    }
    gridInit(history, pattern, density);
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
#endif
#ifdef __unix__
    system("clear");
#endif
    fflush(stdout);
    unsigned int niter = 0;
    int loop_found = 0;
    while (niter < maxNumIters){
#ifdef _WIN32
        Sleep(sleepTime);
        SetConsoleCursorPosition(hConsole, cursorPos);
#endif
#ifdef __unix__
        usleep(sleepTime);
        printf("\033[H");
#endif
        fflush(stdout);
        gridShow(history[1]);
        printf("Iteration: %u / %u\n", niter + 1, maxNumIters);
        gridEvolve(history[1], history[0]);
        int loop_period = gridCompare(history);
        if (loop_period > 0){
            printf("\nLoop detected after %u iterations!\n", niter + 1);
            printf("Loop Period: %d\n", loop_period);
            loop_found = 1;
            break;
        }
        slideHistory(history);
        niter++;
    }
    if (!loop_found && niter == maxNumIters){
        printf("\nMaximum iterations (%u) reached without detecting a loop (within history window %u).\n", maxNumIters, GLOBAL_loopwindow);
    }
    if (history){
        for (int i = 0; i < GLOBAL_loopwindow; i++){
            if (history[i]){
                free(history[i]);
            }
        }
        free(history);
    }
    return 0;
}