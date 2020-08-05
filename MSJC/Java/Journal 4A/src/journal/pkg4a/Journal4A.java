/*
Daniel Meyer
0405182
11-5-14
Journal 4A
Simple Methods
 */
package journal.pkg4a;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.text.NumberFormat;
public class Journal4A 
{
    public void printName()
    {
        System.out.println("Hello from Daniel.");
    }
    public void SayHello()
    {
        this.printName();
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        System.out.println("Hwo many times do you want to print your name?");
        int count = in.nextInt();
        for(int i = 0; i <= count; i++)
        {
            Journal4A c = new Journal4A();
            c.printName();
            
        }
        
    }
    
}
