#grep -rl '\t' ./ | xargs sed -i 's/\t/    /g'
# :args ./src/**/*.* | argdo execute "normal gg=G" | update
find ./src -type f -exec sed -i "s/\t/    /g" {} \;
