#!/usr/bin/sh

./bin/notebookgen src/ gen/notebook.pdf 
evince gen/notebook.pdf &

