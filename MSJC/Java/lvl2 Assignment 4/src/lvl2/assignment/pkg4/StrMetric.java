/*
Daniel Meyer
0405182
9-9-15 
Assignent 4
Constructors
 */
package lvl2.assignment.pkg4;

import java.util.Scanner;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class StrMetric 
{
    private String metric;
    
    Lvl2Assignment4 con = new Lvl2Assignment4();
    
    public StrMetric()
    {
        this("");
    }
    
    public StrMetric(byte[] bt)
    {
        //String str = new String(bt);
        this.metric = this.toString(bt);
        
        this.getSumASCII(metric);
        this.getNumVowels(metric);
        this.getNumDigits(metric);
        this.getNumUpperCase(metric);
        this.getLowerCaseDigit(metric);
        
        /*
        this.getSumASCII(metric);
        con.lblSum.setText(metric);
        this.getNumVowels(metric);
        con.lblNumVowels.setText(metric);
        this.getNumDigits(metric);
        con.lblNumDigits.setText(metric);
        this.getNumUpperCase(metric);
        con.lblNumUpper.setText(metric);
        this.getLowerCaseDigit(metric);
        con.lblNumLower.setText(metric);
        */
    }
    
    public StrMetric(char[] ch)
    {
        //String str = new String(ch);
        this.metric = this.toString(ch);
        
        this.getSumASCII(metric);
        this.getNumVowels(metric);
        this.getNumDigits(metric);
        this.getNumUpperCase(metric);
        this.getLowerCaseDigit(metric);
        
        /*
        this.getSumASCII(metric);
        con.lblSum.setText(metric);
        this.getNumVowels(metric);
        con.lblNumVowels.setText(metric);
        this.getNumDigits(metric);
        con.lblNumDigits.setText(metric);
        this.getNumUpperCase(metric);
        con.lblNumUpper.setText(metric);
        this.getLowerCaseDigit(metric);
        con.lblNumLower.setText(metric);
        */
    }
    
    public StrMetric(String str)
    {
        //this.metric = str;
        str = metric;
        //this.getSumASCII(str);
        
        /*
        this.getSumASCII(metric); //how to get results to GUI?
        this.getNumVowels(metric); //need to set metrc back to tf input after each one
        this.getNumDigits(metric);
        this.getNumUpperCase(metric);
        this.getLowerCaseDigit(metric);
        */
        
        /*
        this.getSumASCII(metric);
        con.lblSum.setText(metric);
        str = metric;
        this.getNumVowels(metric);
        con.lblNumVowels.setText(metric);
        str = metric;
        this.getNumDigits(metric);
        con.lblNumDigits.setText(metric);
        str = metric;
        this.getNumUpperCase(metric);
        con.lblNumUpper.setText(metric);
        str = metric;
        this.getLowerCaseDigit(metric);
        con.lblNumLower.setText(metric);
        str = metric;
        */
    }
    
    public int getSumASCII(String str)
    {
        int sum = 0;
        int ascii;
        
        for(int i = 0; i <= str.length(); i++)
        {
            char ch = str.charAt(i);
            ascii = (int)ch;
            sum += ascii;
        }
        
        return sum;
    }
    
    public int getNumVowels(String str)
    {
        int count = 0;
        
        for(int i = 0; i <= str.length(); i++)
        {
            
            if(str.charAt(i) == 'a' || str.charAt(i) == 'A' || str.charAt(i) == 'e' ||
                str.charAt(i) == 'E' || str.charAt(i) == 'i' || str.charAt(i) == 'I' ||
                str.charAt(i) == 'o' || str.charAt(i) == 'O' || str.charAt(i) == 'u' ||
                str.charAt(i) == 'U')
            {
                count++;
            }
        
        }
        
        return count;
    }
    
    public int getNumDigits(String str)
    {
        int count = 0;
        
        for(int i = 0; i <= str.length(); i++)
        {
            
            if(str.charAt(i) == '0' || str.charAt(i) == '1' || str.charAt(i) == '2' ||
                str.charAt(i) == '3' || str.charAt(i) == '4' || str.charAt(i) == '5' ||
                str.charAt(i) == '6' || str.charAt(i) == '7' || str.charAt(i) == '8' ||
                str.charAt(i) == '9')
            {
                count++;
            }
            
        }
        
        return count;
    }
    
    public int getNumUpperCase(String str)
    {
        int count = 0;
        
        for(int i = 0; i <= str.length(); i++)
        {
            if(Character.isUpperCase(str.charAt(i)) == true)
            {
                count++;
            }
        }
        
        return count;
    }
    
    public int getLowerCaseDigit(String str)
    {
        int count = 0;
        
        for(int i = 0; i <= str.length(); i++)
        {
            if(Character.isLowerCase(str.charAt(i)) == true)
            {
                count++;
            }
        }
        
        
        return count;
    }
    
    public String toString(int count) //converts arrays into strings
    {
        String str = "" + count;
        return str;
    }
    
    public String toString(byte[] bt)
    {
        String str = new String(bt);
        return str;
    }
    
    public String toString(char[] ch)
    {
        String str = new String(ch);
        return str;
    }
    
    public void setString(String str) //takes info from textfield
    {
        metric = str;
    }
}
