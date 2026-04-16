
#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;

class strm {
private:
    int len;
    char A[N + 1];

public:
    strm();
    ~strm();

    char getLen() const { return len; }
    char getChar(int i) const { return A[i]; }
    const char* getString() const { return A; }

    void setLen(int n) { len = n; }
    void setChar(int i, char c) { A[i] = c; }

    /*void clear(char m) {
        mark = m;
        for (int i = 0; i <= N; i++) {
            A[i] = m;
        }
    }*/

    void swap(strm& a);
    void process(strm& a);
    void skipToNextLine(std::ifstream& file);
    bool readLine(std::ifstream& file, strm& a, int n);

};

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, char symbol, strm& a) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text;
    if (symbol == ' ') {
        for (int i = 0; i < a.getLen(); i++) {
            file << a.getChar(i);
        }
    }
    else {
        file << symbol;
    }
    file << std::endl;
    file.close();
}

void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text << n << std::endl;
    file.close();
}

void outp_t(const char* text) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text;
    file << std::endl;
    file.close();
}

void strm::swap(strm& a) {
    if (a.getLen() <= 1) return;
    char temp = a.getChar(0);
    for (int i = 0; i < a.getLen() - 1; i++) {
        a.setChar(i, a.getChar(i + 1));
    }
    a.setChar(a.getLen() - 1, temp);
}

void strm::process(strm& a) {
    if (a.getLen() <= 0) return;
    int pos_count = a.getLen() / 2;
    outp_n("Количество символов в строке : ", a.getLen());
    outp_n("Сколько раз свапаем : ", pos_count);
    outp("Строка до свапа : ", ' ', a);
    for (int i = 0; i < pos_count; i++) swap(a);
    outp("Результат : ", ' ', a);
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
        outp_t("Ошибка: Пусто");
        return false;
    }
    if (stop == '\n') {
        outp_t("Ошибка: Пусто");
        return false;
    }
    
    outp("Ограничитель : ", stop, a);

    // Читаем строку до ограничителя
    unsigned i = 0;

    while (file.get(c) && c != '\n') {
        if (c == stop) {
            a.setLen(i);
            skipToNextLine(file);
            return true;
        }
        a.setChar(i, c);
        i++;
        if (i == N) {
            outp_t("В строке взяты первые 100 символов");
            a.setLen(i);
            skipToNextLine(file);
            break;
        }
    }
    if (i == 0) {
        outp_t("В строке нет символов");
        return false;

    }

    a.setLen(i);
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
        outp_t("Ошибка открытия входного файла");
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}

strm::strm() : len(0) {
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
        outp_n("-------------- Номер строки: ", lineNumber);

        if (string.readLine(file, string, lineNumber)) string.process(string);
        lineNumber++;
    }

    return 1;
}