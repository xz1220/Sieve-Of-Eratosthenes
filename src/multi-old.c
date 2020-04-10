//关于任意两个矩阵的乘法运算
//关于任意两个矩阵的乘法运算
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define MAX 10
void matrix_multiplication(int line1, int column1, int column2, int arr1[MAX][MAX], int arr2[MAX][MAX], int arr3[MAX][MAX])
{
    int i, j, k;
    int ret;
    for (i = 0; i < line1; i++)
    {
        for (j = 0; j < column1; j++)
        {
            ret = 0;
            for (k = 0; k < column2+1; k++)
            {
                ret += arr1[i][k] * arr2[k][j];   //按照矩阵的乘法规则进行运算
            }
            arr3[i][j] = ret;
        }
    }
}
int main()
{   clock_t start = clock();
    int line1=10, column1=10, column2=10;
    int i, j;
    //int temp;
    int arr1[MAX][MAX], arr2[MAX][MAX], arr3[MAX][MAX];


    // printf("输入第一个矩阵的行数:\n");
    // scanf("%d", &line1);
    // printf("输入第一个矩阵的列数:\n");
    // scanf("%d", &column1);
    // printf("输入第一个矩阵的列数:\n");
    // scanf("%d", &column2);

    printf("输入第一个矩阵的元素(%d*%d):\n",line1,column1);
    for (i = 0; i < line1; i++)
    {
        for (j = 0; j < column1; j++)
        {
            //scanf("%d", &temp);
            arr1[i][j] = 2;
        }
    }
    printf("输入第二个矩阵的元素(%d*%d):\n", column1, column2);    //因为在这里矩阵的乘法会要求第一个的列与第二个行相等
    for (i = 0; i < column1; i++)
    {
        for (j = 0; j < column2; j++)
        {
            //scanf("%d", &temp);
            arr2[i][j] = 2;
        }
    }

    matrix_multiplication(line1, column1, column2, arr1, arr2, arr3);
    // printf("输出的两个矩阵的乘法运算的结果是：\n");
    // for (i = 0; i<line1; i++)
    // {
    //     for (j = 0; j<column2; j++)
    //         printf("%ld ", arr3[i][j]);
    //     printf("\n");
    // }

    clock_t end = clock();
    double runtime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%f\n", runtime);
    //system("pause");
    return 0;
}