﻿#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

void Fun_Filling(double matrix[5][5], const size_t FFT_1, const size_t FFT_2, int limiterZapolnenia, int RangeMax_min) {
    srand(time(NULL));
    int n1, n2;
    float tRandChislo_1;
    for (int i = 0; i < limiterZapolnenia; i++) {
        n1 = rand() % FFT_1;
        n2 = rand() % FFT_1;
        tRandChislo_1 = rand() % RangeMax_min;
            matrix[n1][n2] = tRandChislo_1;
    }
}
void Fun_Matrix_Multiplication(double matrix1[5][5], double matrix2[5][5], double matrix3[5][5], const size_t FFT_1_1, const size_t FFT_1_2) 
{
    for (int row = 0; row < FFT_1_1; row++) {
        for (int col = 0; col < FFT_1_2; col++) {
            matrix3[row][col] += matrix2[row][col] * matrix1[row][col];
        }
    }
}
void Fun_Threshold(double matrix1[5][5], const size_t FFT_1, const size_t FFT_2)
{
    const float e = 2.718;
    for (int row = 0; row < FFT_1; row++) 
    {
        for (int col = 0; col < FFT_2; col++) 
        {
            matrix1[row][col] = 1 / (1 + pow(e, -(matrix1[row][col])));
        }
    }
}
void Fun_Matrix_Glaz(double matrix1[5][5], const size_t FFT_1, const size_t FFT_2)
{
    for (int row = 0; row < FFT_1; row++) {
        for (int col = 0; col < FFT_2; col++) {
            cout << "|" << setprecision(3) << matrix1[row][col] << "|";
        }
        cout << "\n";
    }
    cout << "\n\n";
}
void Fun_Matrix_Error(double matrix1[5][5], double matrix2[5][5], double matrix3[5][5], const size_t FFT_1, const size_t FFT_2) {
    float Chislo_1 = 0;

    for (int row_1 = 0; row_1 < FFT_1; row_1++) {
        for (int col_1 = 0; col_1 < FFT_2; col_1++) {
            Chislo_1 += matrix2[row_1][col_1];
        }
    }

    for (int col_1 = 0; col_1 < FFT_1; col_1++) {
        for (int row_1 = 0; row_1 < FFT_2; row_1++) {
            if (matrix2[row_1][col_1] == 0) {
                matrix2[row_1][col_1] = 0.01;
            }

            matrix3[col_1][row_1] = (matrix1[row_1][col_1]) * (matrix2[row_1][col_1] / Chislo_1);
        }
    }
    
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int Org_f = 0;
    int Org_w;
    cout << "Введите количество итераций: ";
    cin >> Org_w;
    const size_t J_1_1 = 5;
    const size_t J_1_2 = 5;
    double matrix_1[J_1_1][J_1_2]{};
    Fun_Filling(matrix_1, J_1_1, J_1_2, 1000, 10);
    const size_t W_1_1 = 5;
    const size_t W_1_2 = 5;
    double matrixWeight_1[W_1_1][W_1_2]{};
    Fun_Filling(matrixWeight_1, W_1_1, W_1_2, 1000, 10);
    const size_t J_2_1 = 5;
    const size_t J_2_2 = 5;
    double matrix_2[J_2_1][J_2_2]{};
    const size_t W_2_1 = 5;
    const size_t W_2_2 = 5;
    double matrixWeight_2[W_2_1][W_2_2]{};
    Fun_Filling(matrixWeight_2, W_2_1, W_2_2, 1000, 10);
    const size_t J_3_1 = 5;
    const size_t J_3_2 = 5;
    double matrix_3[J_3_1][J_3_2]{};
    for (int i = 1; i <= Org_w; i++) {
        Org_f = i;
        cout << endl << "\tИтерация: " << Org_f << "\n\n";
        Fun_Matrix_Multiplication(matrix_1, matrixWeight_1, matrix_2, J_2_1, J_2_2);
        Fun_Threshold(matrix_2, J_2_1, J_2_2);
        Fun_Matrix_Multiplication(matrix_2, matrixWeight_2, matrix_3, J_2_1, J_2_2);
        Fun_Threshold(matrix_3, J_3_1, J_3_2);
        Fun_Matrix_Glaz(matrix_1, J_1_1, J_1_2);
        Fun_Matrix_Glaz(matrix_2, J_2_1, J_2_2);
        Fun_Matrix_Glaz(matrix_3, J_3_1, J_3_2);
        Fun_Matrix_Error(matrix_3, matrixWeight_2, matrix_2, J_2_1, J_2_2);
        Fun_Matrix_Error(matrix_2, matrixWeight_1, matrix_1, J_1_1, J_1_2);
        Fun_Matrix_Glaz(matrix_3, J_1_1, J_1_2);
        Fun_Matrix_Glaz(matrix_2, J_2_1, J_2_2);
        Fun_Matrix_Glaz(matrix_1, J_3_1, J_3_2);
        cout << endl <<"------------------------------------------" << "\n";
    }
    system("PAUSE");
    return 0;
}


