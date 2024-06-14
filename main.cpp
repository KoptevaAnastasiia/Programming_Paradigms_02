#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 100

class Program {
public:
    char *input;

    Program() {
        input = (char *)
        malloc(BUFFER_SIZE * sizeof(char));
        if (input == NULL) {
            printf("Помилка виділення пам'яті.\n");
            exit(1);
        }
        input[0] = '\0';
    }

    void add_text(char *input, size_t bufferSize);
    void start_newline(char *input);
    void search_substring(char *input);
    void insert_text(char *input);
    void save_to_file(char *input);
     void free_input();
};
void Program::add_text(char *input, size_t bufferSize) {
    printf("Enter the text : ");
    fflush(stdout);   // оч буфету обміну

    char text[BUFFER_SIZE];

    if (fgets(text, BUFFER_SIZE, stdin) == NULL) {
        printf("Помилка читання рядка.\n");
        return;
    }
    strncat(input, text, bufferSize - strlen(input) - 1);  // Додаємо новий рядок до існуючого тексту
}

void Program::start_newline(char *input){
    strncat(input, "\n", BUFFER_SIZE - strlen(input) - 1);
    printf("New line is started\n");
}

void Program::search_substring(char *input) {
    char substring[BUFFER_SIZE];
    printf("Enter the substring to search: ");
    fgets(substring, BUFFER_SIZE, stdin);

    // substring[strcspn(substring, "\n")] = '\0';  // Видалення символу нового рядка




    int line = 0;
    int column = 0;
    int num_matches = 0 ;



    int o = 0 ;
    int p = 0;


    // int i = 0;
    // for(i ; substring[i] != '\0' ; i++) {
    //     if (substring[i] == '\n') {
    //         substring[i] = '\0';
    //         break;
    //     }
    // }

    int l = 0 ;

    while (l- 1 != strlen(input) ) {
        if (input[p] == '\n') {
            line++;
            column = 0;
        }else {
            column++;
        }

        if (substring[o] != input[p]) {
            p++;
            column++;
            num_matches = 0;
            o = 0;
        }
        else {
            p++;
            o++;
            num_matches++;
        }

        if (num_matches == strlen(substring)) {
            printf(" ( %d,%d )", line, column );
            num_matches = 0;
            o = 0;
        }
        l++;
    }

}


void Program::insert_text(char *input) {

    char substring[BUFFER_SIZE];
    int line, index;
    printf("Enter the line and index: ");


    scanf("%d %d", &line, &index);
    getchar();

    // після scanf, коли користувач натискає клавішу "Enter", символ нового рядка (\n) залишається у буфері вводу.
    //  getchar видаляє символ нововго рядка з буфету


    printf("Enter text to insert: ");
    fgets(substring, BUFFER_SIZE, stdin);


    if (substring[strlen(substring) - 1] == '\n') {
        substring[strlen(substring)- 1] = '\0';

    }

    int current_line = 0;
    int current_index = 0;


    char *position = input;


    while (current_line < line && *position != '\0') {
        if (*position == '\n') {
            current_line++;
        }
        position++;
    }

    if (current_line == line) {
        while (current_index < index && *position != '\n' && *position != '\0') {
            position++;
            current_index++;

            char result[BUFFER_SIZE];
            char input_00[BUFFER_SIZE];
            char input_01[BUFFER_SIZE];

            snprintf(input_00, position - input + 1 , "%s", input);
            input_00[position - input] = '\0';


            snprintf(input_01, sizeof(input_01), "%s", position);



            snprintf(result, sizeof(result), "%s%s%s", input_00, substring , input_01);

            printf("Result :  %s", result);


            snprintf(input, BUFFER_SIZE, "%s", result);



        }
    }


}

void Program::save_to_file(char *input) {
    char filename[FILENAME_SIZE];
    printf("Введіть назву файлу для збереження: ");
    if ( fgets     (filename,   sizeof(filename),    stdin) != NULL) {
        filename[strlen(filename) - 1] = '\0';
    }


    FILE* file = fopen64(filename, "w+x");  // 64 for big filles  and add +x

    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return;
    }
    else {

        fprintf(file, "%s", input);      //Функція fprintf () записує вихідні дані в потік, визначений fp , під керуванням специфікатора формату


        fclose(file);   // звільняє ресурси
        printf("Текст було записано у файл успішно.\n");
    }

}


void Program::free_input() {
    free(input);
}


int main() {
    Program program;
    int choice;

    do {
        printf("\n==============================\n");
        printf(" Виберіть команду:\n");
        printf("1. Ввести текст для додавання\n");
        printf("2. Почати нову строку\n");
        printf("3. Ввести ім'я файлу для збереження\n");
        printf("4. Ввести ім'я файлу для завантаження\n");
        printf("5. Надрукувати поточний текст на консоль\n");
        printf("6. Вставити підстроку\n");
        printf("7. Пошук позиції підстроки\n");
        printf("8. Видалити файл\n");
        printf("0. Вихід\n");
        printf("===============================\n");
        printf("Введіть ваш вибір: ");
        char choice_str[3];
        fgets(choice_str, sizeof(choice_str), stdin);

        if (choice_str[1] != '\n') {
            printf("Неправильний вибір.\n");
            break;
        }

        choice = choice_str[0] - '0';  // Перетворення символу в число

        switch (choice) {
            case 1:
                program.add_text( program.input, BUFFER_SIZE );
                break;
            case 2:
                program.start_newline(program.input);
                break;
            case 3:
                program.save_to_file(program.input);
                break;
            case 4:

                break;
            case 5:
                printf("Поточний текст: %s\n", program.input);
                break;
            case 6:
                program.insert_text(program.input);
                break;
            case 7:
                program.search_substring(program.input);
                break;
            case 8:
                // printf("Введіть ім'я файлу для видалення: ");
                // char filename[FILENAME_SIZE];
                // fgets(filename, FILENAME_SIZE, stdin);
                // filename[strcspn(filename, "\n")] = '\'\0';
                // if (remove(filename) == 0) {
                //     printf("Файл успішно видалено.\n");
                // } else {
                //     printf("Помилка видалення файлу.\n");
                // }
                // break;
            case 0:
                program.free_input();
                break;
            default:
                printf("Неправильний вибір.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
