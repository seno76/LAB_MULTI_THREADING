#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <syncstream>

using namespace std;

const int numPhilosophers = 20;
const int maxEatingCount = 20; // Максимальное количество еды для каждого философа

mutex forks[numPhilosophers];
mutex outputMutex;

int eatCount[numPhilosophers];

void printMessage(string message)
{
    lock_guard<mutex> lock(outputMutex);
    osyncstream(cout) << message << endl;
}

void printProgress(int id)
{
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
        printMessage("Philosopher " + to_string(id) + " is hungry.");
        lock(leftLock, rightLock);
        // Философ ест
        printMessage("Philosopher " + to_string(id) + " is eating.");
        this_thread::sleep_for(chrono::seconds(1));
        eatCount[id]++;
        printProgress(id);
        // Освобождаем вилки
        leftLock.unlock();
        rightLock.unlock();
        // Проверяем, завершил ли философ все приемы пищи
        if (eatCount[id] >= maxEatingCount)
        {
            break;
        }
    }
}

//void philosopher(int id) 
//{
//    int leftFork = id;
//    int rightFork = (id + 1) % numPhilosophers;
//    while (true) 
//    {
//        this_thread::sleep_for(chrono::seconds(1));
//        if (!forks[leftFork].try_lock())
//        {
//            printMessage("Philosopher " + to_string(id) + " is thinking.");
//            continue;
//        }
//        if (!forks[rightFork].try_lock()) 
//        {
//            forks[leftFork].unlock();
//            printMessage("Philosopher " + to_string(id) + " is thinking.");
//            continue;
//        }
//        printMessage("Philosopher " + to_string(id) + " is eating.");
//        this_thread::sleep_for(chrono::seconds(1));
//        eatCount[id]++;
//        printProgress(id);
//        forks[leftFork].unlock();
//        forks[rightFork].unlock();
//        if (eatCount[id] >= maxEatingCount)
//        {
//            break;
//        }
//    }
//}

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
