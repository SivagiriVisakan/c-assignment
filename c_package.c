//Brackets are not allowed and Function division is not allowed
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

#include<gtk/gtk.h>

//Declaration
void input();
void evaluation(char *str);
void coefficient_input();
int number_of_digits(int a);
void side_separation(char*s);
char * rem_space(char *s);
void input_conversion_left(char *s);
void input_conversion_right(char *s);
double complex poly(int , double complex);
double complex * polyroot(int );
void factorize(char *str);
float two_variablesolve(float a1,float b1,float a2,float b2,char var1,char var2);
void solve_2_equations();
void solve_3_equations();
void findSolution(double coeff[3][4]);
double determinantOfMatrix(double mat[3][3]);

char * complex_to_string(double complex number);
void compute_factors(GtkWidget *widget, GtkWidget *text);
void print_to_label(GtkWidget *label, char *string, int clear_before_printing);
void reset_all();


//Global variable
int degree=1;
char s_left[100]={0},s_right[100]={0};
float coefficient_arr[26][100]={0},temp=0;
float coefficient_input_arr[100]={0};
float coefficient_arr1[26][100]={0};
float coefficient_arr2[26][100]={0};
float coefficient_arr3[26][100]={0};
double con=0,con1=0,con2=0,con3=0;


char output_string[500];
// The label in which the factors are shown
GtkWidget *factors_output_label;

//Function for removing all the blank spaces in the input
char * append(char *a,int number,int digit)
{
    char b[10];
    char c[100];
    int p=0,r=0,i=0;
    int t=0;
    int x,g,s,n,o;
    if(number==1)
    {
        b[0]='^';
        b[1]='1';
        b[2]=0;
    }
    else
    {
        b[0]='1';
        b[1]=0;
    }
    p=digit;
    r = strlen(a);
    n = strlen(b);
    i=0;

    // Copying the input string into another array
    while(i <= r)
    {
        c[i]=a[i];
        i++;
    }
    s = n+r;
    o = p+n;

    // Adding the sub-string
    for(i=p;i<s;i++)
    {
        x = c[i];
        if(t<n)
        {
            a[i] = b[t];
            t=t+1;
        }
        a[o]=x;
        o=o+1;
    }
    return a;
    }
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
    for(i=0; s[i]; i++)
    {
        if(s[i]>='a'&&s[i]<='z')
        {
            if(i>0)
            {
                if(!(s[i-1]>='0'&&s[i-1]<='9'))
                {
                    s=append(s,2,i);
                }
            }
            else
            {
                s=append(s,2,i);
            }
        }
    }
     for(i=0; s[i]; i++)
    {
        if(s[i]>='a'&&s[i]<='z')
        {
            if(s[i+1]!='^')
            {
                s=append(s,1,i+1);
            }
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
    g_print("Enter the input\n");
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
void evaluation(char *str)
{
    int coefficient=0;
    char *s;
    s=rem_space(str);
    side_separation(s);
    input_conversion_left(s_left);
    input_conversion_right(s_right);

    degree_function();
    coefficient_input();
}
void factorize(char *str)
{
    evaluation(str);
    double complex * factors = polyroot(degree);
    
    //A temporary placeholder for strings that are printed to GTK window.
    char string_to_print[50];
    //Print out the evaluated equation
    sprintf(string_to_print, "The given equation is : \n\n\0");
    print_to_label(factors_output_label,string_to_print,0);

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                g_print("%+.2f%c^%d ",coefficient_arr[i][j],i+'a',j);
                
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr[i][j],i+'a',j);
                print_to_label(factors_output_label,string_to_print,0);
            }
        }
    }
    g_print("%+.2f = 0",con);
    sprintf(string_to_print, "%+.2f = 0",con);
    print_to_label(factors_output_label,string_to_print,0);
    
    print_to_label(factors_output_label,"\n\nThe roots are : ", 0);
    for(int i=0;i<degree;i++)
    {
        g_print(complex_to_string(factors[i]));

        sprintf(string_to_print, "\n%s", complex_to_string(factors[i]));
        print_to_label(factors_output_label, string_to_print, 0);

        //g_print("\n%lf  %lf\n",creal(factors[i]),cimag(factors[i]));
    }
}


void show_factorize_screen(GtkWidget *widget, GtkApplication *app)
{
    // The window that contains all the widgets.
    GtkWidget *window;

    // A button with the label "Factorize" that calculates fators when clicked
    GtkWidget *factorize_button;

    // The grid in which all the widgets are placed
    GtkWidget *grid;

    // A GtkEntry which will act as an input for equation
    GtkWidget *equation_textbox;

    // A label with the text "Enter an equation to factorize"
    GtkWidget *enter_eqn_label;

    // A label to show the factors after calculating.
    GtkWidget *factors_label;

    // Initialize and configure UI
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Factoize - EQNS");

    // When a window is set to modal it prevents interaction witb other windows.
    gtk_window_set_modal(GTK_WINDOW (window), TRUE);
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

    equation_textbox = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox), 500, 20);

    factorize_button = gtk_button_new_with_label ("Factorize");
    
    g_signal_connect (factorize_button, "clicked", G_CALLBACK (compute_factors), equation_textbox);
    gtk_widget_set_size_request(GTK_WIDGET(factorize_button), 10, 30);

    enter_eqn_label = gtk_label_new("Enter an equation to factorize : ");

    factors_label = gtk_label_new("\n\n  Factors:\n ");

    grid = gtk_grid_new();
    
    gtk_widget_set_hexpand (factorize_button, TRUE);
    gtk_widget_set_halign (factorize_button, GTK_ALIGN_CENTER);
    
    gtk_widget_set_hexpand (equation_textbox, TRUE);
    gtk_widget_set_halign (equation_textbox, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand (factors_label, FALSE);
    gtk_widget_set_halign (factors_label, GTK_ALIGN_START);


    gtk_grid_attach(GTK_GRID(grid), enter_eqn_label, 0, 0, 10, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox, enter_eqn_label, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), factorize_button, equation_textbox, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), factors_label, enter_eqn_label, GTK_POS_BOTTOM, 15, 20);

    gtk_grid_attach_next_to(GTK_GRID(grid), factors_output_label, factors_label, GTK_POS_BOTTOM, 15, 20);

    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_widget_show_all (window);
}


void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    GtkWidget *text;

    // Initialize this global variable here with empty text
    factors_output_label = gtk_label_new(NULL);

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    button_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    text = gtk_entry_new();

    button = gtk_button_new_with_label ("Hello World");
    //g_signal_connect (button, "clicked", G_CALLBACK (print_hello), text);
    g_signal_connect (button, "clicked", G_CALLBACK (show_factorize_screen), app);
    //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_widget_set_size_request (GTK_WIDGET(button), 100, 50);
    gtk_container_add (GTK_CONTAINER (button_box), button);


    gtk_entry_set_placeholder_text(GTK_ENTRY(text), "Enter the equation !");
    gtk_container_add(GTK_CONTAINER(button_box), text);

    gtk_widget_show_all (window);
}




int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
    // Initializing this here as it can be initialized only once.

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;

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
                g_print("%f %c ^ %d ",coefficient_arr1[i][j],i+'a',j);
        }
    }
    g_print("%f\n",con1);
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
                g_print("%f %c ^ %d ",coefficient_arr[i][j],i+'a',j);
        }
    }
    g_print("%f\n",con);
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
    g_print("\n%f %f",a1,a2);
    g_print("\n %f %f",b1,b2);
    g_print("%f %f",con1,con2);
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
                g_print("Infinitely many solutions\n");
            }
            else
            {
                g_print("No Solution\n");
            }
        }
    }
    g_print("\n%c=%f\t%c=%f\n",var1+'a',x,var2+'a',y);
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
        g_print("Value of x is : %lf\n", x); 
        g_print("Value of y is : %lf\n", y); 
        g_print("Value of z is : %lf\n", z); 
    } 
    // Case 2 
    else { 
        if (D1 == 0 && D2 == 0 && D3 == 0) 
            g_print("Infinite solutions\n"); 
        else if (D1 != 0 || D2 != 0 || D3 != 0) 
            g_print("No solutions\n"); 
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
                g_print("\n%f %c ^ %d ",coefficient_arr1[i][j],i+'a',j);
        }
    }
    g_print("%f\n",con1);
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
                g_print("\n%f %c ^ %d ",coefficient_arr2[i][j],i+'a',j);
        }
    }
    g_print("%f\n",con2);
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
                g_print("\n%f %c ^ %d ",coefficient_arr3[i][j],i+'a',j);
        }
    }
    g_print("%f\n",con3);
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
    g_print("\n%f %f %f",a1,a2,a3);
    g_print("\n %f %f %f",b1,b2,b3);
    g_print("\n %f %f %f",c1,c2,c3);
    g_print("\n%f %f %f\n",con1,con2,con3);
    double coeff[3][4] = { 
        { a1,b1,c1,-1*con1}, 
        { a2,b2,c2,-1*con2}, 
        { a3,b3,c3,-1*con3}, 
    }; 

    findSolution(coeff); 
} 


static void print_hello (GtkWidget *widget, GtkWidget *text)
{
    const gchar *value;
    value = gtk_entry_get_text(GTK_ENTRY(text));
    g_print ("Hello World\n");
    g_print(value);

    char s[50];
    strcpy(s, value);
    g_print("%s", s);
}

void compute_factors(GtkWidget *widget, GtkWidget *text)
{
    const gchar *equation;
    equation = gtk_entry_get_text(GTK_ENTRY(text));
    g_print ("\n-----\n");
    g_print(equation);
    print_to_label(factors_output_label, "", 1);

    char s[50];
    strcpy(s, equation);
    g_print("\n\n%s\n\n", s);

    factorize(s);
    reset_all();
}

void print_to_label(GtkWidget *label, char *string, int clear_before_printing)
{
    if(clear_before_printing) 
    {
        gtk_label_set_text(GTK_LABEL(factors_output_label), string);
    }
    else
    {
        char existing_output[500];
        g_print(string);
        strcpy(existing_output, gtk_label_get_text(GTK_LABEL(factors_output_label)));
        gtk_label_set_text(GTK_LABEL(factors_output_label), strcat(existing_output, string));
    }
}

void reset_all()
{
    /*Clearing all the global variables*/
    degree=1;
    temp=0;
    con=0;con1=0;con2=0;con3=0;
    for(int i = 0; i < 100; i++)
    {
        s_left[i] = s_right[i] = coefficient_input_arr[i] = 0;
    }

    for(int i = 0; i < 26; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            coefficient_arr[i][j]=0;
            coefficient_arr1[i][j]=0;
            coefficient_arr2[i][j]=0;
            coefficient_arr3[i][j]=0;
        }
    }
}

/*
Function to get the printable representation of a complex number.
*/
char *complex_to_string(double complex number)
{
    //static as we are returning this to the calling function
    static char string[15];
    double real = creal(number);
    double imaginary = cimag(number);

    if(fabs(imaginary) < (double) 0.001)
    {
        sprintf(string, "%.2lf", real);
    }
    else if(fabs(real) < (double) 0.001)
    {
        sprintf(string, "%.2lfi", imaginary);
    }
    else
    {
        sprintf(string, "%.2lf%+.2lfi", real, imaginary);
    }

    return string;
}
