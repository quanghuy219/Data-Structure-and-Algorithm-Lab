#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double Ex = 1;
  int n = 0;
  int factorial = 1;
  double x , temp1 = 1;
  double temp = 0;
  double eps;
  sscanf(argv[1],"%lf",&x);
 

  if (argc == 2) eps = 0.0001;
  else if(argc == 3) sscanf(argv[2],"%lf",&eps);
  else {
    printf("Wrong Syntax!!!\nSyntax: x epsilon\n");
    return 0;
  }

  do {
    temp = Ex;
    n++;
    factorial *= n;
    temp1 *= x;
    
    
    Ex +=  temp1/factorial;
    
  } while(fabs(Ex - temp) >= eps);
  printf("x = %lf\n",x);
  printf("Epsilon = %lf\n",eps);
  printf("E(%lf) = %lf\n",x,Ex);

  return 0;
}
