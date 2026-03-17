#include <iostream>
#include <fstream>

const unsigned N = 100;

class StringStream
{
private:

    char mark; char A[N + 1];

    /// <summary>
    /// Функция вывода пустоты в файл out.txt
    /// </summary>
    /// <param name="text"> - сообщение</param>
    /// <param name="c"> - символ на вывод</param>
    void outp(const char* text, char c)
    {
        std::ofstream file("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::app);
        file << text << c << std::endl;

        file.close();
    }

    /// <summary>
    /// Функция вывода строки в файл out.txt
    /// </summary>
    /// <param name="text"> - сообщение</param>
    /// <param name="c"> - символ на вывод</param>
    void output(const char* text, char c)
    {
        std::ofstream file("out.txt", std::ios::app);

        if (A != "") {
            file << text;
            for (int i = 0; i < 100; i++) {
                if (A[i] == '\0') {
                    file << std::endl;
                    file.close();
                    break;
                }
                file << A[i];
            }
            file << std::endl;
        }

        file.close();
    }

    /// <summary>
    /// Перемещает символы в строке
    /// </summary>
    /// <param name="a"> - структура {маркер ; строка с маркером} </param>
    /// <param name="len"> - изначальная позиция маркера </param>
    void swap(int len)
    {
        char temp = A[0];
        for (int i = 0; i < len; i++) {
            A[i] = A[i + 1];
        }
        A[len] = temp;
    }

    /// <summary>
    /// Ищет изначальную позицию маркера
    /// </summary>
    /// <param name="a"> - структура {маркер ; строка с маркером} </param>
    /// <returns></returns>
    int find_pos() {
        int o_pos = 0;

        while (A[o_pos] != '\0')
        {
            if (A[o_pos] == mark) {
                return o_pos;
            }
            o_pos++;
        }
    }

    /// <summary>
    /// Основная работа программы - перемещение символов в строке
    /// </summary>
    /// <param name="a"> - структура {маркер ; строка с маркером} </param>
    /// <param name="o_pos"> - old marker position (конец строки)</param>
    /// <param name="n_pos"> - new marker position (середина строки)</param>
    void process(int o_pos, int n_pos)
    {
        int len = o_pos;
        while (o_pos != n_pos) {
            swap(len);
            o_pos--;
        }
        output("Результат : ", ' ');

    }

public:

    /// <summary>
    /// Функция ввода из файла
    /// </summary>
    /// <param name="a"> - структура {маркер ; строка с маркером} </param>
    /// <returns></returns>
    bool inp() {
        int file_num = 1;
        std::ifstream file("C:\\Users\\Анечка\\Documents\\in3.txt", std::ios::in);
        std::ofstream out("C:\\Users\\Анечка\\Documents\\out3.txt", std::ios::out);

        char stop;
        char c;

        if (!file.is_open()) {
            std::cout << "Ошибка открытия входного файла";
            return false;
        }
        if (!out.is_open()) {
            std::cout << "Ошибка открытия выходного файла";
            return false;
        }

        //читает построчно файл, считывает маркеты и ограничители, читает строки, если что-то не так, то выдает ошибки
        while (!(file.eof())) {
            char n = file_num + '0';
            outp("Cтрока №", n);


            file.get(mark);
            if (mark == '\n') {
                outp("Ошибка - пустая строка", ' ');
                file_num++;
                outp("----------------", ' ');
                continue;
            }

            file.get(stop);
            if (stop == '\n') {
                outp("Ошибка - нет ограничителя", ' ');
                file_num++;
                outp("----------------", ' ');
                continue;
            }

            unsigned i = 0;
            bool flag = false;

            while (file.get(c)) {
                if (c == stop || c == mark) break;
                if (c == '\n' || file.eof()) {
                    file_num++;
                    outp("Ошибка - в строке нет маркера и ограничителя", ' ');
                    outp("----------------", ' ');
                    flag = true;
                    break;

                }

                A[i] = c;
                i++;
                if (i > N) {
                    outp("Ошибка - в строке больше 100 символов", ' ');
                    file_num++;
                    outp("----------------", ' ');
                    flag = true;
                    break;
                }

            }

            //Пропускает остаток строки и переходит на следующую строчку
            if (flag) {
                while (file.get(c)) {
                    if (c == '\n') break;
                    if (file.eof()) return true;
                }
                continue;
            }

            if (i == 0) {
                outp("Ошибка - пустая строка", ' ');
                return 0;
            }
            if (i == N) {
                outp("В строке ровно 100 символов", ' ');
                A[i] = mark;
            }
            if (i < N) {
                A[i] = mark;
                A[i + 1] = '\0';
            }

            outp("Маркер: ", mark);
            outp("Ограничитель: ", stop);
            output("Строка: ", ' ');

            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }

            file_num++;


            int o_pos = find_pos();
            int n_pos = (find_pos()) / 2 + (find_pos()) % 2;
            process(o_pos, n_pos);

            outp("----------------", ' ');


        }
        out.close();
        file.close();
        return true;
    }

};




int main() {
    setlocale(LC_ALL, "ru");
    StringStream str;
    if (!(str.inp())) return 0;

    return 0;
}