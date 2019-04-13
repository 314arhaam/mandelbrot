#include <cmath>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
/*
                    Calculating Mandelbort fractal in C
  ________________________________________________***________________________
  _____________________________________________***___________________________
  _____________________________________________******________________________
  _______________________________________***************_____________________
  ____________________________________*********************__________________
  _________________________________***!!!!!!!!!!!!!!!******__________________
  _____________________******______!!!!!!!!!!!!!!!!!!!!!******_______________
  _____________________!!!!!!!!!***!!!!!!!!!!!!!!!!!!!!!***__________________
  *********************!!!!!!!!!***!!!!!!!!!!!!!!!!!!!!!!!!__________________
  _____________________!!!!!!!!!***!!!!!!!!!!!!!!!!!!!!!***__________________
  _____________________******______!!!!!!!!!!!!!!!!!!!!!******_______________
  _________________________________***!!!!!!!!!!!!!!!******__________________
  ____________________________________*********************__________________
  _______________________________________***************_____________________
  _____________________________________________******________________________
  _____________________________________________***___________________________
  ________________________________________________***________________________
*/
double cabs(double real, double imag){
  // Absolute value of complex number real + imag*j
  return (real*real + imag*imag);
}
int mandelbort(double x, double y){
  /*
  Latex:
  z_{n+1} = z_{n}^{2} + c
  c is a complex number
  c is in Mandelbort if \lim_{n\to\infty} z_{n} < 2
  */
  double a=x, b=y, temp=0;
  int n = 0, MAX_ITER = 500;  // MAX_ITER works as +inf for convergence check.
  if ( cabs(a+0.245,b) <= 0.25 || cabs(a+1,b) <= 0.24*0.24){
    /*
    checks if the c is in main central area of fractal, passes the maximum value so it will not be processed and boosts the code.
    NOTE This area is represented using ! in terminal-based fractal above.
    */
    return MAX_ITER;
  }
  while (n < MAX_ITER && cabs(a, b) < 4){
    temp = a;                 // arbitary variable
    a = a * a - b * b + x;    // complex multiply, real part
    b = temp * b * 2 + y;     // complex multiply, imaginary part
    n++;
  }
  return n;
}
/*
Typical coordinate system in picture plane: NOTE values are arbitary
_______________________________________
|-4  -3  -2  -1  0  1  2  3  4 -> [X] |
_________________1______***____________
_________________2______***____________
_________________3************_________
____________***__4!!!!!!!!!***_________
************!!!**5!!!!!!!!!!!!_________
____________***__6!!!!!!!!!***_________
_________________7************_________
_________________|______***____________
_________________v______***____________
________________[Y]____________________
Each value inside the plane is represented by a complex number, c = x + yj
*/
int mandeldraw(double y){
  double x = y*3/2, a = 0, b = 0;
  int res = 0;
  FILE* output_file;
  output_file = fopen("res1.txt","w");
  for (int y_pixel = 0; y_pixel < y/2 + 1; y_pixel++){  // sweep the y axis
    system("clear");  // NOTE system("CLS") for Windows
    printf("Progress: %.2f %% \n", 200*y_pixel/y); // logging (Optional)
    for (int x_pixel = 0; x_pixel < x; x_pixel++){      // sweep the axis
      a = 2*(x_pixel-2*x/3)/y;  // convert pixel counters to complex number (Re)
      b = 2*(y/2-y_pixel)/y;    // convert pixel counters to complex number (Im)
      res = mandelbort(a, b);   // mandelbort function output stores here.
      fprintf(output_file, "%d ", res);
    }
  }
  fclose(output_file);
  return 0;
}
int main(){
  // lines with /*  Clock Line n */ appeared at first, could be used with "ctime" library, anywhere WITH THE SAME ORDER
  /*  Clock Line 1 */clock_t begin = clock();
  mandeldraw(4000);
  /*  Clock Line 2 */clock_t end = clock();
  /*  Clock Line 3 */double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("elapsed time: %f (s)\n", time_spent);
  return 0;
}
//  non-pointer based performance
//    CPU: Intel Core i5 1.8 GHz
//************************************
// 16000: elapsed time: 120.330728 (s)
// 8000 : elapsed time:  30.975784 (s)
// 4000 : elapsed time:   8.097667 (s)
// 2000 : elapsed time:   2.211209 (s)
// 1000 : elapsed time:   0.689788 (s)
// 500  : elapsed time:   0.224861 (s)
