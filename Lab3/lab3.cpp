#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<time.h>
#include<Windows.h>
#include<condition_variable>
#define MAX 10

using namespace std;

mutex mtx;
condition_variable condProd, condCons;
queue<int> q;

void prod()
{
	while (true)
	{
		Sleep(2000);
		int item = rand() % 100;
		unique_lock<mutex> lock(mtx);
		while (q.size() == MAX)
			condProd.wait(lock);
		q.push(item);
		cout << "Am produs " << item << endl;
		lock.unlock();
		condCons.notify_one();
	}
}

void cons()
{
	while (true)
	{
		unique_lock<mutex> lock(mtx);
		while (q.size() == 0)
			condCons.wait(lock);
		int item = q.front();
		q.pop();
		Sleep(3000);
		cout << "Am consumat " << item << endl;
		lock.unlock();
		condProd.notify_one();
	}
}

int main()
{
	srand(time(NULL));

	thread producatori[10], consumatori[10];

	for (int i = 0; i < 3; i++)
	{
		producatori[i] = thread(prod);
		consumatori[i] = thread(cons);
	}

	for (int i = 0; i < 3; i++)
		producatori[i].join();

	for (int i = 0; i < 3; i++)
		consumatori[i].join();

	return 0;
}
