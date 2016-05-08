import java.awt.FlowLayout;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.Arrays;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.WindowConstants;

public class Visual extends JFrame implements ActionListener {
  public int[] board;
  public String moves;
  
  // GUI
  private Label currentMove;
  
  //Board properties
  private int bHeight;
  private int bWidth;
  private int totalMoves;
  
  public Visual(){
    
    setLayout(new FlowLayout());
    
    currentMove = new Label("Moves");
    add(currentMove);
    
    setTitle("Fifteen");
    setSize(200,200);
    
    setVisible(true);
    this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
  }
  
  public void loadInput(){
    Scanner scanner = null;
    int i = 0;
    
    try {
      URL url = getClass().getResource("input.txt");
      File in = new File(url.getPath());
      scanner = new Scanner(in);
      this.bHeight = scanner.nextInt( );
      this.bWidth = scanner.nextInt( );
      
      this.board = new int[this.bHeight * this.bWidth];
      
      while(scanner.hasNextInt( )){
        board[i] = scanner.nextInt( );
        i++;
      }
      
      
    } catch ( FileNotFoundException e ) {
      System.out.println( "input.txt - not found!" );
      e.printStackTrace();
    } finally {
      if(scanner != null) scanner.close();
    }
    
  }
  
  public void loadOutput(){
    Scanner scanner = null;
    try {
      URL url = getClass().getResource("output.txt");
      File in = new File(url.getPath());
      scanner = new Scanner(in);
      this.totalMoves = scanner.nextInt( );
      this.moves = scanner.next( );
      
    } catch ( FileNotFoundException e ) {
      System.out.println( "output.txt - not found!" );
      e.printStackTrace();
    } finally {
      if(scanner != null) scanner.close();
    }
  }
  
  public static void main( String [ ] args ) {
    
    Visual v = new Visual();
    v.loadInput();
    v.loadOutput();
    System.out.println( Arrays.toString( v.board ) );
    System.out.println( v.moves );
  }

  @Override
  public void actionPerformed( ActionEvent e ) {
    // TODO Auto-generated method stub
    
  }

}
