set arch armv5te
target remote localhost:1234
add-symbol-file kernel/kernel    0xa3000000
add-symbol-file tasks/bin/argh   0xa0000000
set print pretty on
break sleepqueue_wake
break fun1
break fun2
break fun3
break timer_inc
break dispatch_save
break dispatch_nosave
break dispatch_sleep
break ctx_switch_half
break ctx_switch_full
break launch_task
break kmain 
break main 
continue
