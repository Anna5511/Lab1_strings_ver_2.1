// ============================================================================
// Программа обработки строк с маркерами
// Формат: <маркер><число><содержимое>[<маркер>][\n]
// ============================================================================

#include <iostream>
#include <fstream>

const unsigned N = 100;

// ============================================================================
// 🔹 КЛАСС strm
// ============================================================================
class strm {
private:
    char mark;
    char A[N + 1];

public:
    strm() : mark('\0') { A[0] = '\0'; }

    // 🔹 Метод очистки объекта
    void clear() {
        mark = '\0';
        A[0] = '\0';
    }

    char get_mark() const { return mark; }
    void set_mark(char m) { mark = m; }
    char get_A(unsigned idx) const { return (idx <= N) ? A[idx] : '\0'; }
    void set_A(unsigned idx, char c) { if (idx <= N) A[idx] = c; }
    void set_A_null(unsigned idx) { if (idx <= N) A[idx] = '\0'; }
    const char* get_A_ptr() const { return A; }
};

// ============================================================================
// 🔹 Функция вывода
// ============================================================================
void outp(const char* text, const strm& str, char c)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    const char* data = str.get_A_ptr();

    // 🔹 Проверяем, что строка не пустая (первый символ '\0')
    if (data[0] != '\0') {
        file << text;
        for (int i = 0; i <= N; i++) {
            if (data[i] == '\0') {
                file << std::endl;
                file.close();
                return;
            }
            file << data[i];
        }
        file << std::endl;
    }
    else {
        // 🔹 Пустая строка — выводим только текст и символ
        file << text << c << std::endl;
    }
    file.close();
}

// ============================================================================
// 🔹 Функция swap
// ============================================================================
void swap(strm& a, int len)
{
    char temp = a.get_A(0);
    for (int i = 0; i < len; i++) { a.set_A(i, a.get_A(i + 1)); }
    a.set_A(len, temp);
}

// ============================================================================
// 🔹 Функция poisk_pos
// ============================================================================
int poisk_pos(strm& a) {
    for (int i = 0; i <= N; i++) {
        if (a.get_A(i) == '\0') break;
        if (a.get_A(i) == a.get_mark()) return i;
    }
    return -1;
}

// ============================================================================
// 🔹 Функция process
// ============================================================================
void process(strm& a, int o_pos, int n_pos)
{
    int len = o_pos;
    while (o_pos != n_pos) { swap(a, len); o_pos--; }
    outp("Результат : ", a, ' ');
}

// ============================================================================
// 🔹 Вспомогательная: вывод числа в файл
// ============================================================================
void outp_num(const char* text, int num) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text << num << std::endl;
    file.close();
}

// ============================================================================
// 🔹 Функция inp — ИСПРАВЛЕННАЯ ВЕРСИЯ
// ============================================================================
bool inp(strm& a) {
    // Очищаем выходной файл перед записью
    { std::ofstream clear("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::trunc); clear.close(); }

    std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt", std::ios::in);
    if (!file.is_open()) { std::cout << "Ошибка открытия входного файла"; return false; }

    int file_num = 1;
    char ch;

    while (true) {
        // 🔹 Читаем первый непустой символ — это маркер
        if (!file.get(ch)) break;
        if (ch == '\n' || ch == '\r') continue;

        // 🔹 ВАЖНО: Очищаем объект перед новой строкой!
        a.clear();

        char n = file_num + '0';
        outp("Cтрока №", a, n);

        a.set_mark(ch);

        // 🔹 Читаем число после маркера
        int expected_len = 0;
        bool has_digit = false;
        bool is_negative = false;

        if (file.peek() == '-') {
            file.get(ch);
            is_negative = true;
        }

        while (file.peek() >= '0' && file.peek() <= '9') {
            file.get(ch);
            expected_len = expected_len * 10 + (ch - '0');
            has_digit = true;
        }

        if (!has_digit) {
            outp("Ошибка: нет числа", a, ' ');
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp("----------------", a, ' ');
            continue;
        }

        if (is_negative) {
            outp("Ошибка: неверное число (отрицательное значение)", a, ' ');
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp("----------------", a, ' ');
            continue;
        }

        if (expected_len > 100) {
            outp("Ошибка: число > 100", a, ' ');
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp("----------------", a, ' ');
            continue;
        }

        // 🔹 Читаем содержимое: до expected_len символов ИЛИ до конца строки
        unsigned actual_len = 0;
        bool has_extra = false;

        while (actual_len < (unsigned)expected_len && file.get(ch)) {
            if (ch == '\n' || ch == '\r') break;
            if (actual_len < N) {
                a.set_A(actual_len, ch);
            }
            actual_len++;
            if (ch == a.get_mark()) break;
        }

        // 🔹 ПРОВЕРКА: есть ли ещё символы до конца строки?
        if (actual_len == (unsigned)expected_len) {
            char next_ch;
            while (file.get(next_ch)) {
                if (next_ch == '\n' || next_ch == '\r') break;
                has_extra = true;
            }
        }
        else {
            while (file.get(ch)) { if (ch == '\n' || ch == '\r') break; }
        }

        if (actual_len > N) actual_len = N;
        a.set_A_null(actual_len);

        // 🔹 Вывод служебной информации
        if (has_extra) {
            outp("Ошибка - в строке больше 100 символов", a, ' ');
            file_num++;
            outp("----------------", a, ' ');
            continue;
        }

        if (actual_len < (unsigned)expected_len) {
            outp("В строке символов меньше нужного, так что считываем все", a, ' ');
        }
        else if (actual_len > (unsigned)expected_len) {
            outp("В строке символов больше нужного", a, ' ');
        }
        else if (actual_len == N) {
            outp("В строке ровно 100 символов", a, ' ');
        }

        outp("Маркер: ", a, a.get_mark());
        outp_num("Длина считываемой строки: ", expected_len);
        outp("Строка: ", a, ' ');

        file_num++;

        // 🔹 Обработка: поиск маркера и сдвиг
        int o_pos = poisk_pos(a);
        if (o_pos == -1) {
            outp("Ошибка: маркер не найден в строке", a, ' ');
            outp("----------------", a, ' ');
            continue;
        }

        int n_pos = o_pos / 2 + o_pos % 2;
        process(a, o_pos, n_pos);
        outp("----------------", a, ' ');
    }

    file.close();
    return true;
}

// ============================================================================
// 🔹 main
// ============================================================================
int main() {
    setlocale(LC_ALL, "ru");
    strm data;
    if (!inp(data)) return 0;
    return 0;
}