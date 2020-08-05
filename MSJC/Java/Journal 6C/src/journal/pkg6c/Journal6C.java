/*
Daniel Meyer
0405182
11-22-14
Journal 6C
FOnts and Colors
 */
package journal.pkg6c;

import java.util.Scanner;
import javax.swing.*;
import java.awt.*;

public class Journal6C extends JFrame
{

    Container content = this.getContentPane();
    
    Font fnt = new Font("serif", Font.BOLD, 50);
    Color foreClr = new Color(100, 205, 75);
    
    JLabel fName = new JLabel("Daniel");
    JLabel lName = new JLabel("Meyer");
    JLabel date = new JLabel("Today's Date: 11-22-14");
    
    public Journal6C()
    {
        content.setLayout(new GridLayout(3,1));
        content.add(fName);
        content.add(lName);
        content.add(date);
        
        fName.setFont(fnt);
        lName.setFont(fnt);
        
        fName.setForeground(foreClr);
        lName.setForeground(Color.GREEN);
        date.setForeground(Color.BLACK);
        
        this.setVisible(true);
        this.setSize(800,600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("GUI App");
        
    }
    
    public static void main(String[] args) 
    {
        Journal6C con = new Journal6C();
    }
    
}
