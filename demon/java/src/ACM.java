import java.net.SocketOption;
        import java.util.*;
        import java.math.*;
        import java.io.*;


public class ACM {
    public static int prime[] = new int[10000];
    public static BigInteger getFactorSum(int no)
    {
        if(no <= 1) return BigInteger.valueOf(3);
        return getFactorSum(no-1).multiply(BigInteger.valueOf(prime[no] + 1));
    }

    public static String getDiv(BigInteger sum, BigInteger prod)
    {
        BigInteger gcd = sum.gcd(prod);
        return prod.divide(gcd)+"/"+sum.divide(gcd);
    }

    public static void main(String[] args) {
        boolean flag[] = new boolean[10000];
        String str[] = new String[100];
        BigInteger bi[] = new BigInteger[100];
        for(int i = 2; i < 10000; i++)
        {
            if(!flag[i]) prime[++prime[0]] = i;
            for(int j = 1; j <= prime[0] && i*prime[j]<10000; j++)
            {
                flag[prime[j]*i] = true;
                if(i % prime[j] == 0) break;
            }
        }
        BigInteger a = BigInteger.ONE;
        for(int i = 1; i<100; i++)
        {
            a = a.multiply(BigInteger.valueOf(prime[i]));
            str[i] = getDiv(getFactorSum(i),a);
            bi[i] = a;
        }

        Scanner sc = new Scanner(System.in);
        int times;
        times = sc.nextInt();
        while(times --> 0)
        {
            BigInteger n = sc.nextBigInteger();
//            if(n.equals(BigInteger.ONE))
//            {
//                System.out.println("1");
//                continue;
//            }
//            if(n.equals(BigInteger.ONE))
//            {
//                System.out.println("1/1");
//                continue;
//            }

//            else if(n.equals(BigInteger.valueOf(2)))
//            {
//                System.out.println("2/3");
//                continue;
//            }
            for(int i = 1; i < 100; i++)
            {
                if(n.compareTo(bi[i]) < 0)
                {
                    System.out.println(str[i-1]);
                    break;
                }
            }
        }

//        Scanner sc = new Scanner(System.in);
//        BigInteger a=sc.nextBigInteger(36);
//        System.out.println(a.toString(10));
    }
}