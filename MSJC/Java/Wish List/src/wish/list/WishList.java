/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wish.list;

import java.util.Scanner;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class WishList extends JFrame
                //implements ActionListener

{
    /*
    Container content = this.getContentPane();
    JButton ps3 = new JButton("Playstation 3");
    boolean toggle = false;
    
    public WishList()
    {
        this.setVisible(true);
        this.setSize(800,600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Daniel Wish List");
        
        this.setLayout(new GridLayout(6,2));
        ps3.addActionListener(this);
    }
    
    public void actionPerformed(ActionEvent ae)
    {
        if(toggle == true)
            
            
            
    }
    */
    
    public static void main(String[] args) 
    {
        WishList gui = new WishList();
        Scanner in = new Scanner(System.in);
        
        
        
        int choice;
        int playstation;
        int dnd;
        
        System.out.println("Daniel's Wish List");
        System.out.println("Importance in descending order.\n");
        System.out.println("1. Playstation 3");
        System.out.println("2. Playstation 4 Controller - $60");
        System.out.println("3. NZXT Phantom Full Tower (Black, Orang/Black, "
                + "White) - $120");
        System.out.println("4. StarCraft BattleChest - $20");
        System.out.println("5. StarCraft 2 Heart of the Swarm Expansion - $20");
        System.out.println("6. Android Netrunner The Living Card Game by Fantasy"
                + " Flight Games - $30");
        System.out.println("7. Civilization: The Board Game by Fantasy Flight "
                + "Games - $60");
        System.out.println("8. Battlestar Gallactica Board Game by Fantasy "
                + "Flight Games - $50");
        System.out.println("9. Nvidia Wireless Controller - $60");
        System.out.println("10. Shadowrun RPG 5th Edition - $60");
        System.out.println("11. Steam Gift Cards");
        System.out.println("12. Dungeons and Dragons 5th Edtion");
        System.out.println("13. A Game of Thrones Books - $50\n");
        choice = in.nextInt();
        
        switch(choice)
        {
            case 1:
                System.out.println("\n1. Playstation 3 SLIM Game Console - "
                        + "120GB+, $200+, Refurbished and Used O.K.");
                System.out.println("2. Final Fantasy X/X-2 HD");
                System.out.println("3. Killzone Trilogy");
                System.out.println("4. Resistance Collection");
                System.out.println("5. Kingdom Hearts 1.5 & 2.5 HD Remix");
                System.out.println("6. InFamous Collection");
                System.out.println("7. Metal Gear Solid: The Legacy Collection");
                System.out.println("8. Uncharted 1-3");
                System.out.println("9. Ratchet and Clank Collection");
                System.out.println("10. The Sly Cooper Collection");
                playstation = in.nextInt();
                switch(playstation)
                {
                    case 1:
                        System.out.println("\nhttp://www.gamestop.com/ps3/"
                                + "consoles/playstation-3-system-120gb-slim-"
                                + "gamestop-premium-refurbished/101890");
                        break;
                    case 2:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games/"
                                + "final-fantasy-x-x2-hd/110038");
                        break;
                    case 3:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games/"
                                + "killzone-trilogy/104688");
                        break;
                    case 4:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games/"
                                + "resistance-collection/105837");
                        break;
                    case 5:
                        System.out.println("\nKingdom Hearts HD 1.5 - http://"
                                + "www.gamestop.com/ps3/games/kingdom-hearts-hd-"
                                + "15-remix/108233");
                        System.out.println("Kingdom Hearts HD 2.5 - http://www."
                                + "gamestop.com/ps3/games/kingdom-hearts-25-"
                                + "remix-limited-edition/115413");
                        break;
                    case 6:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games"
                                + "/infamous-collection/104053");
                        break;
                    case 7:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games"
                                + "/metal-gear-solid-the-legacy-collection/"
                                + "110199");
                        break;
                    case 8:
                        System.out.println("\nUncharted 1 - http://www.gamestop."
                                + "com/ps3/games/uncharted-drakes-fortune/64961");
                        System.out.println("Uncharted 2 - http://www.gamestop."
                                + "com/ps3/games/uncharted-2-among-thieves/73462");
                        System.out.println("Uncharted 3 - http://www.gamestop."
                                + "com/ps3/games/uncharted-3-game-of-the-year-"
                                + "edition/104763");
                        break;
                    case 9:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games/"
                                + "ratchet-clank-collection/99963");
                        break;
                    case 10:
                        System.out.println("\nhttp://www.gamestop.com/ps3/games/"
                                + "the-sly-collection/78155");
                        break;
                    default:
                        System.out.println("Invalid Choice");
                break;
                }
            case 2:
                System.out.println("\nhttp://www.amazon.com/DualShock-Wireless-"
                        + "Controller-PlayStation-Black-4/dp/B00BGA9X9W");
                break;
            case 3:
                System.out.println("\nhttp://www.nzxt.com/product/detail/34-"
                        + "phantom");
                break;
            case 4:
                System.out.println("\nhttp://www.amazon.com/StarCraft-Battle-"
                        + "Chest-Mac/dp/B00001IVRD/ref=sr_1_1?s=videogames&ie="
                        + "UTF8&qid=1415490232&sr=1-1&keywords=starcraft+battle+"
                        + "chest");
                break;
            case 5:
                System.out.println("\nhttp://www.amazon.com/StarCraft-II-Heart-"
                        + "Swarm-Expansion-Pc/dp/B002I0KP4G/ref=pd_sim_vg_4?ie="
                        + "UTF8&refRID=0J54R91ASNNJR61KB2E0");
                break;
            case 6:
                System.out.println("\nhttp://www.fantasyflightgames.com/edge_"
                        + "minisite_sec.asp?eidm=207&esem=2&esum=227");
                System.out.println("http://www.amazon.com/Android-Netrunner-"
                        + "The-Card-Game/dp/1616614609/ref=sr_1_1?s=toys-and-"
                        + "games&ie=UTF8&qid=1414714580&sr=1-1&keywords=android"
                        + "+netrunner");
                break;
            case 7:
                System.out.println("\nhttp://www.fantasyflightgames.com/edge_mi"
                        + "nisite_sec.asp?eidm=128&esem=2");
                System.out.println("http://www.amazon.com/Fantasy-Flight-Games-"
                        + "CI01-Civilization/dp/1589949358/ref=sr_1_1?s=toys-and"
                        + "-games&ie=UTF8&qid=1414714637&sr=1-1&keywords="
                        + "civilization+board+game");
                break;
            case 8:
                System.out.println("\nhttp://www.fantasyflightgames.com/edge_"
                        + "minisite_sec.asp?eidm=18&esem=2");
                System.out.println("http://www.amazon.com/Fantasy-Flight-Games-"
                        + "BSG01-Battlestar/dp/1589944607/ref=sr_1_1?s=toys-and-"
                        + "games&ie=UTF8&qid=1414714676&sr=1-1&keywords=battles"
                        + "tar+galactica+board+game");
                break;
            case 9:
                System.out.println("\nhttp://shield.nvidia.com/wireless-game-"
                        + "controller/");
                break;
            case 10:
                System.out.println("\nhttp://www.barnesandnoble.com/w/shadowrun-"
                        + "rpg-5th-edition-catalyst-game-labs/1116969382?ean="
                        + "9781936876518");
                break;
            case 11:
                System.out.println("\nhttp://www.gamestop.com/collection/steam-"
                        + "cards");
                break;
            case 12:
                System.out.println("\n1. Player Handbook");
                System.out.println("2. Monster Manual");
                System.out.println("3. Dungeon Master Guide");
                dnd = in.nextInt();
                switch(dnd)
                {
                    case 1:
                        System.out.println("\nhttp://www.amazon.com/Players-"
                                + "Handbook-Dungeons-Dragons-Wizards/dp/0786965"
                                + "606/ref=pd_bxgy_b_text_z");
                        break;
                    case 2:
                        System.out.println("\nhttp://www.amazon.com/Monster-"
                                + "Manual-Core-Rulebook-Wizards/dp/0786965614"
                                + "/ref=pd_rhf_se_p_img_1");
                        break;
                    case 3:
                        System.out.println("\nhttp://www.amazon.com/Dungeon-"
                                + "Masters-Guide-Core-Rulebook/dp/0786965622"
                                + "/ref=pd_bxgy_b_text_y");
                        break;
                    default:
                        System.out.println("Invalid Choice");
                }
                break;
            case 13:
                System.out.println("http://www.barnesandnoble.com/w/george-r-r-"
                        + "martins-a-game-of-thrones-5-book-boxed-set-martin-"
                        + "george-r-r/1117519253?ean=9780345535528");
                break;
            default:
                System.out.println("Invalid Choice");
                
                   
        }
        
        
        
    }
    
}
