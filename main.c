#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct Node
{
    char *jam;
    struct Node *next;
};

void add_jadwal(char *jam);
void print_jadwal();
int dayofweek(int d, int m, int y);
char *get_hari(int hari);

struct Node *tail;

int main()
{
    tail = NULL;
    // add_jadwal("07:00");
    // add_jadwal("10:00");
    // add_jadwal("13:00");
    // print_jadwal();

    FILE *file = fopen("sample-data.csv", "r");
    char line[1024];
    int row = 0;
    int column = 0;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int d = tm->tm_mday;
    int m = tm->tm_mon + 1;
    int y = tm->tm_year + 1900;
    int day = dayofweek(d, m, y);
    // printf("The time is %s\n", get_hari(day));

    while (fgets(line, 1024, file))
    {
        column = 0;
        row++;

        if (row == 1)
        {
            continue;
        }

        char *value = strtok(line, ",");

        while (value != NULL)
        {
            column++;

            char *baris_hari = get_hari(row - 1);
            char *hari_ini = get_hari(day);

            // Notes:
            // column > 1  = lewati kolom pertama
            if (baris_hari == hari_ini && column > 1)
            {
                add_jadwal(value);
                // printf("%s ", value);
            }

            value = strtok(NULL, ",");
        }

        printf("\n");
    }

    fclose(file);
    print_jadwal();
    

    return 0;
}

void print_jadwal()
{
    struct Node *temp = tail;

    while (temp != NULL)
    {
        printf("%s->", temp->jam);
        temp = temp->next;
    }

    printf("NULL\n");
}

void add_jadwal(char *jam)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->jam = jam;
    temp->next = NULL;

    if (tail == NULL)
    {
        tail = temp;
    }
    else
    {
        struct Node *node = tail;

        while (node->next != NULL)
        {
            node = node->next;
        }

        node->next = temp;
    }

    // free(temp);
}

char *get_hari(int hari)
{
    switch (hari)
    {
    case 0:
        return "Minggu";
    case 1:
        return "Senin";
    case 2:
        return "Selasa";
    case 3:
        return "Rabu";
    case 4:
        return "Kamis";
    case 5:
        return "Jumat";
    case 6:
        return "Sabtu";
    }
}

int dayofweek(int d, int m, int y)
{
    /*
     * 0 = Minggu
     * 1 = Senin
     * 2 = Selasa
     * 3 = Rabu
     * 4 = Kamis
     * 5 = Jumat
     * 6 = Sabtu
     */

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
