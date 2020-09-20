import java.util.*;
import java.util.Arrays;
public class birth
{
    public static void main(String[]args)
    {
        Scanner in = new Scanner(System.in);
        int num = in.nextInt();
        String birth[] = new String[num];
        
        for( int n = 0; n < num; n++)
        {
            birth[n] = in.next();
        }
        String[] unique = Arrays.stream(birth).distinct().toArray(String[]::new);
        System.out.println(unique.length);
    }
}
