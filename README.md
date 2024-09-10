# Memory Leak Detection (MLD) Library

## Overview
The Memory Leak Detection (MLD) Library is a utility designed to aid developers in managing and tracking dynamically allocated memory in C and C++ applications. It offers comprehensive features to help in debugging, preventing memory leaks, and enhancing memory management practices.

## Table of Contents
- Phase 1: Structure Database Development
- Phase 2: Object Database and Custom Memory Allocation
- Phase 3: Memory Leak Detection System

---

# Phase 1: Structure Database Development

## Overview
This phase involves the creation of a Structure Database to record details of all data structures utilized by an application, crucial for managing memory leaks effectively.

## Objective
Develop the MLD Database to support the registration of data structures, allowing for detailed monitoring of memory allocation and inter-structural relationships.

## Key Components
- **Structure Database (Structure DB)**: A database in the form of a linked list that stores metadata about each structure.
- **Field Information (field_info_t)**: Structs providing detailed information on each structure's fields.
- **Structure Record (struct_db_rec_t)**: A record within the Structure DB holding extensive metadata about a structure.

## Development Tools
- **Operating System**: Linux/Unix
- **Compiler**: gcc

## Functions and Macros
- **`struct_db_look_up`**: Retrieves a structure record by its name.
- **`print_structure_rec`** and **`print_structure_db`**: Functions to display the contents of the Structure DB.
- **`add_structure_to_struct_db`**: Registers a new structure record to the Structure DB.

## Implementation Details
Structures are registered at initialization with comprehensive field metadata. Efficient data capture is facilitated through macros like `FIELD_INFO` and `REG_STRUCT`.

---

# Phase 2: Object Database and Custom Memory Allocation

## Overview
This phase adds an object database that manages records for each dynamically allocated object, improving memory allocation tracking and management.

## Key Features
- **Object Tracking**: Keeps detailed records of each dynamic memory allocation.
- **Custom Memory Allocation**: Features 'xcalloc', a function that allocates memory while updating the object database.

# Phase 3: Memory Leak Detection System
## Overview
This phase implements a memory leak detection algorithm that identifies and reports memory leaks based on the reachability of objects from root objects.

## Key Concepts
Memory Leaks: Unreachable objects that have not been freed.
Root Objects: Starting points for memory graph traversal.
Graph Traversal: Methodically explores all objects linked from root objects to identify unreachable ones.
Leak Detection Algorithm
Initialization: Marks all objects as unvisited.
Graph Traversal: Traverses from root objects, marking all reachable objects.
Leak Identification: Objects that remain marked as unvisited are identified as leaks.
## Example
Assuming an object aditi is designated as a root, the system will traverse all objects linked to aditi, marking them as visited. Objects not visited after this traversal are reported as leaks.

## Conclusion
The MLD Library integrates several phases to provide a robust framework for memory tracking, management, and leak detection, vital for developing reliable applications. Its features not only aid in debugging but also improve application performance by ensuring efficient resource utilization.

## Contribution
Contributions to the MLD Library are encouraged, including bug reports, enhancement suggestions, and pull requests with fixes or new features.

## License
This project is licensed under the MIT License.
