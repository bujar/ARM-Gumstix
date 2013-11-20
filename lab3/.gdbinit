set arch armv5te
target remote localhost:1234
add-symbol-file kernel/kernel       0xa3000000
add-symbol-file tasks/bin/stopwatch 0xa0000000
break main
break C_IRQ_Handler
break sleep
break sleep

