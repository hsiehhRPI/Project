class A {
    A m(Object a) { System.out.println("A.m(Object)->A"); return new A(); }
    A m(A a) { System.out.println("A.m(A)->A"); return a; }
    B m(C c) { System.out.println("A.m(C)->B"); return c; }
    }
    class B extends A {
    C m(Integer i) { System.out.println("B.m(Integer)->C"); return new D(); }
    C m(C c) { System.out.println("B.m(C)->C"); return c; }
    B m(B b) { System.out.println("B.m(B)->B"); return b; }
    }
    class C extends B {
    D m(A a) { System.out.println("C.m(A)->D"); return (D)a; }
    D m(int i) { System.out.println("C.m(int)->D"); return new D(); }
    A m(D d) { System.out.println("C.m(D)->A"); return d; }
    }
    class D extends C {
    D m(A a) { System.out.println("D.m(A)->D"); return new D(); }
    C m(D d) { System.out.println("D.m(D)->C"); return d; }
    }

public class quiz8 {
        // Assume the definitions below are placed inside a valid class and method
        public static void main(String[] args) {
            A a1 = new A();
            A a2 = new B();
            A a3 = new C();
            A a4 = new D();
            B b1 = new B();
            B b2 = new C();
            B b3 = new D();
            Object b4 = new B();
            C c1 = new C();
            C c2 = new D();
            D d1 = new D();
        // What is printed by the following method calls?
            b1.m("RPI");
            a1.m(5);
            a3.m(d1);
            c1.m(37);
            b2.m(42);
            a4.m(d1);
            b3.m(b3);
            //b2.m(a2);
            a3.m(new D());
            c2.m(c1);
            a2.m(a2);
            //b4.m(b1);
            //a2 = a3.m(b2);
            //c2 = b2.m(a4);
            c2.m(b4);
        }
}
