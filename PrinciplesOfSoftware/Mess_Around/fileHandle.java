//Import statements
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class fileHandle {
    //Search register
    static int srcRegIdx(String target, String[] sRegs, String[] tRegs) {
        int retVal = -1;
        for (int n = 0; n < 8; n++) {
            if (sRegs[n].contains(target)) {
                retVal = n;
            }
        }
        for (int n = 0; n < 10; n++) {
            if (tRegs[n].contains(target)) {
                retVal = n;
            }
        }
        return retVal;
    }
    static String srcRegType(String target, String[] sRegs, String[] tRegs) {
        String retVal = "";
        for (int n = 0; n < 8; n++) {
            if (sRegs[n].contains(target)) {
                retVal = "s";
            }
        }
        for (int n = 0; n < 10; n++) {
            if (tRegs[n].contains(target)) {
                retVal = "t";
            }
        }
        return retVal;
    }
    public static void main(String[]args){
        //File handling
        String[] inputs = new String[256];
        int idx = 0;
        try{
        File inFile = new File("ex2.txt");
        Scanner myReader = new Scanner(inFile);
        while (myReader.hasNextLine()) {
            inputs[idx] = myReader.nextLine();
            System.out.println(inputs[idx]);
            idx++;
        }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        }
        //Parse the input
        String[][] parsed = new String[idx][];
        for (int i = 0; i < idx; i++) {
            String[] tmp = inputs[i].split("\\s+");
            //System.out.println(tmp[tmp.length-1]);
            tmp[tmp.length-1] = tmp[tmp.length-1].replace(";", "");
            parsed[i] = tmp;
        }
        //Now that we have the inputs, lets make the registers
        //10 t registers and 8 s registers
        String[] tRegs = new String[] {"*","*","*","*","*","*","*","*","*","*" };
        String[] sRegs = new String[] {"*","*","*","*","*","*","*","*"};
        int tIdx = 0;
        int sIdx = 0;
        //Operation start
        String alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int n = 0; n < idx; n++) {
            for (int v = 0; v < parsed[n].length; v++) {
                //System.out.println(parsed[n][v]);
                if (parsed[n][v].contains("+")) {
                    //System.out.println(parsed[n][v+1].length());
                    if (alphabets.contains(parsed[n][v+1])) {
                        int tg1dx = -1;
                        int tg2dx = -1;
                        String tg1type = "";
                        String tg2type = "";
                        tg1dx = srcRegIdx(parsed[n][v-1], sRegs, tRegs);
                        tg2dx = srcRegIdx(parsed[n][v+1], sRegs, tRegs);
                        tg1type = srcRegType(parsed[n][v-1], sRegs, tRegs);
                        tg2type = srcRegType(parsed[n][v+1], sRegs, tRegs);
                        if (parsed[n][v-2].contains("=")) {
                            System.out.printf("add $s%d, $%s%d, $%s%d\n", sIdx, tg1type, tg1dx, tg2type, tg2dx);
                        }
                        else {
                            System.out.printf("add $t%d, $%s%d, $%s%d\n", tIdx, tg1type, tg1dx, tg2type, tg2dx);
                        }
                    } else {
                        int tg1dx = -1;
                        String tg1type = "";
                        tg1dx = srcRegIdx(parsed[n][v-1], sRegs, tRegs);
                        tg1type = srcRegType(parsed[n][v-1], sRegs, tRegs);
                        if (parsed[n][v-2].contains("=")) {
                            System.out.printf("addi $s%d, $%s%d, %s\n", sIdx, tg1type, tg1dx, parsed[n][v+1]);
                        }
                        else {
                            System.out.printf("addi $t%d, $%s%d, %s\n", tIdx, tg1type, tg1dx, parsed[n][v+1]);
                        }
                    }
                }
                else if (parsed[n][v].contains("-")) {
                    if (alphabets.contains(parsed[n][v+1])) {
                        int tg1dx = -1;
                        int tg2dx = -1;
                        String tg1type = "";
                        String tg2type = "";
                        tg1dx = srcRegIdx(parsed[n][v-1], sRegs, tRegs);
                        tg2dx = srcRegIdx(parsed[n][v+1], sRegs, tRegs);
                        tg1type = srcRegType(parsed[n][v-1], sRegs, tRegs);
                        tg2type = srcRegType(parsed[n][v+1], sRegs, tRegs);
                        if (parsed[n][v-2].contains("=")) {
                            System.out.printf("sub $s%d, $%s%d, $%s%d\n", sIdx, tg1type, tg1dx, tg2type, tg2dx);
                        }
                        else {
                            System.out.printf("sub $t%d, $%s%d, $%s%d\n", tIdx, tg1type, tg1dx, tg2type, tg2dx);
                        }
                    } else {
                        int tg1dx = -1;
                        String tg1type = "";
                        tg1dx = srcRegIdx(parsed[n][v-1], sRegs, tRegs);
                        tg1type = srcRegType(parsed[n][v-1], sRegs, tRegs);
                        if (parsed[n][v-2].contains("=")) {
                            System.out.printf("subi $s%d, $%s%d, %s\n", sIdx, tg1type, tg1dx, parsed[n][v+1]);
                        }
                        else {
                            System.out.printf("subi $t%d, $%s%d, %s\n", tIdx, tg1type, tg1dx, parsed[n][v+1]);
                        }
                    }
                }
                else if (parsed[n][v].contains("*")) {

                }
                else if (parsed[n][v].contains("/")) {

                }
                else if (parsed[n][v].contains("=")) {
                    if (v+2 == parsed[n].length) {
                        if (sIdx == 10) {
                            sIdx = 0;
                        }
                        sRegs[sIdx] = parsed[n][v-1];
                        System.out.printf("li $s%d, %s\n", sIdx, parsed[n][v+1]);
                        sIdx++;
                    }
                }
            }
        }
    }
}
