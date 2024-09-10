#ifndef __MLD__
#define __MLD__
#include <stdint.h>

#include <assert.h>

/* Defines for maximum sizes of structure and field names */
#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

/* Enumerations for supported data types in structures */
typedef enum {
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
} data_type_t;

/* Macros to compute the offset and size of a structure field */
#define OFFSETOF(struct_name, fld_name)     \
    ((uintptr_t)&(((struct_name *)0)->fld_name))

#define FIELD_SIZE(struct_name, fld_name)   \
    sizeof(((struct_name *)0)->fld_name)

/* Forward declaration of the structure database record type */
typedef struct _struct_db_rec_t struct_db_rec_t;

/* Structure to hold information about a field in a C struct */
typedef struct _field_info_{
    char fname[MAX_FIELD_NAME_SIZE];   /* Name of the field */
    data_type_t dtype;                 /* Data type of the field */
    unsigned int size;                 /* Size of the field */
    unsigned int offset;               /* Offset of the field */
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE]; /* Name of nested structure if field is a struct or pointer to struct */
} field_info_t;

/* Structure to hold metadata for a C structure including its fields */
struct _struct_db_rec_t{
    struct_db_rec_t *next; /* Next structure in the linked list */
    char struct_name[MAX_STRUCTURE_NAME_SIZE]; /* Name of the structure */
    unsigned int ds_size;  /* Total size of the structure */
    unsigned int n_fields; /* Number of fields in the structure */
    field_info_t *fields;  /* Array of field metadata */
};

/* Head of the linked list that forms the structure database */
typedef struct _struct_db_{
    struct_db_rec_t *head;
    unsigned int count;
} struct_db_t;

/* Declarations of functions for printing and managing the structure database */
void print_structure_rec(struct_db_rec_t *struct_rec);
void print_structure_db(struct_db_t *struct_db);
int add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

/* Macros to simplify registration of structures and their fields */
#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)    \
   {#fld_name, dtype, FIELD_SIZE(struct_name, fld_name),                \
        OFFSETOF(struct_name, fld_name), #nested_struct_name} 

#define REG_STRUCT(struct_db, st_name, fields_arr)                    \
    do{                                                               \
        struct_db_rec_t *rec = calloc(1, sizeof(struct_db_rec_t));    \
        strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE); \
        rec->ds_size = sizeof(st_name);                               \
        rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);      \
        rec->fields = fields_arr;                                     \
        if(add_structure_to_struct_db(struct_db, rec)){               \
            assert(0);                                                \
        }                                                             \
    }while(0);

#endif /* __MLD__ */
