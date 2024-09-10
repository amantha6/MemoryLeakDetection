## Phase 1: Structure Database Development

### Overview
Phase 1 of the Memory Leak Detection (MLD) project is centered on the development of a structure database that maintains records of all structures utilized by an application. This database is essential for the detection and management of memory leaks in C and C++ programs.

### Objective
The main goal of Phase 1 is to design and implement the MLD Database to facilitate the structural registration of data structures used by the application. This foundational database enables the MLD library to monitor each structure's memory allocation and relationships comprehensively.

### Key Components
- **Structure Database (Structure DB)**: A linked list database storing metadata about each structure, including its name, size, fields, and more.
- **Field Information (`field_info_t`)**: Structs that define detailed information about each field within a structure, such as name, data type, size, and offset.
- **Structure Record (`struct_db_rec_t`)**: Represents a record in the Structure DB, containing comprehensive metadata about a specific structure.

### Development Tools
- **Operating System**: Linux/Unix, providing the necessary environment for development and execution.
- **Compiler**: gcc, which compiles the C/C++ code ensuring compatibility and performance.

### Functions and Macros
- **`struct_db_look_up`**: Searches for and retrieves a structure record by name from the Structure DB. Returns `NULL` if no record is found.
- **`print_structure_rec`** and **`print_structure_db`**: Functions used to output the contents of the Structure DB, valuable for debugging and verification.
- **`add_structure_to_struct_db`**: Adds a new structure record to the Structure DB, expanding the database with new structural information.

### Implementation Details
- **Structure Registration**: Critical at the initialization phase where the application provides details about each structure it employs.
- **Macros**:
  - **`FIELD_INFO`**: Simplifies the definition of field metadata within a structure.
  - **`REG_STRUCT`**: Facilitates the registration of structures to the Structure DB, ensuring efficient and complete data capture.
- **Data Handling**: Includes detailed enumeration for identifying various field types within the structures, enhancing data management and accessibility.

### Example Implementation
- Structures such as `emp_t` are registered detailing fields like `emp_name`, `emp_id`, `age`, `mgr`, and `salary`. Each field's metadata including size and offset is meticulously recorded.
- The C application must initialize and populate the Structure DB accurately using the macros and functions provided by the MLD library.

### Summary
Phase 1 lays the groundwork for the MLD project's comprehensive memory leak detection capabilities by establishing a detailed and searchable database of all structures used within the application. This database is crucial for the subsequent phases that focus on tracking memory allocations and detecting leaks based on the information collected in this initial phase.

Memory Layout Descriptor (MLD) Library
======================================

Overview
--------
The Memory Layout Descriptor (MLD) Library is designed to track and manage dynamically allocated memory within applications. It provides a detailed tracking system for all memory allocations, ensuring efficient management and aiding in debugging and memory leak prevention.

Key Features
------------
1. Object Tracking:
   - The library records details of every dynamic allocation (malloc), including the memory address and associated metadata.

2. Object Database Modelling:
   - Manages an object database with records for each dynamically allocated object.
   - Each record includes the object's pointer, the number of units allocated, a link to the next object, and a reference to the structure definition.

3. Custom Memory Allocation:
   - Introduces 'xcalloc', a custom function for allocating memory while updating the object database.
   - Usage: void* xcalloc(object_db_t *object_db, char *struct_name, int units);

4. Dumping Functions:
   - Provides functions to dump the contents of the object database, displaying detailed information about each object to aid in debugging and identifying memory leaks.

Usage Example
-------------
To allocate memory for a student_t object:
   student_t *aditi = xcalloc(object_db, "student_t", 1);

Benefits
--------
- Enhanced Debugging: Tracks all dynamic allocations, aiding in quick identification and resolution of memory-related issues.
- Improved Memory Management: Simplifies memory operations, making code cleaner and more robust.
- Leak Detection: Helps identify unreleased memory, preventing leaks and ensuring efficient resource use.

Conclusion
----------
Phase 2 of the MLD library development focuses on providing robust memory tracking and management capabilities essential for developing high-reliability applications. The library's features not only aid in debugging but also enhance overall application performance by ensuring effective resource utilization.

