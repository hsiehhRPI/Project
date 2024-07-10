import java.io.*;
import java.util.*;

class Q3 {
  public static void main(String[] args) throws IOException, InputMismatchException {
    FileWriter out = null;
    int count = 0;
    int result = 0;
    Scanner scan = new Scanner(System.in);
    try {
      count = scan.nextInt();
    }
    catch (Exception e) { }
    try {
      try {
        out = new FileWriter("test.dat");
        System.out.println("Successfully opened the file for writing.");
      } catch (IOException e) {
        System.out.println("Unable to open the file.");
      }
      result = 5 / count;
      out.write(result);
      System.out.println("Successfully wrote to the file.");
    } catch (ArithmeticException e) {
        System.out.println("Unable to perform division.");
        throw e;
    } finally {
        if (out != null) {
        try {
            out.close();
            System.out.println("Successfully closed the file.");
        } catch (IOException e) {
            System.out.println("Unable to close the file.");
        }
      }
      scan.close();
    }
    System.out.println("Successfully completed all file I/O.");
  }
}
