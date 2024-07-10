/*
void add(char** line, int curIdx, struct Register* reg, int regSize, int t) {
	int rNum1;
	int rNum2;
	printf("$error\n");
	printf("%s\n", line[curIdx+1]);
	for (int n = 10; n < 8; n++) {
		if (strcmp(reg[n].varName, line[curIdx-1])==0) {
			rNum1 = reg[n].regNum;
		}
		if (strcmp(reg[n].varName, line[curIdx+1])==0) {
			printf("%s\n", reg[n].varName);
			printf("Reg num: %d\n", reg[n].regNum);
			rNum2 = reg[n].regNum;
		}
	}
	printf("%d\n", rNum2);
	printf("$s%s\n", reg[11].varName);
	printf("$s%d $s%d\n", rNum1, rNum2);
	if (t == 1) {
		printf("$error\n");
		char* tmpN = reg[rNum1+10].varName;
		printf("$error\n");
		strcat(tmpN, reg[rNum2+10].varName);
		printf("$error\n");
		for (int n = 0; n < 10; n++) {
			if (reg[n].status==0) {
				reg[n].varName = tmpN;
				reg[n].val = reg[rNum1+10].val + reg[rNum2+10].val;
				reg[n].status = 1;
				printf("add $t%d,$s%d,$s%d\n", n, rNum1, rNum2);
				return;
			}
		}
	} else {
		for (int n = 10; n < 18; n++) {
			if (reg[n].status==0) {
				reg[n].varName = line[curIdx-3];
				reg[n].val = reg[rNum1+10].val + reg[rNum2+10].val;
				reg[n].status = 1;
				printf("add $t%d,$s%d,$s%d\n", n, rNum1, rNum2);
				return;
			}
		}
	}
}
void addi (char** line, int curIdx, struct Register* reg, int regSize, int t) {
	int rNum1;
	for (int n = 10; n < 8; n++) {
		if (strcmp(reg[n].varName, line[curIdx-1])==0) {
			rNum1 = reg[n].regNum;
		}
		break;
	}
	printf("$s%d\n", rNum1);

	char* tmpN = reg[rNum1+10].varName;
	printf("$error\n");
	strcat(tmpN, "2");
	printf("$error\n");
	if (t == 1) {
		for (int n = 0; n < 10; n++) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-")==0) {
					reg[n].varName = tmpN;
					reg[n].val = reg[rNum1+10].val - atoi(line[curIdx+1]);
					reg[n].status = 1;
					printf("addi $t%d,$s%d,-%s\n", n, rNum1, line[curIdx+1]);
					return;
				}
				else {
					reg[n].varName = tmpN;
					reg[n].val = reg[rNum1+10].val + atoi(line[curIdx+1]);
					reg[n].status = 1;
					printf("addi $t%d,$s%d,%s\n", n, rNum1, line[curIdx+1]);
					return;
				}
			}
		}
	} else {
		for (int n = 10; n < 18; n++) {
			if (strcmp(line[curIdx], "-")==0) {
					reg[n].varName = tmpN;
					reg[n].val = reg[rNum1+10].val - atoi(line[curIdx+1]);
					reg[n].status = 1;
					printf("addi $t%d,$s%d,-%s\n", n, rNum1, line[curIdx+1]);
					return;
				}
				else {
					reg[n].varName = tmpN;
					reg[n].val = reg[rNum1+10].val + atoi(line[curIdx+1]);
					reg[n].status = 1;
					printf("addi $t%d,$s%d,%s\n", n, rNum1, line[curIdx+1]);
					return;
				}
		}
	}
}
*/
/*
for (int n = 10; n < 18; n++) {
			if (reg[n].status==0) {
				if (strcmp(line[curIdx], "-") == 0) {
					//If we are actually subtracting numbers
					reg[n].val = reg[rNum1].val - atoi(line[curIdx+1]);
					reg[n].varName = reg[rNum1].varName;
					strcat(reg[n].varName, "2");
					reg[n].status = 1;
					printf("addi $s%d,$%c%d,-%s\n",n-10, reg[rNum1].type,reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
				else {
					reg[n].val = reg[rNum1].val + atoi(line[curIdx+1]);
					reg[n].varName = reg[rNum1].varName;
					strcat(reg[n].varName, "2");
					reg[n].status = 1;
					printf("addi $s%d,$%c%d,-%s\n",n-10, reg[rNum1].type,reg[rNum1].regNum, line[curIdx+1]);
					return;
				}
			}
		}
	for (int n = pow2; n > -1; n--) {
		if (target > power(2,n)) {
			reg[r1].val += (reg[rNum1].val*power(2,n));
			reg[r1].status = 1;
			printf("sll $t%d,$%c%d,%d\n", r1,reg[rNum1].type,reg[rNum1].regNum,n);
			target -= power(2,n);
		}
		if (strcmp(reg[r2].varName,"$")==0) {
			printf("move $t%d, $t%d\n", r2, r1);
			reg[r2].varName = "tmp";
		}
		else if (target < power(2,n) && target > 0) {
			printf("add $t%d,$t%d,$t%d\n", r2, r2, r1);
		}
		else if (target == power(2,n)) {
			reg[r1].val += (reg[rNum1].val*power(2,n));
			target-= power(2,n);
			printf("add $t%d,$t%d,$%c%d\n", r2, r2, reg[rNum1].type, reg[rNum1].regNum);
		}

	}



	for (int n = pow2; n > 0; n--) {
		if (target >= power(2,n)) {
			reg[r1].val += (reg[rNum1].val*power(2,n));
			reg[r1].status = 1;
			printf("sll $t%d,$%c%d,%d\n", r1,reg[rNum1].type,reg[rNum1].regNum,n);
		}
		if (n==hold) {
			printf("move $t%d, $t%d\n", r2, r1);
			reg[r2].varName = "tmp";
			target -= power(2,n);
		}
		if (target < power(2, n)) {
		} else if (target - power(2,n)!=0) {
			printf("add $t%d,$t%d,$t%d\n", r2, r2, r1);
			target -= power(2,n);
		}
		if (target-power(2,n)==0) {
			if (mode==1) {
				reg[r1].varName = reg[rNum1].varName;
				strcat(reg[r1].varName, "2");
				if (sameSign == 1) {
					reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+1]));
					printf("add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					printf("move $t%d,$t%d\n", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = NULL;
					reg[r2].status == 0;
					return;
				}
				else {
					reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+2])*-1);
					printf("add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					printf("sub $t%d,$zero, $t%d\n", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = NULL;
					reg[r2].status == 0;
					return;
				}
			}
			else {
			for (int n = 10; n < 18; n++) {
				if (reg[n].status==0) {
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					if (sameSign == 1) {
						reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+1]));
						printf("add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
						printf("move $s%d,$t%d\n", reg[n].regNum, r2);
						//Free up the register that is done used
						reg[r2].varName = "$";
						reg[r2].val = NULL;
						reg[r2].status == 0;
						reg[r1].varName = "$";
						reg[r1].val = NULL;
						reg[r1].status == 0;	
						return;
					}
				}
				else {

					reg[r1].val = (reg[rNum1].val* atoi(line[curIdx+2])*-1);
					printf("add $t%d,$t%d,$s%d", r2, r2, reg[rNum1].regNum);
					printf("sub $t%d,$zero, $t%d", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = NULL;
					reg[r2].status == 0;
					reg[r1].varName = "$";
					reg[r1].val = NULL;
					reg[r1].status == 0;	
					return;
				}
			}
		}
	}
	}
	void mul (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err) {
	//Find the two registers containing value we are multiplyin
	int rNum1 = 0;
	int rNum2 = 0;
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1,reg, 1);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
		rNum2 = findRegister1(line, curIdx, 1, reg, mode);
	}
	//Check if both registers have the same sign
	int sameSign = 0;
	if ((reg[rNum1].val < 0 && reg[rNum2].val < 0 )||(reg[rNum1].val >= 0 && reg[rNum2].val >= 0)) {
		sameSign = 1;
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
	//Determine if the second number is power of 2
	int powOf2 = 0;
	int target = abs(reg[rNum2].val);	
	int pow2 = 0;
	while (power(2, pow2) < target) {
		if (target == power(2, pow2)) {
			powOf2 = 1;
		}
	}
	if (powOf2 != 0) {
		pow2 = 0;
	while (power(2, pow2) < target) {
		pow2+=1;
	}
	pow2-=1;		//Since now pow2 is greater than target, -1 to get the greatest power of 2 less than target
	reg[r1].val = 0;
	int hold = pow2;
	for (n = pow2; n > -1; n-=1) {
		if (target > power(2,n)) {
			reg[r1].val += (reg[rNum1].val*power(2,n));
			reg[r1].status = 1;
			fprintf(out, "sll $t%d,$%c%d,%d\n", r1,reg[rNum1].type,reg[rNum1].regNum,n);
		}
		if (n==hold) {
			fprintf(out, "move $t%d,$t%d\n", r2, r1);
			reg[r2].varName = "tmp";
			target -= power(2,n);
		}
		if (target < power(2, n)) {
		} else if (target - power(2,n)!=0) {
			fprintf(out, "add $t%d,$t%d,$t%d\n", r2, r2, r1);
			target -= power(2,n);
		}
		if (target-power(2,n)==0) {
			if (mode==1) {
				reg[r1].varName = reg[rNum1].varName;
				strcat(reg[r1].varName, reg[rNum2].varName);
				reg[r1].val = (reg[rNum1].val* reg[rNum2].val);
				if (sameSign == 1) {
					fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					fprintf(out, "move $t%d,$t%d\n", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = 10000;
					reg[r2].status = 0;
					return;
				}
				else {
					fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
					fprintf(out, "sub $t%d,$zero, $t%d\n", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = 10000;
					reg[r2].status = 0;
					return;
				}
			}
			else {
				int n;
			for (n = 10; n < 18; n+=1) {
				if (reg[n].status==0) {
					reg[r1].val = (reg[rNum1].val* reg[rNum2].val);
					reg[n].varName = line[curIdx-3];
					reg[n].status = 1;
					if (sameSign == 1) {
						fprintf(out, "add $t%d,$t%d,$s%d\n", r2, r2, reg[rNum1].regNum);
						fprintf(out, "move $s%d,$t%d\n", reg[n].regNum, r2);
						//Free up the register that is done used
						reg[r2].varName = "$";
						reg[r2].val = 10000;
						reg[r2].status =0;
						reg[r1].varName = "$";
						reg[r1].val = 10000;
						reg[r1].status = 0;	
						return;
					}
				}
				else {
					fprintf(out, "add $t%d,$t%d,$s%d", r2, r2, reg[rNum1].regNum);
					fprintf(out, "sub $t%d,$zero, $t%d", r1, r2);
					//Free up the register that is done used
					reg[r2].varName = "$";
					reg[r2].val = 10000;
					reg[r2].status = 0;
					reg[r1].varName = "$";
					reg[r1].val = 10000;
					reg[r1].status = 0;	
					return;
				}
			}
		}
	}
	}
	}
	else {
		if (mode == 1) {
			int n;
			for (n = 0; n < 10; n+=1) {
				if (reg[n].status == 0) {
					reg[n].val = (reg[rNum1].val*reg[rNum2].val);
					reg[n].status=1;
					reg[n].varName = reg[rNum1].varName;
					strcat(reg[n].varName, reg[rNum2].varName);
					fprintf(out, "mult $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
					fprintf(out, "mflo $%c%d\n", reg[n].type, reg[n].regNum);
				}
			}
		}
		else {
			int n;
			for (n = 10; n < 18; n += 1) {
				if (reg[n].status == 0) {
					reg[n].val = (reg[rNum1].val*reg[rNum2].val);
					reg[n].status=1;
					reg[n].varName = reg[rNum1].varName;
					strcat(reg[n].varName, reg[rNum2].varName);
					fprintf(out, "mult $%c%d,$%c%d\n", reg[rNum1].type, reg[rNum1].regNum, reg[rNum2].type, reg[rNum2].regNum);
					fprintf(out, "mflo $%c%d\n", reg[n].type, reg[n].regNum);
				}
			}
		}

	}
}


//Find the combination of binary that makes the denominator
	int target = abs(reg[rNum2].val);
	int pow2 = 0;
	while (power(2, pow2) < target) {
		pow2+=1;
	}
	pow2-=1;
	printf("%d\n", pow2);
	//Contrary to divide, we must figure out a sequence of binary that constructs the denominator
	int seq[10];
	int seqSize = 0;
	int hold = target;
	printf("%d\n", hold);
	int reconstruct = 0;
	while (hold != 0) {
		printf("%d\n", hold);
		if (hold - power(2, pow2) >= 0) {
			reconstruct+= power(2, pow2);
			seq[seqSize] = pow2;
			seqSize+=1;
			hold -= power(2, pow2);
			pow2-=1;
		}
		else {
			pow2-=1;
		}
	}
	pow2 = seq[0];
	int lIdx = 0;			//Label index count, for jumping
	fprintf(out, "bltz $s0, L%d", lIdx);
	lIdx+=1;
	int n;
	int v;
	for (n = pow2; n > -1; n+=1) {
		if (reg[rNum1].val < target) {
			for (v = 0; v < seqSize; v+=1) {
				//fprintf("srl $%c%d,$%c%c, n", );
			}
		}
	}

*/