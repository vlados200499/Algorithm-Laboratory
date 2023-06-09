#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <random>
#include <thread>
#include <Windows.h>

using namespace std;






//##############################################################################################
void quick_sort(vector<int>& arr, const int left, const int right)
{
	int i = left, j = right;
	int pivot = arr[left];

	while (i <= j)
	{
		while (arr[i] < pivot)
		{
			i++;
		}

		while (arr[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	if (left < j)
	{
		quick_sort(arr, left, j);
	}

	if (i < right)
	{
		quick_sort(arr, i, right);
	}
}

void Insertion_Sort(std::vector<int>& arr)
{
	int n = arr.size();
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void Selection_Sort(std::vector<int>& arr)
{
	int n = arr.size();
	int j, min_index;
	for (int i = 0; i < n - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		std::swap(arr[min_index], arr[i]);
	}
}


//##############################################################################################






enum SortType
{
	QuikSort,
	SelectionSort,
	InsertSort
};

enum InputVector
{
	Random,
	Rosn,
	Mal,
	constante,
	A
};





std::vector<int> GenerateVector(InputVector type, int n)
{
	std::vector<int> Vector(n);
	switch (type)
	{
	case Random:
		for (int i = 0; i < n; i++)
		{
			Vector[i] = rand() % n;
		}
		return Vector;

	case Rosn:
		for (int i = 0; i < n; i++)
		{
			Vector[i] = i;
		}
		return Vector;
	case Mal:
		for (int i = n - 1; i >= 0; --i)
		{
			Vector[i] = i;
		}
		return Vector;
	case constante:
		for (int i = 0; i < n; i++)
		{
			Vector[i] = 42;
		}
		return Vector;

	case A:
		for (int i = 0; i < n / 2; i++)
		{
			Vector[i] = i;
			Vector[n - i] = i;
		}
		return Vector;
	}
}

void print_vector(const std::vector<int>& v1)
{
	std::cout << "Sorted Vector: ";
	for (int i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i] << " ";
	}
}
vector<int> GetSelected(int x, int size)
{
	switch (x)
	{
	case 1:
		return GenerateVector(Random, size);
		break;
	case 2:
		return GenerateVector(Rosn, size);
		break;
	case 3:
		return GenerateVector(Mal, size);
		break;
	case 4:
		return GenerateVector(constante, size);
		break;

	case 5:
		return GenerateVector(A, size);
		break;
	}
}

void QuikSort_Case(vector<int> ui)
{
	auto start = chrono::high_resolution_clock::now();
	quick_sort(ui, 0, ui.size());
	auto end = chrono::high_resolution_clock::now();
	print_vector(ui);
	std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms " << endl;
}

void Inser_Case(vector<int> ui)
{
	auto start = chrono::high_resolution_clock::now();
	Insertion_Sort(ui);
	auto end = chrono::high_resolution_clock::now();
	print_vector(ui);
	std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms " << endl;
}

void Selection_Case(vector<int> ui)
{
	auto start = chrono::high_resolution_clock::now();
	Selection_Sort(ui);
	auto end = chrono::high_resolution_clock::now();
	print_vector(ui);
	std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms " << endl;
}

void PrintTime(vector<std::pair<int, double>> v1)
{
	for (auto speed_of_sorting : v1)
	{
		std::cout << "Size is " << speed_of_sorting.first << " Time is " << speed_of_sorting.second << "ms" << endl;
	}
}

void QuikSort_Time(vector<std::pair<int, double>>& SpeedOfSortingQuik,InputVector e)
{
	int sizes[] = {10, 100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000};
	for (int siz : sizes)
	{
		auto v = GenerateVector(e, siz);
		auto start = std::chrono::high_resolution_clock::now();
		quick_sort(v, 0, siz-1);
		auto end = std::chrono::high_resolution_clock::now();
		SpeedOfSortingQuik.emplace_back(siz, std::chrono::duration<double, std::milli>(end - start).count());
	}
}

void InsertSort_Time(vector<std::pair<int, double>>& SpeedOfSortingInsert,InputVector e)
{
	int sizes[] = {10, 100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000};
	for (int siz : sizes)
	{
		auto v = GenerateVector(e, siz);
		auto start = std::chrono::high_resolution_clock::now();
		Insertion_Sort(v);
		auto end = std::chrono::high_resolution_clock::now();
		SpeedOfSortingInsert.emplace_back(siz, std::chrono::duration<double, std::milli>(end - start).count());
	}
}

void SelectionSort_Time(vector<std::pair<int, double>>& SpeedOfSortingSelection,InputVector e)
{
	int sizes[] = {10, 100, 500, 1000, 5000, 10000, 25000, 50000, 75000, 100000};
	for (int siz : sizes)
	{
		auto v = GenerateVector(e, siz);
		auto start = std::chrono::high_resolution_clock::now();
		Selection_Sort(v);
		auto end = std::chrono::high_resolution_clock::now();
		SpeedOfSortingSelection.emplace_back(siz, std::chrono::duration<double, std::milli>(end - start).count());
	}
}









/*
int main()
{
	int SelectTask;
	std::cout << "Select 1 or 2 task: "<<endl;
	std::cin >> SelectTask;


	if (SelectTask == 1)
	{
		int a, size, type;


		std::cout << "Select sort type:" << endl;
		std::cout << "1.quick_sort" << endl;

		std::cout << "2.Insertion_Sort" << endl;

		std::cout << "3.Selection_Sort" << endl;

		std::cin >> a;


		std::cout << "Select size:" << endl;

		std::cin >> size;


		std::cout << "Select vector type:" << endl;


		std::cout << "1.Rand" << endl;

		std::cout << "2.Rosn" << endl;

		std::cout << "3.Maleja" << endl;

		std::cout << "4.constante" << endl;

		std::cout << "5.A-shape" << endl;
		std::cin >> type;


		vector<int> ui = GetSelected(a, size);


		switch (a)
		{
		case 1:
			QuikSort_Case(ui);
			break;


		case 2:


			Inser_Case(ui);
			break;


		case 3:

			Selection_Case(ui);
			break;
		default:;
		}
	}
	else
	{
		vector<std::pair<int, double>> SpeedOfSortingQuik;
		vector<std::pair<int, double>> SpeedOfSortingInsert;
		vector<std::pair<int, double>> SpeedOfSortingSelection;


		thread t1(QuikSort_Time, std::ref(SpeedOfSortingQuik));
		t1.join();
		thread t2(InsertSort_Time, std::ref(SpeedOfSortingInsert));
		t2.join();
		thread t3(SelectionSort_Time, std::ref(SpeedOfSortingSelection));
		t3.join();

		std::cout << "Quick sort:" << endl;
		PrintTime(SpeedOfSortingQuik);


		std::cout << "Insert Sort sort:" << endl;
		PrintTime(SpeedOfSortingInsert);


		std::cout << "Selection sort:" << endl;
		PrintTime(SpeedOfSortingSelection);
	}
}
*/



/*enum InputVector
{
	Random,
	Rosn,
	Mal,
	constante,
	A
};
*/

/*
int main()
{

	vector<std::pair<int, double>> time;

	ofstream MyFile("postotxt");
	SelectionSort_Time(time,A);
	MyFile<<"SelectionSort"<<"\n";
	MyFile<<"A"<<"\n";
	for (const std::pair<int, double>& element : time)
	{
		MyFile<<element.first<<" "<<element.second<<"\n";
	}


}*/