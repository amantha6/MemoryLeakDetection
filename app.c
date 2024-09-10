#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>

/* Application Structures */
typedef struct emp_ {
    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
} emp_t;

typedef struct student_ {
    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleague;
} student_t;

/* Declare global object db */
object_db_t *global_object_db = NULL;

int main(int argc, char **argv) {
    /* Step 1: Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    
    /* Step 2: Create structure record for structure emp_t */
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0)
    };
    /* Register the structure in the structure database */
    REG_STRUCT(struct_db, emp_t, emp_fields);

    /* Create structure record for structure student_t */
    static field_info_t stud_fields[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleague, OBJ_PTR, student_t)
    };
    REG_STRUCT(struct_db, student_t, stud_fields);

    /* Verify the correctness of the structure database */
    print_structure_db(struct_db);

    /* Initialize a new object database */
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;
    global_object_db = object_db;

    /* Create some sample objects using xcalloc */
    student_t *aditi = xcalloc(object_db, "student_t", 1);
    strncpy(aditi->stud_name, "Aditi", sizeof(aditi->stud_name));
    aditi->rollno = 101;
    aditi->age = 21;
    aditi->aggregate = 88.5;
    aditi->best_colleague = NULL;

    student_t *adhira = xcalloc(object_db, "student_t", 1);
    strncpy(adhira->stud_name, "Adhira", sizeof(adhira->stud_name));
    adhira->rollno = 102;
    adhira->age = 22;
    adhira->aggregate = 91.2;
    adhira->best_colleague = aditi;

    emp_t *aarushi = xcalloc(object_db, "emp_t", 1);
    strncpy(aarushi->emp_name, "Aarushi", sizeof(aarushi->emp_name));
    aarushi->emp_id = 2001;
    aarushi->age = 25;
    aarushi->salary = 55000.0;
    aarushi->mgr = NULL;

    /* Print the object database */
    print_object_db(object_db);

    /* Dump details of the objects */
    mld_dump_object_rec_detail(object_db->head, "student_t");

    return 0;
}
