#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>


//_____________________________________________________________________________________________________________________________________________________
//System Admin part code - Chu Eugine


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


