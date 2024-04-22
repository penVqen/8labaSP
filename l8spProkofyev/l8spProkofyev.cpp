#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

// Структура для хранения данных о сорте сыра
struct Cheese {
    string brand;
    string manufacturer;
    double fatContent;
    double price;
};

// Класс, реализующий стек структур Cheese
class CheeseStack {
private:
    Cheese* stack; // Указатель для хранения стека сыров
    int capacity; // Текущая емкость стека
    int top; // Индекс вершины стека

public:
    // Конструктор
    CheeseStack(int size) {
        stack = new Cheese[size];
        capacity = size;
        top = -1;
    }

    // Деструктор
    ~CheeseStack() {
        delete[] stack;
    }

    // Добавление элемента в стек
    void push(const Cheese& cheese) {
        if (top == capacity - 1) {
            throw runtime_error("Стек переполнен");
        }
        stack[++top] = cheese;
    }

    // Извлечение элемента из стека с возвратом соответствующей информации о сорте сыра
    Cheese pop() {
        if (top == -1) {
            throw runtime_error("Стек пуст");
        }
        Cheese cheese = stack[top];
        top--;
        return cheese;
    }

    // Получение значения элемента по номеру позиции в стеке
    Cheese getCheese(int position) {
        if (position < 0 || position > top) {
            throw out_of_range("Позиция вне диапазона");
        }
        return stack[position];
    }

    // Получение текущего размера стека
    int size() {
        return top + 1;
    }

    // Запись данных о сырах в текстовый файл
    void writeToFile(const string& filename) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл для записи");
        }
        for (int i = 0; i <= top; i++) {
            file << stack[i].brand << ","
                << stack[i].manufacturer << ","
                << stack[i].fatContent << ","
                << stack[i].price << endl;
        }
        file.close();
    }

    // Подсчёт количества записей в стеке об указанной марке сыра
    int countCheesesByBrand(const string& brand) {
        int count = 0;
        for (int i = 0; i <= top; i++) {
            if (stack[i].brand == brand) {
                count++;
            }
        }
        return count;
    }

    // Получение всех элементов стека с указанным процентом жирности в виде массива
    Cheese* getCheesesByFatContent(double fatContent) {
        int count = 0;
        for (int i = 0; i <= top; i++) {
            if (stack[i].fatContent == fatContent) {
                count++;
            }
        }
        Cheese* result = new Cheese[count];
        int index = 0;
        for (int i = 0; i <= top; i++) {
            if (stack[i].fatContent == fatContent) {
                result[index++] = stack[i];
            }
        }
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        CheeseStack cheeseStack(10); // Размер стека можно изменить по необходимости

        char choice;
        do {
            Cheese cheese;
            cout << "Введите данные о сыре:" << endl;
            cout << "Марка: ";
            cin >> cheese.brand;
            cout << "Производитель: ";
            cin >> cheese.manufacturer;
            cout << "Процент жирности: ";
            cin >> cheese.fatContent;
            cout << "Цена: ";
            cin >> cheese.price;

            cheeseStack.push(cheese);

            cout << "Хотите добавить ещё сыр? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        // Ввод названия файла с клавиатуры
        string filename;
        cout << "Введите название файла для сохранения (без расширения .txt): ";
        cin >> filename;
        filename += ".txt"; // Добавление расширения файла

        // Запись данных о сырах в текстовый файл
        cheeseStack.writeToFile(filename);

        // Вывод добавленных сыров
        cout << "Добавленные сыры:" << endl;
        for (int i = 0; i < cheeseStack.size(); ++i) {
            Cheese cheese = cheeseStack.getCheese(i);
            cout << "Марка: " << cheese.brand << ", Производитель: " << cheese.manufacturer
                << ", Процент жирности: " << cheese.fatContent
                << ", Цена: " << cheese.price << endl;
        }

        // Извлечение элемента из стека
        cheeseStack.pop();
        cout << "Сыр успешно извлечен из стека." << endl;

        // Подсчёт количества записей в стеке об указанной марке сыра
        string brand;
        cout << "Введите марку сыра для подсчета: ";
        cin >> brand;
        int count = cheeseStack.countCheesesByBrand(brand);
        if (count == -1) {
            cout << "Сыров с указанной маркой не найдено." << endl;
        }
        else {
            cout << "Количество сыров с маркой \"" << brand << "\": " << count << endl;
        }

        // Получение всех элементов стека с указанным процентом жирности в виде массива
        double fatContent;
        cout << "Введите процент жирности для фильтрации сыров: ";
        cin >> fatContent;
        Cheese* filteredCheeses = cheeseStack.getCheesesByFatContent(fatContent);
        cout << "Сыры с процентом жирности " << fatContent << ":" << endl;
        for (int i = 0; i < count; i++) {
            cout << "Марка: " << filteredCheeses[i].brand << ", Производитель: " << filteredCheeses[i].manufacturer
                << ", Процент жирности: " << filteredCheeses[i].fatContent
                << ", Цена: " << filteredCheeses[i].price << endl;
        }
        delete[] filteredCheeses;

    }
    catch (const exception& e) {
        cerr << "Произошло исключение: " << e.what() << endl;
    }

    system("Pause");
    return 0;
}
