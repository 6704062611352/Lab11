#include <stdio.h>
#define NO_SCORE 5
#define NO_STD 10 
#include <direct.h> 
typedef struct {
    char name[16];
    char surname[20];
    int score[NO_SCORE];
    float total;
} Student;

void readStudentData(Student *);
void findTotalScore(Student *);
float findAverage(Student);
void findLessThanTen(Student);

int main() {
    Student std;
    FILE *fptr;
    int i;
    char path[256];
    getcwd(path, sizeof(path));  // ?????
    printf("Working dir: %s\n", path);  // ?????

    fptr = fopen(".\\std10.dat", "wb");
    if (fptr == NULL) {
        printf("Error: Could not create folder or file!\n");
        return 1;
    }

    for (i = 0; i < NO_STD; i++) {
        printf("\nStudent #%d\n", i + 1);
        readStudentData(&std);
        fwrite(&std, sizeof(Student), 1, fptr);
    }
    fclose(fptr);

    printf("\n--- Reading Data from File ---\n");
    fptr = fopen(".\\std10.dat", "rb"); 
    if (fptr == NULL) return 1;

    while (fread(&std, sizeof(Student), 1, fptr)) {
        findTotalScore(&std);
        float avg = findAverage(std);
        printf("\n\tAverage score is %.2f", avg);
        findLessThanTen(std);
        printf("\n------------------------------\n");
    }

    fclose(fptr);
    return 0;
}

void readStudentData(Student *pStd) {
    int i;
    printf("\tName : ");
    scanf("%s", pStd->name);
    printf("\tSurname : ");
    scanf("%s", pStd->surname);
    for (i = 0; i < NO_SCORE; i++) {
        printf("\tScore %d : ", i + 1);
        scanf("%d", &pStd->score[i]);
    }
}

void findTotalScore(Student *pStd) {
    int i;
    printf("\n%s %s got score: ", pStd->name, pStd->surname);
    pStd->total = 0.0;
    for (i = 0; i < NO_SCORE; i++) {
        printf("%6d", pStd->score[i]);
        pStd->total += pStd->score[i];
    }
    printf("\n\tTotal score is %.2f", pStd->total);
}

float findAverage(Student s) {
    return (s.total / NO_SCORE);
}

void findLessThanTen(Student s) {
    int i, count = 0;
    printf("\n\tScore less than 10:");
    for (i = 0; i < NO_SCORE; i++) {
        if (s.score[i] < 10) {
            printf("\n\t   Test no.%d - %d", i + 1, s.score[i]);
            count++;
        }
    }
    if (count == 0) printf(" None");
}