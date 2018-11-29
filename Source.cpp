#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int** CreateRectMatrix(int Size)//создает квадратную матрицу размером size и генерирует случайные значения для каждого эл-та матрицы в райноне [-size;size]
{
	int** arr = new int*[Size];
	for (int i = 0; i < Size; i++)
	{
		arr[i] = new int[Size];
		for (int j = 0; j < Size; j++)
		{
			arr[i][j] = -Size + rand() % (Size + Size + 1);//генерация значений

			//arr[i][j] = (Size / 2) - i;
			//arr[i][j] = -(Size / 2) + j;

			//cout << "("  << setw(2) << (Size / 2) - i << ", " << setw(2) << -(Size / 2) + j << ") ";
		}
		//cout << endl;
	}

	return arr;
}

void ShowMatrix(int **arr, int Size) //показывает всю матрицу в консоли
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			cout << setw(5) << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void ShowDiagonals(int **arr, int size) //выводит диагонали в окно консоли
{
	cout << endl << "Основная диагональ\n\n";

	for (int i = 0; i < size; i++)
	{
		cout << setw(5 * (i + 1));		//перемещаем курсор консоли на позицию нужного эл-та
		cout << arr[i][i] << endl;	//т.к. в основной диагонали строка каждого элемента равна его столбцу

	}

	cout << endl << "Вспомогательная диагональ\n\n";

	for (int i = 0; i < size; i++)
	{
		cout << setw(5 * (size - i));			//перемещаем курсор консоли на позицию нужного эл-та
		cout << arr[i][size - i - 1] << endl;	//т.к. в дополнительной диагонали столбец каждого элемента противоположен его строке
	}
}

void ShowArray(int *arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << setw(5) << arr[i] << " ";
	}
	cout << endl;
}

int* SortArray(int *arr, int size)//сортирует одномерный массив
{
	for (int i = 0; i < size; i++)
	{
		int smallestIndex = i;

		for (int j = i; j < size; j++)
		{
			if (arr[j] < arr[smallestIndex])
			{
				smallestIndex = j;
			}
		}

		int buf = arr[i];
		arr[i] = arr[smallestIndex];
		arr[smallestIndex] = buf;
	}

	return arr;
}

bool DiagonalSortRect(int **&arr, int size)
{
	int *mainDiagonal = new int[size];		//основная диагональ
	int *auxiliaryDiagonal = new int[size];	//вспомогательная диагональ

	//собираем основную и вспомогательную диагонали из массива
	for (int i = 0; i < size; i++)
	{
		mainDiagonal[i] = arr[i][i];//т.к. в основной диагонали строка каждого элемента равна его столбцу
		auxiliaryDiagonal[i] = arr[i][size - i - 1];//т.к. в дополнительной диагонали столбец каждого элемента противоположен его строке
	}

	mainDiagonal = SortArray(mainDiagonal, size);
	auxiliaryDiagonal = SortArray(auxiliaryDiagonal, size);

	cout << "Основная диагональ после сортировки: " << endl;
	ShowArray(mainDiagonal, size);

	cout << "Дополнительная диагональ после сортировки: " << endl;
	ShowArray(auxiliaryDiagonal, size);

	int midEl = (size - 1) / 2;//индекс середины диагонали

	cout << endl << "Элементы в точке пересечения диагоналей ";
	if (mainDiagonal[midEl] == auxiliaryDiagonal[midEl])
	{
		cout << mainDiagonal[midEl] << " == " << auxiliaryDiagonal[midEl] << endl;

		for (int j = 0; j < size; j+=2)
		{
			for (int i = 0; i < size; i++)
			{
				int smallestIndex = i;

				for (int sr = i; sr < size; sr++)
				{
					if (arr[sr][j] < arr[smallestIndex][j])
					{
						smallestIndex = sr;
					}
				}

				int buf = arr[i][j];
				arr[i][j] = arr[smallestIndex][j];
				arr[smallestIndex][j] = buf;
			}
		}
	}
	else
	{
		cout << mainDiagonal[midEl] << " != " << auxiliaryDiagonal[midEl] << endl;

		for (int i = 1; i < size; i += 2)
		{
			for (int j = 0; j < size; j++)
			{
				int biggestIndex = j;

				for (int sr = j; sr < size; sr++)
				{
					if (arr[i][sr] > arr[i][biggestIndex])
					{
						biggestIndex = sr;
					}
				}

				int buf = arr[i][j];
				arr[i][j] = arr[i][biggestIndex];
				arr[i][biggestIndex] = buf;
			}
		}
	}

	return false;
}

void CheckCin(int &N, int Smallest)
{
	while (!(cin >> N) || N < Smallest)
	{
		cout << "Ошибка повторите ввод: ";

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	

	int N;

	cout << "Введите N: ";
	CheckCin(N, 0);

	int size = N * 10 + 1;

	int **arr = CreateRectMatrix(size);

	cout << "\nСлучайный массив:\n\n";

	ShowMatrix(arr, size); cout << endl;
	ShowDiagonals(arr, size); cout << endl;

	DiagonalSortRect(arr, size);

	cout << "\nОтсортированный массив:\n\n";

	ShowMatrix(arr, size); cout << endl;

	cin.get();

	return 0;
}