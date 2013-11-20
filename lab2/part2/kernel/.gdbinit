set arch armv5te
target remote localhost:1234
add-symbol-file kernel 0xa3000000
add-symbol-file ../../part1/exittest/exittest 0xa2000000
break main
break main


