#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5

typedef struct {
    char id[50];
    char name[50];
    int age;
    float gpa;
} Student;

void inputStudent(Student *s) {
    printf("Nhap ID: ");
    scanf("%49s", s->id);

    while (getchar() != '\n');

    printf("Nhap ten: ");
    fgets(s->name, sizeof(s->name), stdin);
    size_t len = strlen(s->name);
    if (len > 0 && s->name[len - 1] == '\n') {
        s->name[len - 1] = '\0';
    }

    printf("Nhap tuoi: ");
    scanf("%d", &s->age);

    printf("Nhap GPA: ");
    scanf("%f", &s->gpa);
}

void printStudent(const Student *s) {
    printf("ID: %s | Name: %s | Age: %d | GPA: %.2f\n",
           s->id, s->name, s->age, s->gpa);
}

void saveToFile(const char *filename, const Student *list, int n) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong the mo file %s de ghi!\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s;%s;%d;%.2f\n",
                list[i].id,
                list[i].name,
                list[i].age,
                list[i].gpa);
    }

    fclose(f);
    printf("Da luu %d sinh vien vao file %s\n", n, filename);
}

int loadFromFile(const char *filename, Student *list, int maxStudents) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo file %s de doc!\n", filename);
        return 0;
    }

    int count = 0;

    while (count < maxStudents &&
           fscanf(f, " %49[^;];%49[^;];%d;%f",
                  list[count].id,
                  list[count].name,
                  &list[count].age,
                  &list[count].gpa) == 4) {
        int c;
        while ((c = fgetc(f)) != '\n' && c != EOF)
            ;

        count++;
    }

    fclose(f);
    return count;
}

int main(void) {
    Student studentList[MAX_STUDENTS];
    int n;

    do {
        printf("Nhap so luong sinh vien (toi da %d): ", MAX_STUDENTS);
        scanf("%d", &n);
        if (n < 1 || n > MAX_STUDENTS) {
            printf("So luong khong hop le! Vui long nhap lai.\n");
        }
    } while (n < 1 || n > MAX_STUDENTS);

    for (int i = 0; i < n; i++) {
        printf("\n=== Nhap thong tin sinh vien thu %d ===\n", i + 1);
        inputStudent(&studentList[i]);
    }

    printf("\n=== Danh sach sinh vien vua nhap ===\n");
    for (int i = 0; i < n; i++) {
        printStudent(&studentList[i]);
    }

    saveToFile("students.txt", studentList, n);
	
	Student loadedList[MAX_STUDENTS];
    int loadedCount = loadFromFile("students.txt", loadedList, MAX_STUDENTS);

	printf("\n=== Danh sach sinh vien doc tu file ===\n");
    for (int i = 0; i < loadedCount; i++) {
        printStudent(&loadedList[i]);
    }
    return 0;
}
