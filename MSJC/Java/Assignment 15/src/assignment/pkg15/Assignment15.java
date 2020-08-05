/*
Daniel Meyer
0405182
11-22-14
Assignment 15
GUI Application
 */
package assignment.pkg15;

import javax.swing.*;
import java.awt.*;

public class Assignment15 extends JFrame
{

    Font nameFont = new Font("serif", Font.BOLD, 30);
    Font dateFont = new Font("monospaced", Font.BOLD + Font.ITALIC, 24);
    
    Color nameColor = new Color(155, 20, 200);
    Color dateColor = new Color(.5F, .2F, 1.0F);
    
    Container content = this.getContentPane();
    
    JLabel lblFName = new JLabel("Daniel");
    JLabel lblLName = new JLabel("Meyer");
    JLabel lblDate = new JLabel("11-22-14");
    
    public Assignment15()
    {
        this.setVisible(true);
        this.setSize(300,300);
        this.setTitle("First GUI App");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLayout(new GridLayout(3,1));
        
        content.add(lblFName);
        lblFName.setFont(nameFont);
        lblFName.setForeground(nameColor);
        
        content.add(lblLName);
        lblLName.setFont(nameFont);
        lblLName.setForeground(nameColor);
        
        content.add(lblDate);
        lblDate.setFont(dateFont);
        lblDate.setForeground(dateColor);
    }
    
    public static void main(String[] args) 
    {
        Assignment15 con = new Assignment15();
    }
    
}
