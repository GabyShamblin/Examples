import java.util.*;
import java.util.Arrays;
public class digit
{
    public static void main(String[]args)
    {
        Scanner in = new Scanner(System.in);
        String bot = in.next();
        String top = in.next();
        String digit = in.next();
        
        if( bot.equals(top) )
        {
            int occ = 0;
            String[] nums = top.split("");
            for( int n = 0; n < nums.length; n++ )
            {
                if( nums[n].equals(digit) )
                    occ++;
            }
            System.out.println(occ);
        }
        else
        {
            int botInt = Integer.parseInt(bot);
            int topInt = Integer.parseInt(top);
            
            System.out.println(run(botInt, topInt, digit));
        }
    }
    
    public static int run(int bot, int top, String dig)
    {
        int occ = 0;
        while( bot <= top )
        {
            String num = Integer.toString(bot);
            String[] nums = num.split("");
            for( int i = 0; i < num.length(); i++ )
            {
                if( nums[i].equals(dig) )
                    occ++;
            }
            bot++;
        }
        
        return occ;
    }
}
