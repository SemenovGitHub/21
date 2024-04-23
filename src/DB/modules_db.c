#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "shared_queries.h"
#include "db_modules.h"

int main() {
    // Открыть файлы таблиц
    FILE *modules = fopen("modules.dat", "r+b");
    FILE *levels = fopen("levels.dat", "r+b");
    FILE *status_events = fopen("status_events.dat", "r+b");

    // Основной цикл программы
    while (1) {
        // Вывести меню и получить выбор пользователя
        int choice;
        printf("Please choose one operation:\n");
        printf("1. SELECT\n");
        printf("2. INSERT\n");
        printf("3. UPDATE\n");
        printf("4. DELETE\n");
        printf("5. Get all active additional modules (last module status is 1)\n");
        printf("6. Delete modules by ids\n");
        printf("7. Set protected mode for module by id\n");
        printf("8. Move module by id to specified memory level and cell\n");
        printf("9. Set protection flag of the specified memory level\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        // Выполнить соответствующую операцию
        switch (choice) {
            case 1: {
                            int table_choice;
                            printf("Please choose a table:\n");
                            printf("1. Modules\n");
                            printf("2. Levels\n");
                            printf("3. Status events\n");
                            scanf("%d", &table_choice);

                            if (table_choice == 1) {
                                int num_records;
                                printf("Insert the number of records or leave empty to output all of them: ");
                                scanf("%d", &num_records);
                                select_modules(modules, num_records);
                            } else if (table_choice == 2) {
                                int num_records;
                                printf("Insert the number of records or leave empty to output all of them: ");
                                scanf("%d", &num_records);
                                select_levels(levels, num_records);
                            } else if (table_choice == 3) {
                                int num_records;
                                printf("Insert the number of records or leave empty to output all of them: ");
                                scanf("%d", &num_records);
                                select_status_events(status_events, num_records);
                            }
                            break;
                        }
            case 2: {
                // INSERT
                break;
            }
            case 3: {
                // UPDATE
                break;
            }
            case 4: {
                // DELETE
                break;
            }
            case 5:
                get_all_active_additional_modules(modules);
                break;
            case 6: {
                // Delete modules by ids
                break;
            }
            case 7: {
                // Set protected mode for module by id
                break;
            }
            case 8: {
                // Move module by id to specified memory level and cell
                break;
            }
            case 9: {
                // Set protection flag of the specified memory level
                break;
            }
            case 0:
                // Выход
                fclose(modules);
                fclose(levels);
                fclose(status_events);
                return 0;
        }
    }
}
