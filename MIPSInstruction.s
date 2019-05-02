LUI $t1 0x1234
ORI $t1 $t1 0x5678 // t1=0x12345678
LUI $t2 0x0000
ORI $t2 $t2 0x0000 //t2=0x00000000
SW $t1 0x0000 $t2   //Store 12345678 in address 00000000
ANDI $t1 $t1 0x0000 //t1=0000
LUI $t1 0xABCD 	    //t1=ABCD0000
ORI $t1 $t1 0xEF12  //t1=ABCDEF12
SW $t1 0x0004 $t2   //Store ABCDEF12 in address 00000004
ANDI $t1 $t1 0x0000  
LUI $t1 0x1122 
ORI $t1 $t1 0x3344  // t1=11223344
SW $t1 0x0008 $t2   //Store 11223344 in address 00000008
BEQ $t5 $t6 0x0003  
ORI $t7 $t7 0xFFFF  // t7=0xffff
ORI $t0 $t0 0xDAAD  //t0=0xdaad
ORI $t0 $t0 0xEAAE  //t0=oxfaaf
LW $t3 0x0000 $t2   //t3=12345678 //Skips here
LW $t4 0x0004 $t2   //t4=ABCDEF12
LW $t5 0x0008 $t2    //t5=11223344
ADD $t6 $t3 $t4      //t6=BE02458A   
SW $t6 0x000C $t2    //sTORE BE02458A in address 0000000c
ADD $t0 $t4 $t5      //t0=bcf02256
SUB $t7 $t0 $t4      //t7=11223344
ADD $t1 $t7 $t0      //t1=ce12559a
ADD $t2 $Zero, $Zero
ADD $t3 $t2 $t2
ORI $t2 $t2 0xAA76
OR  $t1 $t1 $t2
ADD $t2 $t3 $t3
ORI $t2 $t2 0x5
LUI $t2 0xA
ADD $t3 $t2 $Zero
MUL $t0 $t2 $t3

