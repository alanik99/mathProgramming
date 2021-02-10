//динамическое программирование

#include <iostream>
using namespace std;

const int N = 5;
const int zm = N-1;

int indexOfMax;

double g_x[zm][N] =
{
    {0, 0.20, 0.25, 0.40, 0.60}, // g1_x1
    {0, 0.15, 0.30, 0.45, 0.55}, // g2_x2
    {0, 0.10, 0.30, 0.55, 0.70}, // g3_x3
    {0, 0.22, 0.40, 0.50, 0.60}  // g4_x4
},

v[zm][N], x[zm][N], forv[N];

double max(const double* arr, const int lim) //ищет макс. элемент массива до определенного элемента под номером lim
{
    double max = arr[0];
    indexOfMax = 0;

    for(int i = 1; i < lim; ++i)
        if(arr[i] > max)
        {
            max = arr[i];
            indexOfMax = i;
        }
    return max;
}

int main()
{
    v[0][0] = g_x[0][0]; // заполнение v1, x1
    x[0][0] = 0;
    cout << "\nv1(0) = max( "<< g_x[0][0]  << " ) = " << v[0][0]  << ";\tx1(0) = " << x[0][0];

    double maximum;
    for(int j = 1; j < N; ++j)
    {
        maximum = max(g_x[0], j+1);
        v[0][j] = maximum;
        x[0][j] = indexOfMax;

        cout << "\n\nv1(" << j << ") = max(  ";
        for(int k = 0; k < j+1; ++k)
            cout << g_x[0][k] << "  ";
        cout << ") = " << maximum << ";\tx1(" << j << ") = " << x[0][j];
    }


    for(int i = 1; i < zm; ++i) // заполнение   v2, x2;   v3, x3;   v4, x4;
    {
        v[i][0] = g_x[i][0] + v[i-1][0];
        x[i][0] = 0;
        cout << "\n\n\nv" << i+1 << "(0) = max( "<< g_x[i][0] + v[i-1][0]  << " ) = " << v[i][0]
              << ";\tx" << i+1 << "(0) = " << x[i][0];

        for(int j = 1; j < N; ++j)
        {
            for(int k = 0; k <= j; ++k)
                forv[k] = g_x[i][k] + v[i-1][j-k]; // массив размерности j+1 для дальнейшего определения в нём макс. элемента

            maximum = max(forv, j+1);
            v[i][j] = maximum;
            x[i][j] = indexOfMax;

            cout << "\n\nv" << i+1 << "(" << j << ") = max(  ";
            for(int k = 0; k <= j; ++k)
                cout << forv[k] << "  ";
            cout << ") = " << maximum << ";\tx" << i+1 << "(" << j << ") = " << x[i][j];
        }
    }

    int x4opt = x[zm-1][N-1];

    int z = zm - x4opt;
    int x3opt = x[zm-2][z];

    z = z - x3opt;
    int x2opt = x[zm-3][z];

    z = z - x2opt;
    int x1opt = x[zm-4][z];

    cout << "\n\n\nTable:\n";
    cout << "z\tv1(z)\tv2(z)\tv3(z)\tv4(z)\tx1(z)\tx2(z)\tx3(z)\tx4(z)\n";
    for(int j = 0; j < N; ++j)
    {
        cout << j;
        for(int i = 0; i < zm; ++i)
          cout << "\t" << v[i][j];
        for(int i = 0; i < zm; ++i)
          cout << "\t" << x[i][j];
        cout<< endl;
    }

    cout << "\nOptimal x:\n";
    cout << "x1 = " << x1opt << endl;
    cout << "x2 = " << x2opt << endl;
    cout << "x3 = " << x3opt << endl;
    cout << "x4 = " << x4opt << endl;
    return 0;
}
