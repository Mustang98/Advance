#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*
Функция находит ответ для подзадачи, характеризуемой следующими параметрами:
currentBus - номер автобуса (начиная с 0), который стоит на остановке
currentPassenger - номер пассажира (начиная с 0), стоящего в начале очереди
busySpace - сколько объёма занято в текущем автобусе
*/
int findMaximumProfit(int const currentBus,
                      int const currentPassenger,
                      int const busySpace,
                      std::vector<int> const &peopleVolume,
                      std::vector<std::vector<std::vector<int> > >& partialAnswer,
                      std::vector<std::vector<std::vector<bool> > >& isVisited)
{
    int busNumber = partialAnswer.size();
    int peopleNumber = partialAnswer[0].size();
    int busCapacity = partialAnswer[0][0].size() - 1;
    // Если закончились автобусы или люди в очереди, ты мы никого уже не сможем увезти
    if (currentBus == busNumber || currentPassenger == peopleNumber)
    {
        return 0;
    }

    // Если для текущей подзадачи уже посчитан ответ, возвращаем его
    if (isVisited[currentBus][currentPassenger][busySpace])
    {
        return partialAnswer[currentBus][currentPassenger][busySpace];
    }

    int maximumProfit; // Ответ для текущей подзадачи

    // Если текущий пассажир уходит из очереди
    maximumProfit = findMaximumProfit(currentBus,
                                      currentPassenger + 1,
                                      busySpace,
                                      peopleVolume,
                                      partialAnswer,
                                      isVisited);

    // Если в автобусе достаточно свободного места, текущий пассажир садится в него
    if (peopleVolume[currentPassenger] + busySpace <= busCapacity)
    {
        int newProfit = 1 + findMaximumProfit(currentBus,
                                              currentPassenger + 1,
                                              busySpace + peopleVolume[currentPassenger],
                                              peopleVolume,
                                              partialAnswer,
                                              isVisited);

        maximumProfit = std::max(maximumProfit, newProfit);
    }
    else // Иначе подъезжает следующий автобус
    {
        int newProfit = findMaximumProfit(currentBus + 1,
                                          currentPassenger,
                                          0,
                                          peopleVolume,
                                          partialAnswer,
                                          isVisited);
        maximumProfit = std::max(maximumProfit, newProfit);
    }

    // Сохраняем ответ для текущей подзадачи
    isVisited[currentBus][currentPassenger][busySpace] = true;
    partialAnswer[currentBus][currentPassenger][busySpace] = maximumProfit;

    return maximumProfit;
}

void readBusData(std::ifstream &inputStream,
               int& busNumber,
               int& peopleNumber,
               int& busCapacity,
               std::vector<int>& peopleVolume)
{
    inputStream >> busNumber;
    inputStream >> busCapacity;
    inputStream >> peopleNumber;

    int volume;
    for (int i = 0; i < peopleNumber; ++i)
    {
        inputStream >> volume;
        peopleVolume.push_back(volume);
    }
}

void writeMaximumProfit(std::ofstream& outputStream, int const maximumProfit)
{
    outputStream << maximumProfit;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("c.in");
    std::ofstream fout("c.out");

    int busNumber; // Количество автобусов
    int peopleNumber; // Количество людей в очереди
    int busCapacity; // Вместимость автобуса
    std::vector<int> peopleVolume; // Массив объемов людей в очереди

    // Считываем входные данные
    readBusData(fin,
              busNumber,
              peopleNumber,
              busCapacity,
              peopleVolume);

    // Массив ответов для подзадач
    std::vector<std::vector<std::vector<int> > > partialAnswer
    (busNumber,
     std::vector<std::vector<int>  > (peopleNumber,
                                      std::vector<int> (busCapacity + 1, 0)));
    // Булевый массив. Отвечает за то, посчитан ли уже ответ для конкретной подзадачи
    std::vector<std::vector<std::vector<bool> > > isVisited
    (busNumber,
     std::vector<std::vector<bool>  > (peopleNumber,
                                       std::vector<bool> (busCapacity + 1, 0)));

    // Вызываем рекурсивную функцию поиска ответа и выводим результат
    int maximumProfit = findMaximumProfit(0,
                                          0,
                                          0,
                                          peopleVolume,
                                          partialAnswer,
                                          isVisited);

    writeMaximumProfit(fout, maximumProfit);

    fin.close();
    fout.close();
    return 0;
}
