data
	newline: 		.asciiz "\n"
	var1: 			.word 7
	var2:			.word 3
.text
	.align 2
	.globl main
	.globl multiply

main: 
	jal multiply
	jr $ra

multiply:	
		sub $sp, $sp, 1   # allocate stack space to store $ra (return address pointer)
  		sw  $ra, 0($sp)		
  		li $a0, 9				#First argument load to $a0
	  	li $a1, 5 				#Second argument load to $a1
	  	li $a2, 0
	  	li $s0, 0 				#Assign int i = 0
	  	li $s2, 0				#The variable that we are performing multiplication on, initialize to zero
	  	beq $a0, $zero, L1		#Check if either a0 or a1 is 0
	  	beq $a1, $zero, L1	


Loop:	slt $t2, $s0, $a1		


L1: 	li $v1, 0 				#If multiply by zero, set ra to zero and return
		li $v0, 1
		syscall
		li $ra, 0
		jr $ra


.data
	newline: 		.asciiz "\n"
	var1: 			.word 7
	var2:			.word 3
.text
	.align 2
	.globl main
	.globl multiply

main: 
	jal multiply
	jr $ra

multiply:	
		sub $sp, $sp, 16   		# allocate stack for $ra (return address pointer)
  		sw  $ra, 0($sp)	   		# store the storage registers
  		sw  $s0, 4($sp)   
  		sw  $s1, 8($sp)    
  		sw  $s2, 12($sp)
  		li $a0, 9				#First argument load to $a0
	  	li $a1, 5				#Second argument load to $a1
	  	li $a2, 0
	  	li $s0, 0 				#Assign int i = 0
	  	li $s2, 0				#The variable that we are performing multiplication on, initialize to zero
	  	slt $t0, $a0, $zero		#Check if a0 is negative
	  	bne $t0, $zero, L3		#Jump to L3, where checks whether $a1 is also negative
	  	li $s1, 1 				#Set to 1, used for checking conditions

Loop:	
		slt $t0, $s0, $a1
		beq $t0, $zero, Done	#Done looping
		beq $t0, $s1, L2		
		subu $s2, $s2, $a0		#If it is negative		
		addi $s0, $s0, 1   		#Increment i by 1
		j Loop 								

L1:		
		li $v1, 0
		syscall
		li $v0, 4
		la $a2, newline
		syscall
		li $ra, 0
		jr $ra

L2: 	
		add $s2, $s2, $a0		#Mult by negative, subtract instead
		addi $s0, $s0, 1   		#Increment i by 1
		j Loop

L3:		
		slt $t2, $a1, $zero
		bne $t2, $zero, Loop


Done:
		lw $v1, 0($s2)
		li $v0, 1
		syscall
		li $v0, 4
		la $a2, newline
		syscall
		lw $ra, 0($s2)
		jr $ra