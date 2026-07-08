 #include "kernel/types.h"
 #include "user/user.h"

 int
 main(int argc, char **argv) {
    int p2c[2];
    int c2p[2];
    char buf;
    char byte = '!';
    
    pipe(p2c);
    pipe(c2p);

    if (fork() == 0) {
        // unused pipes
        close(p2c[1]);
        close(c2p[0]);

        // bounce it back crazy style
        read(p2c[0],&buf,1);
        fprintf(2, "%d: received ping\n", getpid());
        write(c2p[1],&buf,1);

        //cleanup
        close(p2c[0]);        
        close(c2p[1]);
        exit(0);
    } 

    // unused pipes
    close(p2c[0]);
    close(c2p[1]);

    // send byte
    write(p2c[1],&byte,1);
    read(c2p[0],&buf,1);
    fprintf(2, "%d: received pong\n", getpid());

    // cleanup
    close(p2c[1]);
    close(c2p[0]);
    wait(0);
    exit(0);
 }