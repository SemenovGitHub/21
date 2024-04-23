#ifndef DB_MODULES_H
#define DB_MODULES_H

void get_all_active_additional_modules(FILE *modules);
void delete_modules_by_ids(FILE *modules, int *ids, int num_ids);
void set_protected_mode_for_module_by_id(FILE *modules, int id, int is_protected);
void move_module_by_id_to_specified_memory_level_and_cell(FILE *modules, FILE *levels, int id, int level_num, int cell_num);
void set_protection_flag_of_the_specified_memory_level(FILE *levels, int level_num, int is_protected);

#endif
