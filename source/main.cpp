# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <mpi.h>

using namespace std;

int main ();
void timestamp ( );



//****************************************************************************80

int main ()

//****************************************************************************80
{
  int ierr;
  int world_rank;
  int world_size;
  double wtime;
//
//  Initialize MPI.
//
  ierr = MPI_Init ( NULL, NULL);
//
//  Get the number of processes.
//
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &world_size );
//
//  Get the individual process ID.
//
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &world_rank );
//
//  Process 0 prints an introductory message.
//
  if ( world_rank == 0 ) 
  {
    timestamp ( );
    cout << "\n";
    cout << "P" << world_rank << ":  HELLO_MPI - Master process:\n";
    cout << "P" << world_rank << ":    C++/MPI version\n";
    cout << "P" << world_rank << ":    An MPI example program.\n";
    cout << "\n";
    cout << "P" << world_rank << ":    The number of processes is " << world_size << "\n";
    cout << "\n";
  }
//
//  Every process prints a hello.
//
  if ( world_rank == 0 ) 
  {
    wtime = MPI_Wtime ( );
  }
  cout << "P" << world_rank << ":    'Hello, world!'\n";
//
//  Process 0 says goodbye.
//
  if ( world_rank == 0 )
  {
    wtime = MPI_Wtime ( ) - wtime;
    cout << "P" << world_rank << ":    Elapsed wall clock time = " << wtime << " seconds.\n";
  }
//
//  Terminate MPI.
//
  MPI_Finalize ( );
//
//  Terminate.
//
  if ( world_rank == 0 )
  {
    cout << "\n";
    cout << "P" << world_rank << ":  HELLO_MPI:\n";
    cout << "P" << world_rank << ":    Normal end of execution.\n";
    cout << "\n";
    timestamp ( );
  }
  return 0;
}
//****************************************************************************80

void timestamp ( )

//****************************************************************************80
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}
