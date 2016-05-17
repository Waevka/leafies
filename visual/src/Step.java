
public class Step {
  private int[] oldBoard;
  private Object[][] table;
  private int zeroPos;
  
  Step(int height, int width, int[] board, int zeroPos){
    this.zeroPos = zeroPos;
    oldBoard = board;
    table = new Object[height][width];
    int i = 0;
    int row = 0;
    for(int x : board){
      //System.out.println( x );
      table[row][i - (row*width)] = x;
      i++;
      //System.out.println( i%(width) );
      if(i%(width) == 0) row++;
    }
  }
  
  public Object[][] getTable(){
    return this.table;
  }
  
  public int[] getBoard(){
    return this.oldBoard;
  }
  
  public int getZeroPos(){
    return this.zeroPos;
  }
}
