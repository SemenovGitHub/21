#include "shared_queries.h"
#include "shared.h"
#include <stdio.h>

void get_modules_by_level(FILE *modules, int level_num) {
    fseek(modules, 0, SEEK_SET);
    Module module;

    while (fread(&module, sizeof(Module), 1, modules) == 1) {
        if (!module.is_deleted && module.level_num == level_num) {
            printf("%d %s %d %d %d\n", module.id, module.name, module.level_num, module.cell_num, module.is_deleted);
        }
    }
}

void get_levels_with_more_than_n_cells(FILE *levels, int n) {
    fseek(levels, 0, SEEK_SET);
    Level level;

    while (fread(&level, sizeof(Level), 1, levels) == 1) {
        if (level.num_cells > n) {
            printf("%d %d %d\n", level.level_num, level.num_cells, level.is_protected);
        }
    }
}

void get_status_events_for_module(FILE *status_events, int module_id) {
    fseek(status_events, 0, SEEK_SET);
    StatusEvent status_event;

    while (fread(&status_event, sizeof(StatusEvent), 1, status_events) == 1) {
        if (status_event.module_id == module_id) {
            printf("%d %d %d %s %s\n", status_event.id, status_event.module_id, status_event.new_status, status_event.date, status_event.time);
        }
    }
}
