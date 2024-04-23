#ifndef SHARED_QUERIES_H
#define SHARED_QUERIES_H

void get_modules_by_level(FILE *modules, int level_num);
void get_levels_with_more_than_n_cells(FILE *levels, int n);
void get_status_events_for_module(FILE *status_events, int module_id);

#endif
