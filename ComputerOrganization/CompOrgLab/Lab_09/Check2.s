.data
	matrix: .word 5, 6, 7, 8
	newline: 		.asciiz "\n"
###############################################################################################
.text
	.align 2
	.globl main
	.globl multiply
	.globl det
###############################################################################################
main: 
	jal det
	jr $ra	
###############################################################################################
multiply:	
		addi $sp, $sp, -16   	# allocate stack for $ra (return address pointer)
  		sw  $ra, 0($sp)	   		# store the storage registers and return register
  		sw  $s0, 4($sp)   
  		sw  $s1, 8($sp)    
  		sw  $s2, 12($sp)
	  	li $s0, 0 				#Assign int i = 0
	  	li $s2, 0				#The variable for multiply, initialize to zero
	  							#Check condition, must check whether (p*p), (n*p) or (p*n), (n*n)
	  	beq $a0, $zero, Done	#Check for multiply by zero
	  	beq $a1, $zero, Done
	  	slt $t0, $zero, $a0  	#Zero less than a0, set to 1
	  	slt $t1, $zero, $a1		#Zero less than a1, set to 1
	  	bne $t0, $t1, L1		#Check for opposite signs
	  							#If signs are equal, check for double negatives
	  	beq $t0, $zero, L3		#Signs are equal, both negative

Loop:	
		slt $t0, $s0, $a0
		beq $t0, $zero, Done	#Done looping(s0 no longer less than a0)
		add $s2, $s2, $a1		#Add the values
		addi $s0, $s0, 1
		j Loop

L1:		
	slt $t2, $t0, $t1			#Investigate which one is negative
	bne $t2, $zero, L2			#If a0 less than a1, switch the two
	j Loop

L2:
	move $t2, $a0			#Switch vals so negative in a1, pos in a0
	move $a0, $a1
	move $a1, $t2
	j Loop

L3:
	sub $a0, $zero, $a0			#Negate both a0, a1
	sub $a1, $zero, $a1
	j Loop

Done:
	move $a0, $s2				#move $a2, $s2
	li $v0, 1
	syscall
  	la $a0, newline
  	li $v0, 4
  	syscall
  	lw $ra, 0($sp)	   		# store the storage registers and return register
  	lw $s0, 4($sp)   
    lw $s1, 8($sp)    
  	lw $s2, 12($sp)
  	add $sp, $sp, 16   		# allocate stack for $ra (return address pointer)
	jr $ra



###############################################################################################
det:
	addi $sp, $sp, -20 		#Allocate enough space for register ra to be on stack
	sw  $ra, 0($sp)			#Store ra on stack
	sw  $s0, 4($sp)   
	sw  $s1, 8($sp)
	sw  $s2, 12($sp)
	sw  $s3, 16($sp)

	li $s0, 0 				#We use s0 for index
	li $s1, 4				#4 because 4 elements in 2x2 matrix
	la $a2, matrix			#Store and allocate space for matrix


	lw $a0, 0($a2)
	lw $a1, 12($a2)
	jal multiply
	move $s3, $s2
	lw $a0, 4($a2)
	lw $a1, 8($a2)
	jal multiply 
	sub $t7, $s3, $s2
	move $a0, $t7
	li $v0, 1
	syscall
  	la $a0, newline
  	li $v0, 4
  	syscall
	jr $ra
###############################################################################################
