#include <iostream>
#include <vector>
#include <array>

// Вариант 2
using namespace std;

vector<int> item1(0);
vector<int>& refvec = item1;

/*
Пункт 3:

Для П.1 используем std::vector, т.к. там требуется добавлять и удалять элементы, а в П.2 массив фиксированный, подойдёт и std::array.

Здесь представлен выбор без выбора, 
т.к. у std::array отсутствует возможность динамически расширять массив (что необходимо для выполнения П.1), в отличие от std::vector.

std::array и std::vector играют одну и ту же роль, если массив должен быть фиксированным

*/

void print_vector(vector<int>& vec) {
	cout << "[";
	for (int index = 0; index < vec.size(); ++index) {
		cout << vec[index] << (index == vec.size() - 1 ? "" : " ");
	}
	cout << "]";
}

void print_vector(vector<int>& vec, bool usecomma) {
	cout << "[";
	for (int index = 0; index < vec.size(); ++index) {
		cout << vec[index] << (index == vec.size() - 1 ? "" : ", ");
	}
	cout << "]";
}

void add_beginning(vector<int>& vec) {
	int element;
	cout << endl << "Введите значение элемента: ";
	cin >> element;
	vec.reserve(vec.size() + 1);
	vec.insert(vec.begin(), element);
	cout << "Элемент со значением " << element << " был добавлен в начало массива.";
}

void add_end(vector<int>& vec) {
	int element;
	cout << endl << "Введите значение элемента: ";
	cin >> element;
	vec.reserve(vec.size() + 1);
	vec.push_back(element);
	cout << "Элемент со значением " << element << " был добавлен в конец массива.";
}

void vector_clear(vector<int>& vec) {
	cout << endl << "Массив ";
	print_vector(vec);
	vec.clear();
	vec.shrink_to_fit();
	cout << " был успешно очищен";
}

void vector_seeker(vector<int>& vec) {
	int seekfor;
	cout << "Введите значение искомого элемента: ";
	cin >> seekfor;
	vector<int> seekerofthestorm(0);
	vector<int>& skrskr = seekerofthestorm;
	for (int index = 0; index < vec.size(); ++index) {
		if (vec[index] == seekfor) {
			skrskr.reserve(skrskr.size() + 1);
			skrskr.push_back(index);
		}
	}
	cout << endl << "Соответствующие поиску индексы: ";
	print_vector(skrskr, true);
}

void vector_variant(vector<int>& vec) {
	if (vec.size() == 0) {
		cout << endl << "В массиве нет элементов :(";
		return;
	}
	cout << endl << "Массив до Божественного вмешательства: ";
	print_vector(vec);
	cout << endl;
	if ((vec.size() & 1) == 0) {
		vec.erase(vec.begin());
	}
	else {
		if (vec.size() >= 4)
			vec.erase(vec.begin(), vec.end()-4);
	}
	cout << "После: ";
	print_vector(vec);
}

void menu(int x) {
	switch (x)
	{
	case 0:
		cout << endl << "пока." << endl;
		break;
	case 1:
		cout << endl << "Текущий массив: ";
		print_vector(refvec);
		break;
	case 2:
		add_beginning(refvec);
		break;
	case 3:
		add_end(refvec);
		break;
	case 4:
		vector_clear(refvec);
		break;
	case 5:
		vector_seeker(refvec);
		break;
	case 6:
		vector_variant(refvec);
		break;
	default:
		cout << "Неизвестное значение" << endl;
		break;
	}
}

void arr_sort(array<int, 10>* parr) {
	array<int, 10> arr = *parr;
	for (char i = 0; i < 10 - 1; ++i) {
		for (char j = i + 1; j < 10; ++j) {
			if (arr[i] < arr[j]) {
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	*parr = arr;
}

void arr_sort(array<int, 10>& arr) {
	for (char i = 0; i < 10 - 1; ++i) {
		for (char j = i + 1; j < 10; ++j) {
			if (arr[i] > arr[j]) {
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void arr_print(array<int, 10> arr) {
	cout << "[";
	for (int index = 0; index < arr.size(); ++index) {
		cout << arr[index] << (index == arr.size() - 1 ? "" : " ");
		arr[index] = 0;
	}
	cout << "]";
}

void item2() {
	cout << "Пункт 2." << endl << endl;
	array<int, 10> array_item2;
	array<int, 10>& arr = array_item2;
	array<int, 10>* parr = &array_item2;
	for (int c = 0; c < 10; ++c) {
		cout << "Введите элемент массива в пределах [-10;10] (Осталось: " << 10 - c << "): ";
		cin >> arr[c];
	}
	cout << endl;
	cout << "Массив: ";
	arr_print(array_item2);
	arr_sort(parr);
	cout << endl;
	cout << "Массив в порядке убывания: ";
	arr_print(array_item2);
	arr_sort(arr);
	cout << endl;
	cout << "Массив в порядке возрастания: ";
	arr_print(array_item2);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	

    while (true) {
		cout << endl << "- - - - - - - - - Меню - - - - - - - - -" << endl
			<< "0. Выход." << endl
			<< "1. Просмотр массива." << endl
			<< "2. Добавить элемент в начало." << endl
			<< "3. Добавить элемент в конец." << endl
			<< "4. Очистка всего массива." << endl
			<< "5. Поиск элемента в массиве." << endl
			<< "6. Задание варианта." << endl
			<< endl << "Выбор: ";
		int input;
		cin >> input;
		menu(input);
		if (input == 0) {
			item2();
			break;
		}
    }
}
