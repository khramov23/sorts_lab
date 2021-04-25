#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

// Копирование массива
void copy_array(double* copy, double* arr, int n) {
	for (int i = 0; i < n; i++)
		copy[i] = arr[i];
}

// Пузырьковая сортировка
void bubble_sort(double* arr, int n) {
	int tmp;
	bool noSwap;
	for (int i = n - 1; i >= 0; i--)
	{
		noSwap = true;
		for (int j = 0; j < i; j++)
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				noSwap = false;
			}
		if (noSwap) break;
	}

}

// Сортировка вставками
void insert_sort(double* arr, int n) {
	for (int i = 1; i < n; i++) {
		int k = i;
		while (k > 0 && arr[k - 1] > arr[k]) {
			std::swap(arr[k], arr[k - 1]);
			k -= 1;
		}
	}
}

// Сортировка выбором
void selection_sort(double* arr, int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		std::swap(arr[i], arr[minIndex]);
	}
}

// Сортировка слиянием
void merge(double* arr, int left, int right, int middle)
{
	int j = left;
	int k = middle + 1;
	int count = right - left + 1;
	if (count <= 1) return;
	double* temp = new double[count];
	for (int i = 0; i < count; i++) {
		if (j <= middle && k <= right) {
			if (arr[j] < arr[k])
				temp[i] = arr[j++];
			else
				temp[i] = arr[k++];
		}
		else {
			if (j <= middle)
				temp[i] = arr[j++];
			else
				temp[i] = arr[k++];
		}
	}
	j = 0;
	for (int i = left; i <= right; i++) {
		arr[i] = temp[j++];
	}
	delete[] temp;
}
void merge_sort(double* arr, int left, int right)
{
	int middle = left + (right - left) / 2;
	if (left >= right) return;

	merge_sort(arr, left, middle);
	merge_sort(arr, middle + 1, right);
	merge(arr, left, right, middle);
}
void call_merge_sort(double* arr, int n) {
	merge_sort(arr, 0, n - 1);
}

// Модифицированная сортировка слиянием
void merge_mod(double* temp, double* arr, int left, int right, int middle) {
	int j = left;
	int k = middle + 1;
	int count = right - left + 1;
	if (count <= 1) return;
	for (int i = 0; i < count; i++) {
		if (j <= middle && k <= right) {
			if (arr[j] < arr[k])
				temp[i] = arr[j++];
			else
				temp[i] = arr[k++];
		}
		else {
			if (j <= middle)
				temp[i] = arr[j++];
			else
				temp[i] = arr[k++];
		}
	}
	j = 0;
	for (int i = left; i <= right; i++) {
		arr[i] = temp[j++];
	}
}
void merge_sort_mod(double* temp, double* arr, int left, int right) {
	int middle = left + (right - left) / 2;
	if (left >= right) return;

	merge_sort_mod(temp, arr, left, middle);
	merge_sort_mod(temp, arr, middle + 1, right);
	merge_mod(temp, arr, left, right, middle);
}
void call_merge_sort_mod(double* arr, int n) {
	double* temp = new double[n];
	merge_sort_mod(temp, arr, 0, n - 1);
	copy_array(arr, temp, n);
	delete[] temp;
}

// std sort
void std_sort(double* arr, int n) {
	std::sort(arr, arr + n);
}

// Быстрая сортировка
void quick_sort(double* mas, int size) {
	int i = 0;
	int j = size - 1;
	double mid = mas[size / 2];

	do {
		while (mas[i] < mid) {
			i++;
		}
		while (mas[j] > mid) {
			j--;
		}
		if (i <= j) {
			double tmp = mas[i];
			mas[i] = mas[j];
			mas[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);

	if (j > 0) {
		quick_sort(mas, j + 1);
	}
	if (i < size) {
		quick_sort(&mas[i], size - i);
	}
}

// Проверка сортировки
bool check(double* ar, int n)
{
	for (int i = 0; i < n - 1; i++)
		if (ar[i + 1] < ar[i])
			return false;
	return true;
}

// Длина строки
int get_str_len(const char* str) {
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

// Проверка равенства строк
bool is_equal(const char* a, const char* b) {
	int len1 = get_str_len(a);
	int len2 = get_str_len(b);

	if (len1 != len2)
		return false;

	for (int i = 0; i < len1; i++)
		if (a[i] != b[i])
			return false;

	return true;
}


void (*my_sort) (double*, int);

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	if (argc == 1) {
		my_sort = &bubble_sort;
		printf("bubble sort\n");
	}
	else if (argc == 2) {
		if (is_equal(argv[1], "std_sort")) {
			my_sort = &std_sort;
			printf("\nstd sort\n");
		}
		else if (is_equal(argv[1], "bubble_sort")) {
			my_sort = &bubble_sort;
			printf("\n\nbubble sort\n");
		}
		else if (is_equal(argv[1], "insert_sort")) {
			my_sort = &insert_sort;
			printf("\n\ninsert sort\n");
		}
		else if (is_equal(argv[1], "selection_sort")) {
			my_sort = &selection_sort;
			printf("\n\nselection sort\n");
		}
		else if (is_equal(argv[1], "merge_sort")) {
			my_sort = &call_merge_sort;
			printf("\n\nmerge sort\n");
		}
		else if (is_equal(argv[1], "merge_sort_mod")) {
			my_sort = &call_merge_sort_mod;
			printf("\n\nmerge sort modified\n");
		}
		else if (is_equal(argv[1], "quick_sort")) {
			my_sort = &quick_sort;
			printf("\n\nquick_sort\n");
		}
		else
			printf("Некорректные данные, попробуйте еще раз;");
	}

	const int n = 200000;
	double* arr = new double[n];
	double* copy = new double[n];
	for (int i = 0; i < n; i++) {
		int a = rand() % 1001;
		arr[i] = pow(-1, rand()) * (double)a / 10;
	}

	// Вывод количества элементов
	for (int i = 10000; i <= n; i += 10000)
		printf("%d;", i);
	printf("\n");

	// Вывод времени сортировки
	for (int i = 10000; i <= n; i += 10000)
	{
		copy_array(copy, arr, i);
		int t1 = clock();
		my_sort(copy, i);
		t1 = clock() - t1;
		if (check(copy, i))
			printf("%d;", t1);
		else
			printf("Ошибка сортировки\n");
	}

	return 0;
}