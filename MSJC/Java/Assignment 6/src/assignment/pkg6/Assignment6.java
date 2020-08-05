/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment.pkg6;

/**
 *
 * @author User
 */
import java.util.Scanner;
import java.text.NumberFormat;

public class Assignment6 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        NumberFormat fmt = NumberFormat.getCurrencyInstance();
        int widgets;
        double price;
        double value1;
        double value2;
        double value3;
        double value4;
        
        System.out.println("How many widgets do you wish to buy?");
        widgets = in.nextInt();
        
        value1 = 5.38;
        value2 = 4.89;
        value3 = 4.66;
        value4 = 4.23;
        
        switch(widgets)
        {
            case 1:
                System.out.println("Total Cost of your widgsts is " + fmt.format(value1));
                break;
            case 2:
                System.out.println("Total Cost of your widgsts is " + fmt.format(value2 * 2));
                break;
            case 3:
                System.out.println("Total Cost of your widgsts is " + fmt.format(value3 * 3));
                break;
            case 4:
                System.out.println("Total Cost of your widgsts is " + fmt.format(value4 * 4));
                break;
            default:
                System.out.println("You are only allowed to purchase up to 4 widgets.");
        }
                
        
        
    }
    
}
