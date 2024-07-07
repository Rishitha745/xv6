#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int arrGlobal[10000];

int main(){
    int arrLocal[10000]={0};
    for(int i=0;i<10000;i++){
        arrLocal[i]++;
    }
    pgtPrint();
    return 0;
}