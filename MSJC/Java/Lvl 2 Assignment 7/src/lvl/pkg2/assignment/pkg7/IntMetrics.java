/*
Daniel Meyer
0405182
9-29-15
Assignment 7
Execptions
 */
package lvl.pkg2.assignment.pkg7;


public class IntMetrics 
{
    
    private int maxDigits;
    private int input;
    
    public IntMetrics()
    {
        setValue(0);
        setLength(3);
    }
    
    public IntMetrics(int num)
    {
        setValue(num);
        setLength(3);
    }
    
    public IntMetrics(int num, int size)
    {
        setValue(num);
        setLength(size);
        
    }
    
    public int[] getArray()
    {
        int[] array = new int[maxDigits];
        
        String digits = Integer.toString(input);
        
        for(int i = 0; i < maxDigits; i++)
        {
            int x = (int)digits.charAt(i) - 48;
            
            array[i] = x;
        }
        
        return array;
    }
    
    public String reverseNums()
    {
        StringBuffer sb = new StringBuffer("");
        
        int rev = 0;
        
        while(input != 0)
        {
            rev = input % 10; //<---- reverse order
            input /= 10;
            sb.insert(0, rev);
        }
        
        return sb.reverse().toString();
    }
    
    public int sum()
    {
        int sum = 0;
        
        while(input != 0)
        {
            sum += input % 10;
            input /= 10;
        }
        
        return sum;
    }
    
    public void setValue(int num)
    {
        int maxDigits = num;
    }
    
    public int getValue()
    {
        return input;
    }
    
    public void setLength(int num)
    {
        maxDigits = num;
    }
    
    public int getLength()
    {
        return maxDigits;
    }
}
