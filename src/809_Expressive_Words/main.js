
/**
 * @param {string} S
 * @param {string[]} words
 * @return {nummber}
 */

//Runtime: 80 ms, faster than 88.62% 
//Memory Usage: 39.2 MB, less than 93.50%
var expressiveWords = function(S, words) {
  var isStretchy = function(w) {
    var i = 0, j = 0;
    while (i < S.length && j < w.length) {
      var e1 = i;
      var e2 = j;
      while (i < S.length && S[e1] == S[i]) {
        i++;
      }
      while (j < w.length && w[e2] == w[j]) {
        j++;
      }
      // 两个while之后，i和e1的char必定不同
      if (S[e1] != w[e2]
        || ((i-e1 < j-e2)
        || ((i-e1 > j-e2) && (i-e1 < 3)))) {
        return false;
      }
      //i = e1;大意啦大意啦，死循环啦
      //j = e2;
      e1 = i;
      e2 = j;
    }
    return ((i == S.length && j == w.length)? true: false);
  };
  var rtn = 0;
  words.forEach(w => {
    if (isStretchy(w)) {
      rtn++;
    }
  });

  return rtn;
};

// js有点像tcl script，并不需要main函数，以下操作只是让函数立即执行而已
!function(){
  var rtn;
  var S;
  var words;

  S = "abcd";
  words = ["abc"];
  rtn = expressiveWords(S, words); 
  console.log("expect value = 0, actual value = " + rtn);
  
  S = "heeellooo";
  words = ["hello", "hi", "helo"];
  rtn = expressiveWords(S, words); 
  console.log("expect value = 1, actual value = " + rtn);
}();

