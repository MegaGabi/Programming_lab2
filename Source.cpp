#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int** CreateRectMatrix(int Size)//������� ���������� ������� �������� size � ���������� ��������� �������� ��� ������� ��-�� ������� � ������� [-size;size]
{
	int** arr = new int*[Size];
	for (int i = 0; i < Size; i++)
	{
		arr[i] = new int[Size];
		for (int j = 0; j < Size; j++)
		{
			arr[i][j] = -Size + rand() % (Size + Size + 1);//��������� ��������

			//arr[i][j] = (Size / 2) - i;
			//arr[i][j] = -(Size / 2) + j;

			//cout << "("  << setw(2) << (Size / 2) - i << ", " << setw(2) << -(Size / 2) + j << ") ";
		}
		//cout << endl;
	}

	return arr;
}

void ShowMatrix(int **arr, int Size) //���������� ��� ������� � �������
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

void ShowDiagonals(int **arr, int size) //������� ��������� � ���� �������
{
	cout << endl << "�������� ���������\n\n";

	for (int i = 0; i < size; i++)
	{
		cout << setw(5 * (i + 1));		//���������� ������ ������� �� ������� ������� ��-��
		cout << arr[i][i] << endl;	//�.�. � �������� ��������� ������ ������� �������� ����� ��� �������

	}

	cout << endl << "��������������� ���������\n\n";

	for (int i = 0; i < size; i++)
	{
		cout << setw(5 * (size - i));			//���������� ������ ������� �� ������� ������� ��-��
		cout << arr[i][size - i - 1] << endl;	//�.�. � �������������� ��������� ������� ������� �������� �������������� ��� ������
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

int* SortArray(int *arr, int size)//��������� ���������� ������
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
	int *mainDiagonal = new int[size];		//�������� ���������
	int *auxiliaryDiagonal = new int[size];	//��������������� ���������

	//�������� �������� � ��������������� ��������� �� �������
	for (int i = 0; i < size; i++)
	{
		mainDiagonal[i] = arr[i][i];//�.�. � �������� ��������� ������ ������� �������� ����� ��� �������
		auxiliaryDiagonal[i] = arr[i][size - i - 1];//�.�. � �������������� ��������� ������� ������� �������� �������������� ��� ������
	}

	mainDiagonal = SortArray(mainDiagonal, size);
	auxiliaryDiagonal = SortArray(auxiliaryDiagonal, size);

	cout << "�������� ��������� ����� ����������: " << endl;
	ShowArray(mainDiagonal, size);

	cout << "�������������� ��������� ����� ����������: " << endl;
	ShowArray(auxiliaryDiagonal, size);

	int midEl = (size - 1) / 2;//������ �������� ���������

	cout << endl << "�������� � ����� ����������� ���������� ";
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
		cout << "������ ��������� ����: ";

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

	cout << "������� N: ";
	CheckCin(N, 0);

	int size = N * 10 + 1;

	int **arr = CreateRectMatrix(size);

	cout << "\n��������� ������:\n\n";

	ShowMatrix(arr, size); cout << endl;
	ShowDiagonals(arr, size); cout << endl;

	DiagonalSortRect(arr, size);

	cout << "\n��������������� ������:\n\n";

	ShowMatrix(arr, size); cout << endl;

	cin.get();

	return 0;
}