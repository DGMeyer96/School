/*
Daniel Meyer
0405182
11-22-14
Journal 6A
GUI Application
 */
package journal.pkg6a;

import javax.swing.*;
import java.awt.*;
import java.util.Scanner;

public class Journal6A extends JFrame
{

    public Journal6A()
    {
        this.setVisible(true);
        this.setSize(800,600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("GUI App");
    }
    
    public Journal6A(String title)
    {
        this.setVisible(true);
        this.setSize(800,600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle(title);
        
    }
    
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        Journal6A gui = new Journal6A();
        System.out.println("Set application title.");
        String title = in.nextLine();
        Journal6A con = new Journal6A(title);
    }
    
}
