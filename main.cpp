#include <iostream>
#include <cstdio>
#include <string>
#include "stdio.h"
#include "stdlib.h"

using namespace std;

void PrintCharField(char *input) {
    int i = 0;
    while (input[i] != '\0') {
        printf("%c", input[i]);
        i++;
    }
    printf("\n");
}

char *LoadStringInput() {
    char *input = (char *) malloc(1 * sizeof(char));
    if (input == NULL) {
        printf("No memory\n");
        exit(100);
    }

    int i = 0;
    char symbol;
    while (1) {
        scanf("%c", &symbol);
        if (symbol == '\r' || symbol == '\n' || symbol == EOF)
            break;

        input[i] = symbol;

        input = (char *) realloc(input, i + 2 * sizeof(char));
        if (input == NULL) {
            printf("No memory\n");
            exit(100);
        }

        i++;
    }

    return input;
}

char *LoadFirstWordFromStringInput(char *input) {
    int i = 0;
    int start = 0;
    bool setStart = false;
    int end = 0;
    while (1) {
        if (input[i] != ' ' && setStart == false) {
            start = i;
            setStart = true;
        }

        if (setStart == true) {
            if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n' || input[i] == '\r' || input[i] == EOF) {
                end = i;
                break;
            }
        }

        if (input[i] == '\n' || input[i] == '\0' || input[i] == '\r' || input[i] == EOF)
            break;
        i++;
    }

    char *word = (char *) calloc((end - start), sizeof(char));
    if (word == NULL) {
        printf("No memory\n");
        exit(100);
    }

    int j = 0;
    for (start; start < end; start++) {
        word[j] = input[start];
        j++;
    }

    return word;
}

typedef enum {
    STRING = 1, INTEGER = 2, FLOAT = 3, BOOL = 4
} DataType;

DataType ChooseType(char *word) {
    int length = 0;
    while (1) {
        if (word[length] == '\n' || word[length] == '\0' || word[length] == '\r' ||
            word[length] == EOF || word[length] == ' ')
            break;
        length++;
    }

    int numbers = 0;
    int dots = 0;
    int otherSymbols = 0;
    int marks = 0;
    for (int i = 0; i < length; i++) {
        if (word[i] >= 48 && word[i] <= 57)
            numbers++;
        else if (word[i] == '.')
            dots++;
        else if (word[i] == '+' || word[i] == '-')
            marks++;
        else
            otherSymbols++;
    }

    if ((word[0] == '+' || word[0] == '-') && marks == 1) {
        if (numbers == length - 1)
            return INTEGER;
        else if (numbers == length - 2 && dots == 1 && word[1] != '.')
            return FLOAT;
        else
            return STRING;
    }

    if (numbers == length)
        return INTEGER;
    else if (numbers == length - 1 && dots == 1 && word[0] != '.')
        return FLOAT;
    else if ((length == 4 && word[0] == 't' && word[1] == 'r' && word[2] == 'u' && word[3] == 'e')
             || (length == 5 && word[0] == 'f' && word[1] == 'a' && word[2] == 'l' && word[3] == 's' && word[4] == 'e'))
        return BOOL;
    else
        return STRING;
}

void PrintDataType(DataType type) {
    printf("DataType is: ");
    if (type == STRING)
        printf("STRING");
    else if (type == INTEGER)
        printf("INTEGER");
    else if (type == FLOAT)
        printf("FLOAT");
    else
        printf("BOOL");
    printf("\n");
}

double ConvertInputToDouble(char *input) {
    int length = 0;
    while (1) {
        if (input[length] == '\n' || input[length] == '\0' || input[length] == '\r' ||
            input[length] == EOF || input[length] == ' ')
            break;
        length++;
    }

    if (input[0] == '+' || input[0] == '-') {
        int mark = 1;
        if (input[0] == '-')
            mark = -1;

        int dotPosition = 0;
        for (int i = 0; i < length; i++) {
            if (input[i] == '.')
                dotPosition = i;
        }

        double value = 0;
        for (int i = dotPosition - 1; i > 0; i--) {
            int multiple = 1;
            for (int j = 0; j < dotPosition - i - 1; j++)
                multiple *= 10;
            value += (input[i] - 48) * multiple;
        }

        for (int i = length - 1; i > dotPosition; i--) {
            double multiple = 1;
            for (int j = 0; j < i - dotPosition; j++)
                multiple = multiple / 10;
            value += (input[i] - 48) * multiple;
        }
        value = value * mark;

        return value;
    }

    int dotPosition = 0;
    for (int i = 0; i < length; i++) {
        if (input[i] == '.')
            dotPosition = i;
    }

    double value = 0;
    for (int i = dotPosition - 1; i > -1; i--) {
        int multiple = 1;
        for (int j = 0; j < dotPosition - i - 1; j++)
            multiple *= 10;
        value += (input[i] - 48) * multiple;
    }

    for (int i = length - 1; i > dotPosition; i--) {
        double multiple = 1;
        for (int j = 0; j < i - dotPosition; j++)
            multiple = multiple / 10;
        value += (input[i] - 48) * multiple;
    }

    return value;
}

int ConvertInputToInteger(char *input) {
    int length = 0;
    while (1) {
        if (input[length] == '\n' || input[length] == '\0' || input[length] == '\r' ||
            input[length] == EOF || input[length] == ' ')
            break;
        length++;
    }

    if (input[0] == '+' || input[0] == '-') {
        int mark = 1;
        if (input[0] == '-')
            mark = -1;

        int value = 0;
        for (int i = length - 1; i > 0; i--) {
            int multiple = 1;
            for (int j = 0; j < length - i - 1; j++)
                multiple *= 10;
            value += (input[i] - 48) * multiple;
        }

        value = value * mark;

        return value;
    }

    int value = 0;
    for (int i = length - 1; i > -1; i--) {
        int multiple = 1;
        for (int j = 0; j < length - i - 1; j++)
            multiple *= 10;
        value += (input[i] - 48) * multiple;
    }
    return value;
}

bool ConvertStringToBool(char *input) {
    int length = 0;
    while (1) {
        if (input[length] == '\n' || input[length] == '\0' || input[length] == '\r' ||
            input[length] == EOF || input[length] == ' ')
            break;
        length++;
    }

    if (length == 4 && input[0] == 't' && input[1] == 'r' && input[2] == 'u' && input[3] == 'e')
        return true;
    else if (length == 5 && input[0] == 'f' && input[1] == 'a' && input[2] == 'l' && input[3] == 's' && input[4] == 'e')
        return false;
}

int main() {

    char *lineInput = LoadStringInput();
    char *input = LoadFirstWordFromStringInput(lineInput);

    DataType type = ChooseType(input);

    if (type == INTEGER) {
        int Ivalue = ConvertInputToInteger(input);
        PrintDataType(type);
        printf("Value is: %d\n", Ivalue);
    } else if (type == FLOAT) {
        double Dvalue = ConvertInputToDouble(input);
        PrintDataType(type);
        printf("Value is: %f\n", Dvalue);
    } else if (type == BOOL) {
        bool Bvalue = ConvertStringToBool(input);
        PrintDataType(type);
        if (Bvalue)
            printf("Value is: true\n");
        else
            printf("Value is: false\n");
    } else {
        PrintDataType(type);
        printf("Value is: %s\n", input);
    }

    return 0;
}
