
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>

class RimNumber;
inline void Paste(std::wstring& rim, std::wstring ch, int count = 1);
inline wchar_t GetChar(std::wstring mes);
double GetNumber(std::wstring s);
inline wchar_t GetOperator(std::wstring mes);
RimNumber Calculate(RimNumber rim1, RimNumber rim2, wchar_t operation);

class RimNumber
{

private:
    std::wstring rim;
    double arabNumb;
    int RimToArab(std::wstring rim)
    {
        if (rim.length() == 1 && std::toupper(rim[0]) == L'N')
        {
            return 0;
        }
        int num = 0, countI = 0, countV = 0, countX = 0, countL = 0, countC = 0, countD = 0, countM = 0, countIV = 0,
            countIX = 0, countXL = 0, countXC = 0, countCD = 0, countCM = 0;
        for (int i = 0, length = rim.length(); i < length; i++)
        {

            switch (std::toupper(rim[i]))
            {
            case (L'-'):
            {
                break;
            }
            case (L'I'):
            {
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'V')
                {
                    num -= 2;
                    countI--;
                    countIV++;
                }
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'X')
                {
                    num -= 2;
                    countI--;
                    countIX++;
                }
                if (i + 1 < length && (std::toupper(rim[i + 1]) == L'L' || std::toupper(rim[i + 1]) == L'C' || std::toupper(rim[i + 1]) == L'D' || std::toupper(rim[i + 1]) == L'M'))
                {
                    return -1;
                }
                num += 1;
                countI++;
                break;
            }
            case (L'V'):
            {
                if (i + 1 < length && (std::toupper(rim[i + 1]) == 'X' || std::toupper(rim[i + 1]) == 'L' || std::toupper(rim[i + 1]) == 'C' || std::toupper(rim[i + 1]) == 'D' || std::toupper(rim[i + 1]) == 'M'))
                {
                    return -1;
                }
                num += 5;
                countV++;
                break;
            }
            case (L'X'):
            {
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'L')
                {
                    num -= 20;
                    countX--;
                    countXL++;
                }
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'C')
                {
                    num -= 20;
                    countX--;
                    countXC++;
                }
                if (i + 1 < length && (std::toupper(rim[i + 1]) == L'D' || std::toupper(rim[i + 1]) == L'M'))
                {
                    return -1;
                }
                num += 10;
                countX++;
                break;
            }
            case (L'L'):
            {
                if (i + 1 < length && (std::toupper(rim[i + 1]) == L'C' || std::toupper(rim[i + 1]) == L'D' || std::toupper(rim[i + 1]) == L'M'))
                {
                    return -1;
                }
                num += 50;
                countL++;
                break;
            }
            case (L'C'):
            {
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'D')
                {
                    num -= 200;
                    countC--;
                    countCD++;
                }
                if (i + 1 < length && std::toupper(rim[i + 1]) == L'M')
                {
                    num -= 200;
                    countC--;
                    countCM++;
                }
                num += 100;
                countC++;
                break;
            }
            case (L'D'):
            {
                num += 500;
                countD++;
                break;
            }
            case (L'M'):
            {
                num += 1000;
                countM++;
                break;
            }
            default:
                return -1;
                break;
            }
        }
        //проверка правил построения римского числа: меньшие числа не стоят перед большими кроме особого случая когда число предыдущего разряда
        // вычитается, нет ситуаций когда из числа сначала вычли единицу, а потом добавили.
        //
        if (countI > 3 || countV > 1 || countX > 3 || countL > 1 || countC > 3 || countD > 1 || countM > 3 ||
            countIV > 1 || countIX > 1 || countXL > 1 || countXC > 1 || countCD > 1 || countCM > 1 ||
            (countIV == 1 && countIX == 1) || (countIV == 0 && countIX == 1 && countV > 0) ||
            (countXL == 1 && countXC == 1) || (countXL == 0 && countXC == 1 && countL > 0) ||
            (countCD == 1 && countCM == 1) || (countCD == 0 && countCM == 1 && countD > 0) ||
            (countIX == 1 && countI > 0) || (countIV == 1 && countI > 0) ||
            (countXC == 1 && countX > 0) || (countXL == 1 && countXC > 0) ||
            (countCM == 1 && countC > 0) || (countCD == 1 && countC > 0))
        {
            return -1;
        }
        return num;
    }
    std::wstring FractionToRim(double num)
    {
        std::wstring answer = L"";
        while (num >= 1.0 / 1728)
        {
            if ((num - 1.0 / 2) >= 0)
            {
                Paste(answer, L"S");
                num -= 1.0 / 2;
            }
            else if ((num - 1.0 / 6) >= 0)
            {
                Paste(answer, L"\u2022");
                num -= 1.0 / 6;
            }
            else if ((num - 1.0 / 8) >= 0)
            {
                Paste(answer, L"f");
                num -= 1.0 / 8;
            }
            else if ((num - 1.0 / 24) >= 0)
            {
                Paste(answer, L"\u03A3");
                num -= 1.0 / 24;
            }
            else if ((num - 1.0 / 36) >= 0)
            {
                Paste(answer, L"\u01A7");
                num -= 1.0 / 36;
            }
            else if ((num - 1.0 / 48) >= 0)
            {
                Paste(answer, L"\u0186");
                num -= 1.0 / 48;
            }
            else if ((num - 1.0 / 72) >= 0)
            {
                Paste(answer, L"\u01A7\u01A7");
                num -= 1.0 / 72;
            }
            else if ((num - 1.0 / 144) >= 0)
            {
                Paste(answer, L"$");
                num -= 1.0 / 144;
            }
            else if ((num - 1.0 / 288) >= 0)
            {
                Paste(answer, L"\u2108");
                num -= 1.0 / 288;
            }
            else if ((num - 1.0 / 1728) >= 0)
            {
                Paste(answer, L"\u00BB");
                num -= 1.0 / 1728;
            }
        }
        return answer;
    }
public:
    void SetByArab(double numb)
    {
        arabNumb = numb;
        std::wstring answer = L"";
        bool isMinus = false;
        if (numb == 0)
        {
            rim = L"N";
        }
        if (numb < 0)
        {
            isMinus = true;
            Paste(answer, L"-");
            numb *= (-1);
        }
        int num = (int)numb;
        if (num / 100000 > 0)
        {
            Paste(answer, L"\u2188 ", num / 100000);
            num %= 100000;
        }
        if (num / 90000 > 0)
        {
            Paste(answer, L"\u2182 \u2188", num / 90000);
            num %= 90000;
        }
        if (num / 50000 > 0)
        {
            Paste(answer, L"\u2187 ", num / 50000);
            num %= 50000;
        }
        if (num / 40000 > 0)
        {
            Paste(answer, L"\u2182 \u2187 ", num / 40000);
            num %= 40000;
        }
        if (num / 10000 > 0)
        {
            Paste(answer, L"\u2182 ", num / 10000);
            num %= 10000;
        }
        if (num / 9000 > 0)
        {
            Paste(answer, L"\u2180 \u2182 ", num / 9000);
            num %= 9000;
        }
        if (num / 5000 > 0)
        {
            Paste(answer, L"\u2181 ", num / 5000);
            num %= 5000;
        }
        if (num / 4000 > 0)
        {
            Paste(answer, L"\u2180 \u2181 ", num / 4000);
            num %= 4000;
        }
        if (num / 1000 > 0)
        {
            Paste(answer, L"M", num / 1000);
            num %= 1000;
        }
        if (num / 900 > 0)
        {
            Paste(answer, L"CM", num / 900);
            num %= 900;
        }
        if (num / 500 > 0)
        {
            Paste(answer, L"D", num / 500);
            num %= 500;
        }
        if (num / 400 > 0)
        {
            Paste(answer, L"CD", num / 400);
            num %= 400;
        }
        if (num / 100 > 0)
        {
            Paste(answer, L"C", num / 100);
            num %= 100;
        }
        if (num / 90 > 0)
        {
            Paste(answer, L"XC", num / 90);
            num %= 90;
        }
        if (num / 50 > 0)
        {
            Paste(answer, L"L", num / 50);
            num %= 50;
        }
        if (num / 40 > 0)
        {
            Paste(answer, L"XL", num / 40);
            num %= 40;
        }

        if (num / 10 > 0)
        {
            Paste(answer, L"X", num / 10);
            num %= 10;
        }
        if (num / 9 > 0)
        {
            Paste(answer, L"IX", num / 9);
            num %= 9;
        }
        if (num / 5 > 0)
        {
            Paste(answer, L"V", num / 5);
            num %= 5;
        }
        else if (num / 4 > 0)
        {
            Paste(answer, L"IV", num / 4);
            num %= 4;
        }
        if (num >= 1)
        {
            Paste(answer, L"I", num / 1);
            num--;
        }
        if (numb - (int)numb > 0)
        {
            answer += FractionToRim(numb - (int)numb);
        }
        rim = answer;
    }
    void CallSetFromConsole(std::wstring const mes)
    {
        arabNumb = -1;
        while (arabNumb == -1)
        {
            std::wcout << (mes);
            std::getline(std::wcin, rim);
            arabNumb = RimToArab(rim);
            if (arabNumb == -1)
            {
                std::wcout << (L"\n введённое число - некоректно, попробуйте снова. \n");
            }
        }
        if (rim[0] == '-')
        {
            arabNumb *= -1;
        }
    }
    std::wstring GetRim()
    {
        return this->rim;
    }
    double GetArab()
    {
        return this->arabNumb;
    }
    RimNumber operator + (RimNumber aRim)
    {
        RimNumber temp;
        temp.SetByArab(this->arabNumb + aRim.arabNumb);
        return temp;
    }
    RimNumber operator - (RimNumber aRim)
    {
        RimNumber temp;
        temp.SetByArab(this->arabNumb - aRim.arabNumb);
        return temp;
    }
    RimNumber operator * (RimNumber aRim)
    {
        RimNumber temp;
        temp.SetByArab(this->arabNumb * aRim.arabNumb);
        return temp;
    }
    RimNumber operator / (RimNumber aRim)
    {
        RimNumber temp;
        if (aRim.arabNumb == 0)
        {
            std::wcout << L"Делить на 0 нельзя." << std::endl;
            return temp;
        }
        temp.SetByArab(this->arabNumb + aRim.arabNumb);
        return temp;
    }

};


int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    RimNumber rim1, rim2;
    wchar_t var = L' ';
    while (var != L'a' && var != L'r')
    {
        var = std::tolower(GetChar(L"выберите тип чисел для ввода a - арабские, r - римские."));
    }
    if (var == L'r')
    {
        rim1.CallSetFromConsole(L"введите римское число 1: ");
        std::wcout << std::endl;
        rim2.CallSetFromConsole(L"введите римское число 2: ");
        std::wcout << std::endl;
    }
    else
    {
        rim1.SetByArab(GetNumber(L"Введите число 1: "));
        std::wcout << std::endl;
        rim2.SetByArab(GetNumber(L"Введите число 2: "));
        std::wcout << std::endl;
    }
    wchar_t operation = GetOperator(L"Выберите операцию + - * / :\n");
    RimNumber answer = Calculate(rim1, rim2, operation);

    std::wcout << rim1.GetArab() << L" " << operation << L" " << rim2.GetArab() << L" = " << answer.GetArab() << std::endl;
    std::wcout << rim1.GetRim() << L" " << operation << L" " << rim2.GetRim() << L" = " << answer.GetRim() << std::endl;
}



inline void Paste(std::wstring& rim, std::wstring ch, int count)
{
    for (int i = 0; i < count; i++)
    {
        rim += ch;
    }
}
inline wchar_t GetChar(std::wstring mes)
{
    wchar_t ch = L' ';
    while (true)
    {
        std::wcout << mes << std::endl;
        std::wcin >> ch;
        if (std::wcin.fail())
        {
            std::wcin.clear();
            std::wcin.ignore(32767, '\n');
            std::wcout << L"некоректное значение, попробуйте снова." << std::endl;
        }
        else
        {
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return ch;
    }
}
double GetNumber(std::wstring s)
{
    double num;
    while (true)
    {
        std::wcout << s;
        std::wcin >> num;
        if (std::wcin.fail()) //проверяем, не заблокирован ли буфер ввода, если да, значит значения ввода юыло некоректным.
        {
            std::wcin.clear(); //возвращаем буфер в обычный режим
            std::wcin.ignore(32767, '\n'); // очищаем буфер ввода
            std::wcout << L"некоректное значение, попробуйте снова" << std::endl; //просим повторный ввод
        }
        else
        {
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем буфер ввода от лишних символов, если таковые есть
            return num; // выходим из функции.
        }
    }
}
inline wchar_t GetOperator(std::wstring mes)
{
    wchar_t operation = L' ';
    while (operation != L'+' && operation != L'-' && operation != L'*' && operation != L'/')
    {
        operation = GetChar(mes);
        if (operation != L'+' && operation != L'-' && operation != L'*' && operation != L'/')
        {
            std::wcout << L"Операция не найдена, попробуйте снова.\n";
        }
    }
    return operation;
}
RimNumber Calculate(RimNumber rim1, RimNumber rim2, wchar_t const operation)
{
    if (operation == L'+')
    {
        return rim1 + rim2;
    }
    if (operation == L'-')
    {
        return rim1 - rim2;
    }
    if (operation == L'*')
    {
        return rim1 * rim2;
    }
    if (operation == L'/')
    {
        return rim1 / rim2;
    }
    return rim1;
}