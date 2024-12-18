#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define BUFFER_SIZE 1000

//___________________________________________________________________________________________________________________________________________________________________________________//
// Lecturer Part Code - Soh Shan Yang TP071129

//list of all the function
void Lecturer_menu(char lecture_id[]);
void view_course(char lecture[]);
void update_student_attendance(char lecture_2[]);
void view_student_attendance_1(char lecture_1[]);
void view_student_attendance_2(char val_2[]);
void student_course_mark(char lecture_3[]);
void student_course_mark_1(char val_4[]);
void view_student_mark(char lecture_4[]);
void view_lecturer_profile(char lecture_5[]);
void update_lecturer_profile (char lecture_6[]);
void upperString(char *str);

//Function use in other part
void delete_lecturer_id(char lec_id[]);
void update_course_detail_for_attendance(char old_course[], char new_course[]);
void update_course_detail_for_coursemark(char old_course_2[], char new_course_2[]);
void delete_course_detail_for_attendance(char course_delete[]);
void delete_course_detail_for_coursemark(char course_detele_2[]);
void add_course_detail_for_attendance(char course_added[], char student_name[]);
void add_course_detail_for_coursemark(char course_added_2[], char student_name[]);
void delete_student_id_for_attendance(char stu_id_2[]);
void delete_student_id_for_coursemark(char stu_id_3[]);


void update_lecturer_detail_in_assignment(char lec_id[], char old_lecturer[], char new_lecturer[]); //Function from programme adminstrator

//__________________________________________________________________________________________________________________________________________________________________________________//
//list of all the structure
struct main{
    char data[100][1000];
    int break_loop;
    int file_exist;
};

struct view_course{
    char subject_name[50];
    char subject_id[50];
    char lecture_id[100];
    char lecture_name[100];
};

struct view_student_attendance_1{
    char view_subject[100];
    int confirm;
    char data[100][1000];
};

struct view_student_attendance_2{
    char data[100][1000];
};

struct update_student_attendance{
    char which_subject[100];
    char line[1000];
    int found_course;
    int which_class, choice, states;
    char data[100][1000];
    char data_2[100][1000];
    char name[50];
};

struct view_student_mark{
    char data[100][1000];
    char course[100];
    char lecturer_id[100];
    char course_id[100];
    char lecturer_name[100];
};

struct student_course_mark{
    char courses[50];
    int confirm;
    char data[100][1000];
};

struct student_course_mark_1{
    char data[100][1000];
    char name[100];
    float new_mark;
    int confirm;
    int confirm_1;
    int success;
};

//Extra feature for lecturer part
struct view_lecturer_profile{
    char lecturer_id[100];
    char lecturer_password[100];
    char lecturer_name[100];
    char lecturer_gender[100];
    char lecturer_age[100];
    char lecturer_email[100];
    char country[1000];
};

struct update_lecturer_profile{
    int choice;
    int loop;
    int loop_2;
    char lecturer_id[100];
    char lecturer_password[100];
    char lecturer_name[100];
    char lecturer_gender[100];
    char lecturer_age[100];
    char lecturer_email[100];
    char country[1000];
    char new_name[100];
    char new_gender[100];
    char new_age[100];
    char new_email[100];
    char new_country[100];
    char confirm[10];
    char data[100][100];
};


//__________________________________________________________________________________________________________________________________________________________________________________//
//function
int check_file(char file_name[]) {
    //This function is use to check is the file exist
    int file_exist = 0;

    if (file_name == NULL) {
        printf("\n--%s file does not exist!\n", file_name);
        file_exist = 1;
        return file_exist;
    }
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("\n--%s file does not exist!\n", file_name);
        file_exist = 1;
        fclose(file);
        return file_exist;
    }
    if (fgetc(file) == EOF) {
        printf("\n--%s file content is empty!\n", file_name);
        file_exist = 1;
    }
    rewind(file);
    fclose(file);
    return file_exist; //return and store the variable 'file_exist' content
}

void Lecturer_menu(char lecture_id[]) {
    struct main m;
    m.break_loop = 0;
    char *ptr = lecture_id;

    FILE *Attendance, *CourseMark, *Lecturer;
    Lecturer = fopen("Lecturer.txt" , "r");
    
    m.file_exist = check_file("Lecturer.txt");
    if (m.file_exist == 1) {
        printf("\n--Please update the lecturer detail before you proceed!");
        fclose(Lecturer);
        return ;
    }
    rewind(Lecturer);   
    fclose(Lecturer);   

    int choice;
    while (1) {
        printf("\n_____________________________________________________________________\n");
        printf("\n");
        printf("\t-------------------------------------------\n");
        printf("\t|          Lecturer System                |\n");
        printf("\t-------------------------------------------\n");
        printf("\t|       1. View Student Attendance        |\n");
        printf("\t|       2. Update Student Attendance      |\n");
        printf("\t|       3. View Student Course Mark       |\n");
        printf("\t|       4. Update Student Course Mark     |\n");
        printf("\t|       5. View Lecturer Profile          |\n");
        printf("\t|       6. Update Lecturer Profile        |\n");
        printf("\t|       7. Exit                           |\n");
        printf("\t-------------------------------------------\n");
        printf("\n");
        printf("_____________________________________________________________________\n");

        while (1) {
            m.file_exist = 0;
            printf("\n--Please enter the number according to the list: ");
            if (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {
                printf("\n--Invalid input! Please enter a mark in a range of 1 to 7.\n");
                while (getchar() != '\n'); //clear input buffer
            } else {
                switch (choice) { //check is the file exist before procceding to other function
                    case 1:
                        Attendance = fopen("Attendance.txt", "r");
                        m.file_exist = check_file("Attendance.txt");
                        if (m.file_exist == 1) {
                            printf("\n--Please enroll student in specific course before proceeding!");
                            fclose(Attendance);
                            break;
                        }
                        fclose(Attendance);
                        view_course(ptr);
                        view_student_attendance_1(ptr);
                        break;
                    case 2:
                        Attendance = fopen("Attendance.txt", "r");
                        m.file_exist = check_file("Attendance.txt");
                        if (m.file_exist == 1) {
                            printf("\n--Please enroll student in specific course before proceeding!");
                            fclose(Attendance);
                            break;
                        }
                        fclose(Attendance);
                        view_course(ptr);
                        update_student_attendance(ptr);
                        break;
                    case 3:
                        CourseMark = fopen("CourseMark.txt", "r");
                        m.file_exist = check_file("CourseMark.txt");
                        if (m.file_exist == 1) {
                            printf("\n--Please enroll student in specific course before proceeding!");
                            fclose(CourseMark);
                            break;
                        }
                        fclose(CourseMark);
                        view_student_mark(ptr);
                        break;
                    case 4:
                        CourseMark = fopen("CourseMark.txt", "r");
                        m.file_exist = check_file("CourseMark.txt");
                        if (m.file_exist == 1) {
                            printf("\n--Please enroll student in specific course before proceeding!");
                            fclose(CourseMark);
                            break;
                        }
                        fclose(CourseMark);
                        view_course(ptr);
                        student_course_mark(ptr);
                        break;
                    case 5:
                        view_lecturer_profile(ptr);
                        break;
                    case 6:
                        update_lecturer_profile(ptr);
                        break;
                    case 7:
                        return;
                }
            }
            break;
        }
    }
}

void centerAlign(char *str, int width) {
    int length = strlen(str);
    if (width > length) {
        int padding = (width - length) / 2;
        printf("%*s%s%*s", padding, "", str, width - padding - length, "");
    } 
    else{
        printf("%.*s", width, str);
    }
}

void view_course(char lecture[]){

    struct view_course vc;

    FILE *Course;
    Course = fopen("assignlecturer.txt" , "r");

    int file_exist = check_file("assignlecturer.txt");
    if (file_exist == 1){
        printf("Please updated the course detail before you procedding!");
        fclose(Course);
        return;
    }
    rewind(Course);

    printf("_______________________________________________________________________-");
    printf("\n\n");
    printf("\t-----------------------------\n");
    printf("\t|          Courses          |\n");
    printf("\t-----------------------------\n");
    while(fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", vc.lecture_id, vc.lecture_name, vc.subject_id, vc.subject_name) == 4){
        if(strcmp(vc.lecture_id, lecture) == 0){
            printf("\t|");
            centerAlign(vc.subject_name, 27);
            printf("|\n");
        }
    }
    printf("\t-----------------------------");
    printf("\n\n");
    printf("_______________________________________________________________________-");
    rewind(Course);
    fclose(Course);


}

void view_student_attendance_1(char lecture_1[]){

    struct view_student_attendance_1 vsa1;
    vsa1.confirm = 0;

    FILE *Course;
    Course = fopen("assignlecturer.txt" , "r");
    rewind(Course);


    printf("\n--(Hint: enter '0' to end)");
    while(1){
        rewind(Course);
        getchar(); //to clean user input buffer
        printf("\n--Please enter the name of course for viewing the attendance: ");
        scanf("%99[^\n]" , vsa1.view_subject);
        upperString(vsa1.view_subject);
        while(fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", vsa1.data[0], vsa1.data[1], vsa1.data[2], vsa1.data[3]) == 4){
            if (strcmp(vsa1.view_subject, vsa1.data[3]) == 0 && strcmp(lecture_1, vsa1.data[0]) == 0){
                vsa1.confirm = 1;
                break;
            }
            if (strcmp(vsa1.view_subject, "0") == 0) {
                printf("\n--Back main page...\n");
                fclose(Course);
                return;
            }
        }

        if (vsa1.confirm == 1){
            break;
        }else{
            printf("\n--Error! Please enter the correct course name base on the list!\n");
        }

    }

    view_student_attendance_2(vsa1.view_subject);

    printf("\n--Press any key to quit: ");
    if (getch()) { // Wait for any key press
        printf("\n");
        printf("\nGoing back to main page...\n");
        fclose(Course);
    }
    fclose(Course);
}

void view_student_attendance_2(char val_2[]){

    struct view_student_attendance_2 vsa2;

    FILE *Attendance;
    Attendance = fopen("Attendance.txt" , "r");
    rewind(Attendance); // Reset file pointer to the beginning of the file
    
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", vsa2.data[0], vsa2.data[1], vsa2.data[2], vsa2.data[3], vsa2.data[4], vsa2.data[5], vsa2.data[6], vsa2.data[7], vsa2.data[8], vsa2.data[9], vsa2.data[10], vsa2.data[11], vsa2.data[12]) == 13){     
        if(strcmp(val_2, vsa2.data[0]) == 0) {
            printf("______________________________________________________________________________________________________________________\n");
            printf("\n\n");
            printf("\t-----------------------------------------------------------------------\n");
            printf("\t|                              Attendance                             |\n");
            printf("\t-----------------------------------------------------------------------\n");
            printf("\t|                          Course:");
            centerAlign(vsa2.data[0], 15);
            printf("                     |\n");
            printf("\t-----------------------------------------------------------------------\n");
            printf("\t|        Student ID        |       Tutorial       |       States      |\n");
            printf("\t-----------------------------------------------------------------------\n");
            rewind(Attendance);
            break;
        }
    }

    rewind(Attendance);
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", vsa2.data[0], vsa2.data[1], vsa2.data[2], vsa2.data[3], vsa2.data[4], vsa2.data[5], vsa2.data[6], vsa2.data[7], vsa2.data[8], vsa2.data[9], vsa2.data[10], vsa2.data[11], vsa2.data[12]) == 13){     
        if(strcmp(val_2, vsa2.data[0]) == 0) {
            printf("\t|");
            centerAlign(vsa2.data[1], 26);
            printf("|");
            centerAlign(vsa2.data[2], 22);
            printf("|");
            centerAlign(vsa2.data[3], 19);
            printf("|\n");
            printf("\t|                          ");
            printf("|");
            centerAlign(vsa2.data[4], 22);
            printf("|");
            centerAlign(vsa2.data[5], 19);
            printf("|\n");
            printf("\t|                          ");
            printf("|");
            centerAlign(vsa2.data[6], 22);
            printf("|");
            centerAlign(vsa2.data[7], 19);
            printf("|\n");
            printf("\t|                          ");
            printf("|");
            centerAlign(vsa2.data[8], 22);
            printf("|");
            centerAlign(vsa2.data[9], 19);
            printf("|\n");
            printf("\t|                          ");
            printf("|");
            centerAlign(vsa2.data[10], 22);
            printf("|");
            centerAlign(vsa2.data[11], 19);
            printf("|\n");
            printf("\t|                          ");
            printf("|  Overall Percentage  :");
            printf("       ");
            centerAlign(vsa2.data[12], 3);
            printf("%%");
            printf("        ");
            printf("|\n");
            printf("\t-----------------------------------------------------------------------\n");
        }
    } 
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");
    rewind(Attendance);
    fclose(Attendance);
    return;
}

void update_student_attendance(char lecture_2[]){
    struct update_student_attendance usa;
    usa.found_course = 0;

    FILE *Attendance;
    Attendance = fopen("Attendance.txt" , "r");
    rewind(Attendance);

    FILE *Course;
    Course = fopen("assignlecturer.txt" , "r");
    rewind(Course);

    printf("\n--(Hint: enter '0' to end)");

    while(1) {
        getchar(); // to clean user input buffer
        printf("\n--Please enter the name of course for updated attendance: ");
        scanf("%99[^\n]" , usa.which_subject);
        upperString(usa.which_subject);
        usa.found_course = 0; // Reset found_course flag
        rewind(Course);

        if (strcmp(usa.which_subject, "0") == 0) {
            printf("\n--Back main page...\n");
            fclose(Attendance);
            fclose(Course);
            return;
        }

        while(fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", usa.data_2[0], usa.data_2[1], usa.data_2[2], usa.data_2[3]) == 4){
            if (strcmp(usa.which_subject, usa.data_2[3]) == 0 && strcmp(lecture_2, usa.data_2[0]) == 0){
                usa.found_course = 1;
                fclose(Course);
                break;
            }
        }
        

        if (!usa.found_course) {
            printf("\n--The course does not exist!\n");
        } else {
            printf("_______________________________________________________________________\n");
            printf("\n\n");
            printf("\t\t---------------------------------------\n");
            printf("\t\t|       Course:");
            centerAlign(usa.which_subject, 10);
            printf("             |\n");
            printf("\t\t---------------------------------------\n");
            printf("\t\t|       1)      |     Tutorial_1      |\n");
            printf("\t\t|       2)      |     Tutorial_2      |\n");
            printf("\t\t|       3)      |     Tutorial_3      |\n");
            printf("\t\t|       4)      |     Tutorial_4      |\n");
            printf("\t\t|       5)      |     Tutorial_5      |\n");
            printf("\t\t---------------------------------------\n");
            printf("\n\n");
            printf("_______________________________________________________________________\n");
            break;  
        }
    }
    printf("\n--(Hint: enter '0' to end)");
    while (1) {
        printf("\n--Please select which tutorial to update (1 to 5): ");
        if (scanf("%d", &usa.choice) != 1 || usa.choice < 0 || usa.choice > 5) {
            printf("\n--Invalid input! Please enter a number between 1 and 5.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            // Assign the corresponding class based on the user's choice
            switch (usa.choice) {
                case 0:
                    printf("\n--Back main page...\n");
                    fclose(Attendance);
                    return;
                case 1:
                    usa.which_class = 3;
                    break;
                case 2:
                    usa.which_class = 5;
                    break;
                case 3:
                    usa.which_class = 7;
                    break;
                case 4:
                    usa.which_class = 9;
                    break;
                case 5:
                    usa.which_class = 11;
                    break;
            }
            break; // Exit the loop if input is valid
        }
    }

    rewind(Attendance); // Reset file pointer to the beginning of the file
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usa.data[0], usa.data[1], usa.data[2], usa.data[3], usa.data[4], usa.data[5], usa.data[6], usa.data[7], usa.data[8], usa.data[9], usa.data[10], usa.data[11], usa.data[12]) == 13){     
        if(strcmp(usa.which_subject, usa.data[0]) == 0) {
            printf("______________________________________________________________________________________________________________________\n");
            printf("\n");
            printf("\n");
            printf("\t-----------------------------------------------------\n");
            printf("\t|                  Attendance                       |\n");
            printf("\t-----------------------------------------------------\n");
            printf("\t|                  Course:");
            centerAlign(usa.data[0], 22);
            printf("    |\n");
            printf("\t-----------------------------------------------------\n");
            printf("\t|                    Tutorial: %s                    |\n" , usa.data[usa.which_class - 1]);
            printf("\t-----------------------------------------------------\n");
            printf("\t|      Student ID           |         States        |\n");
            printf("\t-----------------------------------------------------\n");
            rewind(Attendance);
            break; // to make sure print one times only
        }
    }
    //show all the student name who enroll in course 
    rewind(Attendance);
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usa.data[0], usa.data[1], usa.data[2], usa.data[3], usa.data[4], usa.data[5], usa.data[6], usa.data[7], usa.data[8], usa.data[9], usa.data[10], usa.data[11], usa.data[12]) == 13){     
        if(strcmp(usa.which_subject, usa.data[0]) == 0) {
            printf("\t|");
            centerAlign(usa.data[1], 23);
            printf("    |");
            centerAlign(usa.data[usa.which_class], 23);
            printf("|\n");
        }
    } 
    printf("\t-----------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");
    rewind(Attendance);

    int confirm = 0;
    printf("\n--(Hint: enter '0' to end)");
    while(1){
        getchar();
        rewind(Attendance);
        printf("\n--Please enter the student ID that you would like to modify the state of: ");
        scanf("%99[^\n]" , usa.name);
        upperString(usa.name);
        while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usa.data[0], usa.data[1], usa.data[2], usa.data[3], usa.data[4], usa.data[5], usa.data[6], usa.data[7], usa.data[8], usa.data[9], usa.data[10], usa.data[11], usa.data[12]) == 13){     
            if(strcmp(usa.which_subject, usa.data[0]) == 0 && strcmp(usa.name, usa.data[1]) == 0){
                printf("\n--Successful Access\n");
                confirm = 1;
                break;
            }

            if(strcmp(usa.name, "0") == 0){
                printf("\n--Back main page...\n");
                fclose(Attendance);
                return;
            }
        }
        if (confirm == 1){
            break;
        }else{
            printf("\n--Error! Student '%s' not founded\n" , usa.name);
        }
    }

    // function of update attendance for a student
    int success = 0; // Initialize success flag outside the loop
    while (1) {
        rewind(Attendance);
        success = 0; // Reset success flag at the beginning of each iteration

        while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usa.data[0], usa.data[1], usa.data[2], usa.data[3], usa.data[4], usa.data[5], usa.data[6], usa.data[7], usa.data[8], usa.data[9], usa.data[10], usa.data[11], usa.data[12]) == 13){     
            if (strcmp(usa.which_subject, usa.data[0]) == 0 && strcmp(usa.name, usa.data[1]) == 0) {
                printf("\n--Please choose for changing the state (1 for Attend / 2 for Absent / 3 for NULL): ");
                if (scanf("%d", &usa.states) != 1) {
                    printf("\n--Invalid input! Please enter a number.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue; // Prompt again for input
                }

                if(usa.states == 0){
                    printf("\n--Back main page...\n");
                    fclose(Attendance);
                    return;
                }

                if (usa.states >= 1 && usa.states <= 3) {
                    if (usa.which_class >= 0 && usa.which_class < 100) {
                        switch (usa.states) {
                            case 1:
                                strcpy(usa.data[usa.which_class], "Attend");
                                break;
                            case 2:
                                strcpy(usa.data[usa.which_class], "Absent");
                                break;
                            case 3:
                                strcpy(usa.data[usa.which_class], "NULL");
                                break;
                        }
                        success = 1; // Set success flag to 1 inside the loop
                    } else {
                        printf("\n--Error: No_class index out of bounds.\n");
                    }
                } else {
                    printf("\n--Invalid choice! Please choose 1, 2, or 3.\n");
                    continue; // Prompt again for input
                }
                // To check how many "Attend" in a line
                int att = 0;
                int found = 0;
                int percentage = 0;

                if(strcmp(usa.data[3], "Attend") == 0){
                    found = 1;
                    att++;
                }
                if(strcmp(usa.data[5], "Attend") == 0){
                    found = 1;
                    att++;
                }
                if(strcmp(usa.data[7], "Attend") == 0){
                    found = 1;
                    att++;
                }
                if(strcmp(usa.data[9], "Attend") == 0){
                    found = 1;
                    att++;
                }
                if(strcmp(usa.data[11], "Attend") == 0){
                    found = 1;
                    att++;
                }
                if(!found){
                    break;
                }

                percentage = ((float)att / 5) * 100;
                sprintf(usa.data[12], "%d", percentage);

                rewind(Attendance);
                break;
            }
        
        }

        if (success == 1) {
            break; // Exit the outer loop if success is 1
        } 
    }


    if (success == 1){
        rewind(Attendance);
        //Allocate the line that modified
        int lines = 0;
        char buffer[BUFFER_SIZE];

        while (fgets(buffer, BUFFER_SIZE, Attendance) != NULL){  
            if (strlen(buffer) > 1){
                lines++;
            }

            if ((strstr(buffer, usa.name) != NULL) && (strstr(buffer, usa.which_subject) != NULL)){
                break;
            }
        } 

        //Put the modified data into temp file
        int count = 0;
        FILE *Temp;
        Temp = fopen("Temp.txt" , "w");
        rewind(Attendance);
        while ((fgets(buffer, BUFFER_SIZE, Attendance)) != NULL){ //put the content of file into "buffer"
            count++; //when the line contain information it will auto add up "count" number, else stop add up "count" number

            if (count == lines){
                fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", usa.data[0], usa.data[1], usa.data[2], usa.data[3], usa.data[4], usa.data[5], usa.data[6], usa.data[7], usa.data[8], usa.data[9], usa.data[10], usa.data[11], usa.data[12]);
                // Write the modified data to the temporary file

            }else{
                fputs(buffer, Temp); // Write unmodified data to the temporary file
            }
            
        }
        fclose(Attendance);
        fclose(Temp);

        remove("Attendance.txt");
        
        rename("Temp.txt" , "Attendance.txt");

        printf("\n--Attendance updated successfully!\n");
    }
}

void view_student_mark(char lecture_4[]){

    struct view_student_mark vsm;

    FILE *CourseMark;
    CourseMark = fopen("CourseMark.txt" , "r");
    rewind(CourseMark);

    FILE *Course;
    Course = fopen("assignlecturer.txt" , "r");
    rewind(Course);

    printf("______________________________________________________________________________________________________________________\n");
    printf("\n\n");
    printf("\t---------------------------------------------------------------\n");
    printf("\t|       Course       |        ID        |       Mark(%%)       |\n");
    printf("\t---------------------------------------------------------------\n");
    while (fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", vsm.lecturer_id, vsm.lecturer_name, vsm.course_id, vsm.course) == 4) { // Iterate over each line in Course.txt
        rewind(CourseMark);
        while (fscanf(CourseMark, "%[^,], %[^,], %[^\n]\n", vsm.data[0], vsm.data[1], vsm.data[2]) == 3) {
            if (strcmp(vsm.data[0], vsm.course) == 0 && strcmp(lecture_4, vsm.lecturer_id) == 0){ 
                printf("\t|");
                centerAlign(vsm.data[0], 20);
                printf("|");
                centerAlign(vsm.data[1], 18);
                printf("|");
                centerAlign(vsm.data[2], 21);
                printf("|");
                printf("\n");
            }
        }
    }
    printf("\t---------------------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");

    printf("\n--Press any key to quit: ");
    if (getch()) { // Wait for any key press
        printf("\n");
        printf("\nGoing back to main page...\n");
        fclose(CourseMark);
        fclose(Course);
    }
    fclose(CourseMark);
    fclose(Course);
}

void student_course_mark(char lecture_3[]){
    
    struct student_course_mark scm;
    scm.confirm = 0;

    FILE *Course;
    Course = fopen("assignlecturer.txt" , "r");
    rewind(Course);

    printf("\n--(Hint: enter '0' to end)");
    while(1){
        rewind(Course);
        getchar();
        printf("\n--Please enter the name of course for updated marks: ");
        scanf("%99[^\n]" , scm.courses);
        upperString(scm.courses);
        while(fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", scm.data[0], scm.data[1], scm.data[2], scm.data[3]) == 4){
            if(strcmp(scm.courses, scm.data[3]) == 0 && strcmp(lecture_3, scm.data[0]) == 0){
                scm.confirm = 1;
                fclose(Course);
                student_course_mark_1(scm.courses);
                break;
            }            
            
            if(strcmp(scm.courses, "0") == 0){
                printf("\n--Back main page...\n");
                fclose(Course);
                return;
            }
        }
        if (scm.confirm == 1){ //break out from the loop
            break;
        }else{
            printf("\n--Error! Please enter the correct course name base on the list!\n");
        }
    }
}

void student_course_mark_1(char val_4[]){

    struct student_course_mark_1 scm1;
    scm1.confirm = 0;
    scm1.confirm_1 = 0;
    scm1.success = 0;

    FILE *CourseMark;
    CourseMark = fopen("CourseMark.txt" , "r");
    rewind(CourseMark);

    //view student name and mark according to the course
    printf("______________________________________________________________________________________________________________________\n");
    printf("\n\n");
    printf("\t-----------------------------------------------------\n");
    printf("\t|                  Course:");
    while(fscanf(CourseMark, "%[^,], %[^,], %[^\n]\n", scm1.data[0], scm1.data[1], scm1.data[2]) == 3){ 
        if (strcmp(val_4, scm1.data[0]) == 0){
            centerAlign(scm1.data[0], 10);
            break; //only print the course name once
        }
    }
    rewind(CourseMark);
    printf("\t\t    |\n");
    printf("\t-----------------------------------------------------\n");
    printf("\t|      Student ID           |        Marks(%%)      |\n");
    printf("\t-----------------------------------------------------\n");
    rewind(CourseMark);
    while(fscanf(CourseMark, "%[^,], %[^,], %[^\n]\n", scm1.data[0], scm1.data[1], scm1.data[2]) == 3){ 
        if (strcmp(val_4, scm1.data[0]) == 0){
            printf("\t|");
            centerAlign(scm1.data[1] , 23);
            printf("    |");
            centerAlign(scm1.data[2], 23);
            printf("|\n");
        }
    }    
    printf("\t-----------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");

    rewind(CourseMark);
    printf("\n--(Hint: enter '0' to end)");
    while(fscanf(CourseMark, "%[^,], %[^,], %[^\n]\n", scm1.data[0], scm1.data[1], scm1.data[2]) == 3){ 
        while(1){
            rewind(CourseMark);
            getchar();
            printf("\n--Plese enter the student ID that would like to update course mark: ");
            scanf("%99[^\n]" , scm1.name);
            upperString(scm1.name);
            while(fscanf(CourseMark, "%[^,], %[^,], %[^\n]\n", scm1.data[0], scm1.data[1], scm1.data[2]) == 3){ 
                if (strcmp(scm1.name, scm1.data[1]) == 0 && strcmp(val_4, scm1.data[0]) == 0){
                    printf("\n--Successful\n");
                    scm1.confirm = 1;
                    break;
                }
                // when user enter "0" quit the whole function
                if(strcmp(scm1.name, "0") == 0){
                    printf("\n--Back main page...\n");
                    fclose(CourseMark);
                    return;
                }
            }
            if (scm1.confirm == 1){
                break;
            }else{
                printf("\n--Student '%s' not founded!\n" , scm1.name);
            }
        }

        rewind(CourseMark);
        while(1){
            rewind(CourseMark);
            printf("\n--Please enter new mark for the selected student: ");
            // make sure the input is in the range of 0 to 100
            if (scanf("%f", &scm1.new_mark) != 1 || scm1.new_mark < 0 || scm1.new_mark > 100){
                printf("\n--Invalid input! Please enter a mark in a range of 0 to 100.\n");
                while(getchar() != '\n'); //clear input buffer

            } else if ((int)(scm1.new_mark * 1000) % 10 != 0){ //to make sure only 2 decimal places allow
                printf("\n--Invalid input! Please enter a number with exactly two decimal places.\n");
                while(getchar() != '\n'); //clear input buffer

            } else {
                printf("\n--Successfully updated!\n");
                scm1.confirm_1 = 1;
                break;
            }
            if (scm1.confirm_1 == 1){
                break;
            }
            
        }
        scm1.success = 1;
        sprintf(scm1.data[2], "%.2f", scm1.new_mark);
        break;
    }
    
    if (scm1.success == 1){
        //locate the line to modified
        rewind(CourseMark);
        int lines = 0;
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, CourseMark) != NULL){
            if (strlen(buffer) > 1){
                lines++;
            }

            if (strstr(buffer, scm1.name) != NULL && strstr(buffer, val_4) != NULL){
                break;
            }
        }
        rewind(CourseMark);

        int count = 0;
        FILE *Temp;
        Temp = fopen("Temp.txt" , "w");
        while ((fgets(buffer, BUFFER_SIZE, CourseMark)) != NULL){
            count++;

            if (count == lines){
                fprintf(Temp, "%s,%s,%s\n", scm1.data[0], scm1.data[1], scm1.data[2]);
            } else {
                fputs(buffer, Temp);
            }
        }
        fclose(CourseMark);
        fclose(Temp);

        remove("CourseMark.txt");
        rename("Temp.txt" , "CourseMark.txt");
    }
}

//Extra feature for lecturer part
void view_lecturer_profile(char lecture_5[]){

    struct view_lecturer_profile vlp;


    FILE *Lecturer;
    Lecturer = fopen("Lecturer.txt" , "r");
    rewind(Lecturer);

    printf("______________________________________________________________________________________________________________________\n");
    printf("\n\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\t|                           Lecturer Profile                          |\n");
    printf("\t-----------------------------------------------------------------------\n");
    while (fscanf(Lecturer, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", vlp.lecturer_id, vlp.lecturer_password, vlp.lecturer_name, vlp.lecturer_gender, vlp.lecturer_age, vlp.lecturer_email, vlp.country) == 7) {
        if (strcmp(lecture_5, vlp.lecturer_id) == 0){
            printf("\t|      ID      |");
            centerAlign(vlp.lecturer_id, 54);
            printf("|\n");
            printf("\t|     Name     |");
            centerAlign(vlp.lecturer_name, 54);
            printf("|\n");
            printf("\t|    Gender    |");
            centerAlign(vlp.lecturer_gender, 54);
            printf("|\n");
            printf("\t|      Age     |");
            centerAlign(vlp.lecturer_age, 54);
            printf("|\n");
            printf("\t|     Email    |");
            centerAlign(vlp.lecturer_email, 54);
            printf("|\n");
            printf("\t|    Country   |");
            centerAlign(vlp.country, 54);
            printf("|\n");
        }
    
    }
    printf("\t-----------------------------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");
    rewind(Lecturer);
    fclose(Lecturer);

    printf("\n--Press any key to quit: ");
    if (getch()) { // Wait for any key press
        printf("\n");
        printf("\nGoing back to main page...\n");
    }
}

void update_lecturer_profile (char lecture_6[]){
    struct update_lecturer_profile ulp;
    char lec_id[100];
    char old_lecturer[100];
    char new_lecturer[100];

    FILE *Lecturer;
    Lecturer = fopen("Lecturer.txt" , "r");
    rewind(Lecturer);

    // Assign all the data to variable, by confirm which lecturer is
    while (fscanf(Lecturer, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", ulp.lecturer_id, ulp.lecturer_password, ulp.lecturer_name, ulp.lecturer_gender, ulp.lecturer_age, ulp.lecturer_email, ulp.country) == 7) {
        if (strcmp(lecture_6, ulp.lecturer_id) == 0){
            strcpy(lec_id, lecture_6);
            break;
        }
    }
    //print lecturer detail
    printf("______________________________________________________________________________________________________________________\n");
    printf("\n\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\t|                           Lecturer Profile                          |\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\t|      ID      |");
    centerAlign(ulp.lecturer_id, 54);
    printf("|\n");
    printf("\t|     Name     |");
    centerAlign(ulp.lecturer_name, 54);
    printf("|\n");
    printf("\t|    Gender    |");
    centerAlign(ulp.lecturer_gender, 54);
    printf("|\n");
    printf("\t|      Age     |");
    centerAlign(ulp.lecturer_age, 54);
    printf("|\n");
    printf("\t|     Email    |");
    centerAlign(ulp.lecturer_email, 54);
    printf("|\n");
    printf("\t|    Country   |");
    centerAlign(ulp.country, 54);
    printf("|\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");
    rewind(Lecturer);

    while(1){
        ulp.loop = 0;
        ulp.loop_2 = 0;
        printf("\n1. Name\n2. Gender\n3. Age\n4. Email\n5. Country"); //asking user to choose which part of profile to modify
        printf("\n--Please choose according to the number provided to update the lecturer profile: ");
        if(scanf("%d", &ulp.choice) != 1 || ulp.choice < 0 || ulp.choice > 5){
            printf("\n--Invalid input! Please enter according to the number provided.\n");
            while (getchar() != '\n');
        }else{
            switch(ulp.choice){
                case 0:
                    return;
                case 1:
                    getchar();
                    int confirm = 0;
                    while (1) {
                        printf("\n--Please enter new name: ");
                        scanf("%99[^\n]", ulp.new_name);
                        upperString(ulp.new_name);
                        while (getchar() != '\n'); // clear input buffer

                        confirm = 1; // Assume the new name is unique
                        while (fscanf(Lecturer, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", ulp.data[0], ulp.data[1], ulp.data[2], ulp.data[3], ulp.data[4], ulp.data[5], ulp.data[6]) == 7) {
                            if (strcmp(ulp.new_name, ulp.data[2]) == 0) {
                                printf("\nError! The name has exist please enter another new name!\n");
                                confirm = 0; // The new name is not unique
                                break;
                            }
                        }

                        if (confirm == 1 || feof(Lecturer)) {
                            break; // Either a unique name was found or end-of-file was reached
                        }
                    }

                    strcpy(old_lecturer, ulp.lecturer_name);
                    strcpy(new_lecturer, ulp.lecturer_name);
                    strcpy(ulp.lecturer_name, ulp.new_name);
                    strcpy(new_lecturer, ulp.new_name);
                    ulp.loop = 1;
                    break;
                case 2:
                    getchar();
                    printf("\n--Please enter new gender: ");
                    scanf("%99[^\n]", ulp.new_gender);
                    strcpy(ulp.lecturer_gender, ulp.new_gender);
                    ulp.loop = 1;
                    break;
                case 3:
                    getchar();
                    printf("\n--Please enter new age: ");
                    scanf("%99[^\n]", ulp.new_age);
                    strcpy(ulp.lecturer_age, ulp.new_age);
                    ulp.loop = 1;
                    break;
                case 4:
                    getchar();
                    printf("\n--Please enter new email: ");
                    scanf("%99[^\n]", ulp.new_email);
                    strcpy(ulp.lecturer_email, ulp.new_email);
                    ulp.loop = 1;
                    break;
                case 5:
                    getchar();
                    printf("\n--Please enter new coutry: ");
                    scanf("%99[^\n]", ulp.new_country);
                    strcpy(ulp.country, ulp.new_country);
                    ulp.loop = 1;
                    break;
            }
        }
        if(ulp.loop == 1){
            while(1){
                printf("\n--Are you willing to continue to modify?(Y/N): "); // asking user weather to continue
                scanf("%s" , ulp.confirm);
                upperString(ulp.confirm);
                if (strcmp(ulp.confirm , "Y") == 0){
                    break;
                } else if (strcmp(ulp.confirm , "N") == 0){
                    ulp.loop_2 = 1;
                    break;
                } else{
                    printf("\n--Invalid input! Please enter 'Y' or 'N' only\n");
                }
            }
            if (ulp.loop_2 == 1){
                break; //break if the user choose not to continue modify, else continue back to the loop 
            }
        }
    }

    if (ulp.loop == 1){
        getchar();
        rewind(Lecturer);
        //Allocate the line that modified
        int lines = 0;
        char buffer[BUFFER_SIZE];
        //Allocate the line already modified
        while (fgets(buffer, BUFFER_SIZE, Lecturer) != NULL){  
            if (strlen(buffer) > 1){
                lines++;
            }

            if ((strstr(buffer, lecture_6) != NULL)){
                break;
            }
        } 

        int count = 0;
        FILE *Temp;
        Temp = fopen("Temp.txt" , "w");
        rewind(Lecturer);
        while ((fgets(buffer, BUFFER_SIZE, Lecturer)) != NULL){ //put the content of file into "buffer"
            count++; //when the line contain information it will auto add up "count" number, else stop add up "count" number

            if (count == lines){
                fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s\n", ulp.lecturer_id, ulp.lecturer_password, ulp.lecturer_name, ulp.lecturer_gender, ulp.lecturer_age, ulp.lecturer_email, ulp.country);
                // Write the modified data to the temporary file

            }else{
                fputs(buffer, Temp); // Write unmodified data to the temporary file
            }
        }
        fclose(Lecturer);
        fclose(Temp);

        remove("Lecturer.txt");
        rename("Temp.txt" , "Lecturer.txt");

        printf("\n--Lecturer updated successfully!\n");
        update_lecturer_detail_in_assignment(lec_id, old_lecturer, new_lecturer);
    }
}


//Function that use in other part 
void delete_lecturer_id(char lec_id[]) {
    char data[100][1000];
    FILE *Course, *Temp;
    Course = fopen("assignlecturer.txt", "r");
    if (Course == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    Temp = fopen("Temp.txt", "w");
    while (fscanf(Course, "%[^,], %[^,], %[^,], %[^\n]\n", data[0], data[1], data[2], data[3]) == 4) {
        if (strcmp(lec_id, data[0]) != 0) { //if the lec id is not same than written the data for not deleted
            fprintf(Temp, "%s,%s,%s,%s\n", data[0], data[1], data[2], data[3]);
        }
    }

    fclose(Course);
    fclose(Temp);

    remove("assignlecturer.txt");
    rename("Temp.txt", "assignlecturer.txt");
}

void update_course_detail_for_attendance(char old_course[], char new_course[]) {
    char data[100][1000];
    FILE *Attendance;
    Attendance = fopen("Attendance.txt", "r");
    FILE *Temp;
    Temp = fopen("Temp.txt", "w");


    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]) == 13) {
        if (strcmp(old_course, data[0]) == 0) {
            fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", new_course, data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]);
        }
        if (strcmp(old_course, data[0]) != 0){
            fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]);
        }
    }

    rewind(Attendance);

    fclose(Attendance);
    fclose(Temp);
    remove("Attendance.txt");
    rename("Temp.txt", "Attendance.txt");
}

void update_course_detail_for_coursemark(char old_course_2[], char new_course_2[]){
    char data[100][1000];
    FILE *Mark;
    Mark = fopen("CourseMark.txt", "r");
    FILE *Temp;
    Temp = fopen("Temp.txt", "w");


    while (fscanf(Mark, "%[^,], %[^,], %[^\n]\n", data[0], data[1], data[2]) == 3) {
        if (strcmp(old_course_2, data[0]) == 0) {
            fprintf(Temp, "%s,%s,%s\n", new_course_2, data[1], data[2]);
        }
        if (strcmp(old_course_2, data[0]) != 0){
            fprintf(Temp, "%s,%s,%s\n", data[0], data[1], data[2]);
        }
    }

    rewind(Mark);

    fclose(Mark);
    fclose(Temp);
    remove("CourseMark.txt");
    rename("Temp.txt", "CourseMark.txt");
}

void delete_course_detail_for_attendance(char course_delete[]){
    char data[100][1000];
    FILE *Attendance, *Temp;
    Attendance = fopen("Attendance.txt", "r");
    if (Attendance == NULL){
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    Temp = fopen("Temp.txt" , "w");
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]) == 13) {
        if(strcmp(course_delete, data[0]) != 0){
            fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]);
        }

    }
    rewind(Attendance);

    fclose(Attendance);
    fclose(Temp);
    remove("Attendance.txt");
    rename("Temp.txt", "Attendance.txt");

}

void delete_course_detail_for_coursemark(char course_detele_2[]){
    char data[100][1000];
    FILE *Mark, *Temp;
    Mark = fopen("CourseMark.txt", "r");
    if (Mark == NULL){
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    Temp = fopen("Temp.txt" , "w");
    while (fscanf(Mark, "%[^,], %[^,], %[^\n]\n", data[0], data[1], data[2]) == 3) {
        if(strcmp(course_detele_2, data[0]) != 0){
            fprintf(Temp, "%s,%s,%s\n", data[0], data[1], data[2]);
        }

    }
    rewind(Mark);

    fclose(Mark);
    fclose(Temp);
    remove("CourseMark.txt");
    rename("Temp.txt", "CourseMark.txt");
}

void add_course_detail_for_attendance(char course_added[], char student_name[]){
    FILE *Attendance;
    Attendance = fopen("Attendance.txt" , "a");

    fprintf(Attendance, "%s,%s,1,NULL,2,NULL,3,NULL,4,NULL,5,NULL,0\n", course_added, student_name);

    rewind(Attendance);
    fclose(Attendance);

}

void add_course_detail_for_coursemark(char course_added_2[], char student_name[]){
    FILE *Mark;
    Mark = fopen("CourseMark.txt" , "a");

    fprintf(Mark, "%s,%s,0\n", course_added_2, student_name);

    rewind(Mark);
    fclose(Mark);

}

void delete_student_id_for_attendance(char stu_id_2[]){
    char data[100][100];
    FILE *Attendance, *Temp;
    Attendance = fopen("Attendance.txt" , "r");
    if (Attendance == NULL){
        printf("\nError opening file");
        exit(EXIT_FAILURE);
    }

    Temp = fopen("Temp.txt" , "w");

    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]) == 13) {
        if (strcmp(stu_id_2, data[1]) != 0){
            fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]);
        }
    }
    

    fclose(Attendance);
    fclose(Temp);

    remove("Attendance.txt");
    rename("Temp.txt" , "Attendance.txt");
}

void delete_student_id_for_coursemark(char stu_id_3[]){
    char data[100][100];
    FILE *Mark, *Temp;
    Mark = fopen("CourseMark.txt" , "r");
    if (Mark == NULL){
        printf("\nError opening file");
        exit(EXIT_FAILURE);
    }

    Temp = fopen("Temp.txt" , "w");
    while (fscanf(Mark, "%[^,], %[^,], %[^\n]\n", data[0], data[1], data[2]) == 3) {
        if (strcmp(stu_id_3, data[1]) != 0){
            fprintf(Temp, "%s,%s,%s\n", data[0], data[1], data[2]);
        }
    }

    fclose(Mark);
    fclose(Temp);

    remove("CourseMark.txt");
    rename("Temp.txt" , "CourseMark.txt");
}


