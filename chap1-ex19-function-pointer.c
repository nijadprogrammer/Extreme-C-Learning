//Example 19 Chapter 1

#include <stdio.h>

int sum(int a, int b) {
  return a + b;
}

int subtract(int a, int b) {
  return a - b;
}

int main() {
  int (*func_ptr)(int, int);
  func_ptr = NULL;
  func_ptr = &sum;
  int result = func_ptr(5, 4);
  printf("Sum: %d\n", result);
  func_ptr = &subtract;
  result = func_ptr(5, 4);
  printf("Subtract: %d\n", result);
  return 0;
}  
