#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                                ДОМАШНЄ ЗАВДАННЯ 28 тема: клас string
==========================================================================================================================================
*/

// ===================================== РІВЕНЬ 1 =====================================

class FileName
{
private:
    string name;

public:
    FileName(const string& name) : name(name)
    {}

    string getName() const
    {
        return name;
    }

    //  1. Як би ви писали getExtension, якби name був char*? Перелічіть кроки. Що з цього string зробив за вас?
    string getExtension() const
    {
    //  2. Що повертає rfind для "README"? Як ваш getExtension це обробляє?
        size_t dot = name.rfind('.');               // .rfind() шукає з кінця - остання крапка
        if (dot == string::npos)
        {
            return "";                              // розширення немає
        }
        return name.substr(dot + 1);
    }

    string getBaseName() const
    {
        size_t dot = name.rfind('.');
        if (dot == string::npos)
        {
            return name;
        }
        return name.substr(0, dot);
    }

    void changeExtension(const string& newExtension)
    {
        name = getBaseName() + "." + newExtension;
    }

    bool isImage() const
    {
        string extension = getExtension();
        return extension == "png" || extension == "jpg" || extension == "gif";
    }

    void print() const
    {
        cout << name << " | ім'я: " << getBaseName() << " | розширення: [" << getExtension() << "]";
        if (isImage())
        {
            cout << " | зображення";
        }
        cout << endl;
    }
};

// ===================================== РІВЕНЬ 2 =====================================

class MessageTemplate
{
private:
    string text;

    // Замінює всі входження from на to прямо в text
    static void replaceAll(string& text, const string& from, const string& to)
    {
        size_t position = text.find(from);
        while (position != string::npos)
        {
            text.replace(position, from.length(), to);
            position = text.find(from, position + to.length());     // шукаємо ПІСЛЯ вставленого значення
        }
    }

public:
    MessageTemplate(const string& text) : text(text)
    {}

    int countPlaceholders() const
    {
        int count = 0;
        for (int i = 0; i < (int)text.length(); i++)
        {
            if (text[i] == '{')
            {
                count++;
            }
        }
        return count;
    }

    string fill(const string& name, int score) const
    {
        string result = text;                       // копія: сам шаблон не змінюється
        replaceAll(result, "{name}", name);
        replaceAll(result, "{score}", to_string(score));
        return result;
    }
};

// ===================================== РІВЕНЬ 3 =====================================

// 6. (Рівень 3) Навіщо перетворювати вік через stoi? Чому не можна просто додати 1 до рядка "20"?
void parseStudent(const string& line)
{
    size_t first = line.find(';');
    size_t second = line.find(';', first + 1);

    string name = line.substr(0, first);
    int age = stoi(line.substr(first + 1, second - first - 1));
    string email = line.substr(second + 1);

    cout << "Ім'я: " << name << endl;
    cout << "Вік: " << age << ", наступного року: " << age + 1 << endl;
    cout << "Пошта: " << email << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    //  4. Чому string text = "Вітаю, " + "Олена"; не компілюється, а string text = "Вітаю, " + name; (name — string) компілюється?
    string name = "Олена";
    string text = "Вітаю, " + name;

    cout << "===== РІВЕНЬ 1 =====" << endl;
    FileName report("report.final.docx");
    FileName photo("photo.png");
    FileName readme("README");          //  2. Що повертає rfind для "README"? Як ваш getExtension це обробляє?
    report.print();
    photo.print();
    readme.print();

    report.changeExtension("pdf");
    readme.changeExtension("md");
    report.print();
    readme.print();

    //  3. У FileName немає деструктора і конструктора копіювання. Чому FileName copy = report; все одно працює правильно
    //  і пам'ять не витікає?
    FileName copy = report; 
    copy.changeExtension("txt");
    cout << "Оригінал: " << report.getName() << ", копія: " << copy.getName() << endl;

    if (photo.getName() < report.getName())
    {
        cout << photo.getName() << " стоїть у списку раніше" << endl;
    }
    else
    {
        cout << report.getName() << " стоїть у списку раніше" << endl;
    }

    cout << "===== РІВЕНЬ 2 =====" << endl;
    MessageTemplate message("Вітаю, {name}! Ваш бал за модуль: {score}. {name}, так тримати!");
    cout << "Місць для підстановки: " << message.countPlaceholders() << endl;

    string names[3] = { "Олена", "Марко", "Тарас" };
    int scores[3] = { 11, 9, 12 };
    for (int i = 0; i < 3; i++)
    {
        cout << message.fill(names[i], scores[i]) << endl;
    }

    cout << "===== РІВЕНЬ 3 =====" << endl;
    parseStudent("Олена Коваль;20;olena.koval@itstep.org");

    return 0;
}

/*
  1. Як би ви писали getExtension, якби name був char*? Перелічіть кроки. Що з цього string зробив за вас?
  2. Що повертає rfind для "README"? Як ваш getExtension це обробляє?
  3. У FileName немає деструктора і конструктора копіювання. Чому FileName copy = report; все одно працює правильно
     і пам'ять не витікає?
  4. Чому string text = "Вітаю, " + "Олена"; не компілюється, а string text = "Вітаю, " + name; (name — string)
     компілюється?
  5. (Рівень 2) Чому в replaceAll шукаємо далі з position + to.length(), а не з початку рядка? Що станеться,
     якщо студента звуть "{name}"?
  6. (Рівень 3) Навіщо перетворювати вік через stoi? Чому не можна просто додати 1 до рядка "20"?
  
  ВІДПОВІДІ НА ЧАСТИНУ «ПОЯСНИ»

  1. 

  2. 

  3. 

  4. 

  5. 

  6.
*/
