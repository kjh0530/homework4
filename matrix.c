#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //행과 열의 값을 받아서 행렬(2차원 배열)을 만드는 함수
void print_matrix(int** matrix, int row, int col); //이중포인터와 행과 열의 값을 받아서 행렬의 모든 값을 출력하는 함수
int free_matrix(int** matrix, int row, int col); //이중포인터와 행과 열의 값을 받아서 
                                                 //행렬(2차원 배열)에 할당된 모든 메모리를 free시키는 함수
int fill_data(int** matrix, int row, int col); //이중포인터와 행과 열의 값을 받아서
                                               //행렬이 저장된 2차원 배열에 0~19의 랜덤 값을 할당하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //행렬 두 개를 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //행렬 두 개를 빼는 함수(앞의 것에서 뒤에 것을 뺀다)
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //행렬의 전치행렬을 만드는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //행렬 두 개를 곱하는 함수

int main()
{

    char command; //명령어를 받을 변수
    printf("[----- 김주훈  2020039027 -----]\n"); //이름 학번 출력

    int row, col; //행과 열의 값을 받을 변수
    srand(time(NULL)); //랜덤 값을 만들기 위한 seed를 시간으로 한다.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //행과 열의 값 입력
    int** matrix_a = create_matrix(row, col); //a행렬 만들기
    int** matrix_b = create_matrix(row, col); //b행렬 만들기
    int** matrix_a_t = create_matrix(col, row); //a의 전치행렬 만들기

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} 
    //a와 b행렬(2차원 배열)을 가리키는 이중 포인터가 NULL값이면 오류 발생이므로 프로그램 종료 

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");
        //조작 메뉴 출력
        printf("Command = ");
        scanf(" %c", &command); //command 입력

        switch(command) {
        case 'z': case 'Z': //z를 입력했을 때 fill_data함수로 행렬을 랜덤값으로 채워줌
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': //p를 입력했을 때 print_matrix함수로 행렬을 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': //a를 입력했을 때 addition_matrix함수로 두 행렬을 더한 행렬을 출력
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': //s를 입력했을 때 subtraction_matrix함수로 앞 행렬에서 뒤 행렬을 뺀 행렬을 출력
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': //t를 입력했을 때 transpose_matrix함수로 해당 행렬의 전치행렬을 만들어주고 출력
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': //m을 입력했을 때 multiply_matrix함수로 앞 행렬에 뒤 행렬을 곱한 행렬을 출력
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': //q를 입력했을 때 행렬이 잡고있던 메모리를 free시켜주고 do while문 탈출
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //그 이외일 때 잘못 입력했으므로 집중하라고 알려줌
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //command가 q또는 Q가 아니면 무한 반복

    return 1; //메인함수 종료
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0) //row와 col의 입력값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력값을 확인하라고 출력
        return NULL; //NULL값을 리턴(함수를 끝냄)
    }

    int** matrix = (int**)malloc(sizeof(int*) * row); /* 행의 개수만큼 int를 가리키는 
                                                         포인터를 받을 메모리를 할당 */
    for(int i=0; i<row; i++) //행의 개수만큼 반복
    {
        matrix[i] = (int*)malloc(sizeof(int) * col);
        /* 행을 가리키는 포인터에 열의 크기만큼의 메모리 할당 */
    }

    if(matrix == NULL) //matrix의 값이 NULL일때(malloc으로 값을 못받았을 때)
    {
        printf("Memory Allocation Failed.\n"); //메모리 할당 실패 출력
        return NULL; //NULL값을 리턴(함수를 끝냄)
    }

    return matrix; //matrix(행을 가리키는 포인터 배열의 첫 번째 주소)를 리턴
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return; //return 명령어로 함수를 끝낸다.
    }

    for(int i=0; i<row; i++) //row만큼 반복
    {
        for(int j=0; j<col; j++) //col만큼 반복
        {
            printf("%3d ", matrix[i][j]); //2차원 배열의 원소 출력
        }
        printf("\n");
    }

    if(matrix == NULL) //matrix의 값이 NULL일 때
    //matrix값이 NULL이면 메모리 할당에서 에러가 난 것이거나 함수에 입력을 잘못한 것
    {
        printf("Memory Allocation Failed.\n"); //메모리 할당 실패 출력
        return;
    }

    return; //함수 내의 모든 명령어가 끝난뒤 리턴으로 함수를 끝냄
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }
    for(int i=0; i<row; i++) //row만큼 반복
    {
        free(matrix[i]); //행을 가리키는 포인터들에 할당된 메모리를 free시킨다.
    }
    free(matrix); //그 포인터들을 가리키는 포인터에 할당된 메모리를 free시킨다.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }
    for(int i=0; i<row; i++) //row만큼 반복
    {
        for(int j=0; j<col; j++) //col만큼 반복
        {
            matrix[i][j] = rand()%20; //2차원 배열의 원소에 0~19의 랜덤 값 할당
        }
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
    //이중포인터 matrix_sum에 행과 열이 row와 col인 행렬의 메모리의 주소 할당 

    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }

    for(int i=0; i<row; i++) //row만큼 반복
    {
        for(int j=0; j<col; j++) //col만큼 반복
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
            /* 같은 행과 열에 대응하는 원소끼리 더해서 sum행렬의 값에 할당한다. */ 
        }
    }
    print_matrix(matrix_sum, row, col); //matrix_sum 출력
    free_matrix(matrix_sum, row, col); //matrix_sum에 할당된 모든 메모리를 free시킨다.
    return 1; //1을 리턴(함수가 끝까지 돌음)
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int **matrix_sub = create_matrix(row, col);
     //이중포인터 matrix_sub에 행과 열이 row와 col인 행렬의 메모리의 주소 할당
    
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }

    for(int i=0; i<row; i++) //row만큼 반복
    {
        for(int j=0; j<col; j++) //col만큼 반복
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
            /* 같은 행과 열에 대응하는 원소끼리 빼서 sub행렬의 값에 할당한다. */
        }
    }
    print_matrix(matrix_sub, row, col); //matrix_sub 출력
    free_matrix(matrix_sub, row, col); //matrix_sub에 할당된 모든 메모리를 free시킨다.

    return 1; //1을 리턴(함수가 끝까지 돌음)
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }

    for(int i=0; i<row; i++) //row만큼 반복
    {
        for(int j=0; j<col; j++) //col만큼 반복
        {
            matrix_t[i][j] = matrix[j][i];
            /* matrix의 원소를 행과 열을 바꾼 matrix_t의 원소에 할당 */
        }
    }
    if(matrix == NULL || matrix_t == NULL) //matrix또는 matrix_t의 값이 NULL일 때
    {
        printf("Memory Allocation Failed.\n"); //메모리 할당 오류 출력
        return -1; //-1을 리턴(오류 발생)
    }
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_axt = create_matrix(row, row);
    //전치행렬과의 곱이므로 행과 열의 개수는 그 행렬의 행과 행의 개수와 같다. 
    if(row <= 0 || col <= 0) //row와 col의 값이 0보다 작거나 같으면
    {
        printf("Check the size of row and col!\n"); //입력한 값을 확인하라고 출력
        return -1; //return 명령어로 함수를 끝낸다.(-1이면 오류라고 확인 가능)
    }

	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) //row만큼 반복
    {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) //row만큼 반복
        {
			int temp = 0; //matrix_a의 행과 matrix_t의 열을 곱해서 더한 값의 합을 저장할 변수 
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
            {
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
                //temp에 matrix_a의 행의 원소와 그와 대응하는 matrix_t의 열의 원소의 곱을 더해서 저장
            }
			matrix_axt[matrix_a_row][matrix_t_row] = temp; //원소의 곱을 합한 temp의 값을 matrix_axt의 원소에 저장
		}
	}

    if(matrix_t == NULL || matrix_axt == NULL) //matrix_t또는 matrix_axt의 값이 NULL일 때
    {
        printf("Memory Allocation Failed.\n"); //메모리 할당 오류 출력
        return -1; //-1을 리턴(오류 발생)
    }

    print_matrix(matrix_axt, row, row); //matrix_axt 출력
    free_matrix(matrix_axt, row, col); //이중포인터 matrix_axt에 할당된 모든 메모리를 free시킨다.
    
    return 1; //1을 리턴(함수가 끝까지 돌음)

}
