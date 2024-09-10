# MemoryLeakDetection
Memory Leak Detection 
Overview
Phase 1 of the Memory Leak Detection (MLD) project focuses on developing a structure database to maintain all structures used by the application. This foundational step is crucial for the effective detection of memory leaks in C and C++ programs, as it allows the MLD library to keep track of all memory allocations and relations between different data structures.

Objective
The primary goal of Phase 1 is to design and implement the MLD Database, which is tasked with the structural registration of every data structure used by the application. This registration process ensures that the MLD library has comprehensive knowledge of each structure's layout, facilitating the detection and prevention of memory leaks.

Key Components
Structure Database (Structure DB): A linked list that stores metadata about each registered structure, such as its name, size, number of fields, and detailed information about each field.
Field Information (field_info_t): Describes individual fields within a structure, including field name, data type, size, and offset.
Structure Record (struct_db_rec_t): Contains the metadata for a particular structure, forming an element in the Structure DB.
Development Tools
Environment: Linux/Unix OS, which supports the necessary tools and libraries.
Compiler: gcc, used to compile the application and ensure compatibility with the MLD library.
Functions and Macros
struct_db_look_up: Retrieves a structure record from the Structure DB using the structure's name as a key. If the record is not found, returns NULL.
print_structure_rec and print_structure_db: Debugging functions used to print the contents of the Structure DB, facilitating verification and inspection.
add_structure_to_struct_db: Integrates a new structure record into the Structure DB.
Implementation Details
Structure Registration: At the initialization phase, the application provides detailed information about each structure it uses, including field names, data types, and other relevant metadata.
Macros:
FIELD_INFO: Aids in defining metadata for each field within a structure.
REG_STRUCT: Automates the registration of structures with the Structure DB, ensuring all necessary information is captured efficiently.
Data Handling: Maintains a detailed enumeration for field types, which helps in identifying and managing different data types within the registered structures.
