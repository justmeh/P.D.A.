#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<time.h>
#include<Windows.h>
#include"Semaphore.h"
using namespace std;

Semaphore emptysem(10);
Semaphore fullsem(0);
mutex m;
queue<int> q;

void prod()
{
	while (true)
	{
		Sleep(2000);
		int item = rand() % 100;
		emptysem.down();
		m.lock();
		q.push(item);
		cout << "Am produs " << item << endl;
		m.unlock();
		fullsem.up();
	}
}

void cons()
{
	while (true)
	{
		fullsem.down();
		m.lock();
		int item = q.front();
		q.pop();
		Sleep(3000);
		cout << "Am consumat " << item << endl;
		m.unlock();
		emptysem.up();
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
