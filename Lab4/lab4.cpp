#include<mpi.h>
#include<iostream>
using namespace std;

int v[100] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

int main(int argc, char** argv )
{
	int rc,procid,size;
	int sum = 0;
	MPI_Status status;
	
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		cout<<"Error starting MPI program. Terminating.\n";
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);

	if (procid != 0)
	{
		for (int i = procid - 1; i < 16; i += 4)
		{
			sum += v[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	else
	{
		int aux;
		for (int i = 1; i <= 4; i++)
		{
			MPI_Recv(&aux, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			sum += aux;
		}
		cout << "suma este " << sum << endl;
	}
	
	MPI_Finalize();
	return 0;
}
