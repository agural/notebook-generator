// .vimrc
syn on
set mouse=a sw=4 ts=4 ai si nu wrap
nnoremap ; :
map H :'<,'>!./hash.sh<CR>

// Hash Utility
#!/bin/bash
input=$(cat /dev/stdin)
hash=$(cpp -fpreprocessed -P <(echo "$input")|sed ':a;N;$!ba;s/[ \t\n]//g'|md5sum)
echo "// start: ${hash}"
echo "$input"
echo "// end"

// Terminal: comparing generated output to sample output
./my_program < sample.in | diff sample.out -

