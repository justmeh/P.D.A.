#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include<mutex>
#include<condition_variable>
using namespace std;

class Semaphore
{
private:
	int n;
	mutex mtx;
	condition_variable cond;
public:
	Semaphore(int n);

	void up();
	void down();
};

#endif
