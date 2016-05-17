import java.util.ArrayList;
import java.util.Arrays;

public class StepCreator {
  public StepCreator(){}
  
  public ArrayList<Step> createSteps(String moves, int[] board, int height, int width,
      int totalMoves, int zeroPos){
    
    ArrayList<Step> steps = new ArrayList<Step>( );
    
    Step first = new Step(height, width, board, zeroPos);
    //System.out.println( Arrays.toString(first.getTable( )[0] ) );
    steps.add( first );
    
    for(int i = 0; i<totalMoves; i++){
      char c = moves.charAt( i );
      int moveIndex = countMoveIndex(c, width);
      int[] newBoard = new int[height*width];
      System.arraycopy( steps.get( i ).getBoard( ), 0, newBoard, 0, height*width );
      swapTiles(newBoard, moveIndex, steps.get( i ).getZeroPos( ));
      //System.out.println( Arrays.toString(newBoard) );
      int newZero = steps.get( i ).getZeroPos( ) + moveIndex;
      //System.out.println( newZero );
      Step s = new Step(height, width, newBoard, newZero);
      steps.add( s );
    }
    
    return steps;
  }
  
  private int countMoveIndex(char c, int width){
    int ret = 0;
    if(c == 'D'){
      ret = width;
    }
    if(c == 'G'){
      ret = -width;
    }
    if(c == 'L'){
      ret = -1;
    }
    if(c == 'P'){
      ret = 1;
    }
    return ret;
  }
  
  private void swapTiles(int [] board, int moveIndex, int zeroPos){
    int temp = board[zeroPos];
    board[zeroPos] = board[zeroPos + moveIndex];
    board[zeroPos + moveIndex] = temp;
  }

}
