#include <stdlib.h>
#include <stdio.h>

int BinarySearch(int *firstPart, int *secondPart, int firstPartTarget, int secondPartTarget, int N)
{
    int right = N - 1;
    int left = 0;
    int middle;

    while(left <= right) 
    {
        middle = left + (right - left) / 2;
        if(firstPart[middle] == firstPartTarget) 
        {
            if(secondPart[middle] == secondPartTarget) 
            {
                return middle + 1;
            }
            else 
            {
                for(int i = left; i < right; i++) 
                {
                    if(firstPart[i] == firstPartTarget)
                    {
                        if(secondPart[i] == secondPartTarget)
                        {
                            return i + 1;
                        }
                    }
                }
            }
        }
        if (firstPart[middle] < firstPartTarget)
        {
            left = middle + 1;
        } 
        else 
        {
            right = middle - 1;
        }
    }
    return 0;
}

int main()
{
    int N, M;
    scanf("%d", &N);
    if (N < 1 || N > 50000) 
    {
        return 1;
    }

    int *firstArray = (int *)malloc(N * sizeof(int));
    int *secondArray = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &firstArray[i]);
        secondArray[i] = 0;
        char peek = getchar();
        if (peek == ',') 
        {
            scanf("%d", &secondArray[i]);
            while(secondArray[i] % 10 == 0 && secondArray[i] != 0) 
            {
                secondArray[i] = secondArray[i] / 10;
            }
        }
    }

    scanf("%d", &M);
    if (M < 1 || M > 100000) 
    {
        return 1;
    }

    int firstTarget;
    int secondTarget;
    for (int j = 0; j < M; j++)
    {
        scanf("%d", &firstTarget);
        secondTarget = 0;
        char peek = getchar();
        if (peek == ',') 
        {
            scanf("%d", &secondTarget);
            while(secondTarget % 10 == 0 && secondTarget != 0) 
            {
                secondTarget = secondTarget / 10;
            }
        }
        int result = BinarySearch(firstArray, secondArray, firstTarget, secondTarget, N);
        printf("%d", result);
        if(j < M-1) 
        {
            printf("\n");
        }
    }

    free(firstArray);
    free(secondArray);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>

// typedef struct {
//     long whole_part;
//     long decimal_part;
//     int sign; // 1 for positive and -1 for negative
// } DECIMAL_NUMBER;

// int compare_decimals(const DECIMAL_NUMBER *num1, const DECIMAL_NUMBER *num2);
// void convert_decimals(char *inputStr, DECIMAL_NUMBER *decimal);
// int binary_search(DECIMAL_NUMBER array[], int left, int right, DECIMAL_NUMBER target);

// int main() 
// {
//     int N, M;

//     do {
//         scanf("%d", &N);
//     } while(N < 1 || N > 50000);

//     DECIMAL_NUMBER *sequence = (DECIMAL_NUMBER *)malloc(N * sizeof(DECIMAL_NUMBER));
    
//     char buffer[64];
//     for (int i = 0; i < N; i++) 
//     {
//         scanf("%s", buffer);
//         convert_decimals(buffer, &sequence[i]);
//     }

//     do {
//         scanf("%d", &M);
//     } while(M < 1 || M > 100000);

//     int *results = (int *)malloc(M * sizeof(int));
//     for (int i = 0; i < M; i++) 
//     {
//         scanf("%s", buffer);
//         DECIMAL_NUMBER tmp_decimal;
//         convert_decimals(buffer, &tmp_decimal);
//         results[i] = binary_search(sequence, 0, N - 1, tmp_decimal);
//     }

//     for (int i = 0; i < M; i++) 
//     {
//         if (i < M - 1)
//             printf("%d\n", results[i]);
//         else
//             printf("%d", results[i]); // No new line after the last result
//     }


//     free(results);    
//     free(sequence);
    
//     return 0;
// }

// int compare_decimals(const DECIMAL_NUMBER *num1, const DECIMAL_NUMBER *num2) 
// {
//     if (num1->sign != num2->sign) 
//     {
//         return num1->sign - num2->sign;
//     }
//     else
//     {
//         int signFactor = num1->sign; // Same sign
//         if (num1->whole_part != num2->whole_part) 
//         {
//             return (num1->whole_part - num2->whole_part) * signFactor;
//         }
//         else
//         {
//             return (num1->decimal_part - num2->decimal_part) * signFactor;
//         }
//     }
// }

// void convert_decimals(char *inputStr, DECIMAL_NUMBER *decimal) 
// {
//     decimal->whole_part = 0;
//     decimal->decimal_part = 0;
//     decimal->sign = 1; // Assume positive initially

//     char *ptr = inputStr;
//     if (*ptr == '-') {
//         decimal->sign = -1;
//         ++ptr; // Skip the minus sign for processing numbers
//     }

//     long current_number = 0;
//     int is_decimal_part = 0; // Flag to track if we are on the decimal part

//     for (; *ptr; ++ptr) {
//         if (*ptr == ',') {
//             is_decimal_part = 1;
//             decimal->whole_part = current_number * decimal->sign; // Apply sign
//             current_number = 0; // Reset for decimal part
//             continue;
//         }

//         if (*ptr >= '0' && *ptr <= '9') {
//             current_number = current_number * 10 + (*ptr - '0');
//         }
//     }

//     if (is_decimal_part) {
//         decimal->decimal_part = current_number; // No sign for decimal part
//         // Adjust for trailing zeros if necessary
//         while (decimal->decimal_part % 10 == 0 && decimal->decimal_part != 0) {
//             decimal->decimal_part /= 10;
//         }
//     } else {
//         decimal->whole_part = current_number * decimal->sign; // Apply sign if no decimal part
//     }
// }

// int binary_search(DECIMAL_NUMBER array[], int left, int right, DECIMAL_NUMBER target) 
// {
//     while (left <= right) 
//     {
//         int mid_point = left + (right - left) / 2;
//         int comparison = compare_decimals(&array[mid_point], &target);
//         if (comparison == 0) 
//         {
//             return mid_point + 1; // We count from 1 and not from 0
//         }
//         if (comparison < 0) 
//         {
//             left = mid_point + 1;
//         }
//         else 
//         {
//             right = mid_point - 1;
//         }
//     }
//     return 0; // When not found
// }
