#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX_LIST 50 

long unsigned int searchOldFolder(void)
{
    
    // 숫자를 비교할 배열의 갯수를 MAX_LIST
    long unsigned int num[MAX_LIST] ={2021071321,2021071322,2021071323,2021071324,2021071401,NULL};
    int i;
    long unsigned int min;
    min = num[0];     //min 초기화

    // 배열의 들어있는 값을 출력
    for(i=0;i<MAX_LIST;i++)
    {
        if(num[i]==NULL)
            break;
        printf("%d 번째 배열 요소 . . . . . . %d \n",i+1, num[i]);
    }

    for(i = 0;i<MAX_LIST;i++)
    {
        if(num[i]==NULL)
            break;    
        else
            if(num[i] < min ) //num[i]가 min보다 작다면
                min = num[i]; //min 에는 num[i]의 값이 들어감
    }

    return min;

}

int main(void)
{
    long unsigned int result; 
    char folderName[30];
    result = searchOldFolder();
    sprintf(folderName,"%d",result);
    printf("가장 오래된 폴더는 %s 이다.\n",folderName);
}

