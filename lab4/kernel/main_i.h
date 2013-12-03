
#ifndef MAIN_I_H
#define MAIN_I_H

/* main header with extern functions */

extern void S_Handler();
extern void irq_wrapper();
extern void timer_init(void);
int install_handler(int vec_pos, int my_SWIaddr);

/* unused in Lab 4*/
extern int userSetup(int argc, char **argv);

#endif
