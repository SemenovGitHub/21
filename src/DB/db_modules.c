#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "shared_queries.h"
#include "db_modules.h"

void get_all_active_additional_modules(FILE *modules) {
    fseek(modules, 0, SEEK_SET);
    Module module;

    while (fread(&module, sizeof(Module), 1, modules) == 1) {
        if (!module.is_deleted && module.id != 0) {
            printf("%d %s %d %d %d\n", module.id, module.name, module.level_num, module.cell_num, module.is_deleted);
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
    Module module;
    fseek(modules, id * sizeof(Module), SEEK_SET);
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
