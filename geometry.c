#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YELLOW "\e[5;33m"
#define END "\e[0m"
#define MAX 100

struct point {
    double x;
    double y;
};

struct circle {
    struct point center;
    double radius;
};

enum BUGS {
    BUG_NAME,
    BUG_STAPLES,
    BUG_NUMBER,
    BUG_UNIDENTIFIED_VARIABLES,
    BUG_EXPECT_COMMA,
};

void all_BUGS(int BUGS, int num, char* ch)
{
    for (int i = 0; i < num; i++) {
        putchar(' ');
    }
    printf("^\n");

    switch (BUGS) {
    case BUG_NAME:
        printf("An error %d was found in the input line %s'circle'%s\n",
               num,
               YELLOW,
               END);
        break;
    case BUG_STAPLES:
        if (*ch == ')') {
            printf("An error %d was found in the input line %s')'%s\n",
                   num,
                   YELLOW,
                   END);
            break;
        } else {
            printf("An error %d was found in the input line %s'('%s\n",
                   num,
                   YELLOW,
                   END);
            break;
        }
    case BUG_NUMBER:
        printf("An error %d was found in the input line %s'double'%s\n",
               num,
               YELLOW,
               END);
        break;
    case BUG_UNIDENTIFIED_VARIABLES:
        printf("An error %d was found in the input line %s'variable'%s\n",
               num,
               YELLOW,
               END);
        break;
    case BUG_EXPECT_COMMA:
        printf("An error %d was found in the input line %s','%s\n",
               num,
               YELLOW,
               END);
        break;
    }
}

void to_lower(char* str, int ch)
{
    for (int i = 0; i < ch; i++) {
        str[i] = tolower(str[i]);
    }
}

double x_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == '(' || arr[*num] == ' ') {
            *num += 1;
        } else {
            if (arr[*num] == ')') {
                all_BUGS(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            } else {
                all_BUGS(BUG_NUMBER, *num, NULL);
                exit(1);
            }
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }
    if (arr[*num] != ' ') {
        all_BUGS(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
        exit(1);
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

double y_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            all_BUGS(BUG_NUMBER, *num, NULL);
            exit(1);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ',') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            all_BUGS(BUG_EXPECT_COMMA, *num, NULL);
            exit(1);
        }
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

double radius_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num])) {
        if (arr[*num] == ' ' || arr[*num] == ',') {
            *num += 1;
        } else {
            all_BUGS(BUG_NUMBER, *num, NULL);
            exit(1);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ')') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            if (arr[*num] == '(') {
                all_BUGS(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            } else {
                all_BUGS(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
                exit(1);
            }
        }
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

void empty(char* arr, int* num)
{
    *num += 1;
    while (arr[*num] != '\n' && arr[*num] != EOF) {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            all_BUGS(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
            exit(1);
        }
    }
}

struct point find_center(char* arr, int* num)
{
    struct point Center;

    Center.x = x_data(arr, num);
    Center.y = y_data(arr, num);

    return Center;
}

struct circle find_out_circle(struct point* Center, char* arr, int* num)
{
    struct circle CIRCLE;

    CIRCLE.center.x = Center->x;
    CIRCLE.center.y = Center->y;
    CIRCLE.radius = radius_data(arr, num);

    return CIRCLE;
}

void output_circle_message(struct circle* CIRCLE)
{
    printf("\ncircle(%.2f %.2f, %.2f)\n",
           CIRCLE->center.x,
           CIRCLE->center.y,
           CIRCLE->radius);
    printf("perimeter: %.4f\n", (2 * 3.1415926535 * CIRCLE->radius));
    printf("area: %.4f\n", ((CIRCLE->radius * CIRCLE->radius) * 3.1415926535));
}

int main()
{
    char enter[MAX], shape[MAX];
    int num = 0;

    printf("Enter the name and coordinates of the shape (or press Enter for "
           "exit):\n");
    fgets(enter, MAX, stdin);

    for (int i = 0; i < strlen(enter); i++) {
        if (enter[i] == '(' || enter[i] == ' ') {
            to_lower(shape, num);
            if (strcmp(shape, "circle") == 0) {
                struct point Center = find_center(enter, &num);
                struct circle CIRCLE = find_out_circle(&Center, enter, &num);
                empty(enter, &num);
                output_circle_message(&CIRCLE);
                break;
            } else {
                all_BUGS(BUG_NAME, 0, NULL);
                exit(1);
            }
        } else if (enter[i] == ')') {
            all_BUGS(BUG_STAPLES, num, &enter[i]);
            exit(1);
        }

        shape[num] = enter[i];
        num++;
    }

    return 0;
}
