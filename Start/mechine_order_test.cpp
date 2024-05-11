#include <stdio.h>
#include <bitset>
using namespace std;

union test
{
    short a;
    char b[2];
    /* data */
    // public:
    //     test(){};
};

int main(){
    union test u;
    u.a = 0x0102;
    if(u.b[0] == 0x02 && u.b[1] == 0x01){
        printf("little end mechine/n");
    }else if(u.b[0] == 0x01 && u.b[1] == 0x02){
        printf("big end mechine/n");
    }else{
        printf("unknown mechine/n");
    }
    
}
