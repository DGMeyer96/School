/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package journal.pkg8a;


public class Fraction 
{
    private int num;
    private int den;
    
    /**
     *
     */
    public Fraction()
    {
        this(1,1);
        
    }
        
    public Fraction(int n, int d)
    {
        this.num = n;
        this.den = d;
        
    }
    
    Fraction add(Fraction f)
    {
        Fraction tmp = new Fraction();
        tmp.num = (this.num * f.den) + (f.num * this.den);
        tmp.den = f.den * this.den;
        return tmp;      
    }
    
    Fraction sub(Fraction f)
    {
        Fraction tmp = new Fraction();
        tmp.num = (this.num * f.den) - (f.num * this.den);
        tmp.den = f.den * this.den;
        return tmp;
    }
    
    Fraction mul(Fraction f)
    {
        Fraction tmp = new Fraction();
        tmp.num = this.num * f.num;
        tmp.den = this.den * f.den;
        return tmp;
    }
    
    Fraction div(Fraction f)
    {
        Fraction tmp = new Fraction();
        tmp.num = this.num * f.den;
        tmp.den = this.den * f.num;
        
        //in case of an inversion
        if(tmp.den < 0)
        {
            tmp.num*=1;
            tmp.den*=1;
        }
        
        return tmp;
    }
    
    String toFraction()
    {
        String s = num + "/" + den;
        return s;
    }
}
