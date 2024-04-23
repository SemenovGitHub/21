#ifndef SHARED_H
#define SHARED_H

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

#endif
