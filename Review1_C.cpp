#include <iostream>
#include <fstream>
#include <algorithm>

int busNumber; // Количество автобусов
int peopleNumber; // Количество людей в очереди
int busCapacity; // Вместимость автобуса

int peopleVolume[301]; // Массив объемов людей в очереди
int partialAnswer[102][301][301]; // Массив ответов для подзадач
// Булевый массив. Отвечает за то, посчитан ли уже ответ для конкретной подзадачи
bool isVisited[101][301][301] = {0};

/*
Функция находит ответ для подзадачи, характеризуемой следующими параметрами:
currentBus - номер автобуса (начиная с 0), который стоит на остановке
currentPassenger - номер пассажира (начиная с 0), стоящего в начале очереди
busySpace - сколько объёма занято в текущем автобусе
*/
int findMaximumProfit(int currentBus, int currentPassenger, int busySpace)
{
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
    maximumProfit = findMaximumProfit(currentBus, currentPassenger + 1, busySpace);

    // Если в автобусе достаточно свободного места, текущий пассажир садится в него
    if (peopleVolume[currentPassenger] + busySpace <= busCapacity)
    {
        int newProfit = 1 + findMaximumProfit(currentBus,
                                              currentPassenger + 1,
                                              busySpace + peopleVolume[currentPassenger]);

        maximumProfit = std::max(maximumProfit, newProfit);
    }
    else // Иначе подъезжает следующий автобус
    {
        int newProfit = findMaximumProfit(currentBus + 1,
                                          currentPassenger,
                                          0);
        maximumProfit = std::max(maximumProfit, newProfit);
    }

    // Сохраняем ответ для текущей подзадачи
    isVisited[currentBus][currentPassenger][busySpace] = true;
    partialAnswer[currentBus][currentPassenger][busySpace] = maximumProfit;

    return maximumProfit;
}

int main()
{
    std::ifstream cin("c.in");
    std::ofstream cout("c.out");

    // считыаем входные данные
    cin >> busNumber;
    cin >> busCapacity;
    cin >> peopleNumber;

    for (int i = 0; i < peopleNumber; ++i)
    {
        cin >> peopleVolume[i];
    }

    // вызываем рекурсивную функцию поиска ответа и выводим результат
    cout << findMaximumProfit(0, 0, 0);

    return 0;
}
