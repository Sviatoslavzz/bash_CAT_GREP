touch 3.txt
echo "Hello
World!" > 1.txt
echo "row number one

row number three
tab here	<<<<
another tab	<<
two empty lines below


just line
ﬂ" > 2.txt
echo "Here is some text!
Bro" > 4.txt
touch log.txt
echo "TESTS FOR CAT:" >> log.txt

echo "----------TEST 1: show non empty file----------" >> log.txt
diff -y -q <(cat 1.txt) <(./cat 1.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 2: show non empty files----------" >> log.txt
diff -y -q <(cat 1.txt 2.txt 4.txt) <(./cat 1.txt 2.txt 4.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 3: show empty file----------" >> log.txt
diff -y -q <(cat 3.txt) <(./cat 3.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 4: 1 empty file with non empty files mixed----------" >> log.txt
diff -y -q <(cat 1.txt 2.txt 3.txt 4.txt) <(./cat 1.txt 2.txt 3.txt 4.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 5: non existing file---------" >> log.txt 
cat abracadabra.txt >& out1.txt
./cat abracadabra.txt >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

echo "----------TEST 6: non existing file with existing mixed---------" >> log.txt
cat 1.txt abracadabra.txt 2.txt >& out1.txt
./cat 1.txt abracadabra.txt 2.txt >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

echo "----------TEST 7: files with key -n---------" >> log.txt
diff -y -q <(cat -n 1.txt 2.txt) <(./cat -n 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 8: files with key --number---------" >> log.txt
diff -y -q <(cat --number 1.txt 2.txt) <(./cat --number 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 9: files with key -b---------" >> log.txt
diff -y -q <(cat -b 1.txt 2.txt) <(./cat -b 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 10: files with key --number-nonblank---------" >> log.txt
diff -y -q <(cat --number-nonblank 1.txt 2.txt) <(./cat --number-nonblank 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 11: files with key -e---------" >> log.txt
diff -y -q <(cat -e 1.txt 2.txt) <(./cat -e 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 12: files with key -E---------" >> log.txt
diff -y -q <(cat -E 1.txt 2.txt) <(./cat -E 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 13: files with key -s---------" >> log.txt
diff -y -q <(cat -s 1.txt 2.txt) <(./cat -s 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 14: files with key --squeeze-blank---------" >> log.txt
diff -y -q <(cat --squeeze-blank 1.txt 2.txt) <(./cat --squeeze-blank 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 15: files with key -t---------" >> log.txt
diff -y -q <(cat -t 1.txt 2.txt) <(./cat -t 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 16: files with key -T---------" >> log.txt
diff -y -q <(cat -T 1.txt 2.txt) <(./cat -T 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 17: mixed keys -n -s -b -t -e---------" >> log.txt
diff -y -q <(cat -n -s -b -t -e 1.txt 2.txt) <(./cat -n -s -b -t -e 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 18: mixed keys -nsbte---------" >> log.txt
diff -y -q <(cat -nsbte 1.txt 2.txt) <(./cat -nsbte 1.txt 2.txt) >> log.txt && echo "OK" >> log.txt

echo "File3
1	2	3


<CR><LF>
EndFile3
" > 5.txt

echo "




" > 6.txt

# \n file and multiline \n file testing:
echo "
\n file and multiline \n file testing:" >> log.txt
echo "----------TEST 19:---------" >> log.txt
diff -y -q <(cat 5.txt) <(./cat 5.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 20:---------" >> log.txt
diff -y -q <(cat 6.txt) <(./cat 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 21:---------" >> log.txt
diff -y -q <(cat 5.txt 6.txt) <(./cat 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 22: files with key -n---------" >> log.txt
diff -y -q <(cat -n 5.txt 6.txt) <(./cat -n 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 23: files with key --number---------" >> log.txt
diff -y -q <(cat --number 5.txt 6.txt) <(./cat --number 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 24: files with key -b---------" >> log.txt
diff -y -q <(cat -b 5.txt 6.txt) <(./cat -b 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 25: files with key --number-nonblank---------" >> log.txt
diff -y -q <(cat --number-nonblank 5.txt 6.txt) <(./cat --number-nonblank 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 26: files with key -e---------" >> log.txt
diff -y -q <(cat -e 5.txt 6.txt) <(./cat -e 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 27: files with key -E---------" >> log.txt
diff -y -q <(cat -E 5.txt 6.txt) <(./cat -E 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 28: files with key -s---------" >> log.txt
diff -y -q <(cat -s 5.txt 6.txt) <(./cat -s 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 29: files with key --squeeze-blank---------" >> log.txt
diff -y -q <(cat --squeeze-blank 5.txt 6.txt) <(./cat --squeeze-blank 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 30: files with key -t---------" >> log.txt
diff -y -q <(cat -t 5.txt 6.txt) <(./cat -t 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 31: files with key -T---------" >> log.txt
diff -y -q <(cat -T 5.txt 6.txt) <(./cat -T 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 32: mixed keys -n -s -b -t -e---------" >> log.txt
diff -y -q <(cat -n -s -b -t -e 5.txt 6.txt) <(./cat -n -s -b -t -e 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 33: mixed keys -nsbte---------" >> log.txt
diff -y -q <(cat -nsbte 5.txt 6.txt) <(./cat -nsbte 5.txt 6.txt) >> log.txt && echo "OK" >> log.txt

echo "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim.


3 TAB 			 LINE
Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus.

Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi.

Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunc.
 	

 !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_abcdefghijklmnopqrstuvwxyz{|}~ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ" > ctrl.txt

echo "----------TEST 34: CTRL symbols---------" >> log.txt
diff -y -q <(cat ctrl.txt) <(./cat ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 35: CTRL symbols -v ---------" >> log.txt
diff -y -q <(cat -v ctrl.txt) <(./cat -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 36: files with key -n---------" >> log.txt
diff -y -q <(cat -n -v ctrl.txt) <(./cat -n -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 37: files with key --number---------" >> log.txt
diff -y -q <(cat --number -v ctrl.txt) <(./cat --number -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 38: files with key -b---------" >> log.txt
diff -y -q <(cat -b -v ctrl.txt) <(./cat -b -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 39: files with key --number-nonblank---------" >> log.txt
diff -y -q <(cat --number-nonblank -v ctrl.txt) <(./cat --number-nonblank -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 40: files with key -e---------" >> log.txt
diff -y -q <(cat -e ctrl.txt) <(./cat -e ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 41: files with key -E---------" >> log.txt
diff -y -q <(cat -E -v ctrl.txt) <(./cat -E -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 42: files with key -s---------" >> log.txt
diff -y -q <(cat -s -v ctrl.txt) <(./cat -s -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 43: files with key --squeeze-blank---------" >> log.txt
diff -y -q <(cat --squeeze-blank -v ctrl.txt) <(./cat --squeeze-blank -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 44: files with key -t---------" >> log.txt
diff -y -q <(cat -t ctrl.txt) <(./cat -t ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 45: files with key -T---------" >> log.txt
diff -y -q <(cat -T -v ctrl.txt) <(./cat -T -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 46: mixed keys -n -s -b -t -e---------" >> log.txt
diff -y -q <(cat -n -s -b -t -e -v ctrl.txt) <(./cat -n -s -b -t -e -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 47: mixed keys -nsbte---------" >> log.txt
diff -y -q <(cat -nsbte -v ctrl.txt) <(./cat -nsbte -v ctrl.txt) >> log.txt && echo "OK" >> log.txt

# Different flag locations test
echo "
Different flag locations tests"  >> log.txt
echo "----------TEST 48: files with key -n---------" >> log.txt
diff -y -q <(cat 1.txt 2.txt -n) <(./cat 1.txt 2.txt -n) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 49: files with key -b---------" >> log.txt
diff -y -q <(cat 1.txt 2.txt -b) <(./cat -b 1.txt 2.txt -b) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 50: files with key -e---------" >> log.txt
diff -y -q <(cat -n 1.txt 2.txt -e) <(./cat -n 1.txt 2.txt -e) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 51: files with key -s---------" >> log.txt
diff -y -q <(cat -s 1.txt -n 2.txt) <(./cat -s 1.txt -n 2.txt) >> log.txt && echo "OK" >> log.txt

echo "----------TEST 52: files with key -t---------" >> log.txt
diff -y -q <(cat -t 1.txt -n 2.txt -s) <(./cat -t 1.txt -n 2.txt -s) >> log.txt && echo "OK" >> log.txt

# -- without flags tests
echo "
-- WITHOUT FLAGS TESTS"  >> log.txt

echo "----------TEST 53: -- 1.txt 2.txt---------" >> log.txt
cat -- 1.txt 2.txt >& out1.txt
./cat -- 1.txt 2.txt >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

echo "----------TEST 54: -- 1.txt -- 2.txt---------" >> log.txt
cat -- 1.txt -- 2.txt >& out1.txt
./cat -- 1.txt -- 2.txt >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

echo "----------TEST 55: -- 1.txt -- 2.txt -n---------" >> log.txt
cat -- 1.txt -- 2.txt -n >& out1.txt
./cat -- 1.txt -- 2.txt -n >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

echo "----------TEST 56: -nE -- 1.txt -- 2.txt---------" >> log.txt
cat -nE -- 1.txt -- 2.txt >& out1.txt
./cat -nE -- 1.txt -- 2.txt >& out2.txt
diff -y -q out1.txt out2.txt >> log.txt && echo "OK" >> log.txt

rm 1.txt 2.txt 3.txt 4.txt 5.txt 6.txt ctrl.txt out1.txt out2.txt