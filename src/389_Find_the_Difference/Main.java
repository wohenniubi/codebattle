
class Solution {
    //Runtime: 1 ms, faster than 98.58%
    //Memory Usage: 38.9 MB, less than 17.96%
    public char findTheDifference(String s, String t) {
        //char rtn = t[t.length()-1]; // 因为t比s长1，直接取t最后的一个字符
        char rtn = t.charAt(t.length()-1);// 注意String要用charAt()，要用length()
        
        // 然后就可以把s和t一起处理了
        for (int i = 0; i < s.length(); ++i) {
            // rtn ^= s[i];
            // rtn ^= t[i];
            rtn ^= s.charAt(i);
            rtn ^= t.charAt(i);
        }
        
        return rtn;
    }
}

public class Main {
  public static void main(String[] args) {
    Solution gua = new Solution();
    String s, t;
    char rtn;

    s = new String("abcd");
    t = new String("abcde");
    rtn = gua.findTheDifference(s, t);
    System.out.println("expect value = e, actual value = " + rtn);
    
    s = new String("ea");
    t = new String("aae");
    rtn = gua.findTheDifference(s, t);
    System.out.println("expect value = a, actual value = " + rtn);
    
    s = new String("");
    t = new String("t");
    rtn = gua.findTheDifference(s, t);
    System.out.println("expect value = t, actual value = " + rtn);
  }
}

