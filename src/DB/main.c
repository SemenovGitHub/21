#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    int level_num;
    int cell_num;
    int is_deleted;
} Module;

typedef struct {
    int level_num;
    int num_cells;
    int is_protected;
} Level;

typedef struct {
    int id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} StatusEvent;

void select_modules(FILE *modules, int num_records);
void insert_module(FILE *modules, FILE *levels, Module *module);
void update_module(FILE *modules, int id, Module *updated_module);
void delete_module(FILE *modules, int id);

void select_levels(FILE *levels, int num_records);
void insert_level(FILE *levels, Level *level);
void update_level(FILE *levels, int level_num, Level *updated_level);
void delete_level(FILE *levels, int level_num);

void select_status_events(FILE *status_events, int num_records);
void insert_status_event(FILE *status_events, StatusEvent *status_event);
void update_status_event(FILE *status_events, int id, StatusEvent *updated_status_event);
void delete_status_event(FILE *status_events, int id);

void get_all_active_additional_modules(FILE *modules);
void delete_modules_by_ids(FILE *modules, int *ids, int num_ids);
void set_protected_mode_for_module_by_id(FILE *modules, int id, int is_protected);
void move_module_by_id_to_specified_memory_level_and_cell(FILE *modules, FILE *levels, int id, int level_num, int cell_num);
void set_protection_flag_of_the_specified_memory_level(FILE *levels, int level_num, int is_protected);

void insert_module_data(FILE *modules, FILE *levels) {
    Module module;
    printf("Enter module name: ");
    scanf("%s", module.name);
    printf("Enter level number: ");
    scanf("%d", &module.level_num);
    printf("Enter cell number: ");
    scanf("%d", &module.cell_num);
    module.is_deleted = 0;
    insert_module(modules, levels, &module);
}

void update_module_data(FILE *modules) {
    int id;
    printf("Enter module id to update: ");
    scanf("%d", &id);
    Module updated_module;
    printf("Enter new module name: ");
    scanf("%s", updated_module.name);
    printf("Enter new level number: ");
    scanf("%d", &updated_module.level_num);
    printf("Enter new cell number: ");
    scanf("%d", &updated_module.cell_num);
    updated_module.is_deleted = 0;
    update_module(modules, id, &updated_module);
}

void delete_modules_by_ids(FILE *modules) {
    int num_ids;
    printf("Enter the number of module ids to delete: ");
    scanf("%d", &num_ids);
    int *ids = (int*)malloc(num_ids * sizeof(int));
    for (int i = 0; i < num_ids; i++) {
        printf("Enter module id #%d: ", i + 1);
        scanf("%d", &ids[i]);
    }
    for (int i = 0; i < num_ids; i++) {
        delete_module(modules, ids[i]);
    }
    free(ids);
}

void set_protected_mode_for_module(FILE *modules) {
    int id;
    printf("Enter module id: ");
    scanf("%d", &id);
    int is_protected;
    printf("Enter new protected mode (0 or 1): ");
    scanf("%d", &is_protected);
    set_protected_mode_for_module_by_id(modules, id, is_protected);
}

void select_modules(FILE *modules, int num_records) {
    fseek(modules, 0, SEEK_SET);
    Module module;
    int count = 0;

    while (fread(&module, sizeof(Module), 1, modules) == 1) {
        if (!module.is_deleted) {
            printf("ID: %d\n", module.id);
            printf("Name: %s\n", module.name);
            printf("Level Number: %d\n", module.level_num);
            printf("Cell Number: %d\n", module.cell_num);
            printf("Deleted: %s\n\n", module.is_deleted ? "Yes" : "No");
            count++;
            if (num_records > 0 && count >= num_records)
                break;
        }
    }
}

void insert_module(FILE *modules, FILE *levels, Module *module) {
    fseek(modules, 0, SEEK_END);
    module->id = (int)ftell(modules) / sizeof(Module);
    fwrite(module, sizeof(Module), 1, modules);
}

void update_module(FILE *modules, int id, Module *updated_module) {
    fseek(modules, id * sizeof(Module), SEEK_SET);
    fwrite(updated_module, sizeof(Module), 1, modules);
}

void delete_module(FILE *modules, int id) {
    fseek(modules, id * sizeof(Module), SEEK_SET);
    Module module;
    fread(&module, sizeof(Module), 1, modules);
    module.is_deleted = 1;
    fseek(modules, -sizeof(Module), SEEK_CUR);
    fwrite(&module, sizeof(Module), 1, modules);
}

void select_levels(FILE *levels, int num_records) {
    fseek(levels, 0, SEEK_SET);
    Level level;
    int count = 0;

    while (fread(&level, sizeof(Level), 1, levels) == 1) {
        printf("Level Number: %d\n", level.level_num);
        printf("Number of Cells: %d\n", level.num_cells);
        printf("Protected: %s\n\n", level.is_protected ? "Yes" : "No");
        count++;
        if (num_records > 0 && count >= num_records)
            break;
    }
}

void insert_level(FILE *levels, Level *level) {
    fseek(levels, 0, SEEK_END);
    level->level_num = (int)ftell(levels) / sizeof(Level);
    fwrite(level, sizeof(Level), 1, levels);
}

void update_level(FILE *levels, int level_num, Level *updated_level) {
    fseek(levels, level_num * sizeof(Level), SEEK_SET);
    fwrite(updated_level, sizeof(Level), 1, levels);
}

void delete_level(FILE *levels, int level_num) {
    // Удаление уровня не поддерживается
}

void select_status_events(FILE *status_events, int num_records) {
    fseek(status_events, 0, SEEK_SET);
    StatusEvent status_event;
    int count = 0;

    while (fread(&status_event, sizeof(StatusEvent), 1, status_events) == 1) {
        printf("ID: %d\n", status_event.id);
        printf("Module ID: %d\n", status_event.module_id);
        printf("New Status: %d\n", status_event.new_status);
        printf("Date: %s\n", status_event.date);
        printf("Time: %s\n\n", status_event.time);
        count++;
        if (num_records > 0 && count >= num_records)
            break;
    }
}

void insert_status_event(FILE *status_events, StatusEvent *status_event) {
    fseek(status_events, 0, SEEK_END);
    status_event->id = (int)ftell(status_events) / sizeof(StatusEvent);
    fwrite(status_event, sizeof(StatusEvent), 1, status_events);
}

void update_status_event(FILE *status_events, int id, StatusEvent *updated_status_event) {
    fseek(status_events, id * sizeof(StatusEvent), SEEK_SET);
    fwrite(updated_status_event, sizeof(StatusEvent), 1, status_events);
}

void delete_status_event(FILE *status_events, int id) {
    // Удаление события статуса не поддерживается
}

void get_all_active_additional_modules(FILE *modules) {
    fseek(modules, 0, SEEK_SET);
    Module module;

    while (fread(&module, sizeof(Module), 1, modules) == 1) {
        if (!module.is_deleted && module.id != 0) {
            printf("ID: %d\n", module.id);
            printf("Name: %s\n", module.name);
            printf("Level Number: %d\n", module.level_num);
            printf("Cell Number: %d\n", module.cell_num);
            printf("Deleted: %s\n\n", module.is_deleted ? "Yes" : "No");
        }
    }
}

void delete_modules_by_ids(FILE *modules, int *ids, int num_ids) {
    for (int i = 0; i < num_ids; i++) {
        delete_module(modules, ids[i]);
    }
    printf("Modules marked as deleted\n");
}

void set_protected_mode_for_module_by_id(FILE *modules, int id, int is_protected) {
    fseek(modules, id * sizeof(Module), SEEK_SET);
    Module module;
    fread(&module, sizeof(Module), 1, modules);
    module.is_deleted = is_protected;
    fseek(modules, -sizeof(Module), SEEK_CUR);
    fwrite(&module, sizeof(Module), 1, modules);
}

void move_module_by_id_to_specified_memory_level_and_cell(FILE *modules, FILE *levels, int id, int level_num, int cell_num) {
    Module module;
    fseek(modules, id * sizeof(Module), SEEK_SET);
    fread(&module, sizeof(Module), 1, modules);

    if (module.is_deleted) {
        printf("Module is deleted\n");
        return;
    }

    Level level;
    fseek(levels, level_num * sizeof(Level), SEEK_SET);
    fread(&level, sizeof(Level), 1, levels);

    if (level.is_protected) {
        printf("Level is protected\n");
        return;
    }

    module.level_num = level_num;
    module.cell_num = cell_num;
    fseek(modules, -sizeof(Module), SEEK_CUR);
    fwrite(&module, sizeof(Module), 1, modules);
}

void set_protection_flag_of_the_specified_memory_level(FILE *levels, int level_num, int is_protected) {
    Level level;
    fseek(levels, level_num * sizeof(Level), SEEK_SET);
    fread(&level, sizeof(Level), 1, levels);
    level.is_protected = is_protected;
    fseek(levels, -sizeof(Level), SEEK_CUR);
    fwrite(&level, sizeof(Level), 1, levels);
}

int main() {
    FILE *modules = fopen("/Users/nikitasemenov/C/test/modules.dat", "r+b");
    FILE *levels = fopen("/Users/nikitasemenov/C/test/levels.dat", "r+b");
    FILE *status_events = fopen("/Users/nikitasemenov/C/test/status_events.dat", "r+b");

    if (!modules || !levels || !status_events) {
        printf("Error opening files.\n");
        return 1;
    }

    int choice;

    while (1) {
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
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int table_choice;
                printf("Please choose a table:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("Enter your choice: ");
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
            case 2:
                insert_module_data(modules, levels);
                break;
            case 3:
                update_module_data(modules);
                break;
            case 4: {
                int table_choice;
                printf("Please choose a table:\n");
                printf("1. Modules\n");
                printf("2. Levels\n");
                printf("3. Status events\n");
                printf("Enter your choice: ");
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
                fclose(modules);
                fclose(levels);
                fclose(status_events);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

//    fclose(modules);
//    fclose(levels);
//    fclose(status_events);

    return 0;
}
