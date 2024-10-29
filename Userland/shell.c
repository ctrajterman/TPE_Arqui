#include <stdlib_user.h>


#define menuDIM 6
#define MAXBUFF 100
typedef struct module {
    char * name;
    void (*function)()
}module;


module * menu ={{"help", help}, {"snake", snake}, {"regvalues",show_regs}, {"time", printTime},
{"div0", div0exc}, {"opcode", opcodeExc}};


void help(){
    print("To print the different functions of the shell >> enter: help\n", MAXBUFF);
    print("To play Snake Game >> enter: snake\n", MAXBUFF);
    print("To show snapshot of the Register values >> enter: regvalues\n", MAXBUFF);
    print("To show current time >> enter: time \n", MAXBUFF);
    print("To try Divide by Zero Exception>> enter: div0 \n", MAXBUFF);
    print("To try Invalid Opcode Exception >> enter: opcode \n", MAXBUFF);
    return;
}

int main(){
    print("Available Features:\n",30);
    for(int i=0; i<menuDIM; i++){
        print(menu[i].name, MAXBUFF);
        print("\n", 1);
    }
    while(1){
        command_wait();
    }
}

void command_wait(){
char buff[MAXBUFF];
getString(buff, MAXBUFF);

if(strlen(buff)!=0){
    for(int i=0; i<menuDIM; i++){
        if(strcmp(buff,menu[i].name)==0){
            menu[i].function();
        }
    }
    err_print("Invalid Command!! \n",18); 
    return;
}
return;

}