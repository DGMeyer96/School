/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testscratch;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.util.Random;
public class TestScratch 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        /*
        for(char c = 'A'; c <= 'Z'; c++)
        {
            if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            {
                
            }
            else
            {
            System.out.println(c);                
            }

        }
        */
        
        /*
        Scanner in = new Scanner(System.in);
        double balance;
        double rate;
        
        System.out.println("Enter your balance and rate");
        balance = in.nextDouble();
        rate = in.nextDouble();
        
        for(int i = 0; i <= 10; i++)
        {
            double interest = balance * rate / 100;
            balance += interest;
        }
        System.out.println("Your balance after 10 years is " + balance);
        */

        Scanner in = new Scanner(System.in);
        Random rdm = new Random();
        
        System.out.println("Enter an end range value");
        int end = in.nextInt();
        
        int num = rdm.nextInt(end);
        
        int sum = 0;
        
        System.out.println(num);
        while(num < end)
        {
            
            if(num % 2 == 0)
            {
                sum += num;
            }
            num = rdm.nextInt(end);
            //System.out.println(sum);
        }
        System.out.println(sum);
    }
}
