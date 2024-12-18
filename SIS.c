#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#define BUFFER_SIZE 1000

#define MAX_LECTURERS 100
#define MAX_COURSES 100
#define MAX_ENROLLMENTS 100
#define MAX_ASSIGNMENTS 100
#define MAX_STRING_LENGTH 100



void loginMenu();
void upperString(char *str);
void stu(), sysAdMenu(), rgmg(), proAdmin(), lec(), systemAdmLogin(), stuLogin(), lecLogin(), programmeAdLogin(), grad(), report();
void Lecturer_menu(char lecture_id[]);
void delete_lecturer_id(char lec_id[]);
void delete_student_id_for_attendance(char stu_id_2[]);// Function from lecturer
void programmeMenu();
void student_menu(char student_id[]);
void delete_student_id_for_coursemark(char stu_id_3[]);
void delete_student_in_enrollment(char UID[]); //Function from programme adminstrator
typedef struct ReportGrade ReportGrade;
void determineGradeLevel(float mark, ReportGrade *gradingData, int numGrades, char *grade, char *level);

int main() {
    loginMenu();
    return 0;
}

//Function to uppercase string
void upperString(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void loginMenu() {
    int num;

    do {
        printf(" -------------------------------------------------- \n");
        printf("|                   Login Menu                     |\n");
        printf(" -------------------------------------------------- \n");
        printf("|                (1) Student                       |\n");
        printf("|                (2) Lecturer                      |\n");
        printf("|                (3) Programme Administrator       |\n");
        printf("|                (4) System Administrator          |\n");
        printf("|                (5) Exit                          |\n");
        printf(" -------------------------------------------------- \n");
        printf(" Please Select Your Option: ");
        if (scanf("%d", &num) != 1 || num < 1 || num > 5) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" -------------------------------------------------- \n");
            printf("\n");
            switch (num) {
                case 1:
                    stuLogin();
                    break;

                case 2:
                    lecLogin(); 
                    break;

                case 3:
                    programmeAdLogin(); 
                    break;

                case 4:
                    systemAdmLogin(); 
                    break;
                
                case 5:
                    printf(" Successfully Exit.....\n");
                    printf("\n");
                    exit(0);
                    break;
                
                default:
                    printf(" Please Enter a Valid Choice!!!\n");
            }

        }
        
    } while (1);
}

void systemAdmLogin() {
    FILE *file;
    char UID[100], ps[100], checkUID[100], checkps[100]; 
    int loginSuccessful = 0, choice;

    do {
        printf(" ------------------------------------------------ \n");
        printf("|                  Login System                  |\n");
        printf(" ------------------------------------------------ \n");
        printf(" User ID: ");
        scanf("%99s", UID);
        printf(" Password: ");
        scanf("%99s", ps);
        printf(" ------------------------------------------------ \n");

        if (strcmp(UID, "exit") == 0 && strcmp(ps, "exit") == 0) {
            printf(" Exiting...\n");
            return; 
        }

        file = fopen("systemAdmin.txt", "r");
        if (file == NULL) {
            printf(" Error Opening Requesting File.\n");
            return;
        }

       while (fscanf(file, "%[^,],%s\n", checkUID, checkps) == 2) {
        if (strcmp(UID, checkUID) == 0 && strcmp(ps, checkps) == 0) {
            fclose(file);
            printf(" Login Successful!\n\n");
            loginSuccessful = 1;
            break;
            }
        }

        if (!loginSuccessful) {
            printf(" Login Failed. Incorrect User ID or Password.\n");
            printf("\n");
            printf(" Do You Want to Try Again? (1: Yes / 2: No): ");
            scanf("%d", &choice);
            if (choice == 2) {
                return;
            }
        }

        fclose(file); 
    } while (!loginSuccessful);
    
    sysAdMenu();
}

void stuLogin() {
   FILE *file;
    char UID[100], ps[100], checkUID[100], checkps[100], temp[100];
    char *token;
    int loginSuccessful = 0, choice;

    do {
        printf(" ------------------------------------------------ \n");
        printf("|                  Login System                  |\n");
        printf(" ------------------------------------------------ \n");
        printf(" User ID: ");
        scanf("%99s", UID);
        upperString(UID);
        printf(" Password: ");
        scanf("%99s", ps);
        printf(" ------------------------------------------------ \n");

        if (strcmp(UID, "exit") == 0 && strcmp(ps, "exit") == 0) {
            printf(" Exiting...\n");
            return;
        }

        file = fopen("student.txt", "r");
        if (file == NULL) {
            printf(" Error Opening Requested File.\n");
            return;
        }

        while (fgets(temp, 100, file) != NULL) {
            token = strtok(temp, ",");
            strcpy(checkUID, token);
            token = strtok(NULL, ",");
            strcpy(checkps, token);
            
            char *start = checkps;
            while (isspace((unsigned char)*start)) {
                start++;
            }
            strcpy(checkps, start);

            if (strcmp(UID, checkUID) == 0 && strcmp(ps, checkps) == 0) {
                fclose(file);
                printf(" Login Successful!\n\n");
                loginSuccessful = 1;
                break;
            }
        }

        fclose(file);

        if (!loginSuccessful) {
            printf(" Login Failed. Incorrect User ID or Password.\n\n");
            printf(" Do You Want to Try Again? (1: Yes / 2: No): ");
            scanf("%d", &choice);
            if (choice != 1) {
                return;
            }
        }

    } while (!loginSuccessful);
    
    student_menu(UID);

}

void lecLogin() {
    FILE *file;
    char UID[100], ps[100], checkUID[100], checkps[100], temp[100];
    char *token;
    int loginSuccessful = 0, choice;

    do {
        printf(" ------------------------------------------------ \n");
        printf("|                  Login System                  |\n");
        printf(" ------------------------------------------------ \n");
        printf(" User ID: ");
        scanf("%99s", UID);
        upperString(UID);
        printf(" Password: ");
        scanf("%99s", ps);
        printf(" ------------------------------------------------ \n");

        if (strcmp(UID, "exit") == 0 && strcmp(ps, "exit") == 0) {
            printf(" Exiting...\n");
            return;
        }

        file = fopen("Lecturer.txt", "r");
        if (file == NULL) {
            printf(" Error Opening Requested File.\n");
            return;
        }

        while (fgets(temp, 100, file) != NULL) {
            token = strtok(temp, ",");
            strcpy(checkUID, token);
            token = strtok(NULL, ",");
            strcpy(checkps, token);
            
            char *start = checkps;
            while (isspace((unsigned char)*start)) {
                start++;
            }
            strcpy(checkps, start);

            if (strcmp(UID, checkUID) == 0 && strcmp(ps, checkps) == 0) {
                fclose(file);
                printf(" Login Successful!\n\n");
                loginSuccessful = 1;
                break;
            }
        }

        fclose(file);

        if (!loginSuccessful) {
            printf(" Login Failed. Incorrect User ID or Password.\n\n");
            printf(" Do You Want to Try Again? (1: Yes / 2: No): ");
            scanf("%d", &choice);
            if (choice != 1) {
                return;
            }
        }

    } while (!loginSuccessful);
    
    Lecturer_menu(UID); 
}

void programmeAdLogin() {
    FILE *file;
    char UID[100], ps[100], checkUID[100], checkps[100];
    int loginSuccessful = 0, choice;

    do {
        printf(" ------------------------------------------------ \n");
        printf("|                  Login System                  |\n");
        printf(" ------------------------------------------------ \n");
        printf(" User ID: ");
        scanf("%99s", UID);
        upperString(UID);
        printf(" Password: ");
        scanf("%99s", ps);
        printf(" ------------------------------------------------ \n");

        if (strcmp(UID, "exit") == 0 && strcmp(ps, "exit") == 0) {
            printf(" Exiting...\n");
            return; 
        }

        file = fopen("programmeAdmin.txt", "r");
        if (file == NULL) {
            printf(" Error Opening Requesting File.\n");
            return;
        }

        while (fscanf(file, "%[^,],%s\n", checkUID, checkps) == 2) {
        if (strcmp(UID, checkUID) == 0 && strcmp(ps, checkps) == 0) {
            fclose(file);
            printf(" Login Successful!\n\n");
            loginSuccessful = 1;
            break;
            }
        }

        if (!loginSuccessful) {
            printf(" Login Failed. Incorrect User ID or Password.\n");
            printf("\n");
            printf(" Do You Want to Try Again? (1: Yes / 2: No): ");
            scanf("%d", &choice);
            if (choice == 2) {
                return;
                printf(" Successfully Exited...");
            }
        }

    } while (!loginSuccessful);

    programmeMenu();
    
}

void sysAdMenu() {
    int choice;

    do {
        printf(" ------------------------------------------------ \n");
        printf("|           System Administrator Menu            |\n");
        printf(" ------------------------------------------------ \n");
        printf("|           (1) Register/Manage User             |\n");
        printf("|           (2) Define Grading System            |\n");
        printf("|           (3) General Report                   |\n");
        printf("|           (4) Exit                             |\n");
        printf(" ------------------------------------------------ \n");
        printf(" Please Select Your Option: ");
        
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" ------------------------------------------------ \n");
            printf("\n");
            switch (choice) {
                case 1:
                    rgmg();
                    break;
                case 2:
                    grad(); 
                    break;
                case 3:
                    report(); 
                    break;
                case 4:
                    printf(" Successfully Logout.....\n");
                    loginMenu();
                    break;
                default:
                    printf(" Please Enter a Valid Choice!!!\n");
            }

        }

    } while (choice != 4);

}

void rgmg(){
    int choice;
    char input[100];
    
    do{
        printf(" ------------------------------------------------ \n");
        printf("|             User Manangement Menu              |\n");
        printf(" ------------------------------------------------ \n");
        printf("|               (1) Student                      |\n");
        printf("|               (2) Programme Administrator      |\n");
        printf("|               (3) Lecturer                     |\n");
        printf("|               (4) Exit                         |\n");
        printf(" ------------------------------------------------ \n");
        printf(" Please Select Your Option: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" ------------------------------------------------ \n");
            printf("\n");

            switch (choice) {
                case 1:
                    stu();
                    break;
                
                case 2:
                    proAdmin(); 
                    break;
                
                case 3:
                    lec(); 
                    break;
            
                case 4:
                    printf(" Successfully Exited......\n");
                    break;
            
                default:
                    printf(" Please Enter a Valid Choice!!!\n");
            }

        }

    } while (choice != 4);

}

int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit((unsigned char)*str)) 
            return 0;
        str++;
    }
    return 1;
}

int isValidStuUID(const char *uid) {
    size_t length = strlen(uid); 
    if (length < 8) 
        return 0;

    if (strncmp(uid, "STUDENT", 7) != 0 || !isNumeric(uid + 7))
        return 0;

    return 1;
}

void stu() {
    FILE *file;
    char UID[100], ps[100], checkUID[100], line[256], temp[100], opt = 'y';
    int op = 1, choice;
    int deleted = 0;

    do {
        printf(" ------------------------------------------------------------ \n");
        printf("|                   Student Management Menu                  |\n");
        printf(" ------------------------------------------------------------ \n");
        printf("|                     (1) Add Details                        |\n");
        printf("|                     (2) Delete Details                     |\n");
        printf("|                     (3) Check Details                      |\n");
        printf("|                     (4) Exit                               |\n");
        printf(" ------------------------------------------------------------ \n");
        printf(" Please Select Your Option: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" ------------------------------------------------------------ \n");
            printf("\n");

            switch (choice) {
               case 1:
                    do {
                        file = fopen("student.txt", "a+");
                        if (file == NULL) {
                            printf(" Error Opening Requesting File....\n");
                            break;
                        }
                        
                        int idExists; 
                        do {
                            idExists = 0; 
                            printf(" ------------------------------------------------------------ \n");
                            printf("|Please Enter the Student's Details:                         |\n");
                            printf(" ------------------------------------------------------------ \n");
                            printf(" User ID: ");
                            scanf("%99s", UID);
                            upperString(UID);
                            rewind(file);  
                            while (fgets(line, sizeof(line), file) != NULL) {
                                sscanf(line, "%99[^,]", checkUID);
                                if (strcmp(UID, checkUID) == 0) {
                                    printf(" Error: User ID '%s' Already Exists.\n", UID);
                                    idExists = 1;
                                    break;
                                }
                            }

                            if (idExists) {
                                continue;  
                            }

                            if (!isValidStuUID(UID)) {
                                printf(" Error: User ID Should Be As Format 'STUDENT<number>'!!!\n");
                                printf(" Example: STUDENT1\n");
                                continue; 
                            }

                            printf(" Password: ");
                            scanf("%99s", ps);

                            if (strlen(ps) != 6 || !isNumeric(ps)) {
                                printf(" Error: Password Should Be  6-DIGIT NUMBER!!!\n");
                                printf(" Example: 123456\n");
                                continue; 
                            }

                            printf(" ------------------------------------------------------------ \n");
                            printf("\n");

                            fprintf(file, "%s,%s,NULL,NULL,NULL,NULL,NULL\n", UID, ps);
                            printf(" Student's Details Successfully Written Into the File.\n");

                        } while (idExists);

                        fclose(file);

                        printf(" Do You Want to Continue Manage Student's Details? (y/n): ");
                        scanf(" %c", &opt);
                        printf("\n");

                        if (opt == 'y') {
                            printf(" Returning to the Student Management Menu.....\n");
                            break; 
                        }

                    } while (opt == 'y');

                    if (opt != 'y') {
                        printf(" Successfully Exited......\n");
                        return; 
                    }

                    break;

                case 2:
                    file = fopen("student.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                    }

                    FILE *tempFile = fopen("temp.txt", "w");
                    if (tempFile == NULL) {
                        printf(" Error Opening Temporary File.\n");
                    }

                    printf(" ---------------------------------------------------------------- \n");
                    printf("|Please Enter the Student's UID to Delete:                       |\n");
                    printf(" ---------------------------------------------------------------- \n");
                    printf(" User ID: ");
                    scanf("%99s", UID);
                    upperString(UID);
                    printf(" ---------------------------------------------------------------- \n");
                    printf("\n");

                    
                    while (fgets(temp, 100, file) != NULL) {
                        sscanf(temp, "%99[^,]", checkUID);

                        if (strcmp(UID, checkUID) == 0) {
                            printf(" User with UID '%s' deleted.\n", UID);
                            deleted = 1;
                        } else {
                            fprintf(tempFile, "%s", temp);
                        }
                    }

                    fclose(file);
                    fclose(tempFile);

                    if (deleted) {
                        remove("student.txt");
                        rename("temp.txt", "student.txt");
                        printf(" The Student's Details with UID '%s' Have Been Deleted Successfully!\n", UID);
                        delete_student_in_enrollment(UID);
                        delete_student_id_for_attendance(UID);
                        delete_student_id_for_coursemark(UID);
                    } else {
                        printf(" No details Found With the Given UID '%s'.\n", UID);
                        remove("temp.txt");
                    }

                    printf(" Do You Want to Continue to Manage the Student's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Student Management Menu.....\n");
                    } else {
                        printf(" Successfully Exited......\n");
                    }

                    break;
                
                case 3:
                    file = fopen("student.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                        break;
                    }

                    printf(" ---------------------------------------------------------------- \n");
                    printf("|                      Student's ID Details                      |\n");
                    printf(" ---------------------------------------------------------------- \n");
                    printf("|   | UID                        | Password                      |\n");
                    printf(" ---------------------------------------------------------------- \n");

                    while (fgets(line, sizeof(line), file) != NULL) {
                        char *token = strtok(line, ",");
                        if (token != NULL) {
                            printf("|%2d.| %-26s |", op++, token);
                        }
                        token = strtok(NULL, ","); 
                        if (token != NULL) {
                            printf(" %-29s |\n", token);
                            printf(" ---------------------------------------------------------------- \n");
                        }
                    }

                    fclose(file);
                    printf(" Do You Want to Continue to Manage the Student's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Student Management Menu.....\n");
                    } else {
                        printf(" Successfully Exited......\n");
                    }

                    break;
                
                case 4:
                    opt = 'n';
                    printf(" Successfully Exited......\n");
                    break;
                
                default:
                    printf(" Please Enter a Valid Choice!!!\n");
            }

        }

    }

    while (opt == 'y'); 
    fclose(file);

}

int isValidPgmUID(const char *uid) {
    size_t length = strlen(uid); 
    if (length < 4) 
        return 0;

    if (strncmp(uid, "PGM", 3) != 0 || !isNumeric(uid + 3))
        return 0;

    return 1;
}

void proAdmin() {
    FILE *file;
    char UID[100], ps[100], checkUID[100], line[256], opt = 'y';
    int op = 1, choice;
    int deleted = 0;

    do {
        printf(" ------------------------------------------------------------ \n");
        printf("|           Programme Administrator Management Menu          |\n");
        printf(" ------------------------------------------------------------ \n");
        printf("|                     (1) Add Details                        |\n");
        printf("|                     (2) Delete Details                     |\n");
        printf("|                     (3) Check Details                      |\n");
        printf("|                     (4) Exit                               |\n");
        printf(" ------------------------------------------------------------ \n");
        printf(" Please Select Your Option: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" ------------------------------------------------------------ \n");
            printf("\n");

            switch (choice) {
                case 1:
                    do {
                        file = fopen("programmeAdmin.txt", "a+");
                        if (file == NULL) {
                            printf(" Error Opening Requesting File....\n");
                            break;
                        }
                        
                        int idExists; 
                        do {
                            idExists = 0; 
                            printf(" ------------------------------------------------------------ \n");
                            printf("|Please Enter the Programme Administrator's Details:         |\n");
                            printf(" ------------------------------------------------------------ \n");
                            printf(" User ID: ");
                            scanf("%99s", UID);
                            upperString(UID);
                            rewind(file);  
                            while (fgets(line, sizeof(line), file) != NULL) {
                                sscanf(line, "%99[^,]", checkUID);
                                if (strcmp(UID, checkUID) == 0) {
                                    printf(" Error: User ID '%s' Already Exists.\n", UID);
                                    idExists = 1;
                                    break;
                                }
                            }

                            if (idExists) {
                                continue;  
                            }

                            if (!isValidPgmUID(UID)) {
                                printf(" Error: User ID Should Be As Format 'PGM<number>'!!!\n");
                                printf(" Example: PGM1\n");
                                continue; 
                            }

                            printf(" Password: ");
                            scanf("%99s", ps);

                            if (strlen(ps) != 6 || !isNumeric(ps)) {
                                printf(" Error: Password Should Be  6-DIGIT NUMBER!!!\n");
                                printf(" Example: 123456\n");
                                continue; 
                            }

                            printf(" ------------------------------------------------------------ \n");
                            printf("\n");

                            fprintf(file, "%s,%s\n", UID, ps);
                            printf(" Programme Administrator's Details Successfully Written Into the File.\n");

                        } while (idExists);

                        fclose(file);

                        printf(" Do You Want to Continue Manage Programme Administrator's Details? (y/n): ");
                        scanf(" %c", &opt);
                        printf("\n");

                        if (opt == 'y') {
                            printf(" Returning to the Programme Administrator Management Menu.....\n");
                            break; 
                        }

                    } while (opt == 'y');

                    if (opt != 'y') {
                        printf(" Successfully Exited......\n");
                        return; 
                    }

                    break;

                case 2:
                    file = fopen("programmeAdmin.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                    }

                    FILE *tempFile = fopen("temp.txt", "w");
                    if (tempFile == NULL) {
                        printf(" Error Opening Temporary File.\n");
                    }

                    printf(" ---------------------------------------------------------------- \n");
                    printf("|Please Enter the Programme Administrator's UID to Delete:       |\n");
                    printf(" ---------------------------------------------------------------- \n");
                    printf(" User ID: ");
                    scanf("%99s", UID);
                    upperString(UID);
                    printf(" ---------------------------------------------------------------- \n");
                    printf("\n");

                    while (fscanf(file, "%99[^,],%99[^\n]\n", checkUID, ps) == 2) {
                        if (strcmp(UID, checkUID) == 0) {
                            printf(" User with UID '%s' deleted.\n", UID);
                            deleted = 1;
                        } else {
                            fprintf(tempFile, "%s,%s\n", checkUID, ps);
                        }
                    }

                    fclose(file);
                    fclose(tempFile);

                    if (deleted) {
                        remove("programmeAdmin.txt");
                        rename("temp.txt", "programmeAdmin.txt");
                        printf(" The Programme Administrator's Details with UID '%s' Have Been Deleted Successfully!\n", UID);
                    } else {
                        printf(" No details found with the given UID '%s'.\n", UID);
                        remove("temp.txt");
                    }

                    printf(" Do You Want to Continue to Manage the Programme Administrator's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Programme Administrator Management Menu.....\n");
                    } else {
                        printf(" Successfully Exited......\n");
                    }

                    break;
                
                case 3:
                    file = fopen("programmeAdmin.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                        break;
                    }

                    printf(" ---------------------------------------------------------------------- \n");
                    printf("|                 Programme Administrator's ID Details                 |\n");
                    printf(" ---------------------------------------------------------------------- \n");
                    printf("|   | UID                             | Password                       |\n");
                    printf(" ---------------------------------------------------------------------- \n");

                    while (fscanf(file, "%99[^,],%99[^\n]\n", checkUID, ps) == 2) {
                        printf("|%2d.| %-31s | %-30s |\n", op++, checkUID, ps);
                        printf(" ---------------------------------------------------------------------- \n");
                    }

                    fclose(file);
                    printf(" Do You Want to Continue to Manage the Programme Administrator's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Programme Administrator Management Menu.....\n");
                    } else {
                        printf(" Successfully Exited......\n");
                    }

                    break;

                case 4:
                    opt = 'n';
                    printf(" Successfully Exited......\n");
                    break;
                
                default:
                    printf(" Please enter a valid choice!!!\n");
            }

        }

    }
    
    while (opt == 'y'); 
    fclose(file);

}

int isValidLecUID(const char *uid) {
    size_t length = strlen(uid); 
    if (length < 4) 
        return 0;

    if (strncmp(uid, "LEC", 3) != 0 || !isNumeric(uid + 3))
        return 0;

    return 1;
}

void lec() {
    FILE *file;
    char UID[100], ps[100], opt = 'y', checkUID[100], temp[100], line[256];
    int op = 1, choice;
    int deleted = 0;

    do {
        printf(" ------------------------------------------------------------ \n");
        printf("|                  Lecturer Management Menu                  |\n");
        printf(" ------------------------------------------------------------ \n");
        printf("|                     (1) Add Details                        |\n");
        printf("|                     (2) Delete Details                     |\n");
        printf("|                     (3) Check Details                      |\n");
        printf("|                     (4) Exit                               |\n");
        printf(" ------------------------------------------------------------ \n");
        printf(" Please Select Your Option: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            printf(" Invalid Input!!! Please Enter Correct Input!!!\n");
            while (getchar() != '\n'); 
        } else {
            printf(" ------------------------------------------------------------ \n");
            printf("\n");

            switch (choice) {
                 case 1:
                    do {
                        file = fopen("Lecturer.txt", "a+");
                        if (file == NULL) {
                            printf(" Error Opening Requesting File....\n");
                            break;
                        }
                        
                        int idExists; 
                        do {
                            idExists = 0; 
                            printf(" ------------------------------------------------------------ \n");
                            printf("|Please Enter the Lecturer's Details:                        |\n");
                            printf(" ------------------------------------------------------------ \n");
                            printf(" User ID: ");
                            scanf("%99s", UID);
                            upperString(UID);
                            rewind(file);  
                            while (fgets(line, sizeof(line), file) != NULL) {
                                sscanf(line, "%99[^,]", checkUID);
                                if (strcmp(UID, checkUID) == 0) {
                                    printf(" Error: User ID '%s' Already Exists.\n", UID);
                                    idExists = 1;
                                    break;
                                }
                            }

                            if (idExists) {
                                continue;  
                            }

                            if (!isValidLecUID(UID)) {
                                printf(" Error: User ID Should Be As Format 'LEC<number>'!!!\n");
                                printf(" Example: LEC1\n");
                                continue; 
                            }

                            printf(" Password: ");
                            scanf("%99s", ps);

                            if (strlen(ps) != 6 || !isNumeric(ps)) {
                                printf(" Error: Password Should Be  6-DIGIT NUMBER!!!\n");
                                printf(" Example: 123456\n");
                                continue; 
                            }

                            printf(" ------------------------------------------------------------ \n");
                            printf("\n");

                            fprintf(file, "%s,%s,NULL,NULL,NULL,NULL,NULL\n", UID, ps);
                            printf(" Lecturer's Details Successfully Written Into the File.\n");

                        } while (idExists);

                        fclose(file);

                        printf(" Do You Want to Continue Manage Lecturer's Details? (y/n): ");
                        scanf(" %c", &opt);
                        printf("\n");

                        if (opt == 'y') {
                            printf(" Returning to the Lecturer Management Menu.....\n");
                            break; 
                        }

                    } while (opt == 'y');

                    if (opt != 'y') {
                        printf(" Successfully Exited......\n");
                        return; 
                    }

                    break;
                
                case 2:
                    file = fopen("Lecturer.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                    }

                    FILE *tempFile = fopen("temp.txt", "w");
                    if (tempFile == NULL) {
                        printf(" Error Opening Temporary File.\n");
                    }

                    printf(" ---------------------------------------------------------------- \n");
                    printf("|Please Enter the Lecturer's UID to Delete:                      |\n");
                    printf(" ---------------------------------------------------------------- \n");
                    printf(" User ID: ");
                    scanf("%99s", UID);
                    upperString(UID);
                    printf(" ---------------------------------------------------------------- \n");
                    printf("\n");

                    
                    while (fgets(temp, 100, file) != NULL) {
                        sscanf(temp, "%99[^,]", checkUID);

                        if (strcmp(UID, checkUID) == 0) {
                            printf(" User with UID '%s' deleted.\n", UID);
                            deleted = 1;
                        } else {
                            fprintf(tempFile, "%s", temp);
                        }
                    }

                    fclose(file);
                    fclose(tempFile);

                    if (deleted) {
                        remove("Lecturer.txt");
                        rename("temp.txt", "Lecturer.txt");
                        printf(" The Lecturer's Details with UID '%s' Have Been Deleted Successfully!\n", UID);
                        delete_lecturer_id(UID);
                    } else {
                        printf(" No details found with the given UID '%s'.\n", UID);
                        remove("temp.txt");
                    }

                    printf(" Do You Want to Continue to Manage the Lecturer's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Lecturer Management Menu.....\n");
                    } else {
                        printf(" Successfully Exited......\n");
                    }

                    break;
                
                case 3:
                    file = fopen("Lecturer.txt", "r");
                    if (file == NULL) {
                        printf(" Error Opening Requesting File.\n");
                        break;
                    }

                    printf(" ---------------------------------------------------------------- \n");
                    printf("|                     Lecturer's ID Details                      |\n");
                    printf(" ---------------------------------------------------------------- \n");
                    printf("|   | UID                        | Password                      |\n");
                    printf(" ---------------------------------------------------------------- \n");

                    while (fgets(line, sizeof(line), file) != NULL) {
                        char *token = strtok(line, ",");
                        if (token != NULL) {
                            printf("|%2d.| %-26s |", op++, token);
                        }
                        token = strtok(NULL, ","); 
                        if (token != NULL) {
                            printf(" %-29s |\n", token);
                            printf(" ---------------------------------------------------------------- \n");
                        }
                    }

                    fclose(file);
                    printf(" Do You Want to Continue to Manage the Lecturer's Details? (y/n): ");
                    scanf(" %c", &opt); 
                    printf("\n");

                    if (opt == 'y') {
                        printf(" Returning to the Lecturer Management Menu.....\n");
                    } else {
                        printf(" Sucessfully Exited......\n");
                    }

                    break;
                
                case 4:
                    opt = 'n';
                    printf(" Successfully Exited......\n");
                    break;
                
                default:
                    printf(" Please Enter a Valid Choice!!!\n");
            }
        }

    }
    
    while (opt == 'y'); 
    fclose(file);

}

void grad() {
    FILE *file;
    char grade[50], level[50], opt = 'y', choice = 'y';
    int range1, range2, lineNumber = 0;
    int lineToUpdate, newRange1, newRange2, op = 1;
    char newGrade[50], newLevel[50];

    do {
        file = fopen("grading.txt", "r");
        if (file == NULL) {
            printf(" Error Opening Requesting File.\n");
            return;
        }

        printf(" ----------------------------------------------------------------- \n");
        printf("|                         Grading Standard                        |\n");
        printf(" ----------------------------------------------------------------- \n");
        printf("|   |    Marks Range     | Grade       | Level                    |\n");
        printf(" ----------------------------------------------------------------- \n");

        while (fscanf(file, "%d,%d,%[^,],%s", &range1, &range2, grade, level) == 4) {
            lineNumber++;
            printf("|%2d.|%9d-%-9d | %-10s | %-25s |\n", op++, range1, range2, grade, level);
            printf(" ----------------------------------------------------------------- \n");
        }

        fclose(file);

        printf(" Do You Want to Update the Grading Standard? (y/n): ");
        scanf(" %c", &opt);
        printf("\n");
        if (opt == 'y') {
            printf(" Enter the Line Number to Update: ");
            scanf("%d", &lineToUpdate);

            if (lineToUpdate < 1 || lineToUpdate > lineNumber) {
                printf(" Invalid Line Number.\n");
                return;
            }

            printf(" Enter the New Marks Range (e.g., 80 100): ");
            scanf("%d %d", &newRange1, &newRange2);

            printf(" Enter the New Grade (e.g., A, B, C...): ");
            scanf("%s", newGrade);
            upperString(newGrade);

            printf(" Enter the New Level (e.g., 4.00 , 3.70, 3.30...): ");
            scanf("%s", newLevel);

            file = fopen("grading.txt", "r");
            if (file == NULL) {
                printf(" Error Opening Requesting File.\n");
                return;
            }

            FILE *tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL) {
                printf(" Error Opening Temporary File.\n");
                fclose(file);
                return;
            }

            int currentLine = 0;
            while (fscanf(file, "%d,%d,%[^,],%s", &range1, &range2, grade, level) == 4) {
                currentLine++;
                if (currentLine == lineToUpdate) {
                    fprintf(tempFile, "%d,%d,%s,%s\n", newRange1, newRange2, newGrade, newLevel);
                } else {
                    fprintf(tempFile, "%d,%d,%s,%s\n", range1, range2, grade, level);
                }
            }

            fclose(file);
            fclose(tempFile);

            remove("grading.txt");
            rename("temp.txt", "grading.txt");

            printf(" Grading Standard Updated Successfully.\n");
            
        } else {
            sysAdMenu();
        }

        printf("\n");
        printf(" Do You Want to Update the Standard? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y');

}

struct ReportGrade{
    float lowerMarks;
    float upperMarks;
    char grade[10];
    char level[10];
};

void determineGradeLevel(float mark, ReportGrade *gradingData, int numGrades, char *grade, char *level) {
    int i;
    for (i = 0; i < numGrades; i++) {
        if (mark >= gradingData[i].lowerMarks && mark <= gradingData[i].upperMarks) {
            strcpy(grade, gradingData[i].grade);
            strcpy(level, gradingData[i].level);
            return;
        }
    }
    strcpy(grade, "N/A");
    strcpy(level, "N/A");
}

void report() {
    FILE *CourseMark, *grading, *student;
    char course[50], studentID_course[50], studentID_student[50], student_pw[50], studentName[50], student_gender[50], student_age[50], student_email[50], country[50], ID[100];
    float mark;
    int found = 0;

    printf(" --------------------------------------------------------------- \n");
    printf("|                         Report Menu                           |\n");
    printf(" --------------------------------------------------------------- \n");
    printf(" Enter a Student ID to Generate Report: ");
    scanf("%s", ID);
    upperString(ID);
    printf(" --------------------------------------------------------------- \n");

    CourseMark = fopen("CourseMark.txt", "r");
    grading = fopen("grading.txt", "r");
    student = fopen("Student.txt", "r");

    if (CourseMark == NULL || grading == NULL || student == NULL) {
        printf(" Error Opening Requesting File.\n");
        return;
    }
    
    ReportGrade gradingData[100];
    int numGrades = 0;
    while (fscanf(grading, "%f,%f,%[^,],%s\n", &gradingData[numGrades].lowerMarks, &gradingData[numGrades].upperMarks, gradingData[numGrades].grade, gradingData[numGrades].level) == 4) {
        numGrades++;
    }

    while (fscanf(student, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", studentID_student, student_pw, studentName, student_gender, student_age, student_email, country) == 7) {
        if (strcmp(ID, studentID_student) == 0) { 
            fseek(CourseMark, 0, SEEK_SET); 
            found = 0;
            while (fscanf(CourseMark, "%[^,],%[^,],%f\n", course, studentID_course, &mark) == 3) {
                if (strcmp(ID, studentID_course) == 0) {
                    found = 1;
                    break;
                }
            }
            printf("\n");
            printf(" ------------------------------------------------------------------------------ \n");
            printf("|                                Student Report                                |\n");
            printf(" ------------------------------------------------------------------------------ \n");
            printf("| Student Name: %-62s |\n", studentName); 
            printf("|                                                                              |\n");
            printf(" ------------------------------------------------------------------------------ \n");
            printf("| Course: %-68s |\n", course);
            printf("|                                                                              |\n");
            printf(" ------------------------------------------------------------------------------ \n");
            if (found) {
                printf("| Mark: %-6.2f%64s |\n", mark, "");
            } else {
                printf("| Mark: %-6s%64s |\n", "NULL", "");
            }
            printf("|                                                                              |\n");
            printf(" ------------------------------------------------------------------------------ \n");
            if (found) {
                for (int i = 0; i < numGrades; i++) {
                    if (mark >= gradingData[i].lowerMarks && mark <= gradingData[i].upperMarks) {
                        printf("| Grade: %-69s |\n", gradingData[i].grade); 
                        printf("|                                                                              |\n");
                        printf(" ------------------------------------------------------------------------------ \n");
                        printf("| Level: %-7s%62s |\n", gradingData[i].level, "");
                        printf("|                                                                              |\n");
                        printf(" ------------------------------------------------------------------------------ \n");
                        break;
                    }
                }
            }
            fclose(CourseMark);
            fclose(grading);
            fclose(student);
            return;
        }
    }

    if (!found) {
        printf(" No matching records found for Student ID %s.\n", ID);
    }

    fclose(CourseMark);
    fclose(grading);
    fclose(student);
}




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
                printf("\n--Invalid input! Please enter a mark in a range of 1 to 5.\n");
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
    } while (choice == 'Y');
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
                if (vcgc.grade_mark_1 <= vcgc.mark && vcgc.mark < vcgc.grade_mark_2) {
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

