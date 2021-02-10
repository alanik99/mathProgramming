//Метод наискорейшего спуска

#include <iostream>
using namespace std;

double F(const double* x) //для метода наискорейшего спуска
{
    return 2*x[0]*x[0] + x[0]*x[1] + 2.1*x[1]*x[1] + 1;
}

double F(const double* x, const double* grad_x, const double h) //для метода зол. сечения
{
    double x1 = x[0] - h*grad_x[0];
    double x2 = x[1] - h*grad_x[1];

    return 2*x1*x1 + x1*x2 + 2.1*x2*x2 + 1;
}

int main()
{
    double x[] = {0.5, 1};
    double F_old = F(x);

    const double ALPHA = 0.618;
    const double e = 0.01; //точность внутреннего цикла - метода зол. сечения
    const double eps = 0.05; //точность внешнего цикла - наискорейшего спуска

    double grad_x[2], a, b, l, mu, hmin, F_new;

    int i = 0;
    bool firsttime = true;
    do
    {
        ++i;
        if(!firsttime)
            F_old = F_new;

        grad_x[0] = 4*x[0] + x[1];
        grad_x[1] = x[0] + 4.2*x[1];

        a = 0;
        b = 1;
        l = a + (1-ALPHA)*(b-a);
        mu = a + ALPHA*(b-a);

        while(b - a > e) //внутренний цикл - метод зол. сечения
        {
            if(F(x, grad_x, l) > F(x, grad_x, mu))
            {
                a = l;
                l = mu;
                mu = a + ALPHA*(b-a);
            }
            else
            {
                b = mu;
                mu = l;
                l = a + (1-ALPHA)*(b-a);
            }
        }
        hmin = a + (b-a)/2;

        x[0] = x[0] - hmin*grad_x[0];
        x[1] = x[1] - hmin*grad_x[1];

        F_new = F(x);

        firsttime = false;

        cout << "i = " << i << "\tx1 = " << x[0] << "\tx2 = " << x[1] << "\th = " << hmin << "\tF(x) = " << F_new << endl;

    } while(F_old - F_new > eps); //внешний цикл - метод наискорейшего спуска

    return 0;
}
