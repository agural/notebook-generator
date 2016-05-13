// .vimrc
syn on
set mouse=a sw=4 ts=4 ai si nu wrap
nnoremap ; :

// Terminal: comparing generated output to sample output
./my_program < sample.in | diff sample.out -

