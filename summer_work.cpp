#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

/*******************************************************************
*          Г Л О Б А Л Ь Н Ы Е     К О Н С Т А Н Т Ы               *
********************************************************************/

const char fNAME[] = "TEST1.TXT";
const int MAX_STR_LEN = 256;
const int MAX_RECORDS = 100;
const int INDFLAG_ON = true;
const int INDFLAG_OFF = false;

struct Reys
{
    string model;//модель самолета
    string bort;//борт 
    string time;//время посадки
    string airoport;//аэропорт посадки 
};

struct IndexItem
{
    int ind;          // индекс в исходном массиве
    string key;       // время (для сортировки)
    string airoport;  // аэропорт (для группировки)
};

struct ErrorRecord
{
    int lineNum;          // номер строки с ошибкой
    string originalLine;  // строка с ошибкой
    int errorCodes[5];    // массив кодов ошибок (макс 5 шт)
    int errorCount;       // количество ошибок в строке
};

/******************************************************************
*              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                 *
*******************************************************************/
string ErrCode(int code, const char* FNAME);//коды ошибок
int ReadFileWithErrors(const char* FileName, Reys Planes[], int& PlaneNumber, ErrorRecord errors[], int& errorLineCount);//считывание данных
void PrintAllErrors(ErrorRecord errors[], int errorLineCount, const char* FNAME);//вывод всех ошибок
void PrintTable(Reys* pSt, int QStud, const char* title);//вывод таблицы
void IndexSortByTime(Reys* AGroup, int NRec, IndexItem* IndexVec);//индексная сортировка по времени
void PrintGroupedByAirport(Reys* AGroup, int NRec, IndexItem* IndexVec);

bool isValidTime(const string& time);//проверка времени
bool isValidAiroport(const string& airoport);// проверка аэропорта
bool isValidbort(const string& bort);//проверка борта

const int M_MAX = 20;

/******************************************************************
*              О С Н О В Н А Я      П Р О Г Р А М М А             *
******************************************************************/
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    system("CLS");
    system("color F0");

    int NRec = 0;//количество записей
    int errorLineCount = 0;//количество строк с ошибкой

    IndexItem IndexVec[M_MAX];
    Reys AGroup[M_MAX];
    ErrorRecord errors[MAX_RECORDS];

    int result = ReadFileWithErrors(fNAME, AGroup, NRec, errors, errorLineCount);

    if (result != 0 && NRec == 0)
    {
        return 1;
    }

    // ВЫВОД ОШИБОК В НАЧАЛЕ
    if (errorLineCount > 0)
    {
        PrintAllErrors(errors, errorLineCount, fNAME);
    }
    else
    {
        cout << "\n========================================" << endl;
        cout << "Ошибок не обнаружено!" << endl;
        cout << "========================================" << endl;
    }

    // эхо-печать
    if (NRec > 0)
    {
        PrintTable(AGroup, NRec, "КОРРЕКТНЫЕ ДАННЫЕ");
    }
    else
    {
        cout << "\nНет корректных записей для обработки!" << endl;
        return 1;
    }

    // СОРТИРУЕМ ПО ВРЕМЕНИ
    IndexSortByTime(AGroup, NRec, IndexVec);


    /*// печать исходных данных после индексной сортировки
    cout << "Печать исходных данных после индексной сортировки по полю time" << endl;
    for (int i = 0; i < NRec; i++)
    {
        int idx = IndexVec[i].ind;  // берём индекс из отсортированного массива
        cout << AGroup[idx].model << " "
            << AGroup[idx].bort << " "
            << AGroup[idx].time << " "
            << AGroup[idx].airoport << endl;
    }*/
    // ВЫВОДИМ С ГРУППИРОВКОЙ ПО АЭРОПОРТАМ


    PrintGroupedByAirport(AGroup, NRec, IndexVec);

    return 0;
}

/*******************************************************************
*       Ф У Н К Ц И Я   В О З В Р А Т А   Т Е К С Т А   О Ш И Б К И
*******************************************************************/
string ErrCode(int code, const char* FNAME)
{
    switch (code)
    {
    case 1:
        return "Ошибка: не удалось открыть файл " + string(FNAME);
    case 2:
        return "Ошибка: файл " + string(FNAME) + " пустой! Нет данных для чтения";
    case 3:
        return "Ошибка: некорректный формат времени (ЧЧ:ММ)";
    case 4:
        return "Ошибка: некорректный номер аэропорта (допустимые значения: 1, 2, 3)";
    case 5:
        return "Ошибка: некорректный бортовой номер (формат: Б-XXXX, где XXXX - 4 цифры)";
    case 6:
        return "Ошибка: недостаточно полей (требуется: модель, борт, время, аэропорт)";
    case 7:
        return "Ошибка: превышен максимальный размер массива";
    case 8:
        return "Ошибка: лишние данные после 4-го поля";
    default:
        return "Неизвестная ошибка";
    }
}

/*******************************************************************
*            Ф У Н К Ц И Я   В Ы В О Д А   О Ш И Б О К              *
*******************************************************************/
void PrintAllErrors(ErrorRecord errors[], int errorLineCount, const char* FNAME)
{
    cout << "\n========================================" << endl;
    cout << "ОШИБКИ (всего строк с ошибками : " << errorLineCount << ")" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < errorLineCount; i++)
    {
        cout << "\nСтрока " << errors[i].lineNum << ": \"" << errors[i].originalLine << "\"" << endl;
        cout << "----------------------------------------" << endl;
        for (int j = 0; j < errors[i].errorCount; j++)
        {
            cout << "Ошибка: " << ErrCode(errors[i].errorCodes[j], FNAME) << endl;
        }
    }
    cout << endl;
}

/*******************************************************************
*            Ф У Н К Ц И Я   В Ы В О Д А   Т А Б Л И Ц Ы           *
*******************************************************************/
void PrintTable(Reys* pSt, int QStud, const char* title)
{
    cout << "\n" << string(90, '=') << endl;
    cout << title << endl;
    cout << string(90, '=') << endl;

    cout << left << setw(5) << "N"
        << setw(22) << "Модель самолета"
        << setw(16) << "Номер борта"
        << setw(14) << "Время посадки"
        << setw(10) << "Аэропорт" << endl;
    cout << string(90, '-') << endl;

    for (int i = 0; i < QStud; i++)
    {
        cout << left << setw(5) << i + 1
            << setw(22) << pSt[i].model
            << setw(16) << pSt[i].bort
            << setw(14) << pSt[i].time
            << setw(10) << pSt[i].airoport << endl;
        cout << string(90, '-') << endl;
    }

    //cout << string(90, '=') << endl;
}
/*void PrintTable(Reys* pSt, int QStud, const char* title)
{
    cout << title << endl;                         // вывод заголовка

    setlocale(0, "C");                             // отключение русского для псевдографики

    // Верхняя граница таблицы (увеличена ширина для времени)
    cout << char(218) << setfill(char(196)) << setw(8) << char(194)
        << setw(22) << char(194) << setw(16) << char(194)
        << setw(14) << char(194) << setw(10) << char(191) << endl;

    // Заголовки столбцов
    cout << char(179) << setfill(' ');
    setlocale(LC_ALL, "Russian");                  // включение русского
    cout << "   N   ";
    setlocale(0, "C");
    cout << char(179);
    setlocale(LC_ALL, "Russian");
    cout << "   Модель самолета   ";
    setlocale(0, "C");
    cout << char(179);
    setlocale(LC_ALL, "Russian");
    cout << "  Номер борта  ";
    setlocale(0, "C");
    cout << char(179);
    setlocale(LC_ALL, "Russian");
    cout << "Время посадки";
    setlocale(0, "C");
    cout << char(179);
    setlocale(LC_ALL, "Russian");
    cout << "Аэропорт ";
    setlocale(0, "C");
    cout << char(179) << endl;

    // Разделитель между заголовками и телом
    cout << char(195) << setfill(char(196)) << setw(8) << char(197)
        << setw(22) << char(197) << setw(16) << char(197)
        << setw(14) << char(197) << setw(10) << char(180) << endl;

    // Тело таблицы
    for (int i = 0; i < QStud; i++)                // цикл по всем строкам
    {
        // Вывод номера по порядку
        cout << char(179);
        setlocale(LC_ALL, "Russian");
        cout << " " << right << setw(3) << setfill(' ') << i + 1 << "   ";
        setlocale(0, "C");
        cout << char(179);

        // Вывод марки ЛА
        setlocale(LC_ALL, "Russian");
        cout << " " << left << setw(20) << setfill(' ') << pSt[i].model;
        setlocale(0, "C");
        cout << char(179);

        // Вывод бортового номера
        setlocale(LC_ALL, "Russian");
        cout << " " << left << setw(14) << setfill(' ') << pSt[i].bort;
        setlocale(0, "C");
        cout << char(179);

        // Вывод времени посадки
        setlocale(LC_ALL, "Russian");
        cout << " " << right << setw(12) << setfill(' ') << pSt[i].time;
        setlocale(0, "C");
        cout << char(179);

        // Вывод аэропорта
        setlocale(LC_ALL, "Russian");
        cout << " " << right << setw(6) << setfill(' ') << pSt[i].airoport << "  ";
        setlocale(0, "C");
        cout << char(179) << endl;

        // Разделитель между строками (кроме последней)
        if (i < QStud - 1)
        {
            cout << char(195) << setfill(char(196)) << setw(8) << char(197)
                << setw(22) << char(197) << setw(16) << char(197)
                << setw(14) << char(197) << setw(10) << char(180) << endl;
        }
    }

    // Нижняя граница таблицы
    cout << char(192) << setfill(char(196)) << setw(8) << char(193)
        << setw(22) << char(193) << setw(16) << char(193)
        << setw(14) << char(193) << setw(10) << char(217) << endl;

    setlocale(LC_ALL, "Russian");                  // обратное включение русского
}*/

/*void PrintTable(Reys* pSt, int QStud, const char* title)
{
    // Верхняя рамка
    cout << "\n╔════════╦════════════════════════╦══════════════════════════╦════════════╗" << endl;
    cout << "║   N    ║    Модель самолета     ║       Номер борта        ║  Аэропорт  ║" << endl;
    cout << "╠════════╬════════════════════════╬══════════════════════════╬════════════╣" << endl;

    for (int i = 0; i < QStud; i++)
    {
        cout << "║" << setw(6) << i + 1 << " ║"
            << setw(22) << pSt[i].model << " ║"
            << setw(24) << pSt[i].bort << " ║"
            << setw(8) << pSt[i].airoport << "   ║" << endl;

        // Разделитель между строками (кроме последней)
        if (i < QStud - 1)
        {
            cout << "╠════════╬════════════════════════╬══════════════════════════╬════════════╣" << endl;
        }
    }

    // Нижняя рамка
    cout << "╚════════╩════════════════════════╩══════════════════════════╩════════════╝" << endl;
}*/

/*******************************************************************
*            Ф У Н К Ц И Я   Ч Т Е Н И Я   Ф А Й Л А              *
*******************************************************************/
int ReadFileWithErrors(const char* FileName, Reys Planes[], int& PlaneNumber,
    ErrorRecord errors[], int& errorLineCount)
{
    char str[MAX_STR_LEN];
    int i, field, bw, ew;
    int lineNumber = 0;
    int validRecords = 0;
    errorLineCount = 0;
    fstream fin(FileName);

    if (!fin)
    {
        cout << ErrCode(1, FileName) << endl;
        return 1;
    }

    if (fin.eof())
    {
        cout << ErrCode(2, FileName) << endl;
        return 2;
    }

    while (fin.getline(str, MAX_STR_LEN))
    {
        i = 0;
        field = 0;
        lineNumber++;

        if (str[0] == '\0')
        {
            continue;
        }

        string fields[4];
        int errorCodes[5];
        int errCount = 0;

        // Разбор строки на поля
        while (str[i] != '\0' && field < 4)
        {
            while (str[i] == ' ' && str[i] != '\0')
            {
                i++;
            }

            bw = i;
            while (str[i] != ' ' && str[i] != '\0')
            {
                i++;
            }
            ew = i - 1;

            for (int j = bw; j <= ew; j++)
            {
                fields[field] += str[j];
            }
            field++;
        }

        // ПРОВЕРКА 1: достаточно ли полей (код 6)
        if (field != 4)
        {
            errorCodes[errCount++] = 6;
        }

        // ПРОВЕРКА 2: лишние данные после 4-го поля (код 8)
        int tempPos = i;
        while (str[tempPos] == ' ' && str[tempPos] != '\0')
        {
            tempPos++;
        }
        if (str[tempPos] != '\0' && field == 4)
        {
            errorCodes[errCount++] = 8;
        }

        // ПРОВЕРКА 3: бортовой номер (код 5)
        if (field > 1 && !isValidbort(fields[1]))
        {
            errorCodes[errCount++] = 5;
        }

        // ПРОВЕРКА 4: время (код 3)
        if (field > 2 && !isValidTime(fields[2]))
        {
            errorCodes[errCount++] = 3;
        }

        // ПРОВЕРКА 5: аэропорт (код 4)
        if (field > 3 && !isValidAiroport(fields[3]))
        {
            errorCodes[errCount++] = 4;
        }

        // Если есть ошибки — сохраняем
        if (errCount > 0)
        {
            errors[errorLineCount].lineNum = lineNumber;
            errors[errorLineCount].originalLine = str;
            errors[errorLineCount].errorCount = errCount;
            for (int e = 0; e < errCount; e++)
            {
                errors[errorLineCount].errorCodes[e] = errorCodes[e];
            }
            errorLineCount++;
            continue;
        }

        // Корректная записть
        Planes[PlaneNumber].model = fields[0];
        Planes[PlaneNumber].bort = fields[1];
        Planes[PlaneNumber].time = fields[2];
        Planes[PlaneNumber].airoport = fields[3];
        PlaneNumber++;
        validRecords++;
    }

    fin.close();

    cout << "\nВсего обработано строк: " << lineNumber << endl;
    cout << "Считано корректных записей: " << validRecords << endl;
    cout << "Строк с ошибками: " << errorLineCount << endl;

    return 0;
}

/*******************************************************************
*            Ф У Н К Ц И И   П Р О В Е Р К И                      *
*******************************************************************/
bool isValidTime(const string& time)
{
    if (time.length() != 5)
    {
        return false;
    }
    if (time[2] != ':')
    {
        return false;
    }

    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;
        }

        if (time[i] < '0' || time[i] > '9')
        {
            return false;
        }
    }

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    if (hours < 0 || hours > 23)
    {
        return false;
    }

    if (minutes < 0 || minutes > 59)
    {
        return false;
    }

    return true;
}

bool isValidAiroport(const string& airoport)
{
    return (airoport == "1" || airoport == "2" || airoport == "3");
}

bool isValidbort(const string& bort)
{
    if (bort.length() != 6)
    {
        return false;
    }

    if (bort[1] != '-')
    {
        return false;
    }
    if (bort[0] != 'Б')
    {
        return false;
    }
    for (int i = 2; i < 6; i++)
    {
        if (bort[i] < '0' || bort[i] > '9')
        {
            return false;
        }
    }

    return true;
}

/*******************************************************************
*            И Н Д Е К С Н А Я   С О Р Т И Р О В К А               *
*******************************************************************/
void IndexSortByTime(Reys* AGroup, int NRec, IndexItem* IndexVec)
{
    // Заполняем индексный массив
    for (int i = 0; i < NRec; i++)
    {
        IndexVec[i].ind = i;
        IndexVec[i].key = AGroup[i].time;
        IndexVec[i].airoport = AGroup[i].airoport;
    }

    // Сортировка по времени (убывание)
    for (int i = 0; i < NRec - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < NRec; j++)
        {
            if (IndexVec[j].key > IndexVec[maxIndex].key)
            {
                maxIndex = j;
            }
        }
        if (maxIndex != i)
        {
            IndexItem temp = IndexVec[i];
            IndexVec[i] = IndexVec[maxIndex];
            IndexVec[maxIndex] = temp;
        }
    }
}

/*******************************************************************
*            В Ы В О Д   С   Г Р У П П И Р О В К О Й               *
*******************************************************************/
void PrintGroupedByAirport(Reys* AGroup, int NRec, IndexItem* IndexVec)
{
    if (NRec == 0) return;

    // Проходим по всем аэропортам от 1 до 3
    for (int airport = 1; airport <= 3; airport++)
    {
        string airportStr = to_string(airport);
        bool hasFlights = false;
        int flightCount = 0;

        // Считаем количество рейсов в этом аэропорту
        for (int i = 0; i < NRec; i++)
        {
            int idx = IndexVec[i].ind;
            if (AGroup[idx].airoport == airportStr)
            {
                hasFlights = true;
                flightCount++;
            }
        }

        // Заголовок аэропорта
        cout << "\n" << string(90, '=') << endl;
        cout << "АЭРОПОРТ " << airport << " (всего рейсов: " << flightCount << ")" << endl;
        cout << string(90, '=') << endl;

        if (!hasFlights)
        {
            cout << "Нет рейсов, зарегистрированных на этот аэропорт" << endl;
            cout << string(90, '=') << endl;
            continue;
        }

        // Шапка таблицы
        cout << left << setw(5) << "N"
            << setw(22) << "Модель самолета"
            << setw(16) << "Номер борта"
            << setw(14) << "Время посадки"
            << setw(10) << "Аэропорт" << endl;
        cout << string(90, '-') << endl;

        // Выводим рейсы этого аэропорта
        int counter = 1;
        for (int i = 0; i < NRec; i++)
        {
            int idx = IndexVec[i].ind;
            if (AGroup[idx].airoport == airportStr)
            {
                cout << left << setw(5) << counter++
                    << setw(22) << AGroup[idx].model
                    << setw(16) << AGroup[idx].bort
                    << setw(14) << AGroup[idx].time
                    << setw(10) << AGroup[idx].airoport << endl;
                cout << string(90, '-') << endl;

            }
        }
        //cout << string(90, '=') << endl;
    }
}
/*void PrintGroupedByAirport(Reys* AGroup, int NRec, IndexItem* IndexVec)
{
    if (NRec == 0) return;

    for (int airport = 1; airport <= 3; airport++)
    {
        string airportStr = to_string(airport);
        bool hasFlights = false;
        int flightCount = 0;

        // Считаем количество рейсов в этом аэропорту
        for (int i = 0; i < NRec; i++)
        {
            int idx = IndexVec[i].ind;
            if (AGroup[idx].airoport == airportStr)
            {
                hasFlights = true;
                flightCount++;
            }
        }

        // Заголовок аэропорта
        setlocale(LC_ALL, "Russian");
        cout << "\n\n                         АЭРОПОРТ " << airport << " (всего рейсов: " << flightCount << ")" << endl;
        setlocale(0, "C");

        if (!hasFlights)
        {
            setlocale(LC_ALL, "Russian");
            cout << "                   Нет рейсов, зарегистрированных на этот аэропорт" << endl;
            setlocale(0, "C");
            continue;
        }

        // Верхняя граница таблицы
        cout << char(218) << setfill(char(196)) << setw(8) << char(194)
            << setw(24) << char(194) << setw(16) << char(194)
            << setw(14) << char(194) << setw(12) << char(191) << endl;

        // Заголовки столбцов
        cout << char(179) << setfill(' ');
        setlocale(LC_ALL, "Russian");
        cout << "   N   ";
        setlocale(0, "C");
        cout << char(179);
        setlocale(LC_ALL, "Russian");
        cout << "    Модель самолета    ";
        setlocale(0, "C");
        cout << char(179);
        setlocale(LC_ALL, "Russian");
        cout << "  Номер борта  ";
        setlocale(0, "C");
        cout << char(179);
        setlocale(LC_ALL, "Russian");
        cout << "Время посадки";
        setlocale(0, "C");
        cout << char(179);
        setlocale(LC_ALL, "Russian");
        cout << " Аэропорт  ";
        setlocale(0, "C");
        cout << char(179) << endl;

        // Разделитель между заголовками и телом
        cout << char(195) << setfill(char(196)) << setw(8) << char(197)
            << setw(24) << char(197) << setw(16) << char(197)
            << setw(14) << char(197) << setw(12) << char(180) << endl;

        // Выводим рейсы этого аэропорта
        int counter = 1;
        int lastIndex = -1;

        // Находим последний индекс для этого аэропорта
        for (int i = NRec - 1; i >= 0; i--)
        {
            int idx = IndexVec[i].ind;
            if (AGroup[idx].airoport == airportStr)
            {
                lastIndex = i;
                break;
            }
        }

        for (int i = 0; i < NRec; i++)
        {
            int idx = IndexVec[i].ind;
            if (AGroup[idx].airoport == airportStr)
            {
                // Вывод номера по порядку
                cout << char(179);
                setlocale(LC_ALL, "Russian");
                cout << " " << right << setw(3) << setfill(' ') << counter++ << "   ";
                setlocale(0, "C");
                cout << char(179);

                // Вывод марки ЛА
                setlocale(LC_ALL, "Russian");
                cout << " " << left << setw(22) << setfill(' ') << AGroup[idx].model;
                setlocale(0, "C");
                cout << char(179);

                // Вывод бортового номера
                setlocale(LC_ALL, "Russian");
                cout << " " << left << setw(14) << setfill(' ') << AGroup[idx].bort;
                setlocale(0, "C");
                cout << char(179);

                // Вывод времени посадки
                setlocale(LC_ALL, "Russian");
                cout << " " << right << setw(12) << setfill(' ') << AGroup[idx].time;
                setlocale(0, "C");
                cout << char(179);

                // Вывод аэропорта
                setlocale(LC_ALL, "Russian");
                cout << "   " << right << setw(4) << setfill(' ') << AGroup[idx].airoport << "    ";
                setlocale(0, "C");
                cout << char(179) << endl;

                // Разделитель между строками (кроме последней)
                if (i != lastIndex)
                {
                    cout << char(195) << setfill(char(196)) << setw(8) << char(197)
                        << setw(24) << char(197) << setw(16) << char(197)
                        << setw(14) << char(197) << setw(12) << char(180) << endl;
                }
            }
        }

        // Нижняя граница таблицы
        cout << char(192) << setfill(char(196)) << setw(8) << char(193)
            << setw(24) << char(193) << setw(16) << char(193)
            << setw(14) << char(193) << setw(12) << char(217) << endl;
    }

    setlocale(LC_ALL, "Russian");
}*/