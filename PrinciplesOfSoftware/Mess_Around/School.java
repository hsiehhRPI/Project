
public class School {
    private String name;
    public School(String theName) {
    this.name = theName;
    }
    public static void main(String[] args) {
    School r1 = new School("RPI" + " 1824");
    School r2 = new School(new String("RPI") + " 1824");
    School r3 = new School(r1.name);
    School r4 = r2;
    String s1 = "RPI 1824";
    String s2 = new String("RPI") + " 1824";
    String s3 = r3.name;
    System.out.println(r1 == r3);
    System.out.println("RPI 1824" == r4.name);
    System.out.println(r1.equals(r3));
    System.out.println(r1.name.equals(r3));
    System.out.println(r1.name.equals(r3.name));
    System.out.println(r1.name == "RPI 18" + "24");
    System.out.println(r2.name == "RPI 18" + "24");
    System.out.println(s1 == s2);
    System.out.println(s1.equals(s2));
    System.out.println(s3 == "RPI 1824".toUpperCase());
    }
    }
    