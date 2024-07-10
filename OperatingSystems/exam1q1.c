#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
  struct rlimit rl;
  getrlimit( RLIMIT_NPROC, &rl );
  printf( "RLIMIT_NPROC soft limit: %ld\n", rl.rlim_cur );
  printf( "RLIMIT_NPROC hard limit: %ld\n", rl.rlim_max );

  /* lower the RLIMIT_NPROC soft limit to 20 */
  rl.rlim_cur = 20;
  setrlimit( RLIMIT_NPROC, &rl );

  getrlimit( RLIMIT_NPROC, &rl );
  printf( "RLIMIT_NPROC soft limit: %ld\n", rl.rlim_cur );
  printf( "RLIMIT_NPROC hard limit: %ld\n", rl.rlim_max );

#if 1
  while ( 1 )
  {
    int p = fork();

    if ( p == -1 )
    {
      perror( "fork() failed" );
      return EXIT_FAILURE;
    }

    printf( "PID %d: fork() worked!\n", getpid() );

    /* this gives us some time to shut things down... */
    sleep( 3 );
  }
#endif

  return EXIT_SUCCESS;
}


/*int main()
{
int rc;
printf( "ONE-%u\n", getpid() );
rc = fork();
//#ifdef PARTC
rc = fork();
//#endif
printf( "TWO-%u\n", getpid() );
if ( rc == 0 ) { printf( "THREE-%u\n", getpid() ); }
if ( rc > 0 ) { printf( "FOUR-%u\n", getpid() ); }
return EXIT_SUCCESS;
}*/

/*int main()
{
int x = 2222;
printf( "PARENT: x is %d\n", x );
pid_t p = fork();
printf( "PARENT %d: forked...\n", p );
if ( p == 0 )
{
printf( "CHILD: happy birthday to %d\n", getpid() );
x += 18;
printf( "CHILD: %d\n", x );
}
else
{
//#ifndef PARTC
waitpid( p, NULL, 0 );
//#endif
printf( "PARENT %d: child completed\n", getpid() );
x -= 2000;
printf( "PARENT: %d\n", x );
}
return EXIT_SUCCESS;
}*/
/*
int main() {
	char * a = "POLYTECHNIC";
	char * b = a;
	char * c = calloc( 100, sizeof( char ) );
	printf( "(%s)(%s)(%s)\n", a + 10, b + 9, c + 8 );
	char ** d = calloc( 100, sizeof( char * ) );
	d[7] = calloc( 20, sizeof( char ) );
	d[6] = c;
	strcpy( d[7], b + 5 );
	strcpy( d[6], b + 4 );
	printf( "(%s)(%s)(%s)\n", d[7], d[6], c + 5 );
	free(c);
	free(d[7]);
	free(d);
	float e = 2.71828;
	float * f = calloc( 1, sizeof( float ) );
	float * g = f;
	float * h = &e;
	printf( "(%3.2f)(%2.2f)(%2.3f)\n", *f, *g, *h );
	free(f);
	return EXIT_SUCCESS;
}*/
/*
int main()
{
close( 2 );
printf( "HELLO\n" );
close(1);
#ifdef QUIET
close( SPARKS );
#endif
int fd = open( "output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644 );
printf( "==> %d\n", fd );
printf( "WHAT?\n" );
fprintf( stderr, "ERROR\n" );
close( fd );
return EXIT_SUCCESS;
}*/
/*
int main()
{
	int * pipefd = calloc( 2, sizeof( int ) );
	int rc = pipe( pipefd );
	pid_t p = fork();
	if ( p == 0 )
	{
	//close(*(pipefd+0));
	rc = write( *(pipefd+1), "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26 );
	printf( "PID %u: Wrote %d bytes\n", getpid(), rc );
	//close(*(pipefd+1));
	}
	else
	{
	close(*(pipefd+1));
	char * buffer = calloc( 26, sizeof( char ) );
	rc = read( *(pipefd+0), buffer, 16 );
	printf( "PID %u: Read [%s]\n", getpid(), buffer );
	#ifdef PARTB
	rc = read( *(pipefd+0), buffer, 16 );
	printf( "PID %u: Read [%s]\n", getpid(), buffer );
	#endif
	//#ifdef PARTC
	rc = read( *(pipefd+0), buffer, 16 );
	printf( "PID %u: Read [%s]\n", getpid(), buffer );
	rc = read( *(pipefd+0), buffer, 16 );
	printf( "PID %u: Read [%s]\n", getpid(), buffer );
	close(*(pipefd+0));
	//#endif
	free(pipefd);
	free(buffer);
	}
return EXIT_SUCCESS;
}*/

/*int main() {
	int q = -3;
	char * name = malloc( 16 );
	int * x = calloc( 2, sizeof( int ) );
	int * numbers = calloc( 32, sizeof( int ) );
	double * values = calloc( 32, sizeof( double ) );
	sprintf( name, "ABCD-%04d-EFGH", *x );
	printf( "%12s\n", name + 3 );
	printf( "%*d%%", q, *(numbers + 5) );
	printf( "%10.4lf\n", *(values + 5) );
}*/

