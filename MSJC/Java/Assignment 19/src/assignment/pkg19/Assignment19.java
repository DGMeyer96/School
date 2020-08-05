/*
Daniel Meyer
0405182
12-10-14
Assignment 19 & 20
Object Arrays
 */
package assignment.pkg19;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class Assignment19 extends JFrame implements ActionListener, MouseListener
{

    Container content = this.getContentPane();
    
    int firstChoice = -1;
    int tries = 0;
    JLabel lblFirst = new JLabel();   
    JButton btnGame = new JButton("New Game");
    JLabel lblTries = new JLabel("0");
    JPanel pnlControls = new JPanel();
    JPanel pnlBoard = new JPanel();
            
    /*        
    public Assignment19()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Concentration");
        JPanel p = new JPanel();
        content.add(pnlBoard);
        content.add(btnGame);
        
    }
    */
    int nums[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};
    JLabel lblBoard[] = new JLabel[16];
    /*
    JLabel lblBoard[] = new JLabel[16];
    {
        for(int i = 0; i <= 16; i++)
        {
            lblBoard[i] = new JLabel();
            lblBoard[i].setText("");
            lblBoard[i].setOpaque(true);
            lblBoard[i].setBackground(Color.blue);
            lblBoard[i].setForeground(Color.white);
            lblBoard[i].setFont(new Font("Serif", Font.BOLD, 24));
            lblBoard[i].addMouseListener(this);
            lblBoard[i].setName("" + i);
            pnlBoard.add(lblBoard[i], BorderLayout.CENTER);  
        }        
    }
    */
    public void Shuffle()
    {
        int num1;
        int num2;
        int tmp;
        Random r = new Random();
        for(int i = 0; i <= 500; i++)
        {
            num1 = r.nextInt(nums.length);
            num2 = r.nextInt(nums.length);
            tmp = nums[num1];
            nums[num1] = nums[num2];
            nums[num2] = tmp;
        }
    }
    
    
    
    
    public void createLabels()
    {
        pnlBoard.setLayout(new GridLayout(4,4, 5,5));
        for(int i = 0; i <= lblBoard.length; i++)
        {
            lblBoard[i] = new JLabel();
            lblBoard[i].setText("");
            lblBoard[i].setOpaque(true);
            lblBoard[i].setBackground(Color.blue);
            lblBoard[i].setForeground(Color.white);
            lblBoard[i].setFont(new Font("Serif", Font.BOLD, 24));
            lblBoard[i].addMouseListener(this);
            lblBoard[i].setName("" + i);
            pnlBoard.add(lblBoard[i]);  
        }        
    }
    
    
    
    public void actionPerformed(ActionEvent ae) 
    {
        this.Shuffle();
        firstChoice = -1;
        for(int i = 0; i < lblBoard.length; i++)
        {
            lblBoard[i].setText("");
        }
        tries = 0;
        lblTries.setText(Integer.toString(tries));
    }

    public void mouseClicked(MouseEvent me) 
    {
        JLabel l = (JLabel)me.getSource();
        l.getName();
        int theNumber = 0;
        l.setName(Integer.toString(theNumber));
        
        if(firstChoice == -1)
        {
            l.setText(Integer.toString(nums[theNumber]));
            lblFirst = l;
            firstChoice = theNumber;
        }
        else if(nums[theNumber] != nums[firstChoice])
        {
            l.setText(Integer.toString(nums[theNumber]));
            pnlBoard.paintImmediately(0,0, pnlBoard.getWidth(), pnlBoard.getHeight());
            try
            {
                Thread.sleep(250);
            }
            catch(InterruptedException e)
            {
                
            }
            lblFirst.setText("");
            l.setText("");
            lblFirst = null;
            firstChoice = -1;
            tries++;
        }
        else
        {
            l.setText(Integer.toString(nums[theNumber]));
            firstChoice = -1;
            tries++;
        }
        lblTries.setText(Integer.toString(tries));
    }

    public void mousePressed(MouseEvent me) 
    {
        
    }

    public void mouseReleased(MouseEvent me) 
    {
        
    }

    public void mouseEntered(MouseEvent me) 
    {
        
    }

    public void mouseExited(MouseEvent me) 
    {
        
    }
    
    public Assignment19()
    {
        this.setVisible(true);
        this.setSize(400,300);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Concentration");
        content.add(pnlBoard, BorderLayout.NORTH);
        content.add(btnGame);
        
    }
    
    public static void main(String[] args) 
    {
        Assignment19 gui = new Assignment19();
    }
        
}
// Could'nt get all elements to show in GUI and am not sure if there were 
// supposed to be instructions under STEP 4 on the blackboard assignment.