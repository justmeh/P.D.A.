#include<iostream>
#include<stdlib.h>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<time.h>
#include<Windows.h>
#include<string>
using namespace std;
#define FREE 3
#define AUX 2
#define BLACK 1
#define WHITE 0

int waiting[2] = { 0,0 }, used[2] = { 0,0 }, in_use[2] = { 0,0 }, user = FREE;

mutex waitMutex, counter;
condition_variable waitCond[2];
string type_string[4] = { "alb", "negru", "aux", "free" };

void get_resource(int type)
{
	Sleep(1000);

	while (true)
	{
		if (user == FREE)
		{
			user = type;
			cout << "user is no longer free\n";
		}

		if (user == type)
		{
			unique_lock<mutex> lock(counter);

			if (used[type] > 4 && waiting[!type])
			{
				user = AUX;
				waiting[type]++;
				waitCond[type].wait(lock);
				lock.unlock();
			}
			else
			{
				cout << "Thread of type " << type_string[type] << " gets the resource\n";
				used[type]++;
				in_use[type]++;
				lock.unlock();

				return;
			}
		}
		else
		{
			unique_lock<mutex> lock(waitMutex);

			waiting[type]++;
			waitCond[type].wait(lock);

			lock.unlock();
		}
	}
}

void use_resource(int type)
{
	counter.lock();
	cout << "Current type: " << type_string[type] << ", user: " << type_string[user] << ", used: " << used[type] << endl;
	counter.unlock();
	Sleep(rand() % 2000 + 3000);
}

void give_resource(int type)
{
	Sleep(1000);

	unique_lock<mutex> lock(counter);
	cout << "Thread of type " << type_string[type] << " gives up the resource\n ";

	in_use[type]--;

	if (in_use[type] == 0 && user == AUX)
	{
		used[type] = 0;
		waiting[!type] = 0;
		user = !type;
		waitCond[!type].notify_all();
	}
	else
	{
		if (in_use[type] == 0)
		{
			user = FREE;
			cout << "user is now free\n";
		}
	}
	lock.unlock();
}

void thread_function(int type)
{
	get_resource(type);

	use_resource(type);
	
	give_resource(type);
}

int main()
{
	srand(time(NULL));
	thread t[100];

	for (int i = 0; i < 100; i++) 
	{
		Sleep(1000);

		int type = rand() % 2;
		t[i] = thread(thread_function, type);
	}

	for (int i = 0; i < 100; i++)
	{
		t[i].join();
	}

	return 0;
}
