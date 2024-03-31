
addi $t0, $zero, 10    # Load immediate value 10 into register $t0
addi $t1, $zero, 20    # Load immediate value 20 into register $t1
add $t2, $t0, $t1      # Add the values in $t0 and $t1 and store the result in $t2
sw $t2, 0($zero)       # Store the value of $t2 in memory at address 0
lw $t3, 0($zero)       # Load the value from memory at address 0 into $t3
beq $t2, $t3, end      # Branch to the 'end' label if $t2 equals $t3
j error                # Jump to the 'error' label if the branch is not taken

end:
    j end               # Infinite loop at the 'end' label

error:
    j error             # Infinite loop at the 'error' label