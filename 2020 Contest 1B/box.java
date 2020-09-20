import java.util.*;
import java.util.Arrays;
public class box
{
    public static void main(String[]args)
    {
        Scanner in = new Scanner(System.in);
        int base = in.nextInt();
        int blocks = in.nextInt();
        int[][] bricks = new int[blocks][3];
        int[] height = new int[base];
        for( int n = 0; n < blocks; n++ )
        {
            for( int i = 0; i < 3; i++ )
            {
                bricks[n][i] = in.nextInt();
            }
        }
        
        for( int n = 0; n < blocks; n++ )
        {
            int len = bricks[n][0];
            int hei = bricks[n][1];
            int col = bricks[n][2] - 1;
            int cols = col + len;
            int i = col;
            int temp = hei;
            if( n != 0)
            {
                for( i = col; i < cols; i++ )
                {
                    if( (height[i] != 0) && (temp < height[i] + hei) )
                        temp = height[i] + hei;
                }
            }
            for( i = col; i < cols; i++ )
            {
                height[i] = temp;
            }
        }
        
        Arrays.sort(height);
        System.out.println(height[height.length - 1]);
    }
}