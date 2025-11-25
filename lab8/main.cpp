// вариант 2
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct Book {
    string author;
    string name;
    unsigned int tome_number;
    unsigned int pages;
    Book* next;
};

Book* Make(Book* head, string author, string name, unsigned int tome_number, unsigned int pages) {
    Book* book = new Book;
    book->author = author;
    book->name = name;
    book->tome_number = tome_number;
    book->pages = pages;
    return book;
}

void Put(Book* head, string author, string name, unsigned int tome_number, unsigned int pages) {
    
    Book* book = Make(head, author, name, tome_number, pages);
    Book* headref = head;

    if ((headref->next == nullptr)) {
        book->next = headref->next;
        headref->next = book;
        return;
    }
    while ((headref->next != nullptr) && (headref->next->author != author)) {
        headref = headref->next;
    }
    while ((headref->next != nullptr) && (headref->next->name != name)) {
        headref = headref->next;
    }
    while ((headref->next != nullptr) && (headref->next->tome_number < tome_number)) {
        headref = headref->next;
    }

    book->next = headref->next;
    headref->next = book;
}

void Print(Book* head) {
    Book* printer = head;
    while (printer->next != nullptr) {
        printer = printer->next;
        cout << printer->author << " \"" << printer->name << "\", " << "Том " << printer->tome_number << ", " << printer->pages << " стр." << endl;
        
    }
}

void PrintSingle(Book* head, int element) {
    Book* printer = head;
    for (int i = 0; i <= element; ++i) {
        if (printer->next == nullptr)
            break;
        printer = printer->next;
        if (i != element)
            continue;
        cout << printer->author << " \"" << printer->name << "\", " << "Том " << printer->tome_number << ", " << printer->pages << " стр." << endl;
        return;
    }
    cout << "Этого элемента ещё не существует." << endl;
}

void SeekForHardest(Book* head, string author) {
    Book* seeker = head;
    int selected_id = -1;
    int selected_pages = -1;
    for (int i = 0; seeker->next != nullptr; ++i) {\
        seeker = seeker->next;
    if ((seeker->author == author) && ((int)seeker->pages > selected_pages)) {
        selected_id = i;
        selected_pages = seeker->pages;
        }
    }
    if (selected_id == -1) {
        cout << "Книги автора не найдены." << endl;
        return;
    }
    PrintSingle(head, selected_id);
}

void SeekForEasiest(Book* head, string author) {
    Book* seeker = head;
    int selected_id = -1;
    unsigned int selected_pages = (pow(2,32))-1;
    for (int i = 0; seeker->next != nullptr; ++i) {
            seeker = seeker->next;
        if ((seeker->author == author) && (seeker->pages < selected_pages)) {
            selected_id = i;
            selected_pages = seeker->pages;
        }
    }
    if (selected_id == -1) {
        cout << "Книги автора не найдены." << endl;
        return;
    }
    PrintSingle(head, selected_id);
}

void MenuCallView(Book* head) {
    int element;
    cout << "Введите номер элемента (введите -1 для вывода всего): ";
    cin >> element;
    if (element == -1) {
        Print(head);
        return;
    }
    PrintSingle(head, element);
}

void MenuCallAdd(Book* head) {
    string author;
    string name;
    unsigned int tome_number;
    unsigned int pages;
    cout << "Введите автора: ";
    cin >> author;
    cout << "Введите название: ";
    cin >> name;
    cout << "Введите том: ";
    cin >> tome_number;
    cout << "Введите кол-во страниц: ";
    cin >> pages;
    Put(head, author, name, tome_number, pages);
    cout << endl << "Элемент помещён!" << endl << endl;
}

void MenuCallSeekFor(Book* head) {
    bool type;
    string author;
    cout << "Введите автора: ";
    cin >> author;
    cout << "Сложный (1) или лёгкий (0)?" << endl;
    cin >> type;
    (type == 1 ? SeekForHardest(head, author) : SeekForEasiest(head, author));
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    Book library;
    library.next = nullptr;

    Book summer;
    summer.next = nullptr;
    short input;
    
    while (true) {
        cout << endl << "- - - Книжник - - -" << endl << endl
            << "1. Просмотр элемента." << endl
            << "2. Создание и помещение нового элемента." << endl
            << "3. Поиск самого сложного/лёгкого текста автора." << endl
            << "4. Сборка очереди на лето." << endl
            << endl << "Ввод: ";
        cin >> input;
        switch (input) {
        case 1:
            MenuCallView(&library);
            break;
        case 2:
            MenuCallAdd(&library);
            break;
        case 3:
            MenuCallSeekFor(&library);
            break;
        case 4:
            break;
        default:
            cout << "Неизвестное значение." << endl;
            break;
        }

    }
}
