import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
public class mian {
    public static void main(String[] args) {
        File f = new File("five_six_letter_words.txt");
        Scanner input = null;

        try {
        input = new Scanner( f );
        } catch ( java.io.FileNotFoundException ex ) {
        System.err.println( "ERROR: " + ex.getMessage() );
        ex.printStackTrace();
        System.exit( 1 );
        }
        while ( input.hasNext() ) {
            String word = input.next();   // get next word
            System.out.println(word);
            /*
             * if ( word.length() == 5 ) {
              words.add( word );
                }
             */

          }
    }
}
