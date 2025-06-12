#include <stdio.h>

#define RED "\x1b[31m"
#define GRE "\x1b[32m"
#define RES "\x1b[0m"

void display_menu();
int valid_input(int n);
void bad_input();
void play(int[9][9], int[9][9]);
void print_board(int[9][9], int[9][9]);
void insert_value(int, int, int, int[9][9], int[9][9]);
void remove_value(int, int, int[9][9], int[9][9]);
int valid_row(int, int[9][9]);
int valid_col(int, int[9][9]);
int valid_block(int, int, int[9][9]);
int valid_diag(int[9][9]);
int valid_sudoku(int[9][9]);

int main()
{
    // Novinski primjer sudoku zagonetke
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    // Označavanje fiksnih (zadano u zagonetki) brojeva
    int fixed[9][9] = {
        {1, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 1, 1}};

    int choice;

    do
    {
        display_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("Izlazim iz programa...\n");
            break;
        case 1:
            play(board, fixed);
            break;
        default:
            printf("Pogrešan odabir.\n");
            printf("Stisni ENTER za nastavak...\n");
            getchar();
            getchar();
        }

    } while (choice != 0);

    return 0;
}

void print_board(int board[9][9], int fixed[9][9])
{
    printf(GRE "    1 2 3   4 5 6   7 8 9\n" RES);
    printf("  +-------+-------+-------+\n");
    for (int i = 0; i < 9; i++)
    {
        printf(GRE "%d" RES, i + 1);
        printf(" | ");
        for (int j = 0; j < 9; j++)
        {
            if (fixed[i][j] == 1)
                printf(RED "%d " RES, board[i][j]);
            else if (board[i][j] == 0)
                printf("_ ");
            else
                printf("%d ", board[i][j]);
            if (j % 3 == 2)
                printf("| ");
        }
        printf("\n");
        if (i == 2 || i == 5)
            printf("  +-------+-------+-------+\n");
    }
    printf("  +-------+-------+-------+\n");
}

void display_menu()
{
    printf("\n=== Sudoku ===\n");
    printf("1. Igraj\n");
    printf("0. Izlaz\n");
    printf("Odaberi: ");
}

void play(int board[9][9], int fixed[9][9])
{
    int choice;
    int row;
    int col;
    int val;

    do
    {
        print_board(board, fixed);

        printf("1. Unesi broj.\n");
        printf("2. Izbrisi broj.\n");
        printf("3. Provjeri ispravnost.\n");
        printf("0. Prekini igru.\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Unesi redak, stupac i vrijednost (odvojene razmakom).\n");
            scanf("%d %d %d", &row, &col, &val);
            if (valid_input(row) && valid_input(col) && valid_input(val))
                insert_value(val, row - 1, col - 1, board, fixed);
            else
                bad_input();
            break;
        case 2:
            printf("Unesi redak, stupac (odvojene razmakom).\n");
            scanf("%d %d", &row, &col);
            if (valid_input(row) && valid_input(col))
                remove_value(row - 1, col - 1, board, fixed);
            else
                bad_input();
            break;
        case 3:
            if (valid_sudoku(board))
            {
                printf("Pobjeda, čestitamo!\n");
                printf("Stisni ENTER za nastavak...\n");
                getchar();
                getchar();
                choice = 0;
            }
            else
            {
                printf("Sudoku nije ispravan!\n");
                printf("Stisni ENTER za nastavak...\n");
                getchar();
                getchar();
            }
            break;
        case 0:
            break;
        default:
            bad_input();
            break;
        }
    } while (choice != 0);
}

int valid_input(int n)
{
    return n > 0 && n < 10;
}

void bad_input()
{
    printf("Pogrešan odabir.\n");
    printf("Stisni ENTER za nastavak...\n");
    getchar();
    getchar();
}

void insert_value(int val, int i, int j, int board[9][9], int fixed[9][9])
{
    if (fixed[i][j] == 0)
        board[i][j] = val;
    else
        printf("Ne možeš mijenjati zadano polje!\n");
}

void remove_value(int i, int j, int board[9][9], int fixed[9][9])
{
    if (fixed[i][j] == 0)
        board[i][j] = 0;
    else
        printf("Ne možeš brisati zadano polje!\n");
}

int valid_row(int row, int board[9][9])
{
    int found[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val = board[row][i];
        if (val < 1 || val > 9)
            return 0;
        found[val - 1] = 1;
    }
    for (int i = 0; i < 9; i++)
        if (found[i] == 0)
            return 0;
    return 1;
}

int valid_col(int col, int board[9][9])
{
    int found[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val = board[i][col];
        if (val < 1 || val > 9)
            return 0;
        found[val - 1] = 1;
    }
    for (int i = 0; i < 9; i++)
        if (found[i] == 0)
            return 0;
    return 1;
}

int valid_block(int x, int y, int board[9][9])
{
    int found[9] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int val = board[i + 3 * x][j + 3 * y];
            if (val < 1 || val > 9)
                return 0;
            found[val - 1] = 1;
        }
    for (int i = 0; i < 9; i++)
        if (found[i] == 0)
            return 0;
    return 1;
}

int valid_diag(int board[9][9])
{
    int found_main[9] = {0};
    int found_off[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        int val1 = board[i][i];
        int val2 = board[i][8 - i];
        if (val1 < 1 || val1 > 9 || val2 < 1 || val2 > 9)
            return 0;
        found_main[val1 - 1] = 1;
        found_off[val2 - 1] = 1;
    }
    for (int i = 0; i < 9; i++)
        if (found_main[i] == 0 || found_off[i] == 0)
            return 0;
    return 1;
}

int valid_sudoku(int board[9][9])
{
    for (int i = 0; i < 9; i++)
        if (!valid_row(i, board) || !valid_col(i, board))
            return 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!valid_block(i, j, board))
                return 0;

    return 1;
}