/*int divi (char** line, int curIdx, struct Register* reg, int mode, FILE* out, FILE* err, int lIdx) {
	if (atoi(line[curIdx+1])==0) {
		fprintf(err, "Error Divide by zero\n");
	}
	int neg = 0;
	if (atoi(line[curIdx+1]) < 0) {
		neg = 1;
	}
	int rNum1 = 0;
	if (mode == 3) {
		rNum1 = findRegister1(line, curIdx, -1, reg, 2);
	}
	if (mode == 2) {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	}
	else {
		rNum1 = findRegister1(line, curIdx, -1, reg, mode);
	}
	//Label index
	int labelIdx = lIdx;
	printf("%d\n", rNum1);
	//Find empty register for storing the result
	//Divide by 1
	if (atoi(line[curIdx+1])==1) {
		int n;
		int r1;
		if (strcmp(line[curIdx-2], "=")==0 && (mode != 1 || mode != 3)) {
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
			//fprintf(out, "move $t%d,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return labelIdx;
		}
		else {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx-3];
			//fprintf(out, "move $s%d,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return labelIdx;
		}
	}
	//Divide by -1
	if (atoi(line[curIdx+1])==-1) {
		int r1;
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
		}
		if (r1 < 10) {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx+1];
			fprintf(out, "sub $t%d,$zero,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return labelIdx;
		}
		else {
			reg[r1].val = reg[rNum1].val;
			reg[r1].varName = line[curIdx-3];
			fprintf(out, "sub $s%d,$zero,$%c%d\n", reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum);
			return labelIdx;
		}
	}
	int r1;
	if (strcmp(line[curIdx-2],"=")==0&&(mode!=1||mode!=3)) {
		int v;
		for (v = 10; v < 18; v+=1) {
			if (reg[v].status == 0) {
				r1 = v;
				reg[r1].status = 1;
				break;
			}
		}
	}
	else {
		int v;
		for (v = 0; v < 10; v+=1) {
			if (reg[v].status == 0) {
				r1 = v;
				reg[r1].status = 1;
				break;
			}
		}
	}
	printf("%d\n", r1);

	//Find empty t register
	int r2 = 0;
	int v;
	for (v = 0; v < 10; v+=1) {
		if (reg[v].status == 0) {
			r2 = v;
			break;
		}
	}
	printf("%d\n", r2);
	if (labelIdx==0) {
		fprintf(out, "bltz $%c%d,L%d\n", reg[rNum1].type, reg[rNum1].regNum, labelIdx);
	}
	labelIdx+=1;
	//Find the greatest power of 2
	int pow2 = 0;
	int target = abs(atoi(line[curIdx+1]));
	while (power(2, pow2) != target) {
		pow2 += 1;
	}
	printf("%d\n", pow2);	
	int n;
	for (n = pow2; n > -1; n-=1) {
		if (power(2, pow2) >= target) {
			printf("powof2: %d, target: %d\n", power(2, pow2), target);
			fprintf(out, "srl $%c%d,$%c%d,%d\n", reg[r1].type, reg[r1].regNum, reg[rNum1].type, reg[rNum1].regNum, pow2);
			if (neg == 1) {
				fprintf(out, "sub $%c%d,$zero,$%c%d\n", reg[r1].type, reg[r1].regNum, reg[r1].type, reg[r1].regNum);

				//fprintf(out, "sub $%c%d,$zero,$%c%d\n", reg[r1].type, reg[r1].regNum, reg[r1].type, reg[r1].regNum);
			}
			//fprintf(out, "j L%d\n", labelIdx);

			//fprintf(out, "j L%d\n", labelIdx);
			target-=power(2, pow2);
			fprintf(out, "L%d:\n", labelIdx-1);
			fprintf(out, "li $t%d,%s\n", reg[r2].regNum,line[curIdx+1]);
			fprintf(out, "div $%c%d,$t%d\n", reg[rNum1].type, reg[rNum1].regNum,reg[r2].regNum);
			fprintf(out, "mflo $%c%d\n", reg[r1].type, reg[r1].regNum);
			fprintf(out, "L%d:\n", labelIdx);
			if (strcmp(line[curIdx-2], "=")) {
				reg[r1].val = (reg[rNum1].val/atoi(line[curIdx+1]));
				reg[r1].varName = line[curIdx-3];
				printf("%s\n", reg[r1].varName);
			}
			else {
				reg[r1].val = (reg[rNum1].val/atoi(line[curIdx+1]));
				reg[r1].varName = reg[rNum1].varName;
				strcat(reg[r1].varName, line[curIdx+1]);
				printf("%s\n", reg[r1].varName);
			}
			return labelIdx;
		}
	}
	return labelIdx;
}
*/