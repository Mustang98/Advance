#include <iostream>
#include <fstream>
#include <algorithm>

int busNumber; // ���������� ���������
int peopleNumber; // ���������� ����� � �������
int busCapacity; // ����������� ��������

int peopleVolume[301]; // ������ ������� ����� � �������
int partialAnswer[102][301][301]; // ������ ������� ��� ��������
// ������� ������. �������� �� ��, �������� �� ��� ����� ��� ���������� ���������
bool isVisited[101][301][301] = {0};

/*
������� ������� ����� ��� ���������, ��������������� ���������� �����������:
currentBus - ����� �������� (������� � 0), ������� ����� �� ���������
currentPassenger - ����� ��������� (������� � 0), �������� � ������ �������
busySpace - ������� ������ ������ � ������� ��������
*/
int findMaximumProfit(int currentBus, int currentPassenger, int busySpace)
{
    // ���� ����������� �������� ��� ���� � �������, �� �� ������ ��� �� ������ ������
    if (currentBus == busNumber || currentPassenger == peopleNumber)
    {
        return 0;
    }

    // ���� ��� ������� ��������� ��� �������� �����, ���������� ���
    if (isVisited[currentBus][currentPassenger][busySpace])
    {
        return partialAnswer[currentBus][currentPassenger][busySpace];
    }

    int maximumProfit; // ����� ��� ������� ���������

    // ���� ������� �������� ������ �� �������
    maximumProfit = findMaximumProfit(currentBus, currentPassenger + 1, busySpace);

    // ���� � �������� ���������� ���������� �����, ������� �������� ������� � ����
    if (peopleVolume[currentPassenger] + busySpace <= busCapacity)
    {
        int newProfit = 1 + findMaximumProfit(currentBus,
                                              currentPassenger + 1,
                                              busySpace + peopleVolume[currentPassenger]);

        maximumProfit = std::max(maximumProfit, newProfit);
    }
    else // ����� ���������� ��������� �������
    {
        int newProfit = findMaximumProfit(currentBus + 1,
                                          currentPassenger,
                                          0);
        maximumProfit = std::max(maximumProfit, newProfit);
    }

    // ��������� ����� ��� ������� ���������
    isVisited[currentBus][currentPassenger][busySpace] = true;
    partialAnswer[currentBus][currentPassenger][busySpace] = maximumProfit;

    return maximumProfit;
}

int main()
{
    std::ifstream cin("c.in");
    std::ofstream cout("c.out");

    // �������� ������� ������
    cin >> busNumber;
    cin >> busCapacity;
    cin >> peopleNumber;

    for (int i = 0; i < peopleNumber; ++i)
    {
        cin >> peopleVolume[i];
    }

    // �������� ����������� ������� ������ ������ � ������� ���������
    cout << findMaximumProfit(0, 0, 0);

    return 0;
}
