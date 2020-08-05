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
public class Box 
{
    private int length;
    private int width;
    private int height;
    
    public Box(int length, int width, int height)
    {
        this.setBox(length, width, height);
    }
    
    public Box(int length, int width)
    {
        this.setBox(length, width, 1);
    }
    
    public Box()
    {
        this(1,1,1);
    }
    
    public void setBox(int length, int width, int height)
    {
        this.length = length;
        this.width = width;
        this.height = height;
    }
    
    public int areaBox()
    {
        return this.length * this.width * this.height;
    }
}
