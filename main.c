#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 1024

typedef struct
{
    int key;
    char value[100];
} DICT;

enum week { Sun = 0, Mon, Tue, Wed, Thur, Fri, Sat };

struct Node
{
    char *jam;
    struct Node *next;
};

void add_jadwal(char *jam);
void print_jadwal();
int dayofweek(int d, int m, int y);
char *get_hari(enum week hari);

struct Node *tail;

int main()
{
    DICT list[100];
    int counter = 0;
    tail = NULL;

    FILE *file = fopen("sample-data.csv", "r");
    char lines[MAX_SIZE];
    int row = 0;
    int column = 0;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int d = tm->tm_mday;
    int m = tm->tm_mon + 1;
    int y = tm->tm_year + 1900;
    int day = dayofweek(d, m, y);

    while (fgets(lines, 1024, file))
    {
        column = 0;
        row++;

        if (row == 1)
        {
            continue;
        }

        char *value = strtok(lines, ",");
        // enum week today = Mon;

        while (value)
        {
            column++;

            char *baris_hari = get_hari(row - 1);
            char *hari_ini = get_hari(day);

            // Notes:
            // column > 1  = lewati kolom pertama
            if (baris_hari == hari_ini && column > 1)
            {
                list[counter].key = counter;
                strcpy(list[counter].value, value);
                counter++;
            }

            value = strtok(NULL, ",");
        }
    }

    fclose(file);
    
    for (int i = 0; i < 3; i++)
    {
        printf("(%d) => %s\n", list[i].key, list[i].value);
    }

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

}

char *get_hari(enum week hari)
{
    // enum week { Sun = 0, Mon, Tue, Wed, Thur, Fri, Sat };
    // enum is zero based index (0, 1, 2, 3, 4, 5, 6)

    switch (hari)
    {
    case Sun:
        return "Minggu";
    case Mon:
        return "Senin";
    case Tue:
        return "Selasa";
    case Wed:
        return "Rabu";
    case Thur:
        return "Kamis";
    case Fri:
        return "Jumat";
    case Sat:
        return "Sabtu";
    }
}

int dayofweek(int d, int m, int y)
{
    // Minggu = 0, Senin, Selasa, Rabu, Kamis, Jumat, Sabtu

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
