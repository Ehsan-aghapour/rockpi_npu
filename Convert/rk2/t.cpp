#include <stdio.h>

int main(void)
{
  float a[10];

  printf("sizeof float %d\n", sizeof(float) );
  printf("sizeof array %d\n", sizeof(a) );
  printf("array size %d\n", sizeof(a)/sizeof(a[0]) ); // sizeof(a[0]) is the same with sizeof(float)
  return 0;
}
