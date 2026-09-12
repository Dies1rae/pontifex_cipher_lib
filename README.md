# Pontifex_cipher_lib

## Sinopsys:
&emsp;Small libs representing Bruce Schneier PONTIFEX(SOLITARE) crypto algorithm work<br>
&emsp;Inspired by Nil Stivenson CRYPTONOMICON book<br>
&emsp;This repository contains full functional cryptolib and some binary example builds with different optargs for encrypt or decrypt some text info<br>

## Requires:
&emsp;CMAKE >= 3.26<br>
&emsp;C++ Compiler with stdc++17<br>

## Build:
&emsp;mkdir -p ./pontifex/build && cd ./pontifex<br>
&emsp;git clone https://github.com/Dies1rae/pontifex_cipher_lib<br>
&emsp;cd ./build<br>
&emsp; cmake ../ && make -j<br>

## Run:
&emsp;Usage: pontifexcmd [enc option] [in option] |text/file| [out option] |text/file| [key option] |text/file|<br>
&emsp;Examples:<br>
&emsp;&emsp;pontifexcmd -e -i |ClearText arg| -o |stdout CipherText| -k |Key arg|<br>
&emsp;&emsp;pontifexcmd -e -I |ClearText filepath| -O |CipherText filepath| -K |Key filepath|<br>
&emsp;&emsp;pontifexcmd -d -i |CipherText arg| -o |stdout ClearText| -k |Key arg|<br>
&emsp;&emsp;pontifexcmd -d -I |CipherText filepath| -O |ClearText filepath| -K |Key filepath|<br>
&emsp;&emsp;pontifexcmd -g  -k |stdout new generated key|<br>
&emsp;&emsp;pontifexcmd -g  -K |Save new generated key to filepath|<br>
