
import java.math.BigInteger;
import java.math.*;
import java.util.*;

public class Main {


    public static void main(String[] args) {
        int kase;
        Scanner cin = new Scanner(System.in);
        kase = cin.nextInt();
        while(kase -- > 0) {
            BigInteger a, b, c, d, g;
            a = cin.nextBigInteger();
            g = a.subtract(BigInteger.valueOf(1));
            b = (a.multiply(g).divide(BigInteger.valueOf(2)));
            
            //c = myBigNumSqrt(a);
            //d = myBigNumSqrt(b);
            c = sqrt(a);
            d = sqrt(b);
            boolean e= false, f = false;
            // System.out.println(c + "  "+ d);
            
            if (c.multiply(c).equals(a)) e = true;
            if (d.multiply(d).equals(b)) f = true;
            
            if(e && f) {
            	System.out.println("Arena of Valor");
            } else if (e) {
            	System.out.println("Hearth Stone");
            } else if (f) {
            	System.out.println("Clash Royale");
            } else {
            	System.out.println("League of Legends");
            }
        }
    }
    
  
    
    private static BigInteger sqrt(BigInteger n) {
		BigInteger a;
		BigInteger b;
		
		//a为10的，n的长度除以二的，十次方
		a=BigInteger.TEN.pow((int)n.toString().length()/2);
		//b=n/a
		b=n.divide(a);
		
		//如果，a!=b,或者a和b的差相差不为0
		while(!(a.equals(b)||a.equals(b.add(new BigInteger("-1")))||b.equals(a.add(new BigInteger("-1"))))){
				
			//a=(a+b)/2
			a=a.add(b).divide(new BigInteger("2"));
			//b=n/a;
			b=n.divide(a);
		}
		//取a,b中较小的一个
		if (a.equals(b.add(new BigInteger("-1")))) {
			return a;
		}
		
		return b;
	}


}
