import java.util.*;

public class bills
{
    public static void main(String[]args)
    {
        Scanner in = new Scanner(System.in);
        int bills[] = new int[6];
        int money[] = new int[] {1, 5, 10, 20, 50, 100};
        
        int largest = 0;
        int num = 0;
        
        for( int n = 0; n < 6; n ++)
        {
            bills[n] = in.nextInt() * money[n];
        }
        for( int n = 0; n < 6; n ++)
        {
            if( bills[n] >= largest )
            {
                largest = bills[n];
                num = n;
            }
        }
        if( num == 0 )
            System.out.print("1");
        else if( num == 1 )
            System.out.print("5");
        else if( num == 2 )
            System.out.print("10");
        else if( num == 3 )
            System.out.print("20");
        else if( num == 4 )
            System.out.print("50");
        else if( num == 5 )
            System.out.print("100");
    }
}
