#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
		
using namespace std;

class Tour {
	private:
		int id;
		string title;
		string location;
		string duration;
		string price;
	
	public:
		Tour(int num, string name, string loc, string time, string p) {
			this->id = num;
			this->title = name;
			this->location = loc;
			this->duration = time;
			this->price = p;
		}


		void changeTitle(string new_title) {
			title = new_title;
		}
		void changeLocation(string new_loc) {
			location = new_loc;
		}
		void changeDuration(string new_time) {
			duration = new_time;
		}
		void changePrice(string new_price) {
			price = new_price;
		}

		int getId() {
			return id;
		}

		string getTitle() {
			return title;
		}

		string getLocation() {
			return location;
		}
		
		string getDuration() {
			return duration;
		}
		
		string getPrice() {
			return price;
		}

};

void showData(vector<Tour>& tours) {
	int length = tours.size();
	int max_page = ceil(length / 10);
	int page;

	cout << "\nВведите номер страницы (от 1 до " << max_page << "): ";
	if (!(cin >> page)) {
		cout << "\nНекорректный ввод!" << endl;
		cin.clear();
		cin.ignore();
		return;
	}

	if (page > max_page) {
		cout << "Такой страницы нет!";
		return; 
	}
	cout << "\n# Название | Страна | Длительность | Цена" << endl;

	for (int i = 10*page-10; i < (page*10); i++) {
		string title = tours[i].getTitle();

		int max_length = 20;
		if (title.size() > max_length) {
			title.erase(max_length, title.size()-1);
			title += "...";
		}
		cout << tours[i].getId() << ") " << title << " |" << tours[i].getLocation() << " |" << tours[i].getDuration() << " |" << tours[i].getPrice() << endl;
	}
	return;
	// cout << "Длина массива: " << length << endl;
	// cout << "Количество страниц: " << max_page << endl;
}


void loadDataFromFile(vector<Tour>& tours, string filename) {
	fstream fin;
   	fin.open(filename, ios_base::in);
	if (!fin.is_open()) {
    	cout << "Указанный файл не существует..." << endl;
		return;
	}
    
    cout << "Файл открыт успешно!" << endl;
	
	int num = 1;
	string line;
    while (getline(fin, line)) {
		string token;
		vector<string> row;
		size_t pos;
		
		while ((pos = line.find(';')) != string::npos) {
			token = line.substr(0, pos);
			row.push_back(token);
			line.erase(0, pos + 1);
		}
		
		tours.push_back(Tour(num, row[0], row[1], row[2], row[3]));
		num++;
	}

	fin.close();
}

void changeData(vector<Tour>& tours) {
	int num;
	cout << "\nВведите номер тура, который хотите изменить: ";
	if (cin >> num) {
		if (num > tours.size()) {
			cout << "\nУказанный номер не существует...";
			return;
		}
	}
	else {
		cout << "\nНекорректный ввод!" << endl;
		cin.clear();
		cin.ignore();
		return;
	}

	int choice;
	do {
		cout << "\nЧто вы хотите изменить:\n" << "1. Название\n" << "2. Локация\n" << "3. Длительность\n" << "4. Цена\n" << "5. Выход\n" << endl; 
		if (!(cin >> choice)) {
			cout << "\nНекорректный ввод! Введите число от 1 до 5!" << endl;
			cin.clear();
			continue;
		}
		
		switch (choice) {
			case 1:
				{
					string title;
					cout << "\nВведите новое название: ";
					cin.ignore();
					getline(cin, title);
					tours[num-1].changeTitle(title);
					break;
				}
			case 2:
				{
					string loc;
					cout << "\nВведите новую локацию: ";
					cin.ignore();
					getline(cin, loc);
					tours[num-1].changeLocation(loc);
					break;
				}
			case 3:
				{
					string duration;
					cout << "\nВведите новую длительность: ";
					cin.ignore();
					getline(cin, duration);
					tours[num-1].changeDuration(duration);
					break;
				}
			case 4:
				{
					string price;
					cout << "\nВведите новую цену: ";
					cin.ignore();
					getline(cin, price);
					tours[num-1].changePrice(price);
					break;
				}
			default:
				cout << "Введите число от 1 до 5";
				break;
		}
	}	while (choice != 5);
		cout << endl;
		return;
}


void saveDataToFile(vector<Tour>& tours) {
	string filename;
	cout << "Введите название файла: ";
	cin >> filename;

	ofstream outfile(filename);
	
	for (int i = 0; i < tours.size(); i++) {
		outfile << tours[i].getId() << "; " << tours[i].getTitle() << "; " << tours[i].getLocation() << "; " << tours[i].getDuration() << "; " << tours[i].getPrice() << "; " << endl;
	}
		
	outfile.close();
	cout << "Файл успешно сохранен!" << endl;

	return;
}

int main() {
    vector<Tour> tours;
    
	string filename;
    cout << "Введите название файла с данными: ";
    cin >> filename;
	loadDataFromFile(tours, filename);

	if (tours.size() == 0) {
		return 0;
	}
	
	int choice;
    do {
		cout << "\n-----------------------" << endl;
		cout << "Список действий:\n" << "1. Просмотреть данные\n" << "2. Изменить данные\n" << "3. Сохранить файл\n" << "4. Выйти\n" << endl;

		if (!(cin >> choice)) {
			cout << "\nНекорректный ввод! Попробуйте ещё раз!" << endl;
			cin.clear();
			cin.ignore();
			continue;
		}
		
		switch(choice) { 
			case 1:
				showData(tours);
				break;
			case 2:
				changeData(tours);
				break;
			case 3:
				saveDataToFile(tours);
				break;
			default:
				cout << "\nВведите число от 1 до 4" << endl;
		}
	}
	while (choice != 4);
	
	tours.clear();
    return 0;
}
		
		
		
		
		
		
