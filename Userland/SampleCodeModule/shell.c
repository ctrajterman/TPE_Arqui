
#include <stdlib_user.h>
#include "snake.h"


#define menuDIM 7
#define MAXBUFF 100


void decrease();//PREGUNTARLE A TOTI ALFINAL COMO QUEDAN ESTAS SYSCALLS
void increase();



typedef struct module {
    char * name;
    void (*function)();
}module;



void help();
void snake();
void show_regs();
void font_size();
void printTime(); 
void div0Exc();
void opcodeExc();
extern void div0();

module menu[] ={{"help", help}, {"snake", snake}, {"regvalues",show_regs},{"fontsize", font_size},{"time", printTime},
{"div0", div0}, {"opcode", opcodeExc}};


void help(){
    print("To print the different functions of the shell >> enter: help\n", MAXBUFF);
    print("To play Snake Game >> enter: snake\n", MAXBUFF);
    print("To show snapshot of the Register values >> enter: regvalues\n", MAXBUFF);
    print("To change the font size >> enter: fontsize \n", MAXBUFF);
    print("To show current time >> enter: time \n", MAXBUFF);
    print("To try Divide by Zero Exception>> enter: div0 \n", MAXBUFF);
    print("To try Invalid Opcode Exception >> enter: opcode \n", MAXBUFF);

    return;
}

void opcodeExc(){
    return;
}
void div0Exc(){
    return;

}

void show_regs(){
    return;

}
void snake(){
    char buff[MAXBUFF];

    print("WELCOME TO THE SNAKE-GAME\n", MAXBUFF);
    int correctAmount=0;
    while(!correctAmount){

        print("Write letter \"q\" to exit\nIntroduce Players (1 or 2): ", MAXBUFF);

        getString(buff, MAXBUFF);

        if(buff[0] =='q'&& buff[1] == '\0'){
            return;
        }
        else if(buff[0] =='1'&& buff[1] == '\0'){
            correctAmount=1;
            gameLoop();
        }
        else if (buff[0] =='2' && buff[1] == '\0'){
            correctAmount=1;
            gameLoop();
        }
        else{
            err_print("Invalid amount!! \n",18); 
        }
    }
    paintAll_vd(0x000000);
}


void command_wait(){
    
    print("\n",1);
    print("shell_TP_ARQUI>$ ", MAXBUFF);

    char buff[MAXBUFF];

    getString(buff, MAXBUFF);

    if(strlen(buff)!=0){
        for(int i=0; i<menuDIM; i++){
            if(strcmp(buff,menu[i].name)==0){
                menu[i].function();
                return;
            }
        }
        paintAll_vd(0x000000);
        err_print("Invalid Command!! \n",18);

    }
    
}

void font_size(){
        char buff[MAXBUFF];
    print("Tap the '+' button to increase the font\n", MAXBUFF);
    print("Tap the '-' button to decrease the font ", MAXBUFF);

    getString(buff, MAXBUFF);
    
    if(buff[0]=='+'){
        //increase() ;//Preguntar a toti el nombre
    }
    else if (buff[0]=='-'){
       // decrease();
    }
    else{
         err_print("Invalid amount!! \n",18); 
    }


}


void shell(){
    // print("Available Features:\n",30);
    //  for(int i=0; i<menuDIM; i++){
    //      print(menu[i].name, MAXBUFF);
    //      print("\n", 1);
    //  }

    while(1){
        print("\nAvailable Features:\n",30);
        for(int i=0; i<menuDIM; i++){
            print(menu[i].name, MAXBUFF);
            print("\n", 1);
        }
        command_wait();
    }

    return 0;
}


