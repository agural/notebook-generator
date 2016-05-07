# notebook-generator
(Auto) generate notebooks from your source code. Useful for ACM-ICPC


## Dependencies
pdflatex

    [sudo] aptitude install texlive

nodejs

	[sudo] aptitude install nodejs

npm

	[sudo aptitude install npm

nodejs module `through2`

    [sudo] npm install through2

## Use

    sh run.sh

The generated pdf is located at ./gen/notebook.pdf and will be launched automatically (you may need to modify `run.sh` to accommodate your local pdf reader.

## Files

The notebook generator will add your source code with syntax highlight, additionally
you can add .tex files which will be rendered as latex code.

## Notes:

- Try to use up to 3 "levels" in your source code.
- Use spaces insead of underscore (in the filenames) to print a prettier TOC.
