#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cstddef>
#include <algorithm>
#include <numeric>

// читаем числа, разделенные пробелами, переводами строк или запятыми
std::vector<int> readNumbers(const std::string& fileName) {
  std::ifstream file(fileName);
  std::vector<int> numbers;
  int number;

  while (file >> number) {
    numbers.push_back(number);
    file >> std::ws;
    if (file.peek() == ',') {
      file.get();
    }
  }
  return numbers;
}

// первый способ подсчета повторений: обычный for
int countNumber(const std::vector<int>& numbers, int value) {
  int count = 0;
  for (int number : numbers) {
    if (number == value) {
      ++count;
    }
  }
  return count;
}

// вычисления задания 4.1 для одного вектора
void showVector(const std::vector<int>& numbers, const std::string& name) {
  std::cout << "\n" << name << '\n';
  std::cout << "Количество чисел: " << numbers.size() << '\n';

  // set нужен, чтобы каждое число выводилось один раз
  std::set<int> unique(numbers.begin(), numbers.end());

  std::cout << "Частоты через for:\n";
  for (int value : unique) {
    std::cout << value << ": " << countNumber(numbers, value) << '\n';
  }

  std::cout << "Частоты через std::count:\n";
  for (int value : unique) {
    std::cout << value << ": " << std::count(numbers.begin(), numbers.end(), value) << '\n';
  }

  // первый способ вычисления суммы
  long long sum1 = std::accumulate(numbers.begin(), numbers.end(), 0LL);

  // второй способ вычисления суммы
  long long sum2 = 0;
  std::for_each(numbers.begin(), numbers.end(), [&sum2](int number) {
    sum2 += number;
  });
  std::cout << "Сумма через accumulate: " << sum1 << '\n';
  std::cout << "Сумма через for_each: " << sum2 << '\n';

  // если элементов меньше десяти, не выходим за границы вектора
  int count = static_cast<int>(std::min<std::size_t>(10, numbers.size()));
  long long sum10 = std::accumulate(numbers.begin(), numbers.begin() + count, 0LL);
  std::cout << "Сумма первых " << count << " элементов: " << sum10 << '\n';
}

// 4.2.1
// произведение первого файла большое, поэтому храним его строкой
std::string multiplySelected(std::string result, int number) {
  if (number == 0 || number <= -50 || number >= 50) {
    return result;
  }

  bool negative = (result[0] == '-') != (number < 0);
  if (result[0] == '-') {
    result.erase(0, 1);
  }
  if (number < 0) {
    number = -number;
  }

  // умножение в столбик справа налево
  int carry = 0;
  for (std::string::reverse_iterator it = result.rbegin(); it != result.rend(); ++it) {
    int current = (*it - '0') * number + carry;
    *it = static_cast<char>('0' + current % 10);
    carry = current / 10;
  }
  while (carry > 0) {
    result.insert(result.begin(), static_cast<char>('0' + carry % 10));
    carry /= 10;
  }
  if (negative) {
    result.insert(result.begin(), '-');
  }
  return result;
}

int main() {
  // ==================== 4.1 ====================

  std::vector<int> first = readNumbers("s04_v1_45_1.txt");
  std::vector<int> second = readNumbers("s04_v1_45_2.txt");

  std::cout << "4.1\n";
  std::cout << "s04_v1_45_1.txt: " << first.size() << " чисел\n";
  std::cout << "s04_v1_45_2.txt: " << second.size() << " чисел\n";

  // первый вектор должен быть большим по количеству элементов
  if (first.size() < second.size()) {
    first.swap(second);
  }

  showVector(first, "Первый вектор");
  showVector(second, "Второй вектор");

  // ==================== 4.2 ====================
  std::cout << "\n4.2\n";

  // 4.2.1: произведение подходящих чисел через accumulate
  std::string product1 = std::accumulate(first.begin(), first.end(), std::string("1"), multiplySelected);
  std::string product2 = std::accumulate(second.begin(), second.end(), std::string("1"), multiplySelected);
  std::cout << "Произведение первого: " << product1 << '\n';
  std::cout << "Произведение второго: " << product2 << '\n';

  std::set<int> unique1(first.begin(), first.end());
  std::set<int> unique2(second.begin(), second.end());

  // 4.2.2: повторяющиеся числа каждого вектора
  std::cout << "\nВо втором векторе встречаются 2 и более раз:\n";
  for (int value : unique2) {
    int count = countNumber(second, value);
    if (count >= 2) {
      std::cout << value << ": " << count << '\n';
    }
  }

  std::cout << "\nВ первом векторе встречаются более 3 раз:\n";
  for (int value : unique1) {
    int count = countNumber(first, value);
    if (count > 3) {
      std::cout << value << ": " << count << '\n';
    }
  }

  // 4.2.3а: общие числа через for
  std::cout << "\nОбщие числа через for:\n";
  for (int value : unique2) {
    int count1 = countNumber(first, value);
    int count2 = countNumber(second, value);
    if (count1 > 3 && count2 >= 2) {
      std::cout << value << ": первый = " << count1 << ", второй = " << count2 << '\n';
    }
  }

  // 4.2.3б: общие числа через алгоритм с лямбдой
  std::cout << "\nОбщие числа через for_each:\n";
  std::for_each(unique2.begin(), unique2.end(), [&first, &second](int value) {
    int count1 = static_cast<int>(std::count(first.begin(), first.end(), value));
    int count2 = static_cast<int>(std::count(second.begin(), second.end(), value));
    if (count1 > 3 && count2 >= 2) {
      std::cout << value << ": первый = " << count1 << ", второй = " << count2 << '\n';
    }
  });

  return 0;
}
