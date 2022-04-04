#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //��� ���� ���� �޾Ƽ� ���(2���� �迭)�� ����� �Լ�
void print_matrix(int** matrix, int row, int col); //���������Ϳ� ��� ���� ���� �޾Ƽ� ����� ��� ���� ����ϴ� �Լ�
int free_matrix(int** matrix, int row, int col); //���������Ϳ� ��� ���� ���� �޾Ƽ� 
                                                 //���(2���� �迭)�� �Ҵ�� ��� �޸𸮸� free��Ű�� �Լ�
int fill_data(int** matrix, int row, int col); //���������Ϳ� ��� ���� ���� �޾Ƽ�
                                               //����� ����� 2���� �迭�� 0~19�� ���� ���� �Ҵ��ϴ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //��� �� ���� ���ϴ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //��� �� ���� ���� �Լ�(���� �Ϳ��� �ڿ� ���� ����)
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //����� ��ġ����� ����� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //��� �� ���� ���ϴ� �Լ�

int main()
{

    char command; //��ɾ ���� ����
    printf("[----- ������  2020039027 -----]\n"); //�̸� �й� ���

    int row, col; //��� ���� ���� ���� ����
    srand(time(NULL)); //���� ���� ����� ���� seed�� �ð����� �Ѵ�.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //��� ���� �� �Է�
    int** matrix_a = create_matrix(row, col); //a��� �����
    int** matrix_b = create_matrix(row, col); //b��� �����
    int** matrix_a_t = create_matrix(col, row); //a�� ��ġ��� �����

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} 
    //a�� b���(2���� �迭)�� ����Ű�� ���� �����Ͱ� NULL���̸� ���� �߻��̹Ƿ� ���α׷� ���� 

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");
        //���� �޴� ���
        printf("Command = ");
        scanf(" %c", &command); //command �Է�

        switch(command) {
        case 'z': case 'Z': //z�� �Է����� �� fill_data�Լ��� ����� ���������� ä����
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': //p�� �Է����� �� print_matrix�Լ��� ����� ���
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a�� �Է����� �� addition_matrix�Լ��� �� ����� ���� ����� ���
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //s�� �Է����� �� subtraction_matrix�Լ��� �� ��Ŀ��� �� ����� �� ����� ���
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //t�� �Է����� �� transpose_matrix�Լ��� �ش� ����� ��ġ����� ������ְ� ���
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': //m�� �Է����� �� multiply_matrix�Լ��� �� ��Ŀ� �� ����� ���� ����� ���
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': //q�� �Է����� �� ����� ����ִ� �޸𸮸� free�����ְ� do while�� Ż��
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //�� �̿��� �� �߸� �Է������Ƿ� �����϶�� �˷���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //command�� q�Ǵ� Q�� �ƴϸ� ���� �ݺ�

    return 1; //�����Լ� ����
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0) //row�� col�� �Է°��� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է°��� Ȯ���϶�� ���
        return NULL; //NULL���� ����(�Լ��� ����)
    }

    int** matrix = (int**)malloc(sizeof(int*) * row); /* ���� ������ŭ int�� ����Ű�� 
                                                         �����͸� ���� �޸𸮸� �Ҵ� */
    for(int i=0; i<row; i++) //���� ������ŭ �ݺ�
    {
        matrix[i] = (int*)malloc(sizeof(int) * col);
        /* ���� ����Ű�� �����Ϳ� ���� ũ�⸸ŭ�� �޸� �Ҵ� */
    }

    if(matrix == NULL) //matrix�� ���� NULL�϶�(malloc���� ���� ���޾��� ��)
    {
        printf("Memory Allocation Failed.\n"); //�޸� �Ҵ� ���� ���
        return NULL; //NULL���� ����(�Լ��� ����)
    }

    return matrix; //matrix(���� ����Ű�� ������ �迭�� ù ��° �ּ�)�� ����
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return; //return ��ɾ�� �Լ��� ������.
    }

    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        for(int j=0; j<col; j++) //col��ŭ �ݺ�
        {
            printf("%3d ", matrix[i][j]); //2���� �迭�� ���� ���
        }
        printf("\n");
    }

    if(matrix == NULL) //matrix�� ���� NULL�� ��
    //matrix���� NULL�̸� �޸� �Ҵ翡�� ������ �� ���̰ų� �Լ��� �Է��� �߸��� ��
    {
        printf("Memory Allocation Failed.\n"); //�޸� �Ҵ� ���� ���
        return;
    }

    return; //�Լ� ���� ��� ��ɾ ������ �������� �Լ��� ����
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }
    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        free(matrix[i]); //���� ����Ű�� �����͵鿡 �Ҵ�� �޸𸮸� free��Ų��.
    }
    free(matrix); //�� �����͵��� ����Ű�� �����Ϳ� �Ҵ�� �޸𸮸� free��Ų��.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }
    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        for(int j=0; j<col; j++) //col��ŭ �ݺ�
        {
            matrix[i][j] = rand()%20; //2���� �迭�� ���ҿ� 0~19�� ���� �� �Ҵ�
        }
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
    //���������� matrix_sum�� ��� ���� row�� col�� ����� �޸��� �ּ� �Ҵ� 

    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }

    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        for(int j=0; j<col; j++) //col��ŭ �ݺ�
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
            /* ���� ��� ���� �����ϴ� ���ҳ��� ���ؼ� sum����� ���� �Ҵ��Ѵ�. */ 
        }
    }
    print_matrix(matrix_sum, row, col); //matrix_sum ���
    free_matrix(matrix_sum, row, col); //matrix_sum�� �Ҵ�� ��� �޸𸮸� free��Ų��.
    return 1; //1�� ����(�Լ��� ������ ����)
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int **matrix_sub = create_matrix(row, col);
     //���������� matrix_sub�� ��� ���� row�� col�� ����� �޸��� �ּ� �Ҵ�
    
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }

    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        for(int j=0; j<col; j++) //col��ŭ �ݺ�
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
            /* ���� ��� ���� �����ϴ� ���ҳ��� ���� sub����� ���� �Ҵ��Ѵ�. */
        }
    }
    print_matrix(matrix_sub, row, col); //matrix_sub ���
    free_matrix(matrix_sub, row, col); //matrix_sub�� �Ҵ�� ��� �޸𸮸� free��Ų��.

    return 1; //1�� ����(�Լ��� ������ ����)
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }

    for(int i=0; i<row; i++) //row��ŭ �ݺ�
    {
        for(int j=0; j<col; j++) //col��ŭ �ݺ�
        {
            matrix_t[i][j] = matrix[j][i];
            /* matrix�� ���Ҹ� ��� ���� �ٲ� matrix_t�� ���ҿ� �Ҵ� */
        }
    }
    if(matrix == NULL || matrix_t == NULL) //matrix�Ǵ� matrix_t�� ���� NULL�� ��
    {
        printf("Memory Allocation Failed.\n"); //�޸� �Ҵ� ���� ���
        return -1; //-1�� ����(���� �߻�)
    }
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_axt = create_matrix(row, row);
    //��ġ��İ��� ���̹Ƿ� ��� ���� ������ �� ����� ��� ���� ������ ����. 
    if(row <= 0 || col <= 0) //row�� col�� ���� 0���� �۰ų� ������
    {
        printf("Check the size of row and col!\n"); //�Է��� ���� Ȯ���϶�� ���
        return -1; //return ��ɾ�� �Լ��� ������.(-1�̸� ������� Ȯ�� ����)
    }

	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) //row��ŭ �ݺ�
    {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) //row��ŭ �ݺ�
        {
			int temp = 0; //matrix_a�� ��� matrix_t�� ���� ���ؼ� ���� ���� ���� ������ ���� 
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
            {
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
                //temp�� matrix_a�� ���� ���ҿ� �׿� �����ϴ� matrix_t�� ���� ������ ���� ���ؼ� ����
            }
			matrix_axt[matrix_a_row][matrix_t_row] = temp; //������ ���� ���� temp�� ���� matrix_axt�� ���ҿ� ����
		}
	}

    if(matrix_t == NULL || matrix_axt == NULL) //matrix_t�Ǵ� matrix_axt�� ���� NULL�� ��
    {
        printf("Memory Allocation Failed.\n"); //�޸� �Ҵ� ���� ���
        return -1; //-1�� ����(���� �߻�)
    }

    print_matrix(matrix_axt, row, row); //matrix_axt ���
    free_matrix(matrix_axt, row, col); //���������� matrix_axt�� �Ҵ�� ��� �޸𸮸� free��Ų��.
    
    return 1; //1�� ����(�Լ��� ������ ����)

}
