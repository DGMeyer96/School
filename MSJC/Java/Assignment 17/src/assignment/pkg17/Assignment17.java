/*
Daniel Meyer
0405182
12-6-14
Assignment 17/18
More Events
 */
package assignment.pkg17;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Scanner;
import java.util.Random;

public class Assignment17 extends JFrame implements ActionListener, KeyListener
{

    Container content = this.getContentPane();
    String playerName;
    
    int theNumber = 20;
    int numTries = 0;
    int numGames = 0;
    double amtRemaining = 100.0;
    
    Random randomizer = new Random();
    
    
    JTextField theGuess = new JTextField(10);
    JTextField thePlayer = new JTextField(20);
    
    JLabel bankRoll = new JLabel("100.00 Zipoids");
    JLabel one = new JLabel(" ");
    JLabel two = new JLabel(" ");
    
    JButton newPlayer = new JButton("New player");
    JButton newNumber = new JButton("New Number");
    
    JTextArea theOutput = new JTextArea();
    
    public Assignment17()
    {
        this.setVisible(true);
        this.setSize(500,400);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Guess O'Matic");
        
        content.add(theGuess, BorderLayout.NORTH);
        content.add(bankRoll, BorderLayout.NORTH);
        
        content.add(thePlayer, BorderLayout.SOUTH);
        content.add(newPlayer, BorderLayout.SOUTH);
        content.add(newNumber, BorderLayout.SOUTH);
        
        content.add(theOutput, BorderLayout.CENTER);
        
        JPanel p1 = new JPanel();
        JLabel guess = new JLabel("Make your guess");
        p1.add(guess);
        p1.add(theGuess);
        p1.add(bankRoll);
        content.add(p1, BorderLayout.NORTH);
        
        JPanel p2 = new JPanel();
        p2.add(newPlayer);
        p2.add(thePlayer);
        p2.add(newNumber);
        content.add(p2, BorderLayout.SOUTH);
        
        content.add(one, BorderLayout.EAST);
        content.add(two, BorderLayout.WEST);
        
        JScrollPane scrollArea = new JScrollPane(theOutput);
        content.add(scrollArea, BorderLayout.CENTER);
        
        newPlayer.addActionListener(this);
        newNumber.addActionListener(this);
        
        thePlayer.addKeyListener(this);
        theGuess.addKeyListener(this);
        
        this.newPlayer();
    }
    
    public void newPlayer()
    {
        String str = "";
        theOutput.setText(str);
        theOutput.append("Enter name and press ENTER to begin\n");
        
        theOutput.setEnabled(false);
        theGuess.setEnabled(false);
        newPlayer.setEnabled(false);
        newNumber.setEnabled(false);
        
        theGuess.setBackground(Color.white);
        
        thePlayer.setEnabled(true);
        thePlayer.setText(str);
        thePlayer.grabFocus();
        thePlayer.requestFocus();
        thePlayer.setBackground(Color.yellow);
    }
    
    private void newGame()
    {
        numGames++;
        theNumber = randomizer.nextInt(101);
        numTries = 0;
        this.displayInstructions();
        amtRemaining--;
        this.updateScore();
    }
    
    public void addPlayer()
    {
        playerName = thePlayer.getText();
        if(playerName.equals(""))
            theOutput.append("Please enter a name to play\n");
        else
        {
            amtRemaining = 100;
            numGames = 0;
            this.newGame();
            this.updateScore();
            thePlayer.setEnabled(false);
            thePlayer.setBackground(Color.white);
            newPlayer.setEnabled(true);
            newNumber.setEnabled(true);
            theGuess.setEnabled(true);
            theGuess.grabFocus();
            theGuess.requestFocus();
            theGuess.setBackground(Color.yellow);
        }
    }
    
    public void newGuess()
    {
        String curStr = theGuess.getText();
        int curGuess;
        curGuess = Integer.parseInt(curStr);
        numTries++;
        theOutput.append("Guesses: " + numTries + "\t Current Guess: " + curGuess + "\n");
        if(curGuess == theNumber)
            this.gameWon();
        else
        {
            if(curGuess > theNumber)
                theOutput.append("Try a lower number\n");
            else if(curGuess < theNumber)
                theOutput.append("Try a higher number\n");
            
            theGuess.requestFocus();
            theGuess.grabFocus();
            theGuess.setBackground(Color.yellow);
            theGuess.selectAll();
        }
    }
    
    public void updateScore()
    {
        thePlayer.setText(playerName + "\t" + numGames + "\n");
        bankRoll.setText(amtRemaining + " Zipoids \n");
    }
    
    public void displayInstructions()
    {
        theOutput.append("I'm Thinking of a number bewtween 1 and 100\n");
        theOutput.append("If you guess the number in fewer than 9 tries you'll ear\n");
        theOutput.append("1 try \t 2.00 Zipoids\n");
        theOutput.append("2 try \t 1.75 Zipoids\n");
        theOutput.append("3 try \t 1.50 Zipoids\n");
        theOutput.append("4 try \t 1.25 Zipoids\n");
        theOutput.append("5 try \t 1.00 Zipoids\n");
        theOutput.append("6 try \t 0.75 Zipoids\n");
        theOutput.append("7 try \t 0.50 Zipoids\n");
        theOutput.append("8 try \t 0.25 Zipoids\n");
    }
    
    public void gameWon()
    {
        theOutput.setText("******* WINNER ********\n");
        theOutput.append("1 Zipoid\n" + numTries);
        double curWinnings = 0;
        if(numTries == 1)
            curWinnings = 2;
        else if(numTries == 2)
            curWinnings = 1.75;
        else if(numTries == 3)
            curWinnings = 1.5;
        else if(numTries == 4)
            curWinnings = 1.25;
        else if(numTries == 5)
            curWinnings = 1;
        else if(numTries == 6)
            curWinnings = 0.75;
        else if(numTries == 7)
            curWinnings = 0.5;
        else if(numTries == 8)
            curWinnings = 0.25;
        else if(numTries >= 9)
            curWinnings = 0;
        theOutput.setText(Double.toString(curWinnings));
        amtRemaining+= curWinnings;
        theOutput.append(playerName + " " + amtRemaining);
        theOutput.append("Press 'New Number' to continue\n");
        this.updateScore();
        theGuess.setText("");
        theGuess.setBackground(Color.white);
        theGuess.setEnabled(false);
        newNumber.grabFocus();
        newNumber.requestFocus();
    }
    
     public void actionPerformed(ActionEvent ae) 
    {
        JButton btn = (JButton)ae.getSource();
        if(btn == newPlayer)
            this.newPlayer();
        else
        {
            this.newGame();
            theGuess.setEnabled(true);
            theGuess.requestFocus();
            theGuess.grabFocus();
            theGuess.setBackground(Color.yellow);
        }
    }
    
        public void keyTyped(KeyEvent ke) 
    {
        
        
    }
        
        public void keyPressed(KeyEvent ke) 
    {
        
        
    }

        public void keyReleased(KeyEvent ke) 
    {
        JTextField tf = (JTextField)ke.getSource();
        int key = ke.getKeyCode();
        if(key == KeyEvent.VK_ENTER)
            if(tf == thePlayer)
                this.addPlayer();
            else
                this.newGuess();
    }
        
    public static void main(String[] args) 
    {
        Assignment17 gui = new Assignment17();
        
    }
   
}
