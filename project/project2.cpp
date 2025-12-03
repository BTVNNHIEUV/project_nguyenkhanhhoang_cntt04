#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 100

typedef struct {
char employeeId[20];
char fullName[50];
char position[15];
double baseSalary;
int workDays;
} Employee;

Employee employeeList[MAX_EMPLOYEES];
int employeeCount = 0;

typedef struct {
int logId;
char employeeId[20];
char date[20];
char status[10];
} Timesheet;

Timesheet timesheetList[MAX_EMPLOYEES];
int timesheetCount = 0;

// Duplicate detection
int isDuplicateId(char id[]) {
for (int i = 0; i < employeeCount; i++) {//duyet nv hien co
if (strcmp(employeeList[i].employeeId, id) == 0) return 1;
}
return 0;
}

// Number input for menu and workdays
int inputNumberInRange(char prompt[], int min, int max) {
char input[20];
do {
printf("%s (from %d to %d): \n", prompt, min, max);
fgets(input, sizeof(input), stdin);
input[strcspn(input, "\n")] = 0;

    if (input[0] == '\0') {
        printf("ERROR: Nothing was inserted.\n");
    } else {
        int isDigit = 1;
        for (int i = 0; input[i]; i++) {
            if (!isdigit(input[i])) {
                isDigit = 0;
                break;
            }
        }
        if (isDigit) {
            int number = atoi(input);//doi so nguyen
            if (number >= min && number <= max) return number;
            else printf("Insert number from %d to %d.\n", min, max);
        } else {
            printf("Please insert a positive number.\n");
        }
    }
} while (1);

}

// Number input for salary
double inputPositiveDouble(char prompt[]) {
char input[50];
do {
printf("%s: ", prompt);
fgets(input, sizeof(input), stdin);
input[strcspn(input, "\n")] = 0;

    int dotCount = 0;
    int valid = 1;

    if (input[0] == '\0') valid = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] == '.') {
            dotCount++;
            if (dotCount > 1) valid = 0;
        } else if (!isdigit(input[i])) valid = 0;
    }

    if (valid) {
        double value = atof(input);//doi thanh so thuc
        if (value > 0) return value;
    }
    printf("Please input a positive number!\n");
} while (1);

}

// Add new employee
void addNewEmployee(Employee *emp) {
char temp[50];

do {
    printf("\nInsert employee ID: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if(temp[0] == '\0') {
        printf("ERROR: ID cannot be empty!\n");
        continue;
    }
    if (isDuplicateId(temp)) {
        printf("ERROR: ID already exists!\n");
        continue;
    }
    strcpy(emp->employeeId, temp);//ghi du lieu
    break;
} while (1);

do {
    printf("Insert full name: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(temp[0] == '\0') {
        printf("ERROR: Name cannot be empty!\n");
        continue;
    }
    strcpy(emp->fullName, temp);
    break;
} while (1);

do {
    printf("Insert position: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(temp[0] == '\0') {
        printf("ERROR: Position cannot be empty!\n");
        continue;
    }
    strcpy(emp->position, temp);
    break;
} while (1);

emp->baseSalary = inputPositiveDouble("Insert salary");

printf("New employee has been added!\n\n");

}

// Show one employee
void showEmployee(Employee emp) {
printf("||%-10s %-20s %-15s %-12.2lf %d      ||\n",
emp.employeeId, emp.fullName, emp.position, emp.baseSalary, emp.workDays);
printf("||--------------------------------------------------------------------||\n");
}

// Show all employees (paginated)
void showEmployeeList(Employee list[], int count) {
if (count == 0) {
printf("The list is empty!\n");
return;
}
int pageSize = 5;
int totalPage = (count + pageSize - 1) / pageSize;
int currentPage = 1;
char choice;

do {
    system("cls");
    int start = (currentPage - 1) * pageSize;//chi so dau
    int end = start + pageSize;// chi so cuoi
    if (end > count) end = count;//ko cho vuot so luong

    printf("||====================================================================||\n");
    printf("||Total %d pages, currently on page %d.                                ||\n", totalPage, currentPage);
    printf("||====================================================================||\n");
    printf("||%-10s %-20s %-15s %-12s %s||\n", "ID", "Name", "Position", "Salary", "Workdays");
    printf("||--------------------------------------------------------------------||\n");

    for (int i = start; i < end; i++) {
        showEmployee(list[i]);
    }

    printf("\n|P|rev - |N|ext - |E|xit: ");
    fflush(stdin);
    scanf("%c", &choice);

    if (choice == 'N' || choice == 'n') {
        if (currentPage < totalPage) currentPage++;
        else printf("ERROR: you have reached the end of the list!\n");
    } else if (choice == 'P' || choice == 'p') {
        if (currentPage > 1) currentPage--;
        else printf("ERROR: you are on the first page!\n");
    } else if (choice == 'E' || choice == 'e') {
        break;
    }
} while (1);

}

// Search by employee ID
int findEmployeeById(Employee list[], int count, char id[]) {
for (int i = 0; i < count; i++) {
if (strcmp(list[i].employeeId, id) == 0) return i;
}
return -1;//no
}

// Fire employee
void fireEmployee(Employee list[], int *count) {
char id[20];
printf("Insert ID to fire: ");
fflush(stdin);
fgets(id, 20, stdin);
id[strcspn(id, "\n")] = '\0';

int pos = findEmployeeById(list, *count, id);
if (pos == -1) {
    printf("ERROR: ID not found!\n");
    return;
}

for (int i = pos; i < *count - 1; i++) list[i] = list[i + 1];
//day vi tri sau len
(*count)--;
printf("Fire complete!\n\n");

}

// Update employee profile
void updateEmployeeProfile(Employee list[], int count) {
char id[20];
char temp[50];

printf("\nInsert employee ID to update: ");
fflush(stdin);
fgets(id, 20, stdin);
id[strcspn(id, "\n")] = '\0';

int pos = findEmployeeById(list, count, id);
if (pos == -1) {
    printf("ERROR: ID not found!\n");
    return;
}

printf("===== Updating employee profile =====\n");

do {
    printf("Insert new full name: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(temp[0] == '\0') {
        printf("ERROR: Name cannot be empty!\n");
        continue;
    }
    strcpy(list[pos].fullName, temp);
    break;
} while (1);

do {
    printf("Insert new position: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(temp[0] == '\0') {
        printf("ERROR: Position cannot be empty!\n");
        continue;
    }
    strcpy(list[pos].position, temp);
    break;
} while (1);

list[pos].baseSalary = inputPositiveDouble("Insert salary");
printf("Update complete!\n\n");

}

// Search by name using Linear Search
void searchEmployeeByName(Employee list[], int count) {
char name[50];
do {
printf("Insert name to search: ");
fflush(stdin);
fgets(name, 50, stdin);
name[strcspn(name, "\n")] = '\0';

    if(name[0] == '\0') 
	printf("ERROR: name cannot be empty!\n");
    else break;
} while (1);

int found = 0;
for (int i = 0; i < count; i++) {
    if (strstr(list[i].fullName, name) != NULL) {//tim chu dau tien
        showEmployee(list[i]);
        found = 1;
    }
}
if (!found) printf("ERROR: no record of that name!\n");

}

// Sort employees by salary using bubble sort
void sortEmployeesBySalary(Employee list[], int count) {
int choice;

printf("\n||====== SORT BY SALARY ======||\n");
printf("||       1. High -> Low       ||\n");
printf("||       2. Low -> High       ||\n");
printf("||============================||\n");

choice = inputNumberInRange("Choose sorting type", 1, 2);

for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
    	//Sort by high to low
        if (choice == 1 && list[i].baseSalary < list[j].baseSalary) {
            Employee temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        //Sort by low to high
        } else if (choice == 2 && list[i].baseSalary > list[j].baseSalary) {
            Employee temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
}

printf("\nSorting complete!\n");
showEmployeeList(list, count);

}

// Employee check-in
void checkIn(Employee list[], int count, Timesheet tsList[], int *tsCount) {
char empId[20], date[20];
int empIndex = -1;

// Insert employee id and if it exist
do {
    printf("\nInsert employee ID: ");
    fgets(empId, sizeof(empId), stdin);
    empId[strcspn(empId, "\n")] = 0;

    if(empId[0] == '\0') {
        printf("ERROR: nothing was inserted! Please try again.\n");
        continue;
    }

    empIndex = findEmployeeById(list, count, empId);
    if (empIndex == -1) {
        printf("ERROR: Can't find the employee! Please try again.\n");
    }
} while (empIndex == -1);

// Insert checkin date and if it valid
int validDate = 0;
do {
    printf("Insert check-in date (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    if(date[0] == '\0') {
        printf("ERROR: please insert a valid date!\n");
        continue;
    }

    // Check if the employee checkin yet
    int duplicate = 0;
    for (int i = 0; i < *tsCount; i++) {
        if (strcmp(tsList[i].employeeId, empId) == 0 && strcmp(tsList[i].date, date) == 0) {
            printf("ERROR: the employee has already checked in that day!\n");
            duplicate = 1;
            break;
        }
    }
    if (!duplicate) validDate = 1;

} while (!validDate);

// Add template

tsList[*tsCount].logId = *tsCount + 1;
strcpy(tsList[*tsCount].employeeId, empId);
strcpy(tsList[*tsCount].date, date);
strcpy(tsList[*tsCount].status, "good");

(*tsCount)++;
list[empIndex].workDays++;

printf("Check-in successful!\n");
}

// Show timesheet
void showEmployeeTimesheet(Employee list[], int count, Timesheet tsList[], int tsCount) {
char empId[20];
int foundEmp = 0;

printf("Insert employee ID to see: ");
fgets(empId, sizeof(empId), stdin);
empId[strcspn(empId, "\n")] = 0;

if(empId[0] == '\0') {
    printf("ERROR: no ID was inserted!\n");
    return;
}

if (findEmployeeById(list, count, empId) == -1) {
    printf("ERROR: can't find the employee!\n");
    return;
}

int foundCount = 0;
printf("\nWORK SHEET %s:\n", empId);
printf("%-10s %-12s %-8s\n", "LogID", "Date", "Status");
printf("-----------------------------\n");

for (int i = 0; i < tsCount; i++) {
    if (strcmp(tsList[i].employeeId, empId) == 0) {
        printf("%-10d %-12s %-8s\n", tsList[i].logId, tsList[i].date, tsList[i].status);
        foundCount++;
    }
}

if (foundCount == 0) 
printf("Employee hasn't checked in yet!\n");

}

// Employed
void addDefaultEmployees() {

strcpy(employeeList[0].employeeId, "NV001");
strcpy(employeeList[0].fullName, "NguyenVanA");
strcpy(employeeList[0].position, "Manager");
employeeList[0].baseSalary = 15000000;
employeeList[0].workDays = 0;

strcpy(employeeList[1].employeeId, "NV002");
strcpy(employeeList[1].fullName, "TranThiB");
strcpy(employeeList[1].position, "Staff");
employeeList[1].baseSalary = 8000000;
employeeList[1].workDays = 0;

strcpy(employeeList[2].employeeId, "NV003");
strcpy(employeeList[2].fullName, "LeVanC");
strcpy(employeeList[2].position, "Staff");
employeeList[2].baseSalary = 9000000;
employeeList[2].workDays = 0;

strcpy(employeeList[3].employeeId, "NV004");
strcpy(employeeList[3].fullName, "PhamVanD");
strcpy(employeeList[3].position, "HR");
employeeList[3].baseSalary = 7000000;
employeeList[3].workDays = 0;

strcpy(employeeList[4].employeeId, "NV005");
strcpy(employeeList[4].fullName, "VoThiE");
strcpy(employeeList[4].position, "Accountant");
employeeList[4].baseSalary = 11000000;
employeeList[4].workDays = 0;

strcpy(employeeList[5].employeeId, "NV006");
strcpy(employeeList[5].fullName, "HoangVanF");
strcpy(employeeList[5].position, "Sales");
employeeList[5].baseSalary = 10000000;
employeeList[5].workDays = 0;

strcpy(employeeList[6].employeeId, "NV007");
strcpy(employeeList[6].fullName, "DoThiG");
strcpy(employeeList[6].position, "Marketing");
employeeList[6].baseSalary = 9500000;
employeeList[6].workDays = 0;

strcpy(employeeList[7].employeeId, "NV008");
strcpy(employeeList[7].fullName, "BuiVanH");
strcpy(employeeList[7].position, "Security");
employeeList[7].baseSalary = 6000000;
employeeList[7].workDays = 0;

strcpy(employeeList[8].employeeId, "NV009");
strcpy(employeeList[8].fullName, "DangThiI");
strcpy(employeeList[8].position, "Cleaner");
employeeList[8].baseSalary = 5000000;
employeeList[8].workDays = 0;

strcpy(employeeList[9].employeeId, "NV010");
strcpy(employeeList[9].fullName, "TrinhVanK");
strcpy(employeeList[9].position, "IT");
employeeList[9].baseSalary = 14000000;
employeeList[9].workDays = 0;

strcpy(employeeList[10].employeeId, "NV011");
strcpy(employeeList[10].fullName, "LeThiL");
strcpy(employeeList[10].position, "Receptionist");
employeeList[10].baseSalary = 6500000;
employeeList[10].workDays = 0;

strcpy(employeeList[11].employeeId, "NV012");
strcpy(employeeList[11].fullName, "PhanVanM");
strcpy(employeeList[11].position, "Driver");
employeeList[11].baseSalary = 7000000;
employeeList[11].workDays = 0;


employeeCount = 12;

}

int main(){
int choice;

addDefaultEmployees();

do {
    printf("\nXX=========== MENU ===========XX\n");
    printf("||1. Add new employee         ||\n");
    printf("||2. Update profile           ||\n");
    printf("||3. Fire employee            ||\n");
    printf("||4. Show employees           ||\n");
    printf("||5. Search by name           ||\n");
    printf("||6. Sort by salary           ||\n");
    printf("||7. Check-in date            ||\n");
    printf("||8. View employee timesheet  ||\n");
    printf("||9. Exit program             ||\n");
    printf("XX============================XX\n");

    choice = inputNumberInRange("Choose", 1, 9);

    switch (choice) {
        case 1: addNewEmployee(&employeeList[employeeCount]); employeeCount++; break;
        case 2: updateEmployeeProfile(employeeList, employeeCount); break;
        case 3: fireEmployee(employeeList, &employeeCount); break;
        case 4: showEmployeeList(employeeList, employeeCount); break;
        case 5: searchEmployeeByName(employeeList, employeeCount); break;
        case 6: sortEmployeesBySalary(employeeList, employeeCount); break;
        case 7: checkIn(employeeList, employeeCount, timesheetList, &timesheetCount); break;
        case 8: showEmployeeTimesheet(employeeList, employeeCount, timesheetList, timesheetCount); break;
        case 9: printf("Exiting...\n"); break;
        default: printf("ERROR: Invalid choice!\n"); break;
    }
} while (choice != 9);

return 0;

}
