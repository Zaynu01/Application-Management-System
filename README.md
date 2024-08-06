# SSE Application Management System

## Description

This C program implements an application management system for the School of Science and Engineering (SSE). It handles applicant information, manages application queues, and processes applications.

## How It Works

The program uses a combination of arrays and linked lists to manage two queues:

1. Official Queue: Implemented as an array of fixed size (3).
2. Waiting List: Implemented as a linked list for overflow management.

Applicant information is stored in structures containing name, ID, and expected salary.

The program offers a menu-driven interface with the following options:
1. Start calling for applications
2. Apply to SSE
3. Drop an application
4. View list of applicants
5. End application process and evaluate candidates

## Features

1. **Load Initial Applications**: Reads applicant data from a file, populating the official queue and waiting list.

2. **New Application Submission**: Allows new applicants to submit their information, adding them to the appropriate queue.

3. **Application Withdrawal**: Enables applicants to withdraw their applications from either queue.

4. **Queue Visualization**: Displays the contents of either the official queue or the waiting list.

5. **Application Processing**: 
   - Sets a maximum salary threshold
   - Processes applications one by one
   - Generates acceptance or rejection files for each applicant
   - Continues until 3 applicants are accepted or all applications are processed

6. **Queue Management**:
   - Automatically moves applicants from the waiting list to the official queue when space becomes available
   - Handles overflow by using a linked list for the waiting queue

7. **Data Persistence**: Writes acceptance/rejection status to individual text files for each applicant.

8. **Dynamic ID Generation**: Automatically generates unique IDs for applicants based on their order of application.

9. **Input Validation**: Ensures proper menu selection and data entry.

10. **Flexible Queue Selection**: Allows users to view either the official queue or the waiting list.

This program provides a comprehensive solution for managing applications, from submission to final processing, with features to handle varying numbers of applicants efficiently.
