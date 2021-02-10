//simplex-метод

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Ni = 3, Nj = 3;
int col, row;

string titles[Ni+1][Nj+1] = // таблица заголовков
{
    {"basis", "x1", "x2", "free"},
    {"x3", "", "", ""},
    {"x4", "", "", ""},
    {"F", "", "", ""},
};

double table[Ni][Nj] =  // таблица значений элементов
{
    {6, 6, 36},
    {4, 8, 32},
    {-3, 4, 0}
};

double newtable[Ni][Nj]; // таблица значений элементов для пересчета на каждой итерации со значений старой таблицы

// прототипы функций
bool there_is_a_negativeElem_in_indexRow_and_there_is_a_positiveElem_in_its_column();

void find_permissive_column();

void find_permissive_row();

void changeVariables();

void fill_newtable();

void print_newtable();

void fill_table_for_next_step();

bool there_is_a_negativeElem_in_indexRow();


int main()
{
    while(there_is_a_negativeElem_in_indexRow_and_there_is_a_positiveElem_in_its_column()) // пока выполняется условие 3
    {
        find_permissive_column(); // ищем разрешающий столбец
        find_permissive_row(); // ищем разрешающую строку
        changeVariables(); // меняем переменные местами: одна выходит из базиса - другая входит в базис
        fill_newtable(); // рассчитываем значения в новой таблице
        print_newtable(); // вывод новой таблицы в консоль
        fill_table_for_next_step(); // table = newtable - для следующей итерации
    }
    // вышли из цикла => условие 3 не выполнилось
    if(there_is_a_negativeElem_in_indexRow() == false) // проверка на условие 1 после проверки на условие 3 в цикле while
        cout << "Plan is optimal, F = " << newtable[Ni-1][Nj-1]
                << ", x1 = " << newtable[row][Nj-1] << ", x2 = 0\n";
    else // условия 1 и 3 не выполнились => условие 2
        cout << "F decreases infinitely\n";

    return 0;
}

bool there_is_a_negativeElem_in_indexRow_and_there_is_a_positiveElem_in_its_column() // условие 3 - условие продолжения цикла
{
    for(int j = 0; j < Nj; ++j)
        if(table[Ni-1][j] < 0)
            for(int i = 0; i < Ni-1; ++i)
                if(table[i][j] > 0)
                    return true;
    return false;
}

void find_permissive_column()
{
    double min = table[Ni-1][0];
    col = 0;
    for(int j = 1; j < Nj; ++j)
        if(table[Ni-1][j] < min)
        {
            min = table[Ni-1][j];
            col = j;
        }
}

void find_permissive_row()
{
    double min;
    if(table[0][col] > 0)
        min = table[0][Nj-1] / table[0][col];

    for(int i = 1; i < Ni-1; ++i)
        if(table[i][col] > 0)
            if(table[i][Nj-1] / table[i][col] < min)
            {
                min = table[i][Nj-1] / table[i][col];
                row = i;
            }
}

void changeVariables()
{
   string temp;
   temp = titles[row+1][0];
   titles[row+1][0] = titles[0][col+1];
   titles[0][col+1] = temp;
}

void fill_newtable()
{
    double elem = table[row][col];
    newtable[row][col] = 1 / elem;

    for(int j = 0; j < Nj; ++j) // заполнение разреш. строки
    {
        if(j == col) continue;
        newtable[row][j] = table[row][j] / elem;
    }
    for(int i = 0; i < Ni; ++i) // заполнение разреш. столбца
    {
        if(i == row) continue;
        newtable[i][col] = -table[i][col] / elem;
    }

    for(int i = 0; i < Ni; ++i) // заполнение остальных элементов таблицы
    {
        if(i == row) continue;
        for(int j = 0; j < Nj; ++j)
        {
            if(j == col) continue;
            newtable[i][j] = (table[i][j]*elem - table[i][col]*table[row][j]) / elem;
        }
    }
}

void print_newtable()
{
    cout << endl;
    for(int j = 0; j < Nj+1; ++j)
        cout << titles[0][j] << "\t";
    cout << endl;
    for(int i = 1; i < Ni+1; ++i)
    {
        cout << titles[i][0] << "\t";
        for(int j = 0; j < Nj; ++j)
            cout << newtable[i-1][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void fill_table_for_next_step()
{
    for(int i = 0; i < Ni; ++i)
        for(int j = 0; j < Nj; ++j)
            table[i][j] = newtable[i][j];
}

bool there_is_a_negativeElem_in_indexRow()
{
    for(int j = 0; j < Nj; ++j)
        if(table[Ni-1][j] < 0)
            return true;
    return false;
}
