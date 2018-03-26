#include<mpi.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;

int randLehmer(int seed)
{
	int a, c, m;
	a = 61;
	c = 19;
	m = 10000;
	return (a*seed + c) % m;
}

int main(int argc, char** argv)
{
	int size, procid, rc, to_send[2], to_receive[2], leaderid;
	MPI_Status status;
	MPI_Request request;

	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) 
	{
		cout << "Error starting MPI program. Terminating.\n";
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);

	leaderid = procid;

	srand(time(NULL));

	int maxprio = randLehmer(7384 * (procid+1))%100;

	for (int i = 0; i < size; i++)
	{
		to_send[0] = leaderid;
		to_send[1] = maxprio;
		MPI_Isend(&to_send, 2, MPI_INT, (procid + 1)%size, 0, MPI_COMM_WORLD, &request);
		MPI_Recv(&to_receive, 2, MPI_INT, (size + procid - 1)%size, 0, MPI_COMM_WORLD, &status);
		cout << "I'm " << procid << " and i received " << to_receive[0] << " " << to_receive[1] << " on step " << i << endl;
		if (to_receive[1] > maxprio)
		{
			leaderid = to_receive[0];
			maxprio = to_receive[1];
			
		}
		else
		{
			if (to_receive[1] == maxprio)
			{
				if (to_receive[0] > procid)
				{
					leaderid = to_receive[0];
					maxprio = to_receive[1];
				}
			}
		}
	}

	Sleep(2000);
	cout << "I'm " << procid << " and my leader is " << leaderid << " with priority " << maxprio << endl;

	MPI_Finalize();
	return 0;
}
