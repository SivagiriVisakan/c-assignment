//Input format for x input as x^1.
//Brackets are not allowed and Function division is not allowed
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <complex.h>
//Declaration
void input();
void evaluation();
void coefficient_input();
int number_of_digits(int a);
void side_separation(char*s);
char * rem_space(char *s);
void input_conversion_left(char *s);
void input_conversion_right(char *s);
double complex poly(int , double complex);
double complex * polyroot(int );
void factorize();
float two_variablesolve(float a1,float b1,float a2,float b2,char var1,char var2);
void solve_2_equations();
void solve_3_equations();
void findSolution(double coeff[3][4]);
double determinantOfMatrix(double mat[3][3]);
//Global variable
int degree=1;
char s_left[100]={0},s_right[100]={0};
float coefficient_arr[26][100]={0},temp=0;
float coefficient_input_arr[100]={0};
float coefficient_arr1[26][100]={0};
float coefficient_arr2[26][100]={0};
float coefficient_arr3[26][100]={0};
double con=0,con1=0,con2=0,con3=0;
//Function for removing all the blank spaces in the input
char * rem_space(char *s)
{
    int i,j, len=strlen(s);
	for(i=0; i<len; i++)
	{
	    if(s[i]==' '&&s[i+1]!='=')
		{
			for(j=i; j<len; j++)
			{
				s[j]=s[j+1];
			}
		len--;
		}
	}

    return (s);
}
//Function for separating the left sid eand right side with some changes
void side_separation(char*s)
{
    int i,j=0;
    for(i=0;s[i]!='=';i++)
    {
        s_left[i]=s[i];
    }
    s_left[i]=' ';//There should me a space bar before the end for certain uses
    s_left[i+1]=0;
    for(i=i+1;s[i];i++,j++)
    {
        s_right[j]=s[i];
    }
    s_right[i]=' ';//There should me a space bar before the end for certain uses
    s_right[i+1]=0;
}
//Function for calculating the number of digits
int number_of_digits(int a)
{
    int count = 0;
    while(a != 0)
    {
        a /= 10;
        ++count;
    }
    return count;
}
//Function for converting the user defined input as arrays for calculations
void input_conversion_left(char *s)
{
    int coefficient=0;
    for(int i=0;s[i];i=i+2)
        {
            if(s[i-1]=='-'&&i>0)
                coefficient=-1*atoi(s+i);
            else
                coefficient=atoi(s+i);
            i=i-1+number_of_digits(coefficient);
            if(s[i+1]>='a'&&s[i+1]<='z')
			{
                if(s[i+2]=='^')
                    {
                            coefficient_arr[s[i+1]-'a'][s[i+3]-'0']+=coefficient;i+=3;
					}
            }
            else
            {
                con+=coefficient;
            }
        }
}
//This right side is subtracted with left side
void input_conversion_right(char *s)
{
    int coefficient=0;
    for(int i=0;s[i];i=i+2)
        {
            if(s[i-1]=='-'&&i>0)
                coefficient=-1*atoi(s+i);
            else
                coefficient=atoi(s+i);
            i=i-1+number_of_digits(coefficient);
            if(s[i+1]>='a'&&s[i+1]<='z')
			{
                if(s[i+2]=='^')
                    {
                            coefficient_arr[s[i+1]-'a'][s[i+3]-'0']+=-1*coefficient;i+=3;
					}
            }
             else
            {
                con+=-1*coefficient;
            }
        }
}
//The input is now ax^n+bx^n-1.........+c=0
void input()
{
    char str[100]; /*Take string as input*/
    char *s;
    printf("Enter the input\n");
    if(temp==0)
    scanf("%[^\n]s",str);
    else
    scanf("%*c%[^\n]s",str);
    int coefficient=0;
    s=rem_space(str);
    side_separation(s);
    input_conversion_left(s_left);
    input_conversion_right(s_right);
    temp++;
}
//Function for identifing The degree and the powers present
void degree_function()
{
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                if(j>degree)
                degree=j;
            }
        }
    }
 }
//function for finding the coefficients of the inputs
void coefficient_input()
{
    int j,var_iable=0;
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<=degree;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                var_iable=i;
            }
        }
    }
    int m=0,k;
    k=coefficient_arr[var_iable][degree];
    for(int i=degree-1;i!=0;i--,m++)
    {

        coefficient_input_arr[m]=coefficient_arr[var_iable][i];
        coefficient_input_arr[m]/=k;
    }
    coefficient_input_arr[degree-1]=con;
    coefficient_input_arr[degree-1]/=k;
}
//Function for evaluation of factors
// "poly" evaluates at x a polynomial of the form:
// f(x) = cpow(x, n) + a1*cpow(x, n - 1) + a2*cpow(x, n - 2) + . . . + a(n - 2)*x*x + a(n - 1)*x + a(n)
// where the vector A = {a1, a2, a3, . . . , a(n - 2), a(n - 1), a(n)}
double complex poly(int degree, double complex x)
{
    double complex y = cpow(x, degree);
    for (int i = 0; i < degree; i++)
        y += coefficient_input_arr[i]*cpow(x, (degree - i - 1) );
    return y;
}

// polyroot uses the Durand-Kerner method to find all roots (real and complex) of a polynomial of the form:
// f(x) = cpow(x, n) + a1*cpow(x, n - 1) + a2*cpow(x, n - 2) + . . . + a(n - 2)*x*x + a(n - 1)*x + a(n)
// where the vector A = {a1, a2, a3, . . . , a(n - 2), a(n - 1), a(n)}
double complex * polyroot(int degree)
{
    int iterations = 1000;
    double complex z = 0.4+ 0.9*I;
    int size = sizeof(z);
    double complex * R;
    R = (double complex *) malloc(size*degree);
    for (int i = 0; i < degree; i++)
        R[i] = cpow(z, i);
    for (int i = 0; i < iterations; i++)
    {
        for (int j = 0; j < degree; j ++)
        {
            double complex B = poly(degree, R[j]);
            for (int k = 0; k < degree; k++)
            {
                if (k != j)
                B /= R[j] - R[k];
            }
            R[j] -= B;
        }
    }
    return R;
}
//function for evaluation
void evaluation()
{
    input();
    degree_function();
    coefficient_input();
}
void factorize()
{
    evaluation();
    double complex * factors = polyroot(degree);
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr[i][j]!=0)
                printf("%f %c ^ %d ",coefficient_arr[i][j],i+'a',j);
        }
    }
    printf("%f",con);
    for(int i=0;i<degree;i++)
    {
        printf("\n%lf  %lf\n",creal(factors[i]),cimag(factors[i]));
    }
}
void main()
{
    solve_3_equations();
}

void solve_2_equations()
{
    float a1,b1,a2,b2;
    int var1=0,var2=0;
    input();
    con1=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr1[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr1[i][j]!=0)
                printf("%f %c ^ %d ",coefficient_arr1[i][j],i+'a',j);
        }
    }
    printf("%f\n",con1);
    input(); 
    con2=con;
    for(int i=0;i<26;i++)
    {
        coefficient_arr2[i][1]=coefficient_arr[i][1];
    }
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr[i][j]!=0)
                printf("%f %c ^ %d ",coefficient_arr[i][j],i+'a',j);
        }
    }
    printf("%f\n",con);
    for(int i=0,j=0;i<26;i++)
    {
        if(j==0)
        {
            if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0)
            {
                a1=coefficient_arr1[i][1];
                a2=coefficient_arr2[i][1];j=1;var1=i;
                continue ;
            }
        }
        if(j==1)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0)
            {
                b1=coefficient_arr1[i][1];
                b2=coefficient_arr2[i][1];var2=i;
            }
        }
    }
    printf("\n%f %f",a1,a2);
    printf("\n %f %f",b1,b2);
    printf("%f %f",con1,con2);
    two_variablesolve(a1,b1,a2,b2,var1,var2);
    
}
float two_variablesolve(float a1,float b1,float a2,float b2,char var1,char var2)
{
    float x=0,y=0;
    if((a1*b2 - a2*b1))
    {
        x = (b1*con2 - b2*con1) / (a1*b2 - a2*b1);
        y = (con1*a2 - con2*a1) / (a1*b2 - a2*b1);
    }
    else
    {
        if((a1*b2 - a2*b1)==0)
        {
            if((b1*con2 - b2*con1)==0&&(con1*a2 - con2*a1)==0)
            {
                printf("Infinitely many solutions\n");
            }
            else
            {
                printf("No Solution\n");
            }
        }
    }
    printf("\n%c=%f\t%c=%f\n",var1+'a',x,var2+'a',y);
    return 0;
}

// This functions finds the determinant of Matrix 
double determinantOfMatrix(double mat[3][3]) 
{ 
    double ans; 
    ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) 
          - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) 
          + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]); 
    return ans; 
} 
  
// This function finds the solution of system of 
// linear equations using cramer's rule 
void findSolution(double coeff[3][4]) 
{ 
    // Matrix d using coeff as given in cramer's rule 
    double d[3][3] = { 
        { coeff[0][0], coeff[0][1], coeff[0][2] }, 
        { coeff[1][0], coeff[1][1], coeff[1][2] }, 
        { coeff[2][0], coeff[2][1], coeff[2][2] }, 
    }; 
    // Matrix d1 using coeff as given in cramer's rule 
    double d1[3][3] = { 
        { coeff[0][3], coeff[0][1], coeff[0][2] }, 
        { coeff[1][3], coeff[1][1], coeff[1][2] }, 
        { coeff[2][3], coeff[2][1], coeff[2][2] }, 
    }; 
    // Matrix d2 using coeff as given in cramer's rule 
    double d2[3][3] = { 
        { coeff[0][0], coeff[0][3], coeff[0][2] }, 
        { coeff[1][0], coeff[1][3], coeff[1][2] }, 
        { coeff[2][0], coeff[2][3], coeff[2][2] }, 
    }; 
    // Matrix d3 using coeff as given in cramer's rule 
    double d3[3][3] = { 
        { coeff[0][0], coeff[0][1], coeff[0][3] }, 
        { coeff[1][0], coeff[1][1], coeff[1][3] }, 
        { coeff[2][0], coeff[2][1], coeff[2][3] }, 
    }; 
  
    // Calculating Determinant of Matrices d, d1, d2, d3 
    double D = determinantOfMatrix(d); 
    double D1 = determinantOfMatrix(d1); 
    double D2 = determinantOfMatrix(d2); 
    double D3 = determinantOfMatrix(d3); 
  
    // Case 1 
    if (D != 0) { 
        // Coeff have a unique solution. Apply Cramer's Rule 
        double x = D1 / D; 
        double y = D2 / D; 
        double z = D3 / D; // calculating z using cramer's rule 
        printf("Value of x is : %lf\n", x); 
        printf("Value of y is : %lf\n", y); 
        printf("Value of z is : %lf\n", z); 
    } 
    // Case 2 
    else { 
        if (D1 == 0 && D2 == 0 && D3 == 0) 
            printf("Infinite solutions\n"); 
        else if (D1 != 0 || D2 != 0 || D3 != 0) 
            printf("No solutions\n"); 
    } 
} 
void solve_3_equations()
{ 
    float a1,b1,a2,b2,a3,b3,c1,c2,c3;
    int var1=0,var2=0,var3=0;
    input();
    con1=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr1[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr1[i][j]!=0)
                printf("\n%f %c ^ %d ",coefficient_arr1[i][j],i+'a',j);
        }
    }
    printf("%f\n",con1);
    input(); 
    con2=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr2[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr2[i][j]!=0)
                printf("\n%f %c ^ %d ",coefficient_arr2[i][j],i+'a',j);
        }
    }
    printf("%f\n",con2);
    input(); 
    con3=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr3[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }
    //test
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr3[i][j]!=0)
                printf("\n%f %c ^ %d ",coefficient_arr3[i][j],i+'a',j);
        }
    }
    printf("%f\n",con3);
    for(int i=0,j=0;i<26;i++)
    {
        if(j==0)
        {
            if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                a1=coefficient_arr1[i][1];
                a2=coefficient_arr2[i][1];
                a3=coefficient_arr3[i][1];
                j=1;var1=i;
                continue ;
            }
        }
        if(j==1)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                b1=coefficient_arr1[i][1];
                b2=coefficient_arr2[i][1];
                b3=coefficient_arr3[i][1];
                var2=i;j=2;
                continue ;
            }
        }
        if(j==2)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                c1=coefficient_arr1[i][1];
                c2=coefficient_arr2[i][1];
                c3=coefficient_arr3[i][1];
                var3=i;j=2;
                continue ;
            }
        }
    }
    printf("\n%f %f %f",a1,a2,a3);
    printf("\n %f %f %f",b1,b2,b3);
    printf("\n %f %f %f",c1,c2,c3);
    printf("\n%f %f %f\n",con1,con2,con3);
    double coeff[3][4] = { 
        { a1,b1,c1,-1*con1}, 
        { a2,b2,c2,-1*con2}, 
        { a3,b3,c3,-1*con3}, 
    }; 

    findSolution(coeff); 
} 
