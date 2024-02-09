#include <stdio.h>

int count = 5;
int value = 3;

int abrbbbababbbsbs()
{
    while(count > 0) {
        printf("outter loop\n");
        while(value > 0) {
            printf("inner loop ");
            value--;
        }
        count--;
    }
}

int main(){
    abrbbbababbbsbs();
}