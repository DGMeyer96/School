/*
Daniel Meyer
0405182
11-1-14
Journal 3B
Random Numbers
 */
package journal.pkg3b;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.util.Random;
public class Journal3B 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        int max = 122; //ascii for z
        int min = 97; //ascii for a
        for(int i = 0; i <= 10; i++)
        {
        char ch = (char) (rdm.nextInt((max - min) + 1 ) + min); //prints a character between values
        System.out.println(ch);
        //int num = rdm.nextInt(100) + 1;
        //System.out.println(num);
        }

        //int max = 122;
        //int min = 97;
        //int r = rdm.nextInt((max - min) + 1 ) + min;
    }
    
}
