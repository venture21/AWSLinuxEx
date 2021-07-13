#include <dirent.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 

// 현재경로를 가리키는 path
// 
const char *path = "/home/park/blackbox/"; 


/* ".", ".." 은 빼고 나머지 파일명 출력하는 필터 함수 */
static int filter(const struct dirent *dirent)
{
  if(!(strcmp(dirent->d_name, ".")) ||
     !(strcmp(dirent->d_name, ".."))){
     /* 현재 디렉토리, 이전 디렉토리 표시는 출력안함 */
   }else{
    printf("   %s() : %s\n", __FUNCTION__, dirent->d_name);
   }
}


int main(void) 
{ 
    struct dirent **namelist; 
    int count; 
    int idx; 
    
    // 1st : 내가 탐색하고자 하는 폴더
    // 2nd : namelist를 받아올 구조체 주소값
    // 3rd : filter
    // 4th : 알파벳 정렬
    // scandir()함수에서 namelist 메모리를 malloc
    if((count = scandir(path, &namelist, *filter, alphasort)) == -1) 
    { 
        fprintf(stderr, "%s Directory Scan Error: %s\n", path, strerror(errno)); 
        return 1; 
    } 
    printf("count=%d\n",count);    

    for(idx = 0; idx < count; idx++) 
    { 
        printf("%s\n", namelist[idx]->d_name); 
    } 
    
    // 건별 데이터 메모리 해제 
    for(idx = 0; idx < count; idx++) 
    { 
        free(namelist[idx]); 
    } 
    
    // namelist에 대한 메모리 해제 
    free(namelist); 
    
    return 0; 
}

