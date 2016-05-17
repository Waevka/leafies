
public class Step {
  private Object[][] table;
  
  Step(int height, int width, int[] board){
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
}
