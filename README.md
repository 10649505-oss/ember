
# `ember` — starter skeleton (Lab 1)

Copy this folder to a repository of your own, `git init`, and start from **M1** of
[Lab 01](../lab-01-a-box-of-bytes.md). It builds and runs as-is.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ember
```

## Why a skeleton exists

Lab 1 is about **bytes and types**. It is not about `while` loops, splitting a
string into words, or `std::setw` — you meet those properly in Labs 4, 5 and 7.
So the parts that need them are given to you, fully written and commented. You
read those. You write the four small things that *are* Lab 1.

## Given — read it, don't rewrite it

| File | What it does |
|---|---|
| `CMakeLists.txt` | C++17, `-Wall -Wextra -Werror`, ASan + UBSan on Debug |
| `src/main.cpp` | the prompt: read a line, split it into words, call your functions |
| `src/memory.hpp` | `Byte`, `MEM_SIZE`, `struct Memory` — the box |
| `src/dump.hpp` | the two declarations |
| `src/dump.cpp` → `dump()` | the hex dump loop |

## Yours — four `TODO(lab-01)` markers

```bash
grep -rn "TODO(lab-01)" src/
```

| # | Where | The job |
|---|---|---|
| 1 | `memory.cpp` → `mem_get` | return the byte, or 0 if the address is outside the box |
| 2 | `memory.cpp` → `mem_set` | write the byte, or return `false` if the address is outside |
| 3 | `dump.cpp` → the ASCII gutter | print the character when the byte is printable |
| 4 | `dump.cpp` → `show_byte` | one byte, four views |

When all four are done:

```txt
ember> set 0 65
ember> set 1 66
ember> get 0
65  0x41  0b01000001  'A'
ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
```

That is M2 and M3 of Lab 1. M4 (the three deliberate breakages) is in the lab.

Until you implement `mem_set`, `set` accepts everything and stores nothing, and
`get` prints `show_byte: not implemented yet`. That is the starting state, not a
bug.

## Later labs

You keep this repository for all eight labs. Every lab adds one `else if` branch
to the dispatcher in `main.cpp` and one or two new files next to these.

---

## Українською

Скопіюйте цю теку у свій репозиторій — вона вже збирається й запускається.

Lab 1 — про **байти й типи**, а не про цикли, розбір рядка на слова чи
форматування виводу (це Labs 4, 5, 7). Тому все, що потребує ще не пройденого,
вам **дано** — з коментарями, щоб читати. Ви пишете чотири маленькі речі, які й
є Lab 1: `mem_get`, `mem_set`, ASCII-колонку в дампі та `show_byte`.

Знайти свою роботу: `grep -rn "TODO(lab-01)" src/`.

Якщо C++ бачите вперше — спочатку
[C++ за годину](../cpp-survival-kit.notes.md), потім
[інструменти й git](../setup.notes.md).

## Результати виконання лабораторної роботи №1

### M3. Робота з пам'яттю
- Реалізовано `mem_get` — читання байта за адресою.
- Реалізовано `mem_set` — запис байта з перевіркою меж пам'яті.
- Реалізовано відображення байта у десятковому, шістнадцятковому та двійковому форматах, а також як символ.
- Реалізовано ASCII-колонку в команді `dump`.

### M4. Експерименти

**Дослід 1. Переповнення байта**

Команди: `set 0 255`, `get 0`, `inc 0`, `get 0`.

Результат: після збільшення значення 255 на 1 байт набуває значення 0.

**Дослід 2. Обчислення з числами з рухомою комою**

Було створено та запущено програму для перевірки виразу `0.1 + 0.2 == 0.3`.

Результат виконання: `false`.

Пояснення: десяткові дроби не завжди можна точно представити у двійковому форматі, тому результат порівняння відрізняється від очікуваного. Це не баг компілятора.

**Дослід 3. ASCII-символи**

Команди: `set 0 65`, `set 1 66`, `set 2 0`, `dump`.

Результат: у дампі відображається `AB`. Значення 65 відповідає символу `A`, а 66 — символу `B`.

**Дослід 4. Ініціалізація пам'яті**

Після тимчасового видалення `{}` з оголошення `Byte data[MEM_SIZE]{}` команда `dump` показала різні значення пам'яті. Після досліду `{}` було повернуто.

### Перевірка збірки
### Додаткові перевірки

**Дослід 5. Переповнення беззнакового байта**

Було створено програму, у якій значення `uint8_t` дорівнює 255, а потім збільшується на 1.

Результат виконання: `0`.

Висновок: беззнаковий байт зберігає значення в діапазоні від 0 до 255. Після збільшення 255 на 1 результат стає 0.

**Дослід 6. Розмір типів даних**

За допомогою оператора `sizeof` перевірено розмір типів `int` і `uint8_t`.

Результати виконання:
- `sizeof(int) = 4`
- `sizeof(uint8_t) = 1`

Висновок: на моєму комп'ютері тип `int` займає 4 байти, а `uint8_t` — 1 байт.

Команда `cmake --build build-gcc` завершилася успішно: `[100%] Built target ember`.

# ember


---

## Лабораторна робота №2 — Біти не брешуть

### Мета роботи
Вивчити двійкову та шістнадцяткову системи числення, бітові операції, 8-бітну арифметику, прапорці процесора Z, N, C та принцип виконання інструкцій CPU.

### Реалізовані компоненти
- alu.hpp, alu.cpp — арифметико-логічний пристрій.
- cpu.hpp, cpu.cpp — процесор, регістри, прапорці та виконання інструкцій.
- decode() — визначення групи та індексу опкода.
- step() — виконання однієї інструкції.
- regs — виведення стану регістрів.

### Реалізовані інструкції ISA

| Опкод | Інструкція | Розмір | Прапорці |
|---|---|---|---|
| 0x00 | HALT | 1 | Без змін |
| 0x01 | NOP | 1 | Без змін |
| 0x10 | ADD A, B | 1 | Z N C |
| 0x11 | SUB A, B | 1 | Z N C |
| 0x12 | AND A, B | 1 | Z N, C=0 |
| 0x13 | OR A, B | 1 | Z N, C=0 |
| 0x14 | XOR A, B | 1 | Z N, C=0 |
| 0x15 | NOT A | 1 | Z N, C=0 |
| 0x16 | SHL A | 1 | Z N C |
| 0x17 | SHR A | 1 | Z N C |
| 0x18 | INC A | 1 | Z N |
| 0x19 | DEC A | 1 | Z N |

### Приклад 1. Переповнення під час ADD

Початкові значення:
A = 200, B = 100.

200 + 100 = 300.
300 mod 256 = 44.

Результат:
A = 44, Z = 0, N = 0, C = 1.

Прапорець C дорівнює 1, оскільки результат перевищив 255.

### Приклад 2. Перенесення під час SHL

Початкове значення:
A = 129.

Двійкове представлення:
10000001.

Після зсуву вліво на один біт:
00000010.

Результат:
A = 2, Z = 0, N = 0, C = 1.

Прапорець C дорівнює 1, оскільки старший біт вийшов за межі байта.

### Трасування програми

Початкові значення:
A = 200, B = 100, PC = 0.

Байти програми:
set 0 0x10
set 1 0x18
set 2 0x19
set 3 0x00

| Крок | Інструкція | PC | A | B | Z | N | C |
|---|---|---|---|---|---|---|---|
| 0 | Початковий стан | 0 | 200 | 100 | 0 | 0 | 0 |
| 1 | ADD | 1 | 44 | 100 | 0 | 0 | 1 |
| 2 | INC | 2 | 45 | 100 | 0 | 0 | 1 |
| 3 | DEC | 3 | 44 | 100 | 0 | 0 | 1 |
| 4 | HALT | 4 | 44 | 100 | 0 | 0 | 1 |

INC та DEC не змінюють прапорець C відповідно до ISA.

### Перевірка лабораторної роботи

Команда збірки:
cmake --build build-gcc

Результат:
[100%] Built target ember

Офіційна перевірка:
Get-Content ..\checks\lab-02.txt | .\build-gcc\ember.exe

Отримано:
PC=0 A=200 B=100 Z=0 N=0 C=0
PC=1 A=44 B=100 Z=0 N=0 C=1
halted
PC=2 A=44 B=100 Z=0 N=0 C=1

Результат відповідає очікуваному.

### Висновок

Під час лабораторної роботи реалізовано арифметико-логічний пристрій та процесор Ember. Вивчено бітові операції, переповнення 8-бітних чисел, роботу прапорців Z, N, C та декодування опкодів. Успішно виконано офіційну перевірку Lab 02.

