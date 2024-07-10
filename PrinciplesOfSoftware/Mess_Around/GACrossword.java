import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class GACrossword
{
  public static int random( int from, int to )
  {
    return (int)( Math.random() * ( to - from + 1 ) + from );
  }


  public static final int populationSize = 10000;
  public static final double replicationPercentage = 0.02;
  public static final double newMembersPercentage = 0.0;
  public static final double mutationProbability = 0.2;
  public static final int maxGenerations = 50000;
//  public static final double singleLetterMutationProbability = 0.01;

  public static ArrayList<String> words = new ArrayList<String>();
  public static ArrayList<String> words6 = new ArrayList<String>();

  public static void main( String[] args )
  {
    System.out.println( "POPULATION SIZE: " + populationSize );
    System.out.println( "REPLICATION PERCENTAGE: " + replicationPercentage );
    System.out.println( "NEW MEMBERS PERCENTAGE: " + newMembersPercentage );
    System.out.println( "MUTATION PROBABILITY: " + mutationProbability );
    System.out.println( "MAX GENERATIONS: " + maxGenerations );

    // read in 5-letter words
    File f = new File( "five_letterWords.txt" );
    Scanner input = null;

    try {
      input = new Scanner( f );
    } catch ( java.io.FileNotFoundException ex ) {
      System.err.println( "ERROR: " + ex.getMessage() );
      ex.printStackTrace();
      System.exit( 1 );
    }

    // keep looping as long as there's more data to read
    while ( input.hasNext() ) {
      String word = input.next();   // get next word
      if ( word.length() == 5 ) {
        words.add( word );
      }
    }

    File g = new File( "five_six_letter_words.txt" );
    input = null;

    try {
      input = new Scanner( g );
    } catch ( java.io.FileNotFoundException ex ) {
      System.err.println( "ERROR: " + ex.getMessage() );
      ex.printStackTrace();
      System.exit( 1 );
    }

    // keep looping as long as there's more data to read
    while ( input.hasNext() ) {
      String word = input.next();   // get next word
      if ( word.length() == 6 ) {
        words6.add( word );
      }
    }

    System.out.println( "SUCCESSFULLY LOADED " + words.size() + " FIVE-LETTER WORDS" );
    Member population[] = new Member[ populationSize ];

    // Initialize the population by picking five random words for the across direction
    // Input 5 letter words for rows k==0 && k==5
    for ( int i = 0 ; i < populationSize ; i++ ) {
      String[] w = new String[6];
      for ( int k = 0 ; k < 6 ; k++ ) {
        if (k == 0||k==5) {
          int x = random( 0, words.size() - 1 );
          w[k] = words.get( x );
        }
        else {
          int x = random( 0, words6.size() - 1 );
          w[k] = words6.get( x );
        }
      }
      population[i] = new Member( w );
    }

    java.util.Arrays.sort( population );

    System.out.println( "INITIAL RANDOM POPULATION (" + populationSize + "):" );
    for ( int i = 0 ; i < populationSize ; i++ ) {
      System.out.println( population[i] );
    }

    boolean keepGoing = true;
    int generation = 1;

    do
    {
      int totalFitness = 0;
      int maxFitness = 0;
      int maxFitnessCount = 0;
      for ( int i = 0 ; i < populationSize ; i++ ) {
        totalFitness += population[i].fitness();
        if ( population[i].fitness() > maxFitness ) {
          maxFitness = population[i].fitness();
          maxFitnessCount = 1;
        } else if ( population[i].fitness() == maxFitness ) {
          maxFitnessCount++;
        }
        population[i].pickMe = totalFitness;
      }
      System.out.println( "GENERATION " + generation + " (" + populationSize + " MEMBERS)" +
      	": total-fitness=" + totalFitness +
        " max-fitness=" + maxFitness + " (" + maxFitnessCount + " at max)" );
      keepGoing = true;


      int j = 0;
      Member newPopulation[] = new Member[ populationSize ];

      // replicate top members of population (skipping adjacent duplicates)
      System.out.println( "REPLICATING " + (int)( populationSize * replicationPercentage ) +
        " MOST FIT MEMBERS" );
      for ( int i = 0 ; i < populationSize && j < ( populationSize * replicationPercentage ) ; i++ ) {
        if ( j == 0 || ! population[i].chromosome().equals( newPopulation[j-1].chromosome() ) )
          newPopulation[j++] = population[i];
      }

      if ( newMembersPercentage > 0 )
      {
        // add brand new members to the population
        System.out.println( "ADDING " + (int)( populationSize * newMembersPercentage ) +
          " NEW MEMBERS" );
        for ( int i = 0 ; i < ( populationSize * newMembersPercentage ) ; i++ ) {
          String[] w = new String[5];
          for ( int k = 0 ; k < 5 ; k++ ) {
            int x = random( 0, words.size() - 1 );
            w[k] = words.get( x );
          }
          newPopulation[j++] = new Member( w );
        }
      }

      System.out.print( "PERFORMING CROSSOVER/MUTATION OPERATIONS..." );

      int mutations = 0;

      while ( j < populationSize ) {
        int a = random( 0, totalFitness - 1 );
        for ( int i = 0 ; i < populationSize ; i++ ) {
          if ( population[i].pickMe >= a ) { a = i;  break; }
        }
        int b;
        do
        {
          b = random( 0, totalFitness - 1 );
          for ( int i = 0 ; i < populationSize ; i++ ) {
            if ( population[i].pickMe >= b ) { b = i;  break; }
          }
        }
        while ( b == a );

        // crossover top n words of aa with bottom 5-n words of bb:
        int crossoverCutoff = random( 0, 4 ) * 5;
        String aa = crossover( population[a].chromosome(), population[b].chromosome(), crossoverCutoff );
        String bb = crossover( population[b].chromosome(), population[a].chromosome(), crossoverCutoff );
        boolean aaMutated = false;
        boolean bbMutated = false;

        if ( random( 0, 99 ) < ( mutationProbability * 100 ) ) {
          aa = mutate( aa );
          aaMutated = true;
          mutations++;
        }

        if ( random( 0, 99 ) < ( mutationProbability * 100 ) ) {
          bb = mutate( bb );
          bbMutated = true;
          mutations++;
        }

        if ( aa.equals( bb ) ) {
          if ( j < populationSize ) newPopulation[j++] = new Member( aa );
          if ( aaMutated && bbMutated ) mutations--;
        } else {
          if ( j < populationSize ) newPopulation[j++] = new Member( aa );
       	  if ( j < populationSize ) newPopulation[j++] = new Member( bb );
        }

//        System.out.println( "CROSSOVER:\n==> " + population[a] + "\n==> " + population[b] +
//                            "\n====> " + newPopulation[j-2] + "\n====> " + newPopulation[j-1] );
      }

      System.out.println( "(" + mutations + " MUTATIONS)" );

      java.util.Arrays.sort( newPopulation );
      population = newPopulation;
      System.gc();
      if ( ++generation > maxGenerations  ||  maxFitness == 10 ) { keepGoing = false; }
      else if ( generation % 50 == 0 )
      {
        System.out.println( "\n\nPOPULATION:" );
        for ( int i = 0 ; i < /* populationSize */ 20 ; i++ ) {
          System.out.println( population[i] );
        }
      }
    }
    while ( keepGoing );

    System.out.println( "\n\nBEST SOLUTIONS AFTER " + ( generation - 1 ) + " GENERATIONS:" );
//    for ( int i = 0 ; i < ( populationSize * replicationPercentage ) ; i++) {
    for ( int i = 0 ; i < populationSize ; i++ ) {
      System.out.println( population[i] );
    }

  }

  public static String crossover( String a, String b, int pivot ) {
    StringBuilder sb = new StringBuilder();
    for ( int i = 0 ; i < pivot ; i++ ) {
      sb.append( a.charAt( i ) );
    }
    for ( int i = pivot ; i < b.length() ; i++ ) {
      sb.append( b.charAt( i ) );
    }
    return sb.toString();
  }

  // mutate by replacing a word in the across direction
  public static String mutate( String a ) {
      int i = random( 0, 4 );
      return a.substring( 0, i * 5 ) + words.get( random( 0, words.size() - 1 ) ) + a.substring( i * 5 + 5 );
  }

//  public static final String alphabet = "abcdefghijklmnopqrstuvwxyz";

  // mutate by replacing a single letter
//  public static String mutateLetter( String a, double mutationProbability ) {
//    if ( random( 0, 99 ) < ( mutationProbability * 100 ) ) {
//      int i = random( 0, 24 );
//      int j = random( 0, 25 );
//      return a.substring( 0, i ) + alphabet.charAt( j ) + a.substring( i + 1 );
////      System.out.println( "*** MUTATED " + a + " TO " + r + " ***" );
//    }
//    return a;
//  }

  public static String encode( char[][] grid ) {
    StringBuilder sb = new StringBuilder();
    for ( int i = 0 ; i < 6 ; i++ ) {
      for ( int j = 0 ; j < 6 ; j++ ) {
        if (!(i==0&&j==5)||!(i==5&&j==5)) {
          sb.append(grid[i][j]);
        }
      }
    }
    return sb.toString();
  }

  public static char[][] decode( String s ) {
    return null;
  }
}



  class Member implements Comparable
  {
    public char[][] grid;
    public int pickMe;
    private int fitness;
    private String chromosome;
    public Member( String[] words ) {
      this.grid = new char[6][6];
      System.out.println("Got here");
      for ( int i = 0 ; i < 6 ; i++ ) {
        System.out.println(words[i]);
        for ( int j = 0 ; j < 6 ; j++ ) {
          if (i == 0) {
            if (j != 0) {
              this.grid[i][j] = words[i].charAt(j-1);
            }
          }
          else if (i == 5) {
            if (j < 5) {
              this.grid[i][j] = words[i].charAt(j);
            }
          }
          else {
            this.grid[i][j] = words[i].charAt(j);
          }
        }
      }
      this.chromosome = GACrossword.encode( this.grid );
      this.fitness = calcFitness();
      this.pickMe = 0;
    }
    public Member( String words ) {
      this.grid = new char[6][6];
      for ( int i = 0 ; i < 6 ; i++ ) {
        for ( int j = 0 ; j < 6 ; j++ ) {
          this.grid[i][j] = words.charAt( 5 * i + j );
        }
      }
      this.chromosome = GACrossword.encode( this.grid );
      this.fitness = calcFitness();
      this.pickMe = 0;
    }
    public String chromosome() {
      return this.chromosome;
    }
    public int fitness() {
      return this.fitness;
    }
    private int calcFitness() {
      int fitness = 0;
      for ( int i = 0 ; i < 5 ; i++ ) {
        String s = "" + this.grid[i][0] + this.grid[i][1] + this.grid[i][2] + this.grid[i][3] + this.grid[i][4];
        if ( GACrossword.words.contains( s ) ) {
          fitness++;
        }
      }
      for ( int j = 0 ; j < 5 ; j++ ) {
        String s = "" + this.grid[0][j] + this.grid[1][j] + this.grid[2][j] + this.grid[3][j] + this.grid[4][j];
        if ( GACrossword.words.contains( s ) ) {
          fitness++;
        }
      }
      return fitness;
    }
    public int compareTo( Object o ) {
      if ( this.fitness() < ((Member)o).fitness() ) return 1;
      else if ( this.fitness() > ((Member)o).fitness() ) return -1;
      else return ( this.chromosome().compareTo( ((Member)o).chromosome() ) );
    }
    public String toString() {
      return "[" + this.chromosome() + "]  fitness=" + this.fitness();
//      String s = "";
//      for ( int i = 0 ; i < 5 ; i++ ) {
//        for ( int j = 0 ; j < 5 ; j++ ) {
//          s += this.grid[i][j];
//        }
//        s += '\n';
//      }
//      s += "[" + this.chromosome() + "]  fitness=" + this.fitness();
//      return s;
    }
  }