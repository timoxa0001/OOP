#include <array>
#include <cstddef>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "hypotenuse_plus_mod.h"

template <typename T1>
T1 randomValue(std::mt19937& generator, std::uniform_int_distribution<T1>& distribution, std::set<T1>& used) {
    T1 value;
    do {
        value = distribution(generator);
    } while (!used.insert(value).second);
    return value;
}

int main() {
  using T1 = long;
  using T2 = double;

  const std::size_t M = 15;
  const T1 N = 50000;

  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<T1> distribution(-N, N);

  const T1 secondArgument = distribution(generator);

  // не допускаем повторов среди всех 60 исходных элементов
  std::set<T1> used;

  std::array<long, M> sourceArray{};
  std::vector<T1> sourceVector(M);
  std::list<T1> sourceList(M);
  std::deque<T1> sourceDeque(M);

  std::list<T1>::iterator fillList = sourceList.begin();
  for (std::size_t i = 0; i < M; ++i, ++fillList) {
    sourceArray[i] = randomValue(generator, distribution, used);
    sourceVector[i] = randomValue(generator, distribution, used);
    *fillList = randomValue(generator, distribution, used);
    sourceDeque[i] = randomValue(generator, distribution, used);
  }

  std::vector<T2> resultVector;
  resultVector.reserve(M);
  std::list<T2> resultList;
  std::deque<T2> resultDeque;
  std::array<T2, M> resultArray{};

  // array -> vector: классический for
  for (std::size_t i = 0; i < M; ++i) {
    resultVector.push_back(Hypo::hypotenuse_plus_mod<T2, T1>(sourceArray[i], secondArgument));
  }

  // vector -> list: for с итератором
  for (std::vector<T1>::const_iterator it = sourceVector.cbegin(); it != sourceVector.cend(); ++it) {
    resultList.push_back(Hypo::hypotenuse_plus_mod<T2>(*it, secondArgument));
  }

  // list -> deque: range-based for
  for (const T1& value : sourceList) {
    resultDeque.push_back(Hypo::hypotenuse_plus_mod<T2>(value, secondArgument));
  }

  // deque -> array: range-based for с индексом результата
  std::size_t index = 0;
  for (const T1& value : sourceDeque) {
    resultArray[index] = Hypo::hypotenuse_plus_mod<T2>(value, secondArgument);
    ++index;
  }

  // все строки данных таблицы создаются одним циклом for
  std::vector<std::string> rows;
  rows.reserve(M);
  std::list<T1>::const_iterator sourceListIt = sourceList.cbegin();
  std::list<T2>::const_iterator resultListIt = resultList.cbegin();

  for (std::size_t i = 0; i < M; ++i, ++sourceListIt, ++resultListIt) {
    std::ostringstream row;
    row << std::fixed << std::setprecision(6)
      << "| " << i + 1
      << " | " << sourceArray[i] << " | " << resultVector[i]
      << " | " << sourceVector[i] << " | " << *resultListIt
      << " | " << *sourceListIt << " | " << resultDeque[i]
      << " | " << sourceDeque[i] << " | " << resultArray[i]
      << " |";
    rows.push_back(row.str());
  }

  std::ofstream file("results.md");

  file << "# Результаты задания 3.IV\n\n"
    << "M = " << M << ", N = " << N
    << ", T1 = long, T2 = double.\n\n"
    << "Общий второй аргумент: " << secondArgument << ".\n\n"
    << "С вероятностью 50% к гипотенузе добавляется число из [0, 1).\n\n"
    << "| № | array (long) | → vector (double)"
    << " | vector (long) | → list (double)"
    << " | list (long) | → deque (double)"
    << " | deque (long) | → array (double) |\n"
    << "|---:|---:|---:|---:|---:|---:|---:|---:|---:|\n";

  // этот цикл записывает уже готовые строки
  for (const std::string& row : rows) {
    file << row << '\n';
  }

  file.close();

  std::cout << "Ready: table saved in results.md\n"
    << "Second argument: " << secondArgument << '\n';
  return 0;
}
