/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package journal.pkg8b;

/**
 *
 * @author User
 */
public class Rectangle 
{
    private int length;
    private int width;
    
    public Rectangle(int length, int width)
    {
        this.setRectangle(length, width);
    }
    
    public Rectangle()
    {
        this(1,1);
    }
    
    public void setRectangle(int length, int width)
    {
        this.length = length;
        this.width = width;
    }
    
    public int area()
    {
        return this.length * this.width;
    }
    
}
