#include "shared.h"
#include <stdio.h>

void select_modules(FILE *modules, int num_records) {
    fseek(modules, 0, SEEK_SET);
    Module module;
    int count = 0;

    while (fread(&module, sizeof(Module), 1, modules) == 1) {
        if (!module.is_deleted) {
            printf("%d %s %d %d %d\n", module.id, module.name, module.level_num, module.cell_num, module.is_deleted);
            count++;
            if (num_records > 0 && count >= num_records)
                break;
        }
    }
}

void insert_module(FILE *modules, FILE *levels, Module *module) {
    fseek(modules, 0, SEEK_END);
    module->id = ftell(modules) / sizeof(Module);
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
        printf("%d %d %d\n", level.level_num, level.num_cells, level.is_protected);
        count++;
        if (num_records > 0 && count >= num_records)
            break;
    }
}

void insert_level(FILE *levels, Level *level) {
    fseek(levels, 0, SEEK_END);
    level->level_num = ftell(levels) / sizeof(Level);
    fwrite(level, sizeof(Level), 1, levels);
}

void update_level(FILE *levels, int level_num, Level *updated_level) {
    fseek(levels, level_num * sizeof(Level), SEEK_SET);
    fwrite(updated_level, sizeof(Level), 1, levels);
}

void delete_level(FILE *levels, int level_num) {
    // Удаление уровня невозможно, так как это может привести к потере данных модулей
    printf("Cannot delete a level\n");
}

void select_status_events(FILE *status_events, int num_records) {
    fseek(status_events, 0, SEEK_SET);
    StatusEvent status_event;
    int count = 0;

    while (fread(&status_event, sizeof(StatusEvent), 1, status_events) == 1) {
        printf("%d %d %d %s %s\n", status_event.id, status_event.module_id, status_event.new_status, status_event.date, status_event.time);
        count++;
        if (num_records > 0 && count >= num_records)
            break;
    }
}

void insert_status_event(FILE *status_events, StatusEvent *status_event) {
    fseek(status_events, 0, SEEK_END);
    status_event->id = ftell(status_events) / sizeof(StatusEvent);
    fwrite(status_event, sizeof(StatusEvent), 1, status_events);
}

void update_status_event(FILE *status_events, int id, StatusEvent *updated_status_event) {
    fseek(status_events, id * sizeof(StatusEvent), SEEK_SET);
    fwrite(updated_status_event, sizeof(StatusEvent), 1, status_events);
}

void delete_status_event(FILE *status_events, int id) {
    // Удаление события статуса невозможно, так как это может привести к потере истории изменений
    printf("Cannot delete a status event\n");
}
