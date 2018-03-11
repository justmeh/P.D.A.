#include "Semaphore.h"

Semaphore::Semaphore(int n)
{
	this->n = n;
}

void Semaphore::up()
{
	unique_lock<mutex> lk(mtx);

	n++;

	lk.unlock();
	cond.notify_one();

}

void Semaphore::down()
{
	unique_lock<mutex> lk(mtx);

	while(!n)
		cond.wait(lk);

	n--;

	lk.unlock();
}
