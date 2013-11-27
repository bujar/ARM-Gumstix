set arch armv5te
target remote localhost:1234
add-symbol-file kernel/kernel 0xa3000000
add-symbol-file tasks/bin/simple 0xa0000000
break kmain
break sleepqueue_wake
break fun1
break timer_inc
break ctx_switch_half
break ctx_switch_full
continue
