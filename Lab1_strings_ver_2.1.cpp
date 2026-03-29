﻿#include <iostream>
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

    void clear(char m) {
        mark = m;
        for (int i = 0; i <= N; i++) {
            A[i] = m;
        }
    }
};

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, const char* str, char mark_symbol) {
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

void swap(strm& a, char mark) {
    char temp = a.getChar(0);
    for (int i = 0; i < N; i++) {
        if (a.getChar(i + 1) != mark) {
            a.setChar(i, a.getChar(i + 1));
        }
        else {
            a.setChar(i, temp);
            break;
        }
    }
}

int poisk_pos(strm& a) {
    int pos = 0;
    while (a.getChar(pos) != a.getMark() && pos != N) {
        pos++;
    }
    return pos;
}

void process(strm& a) {
    int pos = poisk_pos(a);
    int pos_count = pos / 2 + pos % 2;
    for (int i = 0; i < pos_count; i++) {
        swap(a, a.getMark());
    }
    outp("Результат : ", a.getString(), a.getMark());
}

void skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '\n') break;
    }
}

bool readLine(std::ifstream& file, strm& a, int n) {
    char c = ' ';
    char stop;

    char mark;
    if (!file.get(mark)) {
        outp("Ошибка: Пустой входной файл", "", ' ');
        return false;
    }
    if (mark == '\n') {
        outp("Ошибка: Пустая строка (нет маркера)", "", ' ');
        return false;
    }
    a.setMark(mark);

    file.get(stop);
    if (stop == '\n') {
        outp("Ошибка: Нет ограничителя", "", ' ');
        return false;
    }

    outp("Маркер : ", "", a.getMark());
    outp("Ограничитель : ", "", stop);

    unsigned i = 0;

    while (file.get(c) && c != '\n') {
        if (c == stop || c == a.getMark()) {
            skipToNextLine(file);
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

int main() {
    clear_File();
    setlocale(LC_ALL, "ru");

    if (in_file_check()) return 0;
    if (out_file_check()) return 0;

    std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt");
    int lineNumber = 0;

    while (!file.eof()) {
        strm string;
        outp_n("Номер строки: ", lineNumber);

        if (readLine(file, string, lineNumber)) process(string);
        lineNumber++;

        string.clear(string.getMark());
    }

    file.close();
    return 1;
}