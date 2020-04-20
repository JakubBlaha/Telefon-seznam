**Co je to uint?**

Je to unsigned int. Bezznamnkové číslo. Nemůže jít do záportu, ale zato muže jít do dvakrát většího kladu.

**Jak editnu strukturu?**

https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards

`MY_TYPE a = { .flag = true, .value = 123, .stuff = 0.456 };`

**Jak napíšu v C multiline string do sourcu?**

https://jameshfisher.com/2016/11/30/c-multiline-literal/

**Jak poznám, že jsou dva stringy stejné?**

`strcmp(a, b) == 0`


**Jak spojím více .c souborů?**

https://stackoverflow.com/questions/15622409/how-to-link-multiple-implementation-files-in-c

https://medium.com/@markkevinbaltazar/how-to-compile-link-and-build-a-c-program-using-gcc-578071c79a76

**Jak zkompiluji a pustím ve jednom commandu? (Poweshell)**

`taskkill /IM 'program.exe' /F; gcc -o program main.c data.c; if($?) {./program.exe;}`

Jak to funguje?
 - `taskkill /IM 'program.exe' /F` - shodí `program.exe`, pokud nám zůstal viset v paměti.
 - `gcc -o program main.c data.c` - zlinkuje a zkompiluje program do spustiteln0ho souboru `program.exe`
 - `if($?) {./program.exe;}` - pokud byl výsledek předešlého commandu (kompilování) úspěšný, spustí `program.exe`
 - `;` - rozděluje jednotlivé commandy na jednom řádku