#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

/*Register*/
struct Register {
	char type;		//Register type
	char* varName;	//Name of the variable
	int val;		//Variable value
	int regNum;		//Register number
	int status;		//0 for unoccupied, 1 for occupied 
};


/*Functions*/
//Assign values to register, we will be mainly storing input vars into s registers
void assign(char* vName, int v1, struct Register* reg, int regSize, FILE* out, FILE* err) {
	int n;
	for (n = 10; n < regSize; n+=1 ) {
		if (reg[n].status==0) {
			reg[n].varName = vName;
			reg[n].val = v1;
			reg[n].status = 1;
			fprintf(out, "li $s%d,%d\n", n-10, reg[n].val);
			return;
		}
	}
}

//Determine whether an element in the array is a number
int isNum (char* val) {
	int len = strlen(val);
	int number = 1;
	int v;
	//If negative sign is present
	if (val[0]=='-') {
		return 1;
	}
	for (v = 0; v < len; v+=1) {
		if (isdigit(val[v])==0) {
			number = 0;
			return number;
		}
	}
	return number;
}
//I am not sure whether the command line for compilling our hw will include -lm flag for math library
//Here's for calculating power
int power(int base, int power) {
	int result = 1;
	int n;
	for (n = 0; n < power; n+=1) {
		result *= base;
	}
	return result;
}


//Help find which registers containing target value are used for the operation.
int findRegister1(char** line, int curIdx, int offset, struct Register* reg, int mode) {
	int n = 0;
	if (mode >= 2) {
		//There are two operations, and add is the later(search the whole register)
		for (n = 0; n < 10; n+=1) {
			if (strstr(reg[n].varName, line[curIdx+offset])!=NULL) {
				return n;
			}
		}
	} else if (mode < 2) {
		//Add is either the on(only search s registers)
		for (n = 10; n < 18; n+=1) {
			if (strcmp(line[curIdx+offset], reg[n].varName)==0) {
				return n;
			}
		}
	}
	return n;
}

//Addition/subtraction of two values that are already in registers
void add(char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	//Finding target registers
	//Modes: 3: The two values are both in t registers
		//	 2: One of the value is in t register, another in s register
		//   1: Both values are in s registers
	int rNum1 = 0;
	int rNum2 = 0;
	if (mode == 3) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, mode);
	}
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, 1);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1, reg, mode);
	}
	//Check if said variable is in the same line, and has yet to have anything assigned to it
	int n;
	if (strcmp(line[0], line[curIdx+1])==0) {
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = line[0];
				rNum2 = n;
				break;
			}
		}
	}
	//If we store the result in t registers
	if (mode == 1||mode == 3) {
		//This is an intermediate step, store in t register, t = 1 suggest there are more operations to perform
		int n;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-")==0) {
					//If this is a subtraction operation
					//If register is empty
					reg[n].val = reg[rNum1].val - reg[rNum2].val;
					reg[n].varName = reg[rNum2].varName;
					reg[n].status = 1;
					fprintf(out, "sub $t%d,$%c%d,$%c%d\n",n, reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type,reg[rNum2].regNum);
					return;
				}
				else {
					//If this is an addition operation
					//If register is empty
					reg[n].val = reg[rNum1].val - reg[rNum2].val;
					reg[n].varName = reg[rNum2].varName;
					reg[n].status = 1;
					fprintf(out, "add $t%d,$%c%d,$%c%d\n",n, reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type,reg[rNum2].regNum);
					return;
				}
			}
		}
	}
	else {
		//Store the reuslt in s register
		int n;
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-")==0) {
					//If this is a subtraction operation
					//If register is empty
					reg[n].val = reg[rNum1].val + reg[rNum2].val;
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "sub $%c%d,$%c%d,$%c%d\n",reg[n].type, reg[n].regNum, reg[rNum1].type,reg[rNum1].regNum, reg[rNum2].type,reg[rNum2].regNum);
					return;
				}
				else {
					//If this is an addition operation
					//If register is empty
					reg[n].val = reg[rNum1].val + reg[rNum2].val;
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "add $%c%d, $%c%d,$%c%d\n",reg[n].type, reg[n].regNum, reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type,reg[rNum2].regNum);
					return;
				}
			}
		}
	}
}
//Adding a value in register with a number
void addi(char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	int rNum1 = 0;
	//Find the register used for this operation
	rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	if (mode == 1||mode == 3) {
		//This is an intermediate step, store in t register
		int n;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-") == 0) {
					//If we are actually subtracting numbers
					reg[n].val = reg[rNum1].val - atoi(line[curIdx+1]);
					reg[n].varName = line[curIdx+1];
					reg[n].status = 1;
					fprintf(out, "addi $%c%d,$%c%d,%s\n",reg[n].type, reg[n].regNum, reg[rNum1].type, reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
				else {
					reg[n].val = reg[rNum1].val + atoi(line[curIdx+1]);
					reg[n].varName = line[curIdx+1];
					reg[n].status = 1;
					fprintf(out, "addi $%c%d,$%c%d,%s\n",reg[n].type, reg[n].regNum, reg[rNum1].type, reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
			}
		}
	}
	else {
		int n;
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-")==0) {
					//for subtracting numbers
					reg[n].val = reg[rNum1].val - atoi(line[curIdx+1]);
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "addi $s%d,$%c%d,-%s\n",n-10, reg[rNum1].type,reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
				else {
					//If register is empty
					reg[n].val = reg[rNum1].val + atoi(line[curIdx+1]);
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "addi $s%d,$%c%d,%s\n",n-10, reg[rNum1].type,reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
			}
		}
	}
}

//Multiply values that are stored in registers already
void mul (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	//Find the two registers containing value we are multiplyin
	int rNum1 = 0;
	int rNum2 = 0;
	if (strcmp(line[curIdx-2], "=")!=0) {
		rNum1 = findRegister1(line, curIdx, -1, reg, 2);
		rNum2 = findRegister1(line, curIdx, 1,reg, mode);
	}
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, 1);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1, reg, mode);
	}
	//Check if said variable is in the same line, and has yet to have anything assigned to it
	int n;
	if (strcmp(line[0], line[curIdx+1])==0) {
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = line[0];
				rNum2 = n;
				break;
			}
		}
	}
	//Check if both registers have the same sign
	//Check which t registers are available for intermediate steps, r1 being the high register, r2 being the low	
	if (mode == 1||mode==3) {
			int n;
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = (reg[rNum1].val*reg[rNum2].val);
					reg[n].varName = reg[rNum2].varName;
					fprintf(out ,"mult $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
					fprintf(out, "mflo $%c%d\n", reg[n].type, reg[n].regNum);
					reg[n].status=1;
					return;
				}
			}
		}
		else {
			int n;
			for (n = 10; n < 18; n += 1) {
				if (reg[n].status == 0) {
					reg[n].val = (reg[rNum1].val*reg[rNum2].val);
					reg[n].status=1;
					reg[n].varName = line[curIdx-3];
					fprintf(out, "mult $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
					fprintf(out, "mflo $%c%d\n", reg[n].type, reg[n].regNum);
					return;
				}
			}
		}

}

void muli(char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	int rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	//Check if both registers have the same sign
	int sameSign = 0;
	if (atoi(line[curIdx+1])< 0) {
		sameSign = 1;
	}
	//Multiply by zero
	if (atoi(line[curIdx+1])==0) {
		int n;
		if (mode == 1 || mode ==3) {
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status == 0) {
					reg[n].varName = line[curIdx+1];
					reg[n].val = 0;
					reg[n].status = 1;
					fprintf(out, "li $t%d,0\n",  n);
					return;
				}
			}
		}
		else {
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status == 0) {
					reg[n].varName = line[curIdx+1];
					reg[n].val = 0;
					reg[n].status = 1;
					fprintf(out, "li $s%d,0\n", reg[n].regNum);
					return;
				}
			}
		}
	}
	//Multiply by 1
	if (atoi(line[curIdx+1])==1) {
		int n;
		int r1;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status == 0) {
				r1 = n;
				break;
			}
		}
		reg[r1].status = 1;
		fprintf(out, "move $t%d,$%c%d\n", r1, reg[rNum1].type, reg[rNum1].regNum);
		if (mode == 1 || mode == 3) {
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = reg[rNum1].val;
					reg[n].varName = line[curIdx+1];
					reg[n].status = 1;
					fprintf(out, "move $t%d,$t%d\n", n, r1);
					return;
				}
			}
		}
		else {
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = reg[rNum1].val;
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "move $s%d,$t%d\n", n-10, r1);
					return;
				}
			}
		}
	}
	//multiply by negative 1
	if (atoi(line[curIdx+1])==-1) {
		int n;
		int r1;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status == 0) {
				r1 = n;
				break;
			}
		}
		reg[r1].status = 1;
		fprintf(out, "move $t%d,$%c%d\n", r1, reg[rNum1].type, reg[rNum1].regNum);
		if (mode == 1 || mode == 3) {
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = reg[rNum1].val;
					reg[n].varName = line[curIdx+1];
					reg[n].status = 1;
					fprintf(out, "sub $t%d,$zero,$t%d\n", n, r1);
					return;
				}
			}
		}
		else {
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = reg[rNum1].val;
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					fprintf(out, "sub $s%d,$zero,$t%d\n", n-10, r1);
					return;
				}
			}
		}
	}
	//Check which t registers are available for intermediate steps
	int r1 = 0;
	int r2 = 0;
	int n;
	for (n = 0; n < 9; n+=1) {
		if (reg[n].status ==0&&reg[n+1].status ==0) {
			r1 = n;
			r2 = n+1;
			break;
		}
		else if (reg[n].status == 0 && reg[n+1].status ==1) {
			r1 = n;
			r2 = 0;
			//Cycle back to using $t0
		}
	}
	reg[r1].status = 1;
	reg[r2].status = 1;
	//Finding out if the denominator is power of 2 
	int target = 0;
	if (strcmp(line[curIdx+1], "-") == 0) {
		target = atoi(line[curIdx+2]);
	}
	else {
		target = atoi(line[curIdx+1]);
	}
	int pow2 = 0;
	target = abs(target);
	while (power(2, pow2) <= target) {
		pow2+=1;
	}
	pow2-=1;		//Since now pow2 is greater than target, -1 to get the greatest power of 2 less than target
	if (pow2 < 0) {
		pow2 = 0;
	}
	int hold = pow2;	
	for (n = pow2; n > -1; n-=1) {
		if (target > power(2,n)) {
			reg[r1].val += (reg[rNum1].val*power(2,n));
			reg[r1].status = 1;
			fprintf(out,"sll $t%d,$%c%d,%d\n", r1,reg[rNum1].type,reg[rNum1].regNum,n);
		}
		if (n==hold) {
			fprintf(out, "move $t%d,$t%d\n", r2, r1);
			reg[r2].varName = "tmp";
			target -= power(2,n);
		}
		if (target < power(2, n)) {
		} else if (target-power(2,n) != 0) {
			fprintf(out, "add $t%d,$t%d,$t%d\n", r2, r2, r1);
			target -= power(2,n);
		}
		if (target-power(2,n)==0) {
			if (mode==1||mode ==3) {
				reg[r1].varName = line[curIdx+1];
				if (sameSign == 1) {
					reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+1]));
					fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					fprintf(out, "sub $t%d,$t%d\n", r1, r2);
					return;
				}
				else {
					if (strcmp(line[curIdx+1], "-")==0) {
						reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+2]));
					}
					else {
						reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+1]));
					}
					fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					fprintf(out, "move $t%d,$t%d\n", r1, r2);
					return;
				}
			}
			else {
				int n;
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status==0) {
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					if (sameSign == 1) {
						reg[n].val = (reg[rNum1].val* atoi(line[curIdx+1]));
						fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
						fprintf(out, "sub $%c%d,$zero,$t%d\n", reg[n].type, reg[n].regNum, r2);
						return;
					}
					else {
						reg[n].val = (reg[rNum1].val* atoi(line[curIdx+1]));
						fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
						fprintf(out, "move $s%d,$t%d\n", reg[n].regNum, r2);
						return;
					}
				}
			}
		}
	}
	}

}
//Divide two values already stored in the register
void divide (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	//Find the two registers that contain values for operation
	int rNum1 = 0;
	int rNum2 = 0;
	if (mode == 3) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, mode);
	}
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, 1);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1, reg, mode);
	}
	//Check if said variable is in the same line, and has yet to have anything assigned to it
	int n;
	if (strcmp(line[0], line[curIdx+1])==0) {
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = line[0];
				rNum2 = n;
				break;
			}
		}
	}
	if (reg[rNum2].val == 0) {
	}	
	//Divide the numbers!
	fprintf(out, "div $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
	if (mode == 1||mode == 3) {
		//Store to t register
		int n;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = reg[rNum2].varName;
				reg[n].val = (reg[rNum1].val*reg[rNum2].val);
				reg[n].status = 1;
				fprintf(out, "mflo $t%d\n", reg[n].regNum);
				return;
			}
		}
	}
	else {
		//Store to s register
		int n;
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = line[curIdx-3];
				reg[n].val = (reg[rNum1].val*reg[rNum2].val);
				reg[n].status = 1;
				fprintf(out, "mflo $s%d\n", reg[n].regNum);
				return;
			}
		}
	}
	
}

void divi (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err, int* lIdx) {
	if (atoi(line[curIdx+1])==0) {
		fprintf(err, "Error Divide by zero\n");
	}
	int neg = 0;
	if (atoi(line[curIdx+1]) < 0) {
		neg = 1;
	}
	int rNum1 = 0;
	rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	//Label index
	int labelIdx = *lIdx;
	//Find empty register for storing the result
	//Divide by 1
	if (atoi(line[curIdx+1])==1) {
		int n;
		int r1;
		if (strcmp(line[curIdx-2], "=")==0 && (mode != 1 && mode != 3)) {
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status==0) {
					r1 = n;
					reg[r1].status=1;
					break;
				}
			}
		}
		else {
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status==0) {
					r1 = n;
					reg[r1].status=1;
					break;
				}
			}
		}
		if (r1 < 10) {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx+1];
			fprintf(out, "move $t%d,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return;
		}
		else {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx-3];
			fprintf(out, "move $s%d,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return;
		}
	}
	//Divide by -1
	if (atoi(line[curIdx+1])==-1) {
		int r1;		//Find destination register
		int n;
		if (strcmp(line[curIdx-2], "=")==0) {
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status==0) {
					r1 = n;
					reg[r1].status=1;
					break;
				}
			}
		}
		else {
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status==0) {
					r1 = n;
					reg[r1].status=1;
					break;
				}
			}
		}	//Formulate MIPS line
		if (r1 < 10) {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx+1];
			fprintf(out, "sub $%c%d,$zero,$%c%d\n", reg[r1].type, reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return;
		}
		else {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx-3];
			fprintf(out, "sub $%c%d,$zero,$%c%d\n", reg[r1].type, reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return;
		}
	}
	//Find empty t register
	int r2 = 0;
	int v;
	for (v = 0; v < 10; v+=1) {
		if (reg[v].status == 0) {
			r2 = v;
			reg[r2].status = 1;
			break;
		}
	}

	//Find desintation register
	int r1;
	if (strcmp(line[curIdx-2],"=")==0&&(mode!=1&&mode!=3)) {
		int v;
		for (v = 10; v < 18; v+=1) {
			if (reg[v].status == 0) {
				r1 = v;
				reg[r1].status = 1;
				break;
			}
		}
	}
	else if (mode == 2 || mode == 0){
		int v;
		for (v = 10; v < 18; v+=1) {
			if (reg[v].status == 0) {
				r1 = v;
				reg[r1].status = 1;
				break;
			}
		}
	} else {
		int v;
		for (v = 0; v < 10; v+=1) {
			if (reg[v].status == 0) {
				r1 = v;
				reg[r1].status = 1;
				break;
			}
		}
	}
	//Check if the number we are multiplying is powers of 2
	int isPow2 = 0;		//Flag set to zero for now
	int pow2 = 0;
	int target = abs(atoi(line[curIdx+1]));
	while (power(2, pow2) <= target) {
		if (power(2, pow2) == target) {
			isPow2 = 1;
		}
		pow2 += 1;
	}
	pow2 -= 1;
	if (isPow2==0/*not powers of 2*/) {
		reg[r1].val = (reg[rNum1].val*atoi(line[curIdx+1]));
		if (reg[r1].type =='t') {
			reg[r1].varName = line[curIdx+1];
		}
		else {
			reg[r1].varName = line[curIdx-3];
		}
		reg[r1].status = 1;
		fprintf(out, "li $t%d,%s\n", r2, line[curIdx+1]);
		fprintf(out, "div $%c%d,$t%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[r2].regNum);
		fprintf(out, "mflo $%c%d\n", reg[r1].type, reg[r1].regNum);
	}
	else {
		fprintf(out, "bltz $%c%d,L%d\n", reg[rNum1].type, reg[rNum1].regNum, labelIdx);
		labelIdx+=1;
		int n;
	for (n = pow2; n > -1; n-=1) {
		if (power(2, pow2) >= target) {
			fprintf(out, "srl $%c%d,$%c%d,%d\n", reg[r1].type, reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum, pow2);
			if (neg == 1) {
				fprintf(out, "sub $%c%d,$zero,$%c%d\n", reg[r1].type, reg[r1].regNum, reg[r1].type, reg[r1].regNum);
			}
			fprintf(out, "j L%d\n", labelIdx);
			target-=power(2, pow2);
			fprintf(out, "L%d:\n", labelIdx-1);
			fprintf(out, "li $t%d,%s\n", reg[r2].regNum,line[curIdx+1]);
			fprintf(out, "div $%c%d,$t%d\n", reg[rNum1].type, reg[rNum1].regNum,reg[r2].regNum);
			fprintf(out, "mflo $%c%d\n", reg[r1].type, reg[r1].regNum);
			fprintf(out, "L%d:\n", labelIdx);
			if (strcmp(line[curIdx-2], "=") == 0) {
				reg[r1].val = (reg[rNum1].val/atoi(line[curIdx+1]));
				reg[r1].varName = line[curIdx-3];
			}
			else {
				reg[r1].val = (reg[rNum1].val/atoi(line[curIdx+1]));
				reg[r1].varName = line[curIdx+1];
			}
			return;
		}
	}
	return;
	}
	return;
}

//Find remainder of two values already in register
void modulo (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	int rNum1 = 0;
	int rNum2 = 0;
	if (mode == 3) {
		rNum1 = findRegister1(line, curIdx, -1, reg, 2);
		rNum2 = findRegister1(line, curIdx, 1,reg, 2);
	}
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, 1);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1, reg, mode);
	}
	int n;
	if (strcmp(line[0], line[curIdx+1])==0) {
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = line[0];
				rNum2 = n;
				break;
			}
		}
	}
	fprintf(out, "div $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
	if (mode == 1||mode == 3) {
		//Store to t register
		int n;
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status==0) {
				reg[n].varName = reg[rNum2].varName;
				reg[n].val = (reg[rNum1].val - (reg[rNum1].val/reg[rNum2].val));
				reg[n].status = 1;
				fprintf(out,"mfhi $t%d\n", reg[n].regNum);	//Instead of mflo, we use mfhi to find remainder
				return;
			}
		}
	}
	else {
		//Store to s register
		int n;
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				reg[n].val = (reg[rNum1].val - (reg[rNum1].val/reg[rNum2].val));
				reg[n].status = 1;
				fprintf(out,"mfhi $s%d\n", reg[n].regNum);
				return;
			}
		}
	}
}
//Modulo with an immediate
void modi (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	int rNum1;
	rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	int r1;
	int n; 
	for (n = 0; n < 10; n+=1) {
		if (reg[n].status==0) {
			r1 = n;
			reg[r1].status = 1;
			break;
		}
	}
	reg[r1].status = 1;
	if (mode == 1 || mode == 3) {
		//Load the number onto found temporary register
		fprintf(out, "li $t%d,%s\n", r1, line[curIdx+1]);
		int r2;
		int n;
		//Find desination register
		for (n = 0; n < 10; n+=1) {
			if (reg[n].status==0) {
				r2 = n;
				reg[n].status =1;
				reg[n].val = (reg[rNum1].val%atoi(line[curIdx+1]));
				reg[n].varName = line[curIdx+1];
				break;
			}
		}
		fprintf(out, "div $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[r1].type, reg[r1].regNum);
		fprintf(out, "mfhi $%c%d\n", reg[r2].type, reg[r2].regNum);
		return;
	}
	else {
		//Load the number onto found temporary register
		fprintf(out, "li $t%d,%s\n", r1, line[curIdx+1]);
		int r2;
		int n;
		//Find desination register
		for (n = 10; n < 18; n+=1) {
			if (reg[n].status==0) {
				r2 = n;
				reg[n].status =1;
				reg[n].val = (reg[rNum1].val%atoi(line[curIdx+1]));
				reg[n].varName = line[curIdx-3];
				break;
			}
		}
		fprintf(out, "div $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[r1].type, reg[r1].regNum);
		fprintf(out, "mfhi $%c%d\n", reg[r2].type, reg[r2].regNum);
		return;
	}

}

int lidx = 0;	//To keep track of jump labels

/*------------------------------------------------------------MAIN-------------------------------------------------------------------------------*/
int main (int agrc, char* argv[]) {
	//Determine the number of inputs
	int args = 0;
	while (argv[args]!=NULL) {
		args+=1;
	}
	//Now that the command is done, gotta read the lines from file in inputs.
	char inputs [180][180];
	char line[256];						//Hold the lines that in the file
	int inSize = 0;							//Keep track of n elements in inputs
	FILE* file;
	char* infile = argv[1];
	if (NULL == (file = fopen(infile, "r"))) {			//Check if file condition is good
		printf("Error: fail to open %s\n", infile);
		exit(-1);
	}
	while (fgets(line, 256, file) != NULL) {		//Get the lines, put them in inputs, strip the \n
		strtok(line, "\n");
		strcpy(inputs[inSize], line);
		inSize+=1;
	}
	fclose(file);
	//Output file 
	FILE* outfile;
	FILE* errfile;
	errfile = fopen("STDERR.txt","w");
	outfile = fopen("STDOUT.txt","w");
	int n;
	//Keep track of the registers in use
	struct Register registers[18];//0-9 t registers, 10-18 s registers
	
	//Fill the individual registers
	for (n = 0; n < 10; n+=1) {
		registers[n].varName = "$";
		registers[n].val = 10000;
		registers[n].type = 't';
		registers[n].regNum = n;
		registers[n].status = 0;
	}
	for (n = 0; n < 8; n+=1) {
		registers[n+10].varName = "$";
		registers[n].val = 10000;
		registers[n+10].type = 's';
		registers[n+10].regNum = n;
		registers[n+10].status = 0;
	}
	//Identify which functions are needed by looping through inputs array
	int i;
	for (i = 0; i < inSize; i+=1) {
		fprintf(outfile, "# ");
		fprintf(outfile, "%s\n", inputs[i]);
		//After printing the lines, we are good to parse the line to analyze individual elements.
		char* inLine[180];
		int inLSize = 0;
		strtok(inputs[i], ";");				
		char* sub = strtok(inputs[i], " ");
		while (sub != NULL) {
			inLine[inLSize] = sub;
			sub = strtok(NULL, " ");
			inLSize+=1;
		}
		//After elements are parsed, identify which operations to perform
		int v;
		for (v = 0; v < inLSize; v+=1) {
			//Order these by precedence
			if (strcmp(inLine[v], "*")==0) {
				if (strcmp(inLine[v-2], "=")!=0 && inLSize-v > 2) {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						muli (inLine, v, registers, 3, outfile, errfile);
					}
					else {
						mul(inLine, v, registers, 3, outfile, errfile);
					}
				}
				else if (inLSize-v > 2) {
					//There are more operations to come
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						muli (inLine, v, registers, 1, outfile, errfile);
					}
					else {
						mul(inLine, v, registers, 1, outfile, errfile);
					}
				}
				else {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
					//It is a digit, use addi
						if (inLSize == 5) {
							muli (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							muli (inLine, v, registers, 2, outfile, errfile);
						}
					}
					else {
						if (inLSize == 5) {
							mul (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							mul (inLine, v, registers, 2, outfile, errfile);	
						}
					}
				}
			}
			if (strcmp(inLine[v], "/")==0) {
			//Do division
				if (strcmp(inLine[v-2], "=")!=0 && inLSize-v > 2) {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//Second operand is a number
						divi (inLine, v, registers, 1, outfile, errfile, &lidx);
						lidx+=2;
					}
					else {
						divide (inLine, v, registers, 3, outfile, errfile);
					}
				}
				else if (inLSize-v > 2) {
					//There are more operations to come
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//Second operand is a number
						divi (inLine, v, registers, 1, outfile, errfile, &lidx);
						lidx +=2;
					}
					else {
						divide (inLine, v, registers, 1, outfile, errfile);
					}
				}
				else {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//Second operand is a number
						if (inLSize == 5) {
							divi (inLine, v, registers, 0, outfile, errfile, &lidx);
							lidx +=2;
						}
						else {
							divi (inLine, v, registers, 2, outfile, errfile, &lidx);
							lidx+=2;
						}
					}
					else {
						if (inLSize == 5) {
							divide (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							divide (inLine, v, registers, 2, outfile, errfile);	
						}
					}
				}
			}
			if (strcmp(inLine[v], "%")==0) {
				if (strcmp(inLine[v-2], "=")!=0 && inLSize-v > 2) {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						modi (inLine, v, registers, 3, outfile, errfile);
					} else {
						modulo (inLine, v, registers, 3, outfile, errfile);
					}
				} else if (inLSize-v > 2) {
					//There are more operations to come
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//Second operand is a number
						modi (inLine, v, registers, 1, outfile, errfile);
					}
					else {
						modulo (inLine, v, registers, 1, outfile, errfile);
					}
				}
				else {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
					//It is a digit, use addi
						if (inLSize == 5) {
							modi (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							modi (inLine, v, registers, 2, outfile, errfile);
						}
					}
					else {
						if (inLSize == 5) {
							modulo (inLine, v, registers, 0, outfile, errfile);
						}
						else {	
							modulo (inLine, v, registers, 2, outfile, errfile);	
						}
					}
				}

			}
			if (strcmp(inLine[v], "+")==0) {
				//Need to determine:
				//- Is this operation at the start
				//- Are there more operation that follows
				//- Is it addition between to vars or with numbers
				if (strcmp(inLine[v-2], "=")!=0 && inLSize-v > 2) {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						addi (inLine, v, registers, 3, outfile, errfile);
					}
					else {
						add (inLine, v, registers, 3, outfile, errfile);
					}
				}
				else if (inLSize-v > 2) {
					//There are more operations to come
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						addi (inLine, v, registers, 1, outfile, errfile);
					}
					else {
						add(inLine, v, registers, 1, outfile, errfile);
					}
				}
				else {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
					//It is a digit, use addi
						if (inLSize == 5) {
							addi (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							addi (inLine, v, registers, 2, outfile, errfile);
						}
					}
					else {
						if (inLSize == 5) {
							add (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							add (inLine, v, registers, 2, outfile, errfile);	
						}
					}
				}
				
			}
			if (strcmp(inLine[v], "-")==0) {
				if (strcmp(inLine[v-2], "=")!=0 && inLSize-v > 2) {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						addi (inLine, v, registers, 3, outfile, errfile);
					}
					else {
						add (inLine, v, registers, 3, outfile, errfile);
					}
				} else if (inLSize-v > 2) {
					//There are more operations to come
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
						//It is a digit, use addi
						addi (inLine, v, registers, 1, outfile, errfile);
					}
					else {
						add(inLine, v, registers, 1, outfile, errfile);
					}
				}
				else {
					if (strlen(inLine[v+1])> 1||isNum(inLine[v+1])!=0) {
					//It is a digit, use addi
						if (inLSize == 5) {
							addi (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							addi (inLine, v, registers, 2, outfile, errfile);
						}						
					}
					else {
						if (inLSize == 5) {
							add (inLine, v, registers, 0, outfile, errfile);
						}
						else {
							add (inLine, v, registers, 2, outfile, errfile);	
						}
					}
				}
			}
			if (inLSize==3&&strcmp(inLine[v], "=")==0) {
				//If no operation is done, then the last thing available is assignment
				char* variable;
				variable = inLine[v-1];				
				char* val;
				val = inLine[v+1];
				int value = atoi(val);
				assign(variable, value, registers, 18, outfile, errfile);
			}
		}
	}
	fclose(outfile);
	fclose(errfile);
}