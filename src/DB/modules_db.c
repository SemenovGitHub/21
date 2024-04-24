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
                            insert_module_data(modules, levels);
                            break;
                        }
                        case 3: {
                            update_module_data(modules);
                            break;
                        }
                        case 4: {
                            int table_choice;
                            printf("Please choose a table:\n");
                            printf("1. Modules\n");
                            printf("2. Levels\n");
                            printf("3. Status events\n");
                            scanf("%d", &table_choice);

                            if (table_choice == 1) {
                                int id;
                                printf("Enter module id to delete: ");
                                scanf("%d", &id);
                                delete_module(modules, id);
                            } else if (table_choice == 2) {
                                int level_num;
                                printf("Enter level number to delete: ");
                                scanf("%d", &level_num);
                                delete_level(levels, level_num);
                            } else if (table_choice == 3) {
                                int id;
                                printf("Enter status event id to delete: ");
                                scanf("%d", &id);
                                delete_status_event(status_events, id);
                            }
                            break;
                        }
                        case 5:
                            get_all_active_additional_modules(modules);
                            break;
                        case 6:
                            delete_modules_by_ids(modules);
                            break;
                        case 7:
                            set_protected_mode_for_module(modules);
                            break;
                        case 8: {
                            int id, level_num, cell_num;
                            printf("Enter module id: ");
                            scanf("%d", &id);
                            printf("Enter new level number: ");
                            scanf("%d", &level_num);
                            printf("Enter new cell number: ");
                            scanf("%d", &cell_num);
                            move_module_by_id_to_specified_memory_level_and_cell(modules, levels, id, level_num, cell_num);
                            break;
                        }
                        case 9: {
                            int level_num;
                            printf("Enter level number: ");
                            scanf("%d", &level_num);
                            int is_protected;
                            printf("Enter new protection flag (0 or 1): ");
                            scanf("%d", &is_protected);
                            set_protection_flag_of_the_specified_memory_level(levels, level_num, is_protected);
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
