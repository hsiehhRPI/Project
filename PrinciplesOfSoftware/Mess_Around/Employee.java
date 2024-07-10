class Employee{
   public Employee(String n, String i, double s) {
      name = n;
      salary = s;
      id = i;
   }
   public String getName() {
      return name;
   }
   public double getSalary() {
      return salary;
   }
   public String getId() {
      return id;
   }
   public void raiseSalary(double byPercent) {
      double raise = salary * byPercent / 100;
      salary += raise;
   }
   
   public boolean equals(Employee emp2) {
    if (this.name == emp2.name && this.id == emp2.id) {
        return true;
    }
    return false;
   }

   public int hashCode() {
    String iDval = this.getId();
    int preHash = Integer.parseInt(iDval);
    return preHash%367;
   }

   private String name;
   private double salary;
   // id uniquely identifies any employee, be that Employee, Manager, or any other employee
   private String id;
   public static void main(String[] args) {
    /*Employee emp1 = Employee("Gawain", "111", 60000);
    Employee emp2 = Employee("Lancelot", "112", 56000);
    Employee emp0 = Employee("Gawain", "111", 60000);*/
    Employee emp0 = new Employee("Yi Sang", "ID001", 10.00);
    Employee emp1 = new Employee("Yi Sang", "ID001", 10.00);
    Employee emp2 = new Employee("Faust", "ID002", 14.00);
    System.out.println(emp1.equals(emp0));
    }
}
class Manager extends Employee
{
   public Manager(String n, String i, double s) {
      super(n, i, s);
      bonus = 0;
   }
   public double getSalary() {
      double baseSalary = super.getSalary();
      return baseSalary + bonus;
   }
   public void setBonus(double b) {
      bonus = b;
   }
   private double bonus;
   public static void main (String[] args) {
    Manager mng1 = new Manager("Outis", "012", 15.00);
    Manager mng2 = new Manager("Gregor", "013", 15.00);
    Manager mng3 = new Manager("Outis", "012", 15.00);
    Employee emp1 = new Employee("Outis", "012", 15.00);
    Employee emp2 = new Employee("Outis", "012", 15.00);

    System.out.println(mng3.equals(mng1));
    System.out.println(mng1.equals(emp1));
    System.out.println(mng3.equals(emp1));
    System.out.println(mng3.hashCode());
    System.out.println(emp1.hashCode());


    /*System.out.println(emp2==mng1);
    System.out.println(mng1==emp2);
    System.out.println(mng1.equals(emp2));*/

   }
}