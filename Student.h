#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define BUFFER_SIZE 1000


//_____________________________________________________________________________________________________________________________________________________________________________]
//Student Part Code - Chin Tung Lok
void student_menu(char student_id[]);
void update_student_profile(char student_id_2[]);
void view_course_grades_cgpa(char student_id_3[]);
void view_attendance(char student_id_4[]);

void update_student_detail_in_enrollment(char student_id[], char old_student[], char new_student[]); //Function from programme adminstrator

struct student_menu{
    int choice;
};

struct update_student_profile{
    char student_id[100];
    char password[100];
    char student_name[100];
    char gender[100];
    char age[100];
    char email[100];
    char country[100];
    char data[100][100];

    char new_student_name[100];
    char new_gender[100];
    char new_age[100];
    char new_email[100];
    char new_country[100];

    int choice;
    int loop;
    int loop_2;
    char confirm[10];
};

struct view_course_grades_cgpa {
    char course[100];
    char studentID[100];
    double mark;
    int grade_mark_1;
    int grade_mark_2;
    char grade[100];
    double CGPA;
    char string_GGPA[100];
    char string_mark[100];
};


void student_menu(char student_id[]){
    struct student_menu SM;

    while(1){
        printf("\n------------------------------------------");
        printf("\n|              Student Menu              |");
        printf("\n------------------------------------------");
        printf("\n| 1. Update Student Personal Profile     |");
        printf("\n| 2. View Course Enrolled, Grades, CGPA  |");
        printf("\n| 3. View Attendance                     |");
        printf("\n| 4. Exit                                |");
        printf("\n------------------------------------------");


        printf("\n Please enter your choice: ");
        if (scanf("%d", &SM.choice) != 1) {
            printf("\nInvalid input! Please enter an integer.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (SM.choice < 1 || SM.choice > 4) {
            printf("\nInvalid choice! Please enter a number between 1 and 4.\n");
            continue;
        }

        switch(SM.choice){
            case 1:
                update_student_profile(student_id);
                break;
            case 2:
                view_course_grades_cgpa(student_id);
                break;
            case 3:
                view_attendance(student_id);
                break;
            case 4:
                printf("\nExisting to login page\n");
                return;
        }
    }
}

void update_student_profile(char student_id_2[]){
    
    struct update_student_profile usp;
    char student_id[100];
    char old_student[100];
    char new_student[100];
    FILE *Student;
    Student = fopen("student.txt" , "r");
    rewind(Student);

    while (fscanf(Student, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usp.student_id, usp.password, usp.student_name, usp.gender, usp.age, usp.email, usp.country) == 7) {
        if (strcmp(student_id_2, usp.student_id) == 0){
            strcpy(student_id, student_id_2);
            break;
        }
    }
    //print student detail
    printf("______________________________________________________________________________________________________________________\n");
    printf("\n\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\t|                            Student Profile                          |\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\t|      ID      |");
    centerAlign(usp.student_id, 54);
    printf("|\n");
    printf("\t|     Name     |");
    centerAlign(usp.student_name, 54);
    printf("|\n");
    printf("\t|    Gender    |");
    centerAlign(usp.gender, 54);
    printf("|\n");
    printf("\t|      Age     |");
    centerAlign(usp.age, 54);
    printf("|\n");
    printf("\t|     Email    |");
    centerAlign(usp.email, 54);
    printf("|\n");
    printf("\t|    Country   |");
    centerAlign(usp.country, 54);
    printf("|\n");
    printf("\t-----------------------------------------------------------------------\n");
    printf("\n\n");
    printf("______________________________________________________________________________________________________________________\n");
    rewind(Student);

    while(1){
        usp.loop = 0;
        usp.loop_2 = 0;
        printf("\nEnter '0' to quit");
        printf("\n1. Name\n2. Gender\n3. Age\n4. Email\n5. Country"); //asking user to choose which part of profile to modify
        printf("\n--Please choose according to the number provided to update the student profile: ");
        if(scanf("%d", &usp.choice) != 1 || usp.choice < 0 || usp.choice > 5){
            printf("\n--Invalid input! Please enter according to the number provided.\n");
            while (getchar() != '\n');
        }else{
            switch(usp.choice){
                case 0:
                    return;
                case 1:
                    getchar();
                    int confirm = 0;
                    while (1) {
                        printf("\n--Please enter new name: ");
                        scanf("%99[^\n]", usp.new_student_name);
                        upperString(usp.new_student_name);
                        while (getchar() != '\n'); // clear input buffer

                        confirm = 1; // Assume the new name is unique
                        while (fscanf(Student, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", usp.data[0], usp.data[1], usp.data[2], usp.data[3], usp.data[4], usp.data[5], usp.data[6]) == 7) {
                            if (strcmp(usp.new_student_name, usp.data[2]) == 0) {
                                printf("\nError! The name has exist please enter another new name!\n");
                                confirm = 0; // The new name is not unique
                                break;
                            }
                        }

                        if (confirm == 1 || feof(Student)) {
                            break; // Either a unique name was found or end-of-file was reached
                        }
                    }
                    strcpy(old_student,usp.student_name);
                    strcpy(new_student,usp.student_name);
                    strcpy(usp.student_name, usp.new_student_name);
                    strcpy(new_student, usp.new_student_name);
                    usp.loop = 1;
                    break;
                case 2:
                    getchar();
                    printf("\n--Please enter new gender: ");
                    scanf("%99[^\n]", usp.new_gender);
                    strcpy(usp.gender, usp.new_gender);
                    usp.loop = 1;
                    break;
                case 3:
                    getchar();
                    printf("\n--Please enter new age: ");
                    scanf("%99[^\n]", usp.new_age);
                    strcpy(usp.age, usp.new_age);
                    usp.loop = 1;
                    break;
                case 4:
                    getchar();
                    printf("\n--Please enter new email: ");
                    scanf("%99[^\n]", usp.new_email);
                    strcpy(usp.email, usp.new_email);
                    usp.loop = 1;
                    break;
                case 5:
                    getchar();
                    printf("\n--Please enter new coutry: ");
                    scanf("%99[^\n]", usp.new_country);
                    strcpy(usp.country, usp.new_country);
                    usp.loop = 1;
                    break;
            }
        }
        if(usp.loop == 1){
            while(1){
                printf("\n--Are you willing to continue to modify?(Y/N): "); // asking user weather to continue
                scanf("%s" , usp.confirm);
                upperString(usp.confirm);
                if (strcmp(usp.confirm , "Y") == 0){
                    break;
                } else if (strcmp(usp.confirm , "N") == 0){
                    usp.loop_2 = 1;
                    break;
                } else{
                    printf("\n--Invalid input! Please enter 'Y' or 'N' only\n");
                }
            }
            if (usp.loop_2 == 1){
                break; //break if the user choose not to continue modify, else continue back to the loop 
            }
        }
    }

    if (usp.loop == 1){
        getchar();
        rewind(Student);
        //Allocate the line that modified
        int lines = 0;
        char buffer[BUFFER_SIZE];
        //Allocate the line already modified
        while (fgets(buffer, BUFFER_SIZE, Student) != NULL){  
            if (strlen(buffer) > 1){
                lines++;
            }

            if ((strstr(buffer, student_id_2) != NULL)){
                break;
            }
        } 

        int count = 0;
        FILE *Temp;
        Temp = fopen("Temp.txt" , "w");
        rewind(Student);
        while ((fgets(buffer, BUFFER_SIZE, Student)) != NULL){ //put the content of file into "buffer"
            count++; //when the line contain information it will auto add up "count" number, else stop add up "count" number

            if (count == lines){
                fprintf(Temp, "%s,%s,%s,%s,%s,%s,%s\n", usp.student_id, usp.password, usp.student_name, usp.gender, usp.age, usp.email, usp.country);
                // Write the modified data to the temporary file

            }else{
                fputs(buffer, Temp); // Write unmodified data to the temporary file
            }
        }
        fclose(Student);
        fclose(Temp);

        remove("student.txt");
        rename("Temp.txt" , "student.txt");

        printf("\n--Student Profile updated successfully!\n");
        update_student_detail_in_enrollment(student_id, old_student, new_student);
    }

}

void view_course_grades_cgpa(char student_id_3[]) {
    struct view_course_grades_cgpa vcgc;
    FILE *Mark, *Grading;
    Mark = fopen("CourseMark.txt", "r");
    Grading = fopen("grading.txt", "r");

    rewind(Grading);
    rewind(Mark);
    printf("\n----------------------------------------------------------------");
    printf("\n|             Student ID :     ");
    centerAlign(student_id_3, 30);
    printf("  |");
    printf("\n----------------------------------------------------------------\n");
    printf("|      Course Enrolled     |   Grades   |   CGPA    |   Mark   |\n");
    printf("----------------------------------------------------------------\n");
    while (fscanf(Mark, "%[^,], %[^,], %lf\n", vcgc.course, vcgc.studentID, &vcgc.mark) == 3) {
        if (strcmp(student_id_3, vcgc.studentID) == 0) {
            rewind(Grading);
            while (fscanf(Grading, "%d, %d, %[^,], %lf\n", &vcgc.grade_mark_1, &vcgc.grade_mark_2, vcgc.grade, &vcgc.CGPA) == 4) {
                if (vcgc.grade_mark_1 <= vcgc.mark && vcgc.mark <= vcgc.grade_mark_2) {
                    printf("|");
                    centerAlign(vcgc.course, 26);
                    printf("|");
                    centerAlign(vcgc.grade, 13);
                    printf("|");
                    sprintf(vcgc.string_GGPA, "%.2f", vcgc.CGPA);
                    centerAlign(vcgc.string_GGPA, 10);
                    printf("|");
                    sprintf(vcgc.string_mark, "%.2f", vcgc.mark);
                    centerAlign(vcgc.string_mark, 10);
                    printf("|\n");
                }
            }
        }
    }
    printf("----------------------------------------------------------------\n\n");

    fclose(Mark);
    fclose(Grading);
}

void view_attendance(char student_id_4[]){
    
    char data[100][1000];
    FILE *Attendance;
    Attendance = fopen("Attendance.txt" , "r");

    printf("\n----------------------------------------------------------------");
    printf("\n|              Student ID :  ");
    centerAlign(student_id_4, 34);
    printf("|");
    printf("\n----------------------------------------------------------------");
    printf("\n|          Course          |         Overall Percentage        |");
    printf("\n----------------------------------------------------------------");
    while (fscanf(Attendance, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12]) == 13){     
        if (strcmp(student_id_4, data[1]) == 0){
            printf("\n|");
            centerAlign(data[0], 26);
            printf("|                ");
            centerAlign(data[12], 3);
            printf("%%");
            printf("               |");
            printf("\n----------------------------------------------------------------");
        }
    }
    printf("\n\n");
    fclose(Attendance);
}

