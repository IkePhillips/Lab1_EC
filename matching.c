#include <stdio.h>



void read_matrix(FILE* fp, int matrix[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
}

void remove_assigned_programmer(int department_preferences[5][5], int department, int assigned_programmers[5]) {
    do {
        for (int i = 0; i < 4; i++) {
            department_preferences[i][department] = department_preferences[i+1][department];
        }
    } while(assigned_programmers[department_preferences[0][department]-1]);
}


void find_available_programmer(int department_preferences[5][5], int programmer_preferences[5][5], int *preferred_department, int *next_department, int current_department, int assigned_programmers[5]) {
        for (int i = 0; i < 5; i++) {
            if (programmer_preferences[i][*preferred_department] == *next_department+1) {
                remove_assigned_programmer(department_preferences, current_department, assigned_programmers);
                *next_department = current_department;
                *preferred_department = department_preferences[0][current_department]-1;
                break;
            }
            if (programmer_preferences[i][*preferred_department] == current_department+1) {
                remove_assigned_programmer(department_preferences, *next_department, assigned_programmers);
                break;
            } 
        }
}

int main() {
    FILE* fp = fopen("matching-data.txt", "r");

    int department_preferences[5][5];
    int programmer_preferences[5][5];
    read_matrix(fp, department_preferences);
    read_matrix(fp, programmer_preferences);
    fclose(fp);
    
    int preferred_department;
    int assigned_programmers[5];
    
    for (int i = 0; i < 5; i++) {
        assigned_programmers[i] = 0;
    }
    
    for (int i = 0; i < 5; i++) {
        preferred_department = department_preferences[0][i]-1;
        for (int j = i+1; j < 5; j++) {
            if (department_preferences[0][i] == department_preferences[0][j]) {
               find_available_programmer(department_preferences, programmer_preferences, &preferred_department, &j, i, assigned_programmers);
            }
        }  
        printf("Department #%d will get Programmer #%d\n", i+1, preferred_department+1);
        assigned_programmers[preferred_department] = 1;
    }

    return 0;
}

