#include <stdio.h>
#include <stdlib.h>
#include "mld.h"
#include "css.h"

char *DATA_TYPE[] = {"UINT8", "UINT32", "INT32",
                     "CHAR", "OBJ_PTR", "FLOAT",
                     "DOUBLE", "OBJ_STRUCT"};

/* Dumping Function */

void
print_structure_rec(struct_db_rec_t *struct_rec){
    if(!struct_rec) return;
    int j = 0;
    field_info_t *field = NULL;
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "| %-20s | size = %-8d | #flds = %-3d |\n" ANSI_COLOR_RESET, struct_rec->struct_name, struct_rec->ds_size, struct_rec->n_fields);
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    for(j = 0; j < struct_rec->n_fields; j++){
        field = &struct_rec->fields[j];
        printf("  %-20s |", "");
        printf("%-3d %-20s | dtype = %-15s | size = %-5d | offset = %-6d|  nstructname = %-20s  |\n",
                j, field->fname, DATA_TYPE[field->dtype], field->size, field->offset, field->nested_str_name);
        printf("  %-20s |", "");
        printf(ANSI_COLOR_CYAN "--------------------------------------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    }
}

void
print_structure_db(struct_db_t *struct_db){
    
    if(!struct_db) return;
    printf("printing STRUCURE DATABASE\n");
    int i = 0;
    struct_db_rec_t *struct_rec = NULL;
    struct_rec = struct_db->head;
    printf("No of Structures Registered = %d\n", struct_db->count);
    while(struct_rec){
        printf("structure No : %d (%p)\n", i++, struct_rec);
        print_structure_rec(struct_rec);
        struct_rec = struct_rec->next;
    }
}

int
add_structure_to_struct_db(struct_db_t *struct_db, 
                           struct_db_rec_t *struct_rec){

    struct_db_rec_t *head = struct_db->head;

    if(!head){
        struct_db->head = struct_rec;
        struct_rec->next = NULL;
        struct_db->count++;
        return 0;
    }

    struct_rec->next = head;
    struct_db->head = struct_rec;
    struct_db->count++;
    return 0;
}

static struct_db_rec_t *
struct_db_look_up(struct_db_t *struct_db,
                  char *struct_name){
    
    struct_db_rec_t *head = struct_db->head;
    if(!head) return NULL;
    
    for(; head; head = head->next){
        if(strncmp(head->struct_name, struct_name, MAX_STRUCTURE_NAME_SIZE) ==0)
            return head;
    }
    return NULL;
}


static object_db_rec_t *
object_db_look_up(object_db_t *object_db, void *ptr){

    object_db_rec_t *head = object_db->head;
    if(!head) return NULL;
    
    for(; head; head = head->next){
        if(head->ptr == ptr)
            return head;
    }
    return NULL;
}

/*Working with objects*/
static void
add_object_to_object_db(object_db_t *object_db, 
                     void *ptr, 
                     int units,
                     struct_db_rec_t *struct_rec){
     
    object_db_rec_t *obj_rec = object_db_look_up(object_db, ptr);
    /*Dont add same object twice*/
    assert(!obj_rec);

    obj_rec = calloc(1, sizeof(object_db_rec_t));

    obj_rec->next = NULL;
    obj_rec->ptr = ptr;
    obj_rec->units = units;
    obj_rec->struct_rec = struct_rec;

    object_db_rec_t *head = object_db->head;
        
    if(!head){
        object_db->head = obj_rec;
        obj_rec->next = NULL;
        object_db->count++;
        return;
    }

    obj_rec->next = head;
    object_db->head = obj_rec;
    object_db->count++;
}


void *
xcalloc(object_db_t *object_db, 
        char *struct_name, 
        int units){

    struct_db_rec_t *struct_rec = struct_db_look_up(object_db->struct_db, struct_name);
    assert(struct_rec);
    void *ptr = calloc(units, struct_rec->ds_size);
    add_object_to_object_db(object_db, ptr, units, struct_rec);
    return ptr;
}

/* Function to get the previous record in the object database */
static object_db_rec_t *
pre_object_db_rec_fn(object_db_t *object_db, object_db_rec_t *object_db_rec) {
    object_db_rec_t *head = object_db->head;

    if (head == object_db_rec) {
        return NULL;  // No previous record for the head of the list
    }

    while (head) {
        if (head->next == object_db_rec) {
            return head;
        }
        head = head->next;
    }

    return NULL;  // Return NULL if not found
}

/*Dumping Functions for Object database*/
void 
print_object_rec(object_db_rec_t *obj_rec, int i){
    
    if(!obj_rec) return;
    printf(ANSI_COLOR_MAGENTA"-----------------------------------------------------------------------------------|\n");
    printf(ANSI_COLOR_YELLOW "%-3d ptr = %-10p | next = %-10p | units = %-4d | struct_name = %-10s |\n", 
        i, obj_rec->ptr, obj_rec->next, obj_rec->units, obj_rec->struct_rec->struct_name); 
    printf(ANSI_COLOR_MAGENTA "-----------------------------------------------------------------------------------|\n");
}

void
print_object_db(object_db_t *object_db){

    object_db_rec_t *head = object_db->head;
    unsigned int i = 0;
    printf(ANSI_COLOR_CYAN "Printing OBJECT DATABASE\n");
    for(; head; head = head->next){
        print_object_rec(head, i++);
    }
}

// Print detailed object record
void mld_dump_object_rec_detail(object_db_rec_t *object_db_rec,const char *struct_ptr_name) { // Updated function signature

  assert(object_db_rec);

  void *ptr = object_db_rec->ptr;

  field_info_t *fields = object_db_rec->struct_rec->fields;

  unsigned int object_index = 0;

  while (object_index < object_db_rec->units) {

    ptr += object_index * object_db_rec->struct_rec->ds_size;

    for (int i = 0; i < object_db_rec->struct_rec->n_fields; i++) {

      switch (fields[i].dtype) {

      case UINT8: {

        printf("%s[%d]->%s = %hhd\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               *((unsigned char *)(ptr + fields[i].offset)));

        break;

      }

      case UINT32: {

        printf("%s[%d]->%s = %u\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               *((unsigned int *)(ptr + fields[i].offset)));

        break;

      }

      case INT32: {

        printf("%s[%d]->%s = %d\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               *((int *)(ptr + fields[i].offset)));

      }

      case CHAR: {

        printf("%s[%d]->%s = %s\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               (char *)(ptr + fields[i].offset));

        break;

      }

      case FLOAT: {

        printf("%s[%d]->%s = %f\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               *((float *)(ptr + fields[i].offset)));

        break;

      }

      case DOUBLE: {

        printf("%s[%d]->%s = %f\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname,

               *((double *)(ptr + fields[i].offset)));

        break;

      }

      case OBJ_PTR:

      case OBJ_STRUCT: {

        printf("%s[%d]->%s = %s\n", struct_ptr_name,

               object_index, object_db_rec->struct_rec->fields[i].fname, "nil");

        break;

      }

      }

    }

    object_index++;

  }

}

void xfree(object_db_t *object_db, void *ptr) { // Updated signature

  object_db_rec_t *object_db_rec = object_db_look_up(object_db, ptr);

  object_db_rec_t *head = object_db->head;

  if (head == object_db_rec) {

    head = object_db_rec->next;

    object_db->count--;

  } else {

    object_db_rec_t *pre_object_db_rec = pre_object_db_rec_fn(object_db, object_db_rec);

    pre_object_db_rec = object_db_rec->next;

    object_db->count--;

  }

  free(ptr);

  free(object_db_rec);

}
