/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package journal.pkg8a;

/**
 *
 * @author User
 */
public class Box 
{
    private int length;
    private int width;
    private int height;
    
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
