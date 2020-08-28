.data
array1: .word 0, 0, 0
array2: .word 0, 0, 0
array3: .word 0, 0, 0
invalidstring: .asciiz "Invalid Input\n"
ponewon: .asciiz "Player 1 won\n"
ptwowon: .asciiz "Player 2 won\n"
matchtie: .asciiz "Match Tie\n"
enter1: .asciiz "\n"
space1: .asciiz " "
one: .word 1
two: .word 2
three: .word 3
minusthree: .word -3
.text
.globl main

main:
  la $t1, array1
  la $t2, array2
  la $t3, array3
  li $t0, 0 #iterator i
  li $t4, 0 #indicator
  li $t5, 0 #counter


while:		
#1st players turn
		bgt $t5, 8 final
  		li $v0, 5
  		syscall
  		move $t6, $v0 # t6 is a
  		li $v0, 5
  		syscall
  		sub $v0, $v0, 1
  		move $t7, $v0 # t7 is b
  		#subi $t7, $s1, 1
  		bgt $t7, 2, binvalid1
  		blt $t7, 0 binvalid1 #b checked
	 	
	 	bgt $t6, 3, binvalid1
  		blt $t6, 1, binvalid1 #a checked
  		
	 	   beq $t6, 1, PoneAone # if(a == 1) then go to PoneAone
  		j endendif1
	PoneAone:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t1
		lw $s1, 0($t8)
		bne $s1, 0, invalid1 #if array1[b-1] is not equal to zero
		beq $s1, 0, valid1 
	valid1:
		li $s2, 1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif1
	invalid1: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif1;
	endif1:
		j endendif1
		
	endendif1:
  		beq $t6, 2, PoneAtwo # if(a==2) then go to PoneAtwo
  		j endendif2
	PoneAtwo:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t2
		lw $s1, 0($t8)
		bne $s1, 0, invalid2 #if array2[b-1] is not equal to zero
		beq $s1, 0, valid2 
	valid2:
		li $s2, 1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif2;
	invalid2: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif2
	endif2:
		j endendif2
		
	endendif2:
		beq $t6, 3, PoneAthree # if ( a==3) then go to PoneAthree
		j endendif3
	PoneAthree:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t3
		lw $s1, 0($t8)
		bne $s1, 0, invalid3 #if array3[b-1] is not equal to zero
		beq $s1, 0, valid3 
	valid3:
		li $s2, 1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif3;
	invalid3: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif3
	endif3:
		j endendif3
	endendif3:
		#jal showarrayfinal
		jal enter
		jal checker
		
#2nd players turn
	  bgt $t5, 8 final
  li $v0, 5
  syscall
  move $t6, $v0 # t6 is a
  li $v0, 5
  syscall
  sub $v0, $v0, 1
  move $t7, $v0 # t7 is b
  #subi $t7, $s1, 1

  		bgt $t7, 2, binvalid2
  		blt $t7, 0 binvalid2
  		
  beq $t6, 1, PtwoAone # if(a == 1) then go to PoneAone
  j endendif12
	PtwoAone:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t1
		lw $s1, 0($t8)
		bne $s1, 0, invalid12 #if array1[b-1] is not equal to zero
		beq $s1, 0, valid12
	valid12:
		li $s2, -1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif12
	invalid12: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif12;
	endif12:
		j endendif12
		
	endendif12:
  		beq $t6, 2, PtwoAtwo # if(a==2) then go to PtwoAtwo
  		j endendif22
	PtwoAtwo:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t2
		lw $s1, 0($t8)
		bne $s1, 0, invalid22 #if array2[b-1] is not equal to zero
		beq $s1, 0, valid22 
	valid22:
		li $s2, -1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif22;
	invalid22: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif22
	endif22:
		j endendif22
		
	endendif22:
		beq $t6, 3, PtwoAthree # if ( a==3) then go to PtwoAthree
		j endendif32
	PtwoAthree:
		move $t8, $t7
		add $t8, $t8, $t8
		add $t8, $t8, $t8
		add $t8, $t8, $t3
		lw $s1, 0($t8)
		bne $s1, 0, invalid32 #if array3[b-1] is not equal to zero
		beq $s1, 0, valid32 
	valid32:
		li $s2, -1
		sw $s2, 0($t8)
		#sw ($t8), one
		addi $t5, 1 #counter++
		j endif32;
	invalid32: 
		la $a0, invalidstring
		li $v0, 4
		syscall
		j endif32
	endif32:
		j endendif32
	endendif32:
		#jal showarrayfinal
		jal enter
		jal checker
		
		j while

enter:
	la $a0, enter1
	li $v0, 4
	syscall
	jr $ra;
	
checker:
	
	#finding sum of 1st column
	li $s2, 0
	li $t8, 0
	add $t8, $t8, $t8
	add $t8, $t8, $t8
	
	add $s1, $t8, $t1 #array1[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t2 #array2[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t3 #array3[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
		
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#li $v0, 1
	#syscall  #sum of 1st column
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	beq $s2, $s3, final2 #p2 won
	
	#finding sum of 2nd column
	li $s2, 0
	li $t8, 1
	add $t8, $t8, $t8
	add $t8, $t8, $t8
	
	add $s1, $t8, $t1 #array1[1]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t2 #array2[1]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t3 #array3[1]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
		
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#li $v0, 1
	#syscall #sum of 2nd column
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	
	beq $s2, $s3, final2 #p2 won
	
	#finding sum of 3rd column
	li $s2, 0
	li $t8, 2
	add $t8, $t8, $t8
	add $t8, $t8, $t8
	
	add $s1, $t8, $t1 #array1[2]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t2 #array2[2]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	add $s1, $t8, $t3 #array3[2]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
		
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#li $v0, 1
	#syscall #sum of 3rd column
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	beq $s2, $s3, final2 #p2 won
	
	#columns end
	
	#1st Row
	li $s2, 0
	li $s1, 0
	li $t8, 0
	add $s1, $t8, $t1 #array1[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3		
	
	#addu $s1, $s1, 4
	#lw $s3, 0($s1)
	#add $s2, $s2, $s3
	
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#li $v0, 1
	#syscall #sum of 1st row
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	beq $s2, $s3, final2 #p2 won
	
	#2nd Row
	li $s2, 0
	li $t8, 0
	li $s1, 0
	add $s1, $t8, $t2 #array2[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3		
	
	#addu $s1, $s1, 4
	#lw $s3, 0($s1)
	#add $s2, $s2, $s3
	
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#li $v0, 1
	#syscall #sum of 2nd row
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	
	beq $s2, $s3, final2 #p2 won
	
	#3rd Row
	li $s1, 0
	li $s2, 0
	li $t8, 0
	add $s1, $t8, $t3 #array3[0]
	lw $s3, 0($s1)
	add $s2, $s2, $s3
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3 #array3[1]
	
	addu $s1, $s1, 4
	lw $s3, 0($s1)
	add $s2, $s2, $s3	#array3[2]	
	
	#addu $s1, $s1, 4
	#lw $s3, 0($s1)
	#add $s2, $s2, $s3
	
	la $s3, three #if sum is 3
	lw $s3, ($s3)
	
	#move $a0, $s2
	#i $v0, 1
	#syscall #sum of 3rd Row
	
	beq $s2, $s3, final1 # p1 won
	
	la $s3, minusthree #if sum is -3
	lw $s3, ($s3)
	
	
	beq $s2, $s3, final2 #p2 won
	
	
	#1st diagonal
	li $s2, 0
		#array1[0]
		li $t8, 0
		add $s1, $t8, $t1 #array1[0]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		#array2[1]
		li $t8, 4
		add $s1, $t8, $t2 #array2[1]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		li $t8, 8
		add $s1, $t8, $t3 #array3[2]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		la $s3, three #if sum is 3
		lw $s3, ($s3)
	
		#move $a0, $s2
		#li $v0, 1
		#syscall #sum of 1st diagonal
	
		beq $s2, $s3, final1 # p1 won
	
		la $s3, minusthree #if sum is -3
		lw $s3, ($s3)
	
	
		beq $s2, $s3, final2 #p2 won
		
	#2nd diagonal
	li $s2, 0
		#array3[0]
		li $t8, 0
		add $s1, $t8, $t3 #array3[0]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		#array2[1]
		li $t8, 4
		add $s1, $t8, $t2 #array2[1]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		li $t8, 8
		add $s1, $t8, $t1 #array1[2]
		lw $s3, 0($s1)
		add $s2, $s2, $s3
		
		la $s3, three #if sum is 3
		lw $s3, ($s3)
	
		#move $a0, $s2
		#li $v0, 1
		#syscall #sum of 2nd diagonal
	
		beq $s2, $s3, final1 # p1 won
	
		la $s3, minusthree #if sum is -3
		lw $s3, ($s3)
	
		beq $s2, $s3, final2 #p2 won
		
	jr $ra
	
binvalid1:
	la $a0, invalidstring
	li $v0, 4
	syscall
	j endendif3
	
binvalid2:
	la $a0, invalidstring
	li $v0, 4
	syscall
	j endendif32
	
showarrayfinal:
	#array1
	li $t8, 0
	add $s1, $t8, $t1
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(1,1)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(1,2)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(1,3)
	
	la $a0, enter1
	li $v0, 4
	syscall #newline
	
	#array2
	li $t8, 0
	add $s1, $t8, $t2
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(2,1)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(2,2)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(2,3)
	
	la $a0, enter1
	li $v0, 4
	syscall #newline
	
	#array3
	li $t8, 0
	add $s1, $t8, $t3
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(3,1)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(3,2)
	
	la $a0, space1
	li $v0, 4
	syscall #space
	
	addu $s1, 4
	lw $a0, 0($s1)
	li $v0, 1
	syscall #(3,3)
	
	la $a0, enter1
	li $v0, 4
	syscall #newline
										
	jr $ra																											


final:

tie:
	la $a0, matchtie
	li $v0, 4
	syscall
	j exit;

final1:
	la $a0, ponewon
	li $v0, 4
	syscall
	j exit;
	
final2:
	la $a0, ptwowon
	li $v0, 4
	syscall
	j exit;
exit:
	jal showarrayfinal
	li $v0, 10
	syscall
