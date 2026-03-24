#define SENSOR_COUNT 20

void data_init(const char* o_filename, const char* n_filename);
void data_print(const char* filename);
void data_edit(const char* filename, const char* oid, const char* name, const char* status);
void data_active_print(const char* filename);
