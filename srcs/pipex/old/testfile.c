#include "testheader.h"// ===== test main =====
int main(void)
{
    // create 3 redirections: infile, outfile, append
    t_redirect infile = {.name = "input.txt",  .fd = FAIL, .level = INFILE,  .next = NULL};
    t_redirect outfile = {.name = "output.txt", .fd = FAIL, .level = OUTFILE, .next = NULL};
    t_redirect appendf = {.name = "append.txt", .fd = FAIL, .level = APPEND,  .next = NULL};

    // chain them
    infile.next = &outfile;
    outfile.next = &appendf;

    // call your function
    open_fds(&infile);

    printf("infile fd: %d\n", infile.fd);
    printf("outfile fd: %d\n", outfile.fd);
    printf("append fd: %d\n", appendf.fd);

    return 0;
}
