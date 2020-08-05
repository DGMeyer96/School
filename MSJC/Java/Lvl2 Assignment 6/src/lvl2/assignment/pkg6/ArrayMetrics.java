/*
Daniel Meyer
0405182
9-23-15
Assignment 6
Static Classes and Scroll Bars
 */
package lvl2.assignment.pkg6;

import java.util.Random;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class ArrayMetrics 
{
    
    private ArrayMetrics()
    {
        
    }

    public static double mean(int[] ar)
    {
        double mean = 0;
        
        for(int i = 0; i < 50; i++)
        {
            mean += ar[i];
        }
        mean /= ar.length;
        
        return mean;
    }
    
    public static int max(int[] ar)
    {
        int max = ar[0];
        
        for(int i = 0; i < 50; i++)
        {
            if(ar[i] > max)
            {
                max = ar[i];
            }
        }
        
        return max;
    }
    
    public static int min(int[] ar)
    {
        int min = ar[0];
        
        for(int i = 0; i < 50; i++)
        {
            if(ar[i] < min)
            {
                min = ar[i];
            }
        }
        
        return min;
    }
    
    public static int sum(int[] ar)
    {
        int sum = 0;
        
        for(int i = 0; i < 50; i++)
        {
            sum += ar[i];
        }
        
        return sum;
    }
    
    public static int median(int[] ar)
    {
        int median;
        
        if(ar.length % 2 == 0)
        {
            median = ar[ar.length / 2] + ar[ar.length / 2 - 1];
        }
        else
        {
            median = ar[ar.length / 2];
        }
        
        return median;
    }
    
    
}
