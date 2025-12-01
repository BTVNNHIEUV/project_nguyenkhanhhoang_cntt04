#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct{
	char empId[20]; //Ma nhan vien.
	char name[50]; //Ten nhan vien.
	char position[15]; //Chuc vu nhan vien.
	double baseSalary; //Luong co bao nhieu.
	int workDay; //Ngay cong(Mac dinh khi tao = 0)
}Employee;

Employee ds[MAX];
int n = 0;

typedef struct{
	char logId[20]; //Ma giao dich
	char empId[20]; //Ma tai khoan nhan vien
	char date[20]; //Ngay cham cong
	char status[10]; //Trang thai cham cong
}Timesheet;

Timesheet tsList[MAX];
int tsCount = 0;

//DUPLICATE DETECTION
int isDuplicateID(char tempID[]){
for(int i = 0; i < n; i++) {
if(strcmp(ds[i].empId, tempID) == 0)
return 1;
}
return 0;
}

//NUMBER DETECTION FOR MENU AND WORKDAY
int Number(char suggest[], int min, int max){
char string[20];
do{
printf("%s (from %d to %d): \n", suggest, min, max);
fgets(string, sizeof(string), stdin);
string[strcspn(string, "\n")] = 0;

    if(string[0] == '\0'){  
        printf("ERROR:nothing was inserted.\n");
    }else{
        int isDigit = 1;
        for (int i = 0; i < strlen(string); i++){
            if (!isdigit(string[i])){  
                isDigit = 0;
                break;
            }
        }
        if (isDigit){
            int number = atoi(string);
            if (number >= min && number <= max){  
                return number;
            }else{
                printf("Insert number from %d to %d.\n", min, max);
            }
        }else{
            printf("Please insert a positive number.\n");
        }
    }
} while (1);

}

//NUMBER DECTECTION FOR SALARY
double Number2(char suggest[]){
char string[50];
do {
printf("%s: ", suggest);
fgets(string, sizeof(string), stdin);
string[strcspn(string, "\n")] = 0;
int dot = 0;
int valid = 1;
if(string[0]=='\0') valid=0;
for(int i=0; string[i]; i++){
if(string[i]=='.'){
dot++;
if(dot>1) valid=0;
} else if(!isdigit(string[i])) valid=0;
}
if(valid){
double value = atof(string);
if(value>0) return value;
}
printf("Please input a positive numbers!\n");
} while(1);
}

//ENTER NEW EMPLOYEE
void Newemp(Employee *em){
char temp[50];

do{
    printf("\nInsert employee ID: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) == 0){
        printf("ERROR: ID cannot be empty!\n");
        continue;
    }
    if(isDuplicateID(temp)){
        printf("ERROR: ID already exists!\n");
        continue;
    }
    strcpy(em->empId, temp);
    break;
}while(1);

do{
    printf("Insert name: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) == 0){
        printf("ERROR: Name cannot be empty!\n");
        continue;
    }
    strcpy(em->name, temp);
    break;
}while(1);

do{
    printf("Insert position: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';

    if(strlen(temp) == 0){
        printf("ERROR: Position cannot be empty!\n");
        continue;
    }
    strcpy(em->position, temp);
    break;
}while(1);
em->baseSalary = Number2("Insert salary: ");
em->workDay = Number("Insert workday: ",0,100);
printf("New employee have been added!\n\n");  
}
//LIST DATA
void Show1emp(Employee em){
printf("||%-10s %-20s %-15s %-12.2lf %d     ||\n",
em.empId, em.name, em.position, em.baseSalary, em.workDay);
printf("||--------------------------------------------------------------------||\n");
}

//SHOW LIST
void hienThiDS(Employee a[], int n){
if(n == 0){
	printf("The list is empty!\n");
	return;
}
int pagesize = 5;
int totalpage = (n + pagesize - 1) / pagesize;
int currentpage = 1;
char choice;

do{
	system("cls");
	
	int start = (currentpage - 1)*pagesize;
	int end = start + pagesize;
	if(end > n) end = n;
	
	printf("||====================================================================||\n");
	printf("||the list have %d page, you are currently on page %d.                  ||\n",
			totalpage, currentpage);
	printf("||====================================================================||\n");
    printf("||%-10s %-20s %-15s %-12s %s||\n",
	"ID", "Name", "Position", "Salary", "Workday");
	printf("||--------------------------------------------------------------------||\n");
	for(int i = start; i < end; i++){
		Show1emp(a[i]);
	}
		printf("\n|P|rev - |N|ext - |E|xit: ");
		fflush(stdin);
		scanf("%c", &choice);
	
		if(choice == 'N' || choice == 'n'){
			if(currentpage < totalpage)
		   currentpage++;
		else
			printf("ERROR:you have reach the end of the list!\n");
		}else if (choice == 'P' || choice == 'p'){
		if(currentpage > 1)
		   currentpage--;
		else
			printf("ERROR:you are on the first page!\n");
		}else if (choice == 'E' || choice == 'e'){
			break;
		}
	}while (1);
}
int SearchID(Employee a[], int n, char ID[]){
for(int i = 0; i < n; i++){
if(strcmp(a[i].empId, ID) == 0)
return i;
}
return -1;
}

//FIRE EMPLOYEE
void Fire(Employee a[], int *n){
char ID[20];
printf("Insert ID to fire: ");
fflush(stdin);
fgets(ID, 20, stdin);
ID[strcspn(ID, "\n")] = '\0';

int pos = SearchID(a, *n, ID);
if(pos == -1){
    printf("ERROR: ID not found!\n");
    return;
}
for(int i = pos; i < *n - 1; i++)
    a[i] = a[i+1];

(*n)--;
printf("Fire complete!\n\n");

}

//UPDATEFILE
void updateprofile(Employee a[], int n,Employee *em){
char ID[20];
char temp[50];

printf("\nInsert employee ID to update: ");
fflush(stdin);
fgets(ID, 20, stdin);
ID[strcspn(ID, "\n")] = '\0';

int pos = SearchID(a, n, ID);
if(pos == -1){
    printf("ERROR: ID not found!\n");
    return;
}

printf("===== Updating employee profile =====\n");

do{
    printf("Insert new name: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) == 0){
        printf("ERROR: Name cannot be empty!\n");
        continue;
    }
    strcpy(a[pos].name, temp);
    break;
}while(1);

do{
    printf("Insert new position: ");
    fflush(stdin);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if(strlen(temp) == 0){
        printf("ERROR: Position cannot be empty!\n");
        continue;
    }
    strcpy(a[pos].position, temp);
    break;
}while(1);

    a[pos].baseSalary = Number2("Insert salary");
	printf("Update complete!\n\n");
}

//SEARCH NAME
void Searchname(Employee a[], int n){
	char Name[50];
	do{
	printf("Insert name to search: ");
	fflush(stdin);
	fgets(Name, 50, stdin);
	Name[strcspn(Name, "\n")] = '\0';
	
	if(strlen(Name) == 0){
            printf("ERROR:name cannot be empty!\n");
        }else{
            break;
        }
    } while(1);
	int found = 0;
	
	for(int i = 0; i < n; i++){
		if(strstr(a[i].name, Name) != NULL){
			Show1emp(a[i]);
			found = 1; 
		}
	}
	if(!found) printf("ERROR:there no record of that name!\n");
}

//SORTING BY SALARY
void Sortstuff(Employee a[], int n){
    int choice;

    printf("\n||====== SORT BY SALARY ======||\n");
    printf("||       1. High -> Low       ||\n");
    printf("||       2. Low -> High       ||\n");
    printf("||============================||\n");

    choice = Number("Choose sorting type", 1, 2);

    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(choice == 1){  
                //DOWN
                if(a[i].baseSalary < a[j].baseSalary){
                    Employee temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }else{  
                //UP
                if(a[i].baseSalary > a[j].baseSalary){
                    Employee temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }
    }

    printf("\nSorting complete!\n");
    hienThiDS(a, n);
}

void Checkin(Employee ds[], int n, Timesheet tsList[], int *tsCount){
    char empId[20], date[20];

    printf("\nInsert employee ID: ");
    fgets(empId, sizeof(empId), stdin);
    empId[strcspn(empId, "\n")] = 0;

    if(strlen(empId) == 0){
        printf("ERROR: nothing was inserted!\n");
        return;
    }

    printf("Insert checkin date (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    if(strlen(date) == 0){
        printf("ERROR: please insert a valid date!\n");
        return;
    }

    // EXIST?
    int empIndex = -1;
    for(int i = 0; i < n; i++){
        if (strcmp(ds[i].empId, empId) == 0) {
            empIndex = i;
            break;
        }
    }
    if(empIndex == -1){
        printf("ERROR: Can't find the employee'!\n");
        return;
    }

    // 2. CHECKIN YET?
    for(int i = 0; i < *tsCount; i++) {
        if(strcmp(tsList[i].empId, empId) == 0 &&
            strcmp(tsList[i].date, date) == 0){
            printf("ERROR: the employee have already checkin that day!\n");
            return;
        }
    }

    // 3. NEW INTEL
    sprintf(tsList[*tsCount].logId, "TS%03d", *tsCount + 1);
    strcpy(tsList[*tsCount].empId, empId);
    strcpy(tsList[*tsCount].date, date);
    strcpy(tsList[*tsCount].status, "good");

    (*tsCount)++;

    // 4. UP++
    ds[empIndex].workDay++;

    printf("Cham cong thanh cong!\n");
}

//SHOW TIME SHEET
void ShowTimesheet(Employee ds[], int n, Timesheet tsList[], int tsCount){
    char empId[20];
    int foundEmp = 0;

    printf("Insert employee ID to see: ");
    fgets(empId, sizeof(empId), stdin);
    empId[strcspn(empId, "\n")] = 0;

    if(strlen(empId) == 0){
        printf("ERROR: no ID was inserted!\n");
        return;
    }
    // EXIST?
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].empId, empId) == 0) {
            foundEmp = 1;
            break;
        }
    }
    if(!foundEmp){
        printf("ERROR: can't find the employee'!\n");
        return;
    }

    // SHOW
    int count = 0;
    printf("\nWORK SHEET %s:\n", empId);
    printf("%-10s %-12s %-8s\n", "LogID", "Date", "Status");
    printf("-----------------------------\n");

    for (int i = 0; i < tsCount; i++) {
        if (strcmp(tsList[i].empId, empId) == 0) {
            printf("%-10s %-12s %-8s\n", tsList[i].logId, tsList[i].date, tsList[i].status);
            count++;
        }
    }

    if (count == 0){
        printf("Employee didn't checkin yet'!\n");
    }
}

//EXIST EMPLOYEE
void Employd(){
    strcpy(ds[0].empId, "NV001");
    strcpy(ds[0].name, "NguyenVanA");
    strcpy(ds[0].position, "Manager");
    ds[0].baseSalary = 15000000;
    ds[0].workDay = 20;

    strcpy(ds[1].empId, "NV002");
    strcpy(ds[1].name, "TranThiB");
    strcpy(ds[1].position, "Staff");
    ds[1].baseSalary = 8000000;
    ds[1].workDay = 18;

    strcpy(ds[2].empId, "NV003");
    strcpy(ds[2].name, "LeVanC");
    strcpy(ds[2].position, "Staff");
    ds[2].baseSalary = 9000000;
    ds[2].workDay = 22;

    strcpy(ds[3].empId, "NV004");
    strcpy(ds[3].name, "PhamVanD");
    strcpy(ds[3].position, "HR");
    ds[3].baseSalary = 7000000;
    ds[3].workDay = 19;

    strcpy(ds[4].empId, "NV005");
    strcpy(ds[4].name, "VoThiE");
    strcpy(ds[4].position, "Accountant");
    ds[4].baseSalary = 11000000;
    ds[4].workDay = 21;

    strcpy(ds[5].empId, "NV006");
    strcpy(ds[5].name, "HoangVanF");
    strcpy(ds[5].position, "Sales");
    ds[5].baseSalary = 10000000;
    ds[5].workDay = 23;

    strcpy(ds[6].empId, "NV007");
    strcpy(ds[6].name, "DoThiG");
    strcpy(ds[6].position, "Marketing");
    ds[6].baseSalary = 9500000;
    ds[6].workDay = 20;

    strcpy(ds[7].empId, "NV008");
    strcpy(ds[7].name, "BuiVanH");
    strcpy(ds[7].position, "Security");
    ds[7].baseSalary = 6000000;
    ds[7].workDay = 26;

    strcpy(ds[8].empId, "NV009");
    strcpy(ds[8].name, "DangThiI");
    strcpy(ds[8].position, "Cleaner");
    ds[8].baseSalary = 5000000;
    ds[8].workDay = 28;

    strcpy(ds[9].empId, "NV010");
    strcpy(ds[9].name, "TrinhVanK");
    strcpy(ds[9].position, "IT");
    ds[9].baseSalary = 14000000;
    ds[9].workDay = 22;

    strcpy(ds[10].empId, "NV011");
    strcpy(ds[10].name, "LeThiL");
    strcpy(ds[10].position, "Receptionist");
    ds[10].baseSalary = 6500000;
    ds[10].workDay = 24;

    strcpy(ds[11].empId, "NV012");
    strcpy(ds[11].name, "PhanVanM");
    strcpy(ds[11].position, "Driver");
    ds[11].baseSalary = 7000000;
    ds[11].workDay = 25;

    n = 12;
}

int main(){
int choice;

Employd();

do{
    printf("\nXX=========== MENU ===========XX\n");
    printf("||1. Add new employee         ||\n");
    printf("||2. Update profile           ||\n");
    printf("||3. Fire employee	      ||\n");
    printf("||4. Show employees           ||\n");
    printf("||5. Search Name	      ||\n");
    printf("||6. Sorting by salary	      ||\n");
    printf("||7. Checkin date	      ||\n");
    printf("||8. View employee status     ||\n");
    printf("||9. Exit program	      ||\n");
    printf("XX============================XX\n");
   
   choice = Number("choose",1,9); 
    

    switch(choice){
        case 1:
            if(n < MAX){
                Newemp(&ds[n]);
                n++;
            } else {
                printf("The list is full!\n");
            }
            break;
        case 2:
            updateprofile(ds, n,&ds[n]);
            break;
        case 3:
            Fire(ds, &n);
            break;
        case 4:
            hienThiDS(ds, n);
            break;
        case 5:
        	Searchname(ds, n);
            break;
        case 6:
        	Sortstuff(ds, n);
            break;
        case 7:
			Checkin(ds, n, tsList, &tsCount);
            break;
        case 8:
			ShowTimesheet(ds, n, tsList, tsCount);
            break;
        case 9:
            printf("Exiting...\n");
            break;
        default:
            printf("ERROR: Invalid choice!\n");
    }
} while(choice != 9);

return 0;

}


