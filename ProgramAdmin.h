#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX_LECTURERS 100
#define MAX_COURSES 100
#define MAX_ENROLLMENTS 100
#define MAX_ASSIGNMENTS 100
#define MAX_STRING_LENGTH 100

//____________________________________________________________________________________________________________________________________________
//Program Admin Part Code - Heng Jia En

void programmeMenu();
void addCourse();
void deleteCourse();
void viewCourse();
void update_course_name_in_enrollment(char old_course_name[], char new_course_name[]);
void update_course_name_in_assignment(char old_course_name[], char new_course_name[]);
void update_course_id_in_assignment(char old_course_id[], char new_course_id[]);
void update_course_id_in_enrollment(char old_course_id[], char new_course_id[]);
void modifyCourse();
void enrollStudentToCourse();
void viewEnrollments();
void assignLecturerToCourse();
void viewAssignments();
void viewStudentProfiles();
int isDuplicateName(const char *course_name);
int isDuplicateID(const char *course_id);
void upperString(char *str);
void delete_student_in_enrollment(char UID[]); //Used in system adminstrator
void update_lecturer_detail_in_assignment(char lec_id[], char old_lecturer[], char new_lecturer[]); //Used in lecturer
void update_student_detail_in_enrollment(char student_id[], char old_student[], char new_student[]); //Used in student

//Call Function from lecturer
void update_course_detail_for_attendance(char old_course[], char new_course[]);
void update_course_detail_for_coursemark(char old_course_2[], char new_course_2[]);
void delete_course_detail_for_attendance(char course_delete[]);
void delete_course_detail_for_coursemark(char course_detele_2[]);
void add_course_detail_for_attendance(char course_added[], char student_name[]);
void add_course_detail_for_coursemark(char course_added_2[], char student_name[]);

struct Course {
    char course_name[MAX_STRING_LENGTH];
    char course_id[MAX_STRING_LENGTH];
    float credit_hour;
};

struct ViewCourses {
    char *course_name;
    char *course_id;
    float credit_hour;
};

struct StudentEnrollment {
    char student_id[MAX_STRING_LENGTH];
    char student_name[MAX_STRING_LENGTH];
    char course_id[MAX_STRING_LENGTH];
    char course_name[MAX_STRING_LENGTH];
    char enrolled_date[MAX_STRING_LENGTH];

};

struct Assignlecturer {
    char lecturer_id[MAX_STRING_LENGTH];
    char lecturer_name[MAX_STRING_LENGTH];
    char course_id[MAX_STRING_LENGTH];
    char course_name[MAX_STRING_LENGTH];
};

struct Student {
    char student_id[MAX_STRING_LENGTH];
    char student_password[MAX_STRING_LENGTH];
    char student_name[MAX_STRING_LENGTH];
    char student_gender[MAX_STRING_LENGTH];
    char student_age[MAX_STRING_LENGTH];
    char student_email[MAX_STRING_LENGTH];
    char country[MAX_STRING_LENGTH];
};

struct Lecturer {
    char lecturer_id[MAX_STRING_LENGTH];
    char lecturer_password[MAX_STRING_LENGTH];
    char lecturer_name[MAX_STRING_LENGTH];
    char lecturer_gender[MAX_STRING_LENGTH];
    char lecturer_age[MAX_STRING_LENGTH];
    char lecturer_email[MAX_STRING_LENGTH];
    char country[MAX_STRING_LENGTH];
};

void programmeMenu() {
    int main_option;
    while (1) {
        printf("\n+------------------------------------+\n");
        printf("|                 Menu               |\n");
        printf("|------------------------------------|\n");
        printf("|  1. Add New Course Information     |\n");
        printf("|  2. Delete Course Information      |\n");
        printf("|  3. View Course Information        |\n");
        printf("|  4. Modify Course Information      |\n");
        printf("|  5. Student Enrollment             |\n");
        printf("|  6. View Student Enrollment        |\n");
        printf("|  7. Lecture Assignment             |\n");
        printf("|  8. View Lecturer Assignment       |\n");
        printf("|  9. View Student Profile           |\n");
        printf("| 10. Exit                           |\n");
        printf("+------------------------------------+\n");
        printf("Please enter your choice: ");
        if (scanf("%d", &main_option) != 1) {
            printf("Invalid input! Please enter an integer.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (main_option < 1 || main_option > 10) {
            printf("Invalid choice! Please enter a number between 1 and 10.\n");
            continue;
        }

        switch (main_option) {
            case 1:
                addCourse();
                break;
            case 2:
                deleteCourse();
                break;
            case 3:
                viewCourse();
                break;
            case 4:
                modifyCourse();
                break;
            case 5:
                enrollStudentToCourse();
                break;
            case 6:
                viewEnrollments();
                break;
            case 7:
                assignLecturerToCourse();
                break;
            case 8:
                viewAssignments();
                break;
            case 9:
                viewStudentProfiles();
                break;
            case 10:
                printf("Exiting to main menu...\n");
                loginMenu();
                break;
        }
    }
}

// Function to check whether the course name already exists in the file
int isDuplicateName(const char *course_name) {
    FILE *courses;
    courses = fopen("course.txt", "r");
    if (courses == NULL) {
        printf("Error opening file.\n");
        return 0; // Assume no duplicate if file cannot be opened
    }

    char line[100];
    while (fgets(line, sizeof(line), courses) != NULL) {
        char existingName[MAX_STRING_LENGTH];
        sscanf(line, "%[^,],", existingName);
        if (strcmp(course_name, existingName) == 0) {
            fclose(courses);
            return 1; // Name exists
        }
    }

    fclose(courses);
    return 0; // Name does not exist
}

// Function to check whether the course ID already exists in the file
int isDuplicateID(const char *course_id) {
    FILE *courses;
    courses = fopen("course.txt", "r");
    if (courses == NULL) {
        printf("Error opening file.\n");
        return 0; // Assume no duplicate if file cannot be opened
    }

    char line[100];
    while (fgets(line, sizeof(line), courses) != NULL) {
        char existingID[MAX_STRING_LENGTH];
        sscanf(line, "%*[^,],%[^,],", existingID);
        if (strcmp(course_id, existingID) == 0) {
            fclose(courses);
            return 1; // ID exists
        }
    }

    fclose(courses);
    return 0; // ID does not exist
}

void addCourse() {
    FILE *courses;
    struct Course course;
    char confirmation, choice;


    printf("\nNow you are proceeding to add course information....\n");

    do {
        //Check whether the file eixsts
        courses = fopen("course.txt", "a"); 
        if (courses == NULL) {
            printf("Error opening file.\n");
            return;
        }
        
        //Ask user to enter course name
        printf("\nPlease enter course name: ");
        scanf(" %[^\n]%*c", course.course_name);
        upperString(course.course_name);//Uppercase the course name

        //Check for duplicate course name
        if (isDuplicateName(course.course_name)) {
            do {
                printf("Course name already exists.\n");
                printf("Please enter another course name: ");
                scanf(" %[^\n]%*c", course.course_name);
                upperString(course.course_name);//Uppercase the course name
            } while (isDuplicateName(course.course_name));
        }

        //Ask user to enter course ID
        printf("Please enter course ID: ");
        scanf("%s", course.course_id);
        upperString(course.course_id);//Uppercase the course ID

        // Check for duplicate course ID
        if (isDuplicateID(course.course_id)) {
            do {
                printf("Course ID already exists.\n");
                printf("Please enter another course ID: ");
                scanf("%s", course.course_id);
                upperString(course.course_id);//Uppercase the course ID
            } while (isDuplicateID(course.course_id));
        }

        //Ask user to enter credit hour
        printf("Please enter credit hour: ");
        do {
            if (scanf("%f", &course.credit_hour) != 1 || course.credit_hour <= 0) {
                printf("Invalid input. Credit hour must be a positive input.\n");
                printf("Please try again: ");
                while (getchar() != '\n'); // Clear the input buffer
            } else {
                break;
            }
        } while (1);    

        //Confirmation to add course information
        do {
            printf("Are you sure to add this course information? (y/n): ");
            scanf(" %c",&confirmation); // Space before %c to consume newline character
            confirmation = toupper(confirmation); //Uppercase the confirmation
            while (getchar() != '\n'); 
            
            if (confirmation == 'Y') {
                fprintf(courses, "%s,%s,%.1f\n", course.course_name, course.course_id, course.credit_hour); //Write course information into file
                fclose(courses);
                printf("Course added successfully.\n");
                break;

            } else if (confirmation == 'N') {
                printf("Course not added.\n");
                fclose(courses);
                break;

            } else {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            }
        } while (confirmation != 'Y' && confirmation != 'N');

        //Ask for adding more course information
        do {
            printf("Do you want to add another course? (y/n): ");
            scanf(" %c", &choice); // Space before %c to consume newline character
            choice = toupper(choice); // Uppercase the choice
            while (getchar() != '\n'); 

            if (choice != 'Y' && choice != 'N') {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            } else if (choice == 'N') {
                programmeMenu();
                break;
            }
            
        } while (choice != 'Y' && choice != 'N');

    } while ( choice == 'Y');
}

void deleteCourse() {
    FILE *courses, *tempCourseFile, *enrollments, *tempEnrollmentFile, *assignments, *tempAssignmentFile;
    struct Course course;
    struct StudentEnrollment enrollment;
    struct Assignlecturer assignment;
    char courseID[MAX_STRING_LENGTH];
    char confirmation, choice;
    int delete_course;
    char course_name_to_detele[100];

    printf("\nNow you are proceeding to delete the course information....\n");
    
    do {
        courses = fopen("course.txt", "r");
        if (courses == NULL) {
            printf("Error opening file.\n");
            return;
        }
        
        printf("\nPlease enter the course ID to delete: ");
        scanf("%s", courseID);
        upperString(courseID); // Uppercase the course ID

        // Check if the course exists
        delete_course = 0;
        while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, course.course_id, &course.credit_hour) == 3) {
            if (strcmp(courseID, course.course_id) == 0) {
                delete_course = 1;
                break; // Course found, no need to continue searching
            }
        }

        fclose(courses);

        if (!delete_course) {
            printf("No course found with the given ID '%s'.\n", courseID);
            printf("Do you want to delete another course? (y/n): ");
            scanf(" %c", &choice);
            choice = toupper(choice); // Uppercase the choice
            while (getchar() != '\n'); // Clear input buffer

            if (choice != 'Y' && choice != 'N') {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            } else if (choice == 'N') {
                printf("Back to menu...");
                programmeMenu();
                break;
            }
            continue;
        }

        // Ask for confirmation if course found
        do {
            printf("Are you sure you want to delete the course with ID '%s'? (y/n): ", courseID);
            scanf(" %c", &confirmation);
            confirmation = toupper(confirmation); // Uppercase the confirmation
            while (getchar() != '\n'); // Clear input buffer

            if (confirmation != 'Y' && confirmation != 'N') {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            } else if (confirmation == 'N') {
                printf("Deletion cancelled.\n");
                break;
            } else {
                // Proceed with deletion
                tempCourseFile = fopen("temp_course.txt", "w");
                if (tempCourseFile == NULL) {
                    printf("Error opening temporary course file.\n");
                    return;
                }

                courses = fopen("course.txt", "r");
                if (courses == NULL) {
                    printf("Error opening course file.\n");
                    fclose(tempCourseFile);
                    return;
                }

                // Rewrite the file excluding the course to be deleted
                while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, course.course_id, &course.credit_hour) == 3) {
                    if (strcmp(courseID, course.course_id) != 0) {
                        fprintf(tempCourseFile, "%s,%s,%.1f\n", course.course_name, course.course_id, course.credit_hour);
                    }
                }

                rewind(courses);
                while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, course.course_id, &course.credit_hour) == 3) {
                    if (strcmp(courseID, course.course_id) == 0) {
                        strcpy(course_name_to_detele, course.course_name);
                        break;
                    }
                }

                fclose(courses);
                fclose(tempCourseFile);

                remove("course.txt"); // Remove original course file
                rename("temp_course.txt", "course.txt"); // Rename temporary course file to original course file
                printf("The course with ID '%s' has been deleted successfully!\n", courseID);


                tempEnrollmentFile = fopen("temp_enrollments.txt", "w");
                if (tempEnrollmentFile == NULL) {
                    printf("Error opening temporary enrollment file.\n");
                    return;
                }

                enrollments = fopen("enrollment.txt", "r");
                if (enrollments == NULL) {
                    printf("Error opening enrollment file.\n");
                    fclose(tempEnrollmentFile);
                    return;
                }

                // Rewrite the file excluding the enrollments associated with the deleted course
                while (fscanf(enrollments, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date) == 5) {
                    if (strcmp(courseID, enrollment.course_id) != 0) {
                        fprintf(tempEnrollmentFile, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
                    }
                }

                fclose(enrollments);
                fclose(tempEnrollmentFile);

                remove("enrollment.txt"); // Remove original enrollment file
                rename("temp_enrollments.txt", "enrollment.txt"); // Rename temporary enrollment file to original enrollment file

                tempAssignmentFile = fopen("temp_assignments.txt", "w");
                if (tempAssignmentFile == NULL) {
                    printf("Error opening temporary assignment file.\n");
                    return;
                }

                assignments = fopen("assignlecturer.txt", "r");
                if (assignments == NULL) {
                    printf("Error opening assignment file.\n");
                    fclose(tempAssignmentFile);
                    return;
                }

                // Rewrite the file excluding the assignments associated with the deleted course
                while (fscanf(assignments, "%99[^,],%99[^,],%99[^,],%[^\n]\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name) == 4) {
                    if (strcmp(courseID, assignment.course_id) != 0) {
                        fprintf(tempAssignmentFile, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name);
                    }
                }
                fclose(assignments);
                fclose(tempAssignmentFile);

                remove("assignlecturer.txt"); // Remove original assignment file
                rename("temp_assignments.txt", "assignlecturer.txt"); // Rename temporary assignment file to original assignment file

                // call function from lecturer to delete the course at the same time for attendance and coursemark
                delete_course_detail_for_attendance(course_name_to_detele);
                delete_course_detail_for_coursemark(course_name_to_detele);


            }
        } while (confirmation != 'Y' && confirmation != 'N');

        printf("Do you want to delete another course? (y/n): ");
        scanf(" %c", &choice);
        choice = toupper(choice); // Uppercase the choice
        while (getchar() != '\n'); // Clear input buffer

        if (choice != 'Y' && choice != 'N') {
            printf("Invalid input. Please enter 'y' or 'n' only!\n");
        } else if (choice == 'N') {
            printf("Back to menu...");
            programmeMenu();
            break;
        }
        
    } while (choice == 'Y');
}

void viewCourse() {
    struct ViewCourses viewcourses;
    char course_name[100], course_id[100];
    float credit_hour;
    FILE *courses;

    courses = fopen("course.txt", "r");
    if (courses == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\nCourse Information:\n");
    printf("---------------------------------------------------------\n");
    printf("| %-25s | %-10s | %-12s |\n", "Course Name", "ID", "Credit Hour");
    printf("|---------------------------|------------|--------------|\n");
    
    while (fscanf(courses, " %99[^,], %99[^,], %f", course_name, course_id, &credit_hour) == 3) {
        viewcourses.course_name = malloc(strlen(course_name) + 1);
        strcpy(viewcourses.course_name, course_name);
        viewcourses.course_id = malloc(strlen(course_id) + 1);
        strcpy(viewcourses.course_id, course_id);
        viewcourses.credit_hour = credit_hour;
        printf("| %-25s | %-10s | %-12.1f |\n", viewcourses.course_name, viewcourses.course_id, viewcourses.credit_hour);
        //Free allocated memory
        free(viewcourses.course_name);
        free(viewcourses.course_id);
    }
    printf("---------------------------------------------------------\n");
    fclose(courses);
}

void modifyCourse() {
    FILE *courses, *tempFile;
    struct Course course, original_course;
    int modify_option;
    char modify_id[MAX_STRING_LENGTH]; 
    char confirmation, choice;
    int found;
    char new_course_name[100];
    char new_course_id[100];

    do {
        courses = fopen("course.txt", "r");
        if (courses == NULL) {
            printf("Error opening file.\n");
            return;
        }

        // Print all courses
        printf("Course Information:\n");
        printf("----------------------------------------------------------------\n");
        printf("| %-25s | %-15s | %-15s |\n", "Course Name", "Course ID", "Credit Hour");
        printf("|---------------------------|-----------------|-----------------|\n");
        while (fscanf(courses, " %99[^,],%99[^,],%f", course.course_name, course.course_id, &course.credit_hour) == 3) {
            printf("| %-25s | %-15s | %-15.1f |\n", course.course_name, course.course_id, course.credit_hour);
        }
        printf("----------------------------------------------------------------\n");
        fclose(courses);

        // Open original file for reading
        courses = fopen("course.txt", "r");
        if (courses == NULL) {
            printf("Error opening file.\n");
            return;
        }

        // Create a temporary file
        tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Error creating temporary file.\n");
            fclose(courses);
            return;
        }

        printf("Please enter the ID of the course you want to modify: ");
        scanf("%s", modify_id);
        upperString(modify_id);

        found = 0;
        // Read course information and find the course to display and modify
        while (fscanf(courses, " %99[^,],%99[^,],%f", course.course_name, course.course_id, &course.credit_hour) == 3) {
            if (strcmp(course.course_id, modify_id) == 0) {
                found = 1;
                printf("\nCourse Information:\n");
                printf("----------------------------------------------------------------\n");
                printf("| %-25s | %-15s | %-15s |\n", "Course Name", "Course ID", "Credit Hour");
                printf("|---------------------------|-----------------|-----------------|\n");
                printf("| %-25s | %-15s | %-15.1f |\n", course.course_name, course.course_id, course.credit_hour);
                printf("----------------------------------------------------------------\n");

                // Store original course data
                strcpy(original_course.course_name, course.course_name);
                strcpy(original_course.course_id, course.course_id);
                original_course.credit_hour = course.credit_hour;

                strcpy(new_course_name, original_course.course_name);
                strcpy(new_course_id, original_course.course_id);

                do {
                    // Ask user to choose which data to modify
                    printf("Please choose the data type to be modified...\n");
                    printf("1. Course Name\n");
                    printf("2. Course ID\n");
                    printf("3. Credit Hour\n");
                    printf("Enter your choice: ");

                    while (scanf("%d", &modify_option) != 1 || modify_option < 1 || modify_option > 3) {
                        printf("Invalid choice. Please enter a valid input from 1 to 3.\n");
                        printf("Enter your choice: ");
                        while (getchar() != '\n');
                    }
                    
                    switch (modify_option) {
                        case 1:  // Modify course name
                            printf("Please enter modified course name: ");
                            scanf(" %[^\n]%*c", course.course_name);
                            upperString(course.course_name);
                            strcpy(new_course_name ,course.course_name);

                            //Check whether the course name is duplicated
                            while (isDuplicateName(course.course_name)) {
                                printf("Course name already exists. Please enter a unique name: ");
                                scanf(" %[^\n]%*c", course.course_name);
                                upperString(course.course_name);
                                strcpy(new_course_name, course.course_name);
                            }
                            break;

                        case 2: // Modify course ID
                            printf("Please enter modified course id: ");
                            scanf("%s", course.course_id);
                            upperString(course.course_id);
                            strcpy(new_course_id, course.course_id);

                            //Check whether course ID is duple=icated
                            while (isDuplicateID(course.course_id)) {
                                printf("Course ID %s already exists. Please enter a different ID: ", course.course_id);
                                scanf("%s", course.course_id);
                                upperString(course.course_id);
                                strcpy(new_course_id, course.course_id);
                            }
                            break;

                        case 3: // Modify credit hour
                            printf("Please enter credit hour: ");
                            do {
                                if (scanf("%f", &course.credit_hour) != 1 || course.credit_hour <= 0) {
                                    printf("Invalid input. Credit hour must be a positive input.\n");
                                    printf("Please try again: ");
                                    while (getchar() != '\n'); // Clear the input buffer
                                } else {
                                    break;
                                }
                            } while (1);
                            break;   
                    }
                    
                } while (modify_option != 1 && modify_option != 2 && modify_option != 3);

                // Ask for confirmation before writing the modified course to the temporary file
                do {
                    printf("Are you sure you want to modify this course? (y/n): ");
                    scanf(" %c", &confirmation);
                    confirmation = toupper(confirmation); // Uppercase the confirmation
                    while (getchar() != '\n'); 

                    if (confirmation != 'Y' && confirmation != 'N') {
                        printf("Invalid input! Please enter 'y' or 'n' only!\n");
                    }
                } while (confirmation != 'Y' && confirmation != 'N');

                if (confirmation == 'Y') {
                    fprintf(tempFile, "%s,%s,%.1f\n", course.course_name, course.course_id, course.credit_hour); //Print data into file
                    printf("Modification successful!\n");

                } else {
                    // Write the original course data back to the temporary file without any modification
                    fprintf(tempFile, "%s,%s,%.1f\n", original_course.course_name, original_course.course_id, original_course.credit_hour);
                    printf("Modification canceled.\n");
                }
            }
            else {
                fprintf(tempFile, "%s,%s,%.1f\n", course.course_name, course.course_id, course.credit_hour);
            }
        }

        fclose(courses);
        fclose(tempFile);

        // Replace original file with temporary file
        remove("course.txt");
        rename("temp.txt", "course.txt");

        update_course_id_in_enrollment(original_course.course_id, new_course_id);
        update_course_id_in_assignment(original_course.course_id, new_course_id);
        update_course_name_in_enrollment(original_course.course_name, new_course_name);
        update_course_name_in_assignment(original_course.course_name, new_course_name);
        update_course_detail_for_attendance(original_course.course_name, new_course_name);
        update_course_detail_for_coursemark(original_course.course_name, new_course_name);


        if (!found) {
            printf("Course with ID %s does not exist.\n", modify_id);
        }

        do{
            printf("Do you want to modify another course? (y/n): ");
            scanf(" %c", &choice);
            choice = toupper(choice); //Uppercase choice
            while (getchar() != '\n');

            if (choice == 'N') {
                printf("Back to menu...\n");
                programmeMenu();
                break;
            } else if (choice != 'N' && choice != 'Y') {
                printf("Invalid input! Please enter 'y' or 'n' only!\n");
            }
            
        }while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');   
}


void enrollStudentToCourse() {
    FILE *enrollments, *student, *enrollmentCheck, *courses;
    struct Student students;
    struct Course course;
    struct StudentEnrollment studentenrollments;
    
    char confirmation, choice;
    int studentExists;
    int courseExists;
    int studentEnrolled;

    printf("\nNow you are proceeding to enroll student into course...\n");

    do {
        // Validate student enrollment
        do {
            printf("\nStudent Information:\n");
            printf("-----------------------------------------------\n");
            printf("| %-20s | %-20s |\n", "Student ID", "Student Name");
            printf("-----------------------------------------------\n");

            student = fopen("student.txt", "r");
            while (fscanf(student, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", students.student_id, students.student_password, students.student_name, students.student_gender, students.student_age, students.student_email, students.country) == 7){
                printf("| %-20s | %-20s |\n", students.student_id, students.student_name);
            }
            printf("-----------------------------------------------\n");
            fclose(student);

            printf("Enter student ID to be enrolled: ");
            scanf("%s", studentenrollments.student_id);
            upperString(studentenrollments.student_id);

            // Check whether student exists
            studentExists = 0;
            student = fopen("student.txt", "r");
            if (student == NULL) {
                printf("Error opening student file.\n");
                return;
            }

            while (fscanf(student, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", students.student_id, students.student_password, students.student_name, students.student_gender, students.student_age, students.student_email, students.country) == 7){
                if (strcmp(studentenrollments.student_id, students.student_id) == 0) {
                    studentExists = 1;
                    strcpy(studentenrollments.student_name, students.student_name);
                    break;
                }
            }
            fclose(student);

            if (!studentExists) {
                printf("Student with ID %s does not exist.\n", studentenrollments.student_id);
                continue;
            }

            // Check whether the student ID has been assigned
            studentEnrolled = 0;
            enrollmentCheck = fopen("enrollment.txt", "r");
            if (enrollmentCheck == NULL) {
                printf("Error opening enrollment file.\n");
                return;
            }

            char studentID[MAX_STRING_LENGTH];
            char StudentName[MAX_STRING_LENGTH];
            char CourseID[MAX_STRING_LENGTH];
            while (fscanf(enrollmentCheck, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", studentID, StudentName, CourseID, studentenrollments.course_name, studentenrollments.enrolled_date) == 5) {
                if (strcmp(studentenrollments.student_id, studentID) == 0) {
                    studentEnrolled = 1;
                    break;
                }
            }
            fclose(enrollmentCheck);

            if (studentEnrolled) {
                printf("Student with ID %s is already enroll to a course.\n", studentenrollments.student_id);
                continue;
            }
        } while (!studentExists || studentEnrolled);

        // Validate course assignment
        do {
            printf("\nCourse Information:\n");
            printf("----------------------------------------------\n");
            printf("| %-20s | %-20s |\n", "Course Name", "Course ID");
            printf("----------------------------------------------\n");

            courses = fopen("course.txt", "r");
            if (courses == NULL) {
                printf("Error opening course file.\n");
                return;
            }

            while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, course.course_id, &course.credit_hour) == 3) {
                printf("| %-20s | %-20s |\n", course.course_name, course.course_id);
            }
            printf("----------------------------------------------\n");
            fclose(courses);

            printf("Enter course ID to enroll with: ");
            scanf("%s", studentenrollments.course_id);
            upperString(studentenrollments.course_id);

            // Check whether the course exists
            courseExists = 0;
            courses = fopen("course.txt", "r");
            if (courses == NULL) {
                printf("Error opening course file.\n");
                return;
            }

            char existingCourseID[MAX_STRING_LENGTH];
            while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, existingCourseID, &course.credit_hour) == 3) {
                if (strcmp(studentenrollments.course_id, existingCourseID) == 0) {
                    courseExists = 1;
                    strcpy(studentenrollments.course_name, course.course_name);
                    break;
                }
            }
            fclose(courses);

            if (!courseExists) {
                printf("Course with ID %s does not exist.\n", studentenrollments.course_id);
                continue;
            }
        } while (!courseExists);

        // Get the current date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(studentenrollments.enrolled_date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);


        do {
            printf("Are you sure to enroll this student? (y/n): ");
            scanf(" %c",&confirmation); // Space before %c to consume newline character
            confirmation = toupper(confirmation); //Uppercase the confirmation
            while (getchar() != '\n'); 
            
            if (confirmation !='Y' && confirmation !='N'){
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            }
            else if (confirmation == 'Y') {
                enrollments = fopen("enrollment.txt", "a"); 
                if (enrollments == NULL) {
                    printf("Error opening file.\n");
                    return;
                }
                //Write enrollment information into file
                fprintf(enrollments, "%s,%s,%s,%s,%s\n", studentenrollments.student_id, studentenrollments.student_name, studentenrollments.course_id, studentenrollments.course_name,studentenrollments.enrolled_date);
                fclose(enrollments);
                //adding course detail at the same time to attendance and mark file
                add_course_detail_for_attendance(studentenrollments.course_name, studentenrollments.student_id);
                add_course_detail_for_coursemark(studentenrollments.course_name, studentenrollments.student_id);
                printf("Enrollment successful.\n");
                break;

            } else if (confirmation == 'N') {
                printf("Enrollment not successful.\n");
                fclose(enrollments);
                break;
            } 
        } while (confirmation !='Y' && confirmation !='N');


        // Prompt for another enrollment
        do {
            printf("Do you want to enroll another student? (y/n): ");
            scanf(" %c", &choice); // Space before %c to consume newline character
            choice = toupper(choice); // Uppercase the choice
            while (getchar() != '\n'); 

            if (choice != 'Y' && choice != 'N') {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            }
        } while (choice != 'Y' && choice != 'N');

        if (choice == 'N') {
            printf("\nEnrollments: \n");
            printf("----------------------------------------------------------------------------------------------------\n");
            printf("| %-12s | %-20s | %-12s | %-20s | %-20s |\n", "Student ID", "Student Name", "Course ID", "Course Name", "Enrolled Date");
            printf("----------------------------------------------------------------------------------------------------\n");
            FILE *enrollmentCheck; 
            enrollmentCheck = fopen("enrollment.txt", "r");
            if (enrollmentCheck == NULL) {
                printf("Error opening enrollment file.\n");
                fclose(enrollments);
                return;
            }

            while (fscanf(enrollmentCheck, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", studentenrollments.student_id, studentenrollments.student_name, studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date) == 5) {
                printf("| %-12s | %-20s | %-12s | %-20s | %-20s |\n", studentenrollments.student_id, studentenrollments.student_name, studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date);
            }
            printf("----------------------------------------------------------------------------------------------------\n");
            fclose(enrollmentCheck);

            printf("Back to menu....");
            programmeMenu();
            break;
        }
    } while ( choice == 'Y');
}

void viewEnrollments() {
    struct StudentEnrollment enrollments[MAX_ENROLLMENTS];
    int lineEnrollments = 0;
    

    FILE *enrollmentFile;
    enrollmentFile = fopen("enrollment.txt", "r");
    if (enrollmentFile == NULL) {
        printf("Error opening enrollment file.\n");
        return;
    }

    // Read enrollment data into array
    while (fscanf(enrollmentFile, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", enrollments[lineEnrollments].student_id, enrollments[lineEnrollments].student_name, enrollments[lineEnrollments].course_id, enrollments[lineEnrollments].course_name, enrollments[lineEnrollments].enrolled_date) == 5) {
        lineEnrollments++;
        if (lineEnrollments >= MAX_ENROLLMENTS) {
            printf("Maximum enrollments reached. Some data may not be loaded.\n");
            break;
        }
    }
    fclose(enrollmentFile);

    // Display enrollment data
    printf("\nEnrollments:\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-20s | %-12s | %-20s | %-20s |\n", "Student ID", "Student Name", "Course ID", "Course Name", "Enrolled Date");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < lineEnrollments; i++) {
        printf("| %-12s | %-20s | %-12s | %-20s | %-20s |\n", enrollments[i].student_id, enrollments[i].student_name, enrollments[i].course_id, enrollments[i].course_name, enrollments[i].enrolled_date);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
}

void assignLecturerToCourse() {
    FILE *lecturer, *assignments, *assignmentsCheck, *courses;
    struct Lecturer lecturers;
    struct Course course;
    struct Assignlecturer assignlecturers;

    char confirmation, choice;
    int lecturerExists;
    int courseExists;
    int lecturerassigned;

    printf("\nNow you are proceeding to assign lecturer into course...\n");

    do {
        // Validate lecturer assignment
        do {
            printf("\nLecturer Information:\n");
            printf("-----------------------------------------------\n");
            printf("| %-20s | %-20s |\n", "Lecturer ID", "Lecturer Name");
            printf("-----------------------------------------------\n");

            lecturer = fopen("lecturer.txt", "r");
            while (fscanf(lecturer, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", lecturers.lecturer_id, lecturers.lecturer_password, lecturers.lecturer_name, lecturers.lecturer_gender, lecturers.lecturer_age, lecturers.lecturer_email, lecturers.country) == 7){
                printf("| %-20s | %-20s |\n", lecturers.lecturer_id, lecturers.lecturer_name);
            }
            printf("-----------------------------------------------\n");
            fclose(lecturer);

            printf("Enter lecturer ID to be assigned: ");
            scanf("%s", assignlecturers.lecturer_id);
            upperString(assignlecturers.lecturer_id);

            // Check whether lecturer exists
            lecturerExists = 0;
            lecturer = fopen("lecturer.txt", "r");
            if (lecturer == NULL) {
                printf("Error opening lecturer file.\n");
                return;
            }

            while (fscanf(lecturer, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", lecturers.lecturer_id, lecturers.lecturer_password, lecturers.lecturer_name, lecturers.lecturer_gender, lecturers.lecturer_age, lecturers.lecturer_email, lecturers.country) == 7){
                if (strcmp(assignlecturers.lecturer_id, lecturers.lecturer_id) == 0) {
                    lecturerExists = 1;
                    strcpy(assignlecturers.lecturer_name, lecturers.lecturer_name);
                    break;
                }
            }
            fclose(lecturer);

            if (!lecturerExists) {
                printf("Lecturer with ID %s does not exist.\n", assignlecturers.lecturer_id);
                continue;
            }

            // Check whether the lecturer ID has been assigned
            lecturerassigned = 0;
            assignmentsCheck = fopen("assignlecturer.txt", "r");
            if (assignmentsCheck == NULL) {
                printf("Error opening assignment file.\n");
                return;
            }

            char LecturerID[MAX_STRING_LENGTH];
            char LecturerName[MAX_STRING_LENGTH];
            char CourseID[MAX_STRING_LENGTH];
            while (fscanf(assignmentsCheck, "%[^,],%[^,],%[^,],%[^\n]\n", LecturerID, LecturerName, CourseID, assignlecturers.course_name) == 4) {
                if (strcmp(assignlecturers.lecturer_id, LecturerID) == 0) {
                    lecturerassigned = 1;
                    break;
                }
            }
            fclose(assignmentsCheck);

            if (lecturerassigned) {
                printf("Lecturer with ID %s is already assigned to a course.\n", assignlecturers.lecturer_id);
                continue;
            }
        } while (!lecturerExists || lecturerassigned);

        // Validate course assignment
        do {
            printf("\nCourse Information:\n");
            printf("--------------------------------------------------------------\n");
            printf("| %-20s | %-20s | %-12s |\n", "Course Name", "Course ID", "Credit Hour");
            printf("--------------------------------------------------------------\n");

            courses = fopen("course.txt", "r");
            while (fscanf(courses, "%99[^,],%99[^,],%f\n", course.course_name, course.course_id, &course.credit_hour) == 3) {
                printf("| %-20s | %-20s | %-12.1f |\n", course.course_name, course.course_id, course.credit_hour);
            }
            printf("--------------------------------------------------------------\n");
            fclose(courses);

            printf("Enter course ID to assign with: ");
            scanf("%s", assignlecturers.course_id);
            upperString(assignlecturers.course_id);

            // Check whether the course exists
            courseExists = 0;
            courses = fopen("course.txt", "r");
            if (courses == NULL) {
                printf("Error opening course file.\n");
                return;
            }

            char existingCourseID[MAX_STRING_LENGTH];
            while (fscanf(courses, "%[^,],%[^,],%f\n", course.course_name, existingCourseID, &course.credit_hour) == 3) {
                if (strcmp(assignlecturers.course_id, existingCourseID) == 0) {
                    courseExists = 1;
                    strcpy(assignlecturers.course_name, course.course_name);
                    break;
                }
            }
            fclose(courses);

            if (!courseExists) {
                printf("Course with ID %s does not exist.\n", assignlecturers.course_id);
                continue;
            }
        } while (!courseExists);

        do {
            printf("Are you sure to assign this lecturer? (y/n): ");
            scanf(" %c",&confirmation); // Space before %c to consume newline character
            confirmation = toupper(confirmation); //Uppercase the confirmation
            while (getchar() != '\n'); 

            if (confirmation != 'Y' && confirmation != 'N'){
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            }
            if (confirmation == 'Y') {
                assignments = fopen("assignlecturer.txt", "a"); 
                if (assignments == NULL) {
                    printf("Error opening file.\n");
                    return;
                }
                //Write course information into file
                fprintf(assignments, "%s,%s,%s,%s\n", assignlecturers.lecturer_id, assignlecturers.lecturer_name, assignlecturers.course_id, assignlecturers.course_name);
                fclose(assignments);
                printf("Assignment successful.\n");
                break;

            } else if (confirmation == 'N') {
                printf("Assignment not successful.\n");
                fclose(assignments);
                break;
            }
        } while (confirmation != 'Y' && confirmation != 'N');


        // Prompt for another assignment
         do {
            printf("Do you want to assign another lecturer? (y/n): ");
            scanf(" %c", &choice); // Space before %c to consume newline character
            choice = toupper(choice); // Uppercase the choice
            while (getchar() != '\n'); 

            if (choice != 'Y' && choice != 'N') {
                printf("Invalid input. Please enter 'y' or 'n' only!\n");
            }
        } while (choice != 'Y' && choice != 'N');

        if (choice == 'N') {
            printf("\nLecturer Assignments:\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-12s | %-20s | %-12s | %-20s |\n", "Lecturer ID", "Lecturer Name", "Course ID", "Course Name");
            printf("-----------------------------------------------------------------------------\n");

            assignmentsCheck = fopen("assignlecturer.txt", "r");
            if (assignmentsCheck == NULL) {
                printf("Error opening assignment file.\n");
                return;
            }

            while (fscanf(assignmentsCheck, "%99[^,],%99[^,],%99[^,],%[^\n]\n", assignlecturers.lecturer_id, assignlecturers.lecturer_name, assignlecturers.course_id, assignlecturers.course_name) == 4) {
                printf("| %-12s | %-20s | %-12s | %-20s |\n", assignlecturers.lecturer_id, assignlecturers.lecturer_name, assignlecturers.course_id, assignlecturers.course_name);
            }
            printf("-----------------------------------------------------------------------------\n");
            fclose(assignmentsCheck);

            printf("Back to menu....");
            programmeMenu();
            break;
        }
    } while (choice == 'Y');
}

void viewAssignments() {
    struct Assignlecturer assignments[MAX_ASSIGNMENTS];
    int lineAssignments = 0;

    FILE *assignmentFile;
    assignmentFile = fopen("assignlecturer.txt", "r");
    if (assignmentFile == NULL) {
        printf("Error opening assignment file.\n");
        return;
    }

    // Read assignment data into array
    while (fscanf(assignmentFile, "%99[^,],%99[^,],%99[^,],%[^\n]\n", assignments[lineAssignments].lecturer_id, assignments[lineAssignments].lecturer_name, assignments[lineAssignments].course_id, assignments[lineAssignments].course_name) == 4) {
        lineAssignments++;
        if (lineAssignments >= MAX_ASSIGNMENTS) {
            printf("Maximum assignments reached. Some data may not be loaded.\n");
            break;
        }
    }
    fclose(assignmentFile);

    // Display assignment data
    printf("\nAssignments:\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| %-12s | %-20s | %-12s | %-20s |\n", "Lecturer ID", "Lecturer Name", "Course ID", "Course Name");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < lineAssignments; i++) {
        printf("| %-12s | %-20s | %-12s | %-20s |\n", assignments[i].lecturer_id, assignments[i].lecturer_name, assignments[i].course_id, assignments[i].course_name);
    }

    printf("-----------------------------------------------------------------------------\n");
}

void viewStudentProfiles() {
     FILE *studentFile, *enrollmentFile; 
    struct Student students;
    struct StudentEnrollment studentenrollments;
    char view_option;
    char student_id[MAX_STRING_LENGTH];
    int studentExists;

    // Open student file
    studentFile = fopen("student.txt", "r");
    if (studentFile == NULL) {
        printf("Error opening student file.\n");
        return;
    }

    // Display header
    printf("\nAll Student Profile:\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-20s | %-12s | %-12s | %-30s | %-20s | %-12s | %-20s | %-20s |\n", "Student ID", "Student Name", "Gender", "Age", "Email", "Origin Country", "Course ID", "Course Name", "Enroll Date");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Iterate through all students
    while (fscanf(studentFile, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", students.student_id, students.student_password, students.student_name, students.student_gender, students.student_age, students.student_email, students.country) == 7){
        printf("| %-12s | %-20s | %-12s | %-12s | %-30s | %-20s |", students.student_id, students.student_name, students.student_gender, students.student_age, students.student_email, students.country);

        // Check if student is enrolled in any course
        int studentEnrolled = 0;
        enrollmentFile = fopen("enrollment.txt", "r");
        if (enrollmentFile == NULL) {
            printf("Error opening enrollment file.\n");
            fclose(studentFile);
            return;
        }

        // Iterate through enrollment file to find courses for the student
        while (fscanf(enrollmentFile, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", studentenrollments.student_id, studentenrollments.student_name, studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date) == 5) {
            if (strcmp(students.student_id, studentenrollments.student_id) == 0) {
                studentEnrolled = 1;
                printf(" %-12s | %-20s | %-20s |\n", studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date);
                break;
            }
        }
        fclose(enrollmentFile);

        // If the student is not enrolled in any course, print placeholders
        if (!studentEnrolled) {
            printf(" %-12s | %-20s | %-20s |\n", "-", "-", "-");
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(studentFile);
    
    do {
        studentExists = 0;
        printf("\nDo you want to find a specific student profile? (y/n): ");
        scanf(" %c", &view_option);
        view_option = toupper(view_option);
        while (getchar() != '\n');

        if (view_option != 'Y' && view_option != 'N') {
            printf("Invalid input. Please enter 'y' or 'n' only!\n");
        } 
        else if (view_option == 'Y') {
            printf("Enter student ID: ");
            scanf("%s", student_id);
            upperString(student_id);

            // Check if student exists
            studentFile = fopen("student.txt", "r");
            if (studentFile == NULL) {
                printf("Error opening student file.\n");
                return;
            }

            enrollmentFile = fopen("enrollment.txt", "r");
            if (enrollmentFile == NULL) {
                printf("Error opening enrollment file.\n");
                fclose(studentFile);
                return;
            }
            
            // Search for the student profile
            while (fscanf(studentFile, "%99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %99[^,], %[^\n]\n", students.student_id, students.student_password, students.student_name, students.student_gender, students.student_age, students.student_email, students.country) == 7){
                if (strcmp(student_id, students.student_id) == 0) {
                    studentExists = 1;
                    printf("\nStudent Profile:\n");
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-12s | %-20s | %-12s | %-12s | %-30s | %-20s | %-12s | %-20s | %-20s |\n", "Student ID", "Student Name", "Gender", "Age", "Email", "Origin Country", "Course ID", "Course Name", "Enroll Date");
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                    printf("| %-12s | %-20s | %-12s | %-12s | %-30s | %-20s |", students.student_id, students.student_name, students.student_gender, students.student_age, students.student_email, students.country);
        
                    int enrollmentFound = 0;
                    while (fscanf(enrollmentFile, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", studentenrollments.student_id, studentenrollments.student_name, studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date) == 5) {
                        if (strcmp(student_id, studentenrollments.student_id) == 0) {
                            printf(" %-12s | %-20s | %-20s |\n", studentenrollments.course_id, studentenrollments.course_name, studentenrollments.enrolled_date);
                            enrollmentFound = 1;
                        }
                    }
                    if (!enrollmentFound) {
                        printf("| %-12s | %-20s | %-12s | %-12s | %-30s | %-20s | %-12s | %-20s | %-20s |\n", students.student_id, students.student_name, students.student_gender, students.student_age, students.student_email, students.country, "-", "-", "-");
                    }
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    break;
                }
            }
            
            fclose(studentFile);
            fclose(enrollmentFile);

            if (!studentExists) {
                printf("Student with ID %s not found.\n", student_id);
            }
        } 
        else if (view_option == 'N'){
            printf("Back to menu...\n");
            programmeMenu();
            break;
        }

    } while (view_option == 'Y' || view_option != 'Y' && view_option != 'N');
}

void delete_student_in_enrollment(char UID[]){
    struct StudentEnrollment enrollment;

    FILE *enrollments = fopen("enrollment.txt", "r");
    if (enrollments == NULL) {
        printf("Error Opening Enrollment File.\n");
        return;
    }

    FILE *tempEnrollments = fopen("temp_enrollment.txt", "w");
    if (tempEnrollments == NULL) {
        printf("Error Opening Temporary Enrollment File.\n");
        fclose(enrollments);
        return;
    }


    while (fscanf(enrollments, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date) == 5) {
        if (strcmp(UID, enrollment.student_id) != 0) {
            fprintf(tempEnrollments, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
        }
    }

    fclose(enrollments);
    fclose(tempEnrollments);

    remove("enrollment.txt");
    rename("temp_enrollment.txt", "enrollment.txt");
}

void update_lecturer_detail_in_assignment(char lec_id[], char old_lecturer[], char new_lecturer[]) {
    struct Assignlecturer assignment;
    int found;
    FILE *Assignment, *Temp;
    Assignment = fopen("assignlecturer.txt", "r");
    if (Assignment == NULL) {
        printf("Error Opening Assignment File.\n");
        return;
    }

    Temp = fopen("Temp.txt", "w");
    if (Temp == NULL) {
        printf("Error Opening Temporary Assignment File.\n");
        fclose(Assignment);
        return;
    }

    found = 0;
    while (fscanf(Assignment, "%[^,], %[^,], %[^,], %[^\n]\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name) == 4) {
        if (strcmp(lec_id, assignment.lecturer_id) == 0 && strcmp(old_lecturer, assignment.lecturer_name) == 0) {
            fprintf(Temp, "%s,%s,%s,%s\n", assignment.lecturer_id, new_lecturer, assignment.course_id, assignment.course_name);
            found = 1;
        } else {
            fprintf(Temp, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name);
        }
    }

    fclose(Assignment);
    fclose(Temp);
    remove("assignlecturer.txt");
    rename("Temp.txt", "assignlecturer.txt");
}

void update_student_detail_in_enrollment(char student_id[], char old_student[], char new_student[]) {
    struct StudentEnrollment enrollment;
    int found;
    FILE *enrollments, *Temp;
    enrollments = fopen("enrollment.txt", "r");
    if (enrollments == NULL) {
        printf("Error Opening Enrollment File.\n");
        return;
    }

    Temp = fopen("Temp.txt", "w");
    if (Temp == NULL) {
        printf("Error Opening Temporary Enrollment File.\n");
        fclose(enrollments);
        return;
    }

    found = 0;
    while (fscanf(enrollments, "%[^,], %[^,], %[^,], %[^,], %[^\n]\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date) == 5) {
        if (strcmp(student_id, enrollment.student_id) == 0 && strcmp(old_student, enrollment.student_name) == 0) {
            fprintf(Temp, "%s,%s,%s,%s,%s\n", enrollment.student_id, new_student, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
            found = 1;
        } else {
            fprintf(Temp, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
        }
    }
    
    fclose(enrollments);
    fclose(Temp);
    remove("enrollment.txt");
    rename("Temp.txt", "enrollment.txt");
}

void update_course_name_in_enrollment(char old_course_name[], char new_course_name[]) {
    struct StudentEnrollment enrollment;
    FILE *enrollments, *tempEnrollments;
    enrollments = fopen("enrollment.txt", "r");
    if (enrollments == NULL) {
        printf("Error Opening Enrollment File.\n");
        return;
    }

    tempEnrollments = fopen("temp_enrollment.txt", "w");
    if (tempEnrollments == NULL) {
        printf("Error Opening Temporary Enrollment File.\n");
        fclose(enrollments);
        return;
    }

    while (fscanf(enrollments, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date) == 5) {
        if (strcmp(old_course_name, enrollment.course_name) == 0) {
            fprintf(tempEnrollments, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, new_course_name, enrollment.enrolled_date);
        } 
        if (strcmp(old_course_name, enrollment.course_name) != 0) {
            fprintf(tempEnrollments, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
        }
    }
    rewind(enrollments);

    fclose(enrollments);
    fclose(tempEnrollments);
    remove("enrollment.txt");
    rename("temp_enrollment.txt", "enrollment.txt");
}

void update_course_name_in_assignment(char old_course_name[], char new_course_name[]) {
    struct Assignlecturer assignment;
    FILE *assignments, *tempAssignments;
    assignments = fopen("assignlecturer.txt", "r");
    if (assignments == NULL) {
        printf("Error Opening Assignment File.\n");
        fclose(assignments);
        return;
    }

    tempAssignments = fopen("temp_assignlecturer.txt", "w");
    if (tempAssignments == NULL) {
        printf("Error Opening Temporary Assignment File.\n");
        fclose(assignments);
        return;
    }

    while (fscanf(assignments, "%99[^,],%99[^,],%99[^,],%[^\n]\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name) == 4) {
        if (strcmp(old_course_name, assignment.course_name) == 0) {
            fprintf(tempAssignments, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, new_course_name);
        } 
        if (strcmp(old_course_name, assignment.course_name) != 0) {
            fprintf(tempAssignments, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name);
        }
    }
    rewind(assignments);

    fclose(assignments);
    fclose(tempAssignments);
    remove("assignlecturer.txt");
    rename("temp_assignlecturer.txt", "assignlecturer.txt");
}

void update_course_id_in_enrollment(char old_course_id[], char new_course_id[]) {
    struct StudentEnrollment enrollment;
    FILE *enrollments, *tempEnrollments;
    enrollments = fopen("enrollment.txt", "r");
    if (enrollments == NULL) {
        printf("Error Opening Enrollment File.\n");
        return;
    }

    tempEnrollments = fopen("temp_enrollment.txt", "w");
    if (tempEnrollments == NULL) {
        printf("Error Opening Temporary Enrollment File.\n");
        fclose(enrollments);
        return;
    }

    while (fscanf(enrollments, "%99[^,],%99[^,],%99[^,],%99[^,],%[^\n]\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date) == 5) {
        if (strcmp(old_course_id, enrollment.course_id) == 0) {
            fprintf(tempEnrollments, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, new_course_id, enrollment.course_name, enrollment.enrolled_date);
        } 
        if (strcmp(old_course_id, enrollment.course_id) != 0) {
            fprintf(tempEnrollments, "%s,%s,%s,%s,%s\n", enrollment.student_id, enrollment.student_name, enrollment.course_id, enrollment.course_name, enrollment.enrolled_date);
        }
    }
    rewind(enrollments);

    fclose(enrollments);
    fclose(tempEnrollments);
    remove("enrollment.txt");
    rename("temp_enrollment.txt", "enrollment.txt");
}

void update_course_id_in_assignment(char old_course_id[], char new_course_id[]) {
    struct Assignlecturer assignment;
    FILE *assignments, *tempAssignments;
    assignments = fopen("assignlecturer.txt", "r");
    if (assignments == NULL) {
        printf("Error Opening Assignment File.\n");
        return;
    }

    tempAssignments = fopen("temp_assignlecturer.txt", "w");
    if (tempAssignments == NULL) {
        printf("Error Opening Temporary Assignment File.\n");
        fclose(assignments);
        return;
    }

    while (fscanf(assignments, "%99[^,],%99[^,],%99[^,],%[^\n]\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name) == 4) {
        if (strcmp(old_course_id, assignment.course_id) == 0) {
            fprintf(tempAssignments, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, new_course_id, assignment.course_name);
        } 
        if (strcmp(old_course_id, assignment.course_id) != 0) {
            fprintf(tempAssignments, "%s,%s,%s,%s\n", assignment.lecturer_id, assignment.lecturer_name, assignment.course_id, assignment.course_name);
        }
    }
    rewind(assignments);

    fclose(assignments);
    fclose(tempAssignments);
    remove("assignlecturer.txt");
    rename("temp_assignlecturer.txt", "assignlecturer.txt");
}