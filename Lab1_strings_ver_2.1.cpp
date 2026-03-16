// ============================================================================
// Программа обработки строк с маркерами
// ============================================================================

#include <iostream>
#include <fstream>

const unsigned N = 100;

class strm {
private:
    char mark;
    char A[N + 1];

public:
    strm() : mark('\0') { A[0] = '\0'; }

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
// 🔹 Функция вывода — ИСПРАВЛЕНА
// ============================================================================
void outp(const char* text, const strm& str, char c)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    const char* data = str.get_A_ptr();

    // 🔹 Если массив пустой — выводим текст + символ c
    if (data[0] == '\0') {
        file << text << c << std::endl;
    }
    // 🔹 Если массив не пустой — выводим текст + содержимое массива
    else {
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
    file.close();
}

// ============================================================================
// 🔹 Вывод только текста (без объекта и символа)
// ============================================================================
void outp_text(const char* text) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text << std::endl;
    file.close();
}

// ============================================================================
// 🔹 Вывод числа в файл
// ============================================================================
void outp_num(const char* text, int num) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
    file << text << num << std::endl;
    file.close();
}

// ============================================================================
// 🔹 swap
// ============================================================================
void swap(strm& a, int len)
{
    char temp = a.get_A(0);
    for (int i = 0; i < len; i++) { a.set_A(i, a.get_A(i + 1)); }
    a.set_A(len, temp);
}

// ============================================================================
// 🔹 poisk_pos
// ============================================================================
int poisk_pos(strm& a) {
    for (int i = 0; i <= N; i++) {
        if (a.get_A(i) == '\0') break;
        if (a.get_A(i) == a.get_mark()) return i;
    }
    return -1;
}

// ============================================================================
// 🔹 process
// ============================================================================
void process(strm& a, int o_pos, int n_pos)
{
    int len = o_pos;
    while (o_pos != n_pos) { swap(a, len); o_pos--; }
    outp("Результат : ", a, ' ');
}

// ============================================================================
// 🔹 inp — ИСПРАВЛЕННАЯ ВЕРСИЯ
// ============================================================================
bool inp(strm& a) {
    { std::ofstream clear("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::trunc); clear.close(); }

    std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt", std::ios::in);
    if (!file.is_open()) { std::cout << "Ошибка открытия входного файла"; return false; }

    int file_num = 1;
    char ch;

    while (true) {
        if (!file.get(ch)) break;
        if (ch == '\n' || ch == '\r') continue;

        a.clear();

        char n = file_num + '0';
        outp_text("Cтрока №");
        outp_num("", file_num);

        a.set_mark(ch);

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
            outp_text("Ошибка: нет числа");
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp_text("----------------");
            continue;
        }

        if (is_negative) {
            outp_text("Ошибка: неверное число (отрицательное значение)");
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp_text("----------------");
            continue;
        }

        if (expected_len > 100) {
            outp_text("Ошибка: число > 100");
            while (file.get(ch) && ch != '\n' && ch != '\r');
            file_num++;
            outp_text("----------------");
            continue;
        }

        unsigned actual_len = 0;
        bool ended_by_marker = false;

        // 🔹 Читаем содержимое
        while (actual_len < (unsigned)expected_len && file.get(ch)) {
            if (ch == '\n' || ch == '\r') break;
            if (actual_len < N) {
                a.set_A(actual_len, ch);
            }
            actual_len++;
            if (ch == a.get_mark()) {
                ended_by_marker = true;
                break;
            }
        }

        // 🔹 Проверяем, есть ли лишние символы ПОСЛЕ закрывающего маркера
        bool has_extra = false;
        if (!ended_by_marker && actual_len == (unsigned)expected_len) {
            char next_ch;
            while (file.get(next_ch)) {
                if (next_ch == '\n' || next_ch == '\r') break;
                if (next_ch != a.get_mark()) {  // 🔹 Только если это не закрывающий маркер
                    has_extra = true;
                }
            }
        }
        else if (!ended_by_marker) {
            while (file.get(ch)) { if (ch == '\n' || ch == '\r') break; }
        }

        if (actual_len > N) actual_len = N;
        a.set_A_null(actual_len);

        strm empty;  // 🔹 Пустой объект для сообщений без данных

        if (has_extra) {
            outp_text("Ошибка - в строке больше 100 символов");
            file_num++;
            outp_text("----------------");
            continue;
        }

        if (actual_len < (unsigned)expected_len) {
            outp_text("В строке символов меньше нужного, так что считываем все");
        }
        else if (actual_len > (unsigned)expected_len) {
            outp_text("В строке символов больше нужного");
        }
        else if (actual_len == N) {
            outp_text("В строке ровно 100 символов");
        }

        // 🔹 Вывод маркера — используем outp с пустым объектом и символом mark
        outp("Маркер: ", empty, a.get_mark());
        outp_num("Длина считываемой строки: ", expected_len);
        outp("Строка: ", a, ' ');

        file_num++;

        int o_pos = poisk_pos(a);
        if (o_pos == -1) {
            outp_text("Ошибка: маркер не найден в строке");
            outp_text("----------------");
            continue;
        }

        int n_pos = o_pos / 2 + o_pos % 2;
        process(a, o_pos, n_pos);

        a.clear();
        outp_text("----------------");
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