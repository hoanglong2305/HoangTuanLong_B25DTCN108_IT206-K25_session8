#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

void printStudentTable(struct Student students[], int count) {
    printf("\n");
    printf("+------+----------------------+------+-------+\n");
    printf("| ID   | Ho Ten               | Tuoi | GPA   |\n");
    printf("+------+----------------------+------+-------+\n");
    
    for (int i = 0; i < count; i++) {
        printf("| %-4d | %-20s | %-4d | %-5.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }
    
    printf("+------+----------------------+------+-------+\n");
    printf("\n");
}

void inputStudents(struct Student students[], int count) {
    printf("\n========== NHAP THONG TIN SINH VIEN ==========\n");
    for (int i = 0; i < count; i++) {
        printf("\n--- Sinh vien thu %d ---\n", i + 1);
        
        printf("Nhap ID: ");
        scanf("%d", &students[i].id);
        getchar();
        
        printf("Nhap ho ten: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        int len = strlen(students[i].name);
        if (len > 0 && students[i].name[len - 1] == '\n') {
            students[i].name[len - 1] = '\0';
        }
        
        printf("Nhap tuoi: ");
        scanf("%d", &students[i].age);
        
        printf("Nhap GPA: ");
        scanf("%f", &students[i].gpa);
    }
}

void saveToFile(struct Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("\nLoi: Khong the mo file %s de ghi!\n", filename);
        return;
    }
    
    fprintf(file, "%d\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n%s\n%d\n%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    fprintf(file, "\n========== DANH SACH SINH VIEN ==========\n");
    fprintf(file, "+------+----------------------+------+-------+\n");
    fprintf(file, "| ID   | Ho Ten               | Tuoi | GPA   |\n");
    fprintf(file, "+------+----------------------+------+-------+\n");
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "| %-4d | %-20s | %-4d | %-5.2f |\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    fprintf(file, "+------+----------------------+------+-------+\n");
    fprintf(file, "\nTong so sinh vien: %d\n", count);
    
    fclose(file);
    printf("\nDa luu danh sach sinh vien vao file %s thanh cong!\n", filename);
}

int readFromFile(struct Student students[], int maxCount) {
    FILE *file = fopen("student.txt", "r");
    
    if (file == NULL) {
        printf("\nLoi: Khong the mo file de doc!\n");
        return 0;
    }
    
    int count;
    fscanf(file, "%d", &count);
    
    if (count > maxCount) {
        count = maxCount;
    }
    
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &students[i].id);
        fgetc(file);
        fgets(students[i].name, sizeof(students[i].name), file);
        int len = strlen(students[i].name);
        if (len > 0 && students[i].name[len - 1] == '\n') {
            students[i].name[len - 1] = '\0';
        }
        fscanf(file, "%d", &students[i].age);
        fscanf(file, "%f", &students[i].gpa);
    }
    
    fclose(file);
    printf("\nDa doc %d sinh vien tu file student.txt thanh cong!\n", count);
    return count;
}

/**
 * Hàm tìm ki?m sinh viên theo ID
 * 
 * @param students M?ng ch?a danh sách sinh viên
 * @param count S? lu?ng sinh viên trong m?ng
 * @param id ID c?n tìm ki?m
 * @return Ch? s? c?a sinh viên trong m?ng n?u tìm th?y (>= 0), 
 *         -1 n?u không tìm th?y ho?c ID không h?p l? (âm)
 * 
 * @note Hàm s? duy?t qua m?ng và so sánh ID c?a t?ng sinh viên v?i ID c?n tìm
 *       N?u ID là s? âm, hàm s? tr? v? -1 ngay l?p t?c
 * 
 * @example
 *   struct Student students[3] = {{1, "Nguyen Van A", 20, 3.75}, ...};
 *   int index = searchByID(students, 3, 1);  // Tr? v? 0
 *   int index2 = searchByID(students, 3, 5); // Tr? v? -1 (không tìm th?y)
 *   int index3 = searchByID(students, 3, -1); // Tr? v? -1 (ID âm)
 */
int searchByID(struct Student students[], int count, int id) {
    if (id < 0) {
        return -1;
    }
    
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i; // Tìm th?y, tr? v? ch? s?
        }
    }
    
    return -1;
}

/**
 * Hàm in thông tin m?t sinh viên
 * 
 * @param student Con tr? d?n sinh viên c?n in
 */
void printStudent(struct Student *student) {
    printf("\n--- Thong tin sinh vien ---\n");
    printf("ID: %d\n", student->id);
    printf("Ho ten: %s\n", student->name);
    printf("Tuoi: %d\n", student->age);
    printf("GPA: %.2f\n", student->gpa);
}

/**
 * Hàm test các tru?ng h?p tìm ki?m sinh viên theo ID
 * 
 * @param students M?ng ch?a danh sách sinh viên
 * @param count S? lu?ng sinh viên trong m?ng
 */
void testSearchByID(struct Student students[], int count) {
    printf("\n========== TEST TIM KIEM SINH VIEN THEO ID ==========\n");
    
    printf("\n--- Test case 1: Tim ID ton tai ---\n");
    int searchId1 = students[0].id;
    int index1 = searchByID(students, count, searchId1);
    if (index1 >= 0) {
        printf("Tim thay sinh vien co ID = %d tai vi tri %d\n", searchId1, index1);
        printStudent(&students[index1]);
    } else {
        printf("Khong tim thay sinh vien co ID = %d\n", searchId1);
    }
    
    printf("\n--- Test case 2: Tim ID khong ton tai ---\n");
    int searchId2 = 9999;
    int index2 = searchByID(students, count, searchId2);
    if (index2 >= 0) {
        printf("Tim thay sinh vien co ID = %d tai vi tri %d\n", searchId2, index2);
        printStudent(&students[index2]);
    } else {
        printf("Khong tim thay sinh vien co ID = %d (Ket qua mong doi: -1)\n", searchId2);
    }
    
    printf("\n--- Test case 3: Tim ID am (khong hop le) ---\n");
    int searchId3 = -5;
    int index3 = searchByID(students, count, searchId3);
    if (index3 >= 0) {
        printf("Tim thay sinh vien co ID = %d tai vi tri %d\n", searchId3, index3);
        printStudent(&students[index3]);
    } else {
        printf("ID = %d khong hop le (ID am). Ket qua: -1 (Ket qua mong doi)\n", searchId3);
    }
    
    printf("\n========== KET THUC TEST ==========\n");
}

/**
 * Hàm kh?i t?o 10 sinh viên v?i di?m GPA khác nhau
 * 
 * @param students M?ng ch?a danh sách sinh viên
 * @return S? lu?ng sinh viên dã kh?i t?o (10)
 */
int create10Students(struct Student students[]) {
    struct Student data[] = {
        {1, "Nguyen Van An", 20, 3.25},
        {2, "Tran Thi Binh", 19, 3.75},
        {3, "Le Van Cuong", 21, 2.85},
        {4, "Pham Thi Dung", 20, 3.92},
        {5, "Hoang Van Em", 22, 2.50},
        {6, "Vu Thi Phuong", 19, 3.68},
        {7, "Dao Van Giang", 20, 3.45},
        {8, "Bui Thi Hang", 21, 4.00},
        {9, "Dang Van Huy", 20, 2.95},
        {10, "Ngo Thi Lan", 19, 3.55}
    };
    
    // Copy d? li?u vào m?ng students
    for (int i = 0; i < 10; i++) {
        students[i] = data[i];
    }
    
    printf("\nDa khoi tao 10 sinh vien voi diem GPA khac nhau!\n");
    return 10;
}

/**
 * Hàm tính di?m trung bình GPA c?a danh sách sinh viên
 * 
 * @param students M?ng ch?a danh sách sinh viên
 * @param count S? lu?ng sinh viên trong m?ng
 * @return Ði?m trung bình GPA (float)
 * 
 * @note N?u count = 0, hàm s? tr? v? 0.0 d? tránh chia cho 0
 */
float calculateAverageGPA(struct Student students[], int count) {
    if (count == 0) {
        return 0.0;
    }
    
    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }
    
    return sum / count;
}

/**
 * Hàm s?p x?p danh sách sinh viên tang d?n theo di?m GPA
 * 
 * @param students M?ng ch?a danh sách sinh viên c?n s?p x?p
 * @param count S? lu?ng sinh viên trong m?ng
 * 
 * @note S? d?ng thu?t toán Bubble Sort d? s?p x?p
 *       Hàm s? s?p x?p tr?c ti?p trên m?ng students (s?p x?p t?i ch?)
 *       Sau khi s?p x?p, sinh viên có GPA th?p nh?t s? ? d?u m?ng,
 *       sinh viên có GPA cao nh?t s? ? cu?i m?ng
 * 
 * @example
 *   struct Student students[3] = {
 *       {1, "Nguyen Van A", 20, 3.75},
 *       {2, "Tran Thi B", 19, 3.25},
 *       {3, "Le Van C", 21, 3.92}
 *   };
 *   sortStudentsByGPA(students, 3);
 *   // Sau khi s?p x?p: Tran Thi B (3.25) -> Nguyen Van A (3.75) -> Le Van C (3.92)
 */
void sortStudentsByGPA(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].gpa > students[j + 1].gpa) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/**
 * Hàm thêm m?t sinh viên vào danh sách
 * * @param students M?ng ch?a danh sách sinh viên
 * @param count Con tr? qu?n lý s? lu?ng sinh viên hi?n t?i (d? c?p nh?t giá tr? sau khi thêm)
 * @param maxCount Kích thu?c t?i da c?a m?ng
 * @return 1 n?u thêm thành công, 0 n?u m?ng dã d?y
 */
int addStudent(struct Student students[], int *count, int maxCount) {
    if (*count >= maxCount) {
        printf("\nLoi: Danh sach da day, khong the them sinh vien moi!\n");
        return 0;
    }

    printf("\n--- Nhap thong tin sinh vien moi (Vi tri index %d) ---\n", *count);
    
    printf("Nhap ID: ");
    scanf("%d", &students[*count].id);
    getchar();

    printf("Nhap ho ten: ");
    fgets(students[*count].name, sizeof(students[*count].name), stdin);
    int len = strlen(students[*count].name);
    if (len > 0 && students[*count].name[len - 1] == '\n') {
        students[*count].name[len - 1] = '\0';
    }

    printf("Nhap tuoi: ");
    scanf("%d", &students[*count].age);

    printf("Nhap GPA: ");
    scanf("%f", &students[*count].gpa);

    (*count)++;
    printf("\nDa them sinh vien thanh cong!\n");
    return 1;
}

/**
 * Hàm xóa sinh viên kh?i danh sách theo ID
 * * @param students M?ng ch?a danh sách sinh viên
 * @param count Con tr? qu?n lý s? lu?ng sinh viên hi?n t?i
 * @param id ID c?a sinh viên c?n xóa
 * @return 1 n?u xóa thành công, 0 n?u không tìm th?y ID
 */
int deleteStudentByID(struct Student students[], int *count, int id) {
    int index = searchByID(students, *count, id);

    if (index == -1) {
        printf("\nLoi: Khong tim thay sinh vien co ID = %d de xoa!\n", id);
        return 0;
    }

    for (int i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--; 
    printf("\nDa xoa sinh vien co ID = %d thanh cong!\n", id);
    return 1;
}

int main() {
    const int NUM_STUDENTS = 3;
    struct Student students[NUM_STUDENTS];
    struct Student studentsFromFile[NUM_STUDENTS];
    
    // Nh?p thông tin sinh viên t? bàn phím
    inputStudents(students, NUM_STUDENTS);
    
    // In danh sách sinh viên du?i d?ng b?ng
    printf("\n========== DANH SACH SINH VIEN ==========");
    printStudentTable(students, NUM_STUDENTS);
    
    // Luu danh sách sinh viên vào file (ví d?: student.txt cho l?p m?c d?nh)
    saveToFile(students, NUM_STUDENTS, "student.txt");
    
    // Ð?c d? li?u t? file student.txt
    int count = readFromFile(studentsFromFile, NUM_STUDENTS);
    
    // In d? li?u dã d?c t? file ra màn hình
    if (count > 0) {
        printf("\n========== DANH SACH SINH VIEN DOC TU FILE ==========");
        printStudentTable(studentsFromFile, count);
    }
    
    // Test hàm tìm ki?m sinh viên theo ID
    testSearchByID(students, NUM_STUDENTS);
    
    // ========== PH?N T?O 10 SINH VIÊN VÀ TÍNH ÐI?M TRUNG BÌNH ==========
    printf("\n\n");
    printf("=================================================================\n");
    printf("PHAN 2: TAO 10 SINH VIEN VA TINH DIEM TRUNG BINH GPA\n");
    printf("=================================================================\n");
    
    struct Student students10[10];
    int count10 = create10Students(students10);
    
    // In danh sách 10 sinh viên
    printf("\n========== DANH SACH 10 SINH VIEN ==========");
    printStudentTable(students10, count10);
    
    // Tính di?m trung bình GPA
    float avgGPA = calculateAverageGPA(students10, count10);
    printf("\n========== KET QUA TINH TOAN ==========\n");
    printf("Diem trung binh GPA cua %d sinh vien: %.2f\n", count10, avgGPA);
    printf("===========================================\n");
    
    // S?p x?p sinh viên tang d?n theo GPA
    sortStudentsByGPA(students10, count10);
    printf("\n========== DANH SACH 10 SINH VIEN SAU KHI SAP XEP TANG DAN THEO GPA ==========");
    printStudentTable(students10, count10);
    
    addStudent(students, &currentCount, 100);
    printf("\n--- Bang sau khi them sinh vien ---");
    printStudentTable(students, currentCount);

	int currentCount = 0;

    // 1. Gi? s? kh?i t?o 10 sinh viên tru?c
    currentCount = create10Students(students);
    printStudentTable(students, currentCount);

    // 3. Test ch?c nang XÓA
    int idToDelete;
    printf("\nNhap ID sinh vien muon xoa: ");
    scanf("%d", &idToDelete);
    deleteStudentByID(students, &currentCount, idToDelete);
    
    printf("\n--- Bang sau khi xoa sinh vien ---");
    printStudentTable(students, currentCount);
    
    return 0;
}




