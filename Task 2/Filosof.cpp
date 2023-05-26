#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <syncstream>

using namespace std;

const int numPhilosophers = 5;
const int maxEatingCount = 5; // Максимальное количество еды для каждого философа

mutex forks[numPhilosophers];
mutex outputMutex;

int eatCount[numPhilosophers] = { 0 };

void printMessage(string message)
{
    lock_guard<mutex> lock(outputMutex);
    osyncstream(cout) << message << endl;
}

void philosopher(int id)
{
    int leftFork = id;
    int rightFork = (id + 1) % numPhilosophers;
    unique_lock<mutex> leftLock(forks[leftFork], defer_lock);
    unique_lock<mutex> rightLock(forks[rightFork], defer_lock);
    while (true)
    {
        // Философ размышляет
        printMessage("Philosopher " + to_string(id) + " is thinking.");
        this_thread::sleep_for(chrono::seconds(1));
        // Философ голоден и пытается взять вилки
        lock(leftLock, rightLock);
        printMessage("Philosopher " + to_string(id) + " is hungry.");
        // Философ ест
        printMessage("Philosopher " + to_string(id) + " is eating.");
        this_thread::sleep_for(chrono::seconds(1));
        eatCount[id]++;
        // Выводим шкалу прогресса после окончания итерации
        lock_guard<mutex> lock(outputMutex);
        float progress = static_cast<float>(eatCount[id]) / maxEatingCount;
        osyncstream(cout) << "Progress of Philosopher " << id << ": ";
        int filledCount = static_cast<int>(progress * 20);
        for (int j = 0; j < filledCount; j++)
        {
            osyncstream(cout) << "*";
        }
        for (int j = filledCount; j < 20; j++)
        {
            osyncstream(cout) << "-";
        }
        osyncstream(cout) << endl;
        // Проверяем, завершил ли философ все приемы пищи
        if (eatCount[id] >= maxEatingCount)
        {
            break;
        }
        // Освобождаем вилки
        leftLock.unlock();
        rightLock.unlock();
    }
}

int main()
{
    thread philosophers[numPhilosophers];
    // Создаем потоки для каждого философа
    for (int i = 0; i < numPhilosophers; i++)
    {
        philosophers[i] = thread(philosopher, i);
    }
    // Ожидаем завершения всех философов
    for (int i = 0; i < numPhilosophers; i++)
    {
        philosophers[i].join();
    }
    // Выводим статистику
    for (int i = 0; i < numPhilosophers; i++)
    {
        cout << "Philosopher " << i << ": ";
        cout << "Eat count: " << eatCount[i] << endl;
    }
    return 0;
}
