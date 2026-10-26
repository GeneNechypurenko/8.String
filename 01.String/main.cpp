#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                                              Клас string
==========================================================================================================================================

  std::string — це стандартний клас із бібліотеки <string>, який є безпечною та зручною обгорткою над масивом символів. Він автоматично
  керує пам'яттю, дозволяє динамічно змінювати розмір рядка та надає вбудовані методи для маніпуляції текстом.

                                                         Цілі та завдання string
  З C-рядками (char*) програміст сам відповідає за все: new/delete[], strlen, strcpy_s, strcat_s, strcmp, розмір буфера.
  Помилка в будь-якому місці — витік пам'яті, вихід за межі масиву або подвійний delete[].
  string ховає це всередині класу і дає звичні оператори: =, +, +=, ==, <, [], <<, >> та методи.

                                                          Будова класу string
  Усередині string реалізовано:
  - покажчик на динамічний буфер із символами (з '\0' в кінці);
  - size — кількість символів;
  - capacity — скільки символів уміщує вже виділений буфер. Коли місця не вистачає, string виділяє більший буфер (із запасом),
  копіює туди символи і звільняє старий;
  - реалізоване правило п'яти: копія string — завжди незалежна копія, перенесення — швидке.
  Тому клас, у якого поля типу string, а не char*, не потребує власного деструктора, конструктора копіювання і operator=:
  стандартні версії, які створює компілятор, викликають відповідні методи string. Це називають ПРАВИЛОМ НУЛЯ.

                                                       Створення і основні оператори
      string s;                         // порожній рядок ""
      string name = "Олена";            // з C-рядка (конструктор без explicit, як у MyString)
      string line(10, '-');             // "----------"
      string full = name + " " + "Коваль";      // + : новий рядок;  += : дописати в кінець
      name == "Олена"   name < other    // порівняння: ==, !=, <, >, <=, >= (посимвольно, як strcmp)
      name[0]                           // символ за індексом, без перевірки меж

                                                             Основні методи
      s.length()  /  s.size()           // кількість символів (байтів) — однакові методи
      s.empty()                         // true, якщо рядок порожній
      s.clear()                         // зробити порожнім
      s.find("abc")  /  s.find('@')     // позиція першого входження або string::npos, якщо не знайдено
      s.find('.', pos)                  // шукати, починаючи з позиції pos
      s.substr(pos, count)              // новий рядок: count символів, починаючи з pos (без count — до кінця)
      s.insert(pos, "text")             // вставити рядок на позицію pos
      s.erase(pos, count)               // видалити count символів, починаючи з pos
      s.replace(pos, count, "text")     // замінити count символів, починаючи з pos, на text
      s.c_str()                         // const char* — для функцій, які приймають C-рядок

  Позиції та довжини в string мають тип size_t (беззнакове ціле). string::npos — найбільше значення size_t.
  string::npos (no position) — це ⁠спеціальна константа в C++, яка означає «позицію не знайдено» або «до кінця рядка».

                                                       Функції перетворення з числами
      to_string(25)        → "25"           to_string(3.5)  → "3.500000"
      stoi("42")           → 42             stod("3.14")    → 3.14

                                                              Введення
      cin >> s;                         // читає ОДНЕ слово: до пробілу або Enter
      getline(cin, s);                  // читає весь рядок разом із пробілами
  Після cin >> в буфері лишається '\n', і наступний getline одразу прочитає порожній рядок. Перед таким getline викликайте cin.ignore();
*/

class Student
{
private:
    string name;                                    // замість char* — і жодного new/delete[]
    string email;
    int age;

public:
    // Параметри const string& — щоб не копіювати рядок під час передачі
    Student(const string& name, int age) : name(name), email(""), age(age)
    {}

    // Деструктор, конструктор копіювання і operator= НЕ пишемо — правило нуля
    void setName(const string& name)
    {
        this->name = name;                          // operator= класу string: сам звільнить і виділить пам'ять
    }

    string getName() const
    {
        return name;
    }

    // Пошта приймається, лише якщо є '@' (не першим символом) і після нього є '.'
    bool setEmail(const string& email)
    {
        size_t at = email.find('@');
        if (at == string::npos || at == 0)          // '@' немає або логін порожній
        {
            return false;
        }
        if (email.find('.', at) == string::npos)    // шукаємо '.' лише ПІСЛЯ '@'
        {
            return false;
        }
        this->email = email;
        return true;
    }

    string getLogin() const
    {
        return email.substr(0, email.find('@'));    // усе до '@'
    }

    string getDomain() const
    {
        return email.substr(email.find('@') + 1);   // усе після '@' до кінця
    }

    // Збираємо «картку» студента з частин: + і to_string
    string toString() const
    {
        string result = name + ", вік: " + to_string(age);
        if (!email.empty())
        {
            result += ", пошта: " + email;
        }
        return result;
    }
};

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "1. Склеювання рядків" << endl;
    string firstName = "Олена";
    string lastName = "Коваль";
    string fullName = firstName + " " + lastName;   // жодного strcat_s і розрахунку розміру буфера
    // string test = "Олена" + " " + "Коваль";      // не компілюється (див. інсайти)
    cout << fullName << endl;

    cout << "2. Student на string — копіювання без конструктора копіювання" << endl;
    Student olena(fullName, 20);
    Student copy = olena;                           // стандартне копіювання копіює кожен string окремо
    copy.setName("Марія Бондар");
    cout << olena.toString() << endl;               // оригінал не змінився
    cout << copy.toString() << endl;

    cout << "3. Перевірка пошти: find" << endl;
    if (!olena.setEmail("olena.koval"))
    {
        cout << "Помилка: olena.koval — не адреса пошти" << endl;
    }
    if (olena.setEmail("olena.koval@itstep.org"))
    {
        cout << olena.toString() << endl;
    }

    cout << "4. Частини рядка: substr" << endl;
    cout << "Логін: " << olena.getLogin() << endl;
    cout << "Домен: " << olena.getDomain() << endl;

    cout << "5. Зміна рядка: replace, insert, erase" << endl;
    string address = "olena.koval@itstep.org";
    size_t at = address.find('@');
    address.replace(at + 1, address.length() - at - 1, "gmail.com");     // замінюємо домен
    cout << address << endl;
    address.insert(at, "2007");                     // olena.koval2007@gmail.com
    cout << address << endl;
    address.erase(at, 4);                           // прибираємо вставлені 4 символи
    cout << address << endl;

    cout << "6. Порівняння: як strcmp, але операторами" << endl;
    string a = "Anna";
    string b = "Bohdan";
    if (a < b)
    {
        cout << a << " стоїть у списку раніше за " << b << endl;
    }

    cout << "7. Довжина рядка — у байтах" << endl;
    string latinText = "Hello World!";
    string cyrillicText = "Хелло Ворлд!";
    cout << "Латиниця, розмір: " << latinText.length() << endl;        // 12: кожен символ — 1 байт ('\0' не рахується)
    cout << "Кирилиця, розмір: " << cyrillicText.length() << endl;     // 22: 10 літер по 2 байти + пробіл і '!' по 1
    cout << "Латиниця, буфер: " << latinText.capacity() << endl;       // 15: до 15 байтів рядок лежить всередині об'єкта (SSO)
    cout << "Кирилиця, буфер: " << cyrillicText.capacity() << endl;    // більше 22: пам'ять виділено окремо, із запасом

    cout << endl << "8. Введення рядків і reserve" << endl;
    cout << "Введіть ім'я користувача: " << endl;
    string userName;
    cin >> userName;                    // читає ОДНЕ слово
    cin.ignore();                       // після cin >> у буфері лишається '\n' — без ignore getline одразу прочитає порожній рядок
    string comment;
    comment.reserve(1000);              // буфер щонайменше на 1000 байтів, виділяється одразу
    cout << "Введіть коментар: " << endl;
    getline(cin, comment);              // читає весь рядок разом із пробілами
    cout << endl << userName << endl << comment << endl;
    cout << "розмір рядка: " << comment.length() << ", розмір буфера: " << comment.capacity() << endl;
    /*
      reserve тут лише для прикладу: getline і без нього виділить стільки пам'яті, скільки потрібно.
      reserve — оптимізація швидкості. Вона має сенс, коли великий рядок збирається з тисяч частин і кінцевий розмір
      відомий наперед. У звичайних програмах string сам виділяє пам'ять із запасом, і перевиділень дуже мало.
    */

    return 0;
}

/*
  ІНСАЙТИ / BEST PRACTICES
  - З цього моменту в курсі нарешті забуваєм про char* і працюємо із string.
  - Головний виграш — правило нуля: Student з полями string не має ні деструктора, ні копіювання, і все одно копіюється
    правильно. Правило трьох/п'яти пишуть лише ті класи, які САМІ володіють ресурсом (як string усередині).
  - Параметри: const string& — для читання (без копії); string — повертати з методу (копія або перенесення).
  - Перевіряйте результат find на string::npos ДО того, як використовувати позицію в substr чи replace.
    Порівнюйте саме з npos, а не з -1, і зберігайте позицію в size_t, а не в int.
  - "Олена" + " " + "Коваль" не компілюється: це два const char*, а не string. Хоча б один з перших двох доданків має бути string:
        string s = string("Олена") + " " + "Коваль";
  - Кирилиця в UTF-8: length() рахує БАЙТИ, s[0] — половинка літери. find і порівняння працюють правильно,
    а от розрізати рядок посимвольно за індексами не можна. Для логінів, паролів, адрес пошти — латиниця.
  - cin >> s читає одне слово. Для імені з прізвищем — getline(cin, s). Після cin >> краще завжди cin.ignore() (якщо є getline).
  - s += "текст" у циклі працює швидко: string виділяє пам'ять із запасом (capacity), а не на кожне додавання.
    Якщо кінцевий розмір відомий заздалегідь — s.reserve(n).
  - Короткі рядки (до 15 байтів) string зберігає прямо всередині об'єкта, без new (Small String Optimization). Це дуже хитрий трюк:
    розробники бібліотеки додали всередину класу string об'єднання (union), тому ті самі байти об'єкта — це або масив символів 
    (короткий рядок), або покажчик на буфер у динамічній пам'яті (довгий рядок). Що саме там лежить, string визначає за capacity.
    Більшість рядків у програмах короткі, тому для них new і delete не викликаються зовсім.

  ==========================================================================================================================================

  ПРАКТИКА

  1. Клас Player — гравець онлайн-гри:
     - поля (private): string nickname; int id;
     - конструктор Player(int id) — nickname порожній;
     - bool setNickname(const string& nickname) — приймає нікнейм лише якщо:
         * довжина від 3 до 16 символів;
         * немає пробілів (find(' ') повертає string::npos);
       інакше повертає false і нікнейм не змінює;
     - string getTag() const — повертає нікнейм + "#" + id, наприклад: DarkKnight#1042 (використайте to_string);
     У main: перевірте нікнейми "Al", "Dark Knight", "DarkKnight" і виведіть тег гравця.

  2. Клас ChatFilter — фільтр нецензурних слів у чаті гри:
     - поле (private): string badWord;
     - конструктор ChatFilter(const string& badWord);
     - string filter(const string& message) const — повертає копію message, у якій КОЖНЕ входження badWord замінено
       на "***". Алгоритм: знайти find(badWord); поки позиція не string::npos — replace(позиція, довжина badWord, "***")
       і шукати далі, починаючи з позиції + 3.
     - int countIn(const string& message) const — скільки разів badWord трапляється в message.
     У main: ChatFilter filter("noob"); перевірте повідомлення "you noob, total noob!" і повідомлення без цього слова.

  3. Гра «Шибениця» — клас Hangman (слова латиницею: літера кирилиці — 2 байти і в один char не вміщується):
     - поля (private): string word — загадане слово; string hidden — те, що бачить гравець; int attemptsLeft;
       string usedLetters — літери, які гравець уже називав;
     - конструктор Hangman(const string& word, int attempts) — hidden заповнити підкресленнями тієї самої довжини:
       string(word.length(), '_');
     - bool guess(char letter):
         * якщо letter уже є в usedLetters (find) — повернути false, спробу НЕ знімати;
         * дописати letter в usedLetters (+=);
         * якщо letter немає в word (find повертає string::npos) — зменшити attemptsLeft і повернути false;
         * інакше циклом по word відкрити в hidden КОЖНУ таку літеру (hidden[i] = letter) і повернути true;
     - bool isWon() const — у hidden не лишилося '_';
     - bool isLost() const — attemptsLeft == 0;
     - void print() const — виводить, наприклад:  _ r o _ r a _ _ i n _  | спроб: 4 | використані: aeinor
       (між символами hidden — пробіли, щоб підкреслення не зливалися).
     У main:
       Перший гравець вводить слово сам (cin >> secret), після чого виведіть string(40, '\n'), щоб другий гравець його не побачив.
       Hangman game(secret, 6);
       поки гра не виграна і не програна: print(), прочитати літеру (cin >> letter), викликати guess
       і вивести «Є така літера!» або «Немає...».
       Наприкінці виведіть «Перемога!» або «Поразка! Слово було: ...».
*/
