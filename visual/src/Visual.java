import java.awt.FlowLayout;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.WindowConstants;
import javax.swing.table.DefaultTableModel;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JTable;

public class Visual extends JFrame implements ActionListener {
  public static int[] board;
  public static String moves;
  
  public static ArrayList<Step> steps;
  
  // GUI
  private Label currentMove;
  private String[] columnNames;
  
  //Board properties
  private static int bHeight;
  private static int bWidth;
  private static int totalMoves;
  private JTable table;
  
  public Visual(){
    getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    
    currentMove = new Label("LOADING");
    currentMove.setAlignment(Label.CENTER);
    getContentPane().add(currentMove);
    
    setTitle("Fifteen");
    setSize(200,200);

    table = new JTable();
    getContentPane().add(table);
    
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
      Visual.bHeight = scanner.nextInt( );
      Visual.bWidth = scanner.nextInt( );
      
      Visual.board = new int[Visual.bHeight * Visual.bWidth];
      
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
      Visual.moves = scanner.next( );
      
    } catch ( FileNotFoundException e ) {
      System.out.println( "output.txt - not found!" );
      e.printStackTrace();
    } finally {
      if(scanner != null) scanner.close();
    }
  }
  
  public void fillColumnNames(){
    this.columnNames = new String[bWidth];
    for(int i = 0; i<bWidth; i++){
      this.columnNames[i] = Integer.toString( i );
    }
  }
  
  public void fillTable(Step s){
    DefaultTableModel model = new DefaultTableModel(s.getTable( ), columnNames);
    table.setModel( model );
  }
  
  public static void main( String [ ] args ) {
    
    Visual v = new Visual();
    v.loadInput();
    v.loadOutput();
    System.out.println( Arrays.toString( Visual.board ) );
    //System.out.println( Visual.moves );
    v.fillColumnNames();
    StepCreator s = new StepCreator();
    steps = s.createSteps( moves, board, bHeight, bWidth, totalMoves );
    v.fillTable(steps.get( 0 ));
  }

  @Override
  public void actionPerformed( ActionEvent e ) {
    // TODO Auto-generated method stub
    
  }

}
