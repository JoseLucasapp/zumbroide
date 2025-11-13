#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct editorConfig {
    struct termios orig_termios;
    int screenrows;
    int screencols;
};

struct editorConfig E;

void refreshScreen(){
    write(STDIN_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}
void kys(const char *s){
    refreshScreen();

    perror(s);
    exit(1);
}

char editorReadKey(){
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1){
        if(nread == -1 && errno != EAGAIN) kys("read");
    }

    return c;
}

int getWindowSize(int *rows, int *cols){
    struct winsize ws;

    if(1 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
        editorReadKey();
        return -1;
    }else{
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

void init(){
    if(getWindowSize(&E.screenrows, &E.screencols) == -1) kys("getWindowSize");
}

void editorDrawRows(){
    int y;
    for(y = 0; y < E.screenrows; y++){
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void editorRefreshScreen(){
    refreshScreen();
    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

void disableRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) kys("tcsetattr");
}

void enableRawMode(){
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) kys("tcsetattr");
    atexit(disableRawMode);

    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) kys("tcsetattr");
}

void editorProcessKeypress(){
    char c = editorReadKey();

    switch(c){
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}

int main (){
    enableRawMode();
    init();

    while(1){
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}