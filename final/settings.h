#ifndef SETTINGS_H
#define SETTINGS_H

#define MAX_SORT_MODES 4
#define MAX_FMT_MODES  2

#define CSV_FMT_HEADER  ""
#define CSV_FMT_FOOTER  "\n"
#define PIPE 			'\174'

#define XML_FMT_HEADER  	"<?xml version=\"1.0\" ?>\n<tracks>"
#define XML_FMT_FOOTER  	"</tracks>"
#define XML_FMT_INIT_TABS  	1


/*PROTOTIPOS*/
status_t process_config(setting_t *, char *, char *);
status_t set_Vector_config(ADT_Vector_t *, setting_t *);
status_t set_fmt(setting_t *, char *);
status_t set_sortmode(setting_t *, char *);
status_t set_csv_context(setting_t *);
status_t set_xml_context(setting_t *);

void destructor(const void *track);

int compare_by_title(const void *track_1, const void *track_2);
int compare_by_artist(const void *track_1, const void *track_2);
int compare_by_year(const void *track_1, const void *track_2);
int compare_by_genre(const void *track_1, const void *track_2);

void print_as_csv(const void *track, void *del, FILE *fo);
void print_as_xml(const void *track, void *init_tabs, FILE *fo);
/*PROTOTIPOS*/

#endif