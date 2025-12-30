#include "matrix.h"


// ������� �������� ������� � ��������� ������
int creatematrix(matrix* m, int rows, int cols) {
    if (rows < 1 || rows > MAX_SIZE || cols < 1 || cols > MAX_SIZE) {
        printf("������ ������� ������ ���� �� 1 �� 10\n");
        return 0; 
    }
    m->rows = rows; 
    m->cols = cols; 
    m->data = (int*)malloc(rows * cols * sizeof(int)); // �������� ������
    return 1; 
}

// ����������� ������ �������
void freematrix(matrix* m) { 
    if (m->data != NULL) {
        free(m->data); 
        m->data = NULL; // �������� ���������, ��� ��� ������ �� ��������� �� ������������ ������
    }
}

// ���� ������� ������
int mymatrix(matrix* m) {
    printf("������� �������� ������� %d ����� �� %d �������� ���������:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {               
        for (int j = 0; j < m->cols; j++) {        
            if (scanf("%d", m->data + i * m->cols + j) != 1) {
                while (getchar() != '\n');
                return 0;                          
            }
        }
    }
    return 1; 
}


// ����� ������� �� �����
void printmatrix(matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%2d ", *(m->data + i * m->cols + j));
        }
        printf("\n");
    }
}

//���������� ������������� �������
void genmatrix(matrix* m) {
    srand((unsigned int)time(NULL)); // ������������� ���������� ��������� �����. ������� srand - seed random
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            *(m->data + i * m->cols + j) = rand() % 100; // ����� �� 0 �� 99
        }
    }
    // ����� ������� � ������� printmatrix
    printf("��������������� ������� %d �� %d:\n", m->rows, m->cols);
    printmatrix(m);  

}

// �������� ������
int addmatrix(matrix* a, matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("��� ���� ������� ������� ������ ������ ���������.\n");
        return 0;
    }

    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            int df = *(a->data + i * a->cols + j) + *(b->data + i * b->cols + j);
            printf()
          //  *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) + *(b->data + i * b->cols + j);
        }
    }
    return 1;
}






// ��������� ������
int submatrix(matrix* a, matrix* b, matrix* res) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("��� ���� ������� ������� ������ ������ ���������.\n");
        return 0;
    }
    if (!creatematrix(res, a->rows, a->cols)) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) - *(b->data + i * b->cols + j);
        }
    }
    return 1;
}

// ��������� ������
int mulmatrix(matrix* a, matrix* b, matrix* res) {
    if (a->cols != b->rows) {
        //��������� ���������� �� �������� ������� �� ������
        printf("���������� �������� ������ ������� ������ ���� ����� ���������� ����� ������.\n");
        return 0;
    }
    if (!creatematrix(res, a->rows, b->cols)) return 0;
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            int sum = 0;
            for (int k = 0; k < a->cols; k++) { 
                sum += (*(a->data + i * a->cols + k)) * (*(b->data + k * b->cols + j));
            }
            *(res->data + i * res->cols + j) = sum;
        }
    }
    return 1;
}

// ���������������� �������
int transmatrix(matrix* a, matrix* res) {
    if (!creatematrix(res, a->cols, a->rows)) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            //������ ������ �� �������
            *(res->data + j * res->cols + i) = *(a->data + i * a->cols + j);
        }
    }
    return 1;
}



 
// ����������� ������� ��� ���������� ������� � �������
int copymatrix(matrix* a, matrix* res) {
    if (!creatematrix(res, a->rows, a->cols)) return 0;
    for (int i = 0; i < a->rows * a->cols; i++) {
        res->data[i] = a->data[i];
    }
    return 1;
}

// ���������� ������� � �������
int powermatrix(matrix* m, int power, matrix* res) {
    if (m->rows != m->cols) {
        printf("������� ������ ���� ���������� ��� ���������� � �������.\n");
        return 0;
    }
    if (power < 0) {
        printf("������� ������ ���� ��������������� ������.\n");
        return 0;
    }

    matrix temp, base;
    // ������� ��������� ������� � res
    if (!creatematrix(res, m->rows, m->cols)) return 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            res->data[i * res->cols + j] = (i == j) ? 1 : 0; 
        }
    }

    if (!copymatrix(m, &base)) return 0; //base - ������������� ����������� �������

    while (power > 0) {
        if (power % 2 == 1) {
            if (!mulmatrix(res, &base, &temp)) {
                freematrix(&base);
                freematrix(&temp);
                return 0;
            }
            freematrix(res);
            *res = temp;  // �������� ������� res �� ����
            temp.data = NULL;
        }
        if (power > 1) {
            if (!mulmatrix(&base, &base, &temp)) {
                freematrix(&base);
                freematrix(&temp);
                return 0;
            }       freematrix(&base);
            base = temp;  // �������� base � �������
            temp.data = NULL;
        }
        power /= 2;
    }

    freematrix(&base);
    return 1;
}



// ����� ������ ������� ��� ������ � �������������
void getminor(matrix* a, matrix* minor, int delrow, int delcol) { //��� ������ delrow � ������� delcol
    int r = 0, c; //�������� � ������ ������
    for (int i = 0; i < a->rows; i++) {
        if (i == delrow) continue;
        c = 0; // �������� � ������� �������
        for (int j = 0; j < a->cols; j++) {
            if (j == delcol) continue;
            minor->data[r * minor->cols + c] = a->data[i * a->cols + j];
            c++;
        }
        r++;
    }
}

//����� ������������ �������
int determinant(matrix* m) {
    if (m->rows != m->cols) {
        printf("������������ ����� ������� ������ ��� ���������� �������.\n");
        return 0; 
    }

    int n = m->rows;

    //���� ������� 1 �� 1, �� ������������ = �����
    if (n == 1) {
        return m->data[0];
    }

    //���� ������� 2 �� 2
    if (n == 2) {
        return m->data[0] * m->data[3] - m->data[1] * m->data[2];
    }

    int det = 0; //����� ����� �������� ���������
    int sign = 1; //����� ����

    matrix minor;
    if (!creatematrix(&minor, n - 1, n - 1)) return 0;

    for (int j = 0; j < n; j++) {
        getminor(m, &minor, 0, j);
        det += sign * m->data[j] * determinant(&minor);
        sign = -sign; //����� ����������
    }

    freematrix(&minor);
    return det;
}