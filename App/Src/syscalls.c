#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>

extern char _end;
extern char _estack;

static char *heap_end = NULL;


/*=========================================================
 * _sbrk
 *=========================================================*/

void *_sbrk(ptrdiff_t increment)
{
    char *prev_heap_end;

    if (heap_end == NULL)
    {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;

    if ((heap_end + increment) > &_estack)
    {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_end += increment;

    return (void *)prev_heap_end;
}


/*=========================================================
 * _write
 *=========================================================*/

int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;

    /*
     * We are currently using our own UART driver.
     *
     * If printf() is later redirected to UART,
     * this function can transmit 'ptr' through UART.
     */

    return len;
}


/*=========================================================
 * _close
 *=========================================================*/

int _close(int file)
{
    (void)file;

    return -1;
}


/*=========================================================
 * _fstat
 *=========================================================*/

int _fstat(int file, struct stat *st)
{
    (void)file;

    if (st != NULL)
    {
        st->st_mode = S_IFCHR;
    }

    return 0;
}


/*=========================================================
 * _isatty
 *=========================================================*/

int _isatty(int file)
{
    (void)file;

    return 1;
}


/*=========================================================
 * _lseek
 *=========================================================*/

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;

    return 0;
}


/*=========================================================
 * _read
 *=========================================================*/

int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;

    return 0;
}


/*=========================================================
 * _kill
 *=========================================================*/

int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;

    errno = EINVAL;

    return -1;
}


/*=========================================================
 * _getpid
 *=========================================================*/

int _getpid(void)
{
    return 1;
}


/*=========================================================
 * _exit
 *=========================================================*/

void _exit(int status)
{
    (void)status;

    while (1)
    {
    }
}