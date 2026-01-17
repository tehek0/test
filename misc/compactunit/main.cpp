#include <iostream>
#include <bitset>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	unsigned long long Pos = 0; // координаты, 21 бит на каждую координату
	unsigned int Gold = 0; // золото
	unsigned short Mana = 0; // для маны (14 бит)
	unsigned short HealthStatus = 0; // для здоровья (14 бит), определения типа (2 бита)
	unsigned short Character = 0; // для определения силы (4 бита), интеллекта (4 бита), уровня (4 бита), ловкости (4 бита)
	unsigned short EquipmentAndPosNegative = 0; // для определения наличия оружия (1 бит), наличия брони (1 бит), id оружия (4 бита), id брони (4 бита), негативности координат, первый бит - Z, второй - Y, третий - X
	// всего 64+32+16+16+16+16=160 бит, занято 63+32+14+16+16+13=154 бита.
	long long entry; // Переменная для ввода


	cout << "-- Создание Юнита --" << endl;
	cout << "Введите координату X юнита: ";
	cin >> entry;
	if (entry < 0) {
		EquipmentAndPosNegative = (EquipmentAndPosNegative | (1 << 2));
		// cout << endl << bitset<16>(EquipmentAndPosNegative);
		entry = -1 * entry;
	}
	Pos = (Pos | ((entry > 2000000 ? 2000000 : entry) << 42));
	// cout << endl << bitset<64>(Pos) << " " << bitset<21>(entry) << endl;



	cout << "Введите координату Y юнита: ";
	cin >> entry;
	if (entry < 0) {
		EquipmentAndPosNegative = (EquipmentAndPosNegative | (1 << 1));
		// cout << endl << bitset<16>(EquipmentAndPosNegative);
		entry = -1 * entry;
	}
	Pos = (Pos | ((entry > 2000000 ? 2000000 : entry) << 21));
	// cout << endl << bitset<64>(Pos) << " " << bitset<21>(entry) << endl;

	cout << "Введите координату Z юнита: ";
	cin >> entry;
	if (entry < 0) {
		EquipmentAndPosNegative = (EquipmentAndPosNegative | 1);
		// cout << endl << bitset<16>(EquipmentAndPosNegative);
		entry = -1 * entry;
	}
	Pos = (Pos | (entry > 2000000 ? 2000000 : entry));
	// cout << endl << bitset<64>(Pos) << " " << bitset<21>(entry) << endl;

	cout << "Введите количество золота юнита: ";
	cin >> entry;
	Gold = entry > 4000000000 ? 4000000000 : entry;
	cout << endl;

	cout << "Введите количество здоровья юнита: ";
	cin >> entry;
	entry = (entry >= 10000 ? 10000 : (entry < 1 ? 1 : entry));
	HealthStatus = HealthStatus | entry;
	cout << endl;

	cout << "Введите количество маны юнита: ";
	cin >> entry;
	entry = (entry >= 10000 ? 10000 : (entry < 1 ? 1 : entry));
	Mana = Mana | entry;
	cout << endl;

	cout << "Введите силу юнита (1, 10): ";
	cin >> entry;
	entry = (entry >= 10 ? 10 : (entry < 1 ? 1 : entry));
	Character = Character | entry;

	cout << "Введите ловкость юнита (1, 10): ";
	cin >> entry;
	entry = ((entry >= 10 ? 10 : (entry < 1 ? 1 : entry)) << 8);
	Character = Character | entry;

	cout << "Введите интеллект юнита (1, 10): ";
	cin >> entry;
	entry = ((entry >= 10 ? 10 : (entry < 1 ? 1 : entry)) << 4);
	Character = Character | entry;

	cout << "Введите уровень юнита (1, 10): ";
	cin >> entry;
	entry = ((entry >= 10 ? 10 : (entry < 1 ? 1 : entry)) << 12);
	Character = Character | entry;

	cout << "У юнита есть оружие? (0, 1): ";
	cin >> entry;
	entry = (entry >= 1 ? 1 : 0);
	if (entry == 1) {
		EquipmentAndPosNegative = EquipmentAndPosNegative | (entry << 15);
		cout << "Введите ID оружия (1, 10): ";
		cin >> entry;
		entry = (entry >= 10 ? 10 : (entry < 1 ? 1 : entry));
		EquipmentAndPosNegative = EquipmentAndPosNegative | (entry << 10);
	}
	// cout << endl << bitset<16>(EquipmentAndPosNegative) << endl;

	cout << "У юнита есть броня? (0, 1): ";
	cin >> entry;
	entry = (entry >= 1 ? 1 : 0);
	if (entry == 1) {
		EquipmentAndPosNegative = EquipmentAndPosNegative | (entry << 14);
		cout << "Введите ID брони (1, 10): ";
		cin >> entry;
		entry = (entry >= 10 ? 10 : (entry < 1 ? 1 : entry));
		EquipmentAndPosNegative = EquipmentAndPosNegative | (entry << 6);
	}
	// cout << endl << bitset<16>(EquipmentAndPosNegative) << endl;

	cout << "Введите тип юнита (1 - маг, 2 - лучник, 3 - воин): ";
	cin >> entry;
	entry = (entry >= 3 ? 3 : (entry < 1 ? 1 : entry));
	HealthStatus = HealthStatus | (entry << 14);
	cout << endl;



	/*

	Читаем данные

	*/


	cout << endl << "-- Итоги --" << endl;

	cout << "Координаты: " << endl
		<< "X: " << ((((EquipmentAndPosNegative >> 2) & 1) == 0 ? "" : "-")) << ((Pos >> 42) & 0b0111111111111111111111) << endl
		<< "Y: " << ((((EquipmentAndPosNegative >> 1) & 1) == 0 ? "" : "-")) << ((Pos >> 21) & 0b0111111111111111111111) << endl
		<< "Z: " << ((((EquipmentAndPosNegative) & 1) == 0 ? "" : "-")) << (Pos & 0b0111111111111111111111) << endl;

	cout << "Золото юнита: " << Gold << endl;

	cout << "Здоровье юнита: " << (HealthStatus & 0b011111111111111) << endl;

	cout << "Мана юнита: " << Mana << endl;

	cout << "Характеристики: " << endl;
	cout << "- Сила: " << ((Character) & 0b1111) << endl;
	cout << "- Ловкость: " << ((Character >> 8) & 0b1111) << endl;
	cout << "- Интеллект: " << ((Character >> 4) & 0b1111) << endl;
	cout << "- Уровень: " << (Character >> 12) << endl;

	cout << "Есть оружие? " << ((EquipmentAndPosNegative >> 15) == 1 ? "Да" : "Нет") << endl;
	if ((EquipmentAndPosNegative >> 15) == 1)
		cout << " ID оружия: " << ((EquipmentAndPosNegative >> 10) & (0b1111)) << endl;

	cout << "Есть броня? " << (((EquipmentAndPosNegative >> 14) & 0b1) == 1 ? "Да" : "Нет") << endl;
	if (((EquipmentAndPosNegative >> 14) & 0b1) == 1)
		cout << " ID брони: " << ((EquipmentAndPosNegative >> 6) & (0b1111)) << endl;

	cout << "Тип юнита: ";
	switch (HealthStatus >> 14) {
	case 1:
		cout << "Маг" << endl;
		break;
	case 2:
		cout << "Лучник" << endl;
		break;
	default:
		cout << "Воин" << endl;
		break;
	}




	int P = sizeof(Pos) + sizeof(Gold) + sizeof(Mana) + sizeof(HealthStatus) + sizeof(Character) + sizeof(EquipmentAndPosNegative);
	cout << endl << "Итоговый объём юнита в памяти (не включая переменную для ввода): " << P << " байт" << endl;
	/*

	Спроектируем теоретический ввод данных в отдельные переменные (не используя переменную для ввода)

			три переменных int для определения координат		золото					здоровье					мана					уровень						сила					ловкость				интеллект	  наличие оружия		id оружия		  наличие брони			   id брони				  тип

	*/
	int B = (sizeof(int) + sizeof(int) + sizeof(int)) + sizeof(unsigned int) + (sizeof(unsigned short) + sizeof(unsigned short)) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(unsigned char) + sizeof(bool) + sizeof(unsigned char) + sizeof(bool) + sizeof(unsigned char) + sizeof(char);

	cout << "Если хранить значение каждого параметра отдельно: " << B << " байт" << endl;
	cout << "Сэкономлено: " << (((B * 1.) / (P * 1.)) - 1) * 100 << "%" << endl;
};