/*
Daniel Meyer
0405182
11-22-14
Journal 6B
The JLabel Component
 */
package journal.pkg6b;

import javax.swing.*;
import java.awt.*;
import java.util.Scanner;

public class Journal6B extends JFrame
{
    Container content = this.getContentPane();
    
    JLabel lbl = new JLabel("Hello World");
            
    public Journal6B()
    {
        /*
        BorderLayout bLayout = new BorderLayout();
        content.setLayout(bLayout);
        content.add(lbl, BorderLayout.CENTER);
        */
        
        /*
        content.setLayout(new FlowLayout());
        content.add(lbl);
        */
        
        
        content.setLayout(new GridLayout(3,1));
        content.add(new JLabel("Daniel"));
        content.add(new JLabel("Meyer"));
        content.add(new JLabel("Today's Date: 11-22-14"));
        
        
        
        this.setVisible(true);
        this.setSize(800,600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("GUI App");
    }
    
    public static void main(String[] args) 
    {
        Journal6B con = new Journal6B();
        
        
    }
    
}
