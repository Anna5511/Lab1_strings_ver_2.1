
#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;

class strm {
private:
    char mark;
    char A[N + 1];

public:
    strm();
    ~strm();

    char getMark() const { return mark; }
    char getChar(int i) const { return A[i]; }
    const char* getString() const { return A; }

    void setMark(char m) { mark = m; }
    void setChar(int i, char c) { A[i] = c; }

    /*void clear(char m) {
        mark = m;
        for (int i = 0; i <= N; i++) {
            A[i] = m;
        }
    }*/

    ///////////////////////////

    //void outp(const char* text, const char* str, char mark_symbol);
    //void outp_n(const char* text, int n);

    void swap(strm& a);
    int poisk_pos(strm& a);
    void process(strm& a);
    void skipToNextLine(std::ifstream& file);
    bool readLine(std::ifstream& file, strm& a, int n);

};

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, const char* str, char mark_symbol)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    if (str[0] != '\0') {
        file << text;
        for (int i = 0; i <= N; i++) {
            if (str[i] != mark_symbol) {
                file << str[i];
            }
            else {
                file << std::endl;
                break;
            }
        }
    }
    else {
        file << text << mark_symbol << std::endl;
    }
    file.close();
}

void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    if (n != 0) file << "-------------------" << std::endl;
    file << text << n << std::endl;
    file.close();
}

void strm::swap(strm& a) {

    char temp = a.getChar(0);
    for (int i = 0; i < N; i++) {
        if (a.getChar(i + 1) != a.getMark()) {
            a.setChar(i, a.getChar(i + 1));
        }
        else {
            a.setChar(i, temp);
            break;
        }
    }
}

int strm::poisk_pos(strm& a) {
    int pos = 0;
    while (a.getChar(pos) != a.getMark() && pos != N) {
        pos++;
    }return pos;
}

void strm::process(strm& a) {
    int pos = poisk_pos(a);
    int pos_count = pos / 2 + pos % 2;
    outp("Строка : ", a.getString(), a.getMark());
    for (int i = 0; i < pos_count; i++) {
        swap(a);
    }
    outp("Результат : ", a.getString(), a.getMark());
}

void strm::skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '\n') break;
    }
}

bool strm::readLine(std::ifstream& file, strm& a, int n) {
    char c = ' ';
    char stop;
    // Читаем ограничитель
    if (!file.get(stop)) {
        outp("Ошибка: Пусто", "", ' ');
        return false;
    }
    if (stop == '\n') {
        outp("Ошибка: Пусто", "", ' ');
        return false;
    }
    a.setMark(stop);

    outp("Ограничитель : ", "", a.getMark());

    // Читаем строку до ограничителя
    unsigned i = 0;

    while (file.get(c) && c != '\n') {

        if (c == stop || c == a.getMark()) {
            skipToNextLine(file);
            // Добавляем маркер в конец
            a.setChar(i, a.getMark());
            return true;
        }
        a.setChar(i, c);
        i++;
        if (i == N) {
            outp("В строке взяты первые 100 символов", "", ' ');
            skipToNextLine(file);
            break;
        }
    }
    if (i == 0) {
        outp("В строке нет символов", "", ' ');
        return false;

    }
    // Добавляем маркер в конец
    a.setChar(i, a.getMark());

    return true;
}

bool out_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\out3.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}
bool in_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt");
    if (!file.is_open()) {
        outp("Ошибка открытия входного файла", "", ' ');
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}

strm::strm() : mark('\0') {
    //конструктор
    for (int i = 0; i <= N; i++) {
        A[i] = '\0';
    }
}
strm::~strm() {
    //деструктор
}

int main()
{
    clear_File();
    setlocale(LC_ALL, "ru");
    if (in_file_check()) return 0;
    if (out_file_check()) return 0;


    std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt");
    int lineNumber = 0;

    // Основной цикл обработки
    while (!file.eof()) {
        strm string;
        outp_n("Номер строки: ", lineNumber);

        if (string.readLine(file, string, lineNumber)) string.process(string);
        lineNumber++;

        for (int i = 0; i <= N; i++) {
            string.setChar(i, string.getMark());
        }
    }

    return 1;
}