#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

// ------------------------
// Student Structure
// ------------------------
typedef struct {
    int roll;
    char name[50];
    char dept[50];
    float cgpa;
} Student;

// ------------------------
// Function Prototypes
// ------------------------
void addStudent();
void viewStudents();
void searchByRoll();
void searchByName();
void searchByDepartment();
void updateStudent();
void deleteStudent();
void sortByRollAscending();
void sortByRollDescending();
void sortByCGPAAscending();
void sortByCGPADescending();
void sortByNameAZ();
void sortByNameZA();
int loadData(Student s[]);
void saveData(Student s[], int n);

// ------------------------
// Main Menu
// ------------------------
int main() {
    int choice;

    while (1) {
        printf("\n====== Student Management System ======\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search by Roll\n");
        printf("4. Search by Name\n");
        printf("5. Search by Department\n");
        printf("6. Update Student\n");
        printf("7. Delete Student\n");
        printf("8. Sort by Roll (Ascending)\n");
        printf("9. Sort by Roll (Descending)\n");
        printf("10. Sort by CGPA (Ascending)\n");
        printf("11. Sort by CGPA (Descending)\n");
        printf("12. Sort by Name (A to Z)\n");
        printf("13. Sort by Name (Z to A)\n");
        printf("14. Exit\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: searchByDepartment(); break;
            case 6: updateStudent(); break;
            case 7: deleteStudent(); break;
            case 8: sortByRollAscending(); break;
            case 9: sortByRollDescending(); break;
            case 10: sortByCGPAAscending(); break;
            case 11: sortByCGPADescending(); break;
            case 12: sortByNameAZ(); break;
            case 13: sortByNameZA(); break;
            case 14: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

// ------------------------
// Add a new student
// ------------------------
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    Student s;

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    fflush(stdin);

    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(s.dept, 50, stdin);
    s.dept[strcspn(s.dept, "\n")] = '\0';

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// ------------------------
// Load all students into an array
// ------------------------
int loadData(Student s[]) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    int count = 0;
    while (fread(&s[count], sizeof(Student), 1, fp)) {
        count++;
    }
    fclose(fp);
    return count;
}

// ------------------------
// Save array data back to file
// ------------------------
void saveData(Student s[], int n) {
    FILE *fp = fopen(FILE_NAME, "wb");
    for (int i = 0; i < n; i++) {
        fwrite(&s[i], sizeof(Student), 1, fp);
    }
    fclose(fp);
}

// ------------------------
// View all students
// ------------------------
void viewStudents() {
    Student s[1000];
    int n = loadData(s);

    if (n == 0) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < n; i++) {
        printf("Roll: %d | Name: %s | Dept: %s | CGPA: %.2f\n",
               s[i].roll, s[i].name, s[i].dept, s[i].cgpa);
    }
}

// ------------------------
// Search by Roll
// ------------------------
void searchByRoll() {
    Student s[1000];
    int n = loadData(s);

    int roll;
    printf("Enter roll to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < n; i++) {
        if (s[i].roll == roll) {
            printf("Found: Roll: %d | Name: %s | Dept: %s | CGPA: %.2f\n",
                   s[i].roll, s[i].name, s[i].dept, s[i].cgpa);
            return;
        }
    }
    printf("Student not found!\n");
}

// ------------------------
// Search by Name
// ------------------------
void searchByName() {
    Student s[1000];
    int n = loadData(s);

    char name[50];
    fflush(stdin);
    printf("Enter name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcasecmp(s[i].name, name) == 0) {
            printf("Found: Roll: %d | Name: %s | Dept: %s | CGPA: %.2f\n",
                   s[i].roll, s[i].name, s[i].dept, s[i].cgpa);
            return;
        }
    }
    printf("Student not found!\n");
}

// ------------------------
// Search by Department
// ------------------------
void searchByDepartment() {
    Student s[1000];
    int n = loadData(s);

    char dept[50];
    fflush(stdin);
    printf("Enter department: ");
    fgets(dept, 50, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcasecmp(s[i].dept, dept) == 0) {
            printf("Roll: %d | Name: %s | CGPA: %.2f\n",
                   s[i].roll, s[i].name, s[i].cgpa);
            found = 1;
        }
    }

    if (!found) printf("No student found in this department!\n");
}

// ------------------------
// Update Student
// ------------------------
void updateStudent() {
    Student s[1000];
    int n = loadData(s);

    int roll;
    printf("Enter roll to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < n; i++) {
        if (s[i].roll == roll) {
            fflush(stdin);

            printf("Enter new name: ");
            fgets(s[i].name, 50, stdin);
            s[i].name[strcspn(s[i].name, "\n")] = '\0';

            printf("Enter new department: ");
            fgets(s[i].dept, 50, stdin);
            s[i].dept[strcspn(s[i].dept, "\n")] = '\0';

            printf("Enter new CGPA: ");
            scanf("%f", &s[i].cgpa);

            saveData(s, n);
            printf("Record updated!\n");
            return;
        }
    }

    printf("Student not found!\n");
}

// ------------------------
// Delete Student
// ------------------------
void deleteStudent() {
    Student s[1000];
    int n = loadData(s);

    int roll;
    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (s[i].roll == roll) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    for (int i = index; i < n - 1; i++) {
        s[i] = s[i + 1];
    }

    saveData(s, n - 1);
    printf("Record deleted successfully!\n");
}

// ------------------------
// Sorting Helper
// ------------------------
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// ------------------------
// Sorting Functions
// ------------------------
void sortByRollAscending() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].roll > s[j + 1].roll)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}

void sortByRollDescending() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].roll < s[j + 1].roll)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}

void sortByCGPAAscending() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].cgpa > s[j + 1].cgpa)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}

void sortByCGPADescending() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (s[j].cgpa < s[j + 1].cgpa)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}

void sortByNameAZ() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcasecmp(s[j].name, s[j + 1].name) > 0)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}

void sortByNameZA() {
    Student s[1000];
    int n = loadData(s);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcasecmp(s[j].name, s[j + 1].name) < 0)
                swap(&s[j], &s[j + 1]);

    saveData(s, n);
    viewStudents();
}
